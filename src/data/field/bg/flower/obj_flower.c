#include "libforest/gbi_extensions.h"

// clang-format off

static u8 obj_flower_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/flower/obj_flower_tex.inc"
};

static Vtx obj_flower_a_v[] = {
#include "assets/flower/obj_flower_a_v.inc"
};

static Vtx obj_flower_b_v[] = {
#include "assets/flower/obj_flower_b_v.inc"
};

static Vtx obj_flower_c_v[] = {
#include "assets/flower/obj_flower_c_v.inc"
};

extern Gfx obj_flower_aT_mat_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPLoadTextureBlock_4b_Dolphin(obj_flower_tex, G_IM_FMT_CI, 128, 32, 0, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

extern Gfx obj_flower_bT_mat_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPLoadTextureBlock_4b_Dolphin(obj_flower_tex, G_IM_FMT_CI, 128, 32, 1, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

extern Gfx obj_flower_cT_mat_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPLoadTextureBlock_4b_Dolphin(obj_flower_tex, G_IM_FMT_CI, 128, 32, 2, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

extern Gfx obj_flower_aT_gfx_model[] = {
    gsSPVertex(&obj_flower_a_v[0], 8, 0),
    gsSPNTrianglesInit_5b(
        4,       // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 5, 6  // tri2
    ),
    gsSPNTriangles_5b(
        4, 6, 7, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0  // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx obj_flower_bT_gfx_model[] = {
    gsSPVertex(&obj_flower_b_v[0], 8, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 6, 7, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx obj_flower_cT_gfx_model[] = {
    gsSPVertex(&obj_flower_c_v[0], 8, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 6, 7, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

// clang-format on
