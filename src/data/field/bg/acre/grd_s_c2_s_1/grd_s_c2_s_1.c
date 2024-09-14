#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c2_s_1_v[] = {
#include "assets/field/bg/grd_s_c2_s_1_v.inc"
};

extern Gfx grd_s_c2_s_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c2_s_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c2_s_1_v[246], 27, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 9, // tri1
        8, 10, 11, // tri2
        10, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        17, 14, 18, // tri1
        19, 17, 20, // tri2
        21, 19, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 21, 24, // tri0
        25, 23, 26, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c2_s_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        7, 8, 6, // tri1
        7, 9, 8, // tri2
        5, 10, 7 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        12, 14, 13, // tri1
        15, 16, 8, // tri2
        16, 6, 8 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 19, // tri0
        20, 18, 21, // tri1
        18, 22, 21, // tri2
        22, 23, 21 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 14, // tri0
        9, 13, 14, // tri1
        24, 25, 26, // tri2
        24, 27, 25 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 25, // tri0
        28, 29, 25, // tri1
        17, 30, 18, // tri2
        30, 22, 18 // tri3
    ),
    gsSPVertex(&grd_s_c2_s_1_v[31], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        8, 9, 10, // tri1
        9, 11, 10, // tri2
        9, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        16, 17, 18, // tri1
        19, 20, 21, // tri2
        22, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        23, 25, 24, // tri0
        2, 3, 25, // tri1
        26, 27, 28, // tri2
        0, 29, 1 // tri3
    ),
    gsSPNTriangles_5b(
        30, 31, 24, // tri0
        31, 22, 24, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_s_1_v[63], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        6, 7, 8, // tri1
        9, 10, 11, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        6, 13, 7, // tri0
        1, 14, 5, // tri1
        15, 16, 17, // tri2
        16, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 21, // tri0
        22, 23, 24, // tri1
        9, 25, 26, // tri2
        27, 28, 29 // tri3
    ),
    gsSPVertex(&grd_s_c2_s_1_v[93], 5, 0),
    gsSPNTrianglesInit_5b(
        3, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_s_1_v[98], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 4 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        6, 8, 7, // tri1
        9, 11, 12, // tri2
        11, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        13, 17, 14, // tri1
        18, 19, 20, // tri2
        15, 18, 16 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 22, // tri0
        21, 23, 24, // tri1
        23, 25, 24, // tri2
        26, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 26, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_s_1_v[129], 17, 0),
    gsSPNTrianglesInit_5b(
        8, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        1, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        9, 6, 10, // tri1
        7, 11, 12, // tri2
        11, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 9, 16, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c2_s_1_v[146], 32, 0),
    gsSPNTrianglesInit_5b(
        28, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 9, 10, // tri1
        8, 11, 9, // tri2
        10, 9, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 11, 8, // tri0
        13, 14, 11, // tri1
        14, 15, 11, // tri2
        9, 11, 16 // tri3
    ),
    gsSPNTriangles_5b(
        11, 17, 16, // tri0
        11, 15, 17, // tri1
        18, 12, 19, // tri2
        18, 10, 12 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 7, // tri0
        20, 22, 21, // tri1
        21, 5, 7, // tri2
        23, 2, 24 // tri3
    ),
    gsSPNTriangles_5b(
        23, 0, 2, // tri0
        3, 25, 4, // tri1
        25, 26, 4, // tri2
        25, 27, 26 // tri3
    ),
    gsSPNTriangles_5b(
        25, 28, 27, // tri0
        29, 0, 30, // tri1
        29, 3, 0, // tri2
        29, 25, 3 // tri3
    ),
    gsSPNTriangles_5b(
        29, 31, 25, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_s_1_v[178], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        7, 10, 8, // tri1
        10, 11, 8, // tri2
        11, 12, 8 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        13, 16, 14, // tri1
        16, 17, 14, // tri2
        17, 18, 14 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 18, // tri0
        17, 20, 19, // tri1
        20, 21, 19, // tri2
        21, 22, 19 // tri3
    ),
    gsSPNTriangles_5b(
        21, 23, 22, // tri0
        21, 24, 23, // tri1
        24, 25, 23, // tri2
        24, 26, 25 // tri3
    ),
    gsSPNTriangles_5b(
        24, 27, 26, // tri0
        27, 28, 26, // tri1
        15, 14, 29, // tri2
        14, 30, 29 // tri3
    ),
    gsSPNTriangles_5b(
        14, 18, 30, // tri0
        18, 19, 30, // tri1
        19, 31, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_s_1_v[210], 9, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        7, 8, 6, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_s_1_v[219], 27, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 0, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        7, 9, 10, // tri1
        1, 11, 12, // tri2
        11, 6, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        17, 14, 18, // tri1
        19, 20, 21, // tri2
        15, 19, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        24, 17, 26, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
