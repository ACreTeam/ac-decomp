#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c2_s_3_v[] = {
#include "assets/field/bg/grd_s_c2_s_3_v.inc"
};

extern Gfx grd_s_c2_s_3_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c2_s_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c2_s_3_v[204], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 7, 10, // tri1
        11, 9, 12, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c2_s_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        31, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        3, 2, 5, // tri0
        2, 6, 5, // tri1
        6, 7, 5, // tri2
        2, 4, 8 // tri3
    ),
    gsSPNTriangles_5b(
        2, 8, 6, // tri0
        7, 6, 9, // tri1
        7, 9, 10, // tri2
        6, 8, 11 // tri3
    ),
    gsSPNTriangles_5b(
        6, 11, 9, // tri0
        10, 9, 12, // tri1
        10, 12, 13, // tri2
        9, 11, 14 // tri3
    ),
    gsSPNTriangles_5b(
        9, 14, 12, // tri0
        13, 12, 15, // tri1
        13, 15, 16, // tri2
        12, 14, 17 // tri3
    ),
    gsSPNTriangles_5b(
        12, 17, 15, // tri0
        16, 15, 18, // tri1
        15, 19, 18, // tri2
        19, 20, 18 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 21, // tri0
        15, 21, 19, // tri1
        22, 23, 24, // tri2
        22, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        23, 26, 27, // tri0
        23, 27, 24, // tri1
        28, 29, 30, // tri2
        28, 30, 31 // tri3
    ),
    gsSPVertex(&grd_s_c2_s_3_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        34, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        2, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        2, 6, 4, // tri0
        6, 7, 4, // tri1
        7, 8, 4, // tri2
        7, 9, 8 // tri3
    ),
    gsSPNTriangles_5b(
        7, 10, 9, // tri0
        10, 11, 9, // tri1
        10, 12, 11, // tri2
        12, 13, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 11, // tri0
        1, 6, 2, // tri1
        1, 15, 6, // tri2
        15, 16, 7 // tri3
    ),
    gsSPNTriangles_5b(
        15, 7, 6, // tri0
        16, 17, 10, // tri1
        16, 10, 7, // tri2
        17, 18, 10 // tri3
    ),
    gsSPNTriangles_5b(
        18, 12, 10, // tri0
        18, 13, 12, // tri1
        18, 19, 13, // tri2
        19, 20, 13 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        21, 22, 20, // tri1
        22, 23, 20, // tri2
        13, 24, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 20, 24, // tri0
        20, 25, 24, // tri1
        20, 26, 25, // tri2
        20, 23, 26 // tri3
    ),
    gsSPNTriangles_5b(
        23, 27, 26, // tri0
        28, 29, 30, // tri1
        29, 31, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_s_3_v[64], 13, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        3, 2, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 6, 7, // tri0
        6, 8, 9, // tri1
        6, 9, 7, // tri2
        9, 8, 10 // tri3
    ),
    gsSPNTriangles_5b(
        8, 2, 10, // tri0
        2, 11, 10, // tri1
        11, 2, 3, // tri2
        11, 3, 12 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c2_s_3_v[77], 32, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 3, // tri0
        4, 6, 5, // tri1
        7, 8, 9, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 10, // tri0
        12, 9, 10, // tri1
        13, 14, 15, // tri2
        15, 14, 16 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 15, // tri0
        18, 17, 19, // tri1
        16, 19, 17, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        20, 22, 23, // tri0
        22, 24, 25, // tri1
        22, 25, 23, // tri2
        24, 26, 25 // tri3
    ),
    gsSPNTriangles_5b(
        24, 27, 26, // tri0
        27, 28, 26, // tri1
        20, 2, 3, // tri2
        20, 3, 21 // tri3
    ),
    gsSPNTriangles_5b(
        29, 8, 7, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_s_3_v[107], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        3, 8, 4, // tri1
        9, 10, 11, // tri2
        12, 9, 11 // tri3
    ),
    gsSPNTriangles_5b(
        8, 3, 13, // tri0
        14, 15, 16, // tri1
        14, 17, 15, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        18, 20, 21, // tri0
        21, 22, 18, // tri1
        16, 23, 24, // tri2
        15, 23, 16 // tri3
    ),
    gsSPNTriangles_5b(
        18, 25, 26, // tri0
        25, 27, 26, // tri1
        26, 19, 18, // tri2
        28, 29, 30 // tri3
    ),
    gsSPNTriangles_5b(
        29, 31, 30, // tri0
        31, 2, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_s_3_v[139], 23, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        5, 1, 0, // tri0
        6, 4, 0, // tri1
        7, 8, 9, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        7, 11, 8, // tri0
        7, 12, 11, // tri1
        12, 13, 11, // tri2
        14, 6, 15 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        17, 18, 19, // tri1
        17, 16, 18, // tri2
        6, 0, 15 // tri3
    ),
    gsSPNTriangles_5b(
        2, 20, 21, // tri0
        15, 22, 16, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_s_3_v[162], 29, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 8, 9, // tri0
        8, 6, 10, // tri1
        11, 12, 13, // tri2
        12, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        15, 17, 16, // tri1
        15, 18, 17, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 3, // tri0
        3, 22, 23, // tri1
        23, 24, 25, // tri2
        25, 26, 27 // tri3
    ),
    gsSPNTriangles_5b(
        26, 28, 27, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_s_3_v[191], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 8, // tri0
        9, 10, 11, // tri1
        10, 3, 12, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
