#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_act_mus_nisiki_a1_tbl[] = { 56, 7, 2 };

s16 cKF_kn_act_mus_nisiki_a1_tbl[] = { 5, 4, 6, 2, 4, 2, 3 };

s16 cKF_c_act_mus_nisiki_a1_tbl[] = { 0, 900, 0, 0, 0 };

s16 cKF_ds_act_mus_nisiki_a1_tbl[] = { 1,    9,    289,  11,  74,   -3,   24,  -1, -315, 37, -68, 1,    50,
                                       0,    277,  1,    -16, -268, 12,   -65, -5, 37,   61, 2,   50,   -7,
                                       -219, 1,    1195, 0,   9,    1195, 0,   19, 1195, 0,  31,  1195, 0,
                                       41,   1195, 0,    50,  1195, 0,    1,   0,  0,    50, 0,   0,    1,
                                       68,   335,  9,    110, -6,   31,   -98, 2,  50,   57, 354, 1,    0,
                                       0,    50,   0,    0,   1,    -226, 175, 20, 200,  -2, 50,  -229, 13 };

cKF_Animation_R_c cKF_ba_r_act_mus_nisiki_a1 = { cKF_ckcb_r_act_mus_nisiki_a1_tbl,
                                                 cKF_ds_act_mus_nisiki_a1_tbl,
                                                 cKF_kn_act_mus_nisiki_a1_tbl,
                                                 cKF_c_act_mus_nisiki_a1_tbl,
                                                 -1,
                                                 50 };
