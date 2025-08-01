#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_ef_w_palm4_shakeL_tbl[] = { 0, 1 };

s16 cKF_kn_ef_w_palm4_shakeL_tbl[] = { 21 };

s16 cKF_c_ef_w_palm4_shakeL_tbl[] = { 0, 6000, 0, 0, 0, 900, 0, 0 };

s16 cKF_ds_ef_w_palm4_shakeL_tbl[] = { 1,    0,    94,   3,   10,  206, 5,    20,  -94, 6,   11,   -450, 9,
                                       -40,  94,   10,   -24, 750, 13,  60,   -47, 14,  41,  -900, 16,   -41,
                                       -900, 17,   -60,  0,   19,  0,   1238, 20,  41,  900, 21,   60,   47,
                                       24,   -24,  -750, 25,  -40, -94, 28,   11,  450, 29,  20,   70,   32,
                                       -5,   -225, 34,   -8,  112, 37,  5,    23,  41,  0,   -23 };

cKF_Animation_R_c cKF_ba_r_ef_w_palm4_shakeL = { cKF_ckcb_r_ef_w_palm4_shakeL_tbl,
                                                 cKF_ds_ef_w_palm4_shakeL_tbl,
                                                 cKF_kn_ef_w_palm4_shakeL_tbl,
                                                 cKF_c_ef_w_palm4_shakeL_tbl,
                                                 -1,
                                                 41 };
