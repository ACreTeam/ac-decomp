#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];

static Vtx grd_s_e1_1_v[] = {
#include "assets/field/bg/grd_s_e1_1_v.inc"
};

extern Gfx grd_s_e1_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_e1_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_e1_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        41, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        7, 8, 5, // tri1
        7, 9, 8, // tri2
        9, 10, 8 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 10, // tri0
        11, 12, 10, // tri1
        11, 13, 12, // tri2
        11, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 13, // tri0
        14, 16, 15, // tri1
        16, 2, 15, // tri2
        16, 0, 2 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 0, // tri0
        17, 18, 0, // tri1
        17, 19, 18, // tri2
        19, 20, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        19, 22, 21, // tri1
        22, 23, 21, // tri2
        5, 24, 6 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 6, // tri0
        5, 26, 24, // tri1
        5, 8, 26, // tri2
        8, 27, 26 // tri3
    ),
    gsSPNTriangles_5b(
        8, 10, 27, // tri0
        10, 12, 27, // tri1
        12, 28, 27, // tri2
        12, 13, 28 // tri3
    ),
    gsSPNTriangles_5b(
        13, 29, 28, // tri0
        13, 15, 29, // tri1
        15, 3, 29, // tri2
        15, 2, 3 // tri3
    ),
    gsSPNTriangles_5b(
        0, 18, 1, // tri0
        18, 30, 1, // tri1
        18, 20, 30, // tri2
        20, 21, 30 // tri3
    ),
    gsSPNTriangles_5b(
        21, 31, 30, // tri0
        21, 23, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_e1_1_v[32], 31, 0),
    gsSPNTrianglesInit_5b(
        39, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 3, // tri0
        4, 6, 5, // tri1
        6, 7, 5, // tri2
        6, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 7, // tri0
        9, 10, 7, // tri1
        9, 11, 10, // tri2
        9, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 11, // tri0
        13, 14, 11, // tri1
        13, 15, 14, // tri2
        15, 16, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 16, // tri0
        17, 18, 16, // tri1
        18, 19, 16, // tri2
        18, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        18, 21, 20, // tri0
        18, 22, 21, // tri1
        18, 23, 22, // tri2
        18, 17, 23 // tri3
    ),
    gsSPNTriangles_5b(
        17, 15, 23, // tri0
        15, 24, 23, // tri1
        15, 13, 24, // tri2
        13, 25, 24 // tri3
    ),
    gsSPNTriangles_5b(
        13, 12, 25, // tri0
        12, 9, 25, // tri1
        9, 26, 25, // tri2
        9, 8, 26 // tri3
    ),
    gsSPNTriangles_5b(
        8, 27, 26, // tri0
        8, 6, 27, // tri1
        6, 28, 27, // tri2
        6, 4, 28 // tri3
    ),
    gsSPNTriangles_5b(
        4, 29, 28, // tri0
        4, 1, 29, // tri1
        1, 30, 29, // tri2
        1, 0, 30 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_e1_1_v[63], 23, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 2, 4, // tri1
        5, 4, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 6, 8, // tri0
        9, 10, 11, // tri1
        9, 12, 10, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        16, 17, 18, // tri1
        18, 17, 19, // tri2
        16, 20, 17 // tri3
    ),
    gsSPNTriangles_5b(
        16, 15, 20, // tri0
        14, 21, 15, // tri1
        13, 21, 14, // tri2
        9, 22, 12 // tri3
    ),
    gsSPNTriangles_5b(
        12, 22, 13, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
