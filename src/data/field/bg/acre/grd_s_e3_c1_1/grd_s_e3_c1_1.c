#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];

static Vtx grd_s_e3_c1_1_v[] = {
#include "assets/field/bg/grd_s_e3_c1_1_v.inc"
};

extern Gfx grd_s_e3_c1_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_e3_c1_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_e3_c1_1_v[0], 27, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 3, // tri0
        5, 6, 3, // tri1
        5, 7, 6, // tri2
        7, 8, 6 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        10, 12, 11, // tri1
        13, 14, 9, // tri2
        14, 15, 9 // tri3
    ),
    gsSPNTriangles_5b(
        15, 10, 9, // tri0
        14, 16, 15, // tri1
        17, 18, 19, // tri2
        18, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 24, // tri0
        25, 26, 22, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_e3_c1_1_v[27], 32, 0),
    gsSPNTrianglesInit_5b(
        37, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 5, 7, // tri0
        8, 6, 7, // tri1
        9, 8, 7, // tri2
        9, 7, 10 // tri3
    ),
    gsSPNTriangles_5b(
        11, 9, 10, // tri0
        11, 10, 12, // tri1
        11, 12, 13, // tri2
        14, 11, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 13, 15, // tri0
        16, 14, 15, // tri1
        16, 15, 17, // tri2
        16, 17, 0 // tri3
    ),
    gsSPNTriangles_5b(
        16, 0, 2, // tri0
        10, 18, 19, // tri1
        12, 10, 19, // tri2
        13, 12, 19 // tri3
    ),
    gsSPNTriangles_5b(
        13, 19, 20, // tri0
        15, 13, 20, // tri1
        17, 15, 20, // tri2
        17, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        0, 17, 21, // tri0
        0, 21, 22, // tri1
        1, 0, 22, // tri2
        18, 10, 7 // tri3
    ),
    gsSPNTriangles_5b(
        23, 18, 7, // tri0
        23, 7, 5, // tri1
        23, 5, 4, // tri2
        24, 23, 4 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        25, 27, 28, // tri1
        29, 25, 28, // tri2
        29, 28, 30 // tri3
    ),
    gsSPNTriangles_5b(
        31, 29, 30, // tri0
        31, 30, 8, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_e3_c1_1_v[59], 32, 0),
    gsSPNTrianglesInit_5b(
        38, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 0, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 4, 3, // tri0
        5, 3, 6, // tri1
        7, 5, 6, // tri2
        7, 6, 8 // tri3
    ),
    gsSPNTriangles_5b(
        9, 7, 8, // tri0
        10, 9, 8, // tri1
        10, 8, 11, // tri2
        12, 10, 11 // tri3
    ),
    gsSPNTriangles_5b(
        12, 11, 13, // tri0
        14, 12, 13, // tri1
        15, 16, 17, // tri2
        15, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        15, 18, 19, // tri0
        20, 15, 19, // tri1
        20, 19, 1, // tri2
        21, 20, 1 // tri3
    ),
    gsSPNTriangles_5b(
        21, 1, 0, // tri0
        22, 21, 0, // tri1
        22, 0, 4, // tri2
        23, 22, 4 // tri3
    ),
    gsSPNTriangles_5b(
        23, 4, 5, // tri0
        23, 5, 7, // tri1
        24, 23, 7, // tri2
        24, 7, 9 // tri3
    ),
    gsSPNTriangles_5b(
        25, 24, 9, // tri0
        25, 9, 10, // tri1
        25, 10, 12, // tri2
        26, 25, 12 // tri3
    ),
    gsSPNTriangles_5b(
        26, 12, 14, // tri0
        27, 28, 16, // tri1
        27, 16, 15, // tri2
        29, 30, 20 // tri3
    ),
    gsSPNTriangles_5b(
        29, 20, 21, // tri0
        31, 29, 21, // tri1
        22, 31, 21, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_e3_c1_1_v[91], 12, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 2, 5 // tri2
    ),
    gsSPNTriangles_5b(
        4, 0, 2, // tri0
        6, 7, 8, // tri1
        6, 9, 7, // tri2
        5, 6, 8 // tri3
    ),
    gsSPNTriangles_5b(
        4, 5, 8, // tri0
        2, 10, 11, // tri1
        5, 2, 11, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
