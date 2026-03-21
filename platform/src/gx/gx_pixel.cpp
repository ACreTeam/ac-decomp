/* GX pixel/blend/Z state capture. Stage 1: store to GXState. */
#include "gx_state.h"
#include <dolphin/gx.h>

extern "C" {

void GXSetZMode(GXBool compare, GXCompare func, GXBool update) {
    gx_state().zCompare = compare;
    gx_state().zFunc    = func;
    gx_state().zUpdate  = update;
}

void GXSetZTexture(GXZTexOp op, GXTexFmt fmt, u32 bias) {
    (void)op; (void)fmt; (void)bias;
}

void GXSetBlendMode(GXBlendMode type, GXBlendFactor src, GXBlendFactor dst,
                    GXLogicOp op) {
    gx_state().blendMode = type;
    gx_state().blendSrc  = src;
    gx_state().blendDst  = dst;
    (void)op;
}

void GXSetColorUpdate(GXBool enable)  { gx_state().colorUpdate = enable; }
void GXSetAlphaUpdate(GXBool enable)  { gx_state().alphaUpdate = enable; }

void GXSetDstAlpha(GXBool enable, u8 alpha) { (void)enable; (void)alpha; }

void GXSetDither(GXBool dither) { (void)dither; }

void GXSetPMColor(u32 pn, GXColor color) { (void)pn; (void)color; }

} /* extern "C" */
