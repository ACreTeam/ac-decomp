#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c1_s_4_v[] = {
#include "assets/field/bg/grd_s_c1_s_4_v.inc"
};

extern Gfx grd_s_c1_s_4_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c1_s_4_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c1_s_4_v[248], 16, 0),
    gsSPNTrianglesInit_5b(
        8, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        1, 10, 11, // tri1
        10, 7, 11, // tri2
        8, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        12, 14, 15, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_s_4_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        7, 8, 5, // tri1
        9, 10, 11, // tri2
        12, 13, 10 // tri3
    ),
    gsSPNTriangles_5b(
        8, 14, 5, // tri0
        14, 15, 5, // tri1
        15, 16, 5, // tri2
        16, 6, 5 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 17, // tri0
        3, 18, 19, // tri1
        18, 20, 19, // tri2
        18, 21, 20 // tri3
    ),
    gsSPNTriangles_5b(
        4, 22, 7, // tri0
        22, 23, 7, // tri1
        4, 24, 22, // tri2
        12, 4, 13 // tri3
    ),
    gsSPNTriangles_5b(
        24, 4, 12, // tri0
        25, 7, 23, // tri1
        26, 27, 28, // tri2
        29, 30, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 28, 31, // tri0
        28, 27, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_4_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 2, 3 // tri2
    ),
    gsSPNTriangles_5b(
        2, 4, 5, // tri0
        6, 7, 8, // tri1
        6, 8, 9, // tri2
        10, 6, 11 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 12, // tri0
        7, 6, 10, // tri1
        7, 10, 13, // tri2
        7, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 13, 16, // tri0
        17, 14, 13, // tri1
        17, 13, 15, // tri2
        18, 9, 8 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 9, // tri0
        20, 18, 21, // tri1
        20, 19, 18, // tri2
        22, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        28, 29, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_4_v[63], 28, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        6, 9, 7, // tri0
        7, 1, 8, // tri1
        1, 0, 8, // tri2
        7, 10, 1 // tri3
    ),
    gsSPNTriangles_5b(
        7, 11, 10, // tri0
        10, 12, 1, // tri1
        13, 14, 15, // tri2
        16, 14, 9 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 13, // tri0
        17, 19, 18, // tri1
        19, 20, 18, // tri2
        20, 21, 18 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 23, // tri0
        22, 24, 23, // tri1
        20, 22, 21, // tri2
        20, 25, 22 // tri3
    ),
    gsSPNTriangles_5b(
        26, 25, 27, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_s_4_v[91], 16, 0),
    gsSPNTrianglesInit_5b(
        8, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 8, 7, // tri0
        8, 3, 9, // tri1
        10, 11, 12, // tri2
        11, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 5, 15, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_s_4_v[107], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        11, 6, 12, // tri1
        13, 14, 15, // tri2
        16, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        14, 19, 20, // tri0
        19, 8, 21, // tri1
        22, 16, 23, // tri2
        24, 2, 25 // tri3
    ),
    gsSPNTriangles_5b(
        0, 22, 1, // tri0
        26, 27, 28, // tri1
        29, 26, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_4_v[138], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        4, 8, 9, // tri0
        8, 10, 11, // tri1
        12, 13, 14, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 15, 19, // tri0
        13, 20, 21, // tri1
        20, 18, 22, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        16, 23, 26, // tri0
        24, 27, 28, // tri1
        27, 29, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_4_v[169], 32, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 3, 8, // tri0
        9, 10, 11, // tri1
        10, 5, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 15, 17, // tri0
        18, 19, 20, // tri1
        21, 22, 19, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 28, // tri0
        29, 30, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_4_v[201], 3, 0),
    gsSPNTrianglesInit_5b(
        1, // tri count
        0, 1, 2, // tri0
        0, 0, 0, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_s_4_v[204], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 8, // tri0
        4, 8, 5, // tri1
        7, 9, 10, // tri2
        7, 4, 9 // tri3
    ),
    gsSPNTriangles_5b(
        7, 11, 8, // tri0
        12, 13, 14, // tri1
        15, 13, 12, // tri2
        16, 15, 12 // tri3
    ),
    gsSPNTriangles_5b(
        17, 12, 18, // tri0
        17, 18, 19, // tri1
        18, 12, 14, // tri2
        18, 14, 20 // tri3
    ),
    gsSPNTriangles_5b(
        2, 3, 18, // tri0
        3, 19, 18, // tri1
        2, 20, 21, // tri2
        2, 18, 20 // tri3
    ),
    gsSPNTriangles_5b(
        0, 22, 1, // tri0
        21, 23, 2, // tri1
        23, 0, 2, // tri2
        23, 24, 0 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        28, 29, 27, // tri1
        29, 25, 27, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_4_v[234], 14, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        1, 3, 7, // tri0
        1, 8, 2, // tri1
        9, 10, 8, // tri2
        10, 2, 8 // tri3
    ),
    gsSPNTriangles_5b(
        11, 8, 12, // tri0
        11, 9, 8, // tri1
        12, 8, 13, // tri2
        8, 1, 13 // tri3
    ),
    gsSPEndDisplayList(),
};
