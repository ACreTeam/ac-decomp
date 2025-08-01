#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_act_mus_kaseki_a1_tbl[] = { 56, 7, 7, 7 };

s16 cKF_kn_act_mus_kaseki_a1_tbl[] = { 6, 4, 6, 2, 4, 2, 2, 4, 2, 3, 4, 3 };

s16 cKF_c_act_mus_kaseki_a1_tbl[] = { 0, 900, 0 };

s16 cKF_ds_act_mus_kaseki_a1_tbl[] = {
    1,  37,   518,  14, 156,  -5,  33, 1,   -462, 51, -159, 1,    67, -10,  485, 70, 37,   474, 1,  -11,  -215,
    14, -82,  -7,   51, 75,   4,   70, -11, -226, 1,  1627, 0,    14, 1627, 0,   30, 1627, 0,   49, 1627, 0,
    65, 1627, 0,    70, 1627, 0,   1,  0,   0,    70, 0,    0,    1,  51,   198, 10, 77,   -8,  43, -69,  2,
    70, 51,   199,  1,  0,    0,   70, 0,   0,    1,  0,    0,    70, 0,    0,   1,  -67,  -13, 3,  -68,  6,
    30, 73,   0,    70, -67,  -23, 1,  0,   0,    70, 0,    0,    1,  0,    0,   9,  0,    0,   70, 0,    0,
    1,  -64,  -182, 14, -103, 14,  42, 108, -3,   70, -64,  -179, 1,  0,    0,   9,  0,    0,   70, 0,    0
};

cKF_Animation_R_c cKF_ba_r_act_mus_kaseki_a1 = { cKF_ckcb_r_act_mus_kaseki_a1_tbl,
                                                 cKF_ds_act_mus_kaseki_a1_tbl,
                                                 cKF_kn_act_mus_kaseki_a1_tbl,
                                                 cKF_c_act_mus_kaseki_a1_tbl,
                                                 -1,
                                                 70 };
