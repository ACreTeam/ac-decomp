/* GX texture management.
 * GXInitTexObj stores raw GC parameters in the opaque GXTexObj.
 * GXLoadTexObj decodes the GC texture data into RGBA8 and uploads it to a
 * cached MTLTexture, then binds it to the active texture slot.
 */
#import <Metal/Metal.h>
#include "gx_draw_internal.h"
#include "gx_state.h"
#include <dolphin/gx.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Decoder declared in texture_decode.cpp */
extern "C" uint8_t* plat_decode_texture(const void* src, GXTexFmt fmt,
                                         uint32_t width, uint32_t height);

/* GXTexObj layout (dummy[22]):
 *  [0]  = data_ptr lo32
 *  [1]  = data_ptr hi32
 *  [2]  = width
 *  [3]  = height
 *  [4]  = GXTexFmt
 *  [5]  = wrapS
 *  [6]  = wrapT
 *  [7]  = mipmap
 *  [8]  = tlutName (CI formats)
 *  [9]  = mtl_tex_ptr lo32
 *  [10] = mtl_tex_ptr hi32   (void* = id<MTLTexture> via __bridge)
 */

static id<MTLTexture> obj_get_mtl_tex(const GXTexObj* obj) {
    if (!obj) return nil;
    uintptr_t ptr = ((uintptr_t)obj->dummy[10] << 32) | obj->dummy[9];
    if (!ptr) return nil;
    return (__bridge id<MTLTexture>)(void*)ptr;
}

static void obj_set_mtl_tex(GXTexObj* obj, id<MTLTexture> tex) {
    if (!obj) return;
    uintptr_t ptr = (uintptr_t)(__bridge void*)tex;
    obj->dummy[9]  = (uint32_t)(ptr & 0xFFFFFFFFu);
    obj->dummy[10] = (uint32_t)(ptr >> 32);
}

extern "C" {

/* ---- Init --------------------------------------------------------- */

void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height,
                  GXTexFmt format, GXTexWrapMode wrapS, GXTexWrapMode wrapT,
                  u8 mipmap) {
    if (!obj) return;
    memset(obj, 0, sizeof(*obj));
    uintptr_t ptr = (uintptr_t)image_ptr;
    obj->dummy[0] = (u32)(ptr & 0xFFFFFFFFu);
    obj->dummy[1] = (u32)(ptr >> 32);
    obj->dummy[2] = width;
    obj->dummy[3] = height;
    obj->dummy[4] = (u32)format;
    obj->dummy[5] = (u32)wrapS;
    obj->dummy[6] = (u32)wrapT;
    obj->dummy[7] = mipmap;
}

void GXInitTexObjCI(GXTexObj* obj, void* image_ptr, u16 width, u16 height,
                    GXCITexFmt format, GXTexWrapMode wrapS, GXTexWrapMode wrapT,
                    u8 mipmap, u32 tlutName) {
    GXInitTexObj(obj, image_ptr, width, height, (GXTexFmt)format,
                 wrapS, wrapT, mipmap);
    obj->dummy[8] = tlutName;
}

void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min, GXTexFilter mag,
                     f32 minLod, f32 maxLod, f32 lodbias,
                     GXBool biasClamp, GXBool edgeLOD, GXAnisotropy maxAniso) {
    (void)obj; (void)min; (void)mag; (void)minLod; (void)maxLod;
    (void)lodbias; (void)biasClamp; (void)edgeLOD; (void)maxAniso;
}

void GXInitTexObjData(GXTexObj* obj, void* ptr) {
    if (!obj) return;
    uintptr_t p = (uintptr_t)ptr;
    obj->dummy[0] = (u32)(p & 0xFFFFFFFFu);
    obj->dummy[1] = (u32)(p >> 32);
    obj->dummy[9] = 0; obj->dummy[10] = 0;  /* invalidate cached MTLTexture */
}

/* ---- Upload and bind ---------------------------------------------- */

void GXLoadTexObj(GXTexObj* obj, GXTexMapID map_id) {
    if (!obj) return;
    int slot = (int)map_id;
    if (slot < 0 || slot >= 8) return;

    /* Try the cached MTLTexture stored in the obj itself first */
    id<MTLTexture> tex = obj_get_mtl_tex(obj);
    if (!tex) {
        /* Try the global decode cache keyed on the GC data pointer */
        uintptr_t data_key = ((uintptr_t)obj->dummy[1] << 32) | obj->dummy[0];
        tex = (__bridge id<MTLTexture>)plat_metal_get_cached_tex(data_key);
    }

    if (!tex) {
        void*    gc_data = (void*)( ((uintptr_t)obj->dummy[1] << 32) | obj->dummy[0] );
        uint32_t w       = obj->dummy[2];
        uint32_t h       = obj->dummy[3];
        GXTexFmt fmt     = (GXTexFmt)obj->dummy[4];

        if (!gc_data || w == 0 || h == 0) {
            plat_metal_set_texture(slot, plat_metal_white_tex_ptr());
            return;
        }

        uint8_t* rgba = plat_decode_texture(gc_data, fmt, w, h);
        if (!rgba) {
            plat_metal_set_texture(slot, plat_metal_white_tex_ptr());
            return;
        }

        id<MTLDevice> dev = (__bridge id<MTLDevice>)plat_metal_device_ptr();
        if (!dev) { free(rgba); return; }

        MTLTextureDescriptor* td =
            [MTLTextureDescriptor
                texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA8Unorm
                                             width:w height:h mipmapped:NO];
        tex = [dev newTextureWithDescriptor:td];
        if (tex) {
            [tex replaceRegion:MTLRegionMake2D(0, 0, w, h)
                   mipmapLevel:0
                     withBytes:rgba
                   bytesPerRow:w * 4];
        }
        free(rgba);

        if (tex) {
            plat_metal_store_cached_tex((uintptr_t)gc_data,
                                        (__bridge void*)tex);
            obj_set_mtl_tex(obj, tex);
        }
    }

    plat_metal_set_texture(slot, tex ? (__bridge void*)tex
                                     : plat_metal_white_tex_ptr());
}

void GXInvalidateTexAll(void) {
    /* Textures are cached by data pointer; no action needed unless data changes */
}

void GXInvalidateTexRegion(GXTexRegion* region) { (void)region; }

void GXInitTlutObj(GXTlutObj* obj, void* data, GXTlutFmt fmt, u16 entries) {
    if (!obj) return;
    memset(obj, 0, sizeof(*obj));
    uintptr_t ptr = (uintptr_t)data;
    obj->dummy[0] = (u32)(ptr & 0xFFFFFFFFu);
    obj->dummy[1] = (u32)(ptr >> 32);
    obj->dummy[2] = (u32)fmt;
    obj->dummy[3] = entries;
}

void GXLoadTlut(GXTlutObj* obj, u32 tlutName) { (void)obj; (void)tlutName; }

void GXInitTexCacheRegion(GXTexRegion* region, GXBool is32bMips,
                          u32 tmem_even, GXTexCacheSize size_even,
                          u32 tmem_odd, GXTexCacheSize size_odd) {
    (void)region; (void)is32bMips;
    (void)tmem_even; (void)size_even; (void)tmem_odd; (void)size_odd;
}
void GXInitTlutRegion(GXTlutRegion* region, u32 tmem_addr, GXTlutSize size) {
    (void)region; (void)tmem_addr; (void)size;
}
void GXSetTexRegion(GXTexObj* obj, GXTexRegion* region)   { (void)obj; (void)region; }
void GXSetTlutRegion(GXTlutObj* obj, GXTlutRegion* region){ (void)obj; (void)region; }

GXTexRegionCallback  GXSetTexRegionCallback(GXTexRegionCallback cb)   { return cb; }
GXTlutRegionCallback GXSetTlutRegionCallback(GXTlutRegionCallback cb) { return cb; }
void GXPreloadEntireTexture(GXTexObj* obj, GXTexRegion* region) {
    (void)obj; (void)region;
}

/* ---- GXGetTexObj* queries ---- */
GXTexFmt      GXGetTexObjFmt(const GXTexObj* o)    { return o ? (GXTexFmt)o->dummy[4] : GX_TF_RGBA8; }
u16           GXGetTexObjWidth(const GXTexObj* o)   { return o ? (u16)o->dummy[2] : 0; }
u16           GXGetTexObjHeight(const GXTexObj* o)  { return o ? (u16)o->dummy[3] : 0; }
GXBool        GXGetTexObjMipMap(const GXTexObj* o)  { return o ? (GXBool)o->dummy[7] : FALSE; }
GXTexWrapMode GXGetTexObjWrapS(const GXTexObj* o)   { return o ? (GXTexWrapMode)o->dummy[5] : GX_CLAMP; }
GXTexWrapMode GXGetTexObjWrapT(const GXTexObj* o)   { return o ? (GXTexWrapMode)o->dummy[6] : GX_CLAMP; }
void* GXGetTexObjData(const GXTexObj* o) {
    if (!o) return nullptr;
    return (void*)( ((uintptr_t)o->dummy[1] << 32) | o->dummy[0] );
}
u32 GXGetTexObjTlut(const GXTexObj* o, u32* name) {
    if (o && name) *name = o->dummy[8];
    return o ? o->dummy[8] : 0;
}

} /* extern "C" */
