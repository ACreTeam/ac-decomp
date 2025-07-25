#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_npc_1_transfer1_tbl[] = { 56, 7, 0, 7, 7, 7, 0, 7, 7, 7, 0, 7, 7, 7, 0, 7, 7, 0, 7, 7, 7, 7, 0, 7, 0, 0 };

s16 cKF_kn_npc_1_transfer1_tbl[] = { 2,  6, 4,  2,  8,  7,  9, 10, 9, 8, 10, 8, 10, 10, 10, 9, 10, 10,
                                     10, 9, 10, 10, 10, 10, 2, 8,  5, 2, 8,  6, 6,  5,  7,  6, 7,  5,
                                     5,  7, 2,  5,  5,  5,  2, 8,  2, 4, 4,  2, 7,  8,  7,  2, 2,  2 };

s16 cKF_c_npc_1_transfer1_tbl[] = { 0,    0, 900, 0,   0, 1800, 0, 0, 1800, 0, 900, 0, 0,   0,
                                    -900, 0, 0,   900, 0, -900, 0, 0, 0,    0, 0,   0, -900 };

s16 cKF_ds_npc_1_transfer1_tbl[] = {
    1,  0,    0,    39, 0,    0,     1,  1000, 0,    11, 975,   0,    14, 950,   0,    17, 975,  0,     20, 950,  0,
    39, 1000, 0,    1,  0,    0,     20, 0,    0,    26, 0,     0,    39, 200,   0,    1,  0,    0,     39, 0,    0,
    1,  0,    0,    11, 50,   0,     14, 30,   0,    17, 50,    0,    20, 30,    0,    26, 60,   0,     37, -100, 0,
    39, -100, 0,    1,  0,    0,     11, 50,   0,    14, 125,   0,    17, 50,    0,    20, 125,  0,     37, 0,    0,
    39, 0,    0,    1,  -175, 0,     11, -190, 0,    14, -203,  0,    17, -190,  0,    20, -200, 0,     23, -200, 0,
    26, -198, 38,   37, -175, 0,     39, -175, 0,    1,  -100,  0,    11, 0,     0,    14, 38,   0,     17, -5,   0,
    20, 35,   393,  23, 53,   76,    26, 58,   0,    32, -150,  -867, 37, -208,  0,    39, -200, 0,     1,  25,   0,
    11, 15,   0,    14, -77,  0,     17, 18,   0,    20, -75,   0,    23, -68,   227,  26, -40,  343,   37, 25,   0,
    39, 25,   0,    1,  0,    0,     11, 0,    0,    14, 0,     0,    17, 0,     0,    20, 0,    0,     23, 0,    0,
    26, 0,    0,    39, 0,    0,     1,  200,  0,    11, 135,   0,    14, 0,     0,    17, 150,  0,     20, 0,    0,
    23, 0,    0,    26, 25,   251,   29, 50,   253,  37, 200,   0,    39, 200,   0,    1,  0,    0,     11, 0,    0,
    14, 0,    0,    17, 0,    0,     20, 0,    0,    23, 0,     0,    26, 0,     0,    39, 0,    0,     1,  0,    0,
    11, 0,    0,    14, 0,    0,     17, 0,    0,    20, 0,     0,    23, 0,     0,    26, 0,    0,     32, 0,    0,
    37, 0,    0,    39, 0,    0,     1,  -100, 0,    11, -65,   0,    14, 23,    0,    17, -73,  0,     20, 25,   0,
    23, 23,   -76,  26, 3,    -289,  32, -55,  -285, 37, -95,   -160, 39, -100,  0,    1,  0,    0,     11, -45,  0,
    14, -43,  0,    17, -45,  0,     20, -45,  0,    23, -48,   0,    26, -45,   74,   32, -10,  205,   37, 8,    0,
    39, 0,    0,    1,  175,  0,     11, 180,  0,    14, 188,   0,    17, 180,   0,    20, 190,  0,     23, 180,  -25,
    29, 175,  -25,  32, 173,  0,     39, 175,  0,    1,  -100,  0,    11, -158,  0,    14, -265, 0,     17, -158, 0,
    20, -270, 0,    23, -248, 392,   26, -203, 380,  29, -164,  392,  32, -130,  300,  39, -100, 0,     1,  -25,  0,
    11, -113, 0,    14, -223, 0,     17, -113, 0,    20, -225,  0,    23, -208,  258,  26, -170, 464,   29, -120, 489,
    32, -73,  484,  39, -25,  0,     1,  0,    0,    11, 0,     0,    14, 0,     0,    17, 0,    0,     20, 0,    0,
    23, 0,    0,    26, 0,    0,     29, 0,    0,    32, 0,     0,    39, 0,     0,    1,  200,  0,     11, 450,  0,
    14, 650,  0,    17, 453,  0,     20, 655,  0,    23, 635,   -361, 26, 573,   -743, 32, 345,  -1058, 39, 200,  0,
    1,  0,    0,    11, 0,    0,     14, 0,    0,    17, 0,     0,    20, 0,     0,    23, 0,    0,     26, 0,    0,
    29, 0,    0,    32, 0,    0,     39, 0,    0,    1,  0,     0,    11, 0,     0,    14, 0,    0,     17, 0,    0,
    20, 0,    0,    23, 0,    0,     26, 0,    0,    29, 0,     0,    32, 0,     0,    39, 0,    0,     1,  -100, 0,
    11, -235, 0,    14, -345, 0,     17, -235, 0,    20, -340,  0,    23, -330,  225,  26, -300, 348,   29, -265, 310,
    32, -235, 402,  39, -100, 0,     1,  0,    0,    11, -5,    0,    14, 0,     0,    17, -3,   0,     20, 0,    0,
    23, 5,    0,    26, 0,    0,     29, 10,   0,    32, 20,    0,    39, 0,     0,    1,  0,    0,     39, 0,    0,
    1,  60,   0,    9,  -160, 0,     16, 80,   0,    19, 0,     0,    24, 100,   0,    30, -100, 0,     37, 100,  0,
    39, 60,   0,    1,  0,    0,     12, 100,  0,    24, -50,   0,    31, 80,    0,    39, 0,    0,     1,  0,    0,
    39, 0,    0,    1,  82,   0,     6,  150,  0,    11, -80,   0,    17, 150,   0,    22, 0,    0,     28, 250,  0,
    35, -50,  0,    39, 80,   0,     1,  0,    0,    6,  -40,   0,    17, 100,   0,    27, -50,  0,     32, 60,   0,
    39, 0,    0,    1,  0,    0,     14, 550,  0,    17, 500,   0,    20, 550,   0,    35, 0,    0,     39, 0,    0,
    1,  2,    0,    20, 2,    0,     29, 170,  0,    35, 50,    0,    39, 100,   0,    1,  0,    0,     14, -100, 0,
    17, 0,    0,    20, -100, 0,     29, 50,   0,    35, 0,     0,    39, 0,     0,    1,  0,    0,     14, 370,  0,
    17, 320,  0,    20, 370,  0,     36, -600, 0,    39, -600,  0,    1,  58,    0,    14, 200,  0,     17, 150,  0,
    20, 200,  0,    28, -100, -1896, 36, -700, 0,    39, -700,  0,    1,  -614,  0,    14, -160, 0,     20, -160, 0,
    36, 0,    0,    39, 0,    0,     1,  0,    0,    14, 600,   0,    20, 600,   0,    36, 0,    0,     39, 0,    0,
    1,  -57,  468,  14, -900, 0,     17, -850, 0,    20, -900,  0,    26, -900,  0,    36, -50,  0,     39, -50,  0,
    1,  0,    0,    39, 0,    0,     1,  0,    0,    14, -1000, 0,    20, -1000, 0,    36, 600,  0,     39, 600,  0,
    1,  58,   0,    14, -600, 0,     20, -600, 0,    36, -700,  0,    39, -700,  0,    1,  614,  0,     14, 800,  0,
    20, 800,  0,    36, 0,    0,     39, 0,    0,    1,  0,     0,    39, 0,     0,    1,  -57,  468,   7,  -600, 0,
    14, -500, 0,    17, -450, 0,     20, -500, 0,    26, -750,  0,    36, -57,   0,    39, -57,  0,     1,  0,    0,
    39, 0,    0,    1,  0,    0,     26, 700,  0,    36, 300,   0,    39, 300,   0,    1,  0,    0,     26, 403,  -928,
    36, -50,  0,    39, -50,  0,     1,  0,    0,    39, 175,   0,    1,  0,     0,    11, 300,  0,     17, 300,  0,
    20, 275,  -736, 29, -49,  0,     37, 0,    0,    39, 0,     0,    1,  0,     0,    11, -400, 0,     14, -450, 0,
    17, -400, 0,    20, -450, 0,     29, -270, 1803, 33, 0,     746,  39, 0,     0,    1,  0,    -273,  11, -75,  0,
    14, -125, 0,    17, -75,  0,     20, -125, 0,    37, 0,     0,    39, 0,     -273, 1,  0,    0,     39, 0,    0,
    1,  0,    0,    39, 0,    0,     1,  0,    0,    39, 0,     0
};

aNPC_Animation_c cKF_ba_r_npc_1_transfer1 = {
    { cKF_ckcb_r_npc_1_transfer1_tbl, cKF_ds_npc_1_transfer1_tbl, cKF_kn_npc_1_transfer1_tbl, cKF_c_npc_1_transfer1_tbl,
      -1, 39 },
    1.0f,
    39.0f,
    cKF_FRAMECONTROL_STOP,
    -10.0f,
    NULL,
    aNPC_EYE_TEX1,
    -1,
    NULL,
    aNPC_MOUTH_TEX1,
    0,
    -1,
    -1,
    NULL,
    NULL,
};
