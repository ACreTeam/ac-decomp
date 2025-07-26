#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_npc_1_utiwa_wait1_tbl[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0, 0, 0, 0, 0
};

s16 cKF_kn_npc_1_utiwa_wait1_tbl[] = { 4, 4, 4, 2, 2, 2, 4, 4, 4 };

s16 cKF_c_npc_1_utiwa_wait1_tbl[] = { 0, 1000, 0,    0, 0,    900,  0, 0,   0,    0,   0,    1800, -175, -100, 25,
                                      0, 200,  0,    0, -100, 0,    0, 0,   1800, 175, -100, -25,  0,    200,  0,
                                      0, -100, 0,    0, 900,  0,    0, 60,  0,    0,   82,   0,    0,    2,    0,
                                      0, 0,    -900, 0, 58,   -564, 0, -57, 0,    0,   0,    900,  0,    0,    0,
                                      0, -900, 0,    0, 0,    0,    0, 0,   0,    0,   0,    -900 };

s16 cKF_ds_npc_1_utiwa_wait1_tbl[] = { 1,  -58,  -97,  8,  -100, 0,    16, -55,  0,    17, -58,  -97,  1,  -53,  -156,
                                       8,  -100, 0,    16, -50,  0,    17, -53,  -156, 1,  303,  147,  8,  350,  0,
                                       16, 300,  0,    17, 303,  147,  1,  0,    0,    17, 0,    0,    1,  -500, 0,
                                       17, -500, 0,    1,  0,    0,    17, 0,    0,    1,  630,  1063, 2,  650,  0,
                                       10, 200,  0,    17, 630,  1063, 1,  -495, -324, 2,  -500, 0,    10, -400, 0,
                                       17, -495, -324, 1,  348,  138,  2,  350,  0,    10, 300,  0,    17, 348,  138 };

aNPC_Animation_c cKF_ba_r_npc_1_utiwa_wait1 = {
    { cKF_ckcb_r_npc_1_utiwa_wait1_tbl, cKF_ds_npc_1_utiwa_wait1_tbl, cKF_kn_npc_1_utiwa_wait1_tbl,
      cKF_c_npc_1_utiwa_wait1_tbl, -1, 17 },
    1.0f,
    17.0f,
    cKF_FRAMECONTROL_REPEAT,
    -5.0f,
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
