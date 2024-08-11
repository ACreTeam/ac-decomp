#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_8_v[] = {
#include "assets/field/bg/grd_s_f_8_v.inc"
};

extern Gfx grd_s_f_8_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_8_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_8_v[168], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 3, 8, // tri0
        3, 4, 8, // tri1
        9, 10, 11, // tri2
        12, 9, 11 // tri3
    ),
    gsSPNTriangles_5b(
        1, 12, 13, // tri0
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
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_8_v[199], 11, 0),
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
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_8_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        27, // tri count
        0, 1, 2, // tri0
        2, 1, 3, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        6, 2, 3, // tri0
        6, 5, 2, // tri1
        7, 8, 9, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 8, 11, // tri0
        8, 12, 11, // tri1
        13, 7, 14, // tri2
        7, 15, 14 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 15, // tri0
        16, 17, 14, // tri1
        17, 13, 14, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        18, 21, 19, // tri0
        22, 21, 18, // tri1
        23, 21, 22, // tri2
        17, 23, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 17, 16, // tri0
        15, 9, 24, // tri1
        25, 26, 27, // tri2
        27, 28, 25 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 25, // tri0
        30, 31, 29, // tri1
        22, 18, 31, // tri2
        19, 24, 20 // tri3
    ),
    gsSPVertex(&grd_s_f_8_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        5, 11, 6, // tri1
        11, 12, 6, // tri2
        3, 1, 0 // tri3
    ),
    gsSPNTriangles_5b(
        13, 4, 3, // tri0
        13, 14, 4, // tri1
        14, 7, 4, // tri2
        13, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        13, 17, 15, // tri0
        17, 18, 15, // tri1
        17, 19, 18, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        24, 26, 25, // tri1
        26, 27, 25, // tri2
        28, 8, 29 // tri3
    ),
    gsSPNTriangles_5b(
        8, 10, 29, // tri0
        30, 12, 11, // tri1
        31, 14, 13, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_8_v[64], 4, 0),
    gsSPNTrianglesInit_5b(
        2, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_8_v[68], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        4, 6, 9, // tri1
        1, 10, 11, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        10, 12, 15, // tri0
        12, 14, 15, // tri1
        1, 11, 2, // tri2
        16, 9, 17 // tri3
    ),
    gsSPNTriangles_5b(
        5, 8, 6, // tri0
        7, 18, 19, // tri1
        18, 3, 20, // tri2
        21, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        13, 22, 23, // tri0
        22, 24, 25, // tri1
        26, 27, 28, // tri2
        27, 29, 28 // tri3
    ),
    gsSPVertex(&grd_s_f_8_v[98], 27, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        0, 3, 4, // tri1
        5, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        6, 5, 3, // tri0
        7, 8, 6, // tri1
        9, 10, 7, // tri2
        11, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        17, 14, 18, // tri1
        15, 19, 20, // tri2
        19, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        24, 17, 26, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_8_v[125], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        4, 9, 10, // tri0
        11, 3, 12, // tri1
        13, 14, 15, // tri2
        1, 11, 16 // tri3
    ),
    gsSPNTriangles_5b(
        13, 6, 14, // tri0
        9, 13, 15, // tri1
        11, 12, 16, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 22, // tri0
        21, 23, 24, // tri1
        18, 25, 26, // tri2
        25, 20, 27 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_8_v[156], 12, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        9, 0, 11, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
