/* GX transform state capture. Stage 1: store to GXState. */
#include "gx_state.h"
#include <dolphin/gx.h>
#include <string.h>

extern "C" {

void GXSetProjection(const void* mtx, GXProjectionType type) {
    if (mtx) memcpy(gx_state().projMtx, mtx, sizeof(gx_state().projMtx));
    gx_state().projType = type;
}

void GXSetProjectionv(const f32* ptr) {
    if (ptr) memcpy(gx_state().projMtx, ptr, 4*4*sizeof(f32));
}

void GXLoadPosMtxImm(const void* mtx, u32 id) {
    if (id < 10 && mtx) memcpy(gx_state().posMtx[id], mtx, sizeof(gx_state().posMtx[0]));
}

void GXLoadPosMtxIndx(u16 mtxIndx, u32 id) { (void)mtxIndx; (void)id; }

void GXLoadNrmMtxImm(const void* mtx, u32 id)      { (void)mtx; (void)id; }
void GXLoadNrmMtxIndx3x3(u16 i, u32 id)    { (void)i; (void)id; }
void GXLoadTexMtxImm(const void* mtx, u32 id, GXTexMtxType type) {
    (void)mtx; (void)id; (void)type;
}
void GXLoadTexMtxIndx(u16 mtxIndx, u32 id, GXTexMtxType type) {
    (void)mtxIndx; (void)id; (void)type;
}

void GXSetCurrentMtx(u32 id) { gx_state().curMtxIdx = id; }

void GXSetViewport(f32 l, f32 t, f32 wd, f32 ht, f32 nz, f32 fz) {
    gx_state().viewport[0] = l;
    gx_state().viewport[1] = t;
    gx_state().viewport[2] = wd;
    gx_state().viewport[3] = ht;
    gx_state().viewport[4] = nz;
    gx_state().viewport[5] = fz;
}

void GXSetViewportJitter(f32 l, f32 t, f32 wd, f32 ht, f32 nz, f32 fz, u32 field) {
    (void)field;
    GXSetViewport(l, t, wd, ht, nz, fz);
}

void GXGetProjectionv(f32* p) {
    if (p) memcpy(p, gx_state().projMtx, 4*4*sizeof(f32));
}

void GXSetZScaleOffset(f32 scale, f32 offset) { (void)scale; (void)offset; }
void GXSetFieldMask(GXBool odd, GXBool even)  { (void)odd; (void)even; }
void GXSetFieldMode(GXBool texLOD, GXBool as)  { (void)texLOD; (void)as; }

} /* extern "C" */
