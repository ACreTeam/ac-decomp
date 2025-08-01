#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

static u16 act_daruma_pal[] = {
#include "assets/act_darumaA/act_daruma_pal.inc"
};

u8 act_darumaA_tex[] = {
#include "assets/act_darumaA_tex.inc"
};

Vtx act_darumaA_v[] = {
#include "assets/act_darumaA_v.inc"
};

Gfx act_darumaA_model[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, act_daruma_pal),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, act_darumaA_tex),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(act_darumaA_v, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(3, 4, 0, 0, 4, 5, 0, 0),
    gsSP2Triangles(2, 6, 7, 0, 2, 7, 3, 0),
    gsSP2Triangles(3, 8, 4, 0, 7, 9, 3, 0),
    gsSP2Triangles(1, 10, 11, 0, 12, 13, 1, 0),
    gsSP2Triangles(1, 11, 2, 0, 11, 6, 2, 0),
    gsSP2Triangles(0, 5, 12, 0, 0, 12, 1, 0),
    gsSP2Triangles(14, 15, 16, 0, 15, 17, 16, 0),
    gsSP2Triangles(5, 17, 12, 0, 17, 15, 12, 0),
    gsSP2Triangles(14, 18, 15, 0, 15, 19, 12, 0),
    gsSP2Triangles(4, 20, 21, 0, 21, 22, 23, 0),
    gsSP2Triangles(4, 21, 17, 0, 4, 17, 5, 0),
    gsSP2Triangles(16, 17, 21, 0, 16, 21, 23, 0),
    gsSP2Triangles(24, 25, 26, 0, 27, 25, 24, 0),
    gsSP2Triangles(6, 25, 7, 0, 25, 27, 7, 0),
    gsSP2Triangles(27, 28, 7, 0, 11, 29, 26, 0),
    gsSP2Triangles(11, 26, 25, 0, 11, 25, 6, 0),
    gsSPVertex(&act_darumaA_v[30], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};
