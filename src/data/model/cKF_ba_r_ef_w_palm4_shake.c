#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_ef_w_palm4_shake_tbl[] = { 0, 1 };

s16 cKF_kn_ef_w_palm4_shake_tbl[] = { 10 };

s16 cKF_c_ef_w_palm4_shake_tbl[] = { 0, 6000, 0, 0, 0, 900, 0, 0 };

s16 cKF_ds_ef_w_palm4_shake_tbl[] = { 1, 0,  1500, 2, 50, 188,  3, 12, -1125, 4,  -25, -281, 5,  -6, 563,
                                      6, 13, 141,  7, 3,  -281, 8, -6, -70,   10, 3,   23,   11, 0,  -94 };

cKF_Animation_R_c cKF_ba_r_ef_w_palm4_shake = { cKF_ckcb_r_ef_w_palm4_shake_tbl,
                                                cKF_ds_ef_w_palm4_shake_tbl,
                                                cKF_kn_ef_w_palm4_shake_tbl,
                                                cKF_c_ef_w_palm4_shake_tbl,
                                                -1,
                                                11 };
