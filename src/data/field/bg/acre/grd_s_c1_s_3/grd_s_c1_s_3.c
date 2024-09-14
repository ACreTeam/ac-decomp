#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c1_s_3_v[] = {
#include "assets/field/bg/grd_s_c1_s_3_v.inc"
};

extern Gfx grd_s_c1_s_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c1_s_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        8, 7, 9, // tri1
        7, 10, 9, // tri2
        11, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        12, 8, 13, // tri0
        14, 15, 16, // tri1
        0, 17, 1, // tri2
        18, 19, 14 // tri3
    ),
    gsSPNTriangles_5b(
        18, 20, 19, // tri0
        18, 21, 20, // tri1
        20, 22, 19, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        23, 26, 24, // tri0
        23, 27, 26, // tri1
        28, 6, 5, // tri2
        28, 29, 6 // tri3
    ),
    gsSPNTriangles_5b(
        30, 28, 5, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_3_v[31], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        9, 10, 11, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 11, // tri0
        14, 15, 16, // tri1
        14, 17, 15, // tri2
        17, 18, 15 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 21, // tri0
        7, 22, 5, // tri1
        23, 10, 24, // tri2
        10, 9, 24 // tri3
    ),
    gsSPNTriangles_5b(
        20, 25, 26, // tri0
        27, 28, 7, // tri1
        29, 30, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_3_v[63], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        8, 10, 9, // tri1
        11, 12, 4, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        19, 20, 21, // tri1
        19, 22, 20, // tri2
        22, 23, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 24, 19, // tri0
        0, 5, 25, // tri1
        0, 26, 5, // tri2
        26, 3, 5 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 29, // tri0
        0, 2, 26, // tri1
        30, 31, 13, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_3_v[95], 12, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 3 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        8, 11, 9, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_s_3_v[107], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        2, 3, 8, // tri1
        0, 9, 1, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 11, // tri0
        14, 11, 15, // tri1
        14, 16, 11, // tri2
        9, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 8, // tri0
        6, 21, 19, // tri1
        4, 22, 23, // tri2
        24, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 29, // tri0
        15, 27, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_3_v[138], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        6, 8, 4, // tri0
        9, 3, 5, // tri1
        10, 11, 12, // tri2
        13, 10, 14 // tri3
    ),
    gsSPNTriangles_5b(
        11, 15, 16, // tri0
        15, 17, 18, // tri1
        19, 20, 21, // tri2
        20, 13, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        26, 23, 27, // tri1
        28, 29, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_3_v[169], 9, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        5, 0, 7, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_s_3_v[178], 32, 0),
    gsSPNTrianglesInit_5b(
        29, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        6, 7, 8, // tri1
        7, 9, 8, // tri2
        9, 10, 8 // tri3
    ),
    gsSPNTriangles_5b(
        7, 11, 12, // tri0
        11, 13, 12, // tri1
        14, 15, 16, // tri2
        14, 11, 15 // tri3
    ),
    gsSPNTriangles_5b(
        11, 17, 15, // tri0
        11, 18, 17, // tri1
        11, 7, 18, // tri2
        7, 6, 18 // tri3
    ),
    gsSPNTriangles_5b(
        4, 19, 1, // tri0
        19, 20, 1, // tri1
        21, 3, 0, // tri2
        21, 22, 3 // tri3
    ),
    gsSPNTriangles_5b(
        21, 23, 22, // tri0
        1, 24, 2, // tri1
        1, 20, 24, // tri2
        7, 25, 9 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 9, // tri0
        7, 12, 25, // tri1
        27, 28, 29, // tri2
        28, 10, 29 // tri3
    ),
    gsSPNTriangles_5b(
        30, 31, 29, // tri0
        31, 27, 29, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_3_v[210], 32, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        3, 2, 4, // tri1
        3, 0, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 9, 10, // tri1
        11, 8, 10, // tri2
        12, 7, 6 // tri3
    ),
    gsSPNTriangles_5b(
        13, 12, 6, // tri0
        14, 15, 4, // tri1
        16, 14, 4, // tri2
        16, 4, 2 // tri3
    ),
    gsSPNTriangles_5b(
        17, 16, 2, // tri0
        17, 2, 1, // tri1
        17, 1, 18, // tri2
        19, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 22, // tri0
        23, 20, 22, // tri1
        11, 10, 24, // tri2
        25, 18, 1 // tri3
    ),
    gsSPNTriangles_5b(
        0, 25, 1, // tri0
        26, 27, 28, // tri1
        29, 30, 28, // tri2
        30, 26, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 28, 31, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_3_v[242], 14, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 4, 2, // tri1
        4, 0, 2 // tri2
    ),
    gsSPNTriangles_5b(
        3, 2, 5, // tri0
        6, 7, 5, // tri1
        7, 3, 5, // tri2
        8, 9, 6 // tri3
    ),
    gsSPNTriangles_5b(
        8, 6, 5, // tri0
        8, 5, 2, // tri1
        10, 8, 2, // tri2
        10, 2, 1 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        1, 11, 13, // tri1
        10, 1, 13, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
