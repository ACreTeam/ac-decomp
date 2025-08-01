#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_act_m_okuwa_b_tbl[] = { 0, 0, 0, 1, 1 };

s16 cKF_kn_act_m_okuwa_b_tbl[] = { 10, 10 };

s16 cKF_c_act_m_okuwa_b_tbl[] = { 300, 0, -1000, -900, 0, 0, 0, 0, -900, 0, 0, 900, 0, 0, 0, 0 };

s16 cKF_ds_act_m_okuwa_b_tbl[] = { 1,  -900, 199,  2,  -893, 367,  8,  -722, 773,  9,  -700, 253,  10, -706, -300,
                                   11, -720, -131, 13, -704, 214,  14, -700, 20,   15, -703, -82,  80, -900, -3,
                                   1,  0,    -199, 2,  -7,   -368, 8,  -178, -773, 9,  -200, -253, 10, -195, 300,
                                   11, -180, 131,  13, -196, -214, 14, -200, -20,  15, -197, 82,   80, 0,    3 };

cKF_Animation_R_c cKF_ba_r_act_m_okuwa_b = {
    cKF_ckcb_r_act_m_okuwa_b_tbl, cKF_ds_act_m_okuwa_b_tbl, cKF_kn_act_m_okuwa_b_tbl, cKF_c_act_m_okuwa_b_tbl, -1, 80
};
