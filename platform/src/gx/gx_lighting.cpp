/* GX lighting state capture. Stage 1: store to GXState. */
#include "gx_state.h"
#include <dolphin/gx.h>

extern "C" {

void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc ambSrc,
                   GXColorSrc matSrc, u32 lightMask, GXDiffuseFn diffFn,
                   GXAttnFn attnFn) {
    (void)chan; (void)enable; (void)ambSrc; (void)matSrc;
    (void)lightMask; (void)diffFn; (void)attnFn;
}

void GXSetChanAmbColor(GXChannelID chan, GXColor color) { (void)chan; (void)color; }
void GXSetChanMatColor(GXChannelID chan, GXColor color) { (void)chan; (void)color; }

void GXInitLightAttn(GXLightObj* lt, f32 a0, f32 a1, f32 a2,
                     f32 k0, f32 k1, f32 k2) {
    (void)lt; (void)a0; (void)a1; (void)a2; (void)k0; (void)k1; (void)k2;
}
void GXInitLightAttnA(GXLightObj* lt, f32 a0, f32 a1, f32 a2) {
    (void)lt; (void)a0; (void)a1; (void)a2;
}
void GXInitLightAttnK(GXLightObj* lt, f32 k0, f32 k1, f32 k2) {
    (void)lt; (void)k0; (void)k1; (void)k2;
}
void GXInitLightSpot(GXLightObj* lt, f32 cutoff, GXSpotFn fn) {
    (void)lt; (void)cutoff; (void)fn;
}
void GXInitLightDistAttn(GXLightObj* lt, f32 refDist, f32 refBrightness,
                          GXDistAttnFn fn) {
    (void)lt; (void)refDist; (void)refBrightness; (void)fn;
}
void GXInitLightPos(GXLightObj* lt, f32 x, f32 y, f32 z) {
    (void)lt; (void)x; (void)y; (void)z;
}
void GXInitLightDir(GXLightObj* lt, f32 x, f32 y, f32 z) {
    (void)lt; (void)x; (void)y; (void)z;
}
void GXInitSpecularDir(GXLightObj* lt, f32 x, f32 y, f32 z) {
    (void)lt; (void)x; (void)y; (void)z;
}
void GXInitSpecularDirHA(GXLightObj* lt, f32 nx, f32 ny, f32 nz,
                          f32 hx, f32 hy, f32 hz) {
    (void)lt; (void)nx; (void)ny; (void)nz; (void)hx; (void)hy; (void)hz;
}
void GXInitLightColor(GXLightObj* lt, GXColor c) { (void)lt; (void)c; }
void GXLoadLightObjImm(GXLightObj* lt, GXLightID id) { (void)lt; (void)id; }
void GXLoadLightObjIndx(u16 indx, GXLightID id) { (void)indx; (void)id; }

void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz,
              GXColor color) {
    (void)type; (void)startz; (void)endz; (void)nearz; (void)farz; (void)color;
}
void GXSetFogRangeAdj(GXBool en, u16 center, GXFogAdjTable* tbl) {
    (void)en; (void)center; (void)tbl;
}
void GXSetFogColor(GXColor c) { (void)c; }

} /* extern "C" */
