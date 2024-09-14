#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c6_3_v[] = {
#include "assets/field/bg/grd_s_c6_3_v.inc"
};

extern Gfx grd_s_c6_3_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c6_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c6_3_v[197], 17, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 3, 8, // tri0
        3, 4, 8, // tri1
        9, 10, 11, // tri2
        12, 9, 11 // tri3
    ),
    gsSPNTriangles_5b(
        1, 12, 13, // tri0
        9, 14, 10, // tri1
        14, 15, 16, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c6_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        6, 7, 8, // tri1
        7, 9, 8, // tri2
        10, 9, 11 // tri3
    ),
    gsSPNTriangles_5b(
        9, 12, 11, // tri0
        9, 13, 12, // tri1
        9, 7, 13, // tri2
        13, 14, 12 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        16, 18, 17, // tri1
        19, 20, 15, // tri2
        21, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        22, 24, 23, // tri0
        25, 26, 27, // tri1
        26, 28, 27, // tri2
        26, 29, 28 // tri3
    ),
    gsSPNTriangles_5b(
        26, 24, 29, // tri0
        29, 30, 28, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c6_3_v[31], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        5, 8, 6, // tri1
        6, 9, 7, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        16, 17, 11, // tri1
        18, 19, 20, // tri2
        21, 22, 18 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 18, // tri0
        22, 24, 23, // tri1
        21, 25, 22, // tri2
        26, 13, 15 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 13, // tri0
        28, 13, 27, // tri1
        28, 29, 13, // tri2
        30, 31, 28 // tri3
    ),
    gsSPVertex(&grd_s_c6_3_v[63], 23, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        5, 8, 6, // tri1
        8, 9, 6, // tri2
        9, 10, 6 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 6, // tri0
        9, 12, 10, // tri1
        13, 14, 15, // tri2
        14, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        14, 17, 16, // tri0
        17, 18, 16, // tri1
        19, 20, 21, // tri2
        22, 14, 13 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c6_3_v[86], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 0, // tri0
        5, 7, 6, // tri1
        8, 9, 10, // tri2
        8, 11, 9 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 14, // tri0
        15, 12, 16, // tri1
        13, 17, 18, // tri2
        17, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 23, // tri0
        22, 15, 24, // tri1
        25, 26, 27, // tri2
        28, 29, 30 // tri3
    ),
    gsSPNTriangles_5b(
        28, 31, 29, // tri0
        26, 30, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c6_3_v[118], 26, 0),
    gsSPNTrianglesInit_5b(
        12, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        11, 12, 13, // tri1
        14, 15, 16, // tri2
        14, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        14, 11, 15, // tri0
        17, 18, 19, // tri1
        19, 20, 21, // tri2
        22, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        23, 25, 24, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c6_3_v[144], 32, 0),
    gsSPNTrianglesInit_5b(
        38, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        5, 9, 6, // tri2
        6, 10, 8 // tri3
    ),
    gsSPNTriangles_5b(
        11, 10, 12, // tri0
        10, 6, 12, // tri1
        11, 13, 10, // tri2
        14, 15, 4 // tri3
    ),
    gsSPNTriangles_5b(
        14, 16, 15, // tri0
        3, 14, 4, // tri1
        17, 18, 19, // tri2
        18, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        16, 19, 15, // tri0
        16, 17, 19, // tri1
        6, 9, 12, // tri2
        9, 21, 12 // tri3
    ),
    gsSPNTriangles_5b(
        22, 21, 9, // tri0
        22, 23, 21, // tri1
        13, 18, 24, // tri2
        13, 20, 18 // tri3
    ),
    gsSPNTriangles_5b(
        13, 24, 10, // tri0
        3, 25, 26, // tri1
        3, 1, 25, // tri2
        14, 3, 27 // tri3
    ),
    gsSPNTriangles_5b(
        3, 26, 27, // tri0
        16, 27, 28, // tri1
        16, 14, 27, // tri2
        17, 16, 29 // tri3
    ),
    gsSPNTriangles_5b(
        16, 28, 29, // tri0
        18, 29, 30, // tri1
        18, 17, 29, // tri2
        24, 30, 31 // tri3
    ),
    gsSPNTriangles_5b(
        24, 18, 30, // tri0
        10, 24, 8, // tri1
        24, 31, 8, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c6_3_v[176], 4, 0),
    gsSPNTrianglesInit_5b(
        2, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c6_3_v[180], 17, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        4, 9, 10, // tri0
        11, 3, 12, // tri1
        13, 14, 15, // tri2
        1, 11, 16 // tri3
    ),
    gsSPNTriangles_5b(
        13, 6, 14, // tri0
        9, 13, 15, // tri1
        11, 12, 16, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
