/* GX framebuffer / copy operations. */
#include "gx_state.h"
#include <dolphin/gx.h>

extern "C" void plat_metal_present_frame(void);  /* metal_renderer.mm */

extern "C" {

void GXSetCopyClear(GXColor clear_clr, u32 clear_z) {
    gx_state().clearColor = clear_clr;
    gx_state().clearZ     = clear_z;
}

void GXCopyDisp(void* dest, GXBool clear) {
    (void)dest; (void)clear;
    static int s_copydispcnt = 0;
    if (s_copydispcnt < 5) fprintf(stderr, "[GX] GXCopyDisp #%d\n", s_copydispcnt);
    s_copydispcnt++;
    /* Render all accumulated draw calls and present the Metal drawable */
    plat_metal_present_frame();
}

void GXCopyTex(void* dest, GXBool clear) {
    (void)dest; (void)clear;
}

void GXSetDispCopySrc(u16 left, u16 top, u16 wd, u16 ht) {
    (void)left; (void)top; (void)wd; (void)ht;
}

void GXSetDispCopyDst(u16 wd, u16 ht) {
    (void)wd; (void)ht;
}

void GXSetTexCopySrc(u16 left, u16 top, u16 wd, u16 ht) {
    (void)left; (void)top; (void)wd; (void)ht;
}

void GXSetTexCopyDst(u16 wd, u16 ht, GXTexFmt fmt, GXBool mipmap) {
    (void)wd; (void)ht; (void)fmt; (void)mipmap;
}

void GXSetDispCopyGamma(GXGamma gamma) { (void)gamma; }
void GXSetDispCopyFrame2Field(GXCopyMode mode) { (void)mode; }

u32  GXSetDispCopyYScale(f32 vscale) { (void)vscale; return 480; }
f32  GXGetYScaleFactor(u16 efbHeight, u16 xfbHeight) {
    (void)efbHeight; return (xfbHeight > 0) ? 1.0f : 1.0f;
}
u16  GXGetNumXfbLines(u16 efbHeight, f32 yScale) {
    (void)yScale; return efbHeight;
}

void GXSetCopyFilter(GXBool aa, const u8 samplePattern[12][2],
                     GXBool vf, const u8 vfilter[7]) {
    (void)aa; (void)samplePattern; (void)vf; (void)vfilter;
}

void GXClearBoundingBox(void) {}
void GXReadBoundingBox(u16* l, u16* t, u16* r, u16* b) {
    if (l) *l = 0; if (t) *t = 0; if (r) *r = 0; if (b) *b = 0;
}

void GXPokeAlphaMode(GXCompare func, u8 threshold) { (void)func; (void)threshold; }
void GXPokeAlphaRead(GXAlphaReadMode mode) { (void)mode; }
void GXPokeAlphaUpdate(GXBool update) { (void)update; }
void GXPokeBlendMode(GXBlendMode type, GXBlendFactor src, GXBlendFactor dst,
                     GXLogicOp op) { (void)type; (void)src; (void)dst; (void)op; }
void GXPokeColorUpdate(GXBool update) { (void)update; }
void GXPokeDstAlpha(GXBool en, u8 a) { (void)en; (void)a; }
void GXPokeDither(GXBool dither) { (void)dither; }
void GXPokeZMode(GXBool compare, GXCompare func, GXBool update) {
    (void)compare; (void)func; (void)update;
}
void GXPokeZ(u16 x, u16 y, u32 z) { (void)x; (void)y; (void)z; }
void GXPeekZ(u16 x, u16 y, u32* z) { (void)x; (void)y; if (z) *z = 0; }
void GXPokeARGB(u16 x, u16 y, GXColor color) { (void)x; (void)y; (void)color; }
void GXPeekARGB(u16 x, u16 y, GXColor* color) {
    (void)x; (void)y;
    if (color) { color->r = color->g = color->b = color->a = 0; }
}

} /* extern "C" */
