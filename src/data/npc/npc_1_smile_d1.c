#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_npc_1_smile_d1_tbl[] = { 56, 7, 0, 7, 7, 7, 0, 7, 7, 7, 0, 7, 7, 7, 0, 7, 7, 0, 7, 7, 7, 7, 0, 7, 0, 0 };

s16 cKF_kn_npc_1_smile_d1_tbl[] = { 2, 2, 2, 2, 4, 2, 4, 4, 4, 2, 4, 2, 2, 2, 2, 4, 4, 4, 2, 4, 2, 2, 2, 2, 2, 2, 2,
                                    2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2 };

s16 cKF_c_npc_1_smile_d1_tbl[] = { 0,    0, 900, 0,   0, 1800, 0, 0, 1800, 0, 900, 0, 0,   0,
                                   -900, 0, 0,   900, 0, -900, 0, 0, 0,    0, 0,   0, -900 };

s16 cKF_ds_npc_1_smile_d1_tbl[] = {
    1,  0,    0,    12, 0,    0,   1,  2400, 0,    12, 2400, 0,    1,  0,    0,    12, 0,    0,    1,  0,    0,
    12, 0,    0,    1,  80,   0,   3,  60,   0,    7,  80,   0,    12, 70,   0,    1,  0,    0,    12, 0,    0,
    1,  -750, 150,  3,  -700, 0,   7,  -750, 0,    12, -750, 0,    1,  -500, -149, 3,  -550, 0,    7,  -500, 0,
    12, -520, 0,    1,  300,  148, 3,  350,  0,    7,  320,  -202, 12, 310,  0,    1,  0,    0,    12, 0,    0,
    1,  350,  305,  3,  400,  0,   8,  300,  0,    12, 350,  0,    1,  0,    0,    12, 0,    0,    1,  0,    0,
    12, 0,    0,    1,  -100, 0,   12, -100, 0,    1,  0,    0,    12, 0,    0,    1,  750,  -147, 3,  700,  0,
    7,  750,  0,    12, 750,  0,   1,  -500, -150, 3,  -550, 0,    7,  -500, 0,    12, -520, 0,    1,  -300, -148,
    3,  -350, 0,    7,  -320, 200, 12, -310, 0,    1,  0,    0,    12, 0,    0,    1,  350,  302,  3,  400,  0,
    8,  300,  0,    12, 350,  0,   1,  0,    0,    12, 0,    0,    1,  0,    0,    12, 0,    0,    1,  -100, 0,
    12, -100, 0,    1,  0,    0,   12, 0,    0,    1,  0,    0,    12, 0,    0,    1,  -250, 0,    12, -250, 0,
    1,  0,    0,    12, 0,    0,   1,  0,    0,    12, 0,    0,    1,  -100, 0,    12, -100, 0,    1,  0,    0,
    12, 0,    0,    1,  0,    0,   12, 24,   -657, 1,  -100, -101, 4,  -220, 0,    8,  0,    0,    12, -22,  -457,
    1,  0,    0,    12, 0,    0,   1,  0,    0,    12, 0,    0,    1,  50,   0,    5,  -30,  0,    9,  150,  0,
    12, 108,  0,    1,  -650, 0,   12, -565, 0,    1,  0,    0,    12, 0,    0,    1,  -250, 0,    5,  -600, 0,
    8,  -400, 0,    12, -400, 0,   1,  0,    0,    12, 0,    0,    1,  0,    0,    12, 0,    0,    1,  50,   0,
    5,  -30,  0,    9,  150,  0,   12, 108,  0,    1,  650,  0,    12, 565,  0,    1,  0,    0,    12, 0,    0,
    1,  -250, 0,    5,  -600, 0,   8,  -400, 0,    12, -400, 0,    1,  0,    0,    12, 0,    0,    1,  0,    0,
    12, 0,    0,    1,  0,    0,   12, 0,    0,    1,  0,    0,    12, 0,    0,    1,  0,    0,    12, -24,  597,
    1,  0,    -152, 5,  -30,  0,   9,  80,   0,    12, 52,   -726, 1,  0,    0,    12, 0,    0,    1,  0,    0,
    12, 0,    0,    1,  0,    0,   12, 0,    0,    1,  0,    0,    12, 0,    0
};

u8 npc_1_smile_d10_tex_index[] = { 0, 0, 0, 1, 2, 2, 2, 5, 5, 5, 5, 5 };

u8 npc_1_smile_d11_tex_index[] = { 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2 };

aNPC_Animation_c cKF_ba_r_npc_1_smile_d1 = {
    { cKF_ckcb_r_npc_1_smile_d1_tbl, cKF_ds_npc_1_smile_d1_tbl, cKF_kn_npc_1_smile_d1_tbl, cKF_c_npc_1_smile_d1_tbl, -1,
      12 },
    1.0f,
    12.0f,
    cKF_FRAMECONTROL_STOP,
    -7.0f,
    npc_1_smile_d10_tex_index,
    aNPC_EYE_TEX0,
    -1,
    npc_1_smile_d11_tex_index,
    aNPC_MOUTH_TEX0,
    -1,
    1,
    eEC_EFFECT_WARAU,
    NULL,
    NULL,
};
