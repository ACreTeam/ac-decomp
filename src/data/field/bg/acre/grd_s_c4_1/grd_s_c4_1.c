#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c4_1_v[] = {
#include "assets/field/bg/grd_s_c4_1_v.inc"
};

extern Gfx grd_s_c4_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c4_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c4_1_v[168], 23, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        3, 4, 6, // tri0
        8, 9, 10, // tri1
        9, 5, 7, // tri2
        11, 8, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 11, 14, // tri0
        13, 14, 15, // tri1
        16, 17, 18, // tri2
        19, 16, 20 // tri3
    ),
    gsSPNTriangles_5b(
        17, 13, 15, // tri0
        16, 18, 20, // tri1
        21, 19, 22, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        4, 6, 5, // tri0
        7, 8, 9, // tri1
        8, 10, 9, // tri2
        10, 11, 9 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 14, // tri0
        13, 0, 14, // tri1
        15, 16, 17, // tri2
        15, 18, 16 // tri3
    ),
    gsSPNTriangles_5b(
        16, 19, 17, // tri0
        18, 20, 16, // tri1
        12, 21, 22, // tri2
        12, 14, 21 // tri3
    ),
    gsSPNTriangles_5b(
        3, 5, 2, // tri0
        6, 23, 5, // tri1
        24, 25, 7, // tri2
        24, 26, 27 // tri3
    ),
    gsSPNTriangles_5b(
        24, 27, 25, // tri0
        26, 28, 27, // tri1
        26, 17, 28, // tri2
        17, 19, 28 // tri3
    ),
    gsSPNTriangles_5b(
        19, 8, 28, // tri0
        22, 29, 20, // tri1
        29, 16, 20, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c4_1_v[30], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 4, 8, // tri0
        4, 9, 8, // tri1
        10, 7, 11, // tri2
        12, 10, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        13, 12, 14, // tri1
        16, 13, 17, // tri2
        18, 19, 16 // tri3
    ),
    gsSPNTriangles_5b(
        20, 1, 0, // tri0
        2, 21, 0, // tri1
        18, 16, 17, // tri2
        20, 0, 22 // tri3
    ),
    gsSPNTriangles_5b(
        0, 23, 22, // tri0
        20, 22, 24, // tri1
        20, 24, 25, // tri2
        26, 27, 5 // tri3
    ),
    gsSPNTriangles_5b(
        8, 28, 7, // tri0
        29, 30, 31, // tri1
        29, 9, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c4_1_v[62], 4, 0),
    gsSPNTrianglesInit_5b(
        2, // tri count
        0, 1, 2, // tri0
        3, 1, 0, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_1_v[66], 23, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 2, 6, // tri0
        5, 7, 2, // tri1
        7, 0, 2, // tri2
        7, 8, 0 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 0, // tri0
        9, 10, 0, // tri1
        11, 12, 13, // tri2
        12, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        10, 9, 13, // tri0
        9, 11, 13, // tri1
        13, 14, 15, // tri2
        13, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 10, 18, // tri0
        10, 13, 18, // tri1
        13, 16, 18, // tri2
        10, 17, 3 // tri3
    ),
    gsSPNTriangles_5b(
        10, 3, 0, // tri0
        6, 2, 4, // tri1
        19, 6, 4, // tri2
        20, 21, 6 // tri3
    ),
    gsSPNTriangles_5b(
        20, 6, 19, // tri0
        21, 5, 6, // tri1
        21, 22, 5, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_1_v[89], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        2, 3, 4, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        8, 9, 10, // tri1
        11, 12, 13, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        17, 18, 19, // tri1
        19, 20, 21, // tri2
        22, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 24, 26, // tri0
        27, 25, 26, // tri1
        28, 29, 30, // tri2
        31, 29, 28 // tri3
    ),
    gsSPVertex(&grd_s_c4_1_v[121], 20, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        3, 4, 2, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 6, // tri0
        6, 5, 8, // tri1
        10, 11, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        13, 12, 14, // tri0
        13, 15, 16, // tri1
        17, 7, 18, // tri2
        19, 18, 11 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_1_v[141], 27, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 5, 9, // tri0
        10, 8, 11, // tri1
        12, 13, 14, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 12, 19, // tri0
        6, 20, 21, // tri1
        20, 22, 21, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 22, // tri0
        16, 26, 17, // tri1
        23, 15, 24, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
