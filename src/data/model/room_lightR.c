#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 light_window[] = {
#include "assets/light_window.inc"
};

Vtx room_lightR_v[] = {
#include "assets/room_lightR_v.inc"
};

Vtx room_lightL_v[] = {
#include "assets/room_lightL_v.inc"
};

Gfx light_shine01_mode[] = {
    gsDPPipeSync(),
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, SHADE, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, SHADE, 0, PRIMITIVE, 0),
    gsSPEndDisplayList(),
};

Gfx light_shineL01_vtx[] = {
    gsSPVertex(room_lightL_v, 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 3, 2, 0, 4, 2, 5, 0),
    gsSPEndDisplayList(),
};

Gfx light_shineR01_vtx[] = {
    gsSPVertex(room_lightR_v, 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 1, 0, 0, 4, 0, 5, 0),
    gsSPEndDisplayList(),
};

Gfx light_floor01_mode[] = {
    gsDPPipeSync(),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK),
    gsDPSetOtherMode(G_AD_PATTERN | G_CD_BAYER | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_ZB_CLD_SURF | G_RM_ZB_CLD_SURF2),
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0),
    gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, light_window),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 63, 2048),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, G_TX_RENDERTILE, 15, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 60, 60),
    gsSPEndDisplayList(),
};

Gfx light_floorL01_vtx[] = {
    gsSPVertex(&room_lightL_v[6], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx light_floorR01_vtx[] = {
    gsSPVertex(&room_lightR_v[6], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
