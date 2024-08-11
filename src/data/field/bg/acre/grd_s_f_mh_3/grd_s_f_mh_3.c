#include "libforest/gbi_extensions.h"

extern u8 earth_pal_dummy[];
extern u8 stone_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_mh_3_v[] = {
#include "assets/field/bg/grd_s_f_mh_3_v.inc"
};

extern Gfx grd_s_f_mh_3_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_mh_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_mh_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        9, 10, 11, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        14, 16, 15, // tri1
        17, 18, 19, // tri2
        18, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 19, // tri0
        21, 22, 19, // tri1
        23, 13, 15, // tri2
        23, 24, 13 // tri3
    ),
    gsSPNTriangles_5b(
        3, 25, 4, // tri0
        25, 26, 4, // tri1
        9, 27, 28, // tri2
        9, 29, 27 // tri3
    ),
    gsSPNTriangles_5b(
        30, 31, 6, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_mh_3_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        7, 10, 8, // tri1
        10, 11, 12, // tri2
        11, 13, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 12, // tri0
        14, 15, 16, // tri1
        15, 17, 16, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 22, // tri0
        21, 23, 22, // tri1
        24, 25, 26, // tri2
        26, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        27, 1, 28, // tri0
        29, 30, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_mh_3_v[64], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 4, 0, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 8, 7, // tri0
        9, 5, 10, // tri1
        9, 11, 12, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_mh_3_v[77], 32, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        9, 10, 11, // tri2
        9, 0, 10 // tri3
    ),
    gsSPNTriangles_5b(
        9, 1, 0, // tri0
        12, 13, 14, // tri1
        8, 15, 7, // tri2
        16, 9, 17 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 17, // tri0
        6, 18, 8, // tri1
        18, 19, 8, // tri2
        20, 16, 14 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 14, // tri0
        17, 21, 14, // tri1
        22, 3, 23, // tri2
        6, 24, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 18, 25, // tri0
        18, 12, 25, // tri1
        20, 14, 13, // tri2
        26, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        27, 29, 28, // tri0
        4, 3, 22, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_mh_3_v[107], 13, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 2, 1 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        2, 4, 6, // tri1
        6, 7, 8, // tri2
        6, 4, 7 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        11, 10, 12, // tri1
        10, 8, 12, // tri2
        8, 7, 12 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_mh_3_v[120], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 9, 10, // tri1
        11, 12, 9, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 15, 12, // tri0
        17, 18, 19, // tri1
        20, 21, 18, // tri2
        22, 19, 14 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        26, 6, 27, // tri1
        28, 29, 7, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_mh_3_v[150], 26, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        5, 2, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        1, 0, 3, // tri1
        10, 11, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        12, 19, 10, // tri1
        20, 18, 19, // tri2
        11, 10, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 21, 23, // tri0
        24, 15, 25, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
