#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c7_2_v[] = {
#include "assets/field/bg/grd_s_c7_2_v.inc"
};

extern Gfx grd_s_c7_2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c7_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c7_2_v[235], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 7, 10, // tri1
        11, 12, 13, // tri2
        14, 11, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        14, 15, 17, // tri1
        19, 20, 21, // tri2
        20, 16, 18 // tri3
    ),
    gsSPNTriangles_5b(
        22, 19, 23, // tri0
        24, 22, 25, // tri1
        24, 25, 26, // tri2
        27, 28, 29 // tri3
    ),
    gsSPNTriangles_5b(
        28, 24, 26, // tri0
        30, 27, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_2_v[267], 6, 0),
    gsSPNTrianglesInit_5b(
        2, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        0, 0, 0 // tri2
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        31, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 6, 7, // tri0
        5, 8, 6, // tri1
        9, 10, 11, // tri2
        9, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 11, // tri0
        13, 14, 11, // tri1
        12, 11, 15, // tri2
        12, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        11, 14, 15, // tri0
        14, 17, 15, // tri1
        16, 15, 18, // tri2
        15, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 18, // tri0
        15, 21, 19, // tri1
        15, 17, 21, // tri2
        20, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        20, 19, 22, // tri0
        19, 21, 22, // tri1
        21, 24, 22, // tri2
        23, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        23, 22, 25, // tri0
        22, 24, 25, // tri1
        24, 27, 25, // tri2
        26, 25, 28 // tri3
    ),
    gsSPNTriangles_5b(
        25, 29, 28, // tri0
        25, 27, 29, // tri1
        27, 30, 29, // tri2
        28, 29, 31 // tri3
    ),
    gsSPVertex(&grd_s_c7_2_v[32], 28, 0),
    gsSPNTrianglesInit_5b(
        28, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        4, 5, 1 // tri2
    ),
    gsSPNTriangles_5b(
        2, 1, 6, // tri0
        1, 7, 6, // tri1
        1, 5, 7, // tri2
        5, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 10, // tri0
        7, 8, 9, // tri1
        11, 10, 12, // tri2
        10, 13, 12 // tri3
    ),
    gsSPNTriangles_5b(
        10, 14, 13, // tri0
        10, 9, 14, // tri1
        12, 13, 15, // tri2
        13, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 15, // tri0
        13, 18, 16, // tri1
        13, 14, 18, // tri2
        17, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        17, 16, 19, // tri0
        16, 21, 19, // tri1
        16, 18, 21, // tri2
        19, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 22, // tri0
        24, 23, 25, // tri1
        24, 25, 26, // tri2
        23, 22, 25 // tri3
    ),
    gsSPNTriangles_5b(
        22, 27, 25, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_2_v[60], 32, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 3, 0 // tri2
    ),
    gsSPNTriangles_5b(
        0, 5, 4, // tri0
        6, 4, 5, // tri1
        6, 5, 7, // tri2
        8, 6, 7 // tri3
    ),
    gsSPNTriangles_5b(
        9, 8, 7, // tri0
        9, 10, 8, // tri1
        11, 10, 9, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 12, // tri0
        13, 15, 16, // tri1
        15, 13, 10, // tri2
        17, 18, 14 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 21, // tri0
        20, 22, 21, // tri1
        19, 23, 20, // tri2
        19, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        22, 25, 21, // tri0
        22, 26, 25, // tri1
        26, 27, 25, // tri2
        27, 28, 25 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 25, // tri0
        28, 30, 29, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_2_v[91], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        3, 2, 4, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        0, 5, 6, // tri0
        5, 7, 8, // tri1
        7, 9, 8, // tri2
        1, 0, 10 // tri3
    ),
    gsSPNTriangles_5b(
        10, 0, 11, // tri0
        11, 0, 12, // tri1
        0, 6, 12, // tri2
        13, 9, 7 // tri3
    ),
    gsSPNTriangles_5b(
        14, 13, 3, // tri0
        4, 14, 3, // tri1
        15, 16, 17, // tri2
        15, 18, 16 // tri3
    ),
    gsSPNTriangles_5b(
        19, 18, 15, // tri0
        20, 9, 19, // tri1
        21, 22, 23, // tri2
        22, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        28, 29, 30, // tri1
        28, 31, 29, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_2_v[123], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 11, 12, // tri1
        2, 1, 13, // tri2
        14, 4, 15 // tri3
    ),
    gsSPNTriangles_5b(
        5, 4, 14, // tri0
        16, 11, 10, // tri1
        17, 11, 16, // tri2
        16, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 17, // tri0
        0, 19, 18, // tri1
        1, 3, 20, // tri2
        3, 21, 20 // tri3
    ),
    gsSPNTriangles_5b(
        22, 20, 21, // tri0
        13, 1, 23, // tri1
        24, 25, 26, // tri2
        27, 28, 29 // tri3
    ),
    gsSPNTriangles_5b(
        28, 30, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_2_v[154], 7, 0),
    gsSPNTrianglesInit_5b(
        3, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 5, 6 // tri2
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_2_v[161], 28, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        6, 8, 9, // tri1
        10, 11, 4, // tri2
        2, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        0, 13, 14, // tri0
        15, 16, 17, // tri1
        16, 18, 19, // tri2
        18, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        20, 22, 23, // tri0
        22, 24, 25, // tri1
        24, 26, 27, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_2_v[189], 32, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 8, 9, // tri0
        8, 3, 10, // tri1
        11, 12, 13, // tri2
        14, 11, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        19, 20, 21, // tri1
        22, 23, 24, // tri2
        25, 19, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 29, // tri0
        28, 30, 29, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_2_v[220], 15, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        0, 9, 1, // tri0
        10, 11, 12, // tri1
        11, 13, 14, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
