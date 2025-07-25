#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

u8 act_gyoei02_0_int_i4[] = {
#include "assets/act_gyoei02_0_int_i4.inc"
};

u8 act_gyoei02_1_int_i4[] = {
#include "assets/act_gyoei02_1_int_i4.inc"
};

u8 act_gyoei02_2_int_i4[] = {
#include "assets/act_gyoei02_2_int_i4.inc"
};

u8 act_gyoei02_3_int_i4[] = {
#include "assets/act_gyoei02_3_int_i4.inc"
};

Vtx act_gyoei02_00_v[] = {
#include "assets/act_gyoei02_00_v.inc"
};

Gfx act_gyoei02_00_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, COMBINED, COMBINED, 0,
                       PRIMITIVE, 0),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_gyoei02_00_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};
