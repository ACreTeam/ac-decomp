#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];

static Vtx grd_s_e2_1_v[] = {
#include "assets/field/bg/grd_s_e2_1_v.inc"
};

extern Gfx grd_s_e2_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_e2_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_e2_1_v[0], 24, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 2, // tri0
        4, 6, 5, // tri1
        6, 7, 5, // tri2
        7, 8, 5 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        9, 10, 8, // tri1
        10, 11, 8, // tri2
        11, 12, 8 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        0, 14, 1, // tri1
        15, 16, 17, // tri2
        18, 19, 17 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 18, // tri0
        22, 23, 20, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_e2_1_v[24], 32, 0),
    gsSPNTrianglesInit_5b(
        38, // tri count
        0, 1, 2, // tri0
        3, 0, 2, // tri1
        4, 3, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 2, 5, // tri0
        4, 5, 6, // tri1
        4, 6, 7, // tri2
        8, 4, 7 // tri3
    ),
    gsSPNTriangles_5b(
        9, 8, 7, // tri0
        9, 7, 10, // tri1
        9, 10, 11, // tri2
        12, 9, 11 // tri3
    ),
    gsSPNTriangles_5b(
        12, 11, 13, // tri0
        12, 13, 14, // tri1
        15, 12, 14, // tri2
        16, 15, 14 // tri3
    ),
    gsSPNTriangles_5b(
        16, 14, 17, // tri0
        16, 17, 18, // tri1
        19, 16, 18, // tri2
        20, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        20, 18, 21, // tri0
        1, 22, 23, // tri1
        2, 1, 23, // tri2
        5, 2, 23 // tri3
    ),
    gsSPNTriangles_5b(
        5, 23, 24, // tri0
        6, 5, 24, // tri1
        6, 24, 25, // tri2
        7, 6, 25 // tri3
    ),
    gsSPNTriangles_5b(
        7, 25, 26, // tri0
        10, 7, 26, // tri1
        10, 26, 27, // tri2
        11, 10, 27 // tri3
    ),
    gsSPNTriangles_5b(
        11, 27, 28, // tri0
        13, 11, 28, // tri1
        13, 28, 29, // tri2
        14, 13, 29 // tri3
    ),
    gsSPNTriangles_5b(
        14, 29, 30, // tri0
        17, 14, 30, // tri1
        17, 30, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_e2_1_v[56], 32, 0),
    gsSPNTrianglesInit_5b(
        36, // tri count
        0, 1, 2, // tri0
        3, 0, 2, // tri1
        3, 2, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 3, 4, // tri0
        6, 7, 8, // tri1
        9, 6, 8, // tri2
        9, 8, 10 // tri3
    ),
    gsSPNTriangles_5b(
        11, 9, 10, // tri0
        11, 10, 12, // tri1
        13, 11, 12, // tri2
        13, 12, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 13, 14, // tri0
        15, 14, 16, // tri1
        17, 15, 16, // tri2
        17, 16, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 17, 18, // tri0
        19, 18, 20, // tri1
        21, 19, 20, // tri2
        21, 20, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 21, 22, // tri0
        1, 23, 22, // tri1
        1, 22, 24, // tri2
        2, 1, 24 // tri3
    ),
    gsSPNTriangles_5b(
        2, 24, 25, // tri0
        4, 2, 25, // tri1
        4, 25, 26, // tri2
        8, 7, 27 // tri3
    ),
    gsSPNTriangles_5b(
        8, 27, 28, // tri0
        10, 8, 28, // tri1
        12, 10, 28, // tri2
        12, 28, 29 // tri3
    ),
    gsSPNTriangles_5b(
        14, 12, 29, // tri0
        14, 29, 30, // tri1
        16, 14, 30, // tri2
        18, 16, 30 // tri3
    ),
    gsSPNTriangles_5b(
        18, 30, 31, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_e2_1_v[88], 11, 0),
    gsSPNTrianglesInit_5b(
        9, // tri count
        0, 1, 2, // tri0
        3, 0, 2, // tri1
        4, 3, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 2, 5, // tri0
        6, 4, 5, // tri1
        6, 5, 7, // tri2
        8, 6, 7 // tri3
    ),
    gsSPNTriangles_5b(
        9, 8, 7, // tri0
        9, 7, 10, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
