#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 ef_f_tree_leaf_modeset[];
Vtx ef_f_tree5_shake_v[] = {
#include "assets/ef_f_tree5_shake_v.inc"
};

Gfx ef_f_tree5_shake_model[] = {
    gsSPDisplayList(ef_f_tree_leaf_modeset),
    gsSPVertex(ef_f_tree5_shake_v, 15, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 2, 1, 0),
    gsSP2Triangles(4, 0, 2, 0, 3, 4, 2, 0),
    gsSP2Triangles(5, 6, 7, 0, 8, 5, 7, 0),
    gsSP2Triangles(9, 8, 7, 0, 9, 7, 6, 0),
    gsSP2Triangles(10, 11, 12, 0, 10, 13, 11, 0),
    gsSP2Triangles(13, 14, 11, 0, 14, 12, 11, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_ef_f_tree5_shake_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 7000, 0 } },
                                                  { ef_f_tree5_shake_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_ef_f_tree5_shake = { ARRAY_COUNT(cKF_je_r_ef_f_tree5_shake_tbl), 1,
                                               cKF_je_r_ef_f_tree5_shake_tbl };
