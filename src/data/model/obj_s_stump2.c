#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

Vtx obj_s_stump2_v[] = {
#include "assets/obj_s_stump2_v.inc"
};

extern u8 obj_s_tree_young_tex[];

Gfx obj_stump2T_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree_young_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 6, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_gold_stump2T_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_tree_young_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 8, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_stump2T_gfx_model[] = {
    gsSPVertex(obj_s_stump2_v, 7, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 4, 6, 5),
    gsSPNTriangles_5b(0, 3, 1, 3, 5, 1, 1, 6, 2, 1, 5, 6),
    gsSPEndDisplayList(),
};
