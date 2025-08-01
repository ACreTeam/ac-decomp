#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 ef_w_tree_leaf_modeset[];
Vtx ef_w_tree4_shake_v[] = {
#include "assets/ef_w_tree4_shake_v.inc"
};

Gfx ef_w_tree4_shake_leaf_model[] = {
    gsSPDisplayList(ef_w_tree_leaf_modeset),
    gsSPVertex(ef_w_tree4_shake_v, 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(4, 2, 1, 0, 4, 3, 2, 0),
    gsSP2Triangles(5, 6, 7, 0, 6, 8, 7, 0),
    gsSP2Triangles(5, 7, 9, 0, 8, 9, 7, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_ef_w_tree4_shake_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 6000, 0 } },
    { ef_w_tree4_shake_leaf_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_ef_w_tree4_shake = { ARRAY_COUNT(cKF_je_r_ef_w_tree4_shake_tbl), 1,
                                               cKF_je_r_ef_w_tree4_shake_tbl };
