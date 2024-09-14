#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_2_v[] = {
#include "assets/field/bg/grd_s_f_2_v.inc"
};

extern Gfx grd_s_f_2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_2_v[157], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        11, 0, 12, // tri1
        9, 13, 14, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        16, 6, 18, // tri0
        13, 15, 19, // tri1
        16, 18, 17, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 21, // tri0
        13, 19, 14, // tri1
        4, 20, 22, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 23, 27, // tri0
        26, 27, 28, // tri1
        29, 28, 30, // tri2
        31, 29, 30 // tri3
    ),
    gsSPVertex(&grd_s_f_2_v[189], 23, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 0, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 7, 11, // tri1
        8, 12, 13, // tri2
        12, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        14, 16, 15, // tri0
        3, 5, 16, // tri1
        17, 18, 19, // tri2
        18, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        20, 22, 21, // tri0
        10, 11, 22, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        8, 9, 7, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        14, 15, 16, // tri1
        15, 17, 16, // tri2
        15, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        14, 19, 15, // tri0
        16, 20, 14, // tri1
        20, 21, 14, // tri2
        22, 4, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 2, 4, // tri0
        22, 23, 2, // tri1
        0, 24, 3, // tri2
        24, 25, 3 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 3, // tri0
        18, 27, 17, // tri1
        18, 28, 27, // tri2
        27, 29, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 30, 28, // tri0
        18, 9, 30, // tri1
        8, 30, 9, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_2_v[31], 16, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        0, 5, 4, // tri0
        0, 2, 6, // tri1
        2, 7, 6, // tri2
        6, 8, 9 // tri3
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        10, 11, 12, // tri1
        10, 13, 11, // tri2
        13, 9, 11 // tri3
    ),
    gsSPNTriangles_5b(
        11, 14, 15, // tri0
        9, 14, 11, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_2_v[47], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        11, 12, 13, // tri1
        14, 15, 16, // tri2
        17, 0, 18 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 15, // tri0
        19, 6, 20, // tri1
        4, 14, 16, // tri2
        11, 21, 12 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 22, // tri0
        21, 19, 22, // tri1
        9, 11, 13, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 28, // tri0
        29, 26, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_2_v[78], 22, 0),
    gsSPNTrianglesInit_5b(
        12, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        5, 8, 9, // tri0
        10, 9, 8, // tri1
        11, 10, 8, // tri2
        12, 13, 11 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 12, // tri0
        16, 17, 18, // tri1
        16, 19, 17, // tri2
        16, 18, 14 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 21, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_2_v[100], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        7, 9, 10, // tri0
        11, 12, 13, // tri1
        12, 14, 15, // tri2
        16, 0, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        4, 6, 21, // tri1
        14, 3, 22, // tri2
        14, 22, 15 // tri3
    ),
    gsSPNTriangles_5b(
        9, 18, 20, // tri0
        4, 21, 5, // tri1
        16, 17, 19, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 28, // tri0
        29, 26, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_2_v[131], 26, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 0, 9, // tri0
        3, 10, 11, // tri1
        12, 13, 14, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        8, 9, 21, // tri1
        22, 20, 23, // tri2
        12, 5, 13 // tri3
    ),
    gsSPNTriangles_5b(
        24, 22, 23, // tri0
        16, 21, 17, // tri1
        18, 25, 19, // tri2
        10, 14, 11 // tri3
    ),
    gsSPEndDisplayList(),
};
