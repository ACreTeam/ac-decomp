#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c4_s_1_v[] = {
#include "assets/field/bg/grd_s_c4_s_1_v.inc"
};

extern Gfx grd_s_c4_s_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c4_s_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c4_s_1_v[196], 17, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        4, 8, 5, // tri1
        9, 10, 7, // tri2
        2, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 3, 14, // tri0
        11, 15, 16, // tri1
        15, 8, 16, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_s_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 0, // tri0
        6, 7, 0, // tri1
        7, 1, 0, // tri2
        8, 5, 9 // tri3
    ),
    gsSPNTriangles_5b(
        5, 0, 9, // tri0
        1, 7, 10, // tri1
        7, 11, 10, // tri2
        11, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 10, // tri0
        12, 14, 13, // tri1
        3, 15, 4, // tri2
        3, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 4, // tri0
        2, 9, 0, // tri1
        3, 18, 16, // tri2
        3, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 22, // tri0
        21, 23, 22, // tri1
        23, 24, 22, // tri2
        25, 26, 27 // tri3
    ),
    gsSPNTriangles_5b(
        26, 28, 27, // tri0
        29, 30, 2, // tri1
        28, 31, 27, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c4_s_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        3, 1, 0, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        3, 6, 5, // tri1
        7, 8, 6, // tri2
        8, 5, 6 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        10, 11, 12, // tri1
        0, 13, 14, // tri2
        13, 15, 14 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 15, // tri0
        16, 18, 17, // tri1
        18, 19, 20, // tri2
        21, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        22, 24, 23, // tri0
        24, 9, 23, // tri1
        9, 25, 23, // tri2
        9, 7, 25 // tri3
    ),
    gsSPNTriangles_5b(
        24, 26, 9, // tri0
        24, 27, 26, // tri1
        22, 28, 24, // tri2
        29, 30, 31 // tri3
    ),
    gsSPNTriangles_5b(
        0, 30, 3, // tri0
        0, 14, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c4_s_1_v[64], 10, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        1, 0, 3, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        0, 4, 6, // tri0
        7, 8, 9, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_s_1_v[74], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 0, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        7, 9, 8, // tri1
        2, 10, 11, // tri2
        8, 12, 5 // tri3
    ),
    gsSPNTriangles_5b(
        6, 13, 14, // tri0
        15, 16, 17, // tri1
        18, 15, 19, // tri2
        20, 18, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 24, // tri0
        16, 22, 25, // tri1
        23, 26, 27, // tri2
        26, 28, 29 // tri3
    ),
    gsSPNTriangles_5b(
        28, 30, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c4_s_1_v[105], 11, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 8, 9, // tri0
        8, 6, 10, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_s_1_v[116], 32, 0),
    gsSPNTrianglesInit_5b(
        27, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        5, 6, 4, // tri1
        6, 5, 7, // tri2
        8, 6, 7 // tri3
    ),
    gsSPNTriangles_5b(
        0, 2, 9, // tri0
        2, 10, 9, // tri1
        10, 11, 9, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        12, 15, 16, // tri0
        12, 16, 13, // tri1
        12, 14, 17, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        18, 21, 19, // tri0
        22, 23, 18, // tri1
        22, 24, 23, // tri2
        17, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        17, 14, 25, // tri0
        27, 28, 29, // tri1
        28, 30, 29, // tri2
        11, 31, 27 // tri3
    ),
    gsSPNTriangles_5b(
        11, 10, 31, // tri0
        26, 20, 19, // tri1
        26, 25, 20, // tri2
        21, 18, 23 // tri3
    ),
    gsSPVertex(&grd_s_c4_s_1_v[148], 31, 0),
    gsSPNTrianglesInit_5b(
        28, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 0, 5 // tri2
    ),
    gsSPNTriangles_5b(
        0, 2, 5, // tri0
        6, 5, 7, // tri1
        6, 4, 5, // tri2
        8, 6, 7 // tri3
    ),
    gsSPNTriangles_5b(
        8, 7, 9, // tri0
        10, 8, 9, // tri1
        10, 9, 11, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        16, 17, 18, // tri1
        18, 17, 19, // tri2
        17, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 23, // tri0
        24, 21, 23, // tri1
        24, 23, 25, // tri2
        24, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 24, 26, // tri0
        27, 26, 16, // tri1
        28, 27, 18, // tri2
        27, 16, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 28, 18, // tri0
        19, 29, 28, // tri1
        30, 13, 15, // tri2
        22, 21, 30 // tri3
    ),
    gsSPNTriangles_5b(
        15, 22, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_s_1_v[179], 17, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        4, 8, 5, // tri1
        9, 10, 7, // tri2
        11, 3, 12 // tri3
    ),
    gsSPNTriangles_5b(
        2, 13, 14, // tri0
        13, 15, 16, // tri1
        15, 8, 16, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
