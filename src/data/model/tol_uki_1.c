#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

static u16 tol_sao_1_pal[] = {
#include "assets/tol_uki_1/tol_sao_1_pal.inc"
};

static u8 tol_sao_1_uki1_tex_txt[] = {
#include "assets/tol_uki_1/tol_sao_1_uki1_tex_txt.inc"
};

static Vtx tol_uki_1_v[] = {
#include "assets/tol_uki_1/tol_uki_1_v.inc"
};

Gfx inv_uki_model[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, tol_sao_1_pal),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, tol_sao_1_uki1_tex_txt),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 127, 2048),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(tol_uki_1_v, 24, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(4, 0, 2, 0, 6, 7, 8, 0),
    gsSP2Triangles(7, 6, 9, 0, 7, 9, 10, 0),
    gsSP2Triangles(10, 9, 11, 0, 12, 6, 8, 0),
    gsSP2Triangles(6, 12, 13, 0, 6, 13, 9, 0),
    gsSP2Triangles(9, 13, 11, 0, 14, 12, 8, 0),
    gsSP2Triangles(12, 14, 15, 0, 12, 15, 13, 0),
    gsSP2Triangles(13, 15, 11, 0, 16, 14, 8, 0),
    gsSP2Triangles(14, 16, 17, 0, 14, 17, 15, 0),
    gsSP2Triangles(15, 17, 11, 0, 18, 16, 19, 0),
    gsSP2Triangles(16, 18, 20, 0, 16, 20, 17, 0),
    gsSP2Triangles(17, 20, 21, 0, 22, 18, 19, 0),
    gsSP2Triangles(18, 22, 23, 0, 18, 23, 20, 0),
    gsSP1Triangle(20, 23, 21, 0),
    gsSPEndDisplayList(),
};
