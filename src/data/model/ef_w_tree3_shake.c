#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 ef_w_tree_leaf_modeset[];
Vtx ef_w_tree3_shake_v[] = {
#include "assets/ef_w_tree3_shake_v.inc"
};

Gfx ef_w_tree3_shake_leaf_model[] = {
    gsSPDisplayList(ef_w_tree_leaf_modeset),
    gsSPVertex(ef_w_tree3_shake_v, 5, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(0, 2, 4, 0, 3, 4, 2, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_ef_w_tree3_shake_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 4500, 0 } },
    { ef_w_tree3_shake_leaf_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_ef_w_tree3_shake = { ARRAY_COUNT(cKF_je_r_ef_w_tree3_shake_tbl), 1,
                                               cKF_je_r_ef_w_tree3_shake_tbl };
