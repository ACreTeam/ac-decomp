#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

u8 obj_f_tree_young_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_f_tree_young_tex.inc"
};

Vtx obj_f_tree2_v[] = {
#include "assets/obj_f_tree2_v.inc"
};

Gfx obj_f_tree2T_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_f_tree_young_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 6, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_f_gold_tree2T_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_f_tree_young_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 8, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_f_tree2T_gfx_model[] = {
    gsSPVertex(obj_f_tree2_v, 7, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 2, 3, 0, 3, 4, 0),
    gsSPNTriangles_5b(0, 5, 1, 0, 4, 5, 3, 6, 4, 4, 6, 5),
    gsSPEndDisplayList(),
};
