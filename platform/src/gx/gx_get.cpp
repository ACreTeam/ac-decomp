/* GX query functions (GXGet*). Stage 1: return safe defaults. */
#include "gx_state.h"
#include <dolphin/gx.h>

extern "C" {

u32 GXGetTexBufferSize(u16 wd, u16 ht, u32 fmt, GXBool mipmap, u8 maxLOD) {
    (void)mipmap; (void)maxLOD;
    /* Rough upper bound: 4 bytes per pixel */
    return (u32)wd * ht * 4;
}

void GXGetTexObjAll(const GXTexObj* obj,
                    void** dataPtr, u16* wd, u16* ht, GXTexFmt* fmt,
                    GXTexWrapMode* wrapS, GXTexWrapMode* wrapT, GXBool* mipmap) {
    if (dataPtr) *dataPtr = GXGetTexObjData(obj);
    if (wd)      *wd      = GXGetTexObjWidth(obj);
    if (ht)      *ht      = GXGetTexObjHeight(obj);
    if (fmt)     *fmt     = GXGetTexObjFmt(obj);
    if (wrapS)   *wrapS   = GXGetTexObjWrapS(obj);
    if (wrapT)   *wrapT   = GXGetTexObjWrapT(obj);
    if (mipmap)  *mipmap  = GXGetTexObjMipMap(obj);
}

void GXGetVtxDesc(GXAttr attr, GXAttrType* type) {
    if (!type) return;
    for (int i = 0; i < GX_VA_MAX_ATTR; i++) {
        if (gx_state().vtxDesc[i].attr == attr) {
            *type = gx_state().vtxDesc[i].type;
            return;
        }
    }
    *type = GX_NONE;
}

void GXGetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt* cnt,
                     GXCompType* type, u8* frac) {
    if ((int)vtxfmt >= 8) return;
    for (int i = 0; i < GX_VA_MAX_ATTR; i++) {
        if (gx_state().vtxFmt[vtxfmt][i].attr == attr) {
            if (cnt)  *cnt  = gx_state().vtxFmt[vtxfmt][i].compCnt;
            if (type) *type = gx_state().vtxFmt[vtxfmt][i].compType;
            if (frac) *frac = gx_state().vtxFmt[vtxfmt][i].frac;
            return;
        }
    }
}

void GXGetScissor(u32* l, u32* t, u32* wd, u32* ht) {
    if (l)  *l  = gx_state().scissorL;
    if (t)  *t  = gx_state().scissorT;
    if (wd) *wd = gx_state().scissorW;
    if (ht) *ht = gx_state().scissorH;
}

void GXGetProjectionv(f32* p);   /* defined in gx_transform.cpp */

} /* extern "C" */
