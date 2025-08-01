#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_ef_w_cedar3_shakeS_tbl[] = { 0, 1 };

s16 cKF_kn_ef_w_cedar3_shakeS_tbl[] = { 5 };

s16 cKF_c_ef_w_cedar3_shakeS_tbl[] = { 0, 4500, 0, 0, 0, 900, 0, 0 };

s16 cKF_ds_ef_w_cedar3_shakeS_tbl[] = { 1, 0, 931, 3, 40, 0, 6, -20, 0, 8, 10, 0, 9, 0, 0 };

cKF_Animation_R_c cKF_ba_r_ef_w_cedar3_shakeS = { cKF_ckcb_r_ef_w_cedar3_shakeS_tbl,
                                                  cKF_ds_ef_w_cedar3_shakeS_tbl,
                                                  cKF_kn_ef_w_cedar3_shakeS_tbl,
                                                  cKF_c_ef_w_cedar3_shakeS_tbl,
                                                  -1,
                                                  9 };
