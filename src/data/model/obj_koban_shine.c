#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 obj_koban_shine_1[]  = {
#include "assets/obj_koban_shine_1.inc"
};

u8 obj_koban_shine_2[] = {
#include "assets/obj_koban_shine_2.inc"
};

Vtx obj_koban_shine_v[] = {
#include "assets/obj_koban_shine_v.inc"
};

Gfx obj_koban_shine_modelT[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, obj_koban_shine_1),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, 4, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_CLAMP, 4, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_koban_shine_v, 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 4, 0),
    gsSP2Triangles(0, 2, 3, 0, 4, 3, 5, 0),
    gsSP2Triangles(4, 5, 6, 0, 6, 5, 7, 0),
    gsSP2Triangles(5, 1, 7, 0, 7, 1, 0, 0),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, obj_koban_shine_2),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 255, 1024),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 2, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsSPVertex(&obj_koban_shine_v[8], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
