#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c2_s_2_v[] = {
#include "assets/field/bg/grd_s_c2_s_2_v.inc"
};

extern Gfx grd_s_c2_s_2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c2_s_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c2_s_2_v[217], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 7, 10, // tri1
        11, 9, 12, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c2_s_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        29, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        4, 0, 5, // tri0
        0, 6, 5, // tri1
        6, 7, 5, // tri2
        6, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 7, // tri0
        10, 11, 12, // tri1
        11, 13, 12, // tri2
        13, 14, 12 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        16, 18, 17, // tri1
        17, 19, 15, // tri2
        17, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        21, 16, 15, // tri0
        21, 22, 16, // tri1
        15, 19, 21, // tri2
        0, 2, 23 // tri3
    ),
    gsSPNTriangles_5b(
        0, 24, 25, // tri0
        0, 23, 24, // tri1
        6, 0, 25, // tri2
        6, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 8, 6, // tri0
        27, 6, 26, // tri1
        28, 13, 11, // tri2
        29, 28, 11 // tri3
    ),
    gsSPNTriangles_5b(
        30, 29, 11, // tri0
        30, 11, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_s_2_v[32], 22, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        3, 0, 2, // tri1
        4, 3, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 2, 5, // tri0
        1, 6, 7, // tri1
        1, 7, 8, // tri2
        2, 1, 8 // tri3
    ),
    gsSPNTriangles_5b(
        2, 8, 9, // tri0
        2, 9, 10, // tri1
        5, 2, 10, // tri2
        11, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 14, // tri0
        13, 15, 14, // tri1
        12, 16, 17, // tri2
        18, 19, 16 // tri3
    ),
    gsSPNTriangles_5b(
        18, 16, 12, // tri0
        18, 12, 11, // tri1
        20, 18, 11, // tri2
        21, 20, 11 // tri3
    ),
    gsSPNTriangles_5b(
        12, 17, 13, // tri0
        14, 21, 11, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c2_s_2_v[54], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 3, // tri0
        5, 6, 3, // tri1
        5, 7, 6, // tri2
        6, 8, 9 // tri3
    ),
    gsSPNTriangles_5b(
        3, 6, 9, // tri0
        10, 11, 12, // tri1
        11, 13, 12, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 16, // tri0
        13, 18, 19, // tri1
        20, 21, 16, // tri2
        17, 20, 16 // tri3
    ),
    gsSPNTriangles_5b(
        20, 22, 21, // tri0
        18, 23, 19, // tri1
        24, 25, 26, // tri2
        25, 27, 26 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        29, 31, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_s_2_v[86], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 11, 9, // tri1
        12, 13, 14, // tri2
        15, 7, 9 // tri3
    ),
    gsSPNTriangles_5b(
        13, 12, 16, // tri0
        8, 10, 9, // tri1
        17, 18, 4, // tri2
        17, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 18, // tri0
        18, 5, 4, // tri1
        21, 22, 23, // tri2
        1, 12, 14 // tri3
    ),
    gsSPNTriangles_5b(
        1, 0, 12, // tri0
        24, 25, 26, // tri1
        24, 27, 25, // tri2
        24, 28, 27 // tri3
    ),
    gsSPNTriangles_5b(
        29, 17, 4, // tri0
        29, 30, 17, // tri1
        29, 31, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_s_2_v[118], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 3, // tri0
        8, 9, 10, // tri1
        11, 12, 13, // tri2
        9, 14, 10 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        9, 18, 14, // tri1
        12, 11, 10, // tri2
        10, 14, 12 // tri3
    ),
    gsSPNTriangles_5b(
        19, 12, 14, // tri0
        0, 2, 20, // tri1
        21, 12, 19, // tri2
        22, 13, 23 // tri3
    ),
    gsSPNTriangles_5b(
        23, 4, 22, // tri0
        24, 25, 26, // tri1
        27, 24, 1, // tri2
        24, 27, 25 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        29, 31, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_s_2_v[150], 12, 0),
    gsSPNTrianglesInit_5b(
        8, // tri count
        0, 1, 2, // tri0
        1, 0, 3, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 4, // tri0
        2, 1, 8, // tri1
        8, 9, 2, // tri2
        4, 7, 10 // tri3
    ),
    gsSPNTriangles_5b(
        7, 11, 10, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_s_2_v[162], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        6, 8, 9, // tri1
        10, 11, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 11, // tri0
        14, 16, 17, // tri1
        18, 4, 19, // tri2
        20, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 23, // tri0
        24, 23, 25, // tri1
        16, 25, 17, // tri2
        22, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 28, // tri0
        29, 26, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c2_s_2_v[193], 11, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        7, 9, 10, // tri0
        9, 3, 5, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_s_2_v[204], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 8, // tri0
        9, 10, 11, // tri1
        10, 3, 12, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
