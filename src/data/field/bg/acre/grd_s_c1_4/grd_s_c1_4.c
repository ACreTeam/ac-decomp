#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c1_4_v[] = {
#include "assets/field/bg/grd_s_c1_4_v.inc"
};

extern Gfx grd_s_c1_4_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c1_4_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c1_4_v[246], 14, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 3, 7, // tri0
        8, 5, 9, // tri1
        10, 8, 11, // tri2
        12, 10, 13 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_4_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        7, 8, 9, // tri1
        7, 10, 8, // tri2
        8, 11, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 12, 8, // tri0
        13, 14, 15, // tri1
        14, 16, 15, // tri2
        13, 17, 14 // tri3
    ),
    gsSPNTriangles_5b(
        6, 18, 4, // tri0
        6, 19, 18, // tri1
        5, 10, 7, // tri2
        2, 20, 0 // tri3
    ),
    gsSPNTriangles_5b(
        2, 21, 20, // tri0
        22, 23, 24, // tri1
        23, 25, 24, // tri2
        25, 26, 24 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 29, // tri0
        28, 30, 29, // tri1
        19, 31, 18, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_4_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        5, 6, 4, // tri1
        7, 8, 9, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 10, // tri0
        11, 13, 12, // tri1
        12, 14, 10, // tri2
        0, 15, 1 // tri3
    ),
    gsSPNTriangles_5b(
        16, 15, 0, // tri0
        17, 18, 19, // tri1
        20, 21, 22, // tri2
        23, 20, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 20, // tri0
        25, 26, 27, // tri1
        26, 28, 27, // tri2
        29, 30, 28 // tri3
    ),
    gsSPNTriangles_5b(
        30, 27, 28, // tri0
        30, 31, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_4_v[64], 32, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        8, 10, 9, // tri1
        11, 12, 4, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        19, 18, 20, // tri1
        21, 22, 23, // tri2
        24, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 29, // tri0
        30, 29, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_4_v[96], 3, 0),
    gsSPNTrianglesInit_5b(
        1, // tri count
        0, 1, 2, // tri0
        0, 0, 0, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_4_v[99], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 5, // tri0
        8, 9, 10, // tri1
        9, 11, 10, // tri2
        10, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 8, // tri0
        7, 16, 14, // tri1
        3, 17, 18, // tri2
        19, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 21, 23, // tri0
        24, 2, 25, // tri1
        26, 25, 27, // tri2
        28, 27, 20 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 31, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_4_v[131], 21, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 8, // tri0
        1, 8, 2, // tri1
        9, 0, 10, // tri2
        6, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        16, 17, 14, // tri1
        18, 19, 20, // tri2
        16, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 15, // tri0
        13, 16, 14, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_4_v[152], 32, 0),
    gsSPNTrianglesInit_5b(
        29, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 3, 1, // tri0
        2, 6, 0, // tri1
        7, 8, 9, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        8, 11, 10, // tri0
        12, 9, 13, // tri1
        9, 14, 13, // tri2
        9, 10, 14 // tri3
    ),
    gsSPNTriangles_5b(
        12, 7, 9, // tri0
        12, 15, 7, // tri1
        16, 17, 18, // tri2
        16, 19, 17 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 17, // tri0
        21, 20, 19, // tri1
        21, 22, 20, // tri2
        21, 23, 22 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 18, // tri0
        24, 26, 25, // tri1
        16, 18, 25, // tri2
        26, 24, 12 // tri3
    ),
    gsSPNTriangles_5b(
        24, 15, 12, // tri0
        27, 0, 6, // tri1
        8, 28, 11, // tri2
        29, 30, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 31, 30, // tri0
        30, 11, 28, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_4_v[184], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        3, 6, 5, // tri1
        7, 8, 9, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        8, 11, 10, // tri0
        12, 13, 14, // tri1
        12, 15, 13, // tri2
        13, 16, 14 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 16, // tri0
        17, 19, 18, // tri1
        13, 17, 16, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        20, 23, 21, // tri0
        23, 24, 21, // tri1
        24, 25, 21, // tri2
        24, 26, 25 // tri3
    ),
    gsSPNTriangles_5b(
        24, 27, 26, // tri0
        27, 28, 26, // tri1
        28, 29, 26, // tri2
        28, 0, 29 // tri3
    ),
    gsSPNTriangles_5b(
        28, 30, 0, // tri0
        30, 31, 0, // tri1
        31, 1, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_4_v[216], 16, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        5, 6, 4, // tri1
        6, 7, 4, // tri2
        6, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        6, 9, 8, // tri0
        9, 10, 8, // tri1
        10, 11, 8, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 12, // tri0
        13, 14, 12, // tri1
        14, 15, 12, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_4_v[232], 14, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 0, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        1, 6, 9, // tri1
        10, 11, 12, // tri2
        11, 3, 13 // tri3
    ),
    gsSPEndDisplayList(),
};
