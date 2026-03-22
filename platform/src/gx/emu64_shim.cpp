/* emu64_shim.cpp — Minimal N64 F3DZEX2 GBI interpreter for macOS/Metal.
 * Implements emu64_taskstart() by walking GBI display lists and emitting
 * GX / plat_gx calls that the Metal renderer consumes.
 *
 * Supported commands: G_VTX, G_TRI1, G_TRI2, G_QUAD, G_TRIN, G_DL,
 *   G_ENDDL, G_MTX, G_POPMTX, G_TEXTURE, G_SETTIMG, G_SETTILE,
 *   G_SETTILE_DOLPHIN, G_SETTILESIZE, G_LOADBLOCK, G_LOADTILE,
 *   G_GEOMETRYMODE, G_SETOTHERMODE_H/L, G_MOVEWORD (segments).
 * Everything else is silently ignored.
 */
#include "gx_draw_internal.h"
#include "gx_state.h"
#include <dolphin/gx.h>
#include <PR/mbi.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

/* Avoid including emu64_wrapper.h here because it pulls in the original
 * (non-platform) PR/mbi.h via sys_ucode.h causing macro redefinition
 * errors.  Forward-declare what we need instead. */
struct ucode_info_s { int id; void* ucode_p; };
typedef struct ucode_info_s ucode_info;

/* Dolphin/GC GBI extension opcodes not in our platform mbi.h */
#ifndef G_TRIN
#define G_TRIN           0x09
#endif
#ifndef G_SETTILE_DOLPHIN
#define G_SETTILE_DOLPHIN 0xD2
#endif

/* ------------------------------------------------------------------ */
/* N64 GBI format/size → GX texture format table (from emu64.c)       */
/* index: [G_IM_FMT_*][G_IM_SIZ_*]                                    */
/* ------------------------------------------------------------------ */
/* CI textures (palette) fall back to white until TLUT support is added. */
static const int k_fmttbl[8][4] = {
    { GX_TF_CMPR,  -1,           GX_TF_RGB5A3, GX_TF_RGBA8  }, /* RGBA */
    { -1,          -1,           -1,           -1            }, /* YUV  */
    { -1,          -1,           -1,           -1            }, /* CI (TLUT unsupported) */
    { -1,          GX_TF_IA4,   GX_TF_IA8,   -1            }, /* IA   */
    { GX_TF_I4,    GX_TF_I8,    GX_TF_RGB565, -1            }, /* I    */
    { -1, -1, -1, -1 },
    { -1, -1, -1, -1 },
    { -1, -1, -1, -1 },
};

static GXTexFmt n64_to_gx_fmt(int fmt, int siz) {
    if (fmt < 0 || fmt > 7 || siz < 0 || siz > 3) return GX_TF_RGBA8;
    int v = k_fmttbl[fmt][siz];
    return (v < 0) ? GX_TF_RGBA8 : (GXTexFmt)v;
}

/* ------------------------------------------------------------------ */
/* N64 Mtx (s16.16, column-major as int32_t[4][4]) → float            */
/* ------------------------------------------------------------------ */
static void n64mtx_to_3x4(const Mtx* m, float gc[3][4]) {
    const int16_t*  ip = (const int16_t*)m;
    const uint16_t* fp = ((const uint16_t*)m) + 16;
    for (int col = 0; col < 4; col++) {
        gc[0][col] = (float)ip[col*4+0] + (float)fp[col*4+0] * (1.0f/65536.0f);
        gc[1][col] = (float)ip[col*4+1] + (float)fp[col*4+1] * (1.0f/65536.0f);
        gc[2][col] = (float)ip[col*4+2] + (float)fp[col*4+2] * (1.0f/65536.0f);
    }
}

static void n64mtx_to_4x4(const Mtx* m, float gc[4][4]) {
    const int16_t*  ip = (const int16_t*)m;
    const uint16_t* fp = ((const uint16_t*)m) + 16;
    for (int col = 0; col < 4; col++)
        for (int row = 0; row < 4; row++)
            gc[row][col] = (float)ip[col*4+row] + (float)fp[col*4+row] * (1.0f/65536.0f);
}

/* ------------------------------------------------------------------ */
/* 3×4 matrix helpers (row-major, implicit bottom row = [0 0 0 1])     */
/* ------------------------------------------------------------------ */
static void mat3x4_identity(float m[3][4]) {
    m[0][0]=1; m[0][1]=0; m[0][2]=0; m[0][3]=0;
    m[1][0]=0; m[1][1]=1; m[1][2]=0; m[1][3]=0;
    m[2][0]=0; m[2][1]=0; m[2][2]=1; m[2][3]=0;
}

static void mat4x4_identity(float m[4][4]) {
    memset(m, 0, 16*sizeof(float));
    m[0][0]=m[1][1]=m[2][2]=m[3][3]=1.0f;
}

/* C = A × B  (both 3×4, treating bottom row as [0 0 0 1]) */
static void mat3x4_mul(const float a[3][4], const float b[3][4], float c[3][4]) {
    for (int r = 0; r < 3; r++) {
        c[r][0] = a[r][0]*b[0][0] + a[r][1]*b[1][0] + a[r][2]*b[2][0];
        c[r][1] = a[r][0]*b[0][1] + a[r][1]*b[1][1] + a[r][2]*b[2][1];
        c[r][2] = a[r][0]*b[0][2] + a[r][1]*b[1][2] + a[r][2]*b[2][2];
        c[r][3] = a[r][0]*b[0][3] + a[r][1]*b[1][3] + a[r][2]*b[2][3] + a[r][3];
    }
}

/* ------------------------------------------------------------------ */
/* Interpreter state                                                    */
/* ------------------------------------------------------------------ */
enum { VCACHE  = 32, MVSTACK = 32, NTILES = 8 };

static Vtx   s_vc[VCACHE];                 /* N64 vertex cache          */
static float s_mv[MVSTACK][3][4];          /* model-view stack          */
static int   s_mv_top;                     /* current stack depth       */
static float s_proj[4][4];                 /* projection matrix         */
static GXProjectionType s_proj_type;

struct TileInfo {
    int  fmt, siz;        /* N64 format / size codes (or GX fmt if dolphin) */
    bool dolphin;         /* true = fmt is already a GXTexFmt                */
    int  wrap_s, wrap_t;  /* GX wrap modes                                   */
    int  lrs, lrt;        /* SETTILESIZE raw (10.2 fixed; standard mode)      */
    int  width, height;   /* pixel dimensions (dolphin or derived)            */
    void* tex_ptr;        /* host pointer to GC-tiled texture data            */
    bool dirty;
};
static TileInfo s_tiles[NTILES];

static void*  s_setimg_ptr;
static int    s_setimg_fmt, s_setimg_siz;
static bool   s_setimg_dolphin; /* bit[18] of SETTIMG cmd = GC-native        */
static int    s_setimg_w, s_setimg_h;  /* dolphin: explicit w/h; else 0     */

static float  s_tex_scale_s = 1.0f, s_tex_scale_t = 1.0f;
static int    s_tex_tile;
static bool   s_tex_on;

static GXTexObj s_tex_objs[NTILES];
static bool     s_tex_valid[NTILES];

static void*    s_segs[16];   /* segment table: seg# → host pointer */

static bool     s_init;

/* ------------------------------------------------------------------ */
/* Segment resolution                                                   */
/* ------------------------------------------------------------------ */
static void* resolve_ptr(void* raw) {
    uintptr_t v = (uintptr_t)raw;
    /* Segment addresses look like 0x0N??????  (N = 1..F, fits in 32 bits) */
    if (v != 0 && v < (uintptr_t)0x10000000u) {
        int   seg = (int)((v >> 24) & 0xF);
        uintptr_t off = v & 0xFFFFFFu;
        if (s_segs[seg])
            return (uint8_t*)s_segs[seg] + off;
        return nullptr; /* unresolved segment */
    }
    return raw; /* already a host pointer */
}

/* ------------------------------------------------------------------ */
/* Tile width/height helpers                                            */
/* ------------------------------------------------------------------ */
static int tile_width(int tile_idx) {
    const TileInfo& t = s_tiles[tile_idx];
    if (t.dolphin || t.width > 0) return (t.width > 0) ? t.width : 8;
    int w = (t.lrs >> 2) + 1;
    return (w > 0) ? w : 8;
}
static int tile_height(int tile_idx) {
    const TileInfo& t = s_tiles[tile_idx];
    if (t.dolphin || t.height > 0) return (t.height > 0) ? t.height : 8;
    int h = (t.lrt >> 2) + 1;
    return (h > 0) ? h : 8;
}

/* ------------------------------------------------------------------ */
/* Texture binding                                                      */
/* ------------------------------------------------------------------ */
static void bind_tile(int tile_idx) {
    TileInfo& t = s_tiles[tile_idx];
    void* ptr = t.tex_ptr;
    if (!ptr) {
        plat_metal_set_texture(0, plat_metal_white_tex_ptr());
        return;
    }
    if (!s_tex_valid[tile_idx] || t.dirty) {
        int w = tile_width(tile_idx);
        int h = tile_height(tile_idx);
        GXTexFmt gfmt = t.dolphin ? (GXTexFmt)t.fmt
                                  : n64_to_gx_fmt(t.fmt, t.siz);
        GXTexWrapMode ws = (GXTexWrapMode)t.wrap_s;
        GXTexWrapMode wt = (GXTexWrapMode)t.wrap_t;
        GXInitTexObj(&s_tex_objs[tile_idx], ptr,
                     (u16)w, (u16)h, gfmt, ws, wt, GX_FALSE);
        s_tex_valid[tile_idx] = true;
        t.dirty = false;
    }
    GXLoadTexObj(&s_tex_objs[tile_idx], GX_TEXMAP0);
}

/* ------------------------------------------------------------------ */
/* Emit a single triangle from three vertex-cache indices              */
/* ------------------------------------------------------------------ */
static void emit_tri(int i0, int i1, int i2) {
    if ((unsigned)i0 >= VCACHE || (unsigned)i1 >= VCACHE ||
        (unsigned)i2 >= VCACHE) return;

    /* Upload matrices into the GX state so the renderer sees them */
    GXLoadPosMtxImm(s_mv[s_mv_top], GX_PNMTX0);
    GXSetProjection(s_proj, s_proj_type);
    GXSetCurrentMtx(GX_PNMTX0);

    /* Bind the active texture (or white fallback) */
    if (s_tex_on)
        bind_tile(s_tex_tile);
    else
        plat_metal_set_texture(0, plat_metal_white_tex_ptr());

    int tw = s_tex_on ? tile_width(s_tex_tile)  : 8;
    int th = s_tex_on ? tile_height(s_tex_tile) : 8;
    if (tw <= 0) tw = 8;
    if (th <= 0) th = 8;

    plat_gx_begin_draw(GX_TRIANGLES);

    const int idx[3] = { i0, i1, i2 };
    for (int k = 0; k < 3; k++) {
        const Vtx_t& v = s_vc[idx[k]].v;
        plat_gx_start_vertex();
        PlatVertex* pv = plat_gx_cur_vtx();
        pv->x = (float)v.ob[0];
        pv->y = (float)v.ob[1];
        pv->z = (float)v.ob[2];
        pv->r = v.cn[0] * (1.0f/255.0f);
        pv->g = v.cn[1] * (1.0f/255.0f);
        pv->b = v.cn[2] * (1.0f/255.0f);
        pv->a = v.cn[3] * (1.0f/255.0f);
        if (s_tex_on) {
            /* tc[i] is in s10.5 (divide by 32 for texels).
             * s_tex_scale_{s,t} maps [0..65535] → [0..1].
             * Final UV = tc / 32 * scale / texture_dimension. */
            pv->u = (float)v.tc[0] * s_tex_scale_s / (32.0f * (float)tw);
            pv->v = (float)v.tc[1] * s_tex_scale_t / (32.0f * (float)th);
        } else {
            pv->u = pv->v = 0.0f;
        }
    }
    plat_gx_end_draw(GX_TRIANGLES);
}

/* ------------------------------------------------------------------ */
/* N64 wrap-mode bits → GX                                             */
/* ------------------------------------------------------------------ */
static GXTexWrapMode n64_wrap(int cms) {
    /* N64: G_TX_CLAMP=2, G_TX_MIRROR=1, G_TX_WRAP=0 */
    if (cms & G_TX_CLAMP)  return GX_CLAMP;
    if (cms & G_TX_MIRROR) return GX_MIRROR;
    return GX_REPEAT;
}

/* ------------------------------------------------------------------ */
/* Display-list interpreter                                             */
/* ------------------------------------------------------------------ */
static void run_dl(const Gfx* gfx) {
    for (;;gfx++) {
        const uint32_t cmd = gfx->pwords.cmd >> 24;

        switch (cmd) {

        /* ---- Geometry -------------------------------------------- */
        case G_VTX: {
            /* cmd = (G_VTX<<24) | (n<<12) | ((n+v0)<<1) */
            uint32_t w0 = gfx->words.w0;
            int n   = (w0 >> 12) & 0xFF;
            int end = (w0 >>  1) & 0x7F;  /* n + v0 */
            int v0  = end - n;
            if (v0 < 0) v0 = 0;
            const Vtx* src = (const Vtx*)resolve_ptr(gfx->pwords.ptr);
            if (src && n > 0) {
                int lim = v0 + n;
                if (lim > VCACHE) lim = VCACHE;
                for (int i = v0; i < lim; i++)
                    s_vc[i] = src[i - v0];
            }
            break;
        }

        case G_TRI1: {
            /* w1 = (a*2 << 16) | (b*2 << 8) | (c*2) | flag */
            uint32_t w1 = gfx->words.w1;
            emit_tri((w1>>17)&0x3F, (w1>>9)&0x3F, (w1>>1)&0x3F);
            break;
        }

        case G_TRI2: {
            /* w0[23:1] = second tri; w1[31:1] = first tri */
            uint32_t w0 = gfx->words.w0;
            uint32_t w1 = gfx->words.w1;
            emit_tri((w1>>17)&0x3F, (w1>>9)&0x3F, (w1>>1)&0x3F);
            emit_tri((w0>>17)&0x3F, (w0>>9)&0x3F, (w0>>1)&0x3F);
            break;
        }

        case G_QUAD: {
            /* w0 = (cmd<<24)|(a*2<<16)|(b*2<<8)|(c*2)|flag  w1 = d*2 */
            uint32_t w0 = gfx->words.w0;
            uint32_t w1 = gfx->words.w1;
            int a = (w0>>17)&0x3F, b = (w0>>9)&0x3F;
            int c = (w0>>1)&0x3F,  d = (w1>>1)&0x3F;
            emit_tri(a, b, c);
            emit_tri(a, c, d);
            break;
        }

        case G_TRIN: {
            /* G_TRIN: w0 = (cmd<<24)|numtris; each 4-byte group in w1
             * encodes a single triangle as (a,b,c) packed bytes.
             * For now emit the first triangle encoded in w1. */
            uint32_t w1 = gfx->words.w1;
            emit_tri((w1>>17)&0x3F, (w1>>9)&0x3F, (w1>>1)&0x3F);
            break;
        }

        case G_DL: {
            /* bit 0 of cmd = branch vs call */
            bool branch = (gfx->pwords.cmd & 1) != 0;
            const Gfx* sub = (const Gfx*)resolve_ptr(gfx->pwords.ptr);
            if (sub) {
                if (branch) { gfx = sub - 1; /* loop increment will add 1 */ }
                else          run_dl(sub);
            }
            break;
        }

        case G_ENDDL:
            return;

        /* ---- Matrices -------------------------------------------- */
        case G_MTX: {
            const Mtx* n64m = (const Mtx*)resolve_ptr(gfx->pwords.ptr);
            if (!n64m) break;
            uint32_t flags = gfx->pwords.cmd & 0xFF;
            bool is_proj = (flags & G_MTX_PROJECTION) != 0;
            bool is_load = (flags & G_MTX_LOAD)       != 0;
            bool is_push = (flags & G_MTX_PUSH)       != 0;

            if (is_proj) {
                n64mtx_to_4x4(n64m, s_proj);
                /* If [3][3] == 0, it is a perspective matrix, else ortho */
                s_proj_type = (s_proj[3][3] == 0.0f)
                            ? GX_PERSPECTIVE : GX_ORTHOGRAPHIC;
            } else {
                if (is_push && s_mv_top < MVSTACK - 1) {
                    memcpy(s_mv[s_mv_top+1], s_mv[s_mv_top],
                           sizeof(s_mv[0]));
                    s_mv_top++;
                }
                float m34[3][4];
                n64mtx_to_3x4(n64m, m34);
                if (is_load) {
                    memcpy(s_mv[s_mv_top], m34, sizeof(m34));
                } else {
                    float tmp[3][4];
                    mat3x4_mul(s_mv[s_mv_top], m34, tmp);
                    memcpy(s_mv[s_mv_top], tmp, sizeof(tmp));
                }
            }
            break;
        }

        case G_POPMTX: {
            int n = (int)(gfx->words.w1 / 64);
            while (n-- > 0 && s_mv_top > 0)
                s_mv_top--;
            break;
        }

        /* ---- Texture state --------------------------------------- */
        case G_TEXTURE: {
            /* w0 = (cmd<<24)|(level<<11)|(tile<<8)|on */
            /* w1 = (sc<<16) | tc  (16-bit fixed-point scale) */
            uint32_t w0 = gfx->words.w0;
            uint32_t w1 = gfx->words.w1;
            s_tex_tile = (w0 >> 8) & 0x7;
            s_tex_on   = (w0 & 0xFF) != 0;
            uint16_t sc = (uint16_t)(w1 >> 16);
            uint16_t tc = (uint16_t)(w1 & 0xFFFF);
            /* 0xFFFF → 1.0; 0 → 0.0 */
            s_tex_scale_s = (sc == 0xFFFF) ? 1.0f : (float)sc * (1.0f/65536.0f);
            s_tex_scale_t = (tc == 0xFFFF) ? 1.0f : (float)tc * (1.0f/65536.0f);
            break;
        }

        case G_SETTIMG: {
            /* pwords.cmd = (G_SETTIMG<<24)|(fmt<<21)|(siz<<19)|[dolphin bit 18]|(w-1) */
            /* pwords.ptr = texture image host pointer (or segment addr)                */
            uint32_t w0  = gfx->pwords.cmd;
            s_setimg_fmt     = (w0 >> 21) & 0x7;
            s_setimg_siz     = (w0 >> 19) & 0x3;
            s_setimg_dolphin = ((w0 >> 18) & 1) != 0;
            if (s_setimg_dolphin) {
                s_setimg_w = (w0 & 0x3FF) + 1;
                s_setimg_h = (((w0 >> 10) & 0xFF) + 1) * 4;
            } else {
                s_setimg_w = (w0 & 0xFFF) + 1;
                s_setimg_h = 0;
            }
            s_setimg_ptr = resolve_ptr(gfx->pwords.ptr);
            break;
        }

        case G_SETTILE: {
            /* w0 = (cmd<<24)|(fmt<<21)|(siz<<19)|(line<<9)|tmem */
            /* w1 = (tile<<24)|(pal<<20)|(cmt<<18)|(maskt<<14)|(shiftt<<10)|(cms<<8)|(masks<<4)|shifts */
            uint32_t w0 = gfx->words.w0;
            uint32_t w1 = gfx->words.w1;
            int tile = (w1 >> 24) & 0x7;
            s_tiles[tile].fmt    = (w0 >> 21) & 0x7;
            s_tiles[tile].siz    = (w0 >> 19) & 0x3;
            s_tiles[tile].dolphin = false;
            s_tiles[tile].wrap_s = (int)n64_wrap((w1 >>  8) & 0x3);
            s_tiles[tile].wrap_t = (int)n64_wrap((w1 >> 18) & 0x3);
            s_tex_valid[tile] = false;
            break;
        }

        case G_SETTILE_DOLPHIN: {
            /* w0 = (cmd<<24)|(d_fmt<<20)|(tile<<16)|(tlut<<12)|(wrap_s<<10)|(wrap_t<<8)|(shift_s<<4)|shift_t */
            uint32_t w0  = gfx->words.w0;
            int tile     = (w0 >> 16) & 0x7;
            int d_fmt    = (w0 >> 20) & 0xF;  /* GXTexFmt code */
            int gx_ws    = (w0 >> 10) & 0x3;
            int gx_wt    = (w0 >>  8) & 0x3;
            s_tiles[tile].fmt     = d_fmt;
            s_tiles[tile].dolphin = true;
            s_tiles[tile].wrap_s  = gx_ws;
            s_tiles[tile].wrap_t  = gx_wt;
            s_tex_valid[tile] = false;
            break;
        }

        case G_SETTILESIZE: {
            /* w0 = (cmd<<24)|(uls<<12)|ult */
            /* w1 = [dolphin bit31]|(tile<<24)|(lrs<<12)|lrt  OR  dolphin: (height-1) at [9:0] */
            uint32_t w0 = gfx->words.w0;
            uint32_t w1 = gfx->words.w1;
            int tile = (w1 >> 24) & 0x7;
            if (w1 >> 31) {
                /* Dolphin variant: width/height are direct pixel counts */
                s_tiles[tile].width  = (int)(w0 & 0x3FF) + 1;
                s_tiles[tile].height = (int)(w1 & 0x3FF) + 1;
            } else {
                /* Standard: lrs/lrt in 10.2 fixed-point */
                s_tiles[tile].lrs   = (w1 >> 12) & 0xFFF;
                s_tiles[tile].lrt   =  w1        & 0xFFF;
                s_tiles[tile].width = s_tiles[tile].height = 0; /* derive from lrs/lrt */
            }
            s_tex_valid[tile] = false;
            break;
        }

        case G_LOADBLOCK:
        case G_LOADTILE: {
            /* After load, the load tile (7) has the texture from s_setimg.
             * We also propagate to render tile 0 so draws find it there. */
            uint32_t w1  = gfx->words.w1;
            int tile     = (w1 >> 24) & 0x7;
            s_tiles[tile].tex_ptr = s_setimg_ptr;
            s_tiles[tile].dirty   = true;
            if (s_setimg_dolphin) {
                s_tiles[tile].width  = s_setimg_w;
                s_tiles[tile].height = s_setimg_h;
                s_tiles[tile].dolphin = true;
                s_tiles[tile].fmt   = s_setimg_fmt; /* already a GXTexFmt? no, still N64 */
            } else {
                /* Use the SETTILE fmt/siz already stored for this tile */
                if (!s_tiles[tile].fmt && !s_tiles[tile].siz) {
                    s_tiles[tile].fmt = s_setimg_fmt;
                    s_tiles[tile].siz = s_setimg_siz;
                }
            }
            s_tex_valid[tile] = false;
            /* Propagate to render tile if this was the load tile */
            if (tile == G_TX_LOADTILE) {
                s_tiles[G_TX_RENDERTILE].tex_ptr = s_setimg_ptr;
                s_tiles[G_TX_RENDERTILE].dirty   = true;
                s_tex_valid[G_TX_RENDERTILE]     = false;
            }
            break;
        }

        /* ---- Geometry mode --------------------------------------- */
        case G_GEOMETRYMODE: {
            /* w0[23:0] = bits to clear; w1 = bits to set */
            uint32_t clr = gfx->words.w0 & 0x00FFFFFFu;
            uint32_t set = gfx->words.w1;
            /* (not consumed by shim directly; stored for future use) */
            (void)clr; (void)set;
            break;
        }

        /* ---- Othermode ------------------------------------------- */
        case G_SETOTHERMODE_H:
        case G_SETOTHERMODE_L:
            break; /* not consumed yet */

        /* ---- Segment table --------------------------------------- */
        case G_MOVEWORD: {
            /* type = (w0 >> 16) & 0xFF */
            int type = (gfx->pwords.cmd >> 16) & 0xFF;
            if (type == G_MW_SEGMENT) {
                int seg = ((gfx->pwords.cmd & 0xFFFF) / 4) & 0xF;
                s_segs[seg] = gfx->pwords.ptr;
            }
            break;
        }

        /* ---- Ignored RDP / state commands ----------------------- */
        default:
            break;
        }
    }
}

/* ------------------------------------------------------------------ */
/* Public emu64 API (extern "C")                                       */
/* ------------------------------------------------------------------ */
extern "C" {

u8 FrameCansel = 0;

static void shim_reset() {
    s_mv_top = 0;
    mat3x4_identity(s_mv[0]);
    mat4x4_identity(s_proj);
    s_proj_type = GX_PERSPECTIVE;
    s_tex_scale_s = s_tex_scale_t = 1.0f;
    s_tex_tile = 0;
    s_tex_on   = false;
    memset(s_tiles,     0, sizeof(s_tiles));
    memset(s_tex_valid, 0, sizeof(s_tex_valid));
    s_setimg_ptr     = nullptr;
    s_setimg_fmt     = 0;
    s_setimg_siz     = 0;
    s_setimg_dolphin = false;
    s_setimg_w       = 0;
    s_setimg_h       = 0;
    /* Default wrap mode = clamp */
    for (int i = 0; i < NTILES; i++) {
        s_tiles[i].wrap_s = GX_CLAMP;
        s_tiles[i].wrap_t = GX_CLAMP;
    }
}

void emu64_init() {
    if (!s_init) {
        memset(s_segs, 0, sizeof(s_segs));
        s_init = true;
    }
    shim_reset();
}

void emu64_set_ucode_info(int count, ucode_info* info) {
    (void)count; (void)info;
}

void emu64_set_first_ucode(void* ucode) {
    (void)ucode;
}

void emu64_taskstart(Gfx* gfx) {
    if (!gfx) return;
    if (!s_init) emu64_init();
    run_dl(gfx);
}

void emu64_refresh() {
    /* Nothing required; frame presentation is driven by GXCopyDisp */
}

void emu64_cleanup() {
    /* Nothing required; GXCopyDisp → plat_metal_present_frame handles flip */
}

void emu64_texture_cache_data_entry_set(void* begin, void* end) {
    (void)begin; (void)end;
}

} /* extern "C" */
