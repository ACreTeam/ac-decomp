#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_obj_museum5_hasu_tbl[] = { 0, 0, 0, 1, 1, 0, 1, 1, 1, 1 };

s16 cKF_kn_obj_museum5_hasu_tbl[] = { 2, 2, 2, 2, 2, 2 };

s16 cKF_c_obj_museum5_hasu_tbl[] = { 3390, 0,    2800, -900, 0,   0, 0, 0, -900, -1800, 1800, 217, 0,   0,
                                     0,    -900, 0,    0,    900, 0, 0, 0, -900, 0,     0,    0,   -900 };

s16 cKF_ds_obj_museum5_hasu_tbl[] = { 1, -900, 675,  161, 2700,  675,  1, 0, -675, 161, -3600, -675,
                                      1, -900, -675, 161, -4500, -675, 1, 0, 675,  161, 3600,  675,
                                      1, 0,    675,  161, 3600,  675,  1, 0, -675, 161, -3600, -675 };

cKF_Animation_R_c cKF_ba_r_obj_museum5_hasu = { cKF_ckcb_r_obj_museum5_hasu_tbl,
                                                cKF_ds_obj_museum5_hasu_tbl,
                                                cKF_kn_obj_museum5_hasu_tbl,
                                                cKF_c_obj_museum5_hasu_tbl,
                                                -1,
                                                161 };
