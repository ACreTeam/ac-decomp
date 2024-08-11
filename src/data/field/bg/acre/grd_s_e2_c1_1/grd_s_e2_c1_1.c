#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];

static Vtx grd_s_e2_c1_1_v[] = {
#include "assets/field/bg/grd_s_e2_c1_1_v.inc"
};

extern Gfx grd_s_e2_c1_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_e2_c1_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_e2_c1_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        33, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 1, 0 // tri2
    ),
    gsSPNTriangles_5b(
        5, 4, 0, // tri0
        3, 2, 6, // tri1
        2, 7, 6, // tri2
        6, 7, 8 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        9, 10, 8, // tri1
        10, 9, 11, // tri2
        9, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        12, 14, 13, // tri1
        14, 15, 13, // tri2
        13, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        13, 16, 17, // tri0
        13, 17, 11, // tri1
        11, 17, 18, // tri2
        11, 18, 10 // tri3
    ),
    gsSPNTriangles_5b(
        8, 10, 18, // tri0
        8, 18, 19, // tri1
        8, 19, 6, // tri2
        20, 0, 3 // tri3
    ),
    gsSPNTriangles_5b(
        21, 5, 0, // tri0
        21, 0, 20, // tri1
        6, 19, 20, // tri2
        6, 20, 3 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 24, // tri0
        22, 24, 25, // tri1
        22, 25, 26, // tri2
        24, 27, 25 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 25, // tri0
        28, 29, 25, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_e2_c1_1_v[30], 32, 0),
    gsSPNTrianglesInit_5b(
        37, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 0, 2, // tri0
        2, 6, 5, // tri1
        6, 2, 4, // tri2
        7, 4, 3 // tri3
    ),
    gsSPNTriangles_5b(
        8, 7, 3, // tri0
        7, 9, 6, // tri1
        7, 6, 4, // tri2
        10, 11, 8 // tri3
    ),
    gsSPNTriangles_5b(
        7, 8, 11, // tri0
        12, 11, 10, // tri1
        13, 11, 12, // tri2
        11, 13, 9 // tri3
    ),
    gsSPNTriangles_5b(
        9, 7, 11, // tri0
        12, 10, 14, // tri1
        14, 13, 12, // tri2
        14, 15, 13 // tri3
    ),
    gsSPNTriangles_5b(
        15, 14, 16, // tri0
        16, 17, 15, // tri1
        17, 16, 18, // tri2
        19, 20, 17 // tri3
    ),
    gsSPNTriangles_5b(
        19, 17, 18, // tri0
        21, 22, 23, // tri1
        24, 21, 23, // tri2
        21, 24, 20 // tri3
    ),
    gsSPNTriangles_5b(
        20, 19, 21, // tri0
        25, 23, 22, // tri1
        25, 22, 26, // tri2
        26, 27, 25 // tri3
    ),
    gsSPNTriangles_5b(
        28, 25, 27, // tri0
        25, 24, 23, // tri1
        25, 28, 24, // tri2
        29, 15, 17 // tri3
    ),
    gsSPNTriangles_5b(
        30, 17, 20, // tri0
        17, 30, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_e2_c1_1_v[62], 15, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        1, 0, 3, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        1, 4, 5, // tri0
        6, 7, 2, // tri1
        7, 0, 2, // tri2
        7, 8, 0 // tri3
    ),
    gsSPNTriangles_5b(
        7, 6, 9, // tri0
        10, 9, 11, // tri1
        11, 12, 10, // tri2
        7, 9, 10 // tri3
    ),
    gsSPNTriangles_5b(
        8, 7, 10, // tri0
        10, 13, 14, // tri1
        10, 14, 8, // tri2
        13, 10, 12 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_e2_c1_1_v[77], 25, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 9, 10, // tri1
        11, 12, 8, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 13, // tri0
        0, 18, 1, // tri1
        3, 19, 2, // tri2
        19, 20, 2 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        4, 22, 5, // tri1
        23, 7, 5, // tri2
        7, 24, 6 // tri3
    ),
    gsSPEndDisplayList(),
};
