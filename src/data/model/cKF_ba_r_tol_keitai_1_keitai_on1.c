#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_tol_keitai_1_keitai_on1_tbl[] = { 0, 0, 2 };

s16 cKF_kn_tol_keitai_1_keitai_on1_tbl[] = { 14 };

s16 cKF_c_tol_keitai_1_keitai_on1_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, -900, 0, 0 };

s16 cKF_ds_tol_keitai_1_keitai_on1_tbl[] = { 1,     0,    -787,  2,    -26,  -1496, 8,    -900, -5746, 14,   -1774,
                                             -1496, 15,   -1800, 114,  16,   -1766, 1902, 20,   -1169, 5899, 23,
                                             -597,  4831, 25,    -350, 2238, 27,    -296, -180, 29,    -338, -539,
                                             30,    -350, -180,  31,   -350, 0,     68,   -350, 0 };

cKF_Animation_R_c cKF_ba_r_tol_keitai_1_keitai_on1 = { cKF_ckcb_r_tol_keitai_1_keitai_on1_tbl,
                                                       cKF_ds_tol_keitai_1_keitai_on1_tbl,
                                                       cKF_kn_tol_keitai_1_keitai_on1_tbl,
                                                       cKF_c_tol_keitai_1_keitai_on1_tbl,
                                                       -1,
                                                       68 };
