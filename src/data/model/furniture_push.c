#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

u8 cKF_ckcb_r_furniture_push_tbl[] = { 8 };

s16 cKF_kn_furniture_push_tbl[] = { 22 };

s16 cKF_c_furniture_push_tbl[] = { 0, 0, 0, 0, 0 };

s16 cKF_ds_furniture_push_tbl[] = { 1,    0,    92,   3,    19,   803,  5,    126,  2715, 6,    238,  3277, 7,    400,
                                    3277, 8,    602,  3277, 9,    822,  3277, 10,   1057, 3277, 11,   1304, 3277, 12,
                                    1559, 3277, 14,   2082, 3277, 15,   2342, 3277, 16,   2598, 3277, 17,   2845, 3277,
                                    18,   3080, 3277, 19,   3300, 3277, 20,   3499, 3277, 21,   3669, 3277, 22,   3808,
                                    3277, 23,   3912, 2535, 24,   3977, 1314, 25,   4000, 675 };

cKF_Animation_R_c cKF_ba_r_furniture_push = { cKF_ckcb_r_furniture_push_tbl,
                                              cKF_ds_furniture_push_tbl,
                                              cKF_kn_furniture_push_tbl,
                                              cKF_c_furniture_push_tbl,
                                              -1,
                                              25 };
