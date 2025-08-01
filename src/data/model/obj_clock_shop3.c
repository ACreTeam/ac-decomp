#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx obj_clock_shop3_v[];
u16 obj_clock_shop3_pal[] = {
#include "assets/obj_clock_shop3_pal.inc"
};

u8 obj_clock_shop3_hari_tex_txt[] = {
#include "assets/obj_clock_shop3_hari_tex_txt.inc"
};

u8 obj_clock_shop3_body_tex_txt[] = {
#include "assets/obj_clock_shop3_body_tex_txt.inc"
};

u8 obj_clock_shop3_side_tex_txt[] = {
#include "assets/obj_clock_shop3_side_tex_txt.inc"
};

Vtx obj_clock_shop3_v[] = {
#include "assets/obj_clock_shop3_v.inc"
};

Gfx obj_clock_shop3_body_model[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, obj_clock_shop3_pal),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, obj_clock_shop3_body_tex_txt),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 127, 2048),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_clock_shop3_v[3], 16, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
    gsSP2Triangles(8, 9, 10, 0, 9, 11, 10, 0),
    gsSP2Triangles(12, 5, 9, 0, 5, 4, 9, 0),
    gsSP2Triangles(10, 13, 8, 0, 13, 6, 8, 0),
    gsSP2Triangles(4, 11, 9, 0, 4, 14, 11, 0),
    gsSP2Triangles(13, 14, 6, 0, 14, 4, 6, 0),
    gsSP2Triangles(8, 15, 9, 0, 15, 12, 9, 0),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, obj_clock_shop3_pal),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, obj_clock_shop3_side_tex_txt),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
    gsSPVertex(&obj_clock_shop3_v[19], 20, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
    gsSP2Triangles(9, 12, 10, 0, 13, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 6, 8, 19, 0),
    gsSPEndDisplayList(),
};

Gfx obj_clock_shop3_long_model[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, obj_clock_shop3_pal),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, obj_clock_shop3_hari_tex_txt),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_clock_shop3_v, 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

Gfx obj_clock_shop3_short_model[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, obj_clock_shop3_pal),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, obj_clock_shop3_hari_tex_txt),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_clock_shop3_v[39], 3, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

u8 cKF_ckcb_r_obj_clock_shop3_tbl[] = { 0, 0, 0, 0, 0 };

s16 cKF_c_obj_clock_shop3_tbl[] = { 0, 9800, 0, 0, 0, 0, 0, 0, 900, 0, 0, -900, 0, 0, 900, 0, 0, 0 };

cKF_Animation_R_c cKF_ba_r_obj_clock_shop3 = { cKF_ckcb_r_obj_clock_shop3_tbl, NULL, NULL,
                                               cKF_c_obj_clock_shop3_tbl,      -1,   100 };

cKF_Joint_R_c cKF_je_r_obj_clock_shop3_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 0, 9800, 0 } },
    { obj_clock_shop3_body_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 400, 0, 0 } },
    { obj_clock_shop3_short_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { obj_clock_shop3_long_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 400, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_obj_clock_shop3 = { ARRAY_COUNT(cKF_je_r_obj_clock_shop3_tbl), 3,
                                              cKF_je_r_obj_clock_shop3_tbl };
