#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 ef_s_tree_leaf_modeset[];
extern u8 obj_s_tree_cutL_tex_txt[];
extern u8 ef_s_tree_trunk_modeset[];
extern Vtx ef_s_tree5_cutR_v[];
Vtx ef_s_tree5_cutR_v[] = {
#include "assets/ef_s_tree5_cutR_v.inc"
};

Gfx ef_s_tree5_cutR_leaf_model[] = {
    gsSPDisplayList(ef_s_tree_leaf_modeset),
    gsSPVertex(ef_s_tree5_cutR_v, 15, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 2, 1, 0),
    gsSP2Triangles(4, 0, 2, 0, 3, 4, 2, 0),
    gsSP2Triangles(5, 6, 7, 0, 8, 5, 7, 0),
    gsSP2Triangles(9, 8, 7, 0, 9, 7, 6, 0),
    gsSP2Triangles(10, 11, 12, 0, 10, 13, 11, 0),
    gsSP2Triangles(13, 14, 11, 0, 14, 12, 11, 0),
    gsSPEndDisplayList(),
};

Gfx ef_s_tree5_cutR_trunk_model[] = {
    gsSPDisplayList(ef_s_tree_trunk_modeset),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 48, obj_s_tree_cutL_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&ef_s_tree5_cutR_v[15], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(2, 1, 4, 0, 1, 5, 4, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_ef_s_tree5_cutR_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1000, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { ef_s_tree5_cutR_trunk_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 2250, 0, 0 } },
    { ef_s_tree5_cutR_leaf_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 4750, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_ef_s_tree5_cutR = { ARRAY_COUNT(cKF_je_r_ef_s_tree5_cutR_tbl), 2,
                                              cKF_je_r_ef_s_tree5_cutR_tbl };
