#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

static u16 act_f37_kurage_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/act_f37_kurage/act_f37_kurage_pal.inc"
};

u8 act_f37_kurage_head_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/act_f37_kurage_head_tex.inc"
};

u8 act_f37_kurage_foot_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/act_f37_kurage_foot_tex.inc"
};

Vtx act_f37_kurage_a_v[] = {
#include "assets/act_f37_kurage_a_v.inc"
};

Gfx act_f37_kurage_aT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 180),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_f37_kurage_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_f37_kurage_foot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f37_kurage_a_v, 13, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_f37_kurage_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 5, 6, 7, 7, 8, 5, 9, 7, 6),
    gsSPNTriangles_5b(6, 10, 9, 11, 9, 10, 10, 12, 11, 12, 5, 8),
    gsSPNTriangles_5b(8, 11, 12, 9, 8, 7, 9, 11, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};

Vtx act_f37_kurage_b_v[] = {
#include "assets/act_f37_kurage_b_v.inc"
};

Gfx act_f37_kurage_bT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_f37_kurage_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_f37_kurage_foot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f37_kurage_b_v, 13, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_f37_kurage_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 5, 6, 7, 7, 8, 5, 9, 7, 6),
    gsSPNTriangles_5b(6, 10, 9, 11, 9, 10, 10, 12, 11, 12, 5, 8),
    gsSPNTriangles_5b(8, 11, 12, 9, 8, 7, 9, 11, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};

Vtx act_f37_kurage_c_v[] = {
#include "assets/act_f37_kurage_c_v.inc"
};

Gfx act_f37_kurage_cT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_f37_kurage_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_f37_kurage_foot_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_f37_kurage_c_v, 13, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_f37_kurage_head_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 5, 6, 7, 7, 8, 5, 9, 7, 6),
    gsSPNTriangles_5b(6, 10, 9, 11, 9, 10, 10, 12, 11, 12, 5, 8),
    gsSPNTriangles_5b(8, 11, 12, 9, 8, 7, 9, 11, 8, 0, 0, 0),
    gsSPEndDisplayList(),
};
