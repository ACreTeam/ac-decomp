#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 lat_letter38_ce_tex[];
extern u8 lat_letter38_xk_tex[];
Vtx lat_letter38_v[] = {
#include "assets/lat_letter38_v.inc"
};

Gfx lat_letter38_model[] = {
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, lat_letter38_ce_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(lat_letter38_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx lat_letter38_sen_model[] = {
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, lat_letter38_xk_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&lat_letter38_v[4], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
