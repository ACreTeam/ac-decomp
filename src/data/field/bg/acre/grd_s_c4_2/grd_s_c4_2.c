#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c4_2_v[] = {
#include "assets/field/bg/grd_s_c4_2_v.inc"
};

extern Gfx grd_s_c4_2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c4_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c4_2_v[229], 15, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 7, 10, // tri1
        11, 9, 12, // tri2
        13, 11, 14 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        5, 9, 3, // tri0
        10, 11, 3, // tri1
        12, 13, 14, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        18, 20, 21, // tri1
        18, 21, 22, // tri2
        22, 21, 15 // tri3
    ),
    gsSPNTriangles_5b(
        1, 0, 23, // tri0
        24, 25, 26, // tri1
        8, 27, 6, // tri2
        28, 29, 9 // tri3
    ),
    gsSPVertex(&grd_s_c4_2_v[30], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        11, 12, 13, // tri1
        14, 8, 10, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 10, 19, // tri0
        18, 20, 10, // tri1
        19, 10, 21, // tri2
        20, 14, 10 // tri3
    ),
    gsSPNTriangles_5b(
        6, 22, 23, // tri0
        6, 7, 22, // tri1
        4, 24, 25, // tri2
        6, 23, 26 // tri3
    ),
    gsSPNTriangles_5b(
        25, 5, 4, // tri0
        27, 28, 29, // tri1
        26, 30, 6, // tri2
        17, 31, 15 // tri3
    ),
    gsSPVertex(&grd_s_c4_2_v[62], 31, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        11, 12, 13, // tri1
        14, 15, 16, // tri2
        17, 14, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 21, // tri0
        19, 21, 22, // tri1
        20, 15, 21, // tri2
        14, 16, 18 // tri3
    ),
    gsSPNTriangles_5b(
        5, 4, 7, // tri0
        23, 24, 25, // tri1
        24, 26, 25, // tri2
        26, 27, 25 // tri3
    ),
    gsSPNTriangles_5b(
        27, 2, 25, // tri0
        28, 29, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_2_v[93], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 4, 6, // tri0
        8, 9, 10, // tri1
        9, 11, 12, // tri2
        11, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 16, // tri0
        15, 17, 18, // tri1
        19, 20, 21, // tri2
        5, 22, 6 // tri3
    ),
    gsSPNTriangles_5b(
        22, 0, 6, // tri0
        23, 24, 25, // tri1
        26, 23, 27, // tri2
        23, 25, 27 // tri3
    ),
    gsSPNTriangles_5b(
        24, 28, 25, // tri0
        19, 21, 29, // tri1
        17, 30, 31, // tri2
        19, 26, 20 // tri3
    ),
    gsSPVertex(&grd_s_c4_2_v[125], 10, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 7, 9, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_2_v[135], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 2, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 2, // tri0
        6, 7, 8, // tri1
        9, 10, 11, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 13, // tri0
        17, 18, 19, // tri1
        20, 5, 4, // tri2
        21, 22, 19 // tri3
    ),
    gsSPNTriangles_5b(
        18, 21, 19, // tri0
        19, 20, 4, // tri1
        17, 19, 4, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        11, 26, 23, // tri0
        11, 27, 26, // tri1
        28, 9, 11, // tri2
        29, 28, 11 // tri3
    ),
    gsSPNTriangles_5b(
        30, 31, 8, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c4_2_v[167], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        3, 4, 2, // tri1
        1, 3, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 9, 10, // tri1
        5, 7, 8, // tri2
        1, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        1, 12, 3, // tri0
        11, 13, 14, // tri1
        15, 16, 17, // tri2
        18, 19, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 17, 16, // tri0
        10, 15, 20, // tri1
        15, 17, 20, // tri2
        21, 22, 7 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 2, // tri0
        24, 23, 21, // tri1
        25, 26, 27, // tri2
        25, 28, 26 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 26, // tri0
        29, 30, 26, // tri1
        31, 20, 17, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c4_2_v[199], 15, 0),
    gsSPNTrianglesInit_5b(
        9, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        5, 8, 6, // tri1
        9, 10, 11, // tri2
        9, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 10, // tri0
        13, 14, 10, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_2_v[214], 15, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 10, // tri1
        9, 11, 12, // tri2
        11, 13, 14 // tri3
    ),
    gsSPEndDisplayList(),
};
