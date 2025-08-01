#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 ef_w_cedar_light_modeset[];
extern u8 ef_w_cedar_leaf_modeset[];
extern Vtx ef_x_cedar5_shake_v[];
Vtx ef_x_cedar5_shake_v[] = {
#include "assets/ef_x_cedar5_shake_v.inc"
};

Gfx ef_x_cedar5_shake_light_model[] = {
    gsSPDisplayList(ef_w_cedar_light_modeset),
    gsSPVertex(&ef_x_cedar5_shake_v[68], 26, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 3, 0, 2, 4, 3, 5),
    gsSPNTriangles_5b(1, 4, 5, 6, 7, 8, 9, 6, 8, 10, 9, 11),
    gsSPNTriangles_5b(12, 10, 11, 10, 13, 14, 7, 10, 14, 6, 12, 15),
    gsSPNTriangles_5b(13, 6, 15, 16, 17, 18, 17, 19, 18, 20, 21, 22),
    gsSPNTriangles_5b(21, 16, 22, 19, 21, 23, 21, 24, 23, 24, 17, 25),
    gsSPNTriangles_5b(17, 20, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx ef_x_cedar5_shake_model[] = {
    gsSPDisplayList(ef_w_cedar_leaf_modeset),
    gsSPVertex(ef_x_cedar5_shake_v, 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 2, 3, 4, 5, 6, 0),
    gsSPNTriangles_5b(7, 8, 5, 9, 10, 11, 11, 12, 13, 14, 15, 9),
    gsSPNTriangles_5b(16, 17, 14, 18, 19, 20, 20, 21, 22, 23, 24, 18),
    gsSPNTriangles_5b(25, 26, 23, 27, 28, 29, 29, 30, 31, 0, 0, 0),
    gsSPVertex(&ef_x_cedar5_shake_v[32], 32, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 0, 5, 6, 7),
    gsSPNTriangles_5b(8, 9, 10, 10, 11, 3, 12, 13, 14, 14, 15, 16),
    gsSPNTriangles_5b(16, 17, 18, 19, 20, 21, 21, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(27, 28, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&ef_x_cedar5_shake_v[62], 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_ef_x_cedar5_shake_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 9000, 0 } },
    { ef_x_cedar5_shake_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { ef_x_cedar5_shake_light_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_ef_x_cedar5_shake = { ARRAY_COUNT(cKF_je_r_ef_x_cedar5_shake_tbl), 2,
                                                cKF_je_r_ef_x_cedar5_shake_tbl };
