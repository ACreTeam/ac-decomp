#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

Vtx obj_s_cstump3_v[] = {
#include "assets/obj_s_cstump3_v.inc"
};

extern u8 obj_s_cedar_young_tex[];

Gfx obj_s_cstump3T_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_cedar_young_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_cstump3T_gfx_model[] = {
    gsSPVertex(obj_s_cstump3_v, 7, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 2, 2, 5, 3),
    gsSPNTriangles_5b(1, 5, 2, 1, 6, 5, 5, 6, 3, 2, 4, 0),
    gsSPEndDisplayList(),
};
