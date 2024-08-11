#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c6_2_v[] = {
#include "assets/field/bg/grd_s_c6_2_v.inc"
};

extern Gfx grd_s_c6_2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c6_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c6_2_v[220], 28, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 4, 6, // tri0
        8, 9, 5, // tri1
        10, 7, 11, // tri2
        12, 0, 13 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 2, // tri0
        14, 15, 16, // tri1
        17, 13, 18, // tri2
        15, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        19, 18, 20, // tri0
        14, 16, 21, // tri1
        22, 23, 24, // tri2
        25, 21, 23 // tri3
    ),
    gsSPNTriangles_5b(
        22, 25, 23, // tri0
        26, 24, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c6_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        3, 7, 6, // tri0
        3, 8, 7, // tri1
        8, 9, 7, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        12, 14, 13, // tri1
        12, 15, 14, // tri2
        16, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 18, // tri0
        20, 21, 22, // tri1
        23, 20, 22, // tri2
        23, 24, 20 // tri3
    ),
    gsSPNTriangles_5b(
        24, 23, 25, // tri0
        23, 26, 25, // tri1
        23, 27, 28, // tri2
        29, 30, 14 // tri3
    ),
    gsSPNTriangles_5b(
        31, 30, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c6_2_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        7, 10, 9, // tri1
        7, 11, 10, // tri2
        11, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        16, 17, 18, // tri1
        17, 19, 20, // tri2
        19, 21, 20 // tri3
    ),
    gsSPNTriangles_5b(
        22, 18, 17, // tri0
        23, 24, 25, // tri1
        24, 26, 27, // tri2
        26, 28, 27 // tri3
    ),
    gsSPNTriangles_5b(
        26, 29, 28, // tri0
        8, 3, 6, // tri1
        30, 5, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c6_2_v[64], 21, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        12, 13, 14, // tri1
        14, 15, 16, // tri2
        15, 17, 16 // tri3
    ),
    gsSPNTriangles_5b(
        18, 17, 19, // tri0
        18, 16, 17, // tri1
        20, 18, 19, // tri2
        8, 18, 20 // tri3
    ),
    gsSPNTriangles_5b(
        8, 7, 18, // tri0
        15, 14, 13, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c6_2_v[85], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        8, 9, 10, // tri1
        9, 11, 10, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        2, 3, 15, // tri0
        11, 5, 16, // tri1
        11, 16, 10, // tri2
        13, 15, 14 // tri3
    ),
    gsSPNTriangles_5b(
        0, 17, 18, // tri0
        17, 9, 19, // tri1
        6, 20, 21, // tri2
        20, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 26, // tri0
        25, 27, 28, // tri1
        27, 29, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c6_2_v[116], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        7, 10, 8, // tri1
        11, 12, 8, // tri2
        12, 13, 8 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        17, 18, 15, // tri1
        17, 19, 18, // tri2
        19, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        20, 22, 21, // tri0
        23, 24, 22, // tri1
        25, 9, 24, // tri2
        13, 26, 27 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c6_2_v[147], 9, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c6_2_v[156], 32, 0),
    gsSPNTrianglesInit_5b(
        38, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 0, 6, // tri0
        0, 2, 6, // tri1
        3, 7, 8, // tri2
        3, 0, 7 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        9, 10, 8, // tri1
        9, 11, 10, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        12, 15, 13, // tri0
        13, 16, 14, // tri1
        13, 17, 16, // tri2
        15, 18, 13 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 13, // tri0
        19, 17, 13, // tri1
        19, 20, 17, // tri2
        18, 2, 19 // tri3
    ),
    gsSPNTriangles_5b(
        18, 6, 2, // tri0
        2, 20, 19, // tri1
        2, 4, 20, // tri2
        5, 7, 0 // tri3
    ),
    gsSPNTriangles_5b(
        5, 21, 7, // tri0
        21, 22, 7, // tri1
        22, 9, 7, // tri2
        22, 11, 9 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 11, // tri0
        23, 24, 11, // tri1
        24, 25, 11, // tri2
        25, 10, 11 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 10, // tri0
        24, 27, 25, // tri1
        24, 28, 27, // tri2
        27, 29, 25 // tri3
    ),
    gsSPNTriangles_5b(
        29, 26, 25, // tri0
        28, 30, 27, // tri1
        30, 31, 27, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c6_2_v[188], 4, 0),
    gsSPNTrianglesInit_5b(
        2, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c6_2_v[192], 28, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        8, 10, 9, // tri1
        7, 9, 5, // tri2
        11, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        16, 13, 15, // tri1
        17, 18, 14, // tri2
        11, 16, 12 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 3, // tri0
        21, 2, 18, // tri1
        19, 22, 20, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        22, 26, 27, // tri0
        26, 25, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
