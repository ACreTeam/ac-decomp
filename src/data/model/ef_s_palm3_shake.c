#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 ef_s_palm_leaf_modeset[];
Vtx ef_s_palm3_shake_v[] = {
#include "assets/ef_s_palm3_shake_v.inc"
};

Gfx ef_s_palm3_shake_model[] = {
    gsSPDisplayList(ef_s_palm_leaf_modeset),
    gsSPVertex(ef_s_palm3_shake_v, 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_ef_s_palm3_shake_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 3750, 0 } },
                                                  { ef_s_palm3_shake_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_ef_s_palm3_shake = { ARRAY_COUNT(cKF_je_r_ef_s_palm3_shake_tbl), 1,
                                               cKF_je_r_ef_s_palm3_shake_tbl };
