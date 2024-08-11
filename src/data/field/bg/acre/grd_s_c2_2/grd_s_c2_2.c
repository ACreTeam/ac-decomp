#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c2_2_v[] = {
#include "assets/field/bg/grd_s_c2_2_v.inc"
};

extern Gfx grd_s_c2_2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c2_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c2_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 6, 7, // tri1
        9, 10, 11, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        12, 14, 13, // tri1
        14, 15, 13, // tri2
        16, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 12, // tri0
        16, 18, 17, // tri1
        9, 19, 10, // tri2
        8, 20, 18 // tri3
    ),
    gsSPNTriangles_5b(
        8, 21, 20, // tri0
        22, 23, 4, // tri1
        23, 5, 4, // tri2
        8, 7, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        26, 28, 27, // tri1
        29, 30, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_2_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 1, 4, // tri1
        1, 0, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        9, 10, 11, // tri2
        9, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 10, // tri0
        14, 15, 16, // tri1
        15, 17, 16, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 23, // tri0
        24, 25, 26, // tri1
        27, 28, 17, // tri2
        27, 29, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 28, // tri0
        30, 31, 28, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_2_v[64], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        0, 5, 6, // tri0
        7, 8, 9, // tri1
        10, 11, 12, // tri2
        13, 6, 14 // tri3
    ),
    gsSPNTriangles_5b(
        0, 6, 13, // tri0
        13, 15, 16, // tri1
        11, 17, 18, // tri2
        11, 15, 17 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 21, // tri0
        22, 23, 19, // tri1
        24, 25, 26, // tri2
        22, 25, 24 // tri3
    ),
    gsSPNTriangles_5b(
        22, 19, 25, // tri0
        27, 28, 29, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_2_v[94], 4, 0),
    gsSPNTrianglesInit_5b(
        2, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c2_2_v[98], 32, 0),
    gsSPNTrianglesInit_5b(
        27, // tri count
        0, 1, 2, // tri0
        2, 3, 0, // tri1
        0, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        2, 5, 3, // tri0
        6, 7, 8, // tri1
        6, 9, 7, // tri2
        6, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 9, // tri0
        12, 13, 9, // tri1
        13, 7, 9, // tri2
        4, 14, 1 // tri3
    ),
    gsSPNTriangles_5b(
        4, 15, 14, // tri0
        15, 16, 14, // tri1
        13, 17, 7, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 12, // tri0
        11, 5, 12, // tri1
        21, 22, 23, // tri2
        22, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        17, 21, 7, // tri0
        17, 22, 21, // tri1
        25, 18, 20, // tri2
        18, 26, 19 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 19, // tri0
        28, 29, 30, // tri1
        28, 31, 29, // tri2
        29, 25, 30 // tri3
    ),
    gsSPVertex(&grd_s_c2_2_v[130], 31, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        3, 6, 5, // tri1
        6, 7, 5, // tri2
        7, 8, 5 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        7, 10, 9, // tri1
        10, 11, 9, // tri2
        11, 12, 9 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        13, 16, 14, // tri1
        16, 17, 14, // tri2
        17, 18, 14 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 18, // tri0
        17, 20, 19, // tri1
        20, 21, 19, // tri2
        21, 22, 19 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        24, 26, 25, // tri1
        26, 2, 25, // tri2
        2, 27, 25 // tri3
    ),
    gsSPNTriangles_5b(
        5, 28, 29, // tri0
        5, 8, 28, // tri1
        15, 14, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_2_v[161], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 5, // tri0
        9, 10, 11, // tri1
        7, 9, 8, // tri2
        10, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        12, 14, 15, // tri0
        16, 17, 18, // tri1
        14, 18, 15, // tri2
        19, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        16, 19, 17, // tri0
        20, 22, 23, // tri1
        22, 24, 25, // tri2
        24, 26, 25 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 29, // tri0
        30, 27, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_2_v[193], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        1, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        9, 10, 11, // tri1
        12, 9, 11, // tri2
        6, 11, 10 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 12, // tri0
        15, 16, 13, // tri1
        17, 18, 19, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 22, 24, // tri0
        25, 26, 27, // tri1
        28, 29, 26, // tri2
        30, 27, 31 // tri3
    ),
    gsSPVertex(&grd_s_c2_2_v[225], 3, 0),
    gsSPNTrianglesInit_5b(
        1, // tri count
        0, 1, 2, // tri0
        0, 0, 0, // tri1
        0, 0, 0 // tri2
    ),
    gsSPEndDisplayList(),
};
