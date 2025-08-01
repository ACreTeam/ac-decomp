#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx ef_s_cedar4_shake_v[];
extern u8 ef_s_cedar_leaf_modeset[];
Vtx ef_s_cedar4_shake_v[] = {
#include "assets/ef_s_cedar4_shake_v.inc"
};

Gfx ef_s_cedar4_shake_model[] = {
    gsSPDisplayList(ef_s_cedar_leaf_modeset),
    gsSPVertex(ef_s_cedar4_shake_v, 32, 0),
    gsSPNTrianglesInit_5b(13, 0, 1, 2, 2, 3, 4, 5, 6, 0),
    gsSPNTriangles_5b(7, 8, 5, 9, 10, 11, 11, 12, 13, 14, 15, 9),
    gsSPNTriangles_5b(16, 17, 14, 18, 19, 20, 21, 22, 23, 23, 24, 16),
    gsSPNTriangles_5b(25, 26, 7, 27, 28, 29, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&ef_s_cedar4_shake_v[30], 17, 0),
    gsSPNTrianglesInit_5b(7, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(8, 9, 10, 10, 11, 12, 13, 14, 15, 12, 16, 13),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_ef_s_cedar4_shake_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 6750, 0 } },
    { ef_s_cedar4_shake_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_ef_s_cedar4_shake = { ARRAY_COUNT(cKF_je_r_ef_s_cedar4_shake_tbl), 1,
                                                cKF_je_r_ef_s_cedar4_shake_tbl };
