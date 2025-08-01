#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 lat_letter33_ed_tex[];
extern u8 lat_letter33_xk_tex[];
extern u16 lat_letter33_pal[];
Vtx lat_letter33_v[] = {
#include "assets/lat_letter33_v.inc"
};

Gfx lat_letter33_sen_model[] = {
    gsDPSetPrimColor(0, 255, 215, 110, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, lat_letter33_xk_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(lat_letter33_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Gfx lat_letter33_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter33_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, lat_letter33_ed_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsSPVertex(&lat_letter33_v[4], 20, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(3, 2, 4, 0, 5, 6, 7, 0),
    gsSP2Triangles(5, 7, 8, 0, 4, 9, 3, 0),
    gsSP2Triangles(3, 9, 10, 0, 10, 11, 12, 0),
    gsSP2Triangles(10, 12, 3, 0, 11, 13, 12, 0),
    gsSP2Triangles(12, 13, 14, 0, 15, 12, 14, 0),
    gsSP2Triangles(15, 14, 16, 0, 16, 17, 15, 0),
    gsSP2Triangles(15, 17, 18, 0, 18, 19, 0, 0),
    gsSP2Triangles(18, 0, 15, 0, 19, 1, 0, 0),
    gsSPEndDisplayList(),
};
