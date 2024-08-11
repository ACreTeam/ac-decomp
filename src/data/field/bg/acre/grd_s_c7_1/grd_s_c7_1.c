#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c7_1_v[] = {
#include "assets/field/bg/grd_s_c7_1_v.inc"
};

extern Gfx grd_s_c7_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c7_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c7_1_v[195], 29, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        2, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 1, 7, // tri0
        8, 9, 10, // tri1
        11, 8, 10, // tri2
        4, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        8, 13, 9, // tri0
        13, 14, 15, // tri1
        16, 17, 18, // tri2
        19, 16, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 19, 22, // tri0
        23, 21, 24, // tri1
        25, 23, 26, // tri2
        27, 25, 28 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        38, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        0, 2, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 0, 6, // tri0
        0, 4, 6, // tri1
        7, 8, 9, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 9, // tri0
        12, 11, 10, // tri1
        12, 13, 11, // tri2
        12, 6, 13 // tri3
    ),
    gsSPNTriangles_5b(
        12, 5, 6, // tri0
        14, 5, 15, // tri1
        5, 12, 15, // tri2
        14, 0, 5 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 7, // tri0
        17, 8, 7, // tri1
        17, 18, 8, // tri2
        17, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        8, 20, 10, // tri0
        8, 18, 20, // tri1
        10, 15, 12, // tri2
        10, 20, 15 // tri3
    ),
    gsSPNTriangles_5b(
        0, 14, 3, // tri0
        14, 21, 3, // tri1
        1, 22, 23, // tri2
        1, 3, 22 // tri3
    ),
    gsSPNTriangles_5b(
        3, 24, 22, // tri0
        3, 21, 24, // tri1
        23, 25, 26, // tri2
        23, 22, 25 // tri3
    ),
    gsSPNTriangles_5b(
        22, 27, 25, // tri0
        22, 24, 27, // tri1
        26, 28, 29, // tri2
        26, 25, 28 // tri3
    ),
    gsSPNTriangles_5b(
        25, 30, 28, // tri0
        25, 27, 30, // tri1
        29, 28, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_1_v[32], 5, 0),
    gsSPNTrianglesInit_5b(
        3, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        0, 4, 3 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_1_v[37], 32, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        2, 5, 0, // tri0
        5, 6, 0, // tri1
        6, 7, 0, // tri2
        8, 9, 10 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 10, // tri0
        9, 12, 11, // tri1
        9, 13, 12, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 16, // tri0
        18, 19, 20, // tri1
        19, 21, 20, // tri2
        19, 18, 22 // tri3
    ),
    gsSPNTriangles_5b(
        18, 23, 22, // tri0
        16, 24, 14, // tri1
        24, 25, 14, // tri2
        24, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 28, // tri0
        29, 26, 28, // tri1
        28, 30, 29, // tri2
        31, 30, 28 // tri3
    ),
    gsSPVertex(&grd_s_c7_1_v[69], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 5 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        9, 11, 10, // tri1
        12, 13, 8, // tri2
        12, 6, 13 // tri3
    ),
    gsSPNTriangles_5b(
        12, 7, 6, // tri0
        14, 15, 16, // tri1
        15, 17, 16, // tri2
        0, 2, 18 // tri3
    ),
    gsSPNTriangles_5b(
        2, 19, 18, // tri0
        18, 20, 21, // tri1
        18, 19, 20, // tri2
        22, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        28, 14, 16, // tri1
        29, 30, 6, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_1_v[100], 16, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        3, 1, 0, // tri1
        4, 3, 0 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 3, // tri0
        3, 4, 5, // tri1
        6, 5, 7, // tri2
        6, 8, 3 // tri3
    ),
    gsSPNTriangles_5b(
        9, 8, 6, // tri0
        10, 8, 9, // tri1
        11, 12, 13, // tri2
        14, 15, 11 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_1_v[116], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        2, 3, 4, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        8, 9, 10, // tri1
        10, 11, 12, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        15, 18, 16, // tri1
        18, 19, 16, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        20, 23, 21, // tri0
        24, 25, 26, // tri1
        27, 15, 17, // tri2
        28, 29, 30 // tri3
    ),
    gsSPVertex(&grd_s_c7_1_v[147], 19, 0),
    gsSPNTrianglesInit_5b(
        9, // tri count
        0, 1, 2, // tri0
        3, 0, 2, // tri1
        3, 2, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 4, 6, // tri0
        7, 8, 9, // tri1
        10, 11, 12, // tri2
        13, 6, 11 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        17, 18, 15, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_1_v[166], 29, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 1, 5 // tri2
    ),
    gsSPNTriangles_5b(
        2, 6, 7, // tri0
        8, 9, 10, // tri1
        6, 11, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        13, 8, 14, // tri0
        11, 13, 15, // tri1
        16, 17, 18, // tri2
        19, 16, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 23, // tri0
        17, 21, 24, // tri1
        25, 26, 27, // tri2
        26, 19, 28 // tri3
    ),
    gsSPEndDisplayList(),
};
