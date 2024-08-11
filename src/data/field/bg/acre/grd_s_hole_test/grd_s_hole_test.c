#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 stone_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_hole_test_v[] = {
#include "assets/field/bg/grd_s_hole_test_v.inc"
};

extern Gfx grd_s_hole_test_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_hole_test_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_hole_test_v[230], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 7, 4, // tri0
        9, 10, 6, // tri1
        11, 12, 10, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_hole_test_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 5, // tri0
        6, 8, 7, // tri1
        8, 9, 7, // tri2
        10, 11, 4 // tri3
    ),
    gsSPNTriangles_5b(
        3, 10, 4, // tri0
        10, 12, 11, // tri1
        12, 13, 11, // tri2
        12, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        16, 14, 17, // tri1
        16, 18, 14, // tri2
        18, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 13, // tri0
        20, 21, 15, // tri1
        22, 23, 24, // tri2
        25, 24, 20 // tri3
    ),
    gsSPNTriangles_5b(
        23, 21, 20, // tri0
        24, 23, 20, // tri1
        26, 27, 19, // tri2
        27, 26, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 27, 28, // tri0
        30, 31, 29, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_hole_test_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 2, 3, // tri0
        6, 0, 2, // tri1
        6, 7, 0, // tri2
        8, 7, 6 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 7, // tri0
        10, 9, 8, // tri1
        11, 12, 13, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        13, 12, 14, // tri0
        12, 16, 14, // tri1
        14, 17, 18, // tri2
        16, 17, 14 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 18, // tri0
        20, 21, 19, // tri1
        22, 23, 20, // tri2
        24, 23, 22 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 23, // tri0
        26, 27, 28, // tri1
        26, 29, 25, // tri2
        26, 25, 27 // tri3
    ),
    gsSPNTriangles_5b(
        25, 24, 27, // tri0
        29, 30, 25, // tri1
        29, 31, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_hole_test_v[64], 5, 0),
    gsSPNTrianglesInit_5b(
        3, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_hole_test_v[69], 32, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        9, 10, 6, // tri0
        9, 11, 10, // tri1
        6, 10, 7, // tri2
        8, 7, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 11, // tri0
        15, 5, 14, // tri1
        3, 5, 15, // tri2
        15, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        19, 20, 16, // tri1
        19, 21, 20, // tri2
        16, 22, 17 // tri3
    ),
    gsSPNTriangles_5b(
        16, 20, 22, // tri0
        18, 17, 4, // tri1
        23, 24, 21, // tri2
        25, 26, 24 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 26, // tri0
        27, 26, 25, // tri1
        25, 24, 23, // tri2
        29, 30, 31 // tri3
    ),
    gsSPVertex(&grd_s_hole_test_v[101], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 5, 1 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 11, 8, // tri1
        12, 9, 13, // tri2
        14, 13, 4 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        18, 19, 16, // tri1
        20, 21, 22, // tri2
        23, 22, 19 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 26, // tri0
        27, 17, 25, // tri1
        28, 26, 29, // tri2
        30, 29, 31 // tri3
    ),
    gsSPVertex(&grd_s_hole_test_v[133], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        3, 4, 0, // tri1
        3, 5, 4 // tri2
    ),
    gsSPNTriangles_5b(
        0, 6, 1, // tri0
        0, 4, 6, // tri1
        2, 1, 7, // tri2
        8, 9, 10 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 9, // tri0
        13, 7, 12, // tri1
        13, 12, 11, // tri2
        11, 9, 8 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        17, 18, 14, // tri1
        17, 10, 18, // tri2
        14, 18, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 15, 19, // tri0
        20, 21, 22, // tri1
        23, 19, 21, // tri2
        23, 21, 20 // tri3
    ),
    gsSPNTriangles_5b(
        20, 22, 24, // tri0
        25, 26, 27, // tri1
        28, 29, 26, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_hole_test_v[163], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        3, 2, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 6, // tri0
        10, 7, 11, // tri1
        12, 11, 13, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 14, // tri0
        17, 19, 18, // tri1
        14, 18, 15, // tri2
        16, 15, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 23, // tri0
        24, 25, 22, // tri1
        26, 20, 25, // tri2
        26, 25, 24 // tri3
    ),
    gsSPNTriangles_5b(
        24, 22, 21, // tri0
        27, 28, 29, // tri1
        30, 31, 27, // tri2
        30, 23, 31 // tri3
    ),
    gsSPNTriangles_5b(
        27, 31, 28, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_hole_test_v[195], 9, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 4 // tri2
    ),
    gsSPNTriangles_5b(
        8, 2, 7, // tri0
        8, 7, 6, // tri1
        6, 4, 3, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_hole_test_v[204], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 7, 4, // tri0
        9, 10, 11, // tri1
        12, 2, 10, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_hole_test_v[217], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 2, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 4, 6, // tri0
        9, 7, 10, // tri1
        11, 10, 12, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
