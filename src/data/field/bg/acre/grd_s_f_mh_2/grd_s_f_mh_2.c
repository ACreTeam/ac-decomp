#include "libforest/gbi_extensions.h"

extern u8 earth_pal_dummy[];
extern u8 stone_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_mh_2_v[] = {
#include "assets/field/bg/grd_s_f_mh_2_v.inc"
};

extern Gfx grd_s_f_mh_2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_mh_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_mh_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 9, 10, // tri1
        9, 11, 10, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 12, // tri0
        16, 15, 17, // tri1
        18, 19, 20, // tri2
        21, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 26, // tri0
        26, 18, 27, // tri1
        28, 29, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_mh_2_v[31], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 1, 0, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 4, // tri0
        8, 9, 10, // tri1
        11, 9, 12, // tri2
        11, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        14, 16, 17, // tri1
        18, 19, 20, // tri2
        21, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 26, // tri0
        27, 21, 28, // tri1
        29, 30, 27, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_mh_2_v[62], 32, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        9, 11, 12, // tri1
        13, 14, 15, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        21, 22, 23, // tri1
        24, 25, 26, // tri2
        27, 28, 29 // tri3
    ),
    gsSPVertex(&grd_s_f_mh_2_v[92], 9, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 2, 7 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 6, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_mh_2_v[101], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        8, 9, 2, // tri1
        10, 11, 12, // tri2
        11, 13, 12 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        15, 17, 16, // tri1
        15, 18, 17, // tri2
        18, 19, 17 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 22, // tri0
        21, 23, 22, // tri1
        21, 20, 24, // tri2
        20, 25, 24 // tri3
    ),
    gsSPNTriangles_5b(
        7, 4, 26, // tri0
        4, 27, 26, // tri1
        28, 29, 30, // tri2
        28, 31, 29 // tri3
    ),
    gsSPNTriangles_5b(
        28, 7, 31, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_mh_2_v[133], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        8, 10, 11, // tri1
        10, 12, 11, // tri2
        11, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        12, 14, 13, // tri0
        12, 15, 14, // tri1
        15, 16, 14, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        18, 20, 19, // tri0
        19, 21, 16, // tri1
        22, 23, 24, // tri2
        22, 25, 23 // tri3
    ),
    gsSPNTriangles_5b(
        22, 26, 25, // tri0
        27, 28, 29, // tri1
        30, 28, 27, // tri2
        30, 31, 28 // tri3
    ),
    gsSPVertex(&grd_s_f_mh_2_v[165], 8, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 4, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_mh_2_v[173], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 4, 8, // tri0
        9, 10, 11, // tri1
        10, 7, 12, // tri2
        13, 9, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 13, 16, // tri0
        17, 15, 18, // tri1
        19, 20, 21, // tri2
        20, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 26, // tri0
        22, 24, 27, // tri1
        25, 28, 29, // tri2
        28, 30, 31 // tri3
    ),
    gsSPVertex(&grd_s_f_mh_2_v[205], 14, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 3 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 6, // tri0
        8, 10, 9, // tri1
        8, 11, 10, // tri2
        11, 12, 13 // tri3
    ),
    gsSPEndDisplayList(),
};
