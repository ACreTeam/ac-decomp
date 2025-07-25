#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

static u8 obj_s_palm_young_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_s_pstump3/obj_s_palm_young_tex.inc"
};

Vtx obj_s_pstump3_v[] = {
#include "assets/obj_s_pstump3_v.inc"
};

Gfx obj_s_pstump3T_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_palm_young_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_pstump3T_gfx_model[] = {
    gsSPVertex(obj_s_pstump3_v, 7, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 2, 1, 3, 1, 4, 3),
    gsSPNTriangles_5b(0, 5, 1, 5, 4, 1, 4, 6, 3, 4, 5, 6),
    gsSPEndDisplayList(),
};
