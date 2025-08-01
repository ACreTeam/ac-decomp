#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_act_mus_namazu_a1_tbl[] = { 56, 7, 2 };

s16 cKF_kn_act_mus_namazu_a1_tbl[] = { 5, 4, 6, 2, 4, 2, 3 };

s16 cKF_c_act_mus_namazu_a1_tbl[] = { 0, 900, 0, 0, 0 };

s16 cKF_ds_act_mus_namazu_a1_tbl[] = { 1,    9,    296,  15,  96,   -3,   33,  -1, -258, 51, -94, 1,    70,
                                       0,    267,  1,    -13, -171, 16,   -55, -5, 51,   61, 2,   70,   -7,
                                       -174, 1,    1199, 0,   12,   1199, 0,   26, 1199, 0,  43,  1199, 0,
                                       57,   1199, 0,    70,  1199, 0,    1,   0,  0,    70, 0,   0,    1,
                                       60,   292,  12,   96,  -6,   43,   -85, 1,  70,   49, 308, 1,    0,
                                       0,    70,   0,    0,   1,    -148, 115, 27, 131,  -1, 70,  -150, 8 };

cKF_Animation_R_c cKF_ba_r_act_mus_namazu_a1 = { cKF_ckcb_r_act_mus_namazu_a1_tbl,
                                                 cKF_ds_act_mus_namazu_a1_tbl,
                                                 cKF_kn_act_mus_namazu_a1_tbl,
                                                 cKF_c_act_mus_namazu_a1_tbl,
                                                 -1,
                                                 70 };
