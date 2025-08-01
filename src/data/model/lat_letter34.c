#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 lat_letter34_ed_tex[];
extern u16 lat_letter34_pal[];
extern u8 lat_letter34_ce_tex[];
extern u8 lat_letter34_ed2_tex[];
extern u8 lat_letter34_xk_tex[];
Vtx lat_letter34_v[] = {
#include "assets/lat_letter34_v.inc"
};

Gfx lat_letter34_model[] = {
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter34_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, lat_letter34_ce_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(lat_letter34_v, 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(0, 4, 5, 0, 0, 5, 1, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 7, 5, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(6, 3, 2, 0, 6, 2, 7, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter34_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, lat_letter34_ed2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&lat_letter34_v[12], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, lat_letter34_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, lat_letter34_ed_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&lat_letter34_v[20], 20, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(3, 2, 4, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
    gsSP2Triangles(9, 8, 10, 0, 9, 10, 11, 0),
    gsSP2Triangles(11, 10, 12, 0, 11, 12, 13, 0),
    gsSP2Triangles(13, 12, 14, 0, 13, 14, 15, 0),
    gsSP2Triangles(5, 4, 16, 0, 5, 16, 17, 0),
    gsSP2Triangles(17, 16, 18, 0, 17, 18, 19, 0),
    gsSPEndDisplayList(),
};

Gfx lat_letter34_sen_model[] = {
    gsDPSetPrimColor(0, 255, 255, 195, 155, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_8b, 16, 16, lat_letter34_xk_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&lat_letter34_v[40], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};
