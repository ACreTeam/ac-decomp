#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx rom_shop2f_v[];
Vtx rom_shop2f_v[] = {
#include "assets/rom_shop2f_v.inc"
};

Gfx rom_shop2f_modelT[] = {
    gsSPEndDisplayList(),
};

Gfx rom_shop2f_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_5_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(rom_shop2f_v, 22, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 0, 3),
    gsSPNTriangles_5b(2, 5, 3, 6, 7, 8, 6, 9, 7, 9, 10, 7),
    gsSPNTriangles_5b(6, 11, 9, 12, 13, 14, 12, 14, 15, 12, 16, 13),
    gsSPNTriangles_5b(17, 18, 19, 20, 17, 19, 21, 20, 19, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop2f_v[22], 16, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 0, 2, 1, 4, 2),
    gsSPNTriangles_5b(1, 5, 4, 6, 1, 0, 6, 7, 1, 7, 5, 1),
    gsSPNTriangles_5b(8, 9, 10, 8, 10, 11, 12, 13, 9, 8, 12, 9),
    gsSPNTriangles_5b(9, 14, 15, 10, 9, 15, 9, 13, 14, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_3_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop2f_v[38], 14, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 0, 2, 3, 2, 4),
    gsSPNTriangles_5b(5, 6, 0, 5, 0, 3, 7, 5, 3, 8, 9, 10),
    gsSPNTriangles_5b(8, 11, 9, 12, 9, 11, 12, 13, 9, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, anime_4_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_shop2f_v[52], 9, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 5, 0, 2, 5),
    gsSPNTriangles_5b(6, 2, 1, 3, 7, 8, 6, 7, 2, 3, 2, 7),
    gsSPNTriangles_5b(3, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
