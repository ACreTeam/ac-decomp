#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 stone_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_pk_3_v[] = {
#include "assets/field/bg/grd_s_f_pk_3_v.inc"
};

extern Gfx grd_s_f_pk_3_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_pk_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_pk_3_v[245], 13, 0),
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
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_pk_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        2, 4, 0 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        5, 9, 6, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        11, 13, 16, // tri1
        14, 17, 18, // tri2
        17, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        4, 21, 22, // tri0
        23, 3, 24, // tri1
        25, 23, 26, // tri2
        5, 25, 27 // tri3
    ),
    gsSPNTriangles_5b(
        8, 28, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_pk_3_v[30], 27, 0),
    gsSPNTrianglesInit_5b(
        12, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 7, 10, // tri1
        11, 9, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 13, 17, // tri0
        18, 19, 20, // tri1
        19, 16, 21, // tri2
        22, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 22, 26, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_pk_3_v[57], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        0, 2, 4, // tri0
        4, 6, 5, // tri1
        7, 5, 8, // tri2
        5, 6, 8 // tri3
    ),
    gsSPNTriangles_5b(
        6, 9, 8, // tri0
        10, 11, 12, // tri1
        11, 13, 12, // tri2
        14, 3, 15 // tri3
    ),
    gsSPNTriangles_5b(
        3, 1, 15, // tri0
        13, 16, 12, // tri1
        13, 17, 16, // tri2
        17, 18, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 18, // tri0
        19, 20, 18, // tri1
        21, 22, 23, // tri2
        22, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        21, 25, 22, // tri0
        21, 26, 25, // tri1
        26, 27, 25, // tri2
        28, 29, 30 // tri3
    ),
    gsSPNTriangles_5b(
        29, 31, 30, // tri0
        29, 13, 31, // tri1
        13, 11, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_pk_3_v[89], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 3, // tri0
        7, 8, 9, // tri1
        8, 10, 11, // tri2
        10, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 12, 15, // tri0
        12, 16, 15, // tri1
        12, 17, 16, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 19, 18, // tri0
        22, 20, 19, // tri1
        22, 23, 24, // tri2
        25, 26, 27 // tri3
    ),
    gsSPNTriangles_5b(
        26, 23, 27, // tri0
        26, 28, 23, // tri1
        28, 24, 23, // tri2
        28, 29, 24 // tri3
    ),
    gsSPNTriangles_5b(
        26, 25, 30, // tri0
        25, 2, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_pk_3_v[120], 12, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 9, 10, // tri1
        8, 11, 9, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_pk_3_v[132], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        6, 7, 8, // tri1
        6, 8, 9, // tri2
        10, 6, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        12, 14, 13, // tri1
        12, 10, 14, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        16, 11, 18, // tri0
        15, 17, 19, // tri1
        20, 15, 19, // tri2
        21, 20, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        24, 21, 25, // tri1
        21, 22, 25, // tri2
        26, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 29, // tri0
        28, 30, 29, // tri1
        28, 26, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_pk_3_v[163], 32, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        4, 0, 6, // tri0
        7, 8, 9, // tri1
        10, 8, 7, // tri2
        11, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 13, // tri0
        8, 11, 9, // tri1
        13, 12, 14, // tri2
        12, 15, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 14, // tri0
        16, 17, 18, // tri1
        17, 19, 18, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        21, 22, 20, // tri1
        23, 24, 25, // tri2
        26, 23, 25 // tri3
    ),
    gsSPNTriangles_5b(
        22, 26, 25, // tri0
        24, 27, 28, // tri1
        27, 29, 28, // tri2
        29, 30, 28 // tri3
    ),
    gsSPVertex(&grd_s_f_pk_3_v[194], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        3, 1, 0, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 4, 6, // tri0
        8, 9, 10, // tri1
        5, 8, 10, // tri2
        10, 9, 11 // tri3
    ),
    gsSPNTriangles_5b(
        9, 12, 11, // tri0
        12, 13, 11, // tri1
        14, 15, 13, // tri2
        14, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 19, // tri0
        16, 17, 19, // tri1
        15, 16, 19, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        26, 27, 25, // tri1
        28, 29, 30, // tri2
        29, 26, 30 // tri3
    ),
    gsSPVertex(&grd_s_f_pk_3_v[225], 7, 0),
    gsSPNTrianglesInit_5b(
        3, // tri count
        0, 1, 2, // tri0
        2, 3, 4, // tri1
        5, 6, 4 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_pk_3_v[232], 13, 0),
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
