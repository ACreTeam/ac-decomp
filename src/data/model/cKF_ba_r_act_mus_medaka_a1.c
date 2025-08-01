#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_act_mus_medaka_a1_tbl[] = { 56, 7, 2 };

s16 cKF_kn_act_mus_medaka_a1_tbl[] = { 5, 4, 6, 2, 4, 2, 3 };

s16 cKF_c_act_mus_medaka_a1_tbl[] = { 0, 900, 0, 0, 0 };

s16 cKF_ds_act_mus_medaka_a1_tbl[] = { 1,    8,   261, 9,   58,   -3,   19,  -1, -244, 30, -56, 1,    40,
                                       0,    205, 1,   -12, -131, 10,   -37, -5, 30,   37, 2,   40,   -7,
                                       -121, 1,   605, 0,   7,    605,  0,   15, 605,  0,  25,  605,  0,
                                       33,   605, 0,   40,  605,  0,    1,   0,  0,    40, 0,   0,    1,
                                       49,   364, 7,   85,  -6,   25,   -68, 2,  40,   38, 328, 1,    0,
                                       0,    40,  0,   0,   1,    -154, 175, 18, 142,  -2, 40,  -157, 13 };

cKF_Animation_R_c cKF_ba_r_act_mus_medaka_a1 = { cKF_ckcb_r_act_mus_medaka_a1_tbl,
                                                 cKF_ds_act_mus_medaka_a1_tbl,
                                                 cKF_kn_act_mus_medaka_a1_tbl,
                                                 cKF_c_act_mus_medaka_a1_tbl,
                                                 -1,
                                                 40 };
