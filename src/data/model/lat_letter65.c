#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 lat_letter65_me_tex[];
extern u16 lat_letter65_pal[];
extern u8 lat_letter65_kt_tex[];
extern u8 lat_letter65_sk_tex[];
extern u8 lat_letter65_xk_tex[];
Vtx lat_letter65_v[] = {
#include "assets/lat_letter65_v.inc"
};

Gfx lat_letter29_model[] = {
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter65_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, lat_letter65_sk_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPVertex(lat_letter65_v, 18, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 0, 0, 4, 0, 3, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 7, 8, 0),
    gsSP2Triangles(9, 10, 8, 0, 9, 8, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 2, 0),
    gsSP2Triangles(15, 12, 16, 0, 15, 16, 17, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter65_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, lat_letter65_me_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&lat_letter65_v[18], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(3, 4, 5, 0, 3, 5, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter65_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, lat_letter65_kt_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&lat_letter65_v[24], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 7, 5, 0),
    gsSPEndDisplayList(),
};

Gfx lat_letter29_sen_model[] = {
    gsDPSetPrimColor(0, 255, 255, 55, 0, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, lat_letter65_xk_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&lat_letter65_v[32], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
