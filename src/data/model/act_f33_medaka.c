#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

static u16 int_nog_medaka_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/act_f33_medaka/int_nog_medaka_pal.inc"
};

u8 act_f33_medaka_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/act_f33_medaka_tex.inc"
};

Vtx act_f33_medaka_a_v[] = {
#include "assets/act_f33_medaka_a_v.inc"
};

Gfx act_f33_medaka_aT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_medaka_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, act_f33_medaka_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f33_medaka_a_v, 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 3, 4, 5),
    gsSPNTriangles_5b(4, 6, 5, 6, 7, 5, 7, 8, 5, 8, 0, 5),
    gsSPNTriangles_5b(0, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Vtx act_f33_medaka_b_v[] = {
#include "assets/act_f33_medaka_b_v.inc"
};

Gfx act_f33_medaka_bT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_medaka_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, act_f33_medaka_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f33_medaka_b_v, 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 3, 4, 5),
    gsSPNTriangles_5b(4, 6, 5, 6, 7, 5, 7, 8, 5, 8, 0, 5),
    gsSPNTriangles_5b(0, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Vtx act_f33_medaka_c_v[] = {
#include "assets/act_f33_medaka_c_v.inc"
};

Gfx act_f33_medaka_cT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_nog_medaka_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, act_f33_medaka_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f33_medaka_c_v, 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 3, 4, 5),
    gsSPNTriangles_5b(4, 6, 5, 6, 7, 5, 7, 8, 5, 8, 0, 5),
    gsSPNTriangles_5b(0, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
