#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_act_mus_aroana_a1_tbl[] = { 56, 7, 2 };

s16 cKF_kn_act_mus_aroana_a1_tbl[] = { 5, 4, 6, 2, 4, 2, 3 };

s16 cKF_c_act_mus_aroana_a1_tbl[] = { 0, 900, 0, 0, 0 };

s16 cKF_ds_act_mus_aroana_a1_tbl[] = { 1,    8,    261,  15,  58,   -3,   33,  -1, -244, 51, -56, 1,    70,
                                       0,    205,  1,    -12, -131, 16,   -37, -5, 51,   37, 2,   70,   -7,
                                       -121, 1,    1195, 0,   12,   1195, 0,   26, 1195, 0,  43,  1195, 0,
                                       57,   1195, 0,    70,  1195, 0,    1,   0,  0,    70, 0,   0,    1,
                                       68,   335,  12,   110, -6,   43,   -98, 2,  70,   57, 354, 1,    0,
                                       0,    70,   0,    0,   1,    -226, 175, 27, 200,  -1, 70,  -229, 13 };

cKF_Animation_R_c cKF_ba_r_act_mus_aroana_a1 = { cKF_ckcb_r_act_mus_aroana_a1_tbl,
                                                 cKF_ds_act_mus_aroana_a1_tbl,
                                                 cKF_kn_act_mus_aroana_a1_tbl,
                                                 cKF_c_act_mus_aroana_a1_tbl,
                                                 -1,
                                                 70 };
