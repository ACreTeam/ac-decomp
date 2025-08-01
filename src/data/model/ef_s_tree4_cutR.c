#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 ef_s_tree_trunk_modeset[];
extern Vtx ef_s_tree4_cutR_v[];
extern u8 obj_s_tree_cutL_tex_txt[];
extern u8 ef_s_tree_leaf_modeset[];
Vtx ef_s_tree4_cutR_v[] = {
#include "assets/ef_s_tree4_cutR_v.inc"
};

Gfx ef_s_tree4_cutR_leaf_model[] = {
    gsSPDisplayList(ef_s_tree_leaf_modeset),
    gsSPVertex(ef_s_tree4_cutR_v, 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(4, 2, 1, 0, 4, 3, 2, 0),
    gsSP2Triangles(5, 6, 7, 0, 6, 8, 7, 0),
    gsSP2Triangles(5, 7, 9, 0, 8, 9, 7, 0),
    gsSPEndDisplayList(),
};

Gfx ef_s_tree4_cutR_trunk_model[] = {
    gsSPDisplayList(ef_s_tree_trunk_modeset),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 48, obj_s_tree_cutL_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&ef_s_tree4_cutR_v[10], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(2, 1, 4, 0, 1, 5, 4, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_ef_s_tree4_cutR_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 750, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { ef_s_tree4_cutR_trunk_model, 1, cKF_JOINT_FLAG_DISP_OPA, { 2250, 0, 0 } },
    { ef_s_tree4_cutR_leaf_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 3750, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_ef_s_tree4_cutR = { ARRAY_COUNT(cKF_je_r_ef_s_tree4_cutR_tbl), 2,
                                              cKF_je_r_ef_s_tree4_cutR_tbl };
