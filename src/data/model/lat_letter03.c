#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 lat_letter03_01_tex[];
extern u8 lat_tegami_fusen_tex[];
extern u8 lat_letter03_05_tex[];
extern u16 lat_letter03_pal[];
extern u8 lat_letter03_03_tex[];
extern u8 lat_letter03_04_tex[];
extern u8 lat_letter03_07_tex[];
extern u8 lat_letter03_06_tex[];
extern u8 lat_letter03_02_tex[];
Vtx lat_letter03_v[] = {
#include "assets/lat_letter03_v.inc"
};

Gfx lat_letter03_win_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, lat_letter03_07_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(lat_letter03_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, lat_letter03_04_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&lat_letter03_v[4], 15, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
    gsSP2Triangles(8, 9, 10, 0, 9, 11, 10, 0),
    gsSP2Triangles(12, 4, 13, 0, 4, 14, 13, 0),
    gsSPEndDisplayList(),
};

Gfx lat_letter03_winT_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, lat_letter03_06_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&lat_letter03_v[19], 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(3, 4, 5, 0, 6, 3, 5, 0),
    gsSP2Triangles(7, 1, 8, 0, 9, 7, 8, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, lat_letter03_05_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&lat_letter03_v[29], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 4, 6, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, lat_letter03_03_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&lat_letter03_v[37], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 4, 6, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, lat_letter03_02_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&lat_letter03_v[45], 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 0, 2, 0, 7, 8, 6, 0),
    gsSP2Triangles(8, 9, 6, 0, 2, 3, 5, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, lat_letter03_01_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&lat_letter03_v[55], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(4, 6, 5, 0, 1, 7, 2, 0),
    gsSPEndDisplayList(),
};

Gfx lat_letter03_sen_model[] = {
    gsDPSetPrimColor(0, 255, 20, 145, 165, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, lat_tegami_fusen_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&lat_letter03_v[63], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx lat_letter03_model[] = {
    gsSPDisplayList(lat_letter03_win_model),
    gsSPDisplayList(lat_letter03_winT_model),
    gsSPEndDisplayList(),
};
