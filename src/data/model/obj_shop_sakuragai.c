#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u16 obj_shop_sakuragai_pal[] ATTRIBUTE_ALIGN(32)= {
#include "assets/obj_shop_sakuragai_pal.inc"
};

u8 obj_shop_sakuragai_tex[] ATTRIBUTE_ALIGN(32)= {
#include "assets/obj_shop_sakuragai_tex.inc"
};

Vtx obj_shop_sakuragai_v[] = {
#include "assets/obj_shop_sakuragai_v.inc"
};

Gfx obj_sakuragaiT_mat_model[] = {
gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_sakuragai_pal),
gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_sakuragai_tex),
gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
gsSPEndDisplayList(),
};

Gfx obj_sakuragaiT_gfx_model[] = {
gsSPVertex(obj_shop_sakuragai_v, 6, 0),
gsSPNTrianglesInit_5b(5, 0, 1, 2, 1, 3, 2, 3, 4, 2),
gsSPNTriangles_5b(4, 5, 2, 5, 0, 2, 0, 0, 0, 0, 0, 0),
gsSPEndDisplayList(),
};

