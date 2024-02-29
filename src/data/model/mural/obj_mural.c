#include "libforest/gbi_extensions.h"

// clang-format off
static Vtx obj_mural_v[] = {
#include "assets/obj_mural_v.inc"
};

Gfx obj_mural_model[] = {
    gsSPTexture(65535, 65535, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),

    /* @BUG - These commands were never updated for Dolphin and therefore render broken */
#ifndef BUGFIXES
    gsDPLoadTLUT_pal16(15, 0x08000000),
    gsDPLoadTextureBlock_4b(0x09000000, G_IM_FMT_CI, 32, 32, 15, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
#else
    gsDPLoadTLUT_Dolphin(15, 16, 1, 0x08000000),
    gsDPLoadTextureBlock_4b_Dolphin(0x09000000, G_IM_FMT_CI, 32, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
#endif
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&obj_mural_v[0], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

// clang-format on
