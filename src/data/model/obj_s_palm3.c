#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

static u8 obj_s_palm_leaf_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_s_palm3/obj_s_palm_leaf_tex.inc"
};

static u8 obj_s_palm_young_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_s_palm3/obj_s_palm_young_tex.inc"
};

Vtx obj_s_palm3_v[] = {
#include "assets/obj_s_palm3_v.inc"
};

Gfx obj_s_palm3_leafT_mat_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 128, 32, obj_s_palm_leaf_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_palm3_leafT_gfx_model[] = {
    gsSPVertex(obj_s_palm3_v, 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_palm3_trunkT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_palm_young_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_palm3_trunkT_gfx_model[] = {
    gsSPVertex(&obj_s_palm3_v[16], 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 0, 6, 1, 6, 4, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};
