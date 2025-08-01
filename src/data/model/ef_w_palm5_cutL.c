#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 obj_w_palm_cutL_tex_txt[];
extern Vtx ef_w_palm5_cutL_v[];
extern u8 ef_w_palm_leaf_modeset[];
extern u8 ef_w_palm_trunk_modeset[];
Vtx ef_w_palm5_cutL_v[] = {
#include "assets/ef_w_palm5_cutL_v.inc"
};

Gfx ef_w_palm5_cutL_leaf_model[] = {
    gsSPDisplayList(ef_w_palm_leaf_modeset),
    gsSPVertex(ef_w_palm5_cutL_v, 32, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(20, 22, 23, 24, 25, 26, 24, 26, 27, 28, 29, 30),
    gsSPNTriangles_5b(28, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&ef_w_palm5_cutL_v[32], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx ef_w_palm5_cutL_trunk_model[] = {
    gsSPDisplayList(ef_w_palm_trunk_modeset),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 48, obj_w_palm_cutL_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&ef_w_palm5_cutL_v[48], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_ef_w_palm5_cutL_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 64536, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { ef_w_palm5_cutL_trunk_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 2250, 0, 0 } },
    { ef_w_palm5_cutL_leaf_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 4750, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_ef_w_palm5_cutL = { ARRAY_COUNT(cKF_je_r_ef_w_palm5_cutL_tbl), 2,
                                              cKF_je_r_ef_w_palm5_cutL_tbl };
