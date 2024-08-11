#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_7_v[] = {
#include "assets/field/bg/grd_s_f_7_v.inc"
};

extern Gfx grd_s_f_7_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_7_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_7_v[249], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 10, // tri1
        9, 11, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        14, 16, 15, // tri0
        17, 18, 19, // tri1
        20, 17, 21, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        26, 27, 28, // tri1
        24, 22, 25, // tri2
        29, 30, 31 // tri3
    ),
    gsSPVertex(&grd_s_f_7_v[281], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 11, 3, // tri1
        8, 12, 9, // tri2
        13, 4, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 12, // tri0
        17, 18, 19, // tri1
        18, 0, 20, // tri2
        21, 7, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        26, 27, 28, // tri1
        29, 26, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_7_v[312], 27, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        1, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 8, 9, // tri0
        10, 11, 12, // tri1
        3, 5, 11, // tri2
        6, 9, 7 // tri3
    ),
    gsSPNTriangles_5b(
        13, 10, 12, // tri0
        14, 15, 16, // tri1
        17, 14, 18, // tri2
        19, 17, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 19, 22, // tri0
        23, 21, 24, // tri1
        25, 23, 26, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_7_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 1, // tri0
        6, 3, 1, // tri1
        7, 8, 9, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        14, 15, 4, // tri1
        14, 16, 15, // tri2
        16, 17, 15 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        19, 21, 20, // tri1
        12, 20, 21, // tri2
        20, 22, 18 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        24, 26, 25, // tri1
        27, 28, 29, // tri2
        30, 4, 3 // tri3
    ),
    gsSPVertex(&grd_s_f_7_v[31], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 4, // tri0
        8, 4, 7, // tri1
        9, 8, 10, // tri2
        10, 11, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 9, // tri0
        13, 6, 5, // tri1
        14, 13, 5, // tri2
        14, 5, 15 // tri3
    ),
    gsSPNTriangles_5b(
        12, 16, 9, // tri0
        17, 12, 18, // tri1
        19, 20, 21, // tri2
        15, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        24, 15, 23, // tri0
        25, 26, 27, // tri1
        27, 22, 25, // tri2
        25, 28, 26 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        29, 31, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_7_v[63], 22, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        8, 6, 5, // tri1
        9, 10, 11, // tri2
        11, 10, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        16, 17, 18, // tri1
        3, 19, 20, // tri2
        10, 21, 12 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_7_v[85], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        9, 7, 10, // tri2
        9, 11, 7 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 14, // tri0
        12, 15, 13, // tri1
        16, 13, 17, // tri2
        16, 18, 13 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 21, // tri0
        22, 23, 24, // tri1
        14, 22, 25, // tri2
        26, 18, 27 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_7_v[116], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        7, 10, 11, // tri1
        12, 11, 10, // tri2
        13, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 13, // tri0
        16, 17, 14, // tri1
        18, 19, 20, // tri2
        21, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 26, // tri0
        27, 24, 28, // tri1
        29, 30, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_7_v[148], 7, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 5, 1 // tri2
    ),
    gsSPNTriangles_5b(
        6, 0, 2, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_7_v[155], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        0, 7, 8, // tri0
        7, 9, 10, // tri1
        11, 12, 13, // tri2
        12, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 4, 17, // tri0
        18, 19, 20, // tri1
        14, 2, 21, // tri2
        14, 21, 15 // tri3
    ),
    gsSPNTriangles_5b(
        9, 18, 20, // tri0
        16, 17, 19, // tri1
        22, 23, 24, // tri2
        25, 22, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 29, // tri0
        23, 27, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_7_v[186], 32, 0),
    gsSPNTrianglesInit_5b(
        12, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        11, 8, 12, // tri1
        13, 14, 15, // tri2
        14, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        21, 22, 23, // tri1
        24, 13, 25, // tri2
        26, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        16, 29, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_7_v[217], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        0, 12, 1, // tri1
        13, 5, 14, // tri2
        15, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        19, 20, 21, // tri1
        22, 19, 23, // tri2
        24, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        25, 27, 28, // tri0
        20, 29, 30, // tri1
        29, 24, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
