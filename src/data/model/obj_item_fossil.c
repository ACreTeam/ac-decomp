#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

static u16 obj_item_fossil_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/obj_item_fossil/obj_item_fossil_pal.inc"
};

u8 obj_shop_fossil_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/obj_shop_fossil_tex.inc"
};

static Vtx obj_item_fossil_v[] = {
#include "assets/obj_item_fossil/obj_item_fossil_v.inc"
};

Gfx obj_shop_fossil_mat_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_item_fossil_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_fossil_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_shop_fossil_gfx_model[] = {
gsSPVertex(obj_item_fossil_v, 25, 0),
gsSPNTrianglesInit_5b(21, 0, 1, 2, 0, 3, 1, 3, 4, 1),
gsSPNTriangles_5b(4, 5, 1, 5, 6, 1, 6, 7, 1, 7, 2, 1),
gsSPNTriangles_5b(8, 9, 0, 8, 0, 10, 3, 11, 12, 3, 12, 4),
gsSPNTriangles_5b(13, 5, 14, 13, 14, 15, 16, 17, 7, 16, 7, 18),
gsSPNTriangles_5b(19, 13, 15, 19, 15, 20, 4, 12, 21, 4, 21, 22),
gsSPNTriangles_5b(23, 24, 11, 23, 11, 3, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

