#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_10_v[] = {
#include "assets/field/bg/grd_s_f_10_v.inc"
};

extern Gfx grd_s_f_10_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_10_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_10_v[172], 22, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 7, 10, // tri1
        11, 12, 13, // tri2
        14, 11, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 14, 17, // tri0
        18, 16, 19, // tri1
        20, 18, 21, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_10_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        4, 5, 1 // tri2
    ),
    gsSPNTriangles_5b(
        6, 5, 7, // tri0
        8, 9, 10, // tri1
        9, 11, 10, // tri2
        9, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 9, // tri0
        15, 16, 14, // tri1
        17, 18, 16, // tri2
        17, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 19, // tri0
        22, 21, 23, // tri1
        24, 25, 26, // tri2
        25, 22, 26 // tri3
    ),
    gsSPNTriangles_5b(
        24, 27, 25, // tri0
        28, 29, 27, // tri1
        30, 29, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_10_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        10, 12, 13, // tri1
        13, 12, 14, // tri2
        12, 15, 14 // tri3
    ),
    gsSPNTriangles_5b(
        14, 2, 1, // tri0
        0, 2, 16, // tri1
        16, 17, 18, // tri2
        19, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 24, // tri0
        14, 15, 3, // tri1
        15, 4, 3, // tri2
        25, 26, 27 // tri3
    ),
    gsSPNTriangles_5b(
        26, 4, 15, // tri0
        26, 28, 4, // tri1
        25, 29, 30, // tri2
        30, 26, 25 // tri3
    ),
    gsSPNTriangles_5b(
        28, 26, 30, // tri0
        25, 31, 29, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_10_v[64], 16, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        2, 1, 3, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 11, 12, // tri1
        13, 14, 15, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_10_v[80], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 8, 9, // tri0
        8, 6, 10, // tri1
        11, 12, 13, // tri2
        14, 11, 15 // tri3
    ),
    gsSPNTriangles_5b(
        12, 16, 17, // tri0
        16, 18, 19, // tri1
        20, 21, 22, // tri2
        21, 14, 23 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 26, // tri0
        27, 24, 28, // tri1
        25, 29, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_10_v[111], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 5, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        1, 11, 12, // tri1
        13, 14, 15, // tri2
        16, 17, 14 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        16, 18, 17, // tri1
        11, 13, 15, // tri2
        13, 16, 14 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 23, // tri0
        21, 24, 25, // tri1
        26, 25, 24, // tri2
        27, 26, 24 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 27, // tri0
        30, 31, 28, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_10_v[143], 7, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        0, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 6, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_10_v[150], 22, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 8, 9, // tri0
        8, 3, 10, // tri1
        11, 12, 13, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 18, // tri0
        12, 19, 20, // tri1
        19, 14, 21, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
