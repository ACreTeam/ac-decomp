#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 lat_letter10_1[];
extern u8 lat_letter10_sen[];
extern u16 lat_letter10_pal[];
extern u8 lat_letter10_5[];
extern u8 lat_letter10_3[];
extern u8 lat_letter10_2[];
Vtx lat_letter10_v[] = {
#include "assets/lat_letter10_v.inc"
};

Gfx lat_letter10_model[] = {
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter10_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, lat_letter10_5),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(lat_letter10_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter10_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, lat_letter10_3),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&lat_letter10_v[4], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter10_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, lat_letter10_2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&lat_letter10_v[12], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter10_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 16, lat_letter10_1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&lat_letter10_v[20], 16, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSPVertex(&lat_letter10_v[36], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(6, 0, 8, 0, 6, 8, 9, 0),
    gsSP2Triangles(10, 1, 5, 0, 10, 5, 11, 0),
    gsSPEndDisplayList(),
};

Gfx lat_letter10_sen_model[] = {
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0),
    gsDPSetEnvColor(198, 200, 95, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, lat_letter10_sen),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&lat_letter10_v[48], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};
