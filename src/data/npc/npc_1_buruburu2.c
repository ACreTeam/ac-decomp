#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_npc_1_buruburu2_tbl[] = { 56, 7, 0, 7, 7, 7, 0, 7, 7, 7, 0, 7, 7, 7, 0, 7, 7, 0, 7, 7, 7, 7, 0, 7, 0, 0 };

s16 cKF_kn_npc_1_buruburu2_tbl[] = { 2, 3, 2, 2, 2, 2, 2, 3, 2, 2, 3, 2, 2,  3, 3,  2, 3, 2,
                                     2, 3, 2, 2, 3, 3, 2, 9, 2, 2, 9, 2, 10, 3, 12, 2, 2, 2,
                                     2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 16, 4, 13, 2, 2, 2 };

s16 cKF_c_npc_1_buruburu2_tbl[] = { 0,    0, 900, 0,   0, 1800, 0, 0, 1800, 0, 900, 0, 0,   0,
                                    -900, 0, 0,   900, 0, -900, 0, 0, 0,    0, 0,   0, -900 };

s16 cKF_ds_npc_1_buruburu2_tbl[] = {
    1,  0,    0, 31, 0,    0, 1,  875,  0,    17, 925,  0,    31, 875,  0, 1,  50,   0,    31, 50,   0, 1,  0,    0,
    31, 0,    0, 1,  80,   0, 31, 80,   0,    1,  0,    0,    31, 0,    0, 1,  30,   0,    31, 30,   0, 1,  -150, 0,
    17, -80,  0, 31, -150, 0, 1,  -25,  0,    31, -25,  0,    1,  0,    0, 31, 0,    0,    1,  670,  0, 17, 510,  0,
    31, 670,  0, 1,  0,    0, 31, 0,    0,    1,  0,    0,    31, 0,    0, 1,  -440, 0,    17, -350, 0, 31, -440, 0,
    1,  0,    0, 17, 25,   0, 31, 0,    0,    1,  -30,  0,    31, -30,  0, 1,  -150, 0,    17, -80,  0, 31, -150, 0,
    1,  25,   0, 31, 25,   0, 1,  0,    0,    31, 0,    0,    1,  670,  0, 17, 510,  0,    31, 670,  0, 1,  0,    0,
    31, 0,    0, 1,  0,    0, 31, 0,    0,    1,  -440, 0,    17, -350, 0, 31, -440, 0,    1,  0,    0, 17, -25,  0,
    31, 0,    0, 1,  0,    0, 31, 0,    0,    1,  -320, 0,    4,  -280, 0, 8,  -310, 0,    11, -290, 0, 18, -310, 0,
    22, -290, 0, 25, -320, 0, 28, -280, 0,    31, -320, 0,    1,  0,    0, 31, 0,    0,    1,  0,    0, 31, 0,    0,
    1,  -20,  0, 4,  20,   0, 8,  -10,  0,    11, 10,   0,    18, -10,  0, 22, 10,   0,    25, -20,  0, 28, 20,   0,
    31, -20,  0, 1,  0,    0, 31, 0,    0,    1,  0,    -730, 3,  -20,  0, 5,  20,   0,    7,  -20,  0, 9,  20,   0,
    11, -20,  0, 13, 20,   0, 15, -20,  0,    17, 0,    0,    31, 0,    0, 1,  -450, 0,    17, -350, 0, 31, -450, 0,
    1,  0,    0, 11, 0,    0, 13, 20,   0,    15, -20,  0,    17, 20,   0, 19, -20,  0,    21, 20,   0, 23, -20,  0,
    25, 20,   0, 27, -20,  0, 29, 20,   0,    31, 0,    0,    1,  -250, 0, 31, -250, 0,    1,  -950, 0, 31, -950, 0,
    1,  -450, 0, 31, -450, 0, 1,  0,    0,    31, 0,    0,    1,  -700, 0, 31, -850, 0,    1,  0,    0, 31, 0,    0,
    1,  250,  0, 31, 250,  0, 1,  -950, 0,    31, -950, 0,    1,  450,  0, 31, 450,  0,    1,  0,    0, 31, 0,    0,
    1,  -700, 0, 31, -700, 0, 1,  0,    0,    31, 0,    0,    1,  1800, 0, 31, 1800, 0,    1,  600,  0, 31, 600,  0,
    1,  0,    0, 31, -200, 0, 1,  0,    622,  3,  30,   0,    5,  -30,  0, 7,  20,   0,    9,  -30,  0, 11, 20,   0,
    13, -10,  0, 15, 10,   0, 17, -10,  0,    19, 0,    0,    21, 10,   0, 23, -10,  0,    25, 20,   0, 27, -20,  0,
    29, 20,   0, 31, 0,    0, 1,  215,  -217, 6,  200,  0,    22, 270,  0, 31, 215,  -217, 1,  0,    0, 11, 0,    0,
    13, -20,  0, 15, 20,   0, 17, -20,  0,    19, 20,   0,    21, -10,  0, 23, 10,   0,    24, 0,    0, 26, 0,    0,
    27, -10,  0, 29, 10,   0, 31, 0,    0,    1,  0,    0,    31, 0,    0, 1,  -80,  0,    31, -80,  0, 1,  0,    0,
    31, 0,    0
};

aNPC_Animation_c cKF_ba_r_npc_1_buruburu2 = {
    { cKF_ckcb_r_npc_1_buruburu2_tbl, cKF_ds_npc_1_buruburu2_tbl, cKF_kn_npc_1_buruburu2_tbl, cKF_c_npc_1_buruburu2_tbl,
      -1, 31 },
    1.0f,
    31.0f,
    cKF_FRAMECONTROL_REPEAT,
    0.0f,
    NULL,
    aNPC_EYE_TEX0,
    4,
    NULL,
    aNPC_MOUTH_TEX2,
    4,
    -1,
    eEC_EFFECT_BURUBURU,
    NULL,
    NULL,
};
