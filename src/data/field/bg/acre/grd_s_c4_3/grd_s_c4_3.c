#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c4_3_v[] = {
#include "assets/field/bg/grd_s_c4_3_v.inc"
};

extern Gfx grd_s_c4_3_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c4_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c4_3_v[191], 26, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 6, // tri0
        5, 7, 6, // tri1
        7, 8, 6, // tri2
        9, 10, 11 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 14, // tri0
        13, 15, 14, // tri1
        0, 16, 17, // tri2
        16, 12, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        19, 8, 20, // tri1
        21, 9, 22, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 24, // tri0
        15, 23, 25, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        2, 4, 0 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        9, 10, 11, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 12, // tri0
        14, 15, 11, // tri1
        15, 9, 11, // tri2
        14, 11, 16 // tri3
    ),
    gsSPNTriangles_5b(
        11, 17, 16, // tri0
        17, 18, 16, // tri1
        19, 18, 17, // tri2
        19, 20, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        20, 22, 18, // tri1
        19, 23, 21, // tri2
        4, 5, 0 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 26, // tri0
        3, 27, 28, // tri1
        3, 1, 27, // tri2
        27, 29, 28 // tri3
    ),
    gsSPNTriangles_5b(
        22, 20, 30, // tri0
        31, 14, 16, // tri1
        6, 5, 4, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c4_3_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        2, 3, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 8, 7, // tri0
        5, 9, 6, // tri1
        1, 10, 11, // tri2
        1, 0, 10 // tri3
    ),
    gsSPNTriangles_5b(
        10, 12, 11, // tri0
        10, 13, 12, // tri1
        13, 14, 12, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 15, 17, // tri0
        19, 20, 21, // tri1
        22, 17, 23, // tri2
        17, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        15, 25, 16, // tri0
        17, 16, 24, // tri1
        15, 26, 25, // tri2
        15, 27, 26 // tri3
    ),
    gsSPNTriangles_5b(
        15, 28, 27, // tri0
        5, 29, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c4_3_v[63], 13, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 11, 12, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_3_v[76], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 4, 8, // tri0
        5, 9, 10, // tri1
        9, 11, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        14, 7, 16, // tri0
        17, 18, 19, // tri1
        20, 21, 18, // tri2
        22, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        20, 22, 21, // tri0
        23, 25, 26, // tri1
        25, 27, 28, // tri2
        13, 29, 30 // tri3
    ),
    gsSPNTriangles_5b(
        27, 30, 28, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c4_3_v[107], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        1, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 8, // tri1
        10, 11, 12, // tri2
        13, 10, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        15, 17, 9, // tri1
        16, 13, 18, // tri2
        19, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 24, // tri0
        25, 26, 22, // tri1
        27, 28, 25, // tri2
        27, 29, 28 // tri3
    ),
    gsSPNTriangles_5b(
        27, 30, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c4_3_v[138], 3, 0),
    gsSPNTrianglesInit_5b(
        1, // tri count
        0, 1, 2, // tri0
        0, 0, 0, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_3_v[141], 24, 0),
    gsSPNTrianglesInit_5b(
        28, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        0, 5, 3, // tri0
        6, 7, 8, // tri1
        6, 9, 7, // tri2
        7, 10, 8 // tri3
    ),
    gsSPNTriangles_5b(
        10, 4, 8, // tri0
        5, 11, 3, // tri1
        11, 12, 3, // tri2
        10, 2, 4 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        13, 9, 14, // tri1
        9, 6, 14, // tri2
        13, 16, 9 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 9, // tri0
        17, 18, 9, // tri1
        18, 7, 9, // tri2
        18, 10, 7 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 10, // tri0
        20, 2, 10, // tri1
        20, 0, 2, // tri2
        19, 20, 10 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 0, // tri0
        21, 22, 0, // tri1
        22, 5, 0, // tri2
        22, 11, 5 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 11, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_3_v[165], 26, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 6, // tri0
        5, 7, 6, // tri1
        7, 8, 6, // tri2
        9, 10, 11 // tri3
    ),
    gsSPNTriangles_5b(
        0, 12, 13, // tri0
        12, 14, 13, // tri1
        14, 15, 16, // tri2
        15, 17, 16 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        19, 8, 20, // tri1
        21, 9, 22, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        17, 23, 25, // tri0
        21, 22, 24, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
