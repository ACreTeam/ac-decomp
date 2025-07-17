#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"

u16 act_ball_b_pal[] = {
#include "assets/act_ball_b_pal.inc"
};

u8 act_ball_b_1_tex[] = {
#include "assets/act_ball_b_1_tex.inc"
};

Vtx act_ball_b_v[] = {
#include "assets/act_ball_b_v.inc"
};

Gfx act_ball_b_model[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, act_ball_b_pal),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, act_ball_b_1_tex),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_ball_b_v, 26, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(1, 4, 3, 0, 1, 5, 4, 0),
    gsSP2Triangles(4, 6, 3, 0, 4, 7, 6, 0),
    gsSP2Triangles(6, 2, 3, 0, 6, 8, 2, 0),
    gsSP2Triangles(9, 10, 11, 0, 10, 12, 11, 0),
    gsSP2Triangles(10, 13, 12, 0, 10, 14, 13, 0),
    gsSP2Triangles(13, 15, 12, 0, 13, 16, 15, 0),
    gsSP2Triangles(15, 11, 12, 0, 15, 17, 11, 0),
    gsSP2Triangles(5, 1, 18, 0, 1, 19, 18, 0),
    gsSP2Triangles(1, 20, 19, 0, 1, 0, 20, 0),
    gsSP2Triangles(20, 15, 19, 0, 20, 17, 15, 0),
    gsSP2Triangles(15, 18, 19, 0, 15, 16, 18, 0),
    gsSP2Triangles(7, 4, 21, 0, 4, 22, 21, 0),
    gsSP2Triangles(4, 18, 22, 0, 4, 5, 18, 0),
    gsSP2Triangles(18, 13, 22, 0, 18, 16, 13, 0),
    gsSP2Triangles(13, 21, 22, 0, 13, 14, 21, 0),
    gsSP2Triangles(8, 6, 23, 0, 6, 24, 23, 0),
    gsSP2Triangles(6, 21, 24, 0, 6, 7, 21, 0),
    gsSP2Triangles(21, 10, 24, 0, 21, 14, 10, 0),
    gsSP2Triangles(10, 23, 24, 0, 10, 9, 23, 0),
    gsSP2Triangles(0, 2, 20, 0, 2, 25, 20, 0),
    gsSP2Triangles(2, 23, 25, 0, 2, 8, 23, 0),
    gsSP2Triangles(23, 11, 25, 0, 23, 9, 11, 0),
    gsSP2Triangles(11, 20, 25, 0, 11, 17, 20, 0),
    gsSPEndDisplayList()
};
