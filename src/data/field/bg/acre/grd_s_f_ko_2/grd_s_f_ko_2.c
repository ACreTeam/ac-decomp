#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 stone_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_ko_2_v[] = {
#include "assets/field/bg/grd_s_f_ko_2_v.inc"
};

extern Gfx grd_s_f_ko_2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_ko_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_ko_2_v[140], 31, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 0, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 4, 7, // tri0
        8, 6, 9, // tri1
        10, 8, 11, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 12, 16, // tri0
        17, 18, 19, // tri1
        13, 20, 21, // tri2
        22, 15, 23 // tri3
    ),
    gsSPNTriangles_5b(
        24, 17, 25, // tri0
        26, 24, 27, // tri1
        20, 28, 21, // tri2
        20, 26, 28 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 29, // tri0
        30, 22, 29, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_ko_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        27, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 0, // tri0
        6, 1, 0, // tri1
        7, 8, 6, // tri2
        8, 9, 6 // tri3
    ),
    gsSPNTriangles_5b(
        8, 10, 9, // tri0
        5, 11, 7, // tri1
        6, 5, 7, // tri2
        12, 13, 4 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 4, // tri0
        14, 15, 4, // tri1
        14, 16, 15, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        11, 20, 7, // tri0
        18, 21, 19, // tri1
        20, 21, 7, // tri2
        1, 22, 3 // tri3
    ),
    gsSPNTriangles_5b(
        3, 12, 4, // tri0
        23, 24, 25, // tri1
        24, 26, 25, // tri2
        27, 18, 28 // tri3
    ),
    gsSPNTriangles_5b(
        18, 17, 28, // tri0
        12, 29, 13, // tri1
        29, 25, 26, // tri2
        23, 30, 24 // tri3
    ),
    gsSPVertex(&grd_s_f_ko_2_v[31], 29, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        2, 5, 0, // tri0
        6, 7, 1, // tri1
        6, 8, 7, // tri2
        7, 3, 1 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        10, 8, 11, // tri1
        8, 6, 11, // tri2
        12, 13, 9 // tri3
    ),
    gsSPNTriangles_5b(
        13, 10, 9, // tri0
        14, 13, 12, // tri1
        15, 16, 17, // tri2
        16, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 21, // tri0
        22, 2, 4, // tri1
        15, 17, 23, // tri2
        17, 18, 24 // tri3
    ),
    gsSPNTriangles_5b(
        22, 19, 21, // tri0
        22, 25, 19, // tri1
        22, 4, 25, // tri2
        26, 27, 28 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_ko_2_v[60], 23, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 0, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 3, 8, // tri0
        1, 9, 2, // tri1
        0, 2, 6, // tri2
        1, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        10, 11, 14, // tri1
        15, 16, 17, // tri2
        18, 19, 16 // tri3
    ),
    gsSPNTriangles_5b(
        12, 15, 17, // tri0
        18, 20, 19, // tri1
        20, 21, 22, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_ko_2_v[83], 26, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 5 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 7, 11, // tri1
        12, 13, 14, // tri2
        8, 15, 9 // tri3
    ),
    gsSPNTriangles_5b(
        8, 6, 15, // tri0
        16, 14, 1, // tri1
        17, 18, 19, // tri2
        20, 0, 2 // tri3
    ),
    gsSPNTriangles_5b(
        16, 12, 14, // tri0
        7, 9, 11, // tri1
        21, 17, 22, // tri2
        12, 23, 13 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        3, 21, 4, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_ko_2_v[109], 31, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        5, 0, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        8, 10, 9, // tri1
        3, 11, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        5, 6, 16, // tri0
        8, 13, 10, // tri1
        17, 5, 16, // tri2
        14, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 21, // tri0
        22, 23, 24, // tri1
        23, 25, 26, // tri2
        25, 27, 26 // tri3
    ),
    gsSPNTriangles_5b(
        20, 28, 29, // tri0
        28, 22, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
