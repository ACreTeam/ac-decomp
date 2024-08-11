#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c6_1_v[] = {
#include "assets/field/bg/grd_s_c6_1_v.inc"
};

extern Gfx grd_s_c6_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c6_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c6_1_v[209], 28, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 6, // tri0
        7, 3, 8, // tri1
        9, 10, 11, // tri2
        12, 9, 11 // tri3
    ),
    gsSPNTriangles_5b(
        5, 12, 13, // tri0
        9, 14, 10, // tri1
        14, 15, 16, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 17, 21, // tri0
        22, 20, 23, // tri1
        24, 22, 25, // tri2
        26, 24, 27 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c6_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        0, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 2, // tri0
        6, 5, 1, // tri1
        7, 8, 9, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 9, // tri0
        8, 12, 10, // tri1
        12, 13, 10, // tri2
        13, 14, 10 // tri3
    ),
    gsSPNTriangles_5b(
        7, 15, 8, // tri0
        15, 16, 8, // tri1
        17, 18, 19, // tri2
        18, 13, 19 // tri3
    ),
    gsSPNTriangles_5b(
        13, 12, 19, // tri0
        20, 21, 22, // tri1
        20, 23, 21, // tri2
        23, 17, 21 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 26, // tri0
        24, 27, 25, // tri1
        27, 28, 25, // tri2
        25, 29, 26 // tri3
    ),
    gsSPVertex(&grd_s_c6_1_v[30], 32, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        4, 8, 5, // tri1
        7, 9, 10, // tri2
        9, 11, 10 // tri3
    ),
    gsSPNTriangles_5b(
        12, 4, 13, // tri0
        12, 8, 4, // tri1
        14, 15, 16, // tri2
        14, 17, 15 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 15, // tri0
        19, 20, 2, // tri1
        20, 0, 2, // tri2
        19, 2, 21 // tri3
    ),
    gsSPNTriangles_5b(
        2, 14, 21, // tri0
        14, 16, 21, // tri1
        22, 23, 24, // tri2
        22, 20, 23 // tri3
    ),
    gsSPNTriangles_5b(
        23, 25, 24, // tri0
        9, 7, 5, // tri1
        26, 27, 28, // tri2
        26, 29, 27 // tri3
    ),
    gsSPNTriangles_5b(
        26, 30, 29, // tri0
        30, 31, 29, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c6_1_v[62], 19, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        2, 1, 3, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 6, // tri0
        1, 0, 5, // tri1
        5, 7, 6, // tri2
        5, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        7, 8, 12, // tri1
        8, 13, 12, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 17, // tri0
        14, 18, 17, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c6_1_v[81], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        5, 8, 7, // tri1
        8, 9, 7, // tri2
        0, 2, 10 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        14, 15, 16, // tri1
        13, 12, 17, // tri2
        15, 18, 16 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 18, // tri0
        21, 22, 23, // tri1
        24, 11, 23, // tri2
        11, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 11, // tri0
        29, 30, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c6_1_v[112], 30, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 4, 0, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 5, // tri0
        9, 10, 11, // tri1
        9, 12, 10, // tri2
        13, 14, 12 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 14, // tri0
        17, 18, 16, // tri1
        8, 7, 18, // tri2
        19, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 24, // tri0
        25, 26, 27, // tri1
        28, 29, 21, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c6_1_v[142], 28, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 9, 10, // tri1
        9, 11, 12, // tri2
        6, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 8, 15, // tri0
        16, 3, 17, // tri1
        4, 18, 19, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        18, 23, 24, // tri0
        25, 26, 27, // tri1
        25, 20, 26, // tri2
        23, 25, 27 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c6_1_v[170], 32, 0),
    gsSPNTrianglesInit_5b(
        38, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        4, 8, 9, // tri1
        8, 10, 9, // tri2
        8, 11, 10 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 10, // tri0
        5, 13, 14, // tri1
        5, 15, 13, // tri2
        14, 16, 5 // tri3
    ),
    gsSPNTriangles_5b(
        5, 4, 15, // tri0
        4, 9, 15, // tri1
        17, 1, 18, // tri2
        1, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 18, // tri0
        21, 22, 19, // tri1
        22, 20, 19, // tri2
        21, 23, 22 // tri3
    ),
    gsSPNTriangles_5b(
        24, 4, 6, // tri0
        21, 25, 23, // tri1
        24, 11, 8, // tri2
        24, 26, 11 // tri3
    ),
    gsSPNTriangles_5b(
        26, 2, 11, // tri0
        2, 3, 11, // tri1
        3, 27, 11, // tri2
        27, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        7, 5, 16, // tri0
        24, 8, 4, // tri1
        28, 7, 16, // tri2
        3, 17, 27 // tri3
    ),
    gsSPNTriangles_5b(
        3, 1, 17, // tri0
        0, 29, 1, // tri1
        29, 19, 1, // tri2
        19, 29, 30 // tri3
    ),
    gsSPNTriangles_5b(
        21, 31, 25, // tri0
        19, 30, 21, // tri1
        30, 31, 21, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c6_1_v[202], 7, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        2, 3, 4, // tri1
        3, 5, 4 // tri2
    ),
    gsSPNTriangles_5b(
        1, 3, 2, // tri0
        1, 6, 3, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
