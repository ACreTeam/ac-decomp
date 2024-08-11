#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c3_3_v[] = {
#include "assets/field/bg/grd_s_c3_3_v.inc"
};

extern Gfx grd_s_c3_3_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c3_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c3_3_v[182], 28, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        11, 8, 12, // tri1
        13, 14, 15, // tri2
        16, 6, 17 // tri3
    ),
    gsSPNTriangles_5b(
        4, 18, 19, // tri0
        20, 21, 22, // tri1
        23, 24, 21, // tri2
        18, 15, 19 // tri3
    ),
    gsSPNTriangles_5b(
        23, 25, 24, // tri0
        20, 23, 21, // tri1
        1, 26, 22, // tri2
        26, 20, 22 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 27, // tri0
        25, 16, 27, // tri1
        13, 11, 14, // tri2
        11, 12, 14 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c3_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 3, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 9, 10, // tri1
        9, 11, 10, // tri2
        12, 5, 7 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 14, // tri0
        15, 14, 13, // tri1
        16, 17, 15, // tri2
        16, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 18, // tri0
        20, 22, 21, // tri1
        20, 11, 22, // tri2
        23, 24, 3 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 24, // tri0
        27, 28, 26, // tri1
        27, 29, 28, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c3_3_v[30], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 6, // tri0
        1, 8, 2, // tri1
        9, 10, 11, // tri2
        12, 11, 13 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 11, // tri0
        14, 9, 15, // tri1
        3, 14, 4, // tri2
        16, 14, 3 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 12, // tri0
        8, 17, 2, // tri1
        19, 0, 2, // tri2
        0, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 20, 19, // tri0
        22, 23, 24, // tri1
        25, 26, 27, // tri2
        28, 29, 24 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 24, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c3_3_v[61], 20, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        9, 8, 10, // tri0
        11, 12, 13, // tri1
        13, 14, 11, // tri2
        11, 14, 10 // tri3
    ),
    gsSPNTriangles_5b(
        15, 12, 11, // tri0
        15, 16, 12, // tri1
        4, 16, 5, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        19, 15, 17, // tri0
        19, 5, 15, // tri1
        5, 16, 15, // tri2
        6, 1, 7 // tri3
    ),
    gsSPNTriangles_5b(
        17, 7, 18, // tri0
        1, 18, 7, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_3_v[81], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        3, 5, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        9, 10, 8, // tri2
        11, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 14, // tri0
        13, 15, 14, // tri1
        15, 16, 14, // tri2
        16, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 18, // tri0
        19, 20, 18, // tri1
        20, 21, 22, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        24, 26, 27, // tri0
        26, 28, 29, // tri1
        28, 30, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c3_3_v[113], 5, 0),
    gsSPNTrianglesInit_5b(
        2, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c3_3_v[118], 32, 0),
    gsSPNTrianglesInit_5b(
        38, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 3, 6, // tri0
        5, 2, 3, // tri1
        7, 8, 9, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        11, 14, 12, // tri1
        12, 15, 13, // tri2
        16, 12, 14 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 12, // tri0
        17, 18, 12, // tri1
        18, 15, 12, // tri2
        11, 7, 14 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 14, // tri0
        9, 16, 14, // tri1
        9, 19, 16, // tri2
        10, 20, 9 // tri3
    ),
    gsSPNTriangles_5b(
        20, 19, 9, // tri0
        8, 21, 10, // tri1
        21, 22, 10, // tri2
        22, 20, 10 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 20, // tri0
        21, 24, 22, // tri1
        21, 25, 24, // tri2
        24, 23, 22 // tri3
    ),
    gsSPNTriangles_5b(
        24, 26, 23, // tri0
        25, 4, 24, // tri1
        4, 6, 24, // tri2
        6, 26, 24 // tri3
    ),
    gsSPNTriangles_5b(
        6, 27, 26, // tri0
        3, 28, 6, // tri1
        28, 27, 6, // tri2
        1, 28, 3 // tri3
    ),
    gsSPNTriangles_5b(
        1, 29, 28, // tri0
        0, 30, 1, // tri1
        0, 31, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c3_3_v[150], 4, 0),
    gsSPNTrianglesInit_5b(
        2, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_3_v[154], 28, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 4, // tri0
        5, 7, 6, // tri1
        8, 9, 10, // tri2
        11, 8, 10 // tri3
    ),
    gsSPNTriangles_5b(
        7, 11, 12, // tri0
        7, 12, 6, // tri1
        13, 14, 15, // tri2
        16, 13, 17 // tri3
    ),
    gsSPNTriangles_5b(
        8, 18, 9, // tri0
        18, 16, 19, // tri1
        20, 21, 22, // tri2
        14, 22, 15 // tri3
    ),
    gsSPNTriangles_5b(
        20, 23, 21, // tri0
        23, 24, 21, // tri1
        25, 26, 27, // tri2
        23, 25, 24 // tri3
    ),
    gsSPEndDisplayList(),
};
