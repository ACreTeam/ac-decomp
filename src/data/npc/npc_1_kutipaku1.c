#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_npc_1_kutipaku1_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 };

s16 cKF_kn_npc_1_kutipaku1_tbl[] = { 24 };

s16 cKF_c_npc_1_kutipaku1_tbl[] = {
    0, 1000, 0,   0, 0, 900, 0, 0,   0, 0, 0, 1800, 0, 0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 1800, 0, 0,   0,
    0, 0,    0,   0, 0, 0,   0, 900, 0, 0, 0, 0,    0, 0, 0, 0, 0,    0, 0, 0, -900, 0, 0, 0,    0, 0,   0,
    0, 0,    900, 0, 0, 0,   0, 0,   0, 0, 0, 0,    0, 0, 0, 0, -900, 0, 0, 0, 0,    0, 0, 0,    0, -900
};

s16 cKF_ds_npc_1_kutipaku1_tbl[] = { 1,  0,    -1167, 2,  -39,  -1667, 3,  -111, -1667, 4,  -150, 0,
                                     5,  -111, 1667,  6,  -39,  1667,  8,  0,    -586,  9,  -39,  -1875,
                                     11, -211, -1875, 13, -250, 583,   14, -211, 1667,  15, -139, 1667,
                                     16, -100, 115,   18, -200, -2063, 20, -300, 234,   21, -253, 2250,
                                     23, -47,  2250,  24, 0,    -75,   25, -52,  -2222, 26, -148, -2222,
                                     27, -200, 0,     28, -148, 2222,  29, -52,  2222,  30, 0,    1556 };

aNPC_Animation_c cKF_ba_r_npc_1_kutipaku1 = {
    { cKF_ckcb_r_npc_1_kutipaku1_tbl, cKF_ds_npc_1_kutipaku1_tbl, cKF_kn_npc_1_kutipaku1_tbl, cKF_c_npc_1_kutipaku1_tbl,
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
