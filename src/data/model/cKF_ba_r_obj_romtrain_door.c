#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_obj_romtrain_door_tbl[] = { 56, 7, 7, 0 };

s16 cKF_kn_obj_romtrain_door_tbl[] = { 2, 2, 2, 2, 5, 2, 2, 5, 2 };

s16 cKF_c_obj_romtrain_door_tbl[] = { 0, -900, 0, 0, 0, 0 };

s16 cKF_ds_obj_romtrain_door_tbl[] = { 1,  2000,   0, 51, 2000, 0, 1,  0,    0, 51, 0,     0, 1,  -14500, 0,
                                       51, -14500, 0, 1,  0,    0, 51, 0,    0, 1,  0,     0, 21, 140,    0,
                                       27, 140,    0, 48, -3,   0, 51, 0,    0, 1,  0,     0, 51, 0,      0,
                                       1,  0,      0, 51, 0,    0, 1,  -900, 0, 21, -1040, 0, 27, -1040,  0,
                                       48, -898,   0, 51, -900, 0, 1,  0,    0, 51, 0,     0 };

cKF_Animation_R_c cKF_ba_r_obj_romtrain_door = { cKF_ckcb_r_obj_romtrain_door_tbl,
                                                 cKF_ds_obj_romtrain_door_tbl,
                                                 cKF_kn_obj_romtrain_door_tbl,
                                                 cKF_c_obj_romtrain_door_tbl,
                                                 -1,
                                                 51 };
