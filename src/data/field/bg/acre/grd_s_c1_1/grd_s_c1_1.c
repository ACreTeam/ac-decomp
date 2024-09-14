#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c1_1_v[] = {
#include "assets/field/bg/grd_s_c1_1_v.inc"
};

extern Gfx grd_s_c1_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c1_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c1_1_v[201], 29, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 4, 8, // tri0
        9, 7, 10, // tri1
        11, 9, 12, // tri2
        13, 11, 14 // tri3
    ),
    gsSPNTriangles_5b(
        0, 15, 16, // tri0
        17, 18, 19, // tri1
        18, 3, 20, // tri2
        3, 1, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 23, // tri0
        24, 21, 23, // tri1
        15, 24, 25, // tri2
        21, 26, 22 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 28, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        7, 9, 5, // tri1
        5, 4, 8, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        14, 7, 15, // tri1
        7, 16, 15, // tri2
        16, 17, 15 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        19, 21, 20, // tri1
        22, 23, 24, // tri2
        23, 25, 24 // tri3
    ),
    gsSPNTriangles_5b(
        26, 10, 12, // tri0
        27, 28, 29, // tri1
        28, 30, 29, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_1_v[31], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 2, 3, // tri0
        8, 9, 10, // tri1
        9, 1, 10, // tri2
        1, 0, 10 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        12, 14, 13, // tri1
        15, 16, 4, // tri2
        16, 5, 4 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 19, // tri0
        20, 21, 22, // tri1
        21, 23, 22, // tri2
        24, 17, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 28, // tri0
        27, 29, 28, // tri1
        30, 31, 29, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_1_v[63], 26, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 9, 10, // tri1
        8, 11, 9, // tri2
        12, 13, 4 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        17, 18, 19, // tri1
        20, 21, 8, // tri2
        22, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        23, 20, 24, // tri0
        25, 23, 22, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_1_v[89], 31, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        11, 10, 6, // tri1
        12, 9, 8, // tri2
        13, 2, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 14, 16, // tri0
        17, 16, 18, // tri1
        3, 1, 0, // tri2
        19, 7, 4 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 22, // tri0
        23, 20, 24, // tri1
        21, 25, 26, // tri2
        25, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 23, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_1_v[120], 32, 0),
    gsSPNTrianglesInit_5b(
        33, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        3, 5, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 4, // tri0
        1, 4, 2, // tri1
        4, 6, 2, // tri2
        6, 7, 2 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        8, 11, 9, // tri1
        9, 12, 10, // tri2
        13, 12, 14 // tri3
    ),
    gsSPNTriangles_5b(
        12, 9, 14, // tri0
        9, 11, 14, // tri1
        11, 15, 14, // tri2
        12, 13, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 19, // tri0
        17, 20, 18, // tri1
        20, 21, 18, // tri2
        22, 0, 23 // tri3
    ),
    gsSPNTriangles_5b(
        22, 1, 0, // tri0
        24, 12, 25, // tri1
        24, 10, 12, // tri2
        8, 26, 11 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 11, // tri0
        26, 22, 27, // tri1
        26, 28, 22, // tri2
        28, 1, 22 // tri3
    ),
    gsSPNTriangles_5b(
        28, 3, 1, // tri0
        5, 29, 6, // tri1
        5, 30, 29, // tri2
        30, 17, 29 // tri3
    ),
    gsSPNTriangles_5b(
        30, 20, 17, // tri0
        30, 31, 20, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_1_v[152], 20, 0),
    gsSPNTrianglesInit_5b(
        12, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        7, 10, 8, // tri1
        10, 11, 8, // tri2
        11, 12, 8 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        14, 16, 15, // tri1
        14, 17, 16, // tri2
        2, 3, 18 // tri3
    ),
    gsSPNTriangles_5b(
        3, 19, 18, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_1_v[172], 29, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        8, 10, 11, // tri1
        5, 12, 13, // tri2
        12, 7, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        18, 19, 20, // tri1
        21, 18, 22, // tri2
        16, 3, 23 // tri3
    ),
    gsSPNTriangles_5b(
        3, 1, 23, // tri0
        21, 22, 24, // tri1
        25, 21, 24, // tri2
        26, 25, 27 // tri3
    ),
    gsSPNTriangles_5b(
        0, 26, 28, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
