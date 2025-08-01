#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 obj_w_tree_cutS_tex_txt[];
extern u8 ef_w_tree_leaf_modeset[];
extern Vtx ef_w_tree3_cutR_v[];
extern u8 ef_w_tree_trunk_modeset[];
Vtx ef_w_tree3_cutR_v[] = {
#include "assets/ef_w_tree3_cutR_v.inc"
};

Gfx ef_w_tree3_cutR_leaf_model[] = {
    gsSPDisplayList(ef_w_tree_leaf_modeset),
    gsSPVertex(ef_w_tree3_cutR_v, 5, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(0, 2, 4, 0, 3, 4, 2, 0),
    gsSPEndDisplayList(),
};

Gfx ef_w_tree3_cutR_trunk_model[] = {
    gsSPDisplayList(ef_w_tree_trunk_modeset),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_w_tree_cutS_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&ef_w_tree3_cutR_v[5], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 3, 4, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_ef_w_tree3_cutR_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 500, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { ef_w_tree3_cutR_trunk_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 2250, 0, 0 } },
    { ef_w_tree3_cutR_leaf_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2250, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_ef_w_tree3_cutR = { ARRAY_COUNT(cKF_je_r_ef_w_tree3_cutR_tbl), 2,
                                              cKF_je_r_ef_w_tree3_cutR_tbl };
