#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c1_2_v[] = {
#include "assets/field/bg/grd_s_c1_2_v.inc"
};

extern Gfx grd_s_c1_2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c1_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c1_2_v[222], 15, 0),
    gsSPNTrianglesInit_5b(
        8, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        1, 7, 8, // tri0
        7, 9, 8, // tri1
        9, 10, 11, // tri2
        10, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        12, 14, 13, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        2, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 7, 5, // tri1
        5, 3, 2, // tri2
        9, 10, 11 // tri3
    ),
    gsSPNTriangles_5b(
        9, 12, 10, // tri0
        10, 12, 13, // tri1
        12, 14, 13, // tri2
        14, 15, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 16, 15, // tri0
        17, 18, 19, // tri1
        20, 21, 22, // tri2
        17, 19, 23 // tri3
    ),
    gsSPNTriangles_5b(
        19, 24, 23, // tri0
        25, 26, 27, // tri1
        26, 28, 27, // tri2
        26, 29, 28 // tri3
    ),
    gsSPVertex(&grd_s_c1_2_v[30], 32, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 2, // tri0
        6, 7, 8, // tri1
        9, 10, 11, // tri2
        9, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        9, 13, 12, // tri0
        14, 15, 16, // tri1
        17, 18, 19, // tri2
        18, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 9, 19, // tri0
        20, 21, 9, // tri1
        21, 22, 9, // tri2
        22, 13, 9 // tri3
    ),
    gsSPNTriangles_5b(
        19, 23, 17, // tri0
        24, 11, 25, // tri1
        26, 27, 28, // tri2
        27, 29, 28 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        30, 29, 8, // tri1
        31, 30, 8, // tri2
        5, 31, 8 // tri3
    ),
    gsSPVertex(&grd_s_c1_2_v[62], 15, 0),
    gsSPNTrianglesInit_5b(
        12, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 0, // tri0
        7, 8, 9, // tri1
        7, 10, 8, // tri2
        11, 10, 7 // tri3
    ),
    gsSPNTriangles_5b(
        11, 6, 12, // tri0
        10, 11, 12, // tri1
        6, 5, 12, // tri2
        13, 12, 5 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 14, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_2_v[77], 32, 0),
    gsSPNTrianglesInit_5b(
        30, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        3, 8, 9, // tri1
        3, 4, 8, // tri2
        9, 10, 11 // tri3
    ),
    gsSPNTriangles_5b(
        9, 8, 10, // tri0
        12, 13, 14, // tri1
        12, 15, 13, // tri2
        11, 10, 12 // tri3
    ),
    gsSPNTriangles_5b(
        10, 15, 12, // tri0
        14, 13, 16, // tri1
        13, 17, 16, // tri2
        16, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        19, 18, 20, // tri1
        18, 21, 20, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        21, 7, 22, // tri0
        22, 7, 6, // tri1
        23, 24, 25, // tri2
        23, 5, 24 // tri3
    ),
    gsSPNTriangles_5b(
        6, 5, 23, // tri0
        25, 24, 26, // tri1
        24, 27, 26, // tri2
        26, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        27, 29, 28, // tri0
        28, 30, 31, // tri1
        28, 29, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_2_v[109], 28, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        2, 1, 4 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        6, 7, 8, // tri1
        7, 9, 8, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        5, 14, 4, // tri1
        7, 6, 14, // tri2
        14, 6, 4 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        17, 16, 9, // tri1
        15, 18, 16, // tri2
        16, 8, 9 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 16, // tri0
        20, 21, 22, // tri1
        22, 21, 19, // tri2
        19, 18, 22 // tri3
    ),
    gsSPNTriangles_5b(
        20, 23, 21, // tri0
        20, 24, 23, // tri1
        24, 25, 23, // tri2
        24, 26, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 10, 25, // tri0
        26, 27, 10, // tri1
        11, 10, 27, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_2_v[137], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        2, 3, 0, // tri1
        3, 4, 0 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 6, // tri0
        1, 7, 8, // tri1
        9, 6, 10, // tri2
        11, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 11, 15, // tri0
        16, 14, 15, // tri1
        15, 9, 16, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 18, // tri0
        22, 23, 21, // tri1
        22, 24, 23, // tri2
        24, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 26, // tri0
        27, 29, 28, // tri1
        29, 30, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_2_v[169], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        9, 6, 11, // tri1
        12, 13, 14, // tri2
        15, 12, 16 // tri3
    ),
    gsSPNTriangles_5b(
        13, 17, 18, // tri0
        17, 8, 19, // tri1
        20, 21, 22, // tri2
        21, 15, 23 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 10, // tri0
        15, 16, 23, // tri1
        24, 25, 26, // tri2
        27, 24, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 31, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_2_v[201], 6, 0),
    gsSPNTrianglesInit_5b(
        2, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_2_v[207], 15, 0),
    gsSPNTrianglesInit_5b(
        8, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 0, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        7, 4, 8, // tri1
        9, 10, 11, // tri2
        10, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        12, 6, 14, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
