#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c3_1_v[] = {
#include "assets/field/bg/grd_s_c3_1_v.inc"
};

extern Gfx grd_s_c3_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c3_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c3_1_v[221], 23, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 7, 10, // tri1
        11, 9, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 13, 17, // tri0
        0, 16, 18, // tri1
        19, 0, 20, // tri2
        21, 19, 22 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c3_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        5, 8, 6, // tri1
        9, 10, 11, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 4, 6, // tri0
        13, 14, 4, // tri1
        13, 15, 16, // tri2
        15, 17, 16 // tri3
    ),
    gsSPNTriangles_5b(
        18, 16, 17, // tri0
        14, 13, 19, // tri1
        20, 21, 22, // tri2
        21, 23, 22 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 26, // tri0
        25, 27, 26, // tri1
        25, 28, 27, // tri2
        25, 29, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 28, // tri0
        29, 31, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c3_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 0, // tri1
        5, 6, 3 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        8, 10, 9, // tri1
        11, 12, 13, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 19, // tri0
        17, 20, 18, // tri1
        21, 22, 23, // tri2
        21, 24, 22 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        26, 28, 29, // tri1
        28, 17, 29, // tri2
        8, 30, 10 // tri3
    ),
    gsSPNTriangles_5b(
        30, 31, 10, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c3_1_v[64], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        0, 3, 4, // tri1
        2, 1, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        9, 10, 11, // tri1
        10, 12, 11, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 14, 13, // tri0
        15, 17, 18, // tri1
        19, 20, 6, // tri2
        19, 21, 20 // tri3
    ),
    gsSPNTriangles_5b(
        19, 22, 21, // tri0
        23, 24, 25, // tri1
        26, 27, 28, // tri2
        22, 29, 21 // tri3
    ),
    gsSPNTriangles_5b(
        30, 31, 29, // tri0
        22, 30, 29, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c3_1_v[96], 32, 0),
    gsSPNTrianglesInit_5b(
        32, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 2, 6, // tri0
        5, 0, 2, // tri1
        0, 7, 1, // tri2
        7, 8, 1 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        10, 12, 11, // tri1
        13, 14, 15, // tri2
        14, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        14, 17, 16, // tri0
        18, 19, 13, // tri1
        5, 20, 21, // tri2
        5, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        21, 12, 10, // tri0
        21, 10, 22, // tri1
        9, 23, 24, // tri2
        23, 19, 24 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 18, // tri0
        23, 9, 11, // tri1
        17, 25, 16, // tri2
        17, 26, 25 // tri3
    ),
    gsSPNTriangles_5b(
        5, 27, 20, // tri0
        27, 28, 20, // tri1
        18, 24, 19, // tri2
        7, 9, 29 // tri3
    ),
    gsSPNTriangles_5b(
        7, 29, 8, // tri0
        9, 24, 30, // tri1
        9, 30, 29, // tri2
        24, 18, 31 // tri3
    ),
    gsSPNTriangles_5b(
        24, 31, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c3_1_v[128], 9, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        5, 6, 4, // tri1
        5, 7, 8, // tri2
        5, 8, 6 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_1_v[137], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        2, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 0, // tri0
        8, 9, 6, // tri1
        10, 11, 8, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 12, // tri0
        13, 14, 15, // tri1
        16, 17, 18, // tri2
        19, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 19, 23, // tri0
        24, 25, 26, // tri1
        27, 28, 29, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c3_1_v[167], 30, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 5, 1 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        9, 0, 2, // tri1
        10, 11, 12, // tri2
        11, 13, 12 // tri3
    ),
    gsSPNTriangles_5b(
        6, 8, 14, // tri0
        13, 6, 14, // tri1
        15, 10, 16, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 22, // tri0
        23, 24, 20, // tri1
        25, 26, 23, // tri2
        27, 28, 25 // tri3
    ),
    gsSPNTriangles_5b(
        19, 29, 27, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_1_v[197], 24, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 8, 9, // tri0
        8, 3, 10, // tri1
        11, 12, 13, // tri2
        14, 11, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        12, 16, 19, // tri1
        20, 21, 22, // tri2
        21, 14, 23 // tri3
    ),
    gsSPEndDisplayList(),
};
