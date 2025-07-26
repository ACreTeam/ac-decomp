#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_npc_1_kutipaku2_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 };

s16 cKF_kn_npc_1_kutipaku2_tbl[] = { 27 };

s16 cKF_c_npc_1_kutipaku2_tbl[] = {
    0, 1000, 0,   0, 0, 900, 0, 0,   0, 0, 0, 1800, 0, 0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 1800, 0, 0,   0,
    0, 0,    0,   0, 0, 0,   0, 900, 0, 0, 0, 0,    0, 0, 0, 0, 0,    0, 0, 0, -900, 0, 0, 0,    0, 0,   0,
    0, 0,    900, 0, 0, 0,   0, 0,   0, 0, 0, 0,    0, 0, 0, 0, -900, 0, 0, 0, 0,    0, 0, 0,    0, -900
};

s16 cKF_ds_npc_1_kutipaku2_tbl[] = {
    1,  0,    -2718, 2,  -90,  -3882, 3,  -259, -3882, 4,  -349, 0,     5,  -259, 3882, 6,  -90,  3882, 7,  0,    1359,
    8,  0,    -1053, 9,  -70,  -3370, 11, -379, -3370, 12, -449, -1053, 13, -449, 1359, 14, -359, 3882, 15, -190, 3882,
    16, -100, 423,   18, -299, -4119, 19, -437, -2995, 20, -499, 234,   21, -421, 3745, 23, -78,  3745, 24, 0,    -383,
    25, -103, -4438, 26, -296, -4438, 27, -399, 0,     28, -296, 4438,  29, -103, 4438, 30, 0,    3106
};

aNPC_Animation_c cKF_ba_r_npc_1_kutipaku2 = {
    { cKF_ckcb_r_npc_1_kutipaku2_tbl, cKF_ds_npc_1_kutipaku2_tbl, cKF_kn_npc_1_kutipaku2_tbl, cKF_c_npc_1_kutipaku2_tbl,
      -1, 30 },
    1.0f,
    30.0f,
    cKF_FRAMECONTROL_REPEAT,
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
