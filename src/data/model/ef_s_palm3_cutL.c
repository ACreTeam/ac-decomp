#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx ef_s_palm3_cutL_v[];
extern u8 ef_s_palm_leaf_modeset[];
extern u8 ef_s_palm_trunk_modeset[];
extern u8 obj_s_palm_cutS_tex_txt[];
Vtx ef_s_palm3_cutL_v[] = {
#include "assets/ef_s_palm3_cutL_v.inc"
};

Gfx ef_s_palm3_cutL_leaf_model[] = {
    gsSPDisplayList(ef_s_palm_leaf_modeset),
    gsSPVertex(ef_s_palm3_cutL_v, 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx ef_s_palm3_cutL_trunk_model[] = {
    gsSPDisplayList(ef_s_palm_trunk_modeset),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_s_palm_cutS_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&ef_s_palm3_cutL_v[16], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_ef_s_palm3_cutL_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 65036, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { ef_s_palm3_cutL_trunk_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 1750, 0, 0 } },
    { ef_s_palm3_cutL_leaf_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 2000, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_ef_s_palm3_cutL = { ARRAY_COUNT(cKF_je_r_ef_s_palm3_cutL_tbl), 2,
                                              cKF_je_r_ef_s_palm3_cutL_tbl };
