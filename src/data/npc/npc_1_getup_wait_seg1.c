#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_npc_1_getup_wait_seg1_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_c_npc_1_getup_wait_seg1_tbl[] = {
    0,    700, -1750, 0,   0,    900,  0,    -850, 0, 0, 0,    1800, -250, -200, 200, 0,   400,  0,    0, 250,  0,
    0,    0,   1800,  100, -500, -100, 0,    800,  0, 0, 270,  2,    0,    900,  0,   0,   -22,  0,    0, -179, 0,
    0,    -50, 0,     0,   0,    -900, -850, -150, 0, 0, -400, 0,    0,    0,    900, 850, -150, -138, 0, -400, 0,
    -104, 386, -181,  550, 400,  0,    0,    -900, 0, 0, 0,    0,    0,    0,    0,   0,   0,    -900
};

aNPC_Animation_c cKF_ba_r_npc_1_getup_wait_seg1 = {
    { cKF_ckcb_r_npc_1_getup_wait_seg1_tbl, NULL, NULL, cKF_c_npc_1_getup_wait_seg1_tbl, -1, 2 },
    1.0f,
    2.0f,
    cKF_FRAMECONTROL_REPEAT,
    -8.0f,
    NULL,
    aNPC_EYE_TEX0,
    2,
    NULL,
    aNPC_MOUTH_TEX0,
    0,
    -1,
    -1,
    NULL,
    NULL,
};
