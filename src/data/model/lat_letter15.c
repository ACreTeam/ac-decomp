#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 lat_letter15_2[];
extern u16 lat_letter15_pal[];
extern u8 lat_letter15_1[];
Vtx lat_letter15_v[] = {
#include "assets/lat_letter15_v.inc"
};

Gfx lat_letter15_win_model[] = {
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter15_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, lat_letter15_1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(lat_letter15_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSPEndDisplayList(),
};

Gfx lat_letter15_winT_model[] = {
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter15_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, lat_letter15_2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&lat_letter15_v[4], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx lat_letter15_model[] = {
    gsSPDisplayList(lat_letter15_win_model),
    gsSPDisplayList(lat_letter15_winT_model),
    gsSPEndDisplayList(),
};
