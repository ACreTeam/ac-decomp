#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

u8 cKF_ckcb_r_obj_s_post_delivery1_tbl[] = { 56, 0, 7, 0, 0, 7 };

s16 cKF_kn_obj_s_post_delivery1_tbl[] = { 2, 2, 2, 2, 2, 2, 2, 2, 11 };

s16 cKF_c_obj_s_post_delivery1_tbl[] = { 0, 0, 0, 0, 450, 0, 0, 0, 0, 0, 450, 0 };

s16 cKF_ds_obj_s_post_delivery1_tbl[] = { 1,    550, 0,    98,   550,   0,    1,   0,   0,    98,  0,   0,    1,  -450,
                                          0,    98,  -450, 0,    1,     0,    0,   98,  0,    0,   1,   0,    0,  98,
                                          0,    0,   1,    0,    0,     98,   0,   0,   1,    0,   0,   98,   0,  0,
                                          1,    0,   0,    98,   0,     0,    1,   900, 0,    11,  900, 0,    17, 1200,
                                          3750, 26,  2150, 0,    29,    2050, 0,   32,  2120, 0,   35,  2100, 0,  77,
                                          2100, 0,   84,   1300, -4869, 88,   900, 0,   98,   900, 0 };

cKF_Animation_R_c cKF_ba_r_obj_s_post_delivery1 = { cKF_ckcb_r_obj_s_post_delivery1_tbl,
                                                    cKF_ds_obj_s_post_delivery1_tbl,
                                                    cKF_kn_obj_s_post_delivery1_tbl,
                                                    cKF_c_obj_s_post_delivery1_tbl,
                                                    -1,
                                                    98 };
