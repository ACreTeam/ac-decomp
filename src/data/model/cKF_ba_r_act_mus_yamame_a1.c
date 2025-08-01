#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_act_mus_yamame_a1_tbl[] = { 56, 7, 2 };

s16 cKF_kn_act_mus_yamame_a1_tbl[] = { 5, 4, 6, 2, 4, 2, 3 };

s16 cKF_c_act_mus_yamame_a1_tbl[] = { 0, 900, 0, 0, 0 };

s16 cKF_ds_act_mus_yamame_a1_tbl[] = { 1,    8,   300, 13,  74,   -3,   29,  -1, -250, 44, -70, 1,    60,
                                       0,    251, 1,   -12, -181, 14,   -49, -5, 44,   51, 2,   60,   -7,
                                       -168, 1,   999, 0,   11,   999,  0,   23, 999,  0,  37,  999,  0,
                                       49,   999, 0,   60,  999,  0,    1,   0,  0,    60, 0,   0,    1,
                                       68,   335, 10,  110, -6,   37,   -98, 2,  60,   57, 354, 1,    0,
                                       0,    60,  0,   0,   1,    -226, 175, 23, 200,  -2, 60,  -229, 13 };

cKF_Animation_R_c cKF_ba_r_act_mus_yamame_a1 = { cKF_ckcb_r_act_mus_yamame_a1_tbl,
                                                 cKF_ds_act_mus_yamame_a1_tbl,
                                                 cKF_kn_act_mus_yamame_a1_tbl,
                                                 cKF_c_act_mus_yamame_a1_tbl,
                                                 -1,
                                                 60 };
