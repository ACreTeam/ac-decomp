#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_9_v[] = {
#include "assets/field/bg/grd_s_f_9_v.inc"
};

extern Gfx grd_s_f_9_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_9_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_9_v[186], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 8, 9, // tri0
        10, 3, 11, // tri1
        12, 5, 13, // tri2
        14, 12, 15 // tri3
    ),
    gsSPNTriangles_5b(
        8, 16, 9, // tri0
        8, 14, 16, // tri1
        10, 11, 17, // tri2
        18, 10, 17 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 21, // tri0
        20, 22, 21, // tri1
        23, 24, 25, // tri2
        26, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        19, 26, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_9_v[216], 31, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
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
        19, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        20, 17, 22, // tri0
        17, 18, 22, // tri1
        23, 24, 25, // tri2
        26, 23, 25 // tri3
    ),
    gsSPNTriangles_5b(
        15, 26, 27, // tri0
        23, 28, 24, // tri1
        28, 29, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_9_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 9, 10, // tri1
        8, 11, 9, // tri2
        2, 3, 12 // tri3
    ),
    gsSPNTriangles_5b(
        3, 13, 12, // tri0
        13, 14, 12, // tri1
        12, 14, 15, // tri2
        14, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 15, // tri0
        18, 19, 20, // tri1
        19, 21, 22, // tri2
        22, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        21, 23, 22, // tri0
        23, 21, 24, // tri1
        24, 5, 23, // tri2
        25, 23, 5 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 23, // tri0
        26, 27, 23, // tri1
        26, 28, 27, // tri2
        27, 28, 29 // tri3
    ),
    gsSPNTriangles_5b(
        30, 29, 28, // tri0
        31, 29, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_9_v[32], 31, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 5, // tri0
        8, 9, 10, // tri1
        9, 11, 10, // tri2
        9, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 11, // tri0
        12, 14, 13, // tri1
        14, 2, 15, // tri2
        16, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 16, // tri0
        20, 21, 16, // tri1
        21, 22, 16, // tri2
        21, 23, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 22, // tri0
        24, 25, 22, // tri1
        24, 7, 25, // tri2
        24, 5, 7 // tri3
    ),
    gsSPNTriangles_5b(
        26, 18, 17, // tri0
        2, 1, 27, // tri1
        28, 29, 15, // tri2
        15, 30, 28 // tri3
    ),
    gsSPNTriangles_5b(
        30, 26, 28, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_9_v[63], 32, 0),
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
        18, 16, 19, // tri1
        20, 21, 22, // tri2
        14, 20, 23 // tri3
    ),
    gsSPNTriangles_5b(
        21, 24, 25, // tri0
        24, 26, 27, // tri1
        28, 29, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_9_v[94], 30, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        0, 3, 1 // tri2
    ),
    gsSPNTriangles_5b(
        4, 6, 7, // tri0
        6, 8, 9, // tri1
        10, 11, 12, // tri2
        8, 12, 9 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        10, 13, 11, // tri1
        14, 16, 17, // tri2
        16, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        18, 20, 19, // tri0
        21, 22, 23, // tri1
        24, 21, 25, // tri2
        26, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        26, 28, 20, // tri0
        27, 24, 29, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_9_v[124], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
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
        25, 26, 27 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_9_v[155], 31, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        9, 3, 10, // tri0
        6, 11, 7, // tri1
        1, 6, 8, // tri2
        3, 5, 10 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 14, // tri0
        13, 15, 16, // tri1
        17, 12, 18, // tri2
        19, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        20, 22, 21, // tri0
        15, 23, 24, // tri1
        25, 26, 27, // tri2
        17, 18, 28 // tri3
    ),
    gsSPNTriangles_5b(
        20, 25, 22, // tri0
        29, 17, 28, // tri1
        26, 29, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
