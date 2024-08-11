#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c5_s_1_v[] = {
#include "assets/field/bg/grd_s_c5_s_1_v.inc"
};

extern Gfx grd_s_c5_s_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c5_s_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c5_s_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        35, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        0, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        0, 5, 4, // tri0
        2, 6, 0, // tri1
        6, 7, 0, // tri2
        1, 8, 2 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 2, // tri0
        9, 10, 2, // tri1
        10, 6, 2, // tri2
        8, 11, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 9, // tri0
        12, 13, 9, // tri1
        13, 10, 9, // tri2
        11, 14, 12 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 12, // tri0
        15, 16, 12, // tri1
        16, 13, 12, // tri2
        15, 17, 16 // tri3
    ),
    gsSPNTriangles_5b(
        14, 18, 15, // tri0
        18, 19, 15, // tri1
        19, 17, 15, // tri2
        19, 20, 17 // tri3
    ),
    gsSPNTriangles_5b(
        21, 19, 18, // tri0
        21, 22, 19, // tri1
        22, 20, 19, // tri2
        4, 5, 23 // tri3
    ),
    gsSPNTriangles_5b(
        4, 23, 24, // tri0
        0, 7, 5, // tri1
        7, 25, 5, // tri2
        5, 25, 23 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 23, // tri0
        27, 28, 29, // tri1
        27, 30, 28, // tri2
        27, 31, 30 // tri3
    ),
    gsSPVertex(&grd_s_c5_s_1_v[32], 23, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 2, // tri0
        3, 6, 1, // tri1
        3, 7, 6, // tri2
        7, 8, 6 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        9, 10, 8, // tri1
        10, 11, 8, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 8, // tri0
        11, 14, 13, // tri1
        12, 15, 11, // tri2
        12, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        15, 14, 11, // tri0
        15, 17, 14, // tri1
        15, 18, 17, // tri2
        18, 19, 17 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 18, // tri0
        20, 0, 21, // tri1
        0, 2, 21, // tri2
        2, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        2, 5, 22, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c5_s_1_v[55], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        7, 8, 6, // tri1
        9, 10, 11, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        14, 16, 15, // tri1
        16, 17, 15, // tri2
        7, 18, 8 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 8, // tri0
        20, 21, 22, // tri1
        20, 23, 21, // tri2
        21, 24, 22 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        26, 28, 27, // tri1
        29, 30, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_s_1_v[87], 32, 0),
    gsSPNTrianglesInit_5b(
        28, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 2, 5 // tri2
    ),
    gsSPNTriangles_5b(
        2, 6, 5, // tri0
        2, 1, 6, // tri1
        4, 7, 2, // tri2
        7, 8, 2 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        9, 12, 10, // tri1
        13, 6, 1, // tri2
        13, 14, 6 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 6, // tri0
        15, 5, 6, // tri1
        15, 16, 5, // tri2
        15, 17, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 16, // tri0
        18, 17, 19, // tri1
        18, 19, 20, // tri2
        21, 22, 13 // tri3
    ),
    gsSPNTriangles_5b(
        22, 14, 13, // tri0
        21, 23, 22, // tri1
        23, 24, 22, // tri2
        24, 25, 22 // tri3
    ),
    gsSPNTriangles_5b(
        25, 14, 22, // tri0
        8, 26, 27, // tri1
        28, 27, 26, // tri2
        1, 3, 13 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 31, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_s_1_v[119], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 1, 7 // tri2
    ),
    gsSPNTriangles_5b(
        0, 8, 1, // tri0
        8, 0, 9, // tri1
        9, 10, 11, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 4, 3, // tri0
        16, 17, 18, // tri1
        10, 9, 0, // tri2
        11, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        11, 21, 19, // tri0
        22, 23, 24, // tri1
        23, 23, 24, // tri2
        23, 25, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 25, 24, // tri0
        25, 26, 24, // tri1
        26, 27, 28, // tri2
        27, 29, 28 // tri3
    ),
    gsSPNTriangles_5b(
        3, 16, 30, // tri0
        29, 6, 28, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_s_1_v[150], 16, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        3, 1, 4, // tri1
        3, 2, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        3, 8, 9, // tri1
        10, 11, 12, // tri2
        10, 13, 11 // tri3
    ),
    gsSPNTriangles_5b(
        10, 14, 13, // tri0
        11, 15, 12, // tri1
        15, 9, 12, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c5_s_1_v[166], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        3, 2, 1, // tri1
        4, 3, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 4, // tri0
        7, 8, 5, // tri1
        9, 10, 7, // tri2
        9, 11, 10 // tri3
    ),
    gsSPNTriangles_5b(
        9, 12, 11, // tri0
        12, 13, 14, // tri1
        0, 15, 16, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 18, // tri0
        20, 22, 21, // tri1
        23, 24, 25, // tri2
        26, 25, 27 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        22, 28, 30, // tri1
        31, 27, 29, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_s_1_v[198], 18, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 2, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        6, 9, 10, // tri1
        6, 8, 9, // tri2
        11, 10, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        16, 12, 14, // tri1
        17, 13, 15, // tri2
        0, 17, 1 // tri3
    ),
    gsSPEndDisplayList(),
};
