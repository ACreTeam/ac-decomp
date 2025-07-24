#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

static u16 obj_item_tane_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_item_tane/obj_item_tane_pal.inc"
};

static u8 obj_item_tane_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_item_tane/obj_item_tane_tex.inc"
};

static Vtx obj_item_tane_v[] = {
#include "assets/obj_item_tane/obj_item_tane_v.inc"
};

Gfx obj_taneT_mat_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_item_tane_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_item_tane_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_taneT_gfx_model[] = {
    gsSPVertex(obj_item_tane_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
