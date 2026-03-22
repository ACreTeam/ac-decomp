/* Metal renderer: device, command queue, pipeline management, draw-list submission.
 * Implements the plat_gx_* and plat_metal_* API declared in gx_draw_internal.h.
 *
 * Rendering model:
 *   GXBegin/GXEnd accumulate PlatVertex records into a per-draw DrawCmd.
 *   GXCopyDisp (→ plat_metal_present_frame) drains the draw list and submits
 *   one Metal command buffer that renders every accumulated draw call, then
 *   presents the drawable.
 */
#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>
#include "platform/platform.h"
#include "gx_draw_internal.h"
#include "gx_state.h"
#include <dolphin/gx.h>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <string.h>
#include <stdio.h>

/* ------------------------------------------------------------------ */
/* Per-draw-call command                                                */
/* ------------------------------------------------------------------ */
struct DrawCmd {
    std::vector<PlatVertex> verts;
    MTLPrimitiveType         primType;
    __strong id<MTLTexture>  texture;      /* nil → use white fallback */
    float                    model[3][4];  /* 3×4 row-major model matrix */
    float                    proj[4][4];   /* 4×4 row-major projection matrix */
    bool                     blend;        /* alpha blending enabled? */
    bool                     depthTest;
    bool                     depthWrite;
};

/* ------------------------------------------------------------------ */
/* MSL shader source                                                    */
/* ------------------------------------------------------------------ */
static const char* kShaderSrc = R"MSL(
#include <metal_stdlib>
using namespace metal;

struct Vtx {
    float3 pos   [[attribute(0)]];
    float4 color [[attribute(1)]];
    float2 uv    [[attribute(2)]];
};

struct VOut {
    float4 pos   [[position]];
    float4 color;
    float2 uv;
};

/* Row-major matrices passed as arrays of float4 rows */
struct Uniforms {
    float4 model[3];   /* 3×4 position matrix (row per row) */
    float4 proj[4];    /* 4×4 projection matrix (row per row) */
};

vertex VOut vert_main(Vtx in [[stage_in]],
                      constant Uniforms& u [[buffer(1)]]) {
    float4 wp = float4(in.pos, 1.0);
    /* Transform to eye space using the 3×4 model matrix */
    float4 ep = float4(
        dot(wp, u.model[0]),
        dot(wp, u.model[1]),
        dot(wp, u.model[2]),
        1.0
    );
    /* Project using the 4×4 projection matrix */
    float4 cp = float4(
        dot(ep, u.proj[0]),
        dot(ep, u.proj[1]),
        dot(ep, u.proj[2]),
        dot(ep, u.proj[3])
    );
    /* Remap GC clip-space depth [-w, w] → Metal [0, w] */
    cp.z = (cp.z + cp.w) * 0.5;

    VOut out;
    out.pos   = cp;
    out.color = in.color;
    out.uv    = in.uv;
    return out;
}

fragment float4 frag_main(VOut               in   [[stage_in]],
                           texture2d<float>   tex  [[texture(0)]],
                           sampler            samp [[sampler(0)]]) {
    return in.color * tex.sample(samp, in.uv);
}
)MSL";

/* ------------------------------------------------------------------ */
/* Global Metal objects                                                 */
/* ------------------------------------------------------------------ */
static id<MTLDevice>                g_device      = nil;
static id<MTLCommandQueue>          g_cmdQueue    = nil;
static CAMetalLayer*                g_metalLayer  = nil;
static id<MTLTexture>               g_depthTex    = nil;
static id<MTLTexture>               g_whiteTex    = nil;
static id<MTLRenderPipelineState>   g_pipeOpaque  = nil;
static id<MTLRenderPipelineState>   g_pipeBlend   = nil;
static id<MTLDepthStencilState>     g_dssDepthOn  = nil;
static id<MTLDepthStencilState>     g_dssDepthOff = nil;
static id<MTLSamplerState>          g_sampler     = nil;

/* ------------------------------------------------------------------ */
/* Draw list — filled by GXBegin/GXEnd, drained by present_frame       */
/* ------------------------------------------------------------------ */
static std::vector<DrawCmd> s_drawList;
static std::mutex           s_drawMtx;

/* Per-draw accumulator (filled during a GXBegin…GXEnd pair) */
static DrawCmd   s_cur;
static bool      s_inDraw      = false;
static PlatVertex s_curVtx;
static bool      s_vtxStarted  = false;

/* Active texture per GXTexMapID slot */
static __strong id<MTLTexture> g_activeTextures[8];

/* Texture decode cache: GC data pointer → MTLTexture */
static std::unordered_map<uintptr_t, __strong id<MTLTexture>> g_texCache;

/* ------------------------------------------------------------------ */
/* Forward declarations                                                 */
/* ------------------------------------------------------------------ */
static void rebuild_depth_tex(NSUInteger w, NSUInteger h);
static void make_white_tex(void);
static id<MTLRenderPipelineState> build_pipeline(id<MTLFunction> vs,
                                                  id<MTLFunction> fs,
                                                  bool blend);
static MTLPrimitiveType gc_to_mtl_prim(GXPrimitive p);
static void convert_quads(std::vector<PlatVertex>& out,
                          const std::vector<PlatVertex>& in);
static void convert_fan(std::vector<PlatVertex>& out,
                        const std::vector<PlatVertex>& in);

/* ================================================================== */
/* Public C API                                                         */
/* ================================================================== */
extern "C" {

/* ---- Initialise Metal (called from vi_shim.cpp once layer is ready) */
void plat_metal_init(void* layer_ptr) {
    g_metalLayer = (__bridge CAMetalLayer*)layer_ptr;
    g_device     = MTLCreateSystemDefaultDevice();
    if (!g_device) {
        fprintf(stderr, "[Metal] No Metal device available\n");
        return;
    }
    g_metalLayer.device             = g_device;
    g_metalLayer.pixelFormat        = MTLPixelFormatBGRA8Unorm;
    g_metalLayer.displaySyncEnabled = YES;
    g_cmdQueue = [g_device newCommandQueue];
    fprintf(stderr, "[Metal] Device: %s\n", [g_device.name UTF8String]);

    /* Compile shaders */
    NSError* err = nil;
    id<MTLLibrary> lib =
        [g_device newLibraryWithSource:@(kShaderSrc) options:nil error:&err];
    if (!lib) {
        fprintf(stderr, "[Metal] Shader error: %s\n",
                [[err localizedDescription] UTF8String]);
        return;
    }
    id<MTLFunction> vs = [lib newFunctionWithName:@"vert_main"];
    id<MTLFunction> fs = [lib newFunctionWithName:@"frag_main"];
    g_pipeOpaque = build_pipeline(vs, fs, false);
    g_pipeBlend  = build_pipeline(vs, fs, true);

    /* Depth-stencil states */
    MTLDepthStencilDescriptor* dsd = [MTLDepthStencilDescriptor new];
    dsd.depthCompareFunction = MTLCompareFunctionLessEqual;
    dsd.depthWriteEnabled    = YES;
    g_dssDepthOn  = [g_device newDepthStencilStateWithDescriptor:dsd];
    dsd.depthWriteEnabled    = NO;
    g_dssDepthOff = [g_device newDepthStencilStateWithDescriptor:dsd];

    /* Linear repeat sampler */
    MTLSamplerDescriptor* sd = [MTLSamplerDescriptor new];
    sd.minFilter    = MTLSamplerMinMagFilterLinear;
    sd.magFilter    = MTLSamplerMinMagFilterLinear;
    sd.sAddressMode = MTLSamplerAddressModeRepeat;
    sd.tAddressMode = MTLSamplerAddressModeRepeat;
    g_sampler = [g_device newSamplerStateWithDescriptor:sd];

    rebuild_depth_tex(640, 480);
    make_white_tex();
}

/* ---- Vertex accumulation (called from gx_vert.cpp) ---------------- */

void plat_gx_start_vertex(void) {
    /* Commit the previous vertex (if any) before starting a new one */
    if (s_vtxStarted && s_inDraw) {
        s_cur.verts.push_back(s_curVtx);
    }
    /* Reset current vertex; default colour = white, fully opaque */
    s_curVtx   = {};
    s_curVtx.r = 1.0f;
    s_curVtx.g = 1.0f;
    s_curVtx.b = 1.0f;
    s_curVtx.a = 1.0f;
    s_vtxStarted = true;
}

PlatVertex* plat_gx_cur_vtx(void) { return &s_curVtx; }

/* ---- Draw context (called from gx_geometry.cpp) ------------------- */

void plat_gx_begin_draw(GXPrimitive prim) {
    s_cur          = DrawCmd{};
    s_cur.primType = gc_to_mtl_prim(prim);

    /* Capture transform matrices from current GX state.
     * curMtxIdx is the XF address (0, 3, 6 … 27); slot = addr/3 */
    uint32_t slot = gx_state().curMtxIdx / 3;
    if (slot >= 10) slot = 0;
    memcpy(s_cur.model, gx_state().posMtx[slot], sizeof(s_cur.model));
    memcpy(s_cur.proj,  gx_state().projMtx,      sizeof(s_cur.proj));

    /* Capture pixel state */
    s_cur.blend      = (gx_state().blendMode == GX_BM_BLEND ||
                        gx_state().blendMode == GX_BM_SUBTRACT);
    s_cur.depthTest  = (bool)gx_state().zCompare;
    s_cur.depthWrite = (bool)gx_state().zUpdate;

    /* Active texture on map slot 0 */
    s_cur.texture = g_activeTextures[0];

    s_vtxStarted = false;
    s_inDraw     = true;
}

void plat_gx_end_draw(GXPrimitive rawPrim) {
    if (!s_inDraw) return;

    /* Flush the last accumulated vertex */
    if (s_vtxStarted) {
        s_cur.verts.push_back(s_curVtx);
        s_vtxStarted = false;
    }
    s_inDraw = false;

    if (s_cur.verts.empty()) return;

    /* Convert non-native primitive types to triangle lists */
    if (rawPrim == GX_QUADS) {
        std::vector<PlatVertex> tris;
        convert_quads(tris, s_cur.verts);
        s_cur.verts    = std::move(tris);
        s_cur.primType = MTLPrimitiveTypeTriangle;
    } else if (rawPrim == GX_TRIANGLEFAN) {
        std::vector<PlatVertex> tris;
        convert_fan(tris, s_cur.verts);
        s_cur.verts    = std::move(tris);
        s_cur.primType = MTLPrimitiveTypeTriangle;
    }

    std::lock_guard<std::mutex> lk(s_drawMtx);
    s_drawList.push_back(std::move(s_cur));
}

/* ---- Texture slot management (called from gx_texture.mm) ---------- */

void plat_metal_set_texture(int slot, void* tex_ptr) {
    if (slot >= 0 && slot < 8)
        g_activeTextures[slot] = (__bridge id<MTLTexture>)tex_ptr;
}

void* plat_metal_get_cached_tex(uintptr_t key) {
    auto it = g_texCache.find(key);
    if (it == g_texCache.end()) return nullptr;
    return (__bridge void*)it->second;
}

void plat_metal_store_cached_tex(uintptr_t key, void* tex_ptr) {
    g_texCache[key] = (__bridge id<MTLTexture>)tex_ptr;
}

void* plat_metal_device_ptr(void)    { return (__bridge void*)g_device; }
void* plat_metal_white_tex_ptr(void) { return (__bridge void*)g_whiteTex; }

/* Legacy accessors kept for source compatibility */
void* plat_metal_get_device(void)   { return (__bridge void*)g_device; }
void* plat_metal_get_cmdqueue(void) { return (__bridge void*)g_cmdQueue; }

/* ---- Frame presentation (called from GXCopyDisp / VIWaitForRetrace) */

void plat_metal_present_frame(void) {
    if (!g_cmdQueue || !g_pipeOpaque) return;

    id<CAMetalDrawable> drawable = [g_metalLayer nextDrawable];
    if (!drawable) return;

    /* Recreate depth texture if drawable size changed */
    NSUInteger dw = drawable.texture.width;
    NSUInteger dh = drawable.texture.height;
    if (!g_depthTex || g_depthTex.width != dw || g_depthTex.height != dh)
        rebuild_depth_tex(dw, dh);

    /* Clear colour from GX state */
    GXColor cc = gx_state().clearColor;
    MTLRenderPassDescriptor* rpd = [MTLRenderPassDescriptor new];
    rpd.colorAttachments[0].texture     = drawable.texture;
    rpd.colorAttachments[0].loadAction  = MTLLoadActionClear;
    rpd.colorAttachments[0].storeAction = MTLStoreActionStore;
    rpd.colorAttachments[0].clearColor  =
        MTLClearColorMake(cc.r / 255.0, cc.g / 255.0,
                          cc.b / 255.0, cc.a / 255.0);
    rpd.depthAttachment.texture     = g_depthTex;
    rpd.depthAttachment.loadAction  = MTLLoadActionClear;
    rpd.depthAttachment.storeAction = MTLStoreActionDontCare;
    rpd.depthAttachment.clearDepth  = 1.0;

    id<MTLCommandBuffer> cmd = [g_cmdQueue commandBuffer];
    id<MTLRenderCommandEncoder> enc =
        [cmd renderCommandEncoderWithDescriptor:rpd];

    /* Drain the draw list atomically */
    std::vector<DrawCmd> local;
    {
        std::lock_guard<std::mutex> lk(s_drawMtx);
        local.swap(s_drawList);
    }

    struct Uniforms {
        float model[3][4];
        float proj[4][4];
    };

    for (DrawCmd& dc : local) {
        if (dc.verts.empty()) continue;

        /* Upload vertex data to a shared MTLBuffer */
        NSUInteger vbytes = dc.verts.size() * sizeof(PlatVertex);
        id<MTLBuffer> vb =
            [g_device newBufferWithBytes:dc.verts.data()
                                  length:vbytes
                                 options:MTLResourceStorageModeShared];

        /* Build uniforms */
        Uniforms uni;
        memcpy(uni.model, dc.model, sizeof(uni.model));
        memcpy(uni.proj,  dc.proj,  sizeof(uni.proj));

        /* Select pipeline and depth state */
        [enc setRenderPipelineState:dc.blend ? g_pipeBlend : g_pipeOpaque];
        [enc setDepthStencilState:dc.depthTest ? g_dssDepthOn : g_dssDepthOff];

        /* Bind vertex buffer and uniform bytes */
        [enc setVertexBuffer:vb offset:0 atIndex:0];
        [enc setVertexBytes:&uni length:sizeof(uni) atIndex:1];

        /* Bind texture (fall back to 1×1 white) */
        id<MTLTexture> tex = dc.texture ? dc.texture : g_whiteTex;
        [enc setFragmentTexture:tex atIndex:0];
        [enc setFragmentSamplerState:g_sampler atIndex:0];

        [enc drawPrimitives:dc.primType
                vertexStart:0
                vertexCount:(NSUInteger)dc.verts.size()];
    }

    [enc endEncoding];
    [cmd presentDrawable:drawable];
    [cmd commit];
}

} /* extern "C" */

/* ================================================================== */
/* Private helpers                                                      */
/* ================================================================== */

static void rebuild_depth_tex(NSUInteger w, NSUInteger h) {
    MTLTextureDescriptor* dd =
        [MTLTextureDescriptor
            texture2DDescriptorWithPixelFormat:MTLPixelFormatDepth32Float
                                         width:w height:h mipmapped:NO];
    dd.usage       = MTLTextureUsageRenderTarget;
    dd.storageMode = MTLStorageModePrivate;
    g_depthTex = [g_device newTextureWithDescriptor:dd];
}

static void make_white_tex(void) {
    MTLTextureDescriptor* td =
        [MTLTextureDescriptor
            texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA8Unorm
                                         width:1 height:1 mipmapped:NO];
    g_whiteTex = [g_device newTextureWithDescriptor:td];
    uint8_t px[4] = {255, 255, 255, 255};
    [g_whiteTex replaceRegion:MTLRegionMake2D(0, 0, 1, 1)
                  mipmapLevel:0
                    withBytes:px
                  bytesPerRow:4];
}

static id<MTLRenderPipelineState> build_pipeline(id<MTLFunction> vs,
                                                  id<MTLFunction> fs,
                                                  bool blend) {
    /* Vertex descriptor matching PlatVertex layout */
    MTLVertexDescriptor* vd = [MTLVertexDescriptor new];
    vd.attributes[0].format      = MTLVertexFormatFloat3;  /* pos  */
    vd.attributes[0].offset      = 0;
    vd.attributes[0].bufferIndex = 0;
    vd.attributes[1].format      = MTLVertexFormatFloat4;  /* rgba */
    vd.attributes[1].offset      = 12;
    vd.attributes[1].bufferIndex = 0;
    vd.attributes[2].format      = MTLVertexFormatFloat2;  /* uv   */
    vd.attributes[2].offset      = 28;
    vd.attributes[2].bufferIndex = 0;
    vd.layouts[0].stride         = sizeof(PlatVertex);     /* 36 B */
    vd.layouts[0].stepFunction   = MTLVertexStepFunctionPerVertex;

    MTLRenderPipelineDescriptor* pd = [MTLRenderPipelineDescriptor new];
    pd.vertexFunction                    = vs;
    pd.fragmentFunction                  = fs;
    pd.vertexDescriptor                  = vd;
    pd.colorAttachments[0].pixelFormat   = MTLPixelFormatBGRA8Unorm;
    pd.depthAttachmentPixelFormat        = MTLPixelFormatDepth32Float;

    if (blend) {
        MTLRenderPipelineColorAttachmentDescriptor* att = pd.colorAttachments[0];
        att.blendingEnabled             = YES;
        att.sourceRGBBlendFactor        = MTLBlendFactorSourceAlpha;
        att.destinationRGBBlendFactor   = MTLBlendFactorOneMinusSourceAlpha;
        att.sourceAlphaBlendFactor      = MTLBlendFactorSourceAlpha;
        att.destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
    }

    NSError* err = nil;
    id<MTLRenderPipelineState> pso =
        [g_device newRenderPipelineStateWithDescriptor:pd error:&err];
    if (!pso)
        fprintf(stderr, "[Metal] Pipeline error: %s\n",
                [[err localizedDescription] UTF8String]);
    return pso;
}

static MTLPrimitiveType gc_to_mtl_prim(GXPrimitive p) {
    switch (p) {
    case GX_TRIANGLES:      return MTLPrimitiveTypeTriangle;
    case GX_TRIANGLESTRIP:  return MTLPrimitiveTypeTriangleStrip;
    case GX_LINES:          return MTLPrimitiveTypeLine;
    case GX_LINESTRIP:      return MTLPrimitiveTypeLineStrip;
    case GX_POINTS:         return MTLPrimitiveTypePoint;
    default:                return MTLPrimitiveTypeTriangle;
    }
}

/* GX_QUADS: groups of 4 vertices → 2 triangles (v0,v1,v2) + (v0,v2,v3) */
static void convert_quads(std::vector<PlatVertex>& out,
                          const std::vector<PlatVertex>& in) {
    for (size_t i = 0; i + 3 < in.size(); i += 4) {
        out.push_back(in[i + 0]);
        out.push_back(in[i + 1]);
        out.push_back(in[i + 2]);
        out.push_back(in[i + 0]);
        out.push_back(in[i + 2]);
        out.push_back(in[i + 3]);
    }
}

/* GX_TRIANGLEFAN: v0 = hub, (v0, v[i], v[i+1]) for i=1..n-2 */
static void convert_fan(std::vector<PlatVertex>& out,
                        const std::vector<PlatVertex>& in) {
    for (size_t i = 1; i + 1 < in.size(); i++) {
        out.push_back(in[0]);
        out.push_back(in[i]);
        out.push_back(in[i + 1]);
    }
}
