#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

u8 logo_nin_copy1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/logo_nin_copy1.inc"
};

u8 logo_nin_copy2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/logo_nin_copy2.inc"
};

Vtx logo_nin_copy_v[] = {
#include "assets/logo_nin_copy_v.inc"
};

Gfx logo_nin_copyT_model[] = {
    gsDPSetCombineMode(G_CC_BLENDPEDECALA, G_CC_BLENDPEDECALA),
    gsDPSetEnvColor(0x00, 0x00, 0x00, 0xFF),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 128, 16, logo_nin_copy2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(logo_nin_copy_v, 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 16, logo_nin_copy1),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 4, 6, 7, 0, 0, 0),
    gsSPEndDisplayList(),
};
