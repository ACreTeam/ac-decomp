#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u16 lat_letter39_pal[];
extern u8 lat_letter39_sk_tex[];
extern u8 lat_letter39_xk_tex[];
Vtx lat_letter39_v[] = {
#include "assets/lat_letter39_v.inc"
};

Gfx lat_letter39_model[] = {
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter39_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, lat_letter39_sk_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPVertex(lat_letter39_v, 28, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 4, 7, 0, 7, 9, 8, 0),
    gsSP2Triangles(7, 10, 11, 0, 7, 11, 9, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 11, 10, 0, 16, 10, 12, 0),
    gsSP2Triangles(17, 16, 12, 0, 12, 15, 17, 0),
    gsSP2Triangles(18, 14, 13, 0, 18, 13, 19, 0),
    gsSP2Triangles(20, 18, 19, 0, 19, 21, 20, 0),
    gsSP2Triangles(19, 22, 23, 0, 19, 23, 21, 0),
    gsSP2Triangles(24, 23, 22, 0, 24, 22, 25, 0),
    gsSP2Triangles(26, 24, 25, 0, 25, 27, 26, 0),
    gsSP2Triangles(25, 6, 5, 0, 25, 5, 27, 0),
    gsSPEndDisplayList(),
};

Gfx lat_letter39_sen_model[] = {
    gsDPSetPrimColor(0, 255, 255, 155, 200, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, lat_letter39_xk_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&lat_letter39_v[28], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
