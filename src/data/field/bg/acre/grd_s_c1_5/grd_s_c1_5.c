#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c1_5_v[] = {
#include "assets/field/bg/grd_s_c1_5_v.inc"
};

extern Gfx grd_s_c1_5_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c1_5_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c1_5_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        8, 10, 9, // tri1
        11, 6, 12, // tri2
        11, 13, 6 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 6, // tri0
        14, 5, 6, // tri1
        5, 15, 3, // tri2
        16, 17, 9 // tri3
    ),
    gsSPNTriangles_5b(
        17, 7, 9, // tri0
        17, 18, 7, // tri1
        18, 19, 7, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        20, 23, 21, // tri0
        20, 24, 23, // tri1
        25, 22, 26, // tri2
        24, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        24, 29, 27, // tri0
        29, 30, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_5_v[31], 27, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 4, // tri0
        7, 8, 4, // tri1
        9, 10, 11, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 11, // tri0
        12, 14, 13, // tri1
        12, 15, 14, // tri2
        13, 14, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 13, 16, // tri0
        18, 19, 20, // tri1
        20, 21, 18, // tri2
        20, 2, 21 // tri3
    ),
    gsSPNTriangles_5b(
        2, 3, 21, // tri0
        21, 3, 22, // tri1
        22, 23, 24, // tri2
        22, 3, 23 // tri3
    ),
    gsSPNTriangles_5b(
        23, 25, 24, // tri0
        24, 25, 26, // tri1
        25, 16, 26, // tri2
        16, 14, 26 // tri3
    ),
    gsSPNTriangles_5b(
        26, 19, 18, // tri0
        14, 19, 26, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_5_v[58], 32, 0),
    gsSPNTrianglesInit_5b(
        30, // tri count
        0, 1, 2, // tri0
        2, 3, 4, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        8, 9, 10, // tri1
        10, 11, 12, // tri2
        11, 13, 12 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 13, // tri0
        14, 16, 15, // tri1
        16, 17, 18, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 22, // tri0
        22, 23, 24, // tri1
        24, 25, 26, // tri2
        25, 27, 26 // tri3
    ),
    gsSPNTriangles_5b(
        25, 28, 27, // tri0
        24, 23, 25, // tri1
        22, 21, 23, // tri2
        20, 29, 21 // tri3
    ),
    gsSPNTriangles_5b(
        20, 19, 29, // tri0
        17, 19, 18, // tri1
        16, 14, 17, // tri2
        13, 11, 14 // tri3
    ),
    gsSPNTriangles_5b(
        10, 9, 11, // tri0
        8, 7, 9, // tri1
        6, 5, 7, // tri2
        4, 3, 5 // tri3
    ),
    gsSPNTriangles_5b(
        2, 1, 3, // tri0
        4, 30, 2, // tri1
        8, 31, 6, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_5_v[90], 27, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 3 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 4, // tri0
        8, 9, 6, // tri1
        8, 10, 9, // tri2
        11, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 11, // tri0
        15, 16, 17, // tri1
        17, 18, 19, // tri2
        17, 16, 18 // tri3
    ),
    gsSPNTriangles_5b(
        18, 14, 19, // tri0
        14, 13, 19, // tri1
        11, 14, 12, // tri2
        10, 12, 9 // tri3
    ),
    gsSPNTriangles_5b(
        6, 9, 7, // tri0
        4, 7, 5, // tri1
        3, 5, 1, // tri2
        2, 1, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 20, 22, // tri0
        22, 20, 23, // tri1
        24, 25, 26, // tri2
        24, 23, 25 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_5_v[117], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        8, 10, 9, // tri1
        11, 12, 13, // tri2
        11, 14, 12 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        18, 15, 19, // tri1
        18, 19, 20, // tri2
        20, 21, 18 // tri3
    ),
    gsSPNTriangles_5b(
        20, 22, 21, // tri0
        22, 23, 24, // tri1
        24, 25, 26, // tri2
        26, 27, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 28, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_5_v[147], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 1, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 7, 10, // tri1
        10, 11, 9, // tri2
        12, 13, 11 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 13, // tri0
        16, 17, 18, // tri1
        19, 16, 20, // tri2
        21, 19, 22 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 23, // tri0
        24, 25, 23, // tri1
        26, 25, 24, // tri2
        27, 26, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 31, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_5_v[179], 26, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 3, // tri0
        6, 5, 7, // tri1
        8, 9, 10, // tri2
        9, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 14, // tri0
        15, 16, 17, // tri1
        18, 15, 19, // tri2
        20, 18, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 24, // tri0
        16, 22, 25, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
