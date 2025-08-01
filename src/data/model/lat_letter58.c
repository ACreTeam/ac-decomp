#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u16 lat_letter58_pal[];
extern u8 lat_letter58_ed_tex[];
extern u8 lat_letter58_xk_tex[];
Vtx lat_letter58_v[] = {
#include "assets/lat_letter58_v.inc"
};

Gfx lat_letter58_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter58_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, lat_letter58_ed_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(lat_letter58_v, 22, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 4, 7, 0, 8, 7, 9, 0),
    gsSP2Triangles(10, 1, 11, 0, 10, 11, 12, 0),
    gsSP2Triangles(12, 11, 0, 0, 12, 0, 13, 0),
    gsSP2Triangles(4, 10, 13, 0, 4, 13, 14, 0),
    gsSP2Triangles(9, 15, 2, 0, 9, 2, 8, 0),
    gsSP2Triangles(16, 3, 17, 0, 16, 17, 18, 0),
    gsSP2Triangles(18, 19, 14, 0, 18, 14, 16, 0),
    gsSP2Triangles(19, 6, 5, 0, 19, 5, 14, 0),
    gsSP2Triangles(3, 20, 21, 0, 3, 21, 17, 0),
    gsSP2Triangles(15, 21, 20, 0, 15, 20, 2, 0),
    gsSPEndDisplayList(),
};

Gfx lat_letter58_sen_model[] = {
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, lat_letter58_xk_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&lat_letter58_v[22], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
