#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_npc_1_umbrella1_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_c_npc_1_umbrella1_tbl[] = { 0,    1000, 0,    0,    0,    900,   0,   0,  0,    0,    0,   1800, -175, -100,
                                    25,   0,    200,  0,    0,    -100,  0,   0,  0,    1800, 175, -100, -25,  0,
                                    200,  0,    0,    -100, 0,    0,     900, 0,  0,    60,   0,   0,    82,   0,
                                    0,    2,    0,    0,    0,    -900,  0,   58, -414, 0,    -57, 0,    0,    0,
                                    900,  -170, -365, 540,  -200, -1060, 420, -8, -50,  -350, 0,   0,    0,    0,
                                    -900, 0,    0,    0,    0,    0,     0,   0,  0,    0,    -900 };

aNPC_Animation_c cKF_ba_r_npc_1_umbrella1 = {
    { cKF_ckcb_r_npc_1_umbrella1_tbl, NULL, NULL, cKF_c_npc_1_umbrella1_tbl, -1, 2 },
    1.0f,
    2.0f,
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
