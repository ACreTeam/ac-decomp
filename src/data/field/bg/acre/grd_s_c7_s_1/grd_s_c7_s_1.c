#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c7_s_1_v[] = {
#include "assets/field/bg/grd_s_c7_s_1_v.inc"
};

extern Gfx grd_s_c7_s_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c7_s_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        1, 0, 3, // tri1
        3, 0, 4 // tri2
    ),
    gsSPNTriangles_5b(
        4, 0, 5, // tri0
        5, 0, 6, // tri1
        7, 6, 0, // tri2
        8, 7, 9 // tri3
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        10, 11, 12, // tri1
        9, 11, 10, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        14, 16, 15, // tri0
        14, 17, 16, // tri1
        18, 19, 4, // tri2
        19, 3, 4 // tri3
    ),
    gsSPNTriangles_5b(
        18, 20, 19, // tri0
        18, 21, 20, // tri1
        21, 22, 20, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        24, 26, 25, // tri0
        27, 25, 26, // tri1
        27, 28, 25, // tri2
        25, 29, 23 // tri3
    ),
    gsSPNTriangles_5b(
        30, 31, 23, // tri0
        31, 24, 23, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        6, 10, 7, // tri1
        11, 12, 13, // tri2
        11, 7, 12 // tri3
    ),
    gsSPNTriangles_5b(
        7, 10, 12, // tri0
        14, 15, 3, // tri1
        15, 16, 3, // tri2
        16, 17, 3 // tri3
    ),
    gsSPNTriangles_5b(
        3, 18, 4, // tri0
        3, 17, 18, // tri1
        19, 20, 21, // tri2
        20, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        23, 26, 24, // tri1
        25, 27, 19, // tri2
        25, 24, 27 // tri3
    ),
    gsSPNTriangles_5b(
        25, 28, 23, // tri0
        29, 23, 28, // tri1
        11, 13, 30, // tri2
        13, 31, 30 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_1_v[64], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        3, 7, 6, // tri0
        8, 9, 10, // tri1
        11, 12, 1, // tri2
        12, 13, 1 // tri3
    ),
    gsSPNTriangles_5b(
        0, 14, 15, // tri0
        0, 16, 14, // tri1
        17, 18, 19, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        21, 23, 22, // tri0
        24, 25, 26, // tri1
        25, 27, 26, // tri2
        25, 28, 27 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 28, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_1_v[95], 32, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        4, 8, 5, // tri1
        5, 9, 7, // tri2
        5, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 7, // tri0
        11, 12, 7, // tri1
        11, 13, 12, // tri2
        13, 14, 12 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        16, 18, 17, // tri1
        19, 20, 21, // tri2
        20, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        23, 26, 24, // tri1
        26, 27, 24, // tri2
        28, 29, 27 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 27, // tri0
        29, 10, 30, // tri1
        10, 31, 30, // tri2
        10, 5, 31 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_1_v[127], 16, 0),
    gsSPNTrianglesInit_5b(
        9, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        0, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        5, 7, 8, // tri1
        9, 10, 11, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 11, // tri0
        14, 15, 13, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_s_1_v[143], 32, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        0, 5, 4, // tri0
        5, 6, 4, // tri1
        5, 7, 8, // tri2
        9, 10, 11 // tri3
    ),
    gsSPNTriangles_5b(
        9, 12, 10, // tri0
        12, 13, 10, // tri1
        14, 15, 16, // tri2
        14, 17, 15 // tri3
    ),
    gsSPNTriangles_5b(
        14, 18, 17, // tri0
        14, 19, 18, // tri1
        19, 20, 18, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        20, 19, 21, // tri0
        21, 23, 22, // tri1
        24, 25, 26, // tri2
        25, 27, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 26, // tri0
        27, 29, 28, // tri1
        25, 30, 27, // tri2
        30, 31, 27 // tri3
    ),
    gsSPNTriangles_5b(
        31, 29, 27, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_1_v[175], 32, 0),
    gsSPNTrianglesInit_5b(
        31, // tri count
        0, 1, 2, // tri0
        3, 4, 0, // tri1
        4, 5, 0 // tri2
    ),
    gsSPNTriangles_5b(
        5, 1, 0, // tri0
        5, 6, 1, // tri1
        4, 7, 5, // tri2
        7, 8, 5 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        9, 10, 8, // tri1
        9, 11, 10, // tri2
        11, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 10, // tri0
        12, 14, 13, // tri1
        14, 15, 13, // tri2
        14, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 19, // tri0
        17, 20, 18, // tri1
        20, 21, 18, // tri2
        20, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        23, 26, 24, // tri1
        26, 27, 24, // tri2
        27, 28, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 20, 17, // tri0
        25, 24, 20, // tri1
        24, 22, 20, // tri2
        24, 28, 22 // tri3
    ),
    gsSPNTriangles_5b(
        29, 13, 15, // tri0
        29, 15, 30, // tri1
        30, 15, 31, // tri2
        15, 16, 31 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_1_v[207], 32, 0),
    gsSPNTrianglesInit_5b(
        27, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 3, 6, // tri0
        8, 9, 10, // tri1
        8, 10, 11, // tri2
        11, 10, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        14, 15, 16, // tri1
        14, 16, 17, // tri2
        13, 12, 15 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 14, // tri0
        17, 16, 18, // tri1
        17, 18, 19, // tri2
        18, 16, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 18, 20, // tri0
        16, 15, 20, // tri1
        15, 22, 20, // tri2
        15, 12, 22 // tri3
    ),
    gsSPNTriangles_5b(
        12, 23, 22, // tri0
        12, 24, 23, // tri1
        12, 10, 24, // tri2
        10, 9, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        25, 28, 26, // tri1
        29, 27, 30, // tri2
        29, 25, 27 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_1_v[238], 23, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 0 // tri2
    ),
    gsSPNTriangles_5b(
        2, 6, 7, // tri0
        4, 0, 2, // tri1
        7, 4, 2, // tri2
        8, 9, 10 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 10, // tri0
        12, 8, 13, // tri1
        8, 10, 13, // tri2
        14, 13, 15 // tri3
    ),
    gsSPNTriangles_5b(
        14, 12, 13, // tri0
        16, 14, 17, // tri1
        14, 15, 17, // tri2
        18, 16, 19 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 19, // tri0
        19, 20, 21, // tri1
        18, 19, 21, // tri2
        22, 18, 21 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_s_1_v[261], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        0, 3, 4, // tri1
        5, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        6, 5, 3, // tri0
        7, 8, 6, // tri1
        9, 10, 7, // tri2
        11, 12, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        11, 14, 13, // tri1
        14, 15, 16, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 17, // tri0
        22, 23, 20, // tri1
        24, 25, 22, // tri2
        23, 21, 20 // tri3
    ),
    gsSPNTriangles_5b(
        24, 26, 27, // tri0
        26, 28, 29, // tri1
        30, 29, 28, // tri2
        28, 31, 30 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_1_v[293], 17, 0),
    gsSPNTrianglesInit_5b(
        8, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 8, 7, // tri0
        8, 9, 10, // tri1
        10, 11, 12, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
