#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_act_m_nokogiri_b_tbl[] = { 0, 0, 0, 1, 1 };

s16 cKF_kn_act_m_nokogiri_b_tbl[] = { 9, 9 };

s16 cKF_c_act_m_nokogiri_b_tbl[] = { 300, 0, -1000, -900, 0, 0, 0, 0, -900, 0, 0, 900, 0, 0, 0, 0 };

s16 cKF_ds_act_m_nokogiri_b_tbl[] = { 1,  -900, 237,  2,  -892, 439,  8,  -687, 934,  9,  -660, 340, 10, -665, -300,
                                      11, -680, -144, 13, -664, 212,  16, -667, -104, 80, -900, -3,  1,  0,    -237,
                                      2,  -8,   -439, 8,  -213, -934, 9,  -240, -340, 10, -236, 300, 11, -220, 144,
                                      13, -236, -212, 16, -233, 104,  80, 0,    3 };

cKF_Animation_R_c cKF_ba_r_act_m_nokogiri_b = { cKF_ckcb_r_act_m_nokogiri_b_tbl,
                                                cKF_ds_act_m_nokogiri_b_tbl,
                                                cKF_kn_act_m_nokogiri_b_tbl,
                                                cKF_c_act_m_nokogiri_b_tbl,
                                                -1,
                                                80 };
