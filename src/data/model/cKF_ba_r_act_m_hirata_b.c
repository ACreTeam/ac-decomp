#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_act_m_hirata_b_tbl[] = { 0, 0, 0, 1, 1 };

s16 cKF_kn_act_m_hirata_b_tbl[] = { 9, 9 };

s16 cKF_c_act_m_hirata_b_tbl[] = { 300, 0, -1000, -900, 0, 0, 0, 0, -900, 0, 0, 900, 0, 0, 0, 0 };

s16 cKF_ds_act_m_hirata_b_tbl[] = { 1,    -900, 180,  2,    -894, 332,  8,    -740, 692,  9,    -720, 210,  10,   -726,
                                    -300, 11,   -740, -124, 13,   -724, 214,  16,   -725, -76,  80,   -900, -3,   1,
                                    0,    -180, 2,    -6,   -332, 8,    -160, -692, 9,    -180, -210, 10,   -174, 300,
                                    11,   -160, 124,  13,   -176, -214, 16,   -175, 76,   80,   0,    3 };

cKF_Animation_R_c cKF_ba_r_act_m_hirata_b = { cKF_ckcb_r_act_m_hirata_b_tbl,
                                              cKF_ds_act_m_hirata_b_tbl,
                                              cKF_kn_act_m_hirata_b_tbl,
                                              cKF_c_act_m_hirata_b_tbl,
                                              -1,
                                              80 };
