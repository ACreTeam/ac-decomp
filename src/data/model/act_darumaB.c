#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

static u16 act_daruma_pal[] = {
#include "assets/act_darumaB/act_daruma_pal.inc"
};

u8 act_darumaB_tex[] = {
#include "assets/act_darumaB_tex.inc"
};

Vtx act_darumaB_v[] = {
#include "assets/act_darumaB_v.inc"
};

Gfx act_darumaB_model[] = {
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
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, act_darumaB_tex),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(act_darumaB_v, 30, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP2Triangles(2, 4, 3, 0, 4, 5, 3, 0),
    gsSP2Triangles(5, 6, 3, 0, 5, 7, 6, 0),
    gsSP2Triangles(7, 8, 6, 0, 9, 10, 11, 0),
    gsSP2Triangles(12, 9, 11, 0, 12, 11, 13, 0),
    gsSP2Triangles(12, 13, 1, 0, 0, 12, 1, 0),
    gsSP2Triangles(3, 14, 0, 0, 6, 15, 3, 0),
    gsSP2Triangles(8, 16, 6, 0, 0, 17, 12, 0),
    gsSP2Triangles(12, 18, 9, 0, 19, 20, 21, 0),
    gsSP2Triangles(21, 22, 23, 0, 24, 25, 26, 0),
    gsSP2Triangles(27, 28, 24, 0, 23, 29, 27, 0),
    gsSP2Triangles(1, 21, 23, 0, 1, 13, 21, 0),
    gsSP2Triangles(13, 11, 21, 0, 11, 19, 21, 0),
    gsSP2Triangles(11, 10, 19, 0, 24, 26, 7, 0),
    gsSP2Triangles(24, 7, 5, 0, 27, 24, 5, 0),
    gsSP2Triangles(27, 5, 4, 0, 27, 4, 2, 0),
    gsSP2Triangles(23, 27, 2, 0, 2, 1, 23, 0),
    gsSPEndDisplayList(),
};
