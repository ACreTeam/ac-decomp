#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 ef_s_cedar_leaf_modeset[];
extern Vtx ef_s_cedar5_shake_v[];
Vtx ef_s_cedar5_shake_v[] = {
#include "assets/ef_s_cedar5_shake_v.inc"
};

Gfx ef_s_cedar5_shake_model[] = {
    gsSPDisplayList(ef_s_cedar_leaf_modeset),
    gsSPVertex(ef_s_cedar5_shake_v, 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 2, 3, 4, 5, 6, 0),
    gsSPNTriangles_5b(7, 8, 5, 9, 10, 11, 11, 12, 13, 14, 15, 9),
    gsSPNTriangles_5b(16, 17, 14, 18, 19, 20, 20, 21, 22, 23, 24, 18),
    gsSPNTriangles_5b(25, 26, 23, 27, 28, 29, 29, 30, 31, 0, 0, 0),
    gsSPVertex(&ef_s_cedar5_shake_v[32], 32, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 0, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 10, 10, 11, 3, 12, 13, 14, 14, 15, 16),
    gsSPNTriangles_5b(16, 17, 18, 19, 20, 21, 21, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(27, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&ef_s_cedar5_shake_v[62], 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_ef_s_cedar5_shake_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 9000, 0 } },
    { ef_s_cedar5_shake_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_ef_s_cedar5_shake = { ARRAY_COUNT(cKF_je_r_ef_s_cedar5_shake_tbl), 1,
                                                cKF_je_r_ef_s_cedar5_shake_tbl };
