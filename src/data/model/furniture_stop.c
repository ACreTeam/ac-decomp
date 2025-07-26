#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

u8 cKF_ckcb_r_furniture_stop_tbl[] = { 0 };

s16 cKF_c_furniture_stop_tbl[] = { 0, 0, 0, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_furniture_stop = {
    cKF_ckcb_r_furniture_stop_tbl, NULL, NULL, cKF_c_furniture_stop_tbl, -1, 2
};

cKF_Joint_R_c cKF_je_r_furniture_stop_tbl[] = {
    { NULL, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
};

cKF_Skeleton_R_c cKF_bs_r_furniture_stop = { ARRAY_COUNT(cKF_je_r_furniture_stop_tbl), 0, cKF_je_r_furniture_stop_tbl };
