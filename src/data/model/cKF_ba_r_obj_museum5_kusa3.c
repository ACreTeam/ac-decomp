#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_obj_museum5_kusa3_tbl[] = { 0, 1, 1, 1 };

s16 cKF_kn_obj_museum5_kusa3_tbl[] = { 4, 3, 4 };

s16 cKF_c_obj_museum5_kusa3_tbl[] = { 0, 5000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_museum5_kusa3_tbl[] = { 1,   900, 36,  35, 917, -21, 81,   881, 13,  101, 900, 36, 1,   -40, 3, 56,  38,
                                       -26, 101, -40, -3, 1,   0,   -126, 29,  -69, 28,  79,  69, -28, 101, 0, -126 };

cKF_Animation_R_c cKF_ba_r_obj_museum5_kusa3 = { cKF_ckcb_r_obj_museum5_kusa3_tbl,
                                                 cKF_ds_obj_museum5_kusa3_tbl,
                                                 cKF_kn_obj_museum5_kusa3_tbl,
                                                 cKF_c_obj_museum5_kusa3_tbl,
                                                 -1,
                                                 101 };
