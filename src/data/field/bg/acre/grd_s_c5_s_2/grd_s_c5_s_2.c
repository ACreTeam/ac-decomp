#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c5_s_2_v[] = {
#include "assets/field/bg/grd_s_c5_s_2_v.inc"
};

extern Gfx grd_s_c5_s_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c5_s_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        32, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 2, // tri0
        6, 7, 8, // tri1
        7, 9, 8, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 11, // tri0
        10, 14, 13, // tri1
        15, 16, 17, // tri2
        16, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        16, 19, 18, // tri0
        16, 20, 19, // tri1
        17, 12, 11, // tri2
        17, 18, 12 // tri3
    ),
    gsSPNTriangles_5b(
        18, 21, 12, // tri0
        18, 19, 21, // tri1
        12, 22, 10, // tri2
        12, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        10, 23, 14, // tri0
        10, 22, 23, // tri1
        13, 24, 25, // tri2
        13, 14, 24 // tri3
    ),
    gsSPNTriangles_5b(
        14, 26, 24, // tri0
        14, 23, 26, // tri1
        26, 27, 24, // tri2
        27, 28, 24 // tri3
    ),
    gsSPNTriangles_5b(
        28, 25, 24, // tri0
        28, 29, 25, // tri1
        27, 30, 28, // tri2
        27, 31, 30 // tri3
    ),
    gsSPNTriangles_5b(
        30, 29, 28, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_s_2_v[32], 29, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        0, 3, 4, // tri1
        4, 5, 0 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 6, // tri0
        1, 0, 5, // tri1
        5, 4, 7, // tri2
        7, 8, 5 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        10, 12, 11, // tri1
        12, 13, 11, // tri2
        9, 14, 10 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 10, // tri0
        14, 16, 15, // tri1
        14, 17, 16, // tri2
        16, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        18, 10, 19, // tri0
        18, 12, 10, // tri1
        16, 20, 18, // tri2
        17, 21, 16 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 16, // tri0
        21, 23, 22, // tri1
        21, 24, 23, // tri2
        24, 25, 23 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 23, // tri0
        26, 27, 23, // tri1
        27, 28, 23, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c5_s_2_v[61], 32, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        3, 4, 0, // tri1
        4, 5, 0 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        7, 9, 8, // tri1
        9, 10, 8, // tri2
        7, 11, 9 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 14, // tri0
        15, 10, 14, // tri1
        0, 16, 1, // tri2
        0, 17, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 16, // tri0
        19, 20, 21, // tri1
        19, 9, 20, // tri2
        19, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 22, 9, // tri0
        23, 5, 24, // tri1
        5, 25, 24, // tri2
        23, 26, 5 // tri3
    ),
    gsSPNTriangles_5b(
        23, 27, 26, // tri0
        27, 28, 26, // tri1
        5, 4, 25, // tri2
        23, 29, 27 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_s_2_v[92], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        9, 10, 2, // tri0
        9, 11, 10, // tri1
        10, 12, 2, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        1, 9, 2, // tri0
        8, 16, 6, // tri1
        11, 9, 17, // tri2
        1, 18, 9 // tri3
    ),
    gsSPNTriangles_5b(
        18, 1, 19, // tri0
        19, 20, 21, // tri1
        21, 22, 23, // tri2
        24, 25, 23 // tri3
    ),
    gsSPNTriangles_5b(
        26, 3, 27, // tri0
        26, 4, 3, // tri1
        28, 27, 29, // tri2
        24, 30, 25 // tri3
    ),
    gsSPNTriangles_5b(
        30, 31, 25, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_s_2_v[124], 21, 0),
    gsSPNTrianglesInit_5b(
        9, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        12, 13, 14, // tri1
        10, 15, 16, // tri2
        15, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        7, 17, 8, // tri0
        18, 19, 20, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c5_s_2_v[145], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        5, 8, 6, // tri1
        6, 9, 7, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 11, // tri0
        8, 14, 15, // tri1
        14, 16, 15, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        17, 20, 18, // tri0
        21, 19, 22, // tri1
        10, 21, 23, // tri2
        24, 12, 25 // tri3
    ),
    gsSPNTriangles_5b(
        17, 26, 27, // tri0
        28, 29, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_s_2_v[176], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 8, // tri1
        10, 11, 12, // tri2
        11, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 16, // tri0
        15, 17, 18, // tri1
        17, 19, 20, // tri2
        19, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        26, 25, 27, // tri1
        28, 29, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_s_2_v[207], 11, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 2, 4, // tri1
        5, 4, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        7, 9, 10, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
