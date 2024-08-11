#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c1_3_v[] = {
#include "assets/field/bg/grd_s_c1_3_v.inc"
};

extern Gfx grd_s_c1_3_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c1_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c1_3_v[203], 23, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 0, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 3, 7, // tri0
        8, 6, 9, // tri1
        10, 8, 11, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 12, 16, // tri0
        17, 15, 18, // tri1
        19, 17, 20, // tri2
        21, 19, 22 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        29, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 0, // tri0
        0, 2, 5, // tri1
        5, 7, 6, // tri2
        8, 9, 10 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 10, // tri0
        9, 12, 11, // tri1
        8, 13, 9, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        15, 4, 16, // tri0
        0, 17, 1, // tri1
        1, 16, 4, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        18, 21, 19, // tri0
        21, 22, 19, // tri1
        21, 23, 22, // tri2
        21, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        19, 14, 20, // tri0
        16, 20, 14, // tri1
        21, 18, 17, // tri2
        10, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 25, // tri0
        11, 27, 25, // tri1
        27, 28, 25, // tri2
        28, 29, 25 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 25, // tri0
        30, 26, 25, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_3_v[31], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 1, 6, // tri0
        1, 4, 6, // tri1
        7, 8, 9, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 9, // tri0
        12, 13, 11, // tri1
        12, 14, 13, // tri2
        13, 9, 11 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        16, 15, 18, // tri1
        19, 20, 21, // tri2
        22, 23, 21 // tri3
    ),
    gsSPNTriangles_5b(
        24, 10, 8, // tri0
        25, 26, 27, // tri1
        26, 28, 27, // tri2
        18, 29, 16 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 16, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_3_v[62], 12, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        3, 7, 6, // tri0
        6, 8, 4, // tri1
        9, 10, 11, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_3_v[74], 32, 0),
    gsSPNTrianglesInit_5b(
        39, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 2, // tri0
        1, 6, 3, // tri1
        6, 7, 3, // tri2
        7, 8, 3 // tri3
    ),
    gsSPNTriangles_5b(
        8, 4, 3, // tri0
        6, 9, 7, // tri1
        6, 10, 9, // tri2
        9, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 8, // tri0
        10, 12, 9, // tri1
        12, 13, 9, // tri2
        13, 14, 9 // tri3
    ),
    gsSPNTriangles_5b(
        14, 11, 9, // tri0
        12, 15, 13, // tri1
        12, 16, 15, // tri2
        15, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 14, // tri0
        16, 18, 15, // tri1
        18, 19, 15, // tri2
        19, 20, 15 // tri3
    ),
    gsSPNTriangles_5b(
        20, 17, 15, // tri0
        18, 21, 19, // tri1
        18, 22, 21, // tri2
        21, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        21, 23, 20, // tri0
        22, 24, 21, // tri1
        24, 25, 21, // tri2
        25, 26, 21 // tri3
    ),
    gsSPNTriangles_5b(
        26, 23, 21, // tri0
        24, 27, 25, // tri1
        24, 28, 27, // tri2
        28, 29, 27 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 27, // tri0
        30, 26, 27, // tri1
        26, 25, 27, // tri2
        28, 31, 29 // tri3
    ),
    gsSPVertex(&grd_s_c1_3_v[106], 5, 0),
    gsSPNTrianglesInit_5b(
        3, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_3_v[111], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
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
        28, 29, 23, // tri1
        30, 31, 26, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_3_v[143], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 0, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        5, 8, 9, // tri0
        8, 10, 11, // tri1
        8, 11, 9, // tri2
        10, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        12, 14, 15, // tri0
        14, 16, 17, // tri1
        16, 18, 19, // tri2
        16, 19, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 20, 21, // tri0
        22, 23, 24, // tri1
        25, 26, 23, // tri2
        27, 28, 26 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_3_v[174], 6, 0),
    gsSPNTrianglesInit_5b(
        2, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_3_v[180], 23, 0),
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
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 16, // tri0
        17, 18, 19, // tri1
        12, 20, 21, // tri2
        20, 14, 22 // tri3
    ),
    gsSPEndDisplayList(),
};
