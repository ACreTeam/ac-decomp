#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_ef_s_palm5_shakeS_tbl[] = { 56, 7 };

s16 cKF_kn_ef_s_palm5_shakeS_tbl[] = { 2, 2, 2, 2, 2, 5 };

s16 cKF_c_ef_s_palm5_shakeS_tbl[] = { 0, 0, 900 };

s16 cKF_ds_ef_s_palm5_shakeS_tbl[] = { 1, 0, 0, 9, 0, 0, 1, 7000, 0, 9,   7000, 0,  1, 0, 0,   9, 0, 0,  1, 0, 0, 9, 0,
                                       0, 1, 0, 0, 9, 0, 0, 1,    0, 663, 3,    30, 0, 6, -20, 0, 8, 10, 0, 9, 0, 0 };

cKF_Animation_R_c cKF_ba_r_ef_s_palm5_shakeS = { cKF_ckcb_r_ef_s_palm5_shakeS_tbl,
                                                 cKF_ds_ef_s_palm5_shakeS_tbl,
                                                 cKF_kn_ef_s_palm5_shakeS_tbl,
                                                 cKF_c_ef_s_palm5_shakeS_tbl,
                                                 -1,
                                                 9 };
