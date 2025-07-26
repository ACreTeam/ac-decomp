#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

u8 cKF_ckcb_r_furniture_pull_tbl[] = { 8 };

s16 cKF_kn_furniture_pull_tbl[] = { 22 };

s16 cKF_c_furniture_pull_tbl[] = { 0, 0, 0, 0, 0 };

s16 cKF_ds_furniture_pull_tbl[] = { 1,     0,     -608,  2,     -20,   -1181, 4,     -172,  -3264, 5,     -296,
                                    -3277, 6,     -448,  -3277, 7,     -625,  -3277, 8,     -822,  -3277, 9,
                                    -1037, -3277, 10,    -1266, -3277, 11,    -1505, -3277, 12,    -1751, -3277,
                                    14,    -2249, -3277, 15,    -2495, -3277, 16,    -2734, -3277, 17,    -2963,
                                    -3277, 18,    -3178, -3277, 19,    -3375, -3277, 20,    -3552, -3277, 21,
                                    -3704, -3277, 22,    -3828, -3264, 24,    -3980, -1181, 25,    -4000, -608 };

cKF_Animation_R_c cKF_ba_r_furniture_pull = { cKF_ckcb_r_furniture_pull_tbl,
                                              cKF_ds_furniture_pull_tbl,
                                              cKF_kn_furniture_pull_tbl,
                                              cKF_c_furniture_pull_tbl,
                                              -1,
                                              25 };
