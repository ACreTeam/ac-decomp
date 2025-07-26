#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_npc_1_landing1_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_c_npc_1_landing1_tbl[] = { 0,    1000, 0,    3600, 0, 900,  0,    200,  0,   0,    0,   1800, -100, -450,
                                   300,  0,    150,  0,    0, 200,  0,    0,    0,   1800, 100, -450, -300, 0,
                                   150,  0,    0,    200,  0, 0,    900,  0,    0,   60,   0,   0,    80,   0,
                                   0,    -200, 0,    0,    0, -900, -100, -100, 300, 0,    200, 300,  0,    0,
                                   900,  100,  -100, -300, 0, 200,  -300, 0,    0,   0,    0,   -300, 0,    0,
                                   -900, 0,    0,    0,    0, 0,    0,    0,    0,   0,    -900 };

aNPC_Animation_c cKF_ba_r_npc_1_landing1 = {
    { cKF_ckcb_r_npc_1_landing1_tbl, NULL, NULL, cKF_c_npc_1_landing1_tbl, -1, 2 },
    1.0f,
    2.0f,
    cKF_FRAMECONTROL_REPEAT,
    -10.0f,
    NULL,
    aNPC_EYE_TEX1,
    -1,
    NULL,
    aNPC_MOUTH_TEX0,
    0,
    -1,
    -1,
    NULL,
    NULL,
};
