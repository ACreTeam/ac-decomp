#include "libforest/gbi_extensions.h"

// clang-format off

static u8 obj_flower_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/flower/obj_flower_leaf_tex.inc"
};

static Vtx obj_flower_leaf_v[] = {
#include "assets/flower/obj_flower_leaf_v.inc"
};

extern Gfx obj_flower_leafT_mat_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPLoadTextureBlock_4b_Dolphin(obj_flower_tex, G_IM_FMT_CI, 128, 32, 0, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

extern Gfx obj_flower_leafT_gfx_model[] = {
    gsSPVertex(&obj_flower_leaf_v[0], 4, 0),
    gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    0, 2, 3, // tri1
    0, 0, 0 // tri2
    ),
    gsSPEndDisplayList(),
};

// clang-format on
