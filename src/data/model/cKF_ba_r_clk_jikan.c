#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_clk_jikan_tbl[] = { 0, 0, 2, 0 };

s16 cKF_kn_clk_jikan_tbl[] = { 5 };

s16 cKF_c_clk_jikan_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0 };

s16 cKF_ds_clk_jikan_tbl[] = { 1, 0, 9, 12, -1050, -8992, 13, -1377, -9336, 14, -1672, -6342, 15, -1800, -3840 };

cKF_Animation_R_c cKF_ba_r_clk_jikan = {
    cKF_ckcb_r_clk_jikan_tbl, cKF_ds_clk_jikan_tbl, cKF_kn_clk_jikan_tbl, cKF_c_clk_jikan_tbl, -1, 15
};
