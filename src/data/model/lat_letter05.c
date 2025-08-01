#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 lat_letter05_1[];
extern u16 lat_letter05_pal[];
extern u8 lat_letter05_2[];
Vtx lat_letter05_v[] = {
#include "assets/lat_letter05_v.inc"
};

Gfx lat_letter05_model[] = {
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter05_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, lat_letter05_2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(lat_letter05_v, 24, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(13, 12, 16, 0, 13, 16, 17, 0),
    gsSP2Triangles(17, 16, 18, 0, 17, 18, 19, 0),
    gsSP2Triangles(8, 6, 5, 0, 8, 5, 9, 0),
    gsSP2Triangles(7, 11, 10, 0, 7, 10, 4, 0),
    gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter05_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, lat_letter05_1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPVertex(&lat_letter05_v[24], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 5, 6, 0, 7, 0, 2, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSPEndDisplayList(),
};
