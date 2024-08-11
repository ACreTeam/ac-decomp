#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 stone_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_pk_1_v[] = {
#include "assets/field/bg/grd_s_f_pk_1_v.inc"
};

extern Gfx grd_s_f_pk_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_pk_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_pk_1_v[225], 11, 0),
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
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_pk_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        8, 10, 11, // tri1
        10, 5, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        19, 18, 14, // tri1
        20, 21, 22, // tri2
        23, 24, 21 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        28, 25, 27, // tri1
        17, 28, 27, // tri2
        29, 15, 30 // tri3
    ),
    gsSPNTriangles_5b(
        31, 29, 30, // tri0
        31, 30, 24, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_pk_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        8, 9, 7, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        12, 14, 13, // tri1
        14, 15, 13, // tri2
        11, 16, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 17, 16, // tri0
        17, 18, 16, // tri1
        3, 19, 4, // tri2
        19, 20, 4 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        21, 22, 20, // tri1
        21, 23, 22, // tri2
        24, 25, 15 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 15, // tri0
        25, 27, 26, // tri1
        27, 28, 26, // tri2
        27, 29, 28 // tri3
    ),
    gsSPNTriangles_5b(
        30, 31, 5, // tri0
        31, 6, 5, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_pk_1_v[64], 29, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        6, 7, 8, // tri1
        7, 9, 10, // tri2
        7, 11, 9 // tri3
    ),
    gsSPNTriangles_5b(
        8, 7, 10, // tri0
        12, 13, 14, // tri1
        15, 12, 14, // tri2
        14, 13, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 14, 16, // tri0
        16, 13, 18, // tri1
        18, 13, 19, // tri2
        11, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        21, 20, 22, // tri0
        22, 20, 23, // tri1
        24, 25, 26, // tri2
        25, 27, 26 // tri3
    ),
    gsSPNTriangles_5b(
        6, 28, 7, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_pk_1_v[93], 32, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 3, 7, // tri0
        8, 9, 10, // tri1
        11, 12, 13, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 19, // tri0
        20, 21, 22, // tri1
        23, 24, 25, // tri2
        26, 23, 25 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 29, // tri0
        28, 30, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_pk_1_v[125], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 4, 6, // tri0
        3, 4, 7, // tri1
        8, 9, 10, // tri2
        11, 8, 10 // tri3
    ),
    gsSPNTriangles_5b(
        5, 8, 11, // tri0
        9, 12, 13, // tri1
        13, 12, 14, // tri2
        12, 15, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        18, 19, 20, // tri1
        21, 18, 20, // tri2
        16, 18, 21 // tri3
    ),
    gsSPNTriangles_5b(
        19, 22, 23, // tri0
        23, 22, 24, // tri1
        22, 25, 24, // tri2
        26, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 26, 28, // tri0
        25, 26, 29, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_pk_1_v[155], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        2, 1, 3, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 5, 7, // tri1
        4, 5, 8, // tri2
        6, 9, 10 // tri3
    ),
    gsSPNTriangles_5b(
        10, 9, 11, // tri0
        9, 12, 11, // tri1
        13, 14, 15, // tri2
        15, 14, 16 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 17, // tri0
        14, 18, 16, // tri1
        16, 18, 19, // tri2
        18, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 22, // tri0
        21, 23, 24, // tri1
        23, 25, 26, // tri2
        27, 28, 29 // tri3
    ),
    gsSPNTriangles_5b(
        30, 27, 29, // tri0
        25, 27, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_pk_1_v[186], 28, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 1, 0, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        2, 4, 5, // tri0
        4, 6, 5, // tri1
        7, 8, 9, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        16, 17, 15, // tri1
        18, 19, 16, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 24, // tri0
        25, 18, 24, // tri1
        26, 27, 14, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_pk_1_v[214], 11, 0),
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
