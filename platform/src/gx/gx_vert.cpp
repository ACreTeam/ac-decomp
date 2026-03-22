/* GX vertex submission functions.
 * Each GXPosition* call flushes the previous accumulated vertex and starts a
 * new one.  GXColor* and GXTexCoord* fill the current vertex's fields.
 * The PlatVertex is always float; integer inputs are scaled by the frac value
 * recorded in the current vertex format. */
#include "gx_draw_internal.h"
#include "gx_state.h"
#include <dolphin/gx/GXVert.h>
#include <stdint.h>

/* Return the fractional-bit scale for attribute `attr` in the current fmt */
static inline float attr_scale(GXAttr attr) {
    GXVtxFmt fmt = gx_state().primFmt;
    if ((int)fmt >= 8) return 1.0f;
    for (int i = 0; i < GX_VA_MAX_ATTR; i++) {
        if (gx_state().vtxFmt[fmt][i].attr == attr) {
            uint8_t frac = gx_state().vtxFmt[fmt][i].frac;
            return (frac > 0) ? (1.0f / (float)(1u << frac)) : 1.0f;
        }
    }
    return 1.0f;
}

extern "C" {

/* ---- Position ---- */
void GXPosition3f32(f32 x, f32 y, f32 z) {
    plat_gx_start_vertex();
    PlatVertex* v = plat_gx_cur_vtx();
    v->x = x; v->y = y; v->z = z;
}
void GXPosition3s16(s16 x, s16 y, s16 z) {
    plat_gx_start_vertex();
    float sc = attr_scale(GX_VA_POS);
    PlatVertex* v = plat_gx_cur_vtx();
    v->x = x * sc; v->y = y * sc; v->z = z * sc;
}
void GXPosition3u16(u16 x, u16 y, u16 z) {
    plat_gx_start_vertex();
    float sc = attr_scale(GX_VA_POS);
    PlatVertex* v = plat_gx_cur_vtx();
    v->x = x * sc; v->y = y * sc; v->z = z * sc;
}
void GXPosition3s8(s8 x, s8 y, s8 z) {
    plat_gx_start_vertex();
    float sc = attr_scale(GX_VA_POS);
    PlatVertex* v = plat_gx_cur_vtx();
    v->x = x * sc; v->y = y * sc; v->z = z * sc;
}
void GXPosition3u8(u8 x, u8 y, u8 z) {
    plat_gx_start_vertex();
    float sc = attr_scale(GX_VA_POS);
    PlatVertex* v = plat_gx_cur_vtx();
    v->x = x * sc; v->y = y * sc; v->z = z * sc;
}
void GXPosition2f32(f32 x, f32 y) {
    plat_gx_start_vertex();
    PlatVertex* v = plat_gx_cur_vtx();
    v->x = x; v->y = y; v->z = 0.0f;
}
void GXPosition2s16(s16 x, s16 y) {
    plat_gx_start_vertex();
    float sc = attr_scale(GX_VA_POS);
    PlatVertex* v = plat_gx_cur_vtx();
    v->x = x * sc; v->y = y * sc; v->z = 0.0f;
}
void GXPosition2u16(u16 x, u16 y) {
    plat_gx_start_vertex();
    float sc = attr_scale(GX_VA_POS);
    PlatVertex* v = plat_gx_cur_vtx();
    v->x = x * sc; v->y = y * sc; v->z = 0.0f;
}
void GXPosition2s8(s8 x, s8 y) {
    plat_gx_start_vertex();
    float sc = attr_scale(GX_VA_POS);
    PlatVertex* v = plat_gx_cur_vtx();
    v->x = x * sc; v->y = y * sc; v->z = 0.0f;
}
void GXPosition2u8(u8 x, u8 y) {
    plat_gx_start_vertex();
    float sc = attr_scale(GX_VA_POS);
    PlatVertex* v = plat_gx_cur_vtx();
    v->x = x * sc; v->y = y * sc; v->z = 0.0f;
}
/* Indexed positions — look up in the GXSetArray data (not yet implemented) */
void GXPosition1x16(u16 index) { (void)index; plat_gx_start_vertex(); }
void GXPosition1x8 (u8 index)  { (void)index; plat_gx_start_vertex(); }

/* ---- Normal (ignored for now — lighting not implemented) ---- */
void GXNormal3f32(f32 x, f32 y, f32 z)    { (void)x; (void)y; (void)z; }
void GXNormal3s16(s16 x, s16 y, s16 z)    { (void)x; (void)y; (void)z; }
void GXNormal3s8 (s8 x, s8 y, s8 z)       { (void)x; (void)y; (void)z; }
void GXNormal1x16(u16 index)               { (void)index; }
void GXNormal1x8 (u8 index)                { (void)index; }

/* ---- Color ---- */
void GXColor4u8(u8 r, u8 g, u8 b, u8 a) {
    PlatVertex* v = plat_gx_cur_vtx();
    v->r = r / 255.0f; v->g = g / 255.0f;
    v->b = b / 255.0f; v->a = a / 255.0f;
}
void GXColor3u8(u8 r, u8 g, u8 b) {
    PlatVertex* v = plat_gx_cur_vtx();
    v->r = r / 255.0f; v->g = g / 255.0f;
    v->b = b / 255.0f; v->a = 1.0f;
}
void GXColor1u32(u32 clr) {
    GXColor4u8((clr >> 24) & 0xFF, (clr >> 16) & 0xFF,
               (clr >> 8)  & 0xFF, (clr)        & 0xFF);
}
void GXColor1u16(u16 clr) {
    /* RGB565 packed colour */
    u8 r = ((clr >> 11) & 0x1F) * 255 / 31;
    u8 g = ((clr >>  5) & 0x3F) * 255 / 63;
    u8 b = ((clr)       & 0x1F) * 255 / 31;
    GXColor4u8(r, g, b, 255);
}
void GXColor1x16(u16 index) { (void)index; }
void GXColor1x8 (u8 index)  { (void)index; }

/* ---- TexCoord ---- */
void GXTexCoord2f32(f32 s, f32 t) {
    PlatVertex* v = plat_gx_cur_vtx();
    v->u = s; v->v = t;
}
void GXTexCoord2s16(s16 s, s16 t) {
    float sc = attr_scale(GX_VA_TEX0);
    PlatVertex* v = plat_gx_cur_vtx();
    v->u = s * sc; v->v = t * sc;
}
void GXTexCoord2u16(u16 s, u16 t) {
    float sc = attr_scale(GX_VA_TEX0);
    PlatVertex* v = plat_gx_cur_vtx();
    v->u = s * sc; v->v = t * sc;
}
void GXTexCoord2s8(s8 s, s8 t) {
    float sc = attr_scale(GX_VA_TEX0);
    PlatVertex* v = plat_gx_cur_vtx();
    v->u = s * sc; v->v = t * sc;
}
void GXTexCoord2u8(u8 s, u8 t) {
    float sc = attr_scale(GX_VA_TEX0);
    PlatVertex* v = plat_gx_cur_vtx();
    v->u = s * sc; v->v = t * sc;
}
void GXTexCoord1f32(f32 s, f32 t) { GXTexCoord2f32(s, t); }
void GXTexCoord1u16(u16 s, u16 t) { GXTexCoord2u16(s, t); }
void GXTexCoord1s16(s16 s, s16 t) { GXTexCoord2s16(s, t); }
void GXTexCoord1u8 (u8 s, u8 t)   { GXTexCoord2u8(s, t); }
void GXTexCoord1s8 (s8 s, s8 t)   { GXTexCoord2s8(s, t); }
void GXTexCoord1x16(u16 index)    { (void)index; }
void GXTexCoord1x8 (u8 index)     { (void)index; }

} /* extern "C" */
