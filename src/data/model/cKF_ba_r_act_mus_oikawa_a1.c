#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_act_mus_oikawa_a1_tbl[] = { 56, 7, 2 };

s16 cKF_kn_act_mus_oikawa_a1_tbl[] = { 5, 6, 6, 2, 4, 2, 3 };

s16 cKF_c_act_mus_oikawa_a1_tbl[] = { 0, 900, 0, 0, 0 };

s16 cKF_ds_act_mus_oikawa_a1_tbl[] = { 1,   0, 239, 12,  58, -3, 25,  1,  -180, 41,  -60, 1,   50,  -8,  236,  1,   -7,
                                       0,   9, -7,  0,   19, -7, 0,   31, -7,   0,   41,  -7,  0,   50,  -7,   0,   1,
                                       803, 0, 9,   803, 0,  19, 803, 0,  31,   803, 0,   41,  803, 0,   50,   803, 0,
                                       1,   0, 0,   50,  0,  0,  1,   64, 306,  9,   99,  -6,  31,  -88, 2,    50,  55,
                                       286, 1, 0,   0,   50, 0,  0,   1,  -168, 175, 20,  148, -2,  50,  -172, 13 };

cKF_Animation_R_c cKF_ba_r_act_mus_oikawa_a1 = { cKF_ckcb_r_act_mus_oikawa_a1_tbl,
                                                 cKF_ds_act_mus_oikawa_a1_tbl,
                                                 cKF_kn_act_mus_oikawa_a1_tbl,
                                                 cKF_c_act_mus_oikawa_a1_tbl,
                                                 -1,
                                                 50 };
