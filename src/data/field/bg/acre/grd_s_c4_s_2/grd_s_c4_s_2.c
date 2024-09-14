#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c4_s_2_v[] = {
#include "assets/field/bg/grd_s_c4_s_2_v.inc"
};

extern Gfx grd_s_c4_s_2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c4_s_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c4_s_2_v[234], 21, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        3, 4, 2, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 5, 7, // tri0
        1, 3, 2, // tri1
        9, 10, 11, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        0, 7, 1, // tri0
        15, 12, 14, // tri1
        16, 17, 13, // tri2
        16, 9, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 15, 19, // tri0
        8, 18, 20, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_s_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        5, 8, 6, // tri1
        5, 9, 8, // tri2
        5, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 9, // tri0
        12, 13, 14, // tri1
        13, 15, 14, // tri2
        14, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        16, 18, 17, // tri0
        18, 19, 17, // tri1
        20, 19, 21, // tri2
        19, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 22, // tri0
        19, 23, 22, // tri1
        17, 19, 20, // tri2
        25, 11, 10 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 11, // tri0
        21, 27, 20, // tri1
        28, 29, 30, // tri2
        29, 31, 30 // tri3
    ),
    gsSPVertex(&grd_s_c4_s_2_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        3, 4, 0, // tri1
        5, 6, 3 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 3, // tri0
        8, 9, 10, // tri1
        9, 11, 10, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 1, 14, // tri0
        1, 15, 14, // tri1
        1, 16, 15, // tri2
        16, 17, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 18, 17, // tri0
        19, 20, 21, // tri1
        19, 21, 22, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 24, 27, // tri0
        26, 27, 19, // tri1
        28, 26, 19, // tri2
        28, 19, 22 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 31, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c4_s_2_v[64], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        6, 8, 9, // tri1
        10, 6, 9, // tri2
        11, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 11, 13, // tri0
        15, 16, 17, // tri1
        15, 17, 18, // tri2
        16, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        17, 16, 20, // tri0
        21, 20, 22, // tri1
        21, 17, 20, // tri2
        23, 18, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        26, 28, 29, // tri1
        29, 27, 26, // tri2
        3, 30, 2 // tri3
    ),
    gsSPNTriangles_5b(
        3, 5, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c4_s_2_v[95], 3, 0),
    gsSPNTrianglesInit_5b(
        1, // tri count
        0, 1, 2, // tri0
        0, 0, 0, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_s_2_v[98], 29, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 4, 8, // tri0
        5, 9, 10, // tri1
        9, 11, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        14, 7, 16, // tri0
        17, 18, 19, // tri1
        17, 20, 18, // tri2
        18, 21, 19 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 2, // tri0
        20, 24, 22, // tri1
        21, 25, 26, // tri2
        3, 27, 28 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_s_2_v[127], 32, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        3, 0, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        7, 8, 6, // tri1
        9, 10, 11, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 12, // tri0
        17, 15, 18, // tri1
        19, 20, 18, // tri2
        20, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        11, 21, 22, // tri0
        21, 23, 22, // tri1
        24, 23, 21, // tri2
        24, 25, 23 // tri3
    ),
    gsSPNTriangles_5b(
        26, 24, 10, // tri0
        24, 21, 10, // tri1
        27, 10, 28, // tri2
        27, 26, 10 // tri3
    ),
    gsSPNTriangles_5b(
        29, 27, 13, // tri0
        27, 28, 13, // tri1
        30, 13, 31, // tri2
        30, 29, 13 // tri3
    ),
    gsSPVertex(&grd_s_c4_s_2_v[159], 32, 0),
    gsSPNTrianglesInit_5b(
        27, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 2, 5 // tri2
    ),
    gsSPNTriangles_5b(
        4, 0, 2, // tri0
        4, 5, 6, // tri1
        7, 4, 6, // tri2
        7, 6, 8 // tri3
    ),
    gsSPNTriangles_5b(
        9, 7, 8, // tri0
        10, 11, 12, // tri1
        13, 10, 14, // tri2
        15, 13, 16 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 16, // tri0
        3, 15, 17, // tri1
        2, 3, 17, // tri2
        5, 2, 18 // tri3
    ),
    gsSPNTriangles_5b(
        8, 6, 19, // tri0
        20, 9, 19, // tri1
        9, 8, 19, // tri2
        21, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        22, 24, 23, // tri0
        24, 25, 23, // tri1
        24, 26, 25, // tri2
        24, 27, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 26, // tri0
        28, 29, 26, // tri1
        28, 30, 29, // tri2
        28, 31, 30 // tri3
    ),
    gsSPVertex(&grd_s_c4_s_2_v[191], 22, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        3, 5, 4 // tri2
    ),
    gsSPNTriangles_5b(
        3, 6, 5, // tri0
        7, 8, 9, // tri1
        8, 10, 9, // tri2
        10, 11, 9 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 14, // tri0
        12, 15, 13, // tri1
        15, 16, 13, // tri2
        16, 17, 13 // tri3
    ),
    gsSPNTriangles_5b(
        16, 0, 17, // tri0
        16, 18, 0, // tri1
        18, 19, 0, // tri2
        19, 20, 3 // tri3
    ),
    gsSPNTriangles_5b(
        20, 6, 3, // tri0
        20, 21, 6, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_s_2_v[213], 21, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        3, 4, 2, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 5, 7, // tri0
        1, 3, 2, // tri1
        9, 10, 11, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 12, 14, // tri0
        0, 7, 1, // tri1
        16, 17, 13, // tri2
        16, 9, 17 // tri3
    ),
    gsSPNTriangles_5b(
        8, 18, 19, // tri0
        18, 15, 20, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
