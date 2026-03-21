/* GX texture management. Stage 1: stubs. Stage 8: real decode + cache. */
#include "gx_state.h"
#include <dolphin/gx.h>
#include <string.h>

extern "C" {

void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height,
                  GXTexFmt format, GXTexWrapMode wrapS, GXTexWrapMode wrapT,
                  u8 mipmap) {
    if (!obj) return;
    /* Store raw parameters in the 88-byte opaque struct (22×u32 under TARGET_PC).
     * Layout: [0]=ptr_lo [1]=ptr_hi [2]=w [3]=h [4]=fmt [5]=wrapS [6]=wrapT
     *         [7]=mipmap  [8..21]=reserved for Metal texture handle */
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
    GXInitTexObj(obj, image_ptr, width, height, (GXTexFmt)format, wrapS, wrapT, mipmap);
    obj->dummy[8] = tlutName;
}

void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min, GXTexFilter mag,
                     f32 minLod, f32 maxLod, f32 lodbias, GXBool biasClamp,
                     GXBool edgeLOD, GXAnisotropy maxAniso) {
    (void)obj; (void)min; (void)mag; (void)minLod; (void)maxLod;
    (void)lodbias; (void)biasClamp; (void)edgeLOD; (void)maxAniso;
}

void GXInitTexObjData(GXTexObj* obj, void* ptr) {
    if (!obj) return;
    uintptr_t p = (uintptr_t)ptr;
    obj->dummy[0] = (u32)(p & 0xFFFFFFFFu);
    obj->dummy[1] = (u32)(p >> 32);
}

void GXLoadTexObj(GXTexObj* obj, GXTexMapID id) {
    (void)obj; (void)id;
    /* TODO Stage 8: decode GC texture format and upload to MTLTexture */
}

void GXInvalidateTexAll(void) {
    /* TODO Stage 8: invalidate texture cache */
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
    (void)region; (void)is32bMips; (void)tmem_even; (void)size_even;
    (void)tmem_odd; (void)size_odd;
}

void GXInitTlutRegion(GXTlutRegion* region, u32 tmem_addr, GXTlutSize size) {
    (void)region; (void)tmem_addr; (void)size;
}

void GXSetTexRegion(GXTexObj* obj, GXTexRegion* region) {
    (void)obj; (void)region;
}

void GXSetTlutRegion(GXTlutObj* obj, GXTlutRegion* region) {
    (void)obj; (void)region;
}

GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback cb)   { return cb; }
GXTlutRegionCallback GXSetTlutRegionCallback(GXTlutRegionCallback cb){ return cb; }

void GXPreloadEntireTexture(GXTexObj* obj, GXTexRegion* region) {
    (void)obj; (void)region;
}

/* ---- GXGetTexObj* queries ---- */
GXTexFmt      GXGetTexObjFmt(const GXTexObj* o) { return o ? (GXTexFmt)o->dummy[4] : GX_TF_RGBA8; }
u16           GXGetTexObjWidth(const GXTexObj* o)  { return o ? (u16)o->dummy[2] : 0; }
u16           GXGetTexObjHeight(const GXTexObj* o) { return o ? (u16)o->dummy[3] : 0; }
GXBool        GXGetTexObjMipMap(const GXTexObj* o) { return o ? (GXBool)o->dummy[7] : FALSE; }
GXTexWrapMode GXGetTexObjWrapS(const GXTexObj* o)  { return o ? (GXTexWrapMode)o->dummy[5] : GX_CLAMP; }
GXTexWrapMode GXGetTexObjWrapT(const GXTexObj* o)  { return o ? (GXTexWrapMode)o->dummy[6] : GX_CLAMP; }
void*         GXGetTexObjData(const GXTexObj* o) {
    if (!o) return nullptr;
    uintptr_t ptr = ((uintptr_t)o->dummy[1] << 32) | o->dummy[0];
    return (void*)ptr;
}
u32           GXGetTexObjTlut(const GXTexObj* o, u32* name) {
    if (o && name) *name = o->dummy[8];
    return o ? o->dummy[8] : 0;
}

} /* extern "C" */
