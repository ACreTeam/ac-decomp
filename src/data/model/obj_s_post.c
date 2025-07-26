#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

u8 cKF_ckcb_r_obj_s_post_tbl[] = { 0, 0, 0, 0, 0, 0 };

s16 cKF_c_obj_s_post_tbl[] = { 550, 0, -450, 0, 0, 0, 0, 450, 0, 0, 0, 0, 0, 0, 0, 0, 450, 0, 0, 0, 900 };

cKF_Animation_R_c cKF_ba_r_obj_s_post = { cKF_ckcb_r_obj_s_post_tbl, NULL, NULL, cKF_c_obj_s_post_tbl, -1, 2 };
