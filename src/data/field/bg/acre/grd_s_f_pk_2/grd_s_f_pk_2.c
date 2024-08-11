#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 stone_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_pk_2_v[] = {
#include "assets/field/bg/grd_s_f_pk_2_v.inc"
};

extern Gfx grd_s_f_pk_2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_pk_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_pk_2_v[204], 14, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 7, 4, // tri0
        9, 10, 11, // tri1
        12, 13, 10, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_pk_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 8, 9, // tri0
        8, 6, 10, // tri1
        11, 12, 13, // tri2
        12, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        17, 18, 19, // tri1
        20, 18, 17, // tri2
        21, 20, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 11, // tri0
        19, 25, 26, // tri1
        18, 25, 19, // tri2
        25, 27, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 29, // tri0
        28, 30, 31, // tri1
        30, 24, 23, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_pk_2_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 9, 10, // tri1
        10, 11, 8, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        11, 7, 8, // tri0
        13, 0, 14, // tri1
        0, 2, 14, // tri2
        3, 15, 2 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 13, // tri0
        17, 18, 13, // tri1
        19, 20, 21, // tri2
        20, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        20, 23, 22, // tri0
        9, 18, 24, // tri1
        18, 25, 24, // tri2
        18, 17, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 28, // tri0
        29, 30, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_pk_2_v[63], 27, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 5, 7, // tri1
        9, 10, 11, // tri2
        11, 10, 12 // tri3
    ),
    gsSPNTriangles_5b(
        12, 10, 1, // tri0
        13, 14, 15, // tri1
        14, 16, 17, // tri2
        18, 17, 16 // tri3
    ),
    gsSPNTriangles_5b(
        18, 6, 17, // tri0
        7, 19, 8, // tri1
        7, 6, 18, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        22, 9, 11, // tri0
        21, 9, 22, // tri1
        21, 23, 24, // tri2
        25, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 24, // tri0
        12, 1, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_pk_2_v[90], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        5, 4, 0 // tri2
    ),
    gsSPNTriangles_5b(
        6, 3, 7, // tri0
        8, 6, 7, // tri1
        9, 6, 8, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        12, 11, 13, // tri0
        11, 9, 13, // tri1
        14, 10, 15, // tri2
        16, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        17, 14, 16, // tri0
        18, 17, 19, // tri1
        19, 17, 16, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        22, 21, 23, // tri0
        21, 18, 23, // tri1
        24, 20, 25, // tri2
        26, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 26, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_pk_2_v[121], 32, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 0, // tri0
        7, 8, 3, // tri1
        9, 10, 11, // tri2
        12, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 11, // tri0
        11, 13, 7, // tri1
        14, 12, 9, // tri2
        15, 16, 14 // tri3
    ),
    gsSPNTriangles_5b(
        17, 16, 15, // tri0
        18, 17, 15, // tri1
        19, 20, 21, // tri2
        20, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 18, // tri0
        23, 24, 25, // tri1
        26, 27, 19, // tri2
        28, 27, 26 // tri3
    ),
    gsSPNTriangles_5b(
        24, 28, 25, // tri0
        25, 28, 26, // tri1
        29, 30, 23, // tri2
        30, 24, 23 // tri3
    ),
    gsSPVertex(&grd_s_f_pk_2_v[152], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 1, 0, // tri1
        4, 3, 0 // tri2
    ),
    gsSPNTriangles_5b(
        2, 5, 6, // tri0
        7, 8, 9, // tri1
        10, 11, 4, // tri2
        12, 11, 10 // tri3
    ),
    gsSPNTriangles_5b(
        8, 12, 9, // tri0
        9, 12, 10, // tri1
        13, 14, 7, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        21, 22, 23, // tri1
        24, 25, 26, // tri2
        27, 28, 26 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 27, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_pk_2_v[183], 7, 0),
    gsSPNTrianglesInit_5b(
        3, // tri count
        0, 1, 2, // tri0
        2, 3, 4, // tri1
        5, 6, 4 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_pk_2_v[190], 14, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 2, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 6, // tri0
        10, 7, 11, // tri1
        12, 11, 13, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
