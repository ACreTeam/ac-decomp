#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c7_s_3_v[] = {
#include "assets/field/bg/grd_s_c7_s_3_v.inc"
};

extern Gfx grd_s_c7_s_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c7_s_3_v[225], 11, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 7, 10, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_s_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 0, 5 // tri2
    ),
    gsSPNTriangles_5b(
        0, 2, 5, // tri0
        6, 7, 8, // tri1
        7, 9, 8, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        14, 16, 15, // tri1
        14, 17, 16, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        20, 13, 18, // tri1
        22, 23, 24, // tri2
        23, 25, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        26, 28, 27, // tri1
        29, 30, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_3_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        5, 8, 7, // tri1
        8, 9, 7, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        10, 14, 15, // tri1
        14, 16, 15, // tri2
        14, 17, 16 // tri3
    ),
    gsSPNTriangles_5b(
        18, 3, 19, // tri0
        3, 0, 19, // tri1
        20, 16, 17, // tri2
        20, 21, 16 // tri3
    ),
    gsSPNTriangles_5b(
        20, 22, 21, // tri0
        22, 23, 21, // tri1
        23, 24, 21, // tri2
        24, 25, 21 // tri3
    ),
    gsSPNTriangles_5b(
        23, 26, 24, // tri0
        27, 11, 28, // tri1
        27, 29, 18, // tri2
        27, 30, 29 // tri3
    ),
    gsSPNTriangles_5b(
        5, 31, 8, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_3_v[64], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        5, 6, 4, // tri1
        6, 7, 4, // tri2
        8, 9, 5 // tri3
    ),
    gsSPNTriangles_5b(
        10, 7, 11, // tri0
        10, 12, 7, // tri1
        13, 14, 15, // tri2
        13, 16, 14 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 14, // tri0
        16, 18, 17, // tri1
        19, 20, 21, // tri2
        20, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        19, 23, 20, // tri0
        24, 25, 26, // tri1
        25, 27, 26, // tri2
        25, 28, 27 // tri3
    ),
    gsSPNTriangles_5b(
        25, 29, 28, // tri0
        28, 30, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_3_v[95], 11, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        6, 9, 8, // tri2
        9, 10, 8 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_s_3_v[106], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        1, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        9, 10, 11, // tri1
        10, 3, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 13, 17, // tri0
        18, 19, 20, // tri1
        21, 18, 22, // tri2
        14, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        23, 21, 25, // tri0
        26, 27, 28, // tri1
        29, 30, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_3_v[138], 17, 0),
    gsSPNTrianglesInit_5b(
        9, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 4 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        11, 8, 10, // tri1
        12, 11, 10, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 13, 15, // tri0
        16, 15, 7, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_s_3_v[155], 32, 0),
    gsSPNTrianglesInit_5b(
        33, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 5, // tri0
        6, 8, 7, // tri1
        8, 9, 7, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        8, 11, 10, // tri0
        11, 12, 10, // tri1
        12, 13, 10, // tri2
        12, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 13, // tri0
        15, 16, 13, // tri1
        3, 17, 4, // tri2
        17, 18, 4 // tri3
    ),
    gsSPNTriangles_5b(
        18, 6, 4, // tri0
        18, 19, 6, // tri1
        19, 8, 6, // tri2
        19, 20, 8 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 8, // tri0
        21, 11, 8, // tri1
        21, 22, 11, // tri2
        22, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 12, // tri0
        23, 14, 12, // tri1
        23, 15, 14, // tri2
        23, 24, 15 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        26, 1, 27, // tri1
        26, 28, 1, // tri2
        26, 29, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 28, // tri0
        29, 31, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_3_v[187], 27, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        5, 6, 4, // tri1
        6, 7, 4, // tri2
        7, 8, 4 // tri3
    ),
    gsSPNTriangles_5b(
        8, 3, 4, // tri0
        8, 9, 3, // tri1
        9, 2, 3, // tri2
        9, 10, 2 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 2, // tri0
        10, 12, 11, // tri1
        10, 13, 12, // tri2
        13, 14, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 14, // tri0
        16, 17, 14, // tri1
        10, 18, 13, // tri2
        19, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 19, // tri0
        22, 19, 21, // tri1
        23, 24, 19, // tri2
        24, 25, 19 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 19, // tri0
        26, 20, 19, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_s_3_v[214], 11, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 8, 9, // tri0
        8, 3, 10, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
