#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_fruitbed01_v[];
u16 int_sum_fruitbed01_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/int_sum_fruitbed01_pal.inc"
};

u8 int_sum_fruitbed01_board_tex[] = {
#include "assets/int_sum_fruitbed01_board_tex.inc"
};

u8 int_sum_fruitbed01_side_tex[] = {
#include "assets/int_sum_fruitbed01_side_tex.inc"
};

u8 int_sum_fruitbed01_back_tex[] = {
#include "assets/int_sum_fruitbed01_back_tex.inc"
};

Vtx int_sum_fruitbed01_v[] = {
#include "assets/int_sum_fruitbed01_v.inc"
};

Gfx int_sum_fruitbed01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_fruitbed01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_fruitbed01_back_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_fruitbed01_v, 26, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 7, 8, 6, 8, 4, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 48, 32, int_sum_fruitbed01_side_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(20, 9, 10, 11, 9, 11, 12, 13, 14, 15),
    gsSPNTriangles_5b(13, 15, 16, 11, 17, 18, 11, 18, 12, 19, 20, 18),
    gsSPNTriangles_5b(19, 18, 17, 21, 13, 22, 13, 16, 22, 16, 19, 22),
    gsSPNTriangles_5b(19, 17, 22, 17, 11, 22, 11, 10, 22, 10, 23, 22),
    gsSPNTriangles_5b(23, 21, 22, 23, 24, 25, 23, 25, 21, 21, 25, 14),
    gsSPNTriangles_5b(21, 14, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_fruitbed01_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_fruitbed01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_fruitbed01_board_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_fruitbed01_v[26], 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
