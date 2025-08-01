#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx act_m_okuwa_b_v[];
u8 act_m_okuwa_txt[] = {
#include "assets/act_m_okuwa_txt.inc"
};

Vtx act_m_okuwa_b_v[] = {
#include "assets/act_m_okuwa_b_v.inc"
};

Gfx act_m_okuwa_b_left_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(act_m_okuwa_b_v, 2, 0),
    gsSPMatrix(&anime_6_mdl[2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, act_m_okuwa_txt),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&act_m_okuwa_b_v[2], 3, 2),
    gsSP2Triangles(2, 0, 1, 0, 3, 4, 0, 0),
    gsSPEndDisplayList(),
};

Gfx act_m_okuwa_b_right_model[] = {
    gsSPMatrix(anime_6_mdl, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&act_m_okuwa_b_v[5], 2, 0),
    gsSPMatrix(&anime_6_mdl[1], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW),
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, act_m_okuwa_txt),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&act_m_okuwa_b_v[7], 3, 2),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 4, 0),
    gsSPEndDisplayList(),
};

Gfx act_m_okuwa_b_base_model[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, act_m_okuwa_txt),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 6, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&act_m_okuwa_b_v[10], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(3, 4, 1, 0, 2, 5, 0, 0),
    gsSP2Triangles(5, 6, 0, 0, 5, 7, 6, 0),
    gsSPEndDisplayList(),
};

cKF_Joint_R_c cKF_je_r_act_m_okuwa_b_tbl[] = {
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 300, 0, 64536 } },
    { act_m_okuwa_b_base_model, 2, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { NULL, 1, cKF_JOINT_FLAG_DISP_OPA, { 1500, 64936, 0 } },
    { act_m_okuwa_b_right_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 0, 0, 0 } },
    { act_m_okuwa_b_left_model, 0, cKF_JOINT_FLAG_DISP_OPA, { 1500, 0, 0 } }
};

cKF_Skeleton_R_c cKF_bs_r_act_m_okuwa_b = { ARRAY_COUNT(cKF_je_r_act_m_okuwa_b_tbl), 3, cKF_je_r_act_m_okuwa_b_tbl };
