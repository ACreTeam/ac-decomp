#include "libforest/gbi_extensions.h"

extern u8 earth_pal_dummy[];
extern u8 stone_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_mh_1_v[] = {
#include "assets/field/bg/grd_s_f_mh_1_v.inc"
};

extern Gfx grd_s_f_mh_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_mh_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_mh_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        8, 9, 10, // tri1
        8, 11, 9, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 14, // tri0
        16, 10, 17, // tri1
        17, 10, 9, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 18, // tri0
        20, 23, 24, // tri1
        24, 25, 26, // tri2
        27, 28, 29 // tri3
    ),
    gsSPNTriangles_5b(
        30, 31, 27, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_mh_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        2, 3, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 5, // tri0
        7, 10, 11, // tri1
        11, 12, 13, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        19, 20, 16, // tri1
        18, 21, 22, // tri2
        22, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        26, 28, 27, // tri1
        29, 30, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_mh_1_v[64], 32, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        12, 13, 10, // tri1
        14, 15, 16, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 22, // tri0
        23, 24, 25, // tri1
        26, 27, 28, // tri2
        29, 30, 26 // tri3
    ),
    gsSPVertex(&grd_s_f_mh_1_v[95], 9, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        2, 3, 4, // tri1
        5, 6, 0 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 5, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_mh_1_v[104], 32, 0),
    gsSPNTrianglesInit_5b(
        29, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 9, 5, // tri1
        8, 5, 4, // tri2
        10, 8, 4 // tri3
    ),
    gsSPNTriangles_5b(
        11, 4, 12, // tri0
        4, 6, 12, // tri1
        6, 13, 12, // tri2
        6, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        16, 15, 17, // tri1
        15, 18, 17, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        18, 20, 19, // tri0
        18, 21, 20, // tri1
        22, 23, 15, // tri2
        22, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        15, 23, 18, // tri0
        23, 24, 25, // tri1
        24, 0, 25, // tri2
        25, 0, 26 // tri3
    ),
    gsSPNTriangles_5b(
        0, 2, 26, // tri0
        1, 27, 3, // tri1
        1, 28, 27, // tri2
        28, 29, 27 // tri3
    ),
    gsSPNTriangles_5b(
        30, 27, 31, // tri0
        27, 29, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_mh_1_v[136], 16, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        2, 1, 3, // tri1
        3, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        3, 1, 4, // tri0
        6, 3, 5, // tri1
        7, 8, 9, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        10, 12, 11, // tri1
        8, 12, 10, // tri2
        13, 14, 11 // tri3
    ),
    gsSPNTriangles_5b(
        15, 1, 14, // tri0
        15, 4, 1, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_mh_1_v[152], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 3, 8, // tri0
        9, 5, 10, // tri1
        11, 9, 12, // tri2
        13, 11, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        16, 18, 19, // tri1
        20, 21, 22, // tri2
        18, 20, 23 // tri3
    ),
    gsSPNTriangles_5b(
        21, 24, 25, // tri0
        24, 26, 27, // tri1
        28, 29, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_mh_1_v[183], 21, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 0, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 11, 12, // tri1
        11, 3, 13, // tri2
        0, 2, 6 // tri3
    ),
    gsSPNTriangles_5b(
        3, 5, 13, // tri0
        7, 9, 14, // tri1
        15, 14, 16, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        18, 15, 16, // tri0
        8, 10, 20, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
