#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c5_2_v[] = {
#include "assets/field/bg/grd_s_c5_2_v.inc"
};

extern Gfx grd_s_c5_2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c5_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c5_2_v[225], 23, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        3, 4, 6, // tri0
        8, 9, 10, // tri1
        9, 5, 7, // tri2
        11, 8, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 11, 14, // tri0
        13, 14, 15, // tri1
        16, 17, 18, // tri2
        17, 13, 15 // tri3
    ),
    gsSPNTriangles_5b(
        19, 16, 20, // tri0
        21, 19, 22, // tri1
        16, 18, 20, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c5_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        7, 9, 5, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 6, 12, // tri0
        6, 5, 12, // tri1
        11, 13, 14, // tri2
        11, 15, 13 // tri3
    ),
    gsSPNTriangles_5b(
        11, 16, 15, // tri0
        11, 10, 16, // tri1
        1, 17, 16, // tri2
        1, 0, 17 // tri3
    ),
    gsSPNTriangles_5b(
        17, 15, 16, // tri0
        3, 18, 4, // tri1
        18, 19, 4, // tri2
        18, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 19, // tri0
        22, 23, 24, // tri1
        23, 25, 24, // tri2
        26, 27, 22 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 22, // tri0
        29, 30, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_2_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        0, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        4, 6, 5, // tri0
        7, 8, 9, // tri1
        8, 10, 9, // tri2
        10, 11, 9 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 14, // tri0
        13, 15, 14, // tri1
        15, 7, 14, // tri2
        11, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        16, 18, 17, // tri0
        11, 10, 16, // tri1
        19, 1, 20, // tri2
        21, 18, 16 // tri3
    ),
    gsSPNTriangles_5b(
        7, 15, 8, // tri0
        12, 22, 13, // tri1
        12, 23, 22, // tri2
        23, 24, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 25, 24, // tri0
        25, 26, 24, // tri1
        26, 27, 24, // tri2
        27, 28, 24 // tri3
    ),
    gsSPNTriangles_5b(
        26, 29, 27, // tri0
        30, 31, 21, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_2_v[64], 16, 0),
    gsSPNTrianglesInit_5b(
        8, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        9, 10, 11, // tri2
        12, 9, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c5_2_v[80], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 6, 5, // tri0
        7, 8, 9, // tri1
        8, 6, 9, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 11, // tri0
        7, 14, 15, // tri1
        14, 12, 16, // tri2
        10, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 18, // tri0
        20, 21, 22, // tri1
        23, 20, 24, // tri2
        25, 26, 27 // tri3
    ),
    gsSPNTriangles_5b(
        25, 27, 19, // tri0
        26, 23, 28, // tri1
        29, 30, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_2_v[112], 12, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        9, 0, 11, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c5_2_v[124], 32, 0),
    gsSPNTrianglesInit_5b(
        30, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        5, 8, 7, // tri1
        4, 9, 5, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        14, 15, 16, // tri1
        14, 17, 15, // tri2
        14, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        0, 19, 1, // tri0
        20, 16, 21, // tri1
        16, 15, 21, // tri2
        0, 22, 19 // tri3
    ),
    gsSPNTriangles_5b(
        0, 23, 22, // tri0
        24, 25, 8, // tri1
        24, 26, 25, // tri2
        26, 27, 25 // tri3
    ),
    gsSPNTriangles_5b(
        27, 17, 25, // tri0
        17, 28, 25, // tri1
        28, 8, 25, // tri2
        17, 18, 28 // tri3
    ),
    gsSPNTriangles_5b(
        28, 7, 8, // tri0
        29, 12, 30, // tri1
        12, 31, 30, // tri2
        12, 13, 31 // tri3
    ),
    gsSPNTriangles_5b(
        29, 9, 12, // tri0
        12, 9, 10, // tri1
        9, 4, 10, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_2_v[156], 32, 0),
    gsSPNTrianglesInit_5b(
        28, // tri count
        0, 1, 2, // tri0
        3, 4, 0, // tri1
        4, 1, 0 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        4, 6, 1, // tri1
        6, 7, 1, // tri2
        7, 2, 1 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        8, 11, 9, // tri1
        12, 8, 13, // tri2
        8, 10, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 13, 15, // tri0
        14, 12, 13, // tri1
        16, 14, 17, // tri2
        14, 15, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 17, 19, // tri0
        18, 16, 17, // tri1
        20, 18, 21, // tri2
        18, 19, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 21, 23, // tri0
        22, 20, 21, // tri1
        24, 25, 26, // tri2
        25, 27, 26 // tri3
    ),
    gsSPNTriangles_5b(
        28, 26, 29, // tri0
        28, 24, 26, // tri1
        5, 30, 4, // tri2
        30, 6, 4 // tri3
    ),
    gsSPNTriangles_5b(
        10, 9, 31, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_2_v[188], 10, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 2, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        7, 9, 8, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c5_2_v[198], 27, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 5, 9, // tri0
        10, 8, 11, // tri1
        12, 13, 14, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 12, 19, // tri0
        6, 20, 21, // tri1
        20, 22, 21, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 22, // tri0
        16, 26, 17, // tri1
        23, 15, 24, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
