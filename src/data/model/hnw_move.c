#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

u8 cKF_ckcb_r_hnw_move_tbl[] = { 0, 0, 3, 0, 4, 0, 4 };

s16 cKF_kn_hnw_move_tbl[] = { 8, 8, 8, 8 };

s16 cKF_c_hnw_move_tbl[] = { 0, 419, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0, -899, 0, 4, 0, 1800, -899, 0, 4 };

s16 cKF_ds_hnw_move_tbl[] = { 1, 94,    1687,   2, 150,   0,      3, 94,   -2250,  5, -94,  -2250,  6, -150,  0,
                              7, -94,   2250,   8, 0,     2813,   9, 94,   2813,   1, -125, 3750,   2, 0,     3750,
                              3, 125,   3000,   4, 200,   0,      5, 125,  -3000,  7, -125, -3000,  8, -200,  0,
                              9, -125,  2250,   1, 281,   -8437,  2, 0,    0,      3, 281,  13500,  5, 1519,  13500,
                              6, 1800,  0,      7, 1519,  -13500, 8, 900,  -18563, 9, 281,  -18563, 1, -1519, -8438,
                              2, -1800, 0,      3, -1519, 13500,  5, -281, 13500,  6, 0,    0,      7, -281,  -13500,
                              8, -900,  -18563, 9, -1519, -18563 };

cKF_Animation_R_c cKF_ba_r_hnw_move = {
    cKF_ckcb_r_hnw_move_tbl, cKF_ds_hnw_move_tbl, cKF_kn_hnw_move_tbl, cKF_c_hnw_move_tbl, -1, 9
};
