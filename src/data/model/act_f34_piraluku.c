#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

static u16 int_nog_piraluku_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/act_f34_piraluku/int_nog_piraluku_pal.inc"
};

u8 act_f34_piraluku_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/act_f34_piraluku_tex.inc"
};

Vtx act_f34_piraluku_a_v[] = {
#include "assets/act_f34_piraluku_a_v.inc"
};

Gfx act_f34_piraluku_aT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_piraluku_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_f34_piraluku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f34_piraluku_a_v, 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 2, 4, 3, 4, 5),
    gsSPNTriangles_5b(0, 6, 1, 6, 7, 1, 7, 8, 1, 8, 4, 1),
    gsSPNTriangles_5b(1, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Vtx act_f34_piraluku_b_v[] = {
#include "assets/act_f34_piraluku_b_v.inc"
};

Gfx act_f34_piraluku_bT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_piraluku_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_f34_piraluku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f34_piraluku_b_v, 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 2, 4, 3, 4, 5),
    gsSPNTriangles_5b(0, 6, 1, 6, 7, 1, 7, 8, 1, 8, 4, 1),
    gsSPNTriangles_5b(1, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Vtx act_f34_piraluku_c_v[] = {
#include "assets/act_f34_piraluku_c_v.inc"
};

Gfx act_f34_piraluku_cT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_piraluku_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, act_f34_piraluku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f34_piraluku_c_v, 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 2, 4, 3, 4, 5),
    gsSPNTriangles_5b(0, 6, 1, 6, 7, 1, 7, 8, 1, 8, 4, 1),
    gsSPNTriangles_5b(1, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
