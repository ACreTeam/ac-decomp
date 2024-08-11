#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c1_s_1_v[] = {
#include "assets/field/bg/grd_s_c1_s_1_v.inc"
};

extern Gfx grd_s_c1_s_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c1_s_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c1_s_1_v[193], 11, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 7, 10, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_s_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 3, 5 // tri2
    ),
    gsSPNTriangles_5b(
        3, 6, 5, // tri0
        7, 8, 9, // tri1
        7, 10, 8, // tri2
        10, 11, 8 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 14, // tri0
        15, 16, 1, // tri1
        15, 17, 16, // tri2
        17, 18, 16 // tri3
    ),
    gsSPNTriangles_5b(
        13, 19, 14, // tri0
        19, 20, 14, // tri1
        21, 22, 23, // tri2
        21, 24, 22 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 22, // tri0
        25, 26, 22, // tri1
        13, 12, 27, // tri2
        12, 28, 27 // tri3
    ),
    gsSPNTriangles_5b(
        12, 29, 28, // tri0
        30, 23, 31, // tri1
        30, 21, 23, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 11, 12, // tri1
        10, 13, 11, // tri2
        14, 8, 11 // tri3
    ),
    gsSPNTriangles_5b(
        15, 5, 16, // tri0
        5, 4, 16, // tri1
        17, 18, 19, // tri2
        18, 12, 19 // tri3
    ),
    gsSPNTriangles_5b(
        18, 10, 12, // tri0
        20, 21, 22, // tri1
        23, 24, 25, // tri2
        0, 26, 27 // tri3
    ),
    gsSPNTriangles_5b(
        28, 7, 29, // tri0
        30, 31, 23, // tri1
        31, 24, 23, // tri2
        30, 5, 31 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_1_v[64], 18, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 1, 8, // tri0
        1, 3, 8, // tri1
        9, 8, 3, // tri2
        10, 9, 3 // tri3
    ),
    gsSPNTriangles_5b(
        6, 11, 4, // tri0
        11, 12, 4, // tri1
        6, 13, 11, // tri2
        6, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        7, 13, 14, // tri0
        15, 16, 17, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_s_1_v[82], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 9, 10, // tri1
        9, 11, 10, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 14, // tri0
        16, 17, 7, // tri1
        17, 18, 7, // tri2
        19, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 19, 23, // tri0
        20, 24, 25, // tri1
        24, 26, 27, // tri2
        28, 29, 30 // tri3
    ),
    gsSPNTriangles_5b(
        28, 31, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_1_v[114], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 11, 7, // tri1
        12, 13, 14, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        21, 18, 22, // tri1
        23, 24, 25, // tri2
        26, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 15, 30, // tri0
        29, 30, 27, // tri1
        19, 26, 28, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c1_s_1_v[145], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        11, 3, 0, // tri1
        12, 11, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_s_1_v[158], 24, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        4, 8, 5, // tri1
        4, 9, 8, // tri2
        8, 10, 5 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 5, // tri0
        11, 7, 5, // tri1
        12, 13, 14, // tri2
        3, 14, 2 // tri3
    ),
    gsSPNTriangles_5b(
        3, 12, 14, // tri0
        15, 16, 12, // tri1
        15, 17, 16, // tri2
        17, 18, 16 // tri3
    ),
    gsSPNTriangles_5b(
        12, 16, 13, // tri0
        16, 18, 13, // tri1
        18, 19, 13, // tri2
        15, 12, 20 // tri3
    ),
    gsSPNTriangles_5b(
        12, 3, 20, // tri0
        1, 20, 3, // tri1
        17, 21, 18, // tri2
        21, 22, 18 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 18, // tri0
        23, 19, 18, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_s_1_v[182], 11, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 8, 9, // tri0
        8, 3, 10, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
