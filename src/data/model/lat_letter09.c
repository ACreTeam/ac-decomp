#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u16 lat_letter09_pal[];
extern u8 lat_letter09_2[];
extern u8 lat_letter09_3[];
extern u8 lat_letter09_1[];
Vtx lat_letter09_v[] = {
#include "assets/lat_letter09_v.inc"
};

Gfx lat_letter09_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter09_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, lat_letter09_3),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(lat_letter09_v, 14, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(2, 8, 7, 0, 2, 7, 3, 0),
    gsSP2Triangles(9, 10, 11, 0, 9, 11, 12, 0),
    gsSP2Triangles(0, 6, 5, 0, 0, 5, 13, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter09_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, lat_letter09_2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&lat_letter09_v[14], 16, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter09_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, lat_letter09_1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&lat_letter09_v[30], 16, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSPEndDisplayList(),
};
