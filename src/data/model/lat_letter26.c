#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 lat_letter26_test10_tex[];
extern u8 lat_letter26_test4_tex[];
extern u8 lat_letter26_test7_tex[];
extern u8 lat_letter26_test11_tex[];
extern u8 lat_letter26_test6_tex[];
extern u8 lat_letter26_test8_tex[];
extern u16 lat_letter26_pal[];
extern u8 lat_letter26_test1_tex[];
extern u8 lat_letter26_test9_tex[];
extern u8 lat_letter26_test2_tex[];
extern u8 lat_letter26_test5_tex[];
Vtx lat_letter26_v[] = {
#include "assets/lat_letter26_v.inc"
};

Gfx lat_letter26_win_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
    gsDPSetRenderMode(G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter26_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, lat_letter26_test11_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(lat_letter26_v, 24, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, lat_letter26_test10_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 7, 4, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, lat_letter26_test9_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(23, 20, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, lat_letter26_test8_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&lat_letter26_v[24], 28, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 1, 3, 2, 1, 4, 5),
    gsSPNTriangles_5b(4, 6, 5, 7, 8, 3, 8, 9, 3, 10, 9, 4),
    gsSPNTriangles_5b(10, 11, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, lat_letter26_test7_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 12, 13, 14, 13, 15, 14, 16, 17, 18),
    gsSPNTriangles_5b(19, 16, 18, 20, 21, 22, 23, 20, 22, 24, 25, 26),
    gsSPNTriangles_5b(25, 27, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, lat_letter26_test6_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&lat_letter26_v[52], 24, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14),
    gsSPNTriangles_5b(14, 15, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, lat_letter26_test5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 16, 17, 18, 16, 19, 17, 20, 21, 22),
    gsSPNTriangles_5b(20, 23, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, lat_letter26_test4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&lat_letter26_v[76], 28, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 0, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 16, 17, 18, 19, 16, 18, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, lat_letter26_test2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 24, 25, 26, 25, 27, 26, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, lat_letter26_test1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&lat_letter26_v[104], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx lat_letter26_model[] = {
    gsSPDisplayList(lat_letter26_win_model),
    gsSPEndDisplayList(),
};
