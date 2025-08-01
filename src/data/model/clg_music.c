#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u16 clg_music_pal[] = {
#include "assets/clg_music_pal.inc"
};

u8 clg_music_tex[] = {
#include "assets/clg_music_tex.inc"
};

Vtx clg_music_v[] = {
#include "assets/clg_music_v.inc"
};

Gfx mCL_music_model[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, clg_music_pal),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 496, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadTLUTCmd(G_TX_LOADTILE, 15),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, clg_music_tex),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(clg_music_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
