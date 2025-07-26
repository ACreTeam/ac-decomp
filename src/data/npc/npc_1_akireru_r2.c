#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_npc_1_akireru_r2_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_c_npc_1_akireru_r2_tbl[] = { 0,    0,    0,    0,  0, 900,  0,   -50,  0,    0,    0,    1800, 0, 0,
                                     0,    0,    0,    0,  0, 0,    0,   0,    0,    1800, 0,    0,    0, 0,
                                     0,    0,    0,    0,  0, 0,    900, 0,    0,    0,    0,    0,    0, 0,
                                     0,    -100, 0,    0,  0, -900, 0,   -53,  -270, 140,  -693, -115, 0, 0,
                                     900,  403,  -548, 98, 0, -793, 0,   -420, 145,  -618, 0,    50,   0, 0,
                                     -900, 0,    0,    0,  0, 0,    0,   0,    0,    0,    -900 };

aNPC_Animation_c cKF_ba_r_npc_1_akireru_r2 = {
    { cKF_ckcb_r_npc_1_akireru_r2_tbl, NULL, NULL, cKF_c_npc_1_akireru_r2_tbl, -1, 2 },
    1.0f,
    2.0f,
    cKF_FRAMECONTROL_REPEAT,
    0.0f,
    NULL,
    aNPC_EYE_TEX0,
    3,
    NULL,
    aNPC_MOUTH_TEX2,
    5,
    -1,
    -1,
    NULL,
    NULL,
};
