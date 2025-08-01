#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_act_mus_onamazu_a1_tbl[] = { 56, 7, 2 };

s16 cKF_kn_act_mus_onamazu_a1_tbl[] = { 6, 4, 6, 2, 5, 2, 3 };

s16 cKF_c_act_mus_onamazu_a1_tbl[] = { 0, 900, 0, 0, 0 };

s16 cKF_ds_act_mus_onamazu_a1_tbl[] = { 1,   27,   378, 15,   114,  -3,  33,   1,   -297, 52,   -116, 1,  68,   -8,
                                        399, 70,   20,  390,  1,    -7,  -151, 15,  -57,  -5,   52,   53, 2,    70,
                                        -7,  -137, 1,   1723, 0,    12,  1723, 0,   26,   1723, 0,    43, 1723, 0,
                                        57,  1723, 0,   70,   1723, 0,   1,    0,   0,    70,   0,    0,  1,    48,
                                        185, 10,   72,  -6,   43,   -64, 2,    67,  23,   286,  70,   48, 187,  1,
                                        0,   0,    70,  0,    0,    1,   -105, 175, 27,   112,  -1,   70, -108, 13 };

cKF_Animation_R_c cKF_ba_r_act_mus_onamazu_a1 = { cKF_ckcb_r_act_mus_onamazu_a1_tbl,
                                                  cKF_ds_act_mus_onamazu_a1_tbl,
                                                  cKF_kn_act_mus_onamazu_a1_tbl,
                                                  cKF_c_act_mus_onamazu_a1_tbl,
                                                  -1,
                                                  70 };
