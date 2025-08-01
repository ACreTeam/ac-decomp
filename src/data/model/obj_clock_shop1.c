#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx obj_clock_shop1_v[];
u16 obj_shop1_clock_pal[] = {
#include "assets/obj_shop1_clock_pal.inc"
};

u8 obj_clock_shop1_tex_txt[] = {
#include "assets/obj_clock_shop1_tex_txt.inc"
};

Vtx obj_clock_shop1_v[] = {
#include "assets/obj_clock_shop1_v.inc"
};

Gfx obj_clock_shop1_base_model[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, obj_shop1_clock_pal),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, obj_clock_shop1_tex_txt),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_clock_shop1_v[12], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 1, 0, 0, 5, 6, 7, 0),
    gsSP2Triangles(6, 8, 7, 0, 5, 9, 6, 0),
    gsSP2Triangles(5, 10, 9, 0, 10, 11, 9, 0),
    gsSP2Triangles(9, 12, 6, 0, 12, 13, 6, 0),
    gsSP2Triangles(9, 14, 12, 0, 15, 16, 17, 0),
    gsSP2Triangles(15, 17, 18, 0, 19, 20, 21, 0),
    gsSP2Triangles(19, 21, 22, 0, 23, 24, 25, 0),
    gsSP2Triangles(23, 25, 26, 0, 27, 28, 29, 0),
    gsSP1Triangle(27, 29, 30, 0),
    gsSPVertex(&obj_clock_shop1_v[43], 22, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSP2Triangles(19, 18, 20, 0, 19, 20, 21, 0),
    gsSPEndDisplayList(),
};

Gfx obj_clock_shop1_long_model[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, obj_shop1_clock_pal),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, obj_clock_shop1_tex_txt),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_clock_shop1_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx obj_clock_shop1_short_model[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, obj_shop1_clock_pal),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, obj_clock_shop1_tex_txt),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_clock_shop1_v[4], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx obj_clock_shop1_pend_model[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, obj_shop1_clock_pal),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, obj_clock_shop1_tex_txt),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 4, 0, G_TX_RENDERTILE, 15, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_clock_shop1_v[8], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_obj_clock_shop1_tbl[] = { 0, 0, 0, 1, 0, 0, 0 };

s16 cKF_kn_obj_clock_shop1_tbl[] = { 5 };

s16 cKF_c_obj_clock_shop1_tbl[] = { 0, 0, 1375, 0, 0, 900, 0, 0, 0, 0, 0, -1800, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s16 cKF_ds_obj_clock_shop1_tbl[] = { 1, -300, 59, 4, -283, 323, 31, 300, 0, 60, -298, -115, 61, -300, -59 };

cKF_Animation_R_c cKF_ba_r_obj_clock_shop1 = { cKF_ckcb_r_obj_clock_shop1_tbl,
                                               cKF_ds_obj_clock_shop1_tbl,
                                               cKF_kn_obj_clock_shop1_tbl,
                                               cKF_c_obj_clock_shop1_tbl,
                                               -1,
                                               61 };

cKF_Joint_R_c cKF_je_r_obj_clock_shop1_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 1375 } },
    { obj_clock_shop1_base_model, 3, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 6000, 0, 65036 } },
    { obj_clock_shop1_pend_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 7000, 0, 0 } },
    { obj_clock_shop1_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_clock_shop1_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 7000, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_clock_shop1 = { ARRAY_COUNT(cKF_je_r_obj_clock_shop1_tbl), 4,
                                              cKF_je_r_obj_clock_shop1_tbl };
