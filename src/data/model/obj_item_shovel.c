#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u16 obj_item_shovel_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_item_shovel_pal.inc"
};

u8 obj_item_shovel_tex[] = {
#include "assets/obj_item_shovel_tex.inc"
};

Vtx obj_item_shovel_v[] = {
#include "assets/obj_item_shovel_v.inc"
};

Gfx obj_item_shovelT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_item_shovel_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_item_shovel_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPEndDisplayList(),
};

Gfx obj_item_shovelT_gfx_model[] = {
    gsSPVertex(obj_item_shovel_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
