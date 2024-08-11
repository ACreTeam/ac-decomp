#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c6_s_1_v[] = {
#include "assets/field/bg/grd_s_c6_s_1_v.inc"
};

extern Gfx grd_s_c6_s_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c6_s_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c6_s_1_v[205], 29, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 7, 10, // tri1
        11, 9, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        17, 13, 19, // tri1
        13, 15, 19, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 20, 22, // tri0
        24, 23, 25, // tri1
        20, 26, 21, // tri2
        26, 27, 28 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c6_s_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        7, 8, 5, // tri1
        4, 9, 7, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        14, 15, 16, // tri1
        14, 17, 15, // tri2
        17, 18, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 19, 14, // tri0
        19, 20, 14, // tri1
        21, 22, 23, // tri2
        22, 19, 23 // tri3
    ),
    gsSPNTriangles_5b(
        22, 20, 19, // tri0
        21, 24, 22, // tri1
        18, 25, 26, // tri2
        25, 13, 26 // tri3
    ),
    gsSPNTriangles_5b(
        25, 27, 13, // tri0
        25, 28, 27, // tri1
        29, 2, 3, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c6_s_1_v[30], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 9, 10, // tri1
        11, 12, 13, // tri2
        12, 14, 8 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 8, // tri0
        4, 16, 17, // tri1
        16, 15, 17, // tri2
        14, 17, 15 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        18, 21, 19, // tri1
        22, 23, 24, // tri2
        23, 25, 24 // tri3
    ),
    gsSPNTriangles_5b(
        23, 26, 25, // tri0
        25, 26, 27, // tri1
        28, 22, 24, // tri2
        29, 30, 3 // tri3
    ),
    gsSPNTriangles_5b(
        29, 11, 30, // tri0
        11, 13, 30, // tri1
        2, 3, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c6_s_1_v[62], 29, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 3, 6, // tri1
        8, 9, 3, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 10, // tri0
        14, 11, 10, // tri1
        14, 15, 11, // tri2
        14, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 11, // tri0
        17, 18, 19, // tri1
        20, 21, 22, // tri2
        21, 20, 23 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 26, // tri0
        27, 4, 28, // tri1
        27, 1, 4, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c6_s_1_v[91], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        5, 8, 6, // tri1
        6, 9, 7, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        13, 14, 12, // tri1
        15, 16, 17, // tri2
        16, 4, 17 // tri3
    ),
    gsSPNTriangles_5b(
        14, 18, 19, // tri0
        20, 21, 22, // tri1
        21, 10, 22, // tri2
        8, 23, 20 // tri3
    ),
    gsSPNTriangles_5b(
        9, 24, 25, // tri0
        26, 27, 28, // tri1
        29, 26, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c6_s_1_v[122], 25, 0),
    gsSPNTrianglesInit_5b(
        12, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        9, 10, 11, // tri1
        12, 13, 14, // tri2
        15, 12, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 19, // tri0
        20, 21, 22, // tri1
        23, 9, 24, // tri2
        23, 24, 21 // tri3
    ),
    gsSPNTriangles_5b(
        13, 20, 22, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c6_s_1_v[147], 29, 0),
    gsSPNTrianglesInit_5b(
        31, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 1, // tri0
        3, 6, 2, // tri1
        6, 7, 2, // tri2
        6, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        10, 12, 11, // tri1
        12, 13, 11, // tri2
        12, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        5, 15, 16, // tri0
        15, 17, 16, // tri1
        17, 15, 18, // tri2
        15, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        15, 4, 19, // tri0
        4, 20, 19, // tri1
        4, 0, 20, // tri2
        0, 21, 20 // tri3
    ),
    gsSPNTriangles_5b(
        0, 2, 21, // tri0
        2, 22, 21, // tri1
        2, 7, 22, // tri2
        7, 23, 22 // tri3
    ),
    gsSPNTriangles_5b(
        7, 24, 23, // tri0
        7, 25, 24, // tri1
        5, 4, 15, // tri2
        8, 26, 7 // tri3
    ),
    gsSPNTriangles_5b(
        26, 25, 7, // tri0
        10, 27, 12, // tri1
        27, 14, 12, // tri2
        27, 28, 14 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c6_s_1_v[176], 29, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 8, // tri0
        9, 10, 11, // tri1
        10, 3, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        19, 20, 21, // tri1
        22, 23, 24, // tri2
        25, 26, 27 // tri3
    ),
    gsSPNTriangles_5b(
        14, 22, 28, // tri0
        25, 16, 26, // tri1
        20, 25, 27, // tri2
        22, 24, 28 // tri3
    ),
    gsSPEndDisplayList(),
};
