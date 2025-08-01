#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_bon_sanshu_v[];
u16 int_sum_bon_sanshu_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/int_sum_bon_sanshu_pal.inc"
};

u8 int_sum_bon_sanshu_tree_tex[] = {
#include "assets/int_sum_bon_sanshu_tree_tex.inc"
};

u8 int_sum_bon_sanshu_treetop_tex[] = {
#include "assets/int_sum_bon_sanshu_treetop_tex.inc"
};

u8 int_sum_bon_sanshu_eda_tex[] = {
#include "assets/int_sum_bon_sanshu_eda_tex.inc"
};

u8 int_sum_bon_sanshu_eda2_tex[] = {
#include "assets/int_sum_bon_sanshu_eda2_tex.inc"
};

u8 int_sum_bon_sanshu_stand_tex[] = {
#include "assets/int_sum_bon_sanshu_stand_tex.inc"
};

u8 int_sum_bon_sanshu_earth_tex[] = {
#include "assets/int_sum_bon_sanshu_earth_tex.inc"
};

u8 int_sum_bon_sanshu_hachi_tex[] = {
#include "assets/int_sum_bon_sanshu_hachi_tex.inc"
};

Vtx int_sum_bon_sanshu_v[] = {
#include "assets/int_sum_bon_sanshu_v.inc"
};

Gfx int_sum_bon_sanshu_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bon_sanshu_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_bon_sanshu_earth_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_bon_sanshu_v, 5, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 3, 4, 2),
    gsSPNTriangles_5b(4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx int_sum_bon_sanshu_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_bon_sanshu_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_bon_sanshu_hachi_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_bon_sanshu_v[5], 12, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 4, 5, 6, 7),
    gsSPNTriangles_5b(3, 5, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_bon_sanshu_stand_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 9, 10, 11, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_bon_sanshu_eda2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_bon_sanshu_v[17], 30, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 25, 26, 27, 28, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_bon_sanshu_eda_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_bon_sanshu_v[47], 30, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 25, 26, 27, 28, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_bon_sanshu_treetop_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_bon_sanshu_v[77], 16, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 0, 2, 3, 4, 5, 1),
    gsSPNTriangles_5b(4, 1, 0, 4, 6, 5, 7, 8, 9, 10, 11, 12),
    gsSPNTriangles_5b(3, 2, 12, 3, 12, 11, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, int_sum_bon_sanshu_tree_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1, 13, 14, 15, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
