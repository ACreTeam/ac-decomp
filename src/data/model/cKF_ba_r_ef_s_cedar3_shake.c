#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_ef_s_cedar3_shake_tbl[] = { 0, 7 };

s16 cKF_kn_ef_s_cedar3_shake_tbl[] = { 2, 2, 7 };

s16 cKF_c_ef_s_cedar3_shake_tbl[] = { 0, 4500, 0, 0, 0, 900 };

s16 cKF_ds_ef_s_cedar3_shake_tbl[] = { 1, 0, 0,   11, 0, 0,  1, 0, 0,  11, 0,  0, 1, 0,  2569, 2, 50,
                                       0, 4, -25, 0,  6, 13, 0, 8, -6, 0,  10, 3, 0, 11, 0,    0 };

cKF_Animation_R_c cKF_ba_r_ef_s_cedar3_shake = { cKF_ckcb_r_ef_s_cedar3_shake_tbl,
                                                 cKF_ds_ef_s_cedar3_shake_tbl,
                                                 cKF_kn_ef_s_cedar3_shake_tbl,
                                                 cKF_c_ef_s_cedar3_shake_tbl,
                                                 -1,
                                                 11 };
