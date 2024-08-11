#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c2_1_v[] = {
#include "assets/field/bg/grd_s_c2_1_v.inc"
};

extern Gfx grd_s_c2_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c2_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c2_1_v[198], 23, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 6, // tri0
        8, 9, 10, // tri1
        11, 12, 13, // tri2
        0, 3, 1 // tri3
    ),
    gsSPNTriangles_5b(
        9, 13, 10, // tri0
        11, 14, 12, // tri1
        15, 0, 2, // tri2
        16, 15, 17 // tri3
    ),
    gsSPNTriangles_5b(
        7, 18, 19, // tri0
        18, 8, 20, // tri1
        14, 21, 22, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c2_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 1 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        11, 9, 8, // tri1
        12, 13, 14, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 15, // tri0
        2, 20, 0, // tri1
        21, 22, 23, // tri2
        22, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        28, 5, 29, // tri1
        30, 20, 2, // tri2
        5, 4, 31 // tri3
    ),
    gsSPNTriangles_5b(
        15, 19, 16, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        3, 5, 12, // tri1
        9, 12, 13, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        9, 13, 10, // tri0
        17, 18, 19, // tri1
        12, 5, 20, // tri2
        21, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        12, 20, 13, // tri0
        22, 24, 23, // tri1
        25, 17, 19, // tri2
        26, 27, 0 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 0, // tri0
        29, 30, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_1_v[64], 24, 0),
    gsSPNTrianglesInit_5b(
        12, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        10, 12, 11, // tri1
        13, 14, 15, // tri2
        10, 16, 12 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 19, // tri0
        20, 6, 8, // tri1
        1, 4, 2, // tri2
        21, 22, 2 // tri3
    ),
    gsSPNTriangles_5b(
        23, 22, 0, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_1_v[88], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        1, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        9, 10, 11, // tri1
        10, 3, 12, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c2_1_v[101], 27, 0),
    gsSPNTrianglesInit_5b(
        32, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        2, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        2, 5, 3, // tri0
        6, 7, 8, // tri1
        6, 8, 9, // tri2
        8, 10, 11 // tri3
    ),
    gsSPNTriangles_5b(
        8, 11, 9, // tri0
        12, 13, 11, // tri1
        4, 2, 14, // tri2
        4, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        16, 18, 6, // tri1
        19, 16, 6, // tri2
        19, 6, 9 // tri3
    ),
    gsSPNTriangles_5b(
        2, 1, 20, // tri0
        2, 20, 14, // tri1
        1, 21, 22, // tri2
        1, 22, 20 // tri3
    ),
    gsSPNTriangles_5b(
        10, 12, 11, // tri0
        18, 23, 7, // tri1
        18, 7, 6, // tri2
        4, 13, 12 // tri3
    ),
    gsSPNTriangles_5b(
        4, 12, 5, // tri0
        21, 1, 0, // tri1
        24, 21, 0, // tri2
        11, 13, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 19, 9, // tri0
        11, 26, 9, // tri1
        4, 15, 25, // tri2
        13, 4, 25 // tri3
    ),
    gsSPNTriangles_5b(
        11, 25, 26, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_1_v[128], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        5, 4, 10, // tri1
        6, 11, 4, // tri2
        7, 9, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 8, 7, // tri0
        14, 15, 11, // tri1
        16, 10, 17, // tri2
        12, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 21, // tri0
        22, 23, 24, // tri1
        22, 24, 25, // tri2
        3, 22, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 28, // tri0
        19, 21, 29, // tri1
        27, 29, 28, // tri2
        30, 31, 13 // tri3
    ),
    gsSPVertex(&grd_s_c2_1_v[160], 11, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_1_v[171], 27, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        1, 6, 2 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        3, 7, 4, // tri1
        10, 11, 6, // tri2
        8, 12, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 11, // tri0
        13, 14, 15, // tri1
        16, 17, 18, // tri2
        17, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        19, 0, 21, // tri0
        22, 23, 24, // tri1
        25, 22, 26, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
