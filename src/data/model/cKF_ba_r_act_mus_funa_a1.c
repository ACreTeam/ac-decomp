#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_act_mus_funa_a1_tbl[] = { 56, 7, 2 };

s16 cKF_kn_act_mus_funa_a1_tbl[] = { 5, 4, 6, 2, 4, 2, 3 };

s16 cKF_c_act_mus_funa_a1_tbl[] = { 0, 900, 0, 0, 0 };

s16 cKF_ds_act_mus_funa_a1_tbl[] = { 1,   8,    210, 11,  40, -3,  24,   -1,  -165, 37,  -38,  1,   50,   0,  180, 1,
                                     -11, -117, 11,  -37, -5, 37,  31,   2,   50,   -7,  -102, 1,   795,  0,  9,   795,
                                     0,   19,   795, 0,   31, 795, 0,    41,  795,  0,   50,   795, 0,    1,  0,   0,
                                     50,  0,    0,   1,   68, 335, 9,    110, -6,   31,  -98,  2,   50,   57, 354, 1,
                                     0,   0,    50,  0,   0,  1,   -226, 175, 20,   200, -2,   50,  -229, 13 };

cKF_Animation_R_c cKF_ba_r_act_mus_funa_a1 = { cKF_ckcb_r_act_mus_funa_a1_tbl,
                                               cKF_ds_act_mus_funa_a1_tbl,
                                               cKF_kn_act_mus_funa_a1_tbl,
                                               cKF_c_act_mus_funa_a1_tbl,
                                               -1,
                                               50 };
