#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"


u16 act_ball_b_pal[] ATTRIBUTE_ALIGN(32)= { 
#include "assets/act_ball_b_pal.inc"
};

u8 act_ball_b_1_tex[] ATTRIBUTE_ALIGN(32)= { 
#include "assets/act_ball_b_1_tex.inc"
};

Vtx act_ball_b_v[] = { 
#include "assets/act_ball_b_v.inc"
};

Gfx act_ball_b_model[] = { 
/* d7000002 ffffffff */ gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
/* e7000000 00000000 */ gsDPPipeSync(),
/* e200001c c8113078 */ gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
/* fc127e60 fffff3f8 */ gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
/* e3001001 00008000 */ gsDPSetTextureLUT(G_TT_RGBA16),
/* fd100000 00000000 */ gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, act_ball_b_pal),
/* e8000000 00000000 */ gsDPTileSync(),
/* f50001f0 07000000 */ gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
/* e6000000 00000000 */ gsDPLoadSync(),
/* f0000000 0703c000 */ gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
/* e7000000 00000000 */ gsDPPipeSync(),
/* fd500000 00000000 */ gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, act_ball_b_1_tex),
/* f5500000 07050140 */ gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
/* e6000000 00000000 */ gsDPLoadSync(),
/* f3000000 0703f800 */ gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
/* e7000000 00000000 */ gsDPPipeSync(),
/* f5400200 00f50140 */ gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
/* f2000000 0003c03c */ gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
/* fa000080 ffffffff */ gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
/* d9000000 00230405 */ gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
/* 0101a034 00000000 */ gsSPVertex(act_ball_b_v, 26, 0),
/* 06000204 00020604 */ gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
/* 06020806 00020a08 */ gsSP2Triangles(1, 4, 3, 0, 1, 5, 4, 0),
/* 06080c06 00080e0c */ gsSP2Triangles(4, 6, 3, 0, 4, 7, 6, 0),
/* 060c0406 000c1004 */ gsSP2Triangles(6, 2, 3, 0, 6, 8, 2, 0),
/* 06121416 00141816 */ gsSP2Triangles(9, 10, 11, 0, 10, 12, 11, 0),
/* 06141a18 00141c1a */ gsSP2Triangles(10, 13, 12, 0, 10, 14, 13, 0),
/* 061a1e18 001a201e */ gsSP2Triangles(13, 15, 12, 0, 13, 16, 15, 0),
/* 061e1618 001e2216 */ gsSP2Triangles(15, 11, 12, 0, 15, 17, 11, 0),
/* 060a0224 00022624 */ gsSP2Triangles(5, 1, 18, 0, 1, 19, 18, 0),
/* 06022826 00020028 */ gsSP2Triangles(1, 20, 19, 0, 1, 0, 20, 0),
/* 06281e26 0028221e */ gsSP2Triangles(20, 15, 19, 0, 20, 17, 15, 0),
/* 061e2426 001e2024 */ gsSP2Triangles(15, 18, 19, 0, 15, 16, 18, 0),
/* 060e082a 00082c2a */ gsSP2Triangles(7, 4, 21, 0, 4, 22, 21, 0),
/* 0608242c 00080a24 */ gsSP2Triangles(4, 18, 22, 0, 4, 5, 18, 0),
/* 06241a2c 0024201a */ gsSP2Triangles(18, 13, 22, 0, 18, 16, 13, 0),
/* 061a2a2c 001a1c2a */ gsSP2Triangles(13, 21, 22, 0, 13, 14, 21, 0),
/* 06100c2e 000c302e */ gsSP2Triangles(8, 6, 23, 0, 6, 24, 23, 0),
/* 060c2a30 000c0e2a */ gsSP2Triangles(6, 21, 24, 0, 6, 7, 21, 0),
/* 062a1430 002a1c14 */ gsSP2Triangles(21, 10, 24, 0, 21, 14, 10, 0),
/* 06142e30 0014122e */ gsSP2Triangles(10, 23, 24, 0, 10, 9, 23, 0),
/* 06000428 00043228 */ gsSP2Triangles(0, 2, 20, 0, 2, 25, 20, 0),
/* 06042e32 0004102e */ gsSP2Triangles(2, 23, 25, 0, 2, 8, 23, 0),
/* 062e1632 002e1216 */ gsSP2Triangles(23, 11, 25, 0, 23, 9, 11, 0),
/* 06162832 00162228 */ gsSP2Triangles(11, 20, 25, 0, 11, 17, 20, 0),
/* df000000 00000000 */ gsSPEndDisplayList()
};

