#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u16 lat_letter11_1_pal[];
extern u8 lat_letter11_1[];
extern u8 lat_letter11_2[];
Vtx lat_letter11_v[] = {
#include "assets/lat_letter11_v.inc"
};

Gfx lat_letter11_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter11_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, lat_letter11_2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(lat_letter11_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter11_1_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, lat_letter11_1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&lat_letter11_v[4], 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(0, 4, 5, 0, 0, 5, 6, 0),
    gsSP2Triangles(7, 5, 4, 0, 7, 4, 8, 0),
    gsSP2Triangles(8, 3, 2, 0, 8, 2, 9, 0),
    gsSPEndDisplayList(),
};
