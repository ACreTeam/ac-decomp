#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 lat_letter50_xk_tex[];
extern u16 lat_letter50_pal[];
extern u8 lat_letter50_ed_tex[];
Vtx lat_letter50_v[] = {
#include "assets/lat_letter50_v.inc"
};

Gfx lat_letter50_model[] = {
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter50_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, lat_letter50_ed_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(lat_letter50_v, 24, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(2, 16, 17, 0, 2, 17, 3, 0),
    gsSP2Triangles(18, 19, 7, 0, 18, 7, 6, 0),
    gsSP2Triangles(20, 21, 11, 0, 20, 11, 10, 0),
    gsSP2Triangles(22, 23, 12, 0, 22, 12, 15, 0),
    gsSPEndDisplayList(),
};

Gfx lat_letter50_sen_model[] = {
    gsDPSetPrimColor(0, 255, 255, 235, 165, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, lat_letter50_xk_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&lat_letter50_v[24], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
