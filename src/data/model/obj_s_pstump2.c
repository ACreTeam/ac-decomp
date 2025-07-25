#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

static u8 obj_s_palm_young_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_s_pstump2/obj_s_palm_young_tex.inc"
};

Vtx obj_s_pstump2_v[] = {
#include "assets/obj_s_pstump2_v.inc"
};

Gfx obj_s_pstump2T_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, obj_s_palm_young_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 7, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_s_pstump2T_gfx_model[] = {
    gsSPVertex(obj_s_pstump2_v, 7, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 2, 0, 6, 1, 6, 4, 1, 0, 0, 0),
    gsSPEndDisplayList(),
};
