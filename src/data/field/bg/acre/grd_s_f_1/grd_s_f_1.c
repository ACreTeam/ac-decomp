#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_1_v[] = {
#include "assets/field/bg/grd_s_f_1_v.inc"
};

extern Gfx grd_s_f_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_1_v[146], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        3, 4, 6, // tri0
        8, 9, 10, // tri1
        9, 5, 7, // tri2
        11, 8, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 11, 14, // tri0
        13, 14, 15, // tri1
        16, 17, 18, // tri2
        17, 13, 15 // tri3
    ),
    gsSPNTriangles_5b(
        19, 16, 20, // tri0
        21, 19, 22, // tri1
        16, 18, 20, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 23, 27, // tri0
        28, 26, 29, // tri1
        30, 28, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_1_v[178], 5, 0),
    gsSPNTrianglesInit_5b(
        2, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        0, 0, 0 // tri2
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        5, 4, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        8, 10, 9, // tri1
        8, 7, 11, // tri2
        7, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        13, 16, 14, // tri1
        17, 10, 18, // tri2
        10, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        1, 20, 2, // tri0
        21, 22, 0, // tri1
        16, 13, 22, // tri2
        14, 19, 15 // tri3
    ),
    gsSPNTriangles_5b(
        12, 23, 11, // tri0
        24, 25, 23, // tri1
        26, 27, 28, // tri2
        20, 3, 29 // tri3
    ),
    gsSPNTriangles_5b(
        26, 6, 27, // tri0
        6, 4, 27, // tri1
        24, 23, 12, // tri2
        30, 28, 25 // tri3
    ),
    gsSPNTriangles_5b(
        2, 20, 31, // tri0
        20, 29, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_1_v[32], 31, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        2, 3, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 9, 6, // tri1
        9, 10, 11, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        18, 19, 12, // tri1
        20, 21, 15, // tri2
        22, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 22, // tri0
        24, 19, 22, // tri1
        25, 26, 27, // tri2
        27, 26, 28 // tri3
    ),
    gsSPNTriangles_5b(
        26, 23, 28, // tri0
        29, 25, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_1_v[63], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 4 // tri2
    ),
    gsSPNTriangles_5b(
        8, 3, 5, // tri0
        9, 10, 11, // tri1
        12, 13, 14, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 17, 13, // tri0
        18, 15, 17, // tri1
        10, 12, 14, // tri2
        10, 14, 11 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 19, // tri0
        0, 8, 1, // tri1
        3, 6, 4, // tri2
        20, 21, 7 // tri3
    ),
    gsSPNTriangles_5b(
        22, 19, 21, // tri0
        23, 24, 16, // tri1
        25, 26, 24, // tri2
        27, 28, 29 // tri3
    ),
    gsSPNTriangles_5b(
        30, 27, 31, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_1_v[95], 10, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 8, 9, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_1_v[105], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 5, 9, // tri0
        10, 8, 11, // tri1
        12, 13, 14, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 12, 19, // tri0
        6, 20, 21, // tri1
        20, 22, 21, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 22, // tri0
        16, 26, 17, // tri1
        23, 15, 24, // tri2
        27, 10, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 27, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_1_v[136], 10, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 8, 9, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
