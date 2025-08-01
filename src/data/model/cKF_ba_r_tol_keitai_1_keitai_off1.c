#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_tol_keitai_1_keitai_off1_tbl[] = { 56, 7, 7 };

s16 cKF_kn_tol_keitai_1_keitai_off1_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 6, 2 };

s16 cKF_c_tol_keitai_1_keitai_off1_tbl[] = { 0, 0, 0 };

s16 cKF_ds_tol_keitai_1_keitai_off1_tbl[] = { 1, 0,    0, 61,   0,    0,  1,    0,    0,     61, 0,     0,  1,  0,
                                              0, 61,   0, 0,    1,    0,  0,    61,   0,     0,  1,     0,  0,  61,
                                              0, 0,    1, -900, 0,    61, -900, 0,    1,     0,  0,     61, 0,  0,
                                              1, -350, 0, 13,   -350, 0,  17,   -350, -2250, 26, -1800, 0,  41, -1800,
                                              0, 61,   0, 0,    1,    0,  0,    61,   0,     0 };

cKF_Animation_R_c cKF_ba_r_tol_keitai_1_keitai_off1 = { cKF_ckcb_r_tol_keitai_1_keitai_off1_tbl,
                                                        cKF_ds_tol_keitai_1_keitai_off1_tbl,
                                                        cKF_kn_tol_keitai_1_keitai_off1_tbl,
                                                        cKF_c_tol_keitai_1_keitai_off1_tbl,
                                                        -1,
                                                        61 };
