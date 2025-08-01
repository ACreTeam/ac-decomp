#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_act_mus_zari_tbl[] = { 0, 0, 0, 1, 0, 1, 0, 1, 1 };

s16 cKF_kn_act_mus_zari_tbl[] = { 23, 3, 3, 14 };

s16 cKF_c_act_mus_zari_tbl[] = { 0, 900, 50,   0,   900, 0, 0,   0,    -1003, 502, -900, 502, 0,
                                 0, 502, -900, 502, 0,   0, 502, -900, 502,   0,   0,    0,   0 };

s16 cKF_ds_act_mus_zari_tbl[] = { 1,   890,  94,   3,  900, 206,  6,   908, -106, 10,  890,  0,    15, 910,  0,
                                  20,  890,  0,    25, 910, 0,    30,  890, 2,    35,  910,  0,    40, 890,  0,
                                  45,  910,  0,    50, 890, 0,    55,  910, 0,    60,  890,  0,    65, 910,  0,
                                  70,  890,  0,    75, 910, 0,    80,  890, 0,    85,  910,  0,    90, 890,  0,
                                  95,  910,  -1,   99, 892, -99,  100, 890, -51,  1,   1800, -2,   55, 1751, 16,
                                  100, 1800, 2,    1,  0,   2,    55,  49,  -16,  100, 0,    -2,   1,  250,  0,
                                  49,  250,  0,    53, 235, -285, 69,  2,   -105, 70,  0,    597,  71, 42,   2112,
                                  73,  259,  3264, 74, 358, 2112, 75,  400, 574,  76,  397,  -189, 86, 233,  -189,
                                  92,  258,  117,  97, 254, -61,  100, 250, -17 };

cKF_Animation_R_c cKF_ba_r_act_mus_zari = {
    cKF_ckcb_r_act_mus_zari_tbl, cKF_ds_act_mus_zari_tbl, cKF_kn_act_mus_zari_tbl, cKF_c_act_mus_zari_tbl, -1, 100
};
