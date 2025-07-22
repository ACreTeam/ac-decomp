#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

u8 act_bee_tex_txt[] = {
#include "assets/act_bee_tex_txt.inc"
};

Vtx act_bee_v[] = {
#include "assets/act_bee_v.inc"
};

Gfx act_bee_C_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 1, 0, TEXEL0, TEXEL1, 0, 0, 0, COMBINED, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, act_bee_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 15, 15),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, act_bee_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 15, 15),
    gsSPDisplayList(anime_1_txt),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH),
    gsSPVertex(act_bee_v, 5, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(&act_bee_v[5], 21, 5),
    gsSPNTrianglesInit_5b(10, 2, 5, 6, 2, 7, 3, 3, 8, 9),
    gsSPNTriangles_5b(3, 10, 0, 1, 11, 12, 1, 13, 4, 0, 14, 15),
    gsSPNTriangles_5b(0, 16, 1, 4, 17, 18, 4, 19, 2, 0, 0, 0),
    gsSPNTrianglesInit_5b(5, 20, 21, 22, 22, 21, 23, 24, 21, 25),
    gsSPNTriangles_5b(23, 21, 24, 25, 21, 20, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList()
};

Gfx act_bee_B_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 1, 0, TEXEL0, TEXEL1, 0, 0, 0, COMBINED, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, act_bee_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 15, 15),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, act_bee_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 15, 15),
    gsSPDisplayList(anime_1_txt),
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH),
    gsSPVertex(&act_bee_v[26], 5, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPVertex(&act_bee_v[31], 15, 5),
    gsSPNTrianglesInit_5b(10, 2, 5, 6, 2, 7, 3, 3, 8, 9),
    gsSPNTriangles_5b(3, 10, 4, 0, 11, 12, 0, 13, 1, 4, 14, 15),
    gsSPNTriangles_5b(4, 16, 0, 1, 17, 18, 1, 19, 2, 0, 0, 0),
    gsSPEndDisplayList()
};

Gfx act_bee_A_model[] = {
    gsSPTexture(4000, 4000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 1, 0, TEXEL0, TEXEL1, 0, 0, 0, COMBINED, COMBINED, 0, PRIMITIVE, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_CLD_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, act_bee_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 15, 15),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, act_bee_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_REPEAT, GX_REPEAT, 15, 15),
    gsSPDisplayList(anime_1_txt),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH),
    gsSPVertex(&act_bee_v[46], 12, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 0, 3, 4, 0, 4, 1),
    gsSPNTriangles_5b(5, 4, 6, 5, 6, 7, 5, 7, 2, 8, 9, 2),
    gsSPNTriangles_5b(8, 10, 11, 8, 11, 9, 7, 6, 10, 7, 10, 8),
    gsSPNTriangles_5b(7, 8, 2, 9, 11, 3, 9, 3, 0, 9, 0, 2),
    gsSPEndDisplayList()
};

u8 cKF_ckcb_r_act_bee_tbl[] = { 0, 0, 2, 2 };

s16 cKF_kn_act_bee_tbl[] = { 2, 2 };

s16 cKF_c_act_bee_tbl[] = { 0, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_act_bee_tbl[] = { 1, 300, -100, 181, -300, -100, 1, 300, -100, 181, -300, -100 };

cKF_Animation_R_c cKF_ba_r_act_bee[] = { { cKF_ckcb_r_act_bee_tbl, cKF_ds_act_bee_tbl, cKF_kn_act_bee_tbl,
                                           cKF_c_act_bee_tbl, -1, 181 } };

cKF_Joint_R_c cKF_je_r_act_bee_tbl[] = { { NULL, 1, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                         { act_bee_A_model, 1, cKF_JOINT_FLAG_DISP_XLU, { 0, 0, 0 } },
                                         { act_bee_B_model, 1, cKF_JOINT_FLAG_DISP_XLU, { 1000, 0, 0 } },
                                         { act_bee_C_model, 0, cKF_JOINT_FLAG_DISP_XLU, { 1500, 0, 0 } } };

cKF_Skeleton_R_c cKF_bs_r_act_bee[] = { { ARRAY_COUNT(cKF_je_r_act_bee_tbl), 3, cKF_je_r_act_bee_tbl } };
