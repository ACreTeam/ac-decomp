#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];

static Vtx grd_s_e3_1_v[] = {
#include "assets/field/bg/grd_s_e3_1_v.inc"
};

extern Gfx grd_s_e3_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_e3_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_e3_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        28, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        0, 5, 3, // tri0
        0, 6, 5, // tri1
        6, 7, 5, // tri2
        6, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 7, // tri0
        8, 10, 9, // tri1
        8, 11, 10, // tri2
        11, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        11, 14, 13, // tri1
        14, 15, 13, // tri2
        14, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        14, 17, 16, // tri0
        17, 18, 16, // tri1
        17, 19, 18, // tri2
        19, 20, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        22, 23, 24, // tri1
        22, 25, 23, // tri2
        25, 26, 23 // tri3
    ),
    gsSPNTriangles_5b(
        25, 27, 26, // tri0
        25, 28, 27, // tri1
        28, 29, 27, // tri2
        28, 30, 29 // tri3
    ),
    gsSPNTriangles_5b(
        30, 31, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_e3_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        34, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 3, // tri0
        4, 6, 5, // tri1
        4, 7, 6, // tri2
        7, 8, 6 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        9, 10, 8, // tri1
        9, 11, 10, // tri2
        9, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 11, // tri0
        14, 15, 16, // tri1
        15, 17, 16, // tri2
        15, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 17, // tri0
        19, 20, 17, // tri1
        19, 21, 20, // tri2
        21, 22, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 2, 22, // tri0
        2, 23, 22, // tri1
        2, 3, 23, // tri2
        3, 5, 23 // tri3
    ),
    gsSPNTriangles_5b(
        5, 24, 23, // tri0
        5, 6, 24, // tri1
        6, 8, 24, // tri2
        8, 25, 24 // tri3
    ),
    gsSPNTriangles_5b(
        8, 10, 25, // tri0
        10, 26, 25, // tri1
        10, 11, 26, // tri2
        11, 27, 26 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 27, // tri0
        28, 29, 30, // tri1
        29, 31, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_e3_1_v[64], 19, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        5, 6, 4, // tri1
        5, 7, 6, // tri2
        7, 8, 6 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 6, // tri0
        8, 10, 9, // tri1
        10, 11, 9, // tri2
        11, 12, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        13, 14, 12, // tri1
        13, 15, 14, // tri2
        15, 16, 14 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 14, // tri0
        16, 18, 17, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_e3_1_v[83], 22, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        7, 8, 9, // tri1
        8, 10, 9, // tri2
        4, 6, 5 // tri3
    ),
    gsSPNTriangles_5b(
        11, 3, 0, // tri0
        11, 4, 3, // tri1
        6, 12, 7, // tri2
        12, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        16, 17, 15, // tri1
        18, 19, 16, // tri2
        20, 21, 18 // tri3
    ),
    gsSPEndDisplayList(),
};
