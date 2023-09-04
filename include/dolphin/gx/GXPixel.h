#ifndef _DOLPHIN_GXPIXEL
#define _DOLPHIN_GXPIXEL

#include <dolphin/gx/GXEnum.h>

#ifdef __cplusplus
extern "C" {
#endif

void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color);
void GXSetFogColor(GXColor color);
// ? GXSetFogRangeAdj();
void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor,
                    GXLogicOp op);
void GXSetColorUpdate(GXBool update_enable);
void GXSetAlphaUpdate(GXBool update_enable);
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
void GXSetZCompLoc(GXBool before_tex);
void GXSetPixelFmt(GXPixelFmt pix_fmt, GXZFmt16 z_fmt);
void GXSetDither(GXBool dither);
void GXSetDstAlpha(GXBool enable, u8 alpha);
// ? GXSetFieldMask();
// ? GXSetFieldMode();

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GXPIXEL
