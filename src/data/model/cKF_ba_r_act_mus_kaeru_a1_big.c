#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_act_mus_kaeru_a1_big_tbl[] = { 0, 0, 1, 0, 1 };

s16 cKF_kn_act_mus_kaeru_a1_big_tbl[] = { 3, 5 };

s16 cKF_c_act_mus_kaeru_a1_big_tbl[] = { 0, 0, 1610, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_act_mus_kaeru_a1_big_tbl[] = { 1, 0,   5,    13, 4,    -19, 20, 0,   -4,  1,  -50, -123,
                                          2, -54, -227, 10, -170, -11, 19, -53, 187, 20, -50, 101 };

cKF_Animation_R_c cKF_ba_r_act_mus_kaeru_a1_big = { cKF_ckcb_r_act_mus_kaeru_a1_big_tbl,
                                                    cKF_ds_act_mus_kaeru_a1_big_tbl,
                                                    cKF_kn_act_mus_kaeru_a1_big_tbl,
                                                    cKF_c_act_mus_kaeru_a1_big_tbl,
                                                    -1,
                                                    20 };
