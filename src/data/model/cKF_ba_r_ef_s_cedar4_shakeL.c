#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_ef_s_cedar4_shakeL_tbl[] = { 56, 3 };

s16 cKF_kn_ef_s_cedar4_shakeL_tbl[] = { 2, 2, 2, 2, 11 };

s16 cKF_c_ef_s_cedar4_shakeL_tbl[] = { 0, 0, 900, 0 };

s16 cKF_ds_ef_s_cedar4_shakeL_tbl[] = { 1,  0,   0, 13, 0,   0, 1,  6750, 0, 13, 6750, 0, 1,  0,   0,
                                        13, 0,   0, 1,  0,   0, 13, 0,    0, 1,  0,    0, 5,  20,  0,
                                        9,  -40, 0, 13, 60,  0, 17, -60,  0, 21, 60,   0, 25, -40, 0,
                                        29, 20,  0, 33, -10, 0, 37, 5,    0, 41, 0,    0 };

cKF_Animation_R_c cKF_ba_r_ef_s_cedar4_shakeL = { cKF_ckcb_r_ef_s_cedar4_shakeL_tbl,
                                                  cKF_ds_ef_s_cedar4_shakeL_tbl,
                                                  cKF_kn_ef_s_cedar4_shakeL_tbl,
                                                  cKF_c_ef_s_cedar4_shakeL_tbl,
                                                  -1,
                                                  41 };
