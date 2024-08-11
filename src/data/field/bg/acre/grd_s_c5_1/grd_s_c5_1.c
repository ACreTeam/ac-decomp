#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c5_1_v[] = {
#include "assets/field/bg/grd_s_c5_1_v.inc"
};

extern Gfx grd_s_c5_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c5_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c5_1_v[163], 12, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 0, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 3, 7, // tri0
        8, 6, 9, // tri1
        10, 8, 11, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c5_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        0, 8, 1, // tri1
        9, 10, 11, // tri2
        9, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 10, // tri0
        9, 14, 12, // tri1
        15, 14, 9, // tri2
        10, 16, 11 // tri3
    ),
    gsSPNTriangles_5b(
        17, 2, 18, // tri0
        19, 4, 20, // tri1
        4, 6, 20, // tri2
        21, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        23, 22, 24, // tri0
        14, 25, 12, // tri1
        26, 27, 28, // tri2
        27, 29, 28 // tri3
    ),
    gsSPNTriangles_5b(
        4, 30, 5, // tri0
        5, 31, 7, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        0, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 9, 10, // tri1
        9, 8, 11, // tri2
        12, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 12, 3, // tri0
        12, 13, 3, // tri1
        3, 14, 1, // tri2
        3, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 1, // tri0
        16, 17, 18, // tri1
        19, 20, 21, // tri2
        20, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 20, 6, // tri0
        7, 6, 20, // tri1
        23, 24, 25, // tri2
        26, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        26, 29, 27, // tri0
        30, 31, 23, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c5_1_v[64], 32, 0),
    gsSPNTrianglesInit_5b(
        30, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        7, 8, 5, // tri1
        9, 10, 11, // tri2
        9, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        13, 16, 14, // tri1
        17, 18, 1, // tri2
        17, 1, 0 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 1, // tri0
        18, 20, 19, // tri1
        21, 1, 19, // tri2
        21, 2, 1 // tri3
    ),
    gsSPNTriangles_5b(
        2, 22, 23, // tri0
        2, 23, 3, // tri1
        21, 22, 2, // tri2
        21, 24, 22 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 23, // tri0
        25, 23, 22, // tri1
        24, 25, 22, // tri2
        24, 27, 25 // tri3
    ),
    gsSPNTriangles_5b(
        25, 27, 4, // tri0
        26, 25, 28, // tri1
        25, 4, 28, // tri2
        4, 6, 28 // tri3
    ),
    gsSPNTriangles_5b(
        27, 29, 4, // tri0
        29, 30, 7, // tri1
        29, 7, 4, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_1_v[95], 9, 0),
    gsSPNTrianglesInit_5b(
        8, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 5, 0 // tri2
    ),
    gsSPNTriangles_5b(
        5, 1, 0, // tri0
        1, 6, 7, // tri1
        1, 7, 2, // tri2
        5, 8, 1 // tri3
    ),
    gsSPNTriangles_5b(
        8, 6, 1, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c5_1_v[104], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 11, 12, // tri1
        10, 13, 11, // tri2
        14, 15, 13 // tri3
    ),
    gsSPNTriangles_5b(
        16, 10, 12, // tri0
        17, 18, 19, // tri1
        20, 3, 21, // tri2
        18, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        18, 21, 19, // tri0
        17, 19, 22, // tri1
        7, 16, 8, // tri2
        10, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 15, // tri0
        25, 22, 24, // tri1
        26, 27, 5, // tri2
        28, 29, 27 // tri3
    ),
    gsSPVertex(&grd_s_c5_1_v[134], 17, 0),
    gsSPNTrianglesInit_5b(
        9, // tri count
        0, 1, 2, // tri0
        3, 2, 4, // tri1
        4, 5, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 4, 6, // tri0
        7, 6, 8, // tri1
        9, 10, 11, // tri2
        12, 13, 8 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 12, // tri0
        14, 15, 16, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c5_1_v[151], 12, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        1, 9, 10, // tri1
        9, 3, 11, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
