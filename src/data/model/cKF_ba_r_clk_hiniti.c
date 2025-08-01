#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 cKF_ckcb_r_clk_hiniti_tbl[] = { 0, 0, 2, 0 };

s16 cKF_kn_clk_hiniti_tbl[] = { 8 };

s16 cKF_c_clk_hiniti_tbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 900, 0, 0, 0 };

s16 cKF_ds_clk_hiniti_tbl[] = { 1,  0,    -257,  2,  -9,    -511,  9,  -522,  -3802, 10, -656,  -4347,
                                11, -812, -6391, 12, -1082, -8964, 14, -1685, -5857, 15, -1800, -3447 };

cKF_Animation_R_c cKF_ba_r_clk_hiniti = {
    cKF_ckcb_r_clk_hiniti_tbl, cKF_ds_clk_hiniti_tbl, cKF_kn_clk_hiniti_tbl, cKF_c_clk_hiniti_tbl, -1, 15
};
