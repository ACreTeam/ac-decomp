#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_3_v[] = {
#include "assets/field/bg/grd_s_f_3_v.inc"
};

extern Gfx grd_s_f_3_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_3_v[113], 13, 0),
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
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        9, 10, 11, // tri1
        12, 11, 10, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 13, // tri0
        17, 15, 18, // tri1
        17, 19, 15, // tri2
        20, 21, 17 // tri3
    ),
    gsSPNTriangles_5b(
        2, 1, 18, // tri0
        1, 0, 22, // tri1
        23, 20, 22, // tri2
        24, 0, 25 // tri3
    ),
    gsSPNTriangles_5b(
        24, 22, 0, // tri0
        26, 27, 25, // tri1
        26, 28, 6, // tri2
        26, 29, 28 // tri3
    ),
    gsSPNTriangles_5b(
        8, 7, 30, // tri0
        9, 11, 7, // tri1
        12, 14, 11, // tri2
        13, 31, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 16, 31, // tri0
        15, 19, 16, // tri1
        17, 21, 19, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_3_v[32], 18, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 3, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 4, // tri0
        7, 8, 9, // tri1
        8, 10, 9, // tri2
        8, 11, 10 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 14, // tri0
        13, 15, 14, // tri1
        16, 11, 17, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_3_v[50], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        11, 12, 13, // tri1
        14, 15, 16, // tri2
        17, 0, 18 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 15, // tri0
        19, 6, 20, // tri1
        4, 14, 16, // tri2
        11, 21, 12 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 22, // tri0
        21, 19, 22, // tri1
        9, 11, 13, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        8, 26, 27, // tri0
        28, 8, 29, // tri1
        24, 30, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_3_v[82], 18, 0),
    gsSPNTrianglesInit_5b(
        8, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        9, 10, 11, // tri1
        11, 12, 13, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_3_v[100], 13, 0),
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
