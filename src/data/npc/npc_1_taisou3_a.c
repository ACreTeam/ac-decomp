#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_npc_1_taisou3_a_tbl[] = { 56, 7, 0, 7, 7, 7, 0, 7, 7, 7, 0, 7, 7, 7, 0, 7, 7, 0, 7, 7, 7, 7, 0, 7, 0, 0 };

s16 cKF_kn_npc_1_taisou3_a_tbl[] = { 2, 17, 17, 2, 17, 2,  14, 17, 13, 2, 17, 2, 2, 17, 13, 14, 17, 13,
                                     2, 17, 2,  2, 17, 13, 2,  18, 2,  2, 9,  2, 2, 17, 2,  2,  14, 13,
                                     2, 9,  2,  2, 14, 13, 2,  9,  2,  2, 2,  2, 2, 18, 2,  2,  2,  2 };

s16 cKF_c_npc_1_taisou3_a_tbl[] = { 0,    0, 900, 0,   0, 1800, 0, 0, 1800, 0, 900, 0, 0,   0,
                                    -900, 0, 0,   900, 0, -900, 0, 0, 0,    0, 0,   0, -900 };

s16 cKF_ds_npc_1_taisou3_a_tbl[] = {
    1,  0,    0,     81, 0,    0,     1,  1500, 0,     6,  1350, -2259, 11, 900,  0,     16, 1350, 2238,
    21, 1500, 0,     26, 1350, -2259, 31, 900,  0,     36, 1350, 2238,  41, 1500, 0,     46, 1350, -2259,
    51, 900,  0,     56, 1350, 2238,  61, 1500, 0,     66, 1350, -2259, 71, 900,  0,     76, 1350, 2238,
    81, 1500, 0,     1,  250,  0,     6,  188,  -947,  11, 0,    0,     16, 188,  939,   21, 250,  0,
    26, 188,  -947,  31, 0,    0,     36, 188,  939,   41, 250,  0,     46, 188,  -947,  51, 0,    0,
    56, 188,  939,   61, 250,  0,     66, 188,  -947,  71, 0,    0,     76, 188,  939,   81, 250,  0,
    1,  0,    0,     81, 0,    0,     1,  -50,  0,     6,  -58,  -112,  11, -80,  0,     16, -58,  113,
    21, -50,  0,     26, -58,  -112,  31, -80,  0,     36, -58,  113,   42, -50,  0,     46, -58,  -112,
    51, -80,  0,     56, -58,  113,   61, -50,  0,     66, -58,  -112,  71, -80,  0,     76, -58,  113,
    81, -50,  0,     1,  0,    0,     81, 0,    0,     1,  -165, 0,     6,  -178, -188,  11, -215, 0,
    16, -178, 188,   26, -178, -188,  31, -215, 0,     36, -178, 188,   46, -178, -188,  51, -215, 0,
    56, -178, 188,   66, -178, -188,  71, -215, 0,     76, -178, 188,   81, -163, 0,     1,  30,   0,
    6,  -65,  -1439, 11, -355, 0,     16, -65,  1421,  21, 30,   0,     26, -65,  -1439, 31, -355, 0,
    36, -65,  1421,  41, 30,   0,     46, -65,  -1439, 51, -355, 0,     56, -65,  1421,  61, 30,   0,
    66, -65,  -1439, 71, -355, 0,     76, -65,  1420,  81, 30,   0,     1,  20,   0,     6,  39,   285,
    11, 95,   0,     16, 39,   -280,  26, 39,   285,   31, 95,   0,     36, 39,   -280,  46, 39,   285,
    51, 95,   0,     56, 39,   -280,  66, 39,   285,   71, 95,   0,     81, 145,  442,   1,  0,    0,
    81, 0,    0,     1,  0,    0,     6,  149,  2243,  11, 595,  0,     16, 149,  -2222, 21, 0,    0,
    26, 149,  2243,  31, 595,  0,     36, 149,  -2222, 41, 0,    0,     46, 149,  2243,  51, 595,  0,
    56, 149,  -2222, 61, 0,    0,     66, 149,  2243,  71, 595,  0,     76, 149,  -2225, 81, 0,    0,
    1,  0,    0,     81, 0,    0,     1,  0,    0,     81, 0,    0,     1,  225,  0,     6,  91,   -2006,
    11, -310, 0,     16, 91,   2006,  21, 225,  0,     26, 91,   -2006, 31, -310, 0,     36, 91,   2006,
    41, 225,  0,     46, 91,   -2006, 51, -310, 0,     56, 91,   2006,  61, 225,  0,     66, 91,   -2006,
    71, -310, 0,     76, 91,   2001,  81, 225,  0,     1,  -35,  0,     6,  -24,  163,   11, 8,    0,
    16, -24,  -160,  26, -24,  163,   31, 8,    0,     36, -24,  -160,  46, -24,  163,   51, 8,    0,
    56, -24,  -160,  66, -24,  163,   71, 8,    0,     81, -50,  -495,  1,  165,  0,     6,  178,  189,
    11, 215,  0,     16, 178,  -190,  26, 178,  189,   31, 215,  0,     36, 178,  -190,  46, 178,  189,
    51, 215,  0,     56, 178,  -190,  66, 178,  189,   71, 215,  0,     76, 178,  -190,  81, 163,  0,
    1,  30,   0,     6,  -65,  -1429, 11, -355, 0,     16, -65,  1422,  21, 30,   0,     26, -65,  -1429,
    31, -355, 0,     36, -65,  1422,  41, 30,   0,     46, -65,  -1429, 51, -355, 0,     56, -65,  1422,
    61, 30,   0,     66, -65,  -1429, 71, -355, 0,     76, -65,  1420,  81, 30,   0,     1,  -20,  0,
    6,  -39,  -280,  11, -95,  0,     16, -39,  276,   26, -39,  -280,  31, -95,  0,     36, -39,  276,
    46, -39,  -280,  51, -95,  0,     56, -39,  276,   66, -39,  -280,  71, -95,  0,     81, -145, -450,
    1,  0,    0,     81, 0,    0,     1,  0,    0,     6,  149,  2248,  11, 595,  0,     16, 149,  -2225,
    21, 0,    0,     26, 149,  2248,  31, 595,  0,     36, 149,  -2225, 41, 0,    0,     46, 149,  2248,
    51, 595,  0,     56, 149,  -2225, 61, 0,    0,     66, 149,  2248,  71, 595,  0,     76, 149,  -2225,
    81, 0,    0,     1,  0,    0,     81, 0,    0,     1,  0,    0,     81, 0,    0,     1,  225,  0,
    6,  91,   -2001, 11, -310, 0,     16, 91,   2001,  21, 225,  0,     26, 91,   -2001, 31, -310, 0,
    36, 91,   2001,  41, 225,  0,     46, 91,   -2001, 51, -310, 0,     56, 91,   2001,  61, 225,  0,
    66, 91,   -2001, 71, -310, 0,     76, 91,   2001,  81, 225,  0,     1,  35,   0,     6,  24,   -161,
    11, -8,   0,     16, 24,   162,   26, 24,   -161,  31, -8,   0,     36, 24,   162,   46, 24,   -161,
    51, -8,   0,     56, 24,   162,   66, 24,   -161,  71, -8,   0,     81, 50,   505,   1,  0,    0,
    81, 0,    0,     1,  148,  155,   2,  150,  0,     7,  75,   -1115, 12, -150, 0,     17, 75,   1123,
    22, 150,  0,     27, 75,   -1115, 32, -150, 0,     37, 75,   1123,  42, 150,  0,     47, 75,   -1115,
    52, -150, 0,     57, 75,   1123,  62, 150,  0,     67, 75,   -1115, 72, -150, 0,     77, 75,   1123,
    81, 148,  122,   1,  0,    0,     81, 0,    0,     1,  0,    0,     81, 0,    0,     1,  150,  0,
    11, -150, 0,     21, 150,  0,     31, -150, 0,     41, 150,  0,     51, -150, 0,     61, 150,  0,
    71, -150, 0,     81, 150,  0,     1,  0,    0,     81, 0,    0,     1,  0,    0,     81, 0,    0,
    1,  150,  0,     6,  80,   -1052, 11, -150, 0,     16, 80,   1054,  21, 150,  0,     26, 80,   -1052,
    31, -150, 0,     36, 80,   1054,  41, 150,  0,     46, 80,   -1052, 51, -150, 0,     56, 80,   1054,
    61, 150,  0,     66, 80,   -1052, 71, -150, 0,     76, 80,   1054,  81, 150,  0,     1,  0,    0,
    81, 0,    0,     1,  0,    0,     81, 0,    0,     1,  100,  0,     6,  135,  530,   11, 250,  0,
    16, 135,  -524,  26, 135,  530,   31, 250,  0,     36, 135,  -524,  46, 135,  530,   51, 250,  0,
    56, 135,  -524,  66, 135,  530,   71, 250,  0,     76, 135,  -524,  81, 93,   0,     1,  -600, 0,
    6,  -575, 372,   11, -500, 0,     16, -575, -373,  26, -575, 372,   31, -500, 0,     36, -575, -373,
    46, -575, 372,   51, -500, 0,     56, -575, -373,  66, -575, 372,   71, -500, 0,     81, -375, 941,
    1,  0,    0,     81, 0,    0,     1,  0,    0,     11, -450, 0,     21, 0,    0,     31, -450, 0,
    41, 0,    0,     51, -450, 0,     61, 0,    0,     71, -450, 0,     81, 0,    0,     1,  0,    0,
    81, 0,    0,     1,  0,    0,     81, 0,    0,     1,  100,  0,     6,  138,  562,   11, 250,  0,
    16, 138,  -560,  26, 138,  562,   31, 250,  0,     36, 138,  -560,  46, 138,  562,   51, 250,  0,
    56, 138,  -560,  66, 138,  562,   71, 250,  0,     76, 138,  -560,  81, 93,   0,     1,  600,  0,
    6,  575,  -374,  11, 500,  0,     16, 575,  374,   26, 575,  -374,  31, 500,  0,     36, 575,  374,
    46, 575,  -374,  51, 500,  0,     56, 575,  374,   66, 575,  -374,  71, 500,  0,     81, 375,  -944,
    1,  0,    0,     81, 0,    0,     1,  0,    0,     11, -450, 0,     21, 0,    0,     31, -450, 0,
    41, 0,    0,     51, -450, 0,     61, 0,    0,     71, -450, 0,     81, 0,    0,     1,  0,    0,
    81, 0,    0,     1,  0,    0,     81, 0,    0,     1,  0,    0,     81, 0,    0,     1,  0,    0,
    81, 0,    0,     1,  0,    0,     81, 0,    0,     1,  3,    84,    4,  20,   301,   9,  80,   0,
    14, 20,   -300,  19, 0,    0,     24, 20,   301,   29, 80,   0,     34, 20,   -300,  39, 0,    0,
    44, 20,   301,   49, 80,   0,     54, 20,   -300,  59, 0,    0,     64, 20,   301,   69, 80,   0,
    74, 20,   -300,  79, 0,    0,     81, 3,    84,    1,  0,    0,     81, 0,    0,     1,  0,    0,
    81, 0,    0,     1,  0,    0,     81, 0,    0,     1,  0,    0,     81, 0,    0
};

aNPC_Animation_c cKF_ba_r_npc_1_taisou3_a = {
    { cKF_ckcb_r_npc_1_taisou3_a_tbl, cKF_ds_npc_1_taisou3_a_tbl, cKF_kn_npc_1_taisou3_a_tbl, cKF_c_npc_1_taisou3_a_tbl,
      -1, 81 },
    1.0f,
    81.0f,
    cKF_FRAMECONTROL_STOP,
    0.0f,
    NULL,
    aNPC_EYE_TEX0,
    0,
    NULL,
    aNPC_MOUTH_TEX0,
    0,
    -1,
    -1,
    NULL,
    NULL,
};
