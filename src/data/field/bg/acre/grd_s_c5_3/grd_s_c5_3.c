#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c5_3_v[] = {
#include "assets/field/bg/grd_s_c5_3_v.inc"
};

extern Gfx grd_s_c5_3_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c5_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c5_3_v[169], 12, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 3, 7, // tri0
        8, 5, 9, // tri1
        10, 8, 11, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c5_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 2, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        5, 1, 6, // tri1
        6, 1, 0, // tri2
        8, 9, 10 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 10, // tri0
        9, 12, 11, // tri1
        11, 12, 13, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 16, // tri0
        17, 18, 16, // tri1
        19, 1, 20, // tri2
        1, 5, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 23, // tri0
        21, 20, 22, // tri1
        20, 24, 22, // tri2
        20, 25, 24 // tri3
    ),
    gsSPNTriangles_5b(
        20, 5, 25, // tri0
        20, 21, 19, // tri1
        26, 27, 28, // tri2
        15, 14, 27 // tri3
    ),
    gsSPNTriangles_5b(
        14, 28, 27, // tri0
        26, 29, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_3_v[31], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        3, 5, 4 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 5, // tri0
        8, 9, 7, // tri1
        10, 11, 9, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 12, // tri0
        15, 16, 17, // tri1
        2, 18, 0, // tri2
        19, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        16, 15, 22, // tri0
        23, 24, 25, // tri1
        25, 26, 23, // tri2
        15, 23, 26 // tri3
    ),
    gsSPNTriangles_5b(
        24, 27, 25, // tri0
        14, 13, 28, // tri1
        12, 10, 13, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        8, 7, 29, // tri0
        3, 6, 5, // tri1
        2, 20, 18, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_3_v[61], 10, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        2, 5, 0 // tri2
    ),
    gsSPNTriangles_5b(
        4, 0, 5, // tri0
        6, 1, 0, // tri1
        7, 6, 8, // tri2
        9, 1, 6 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c5_3_v[71], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 10, // tri1
        9, 11, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 16, // tri0
        17, 13, 16, // tri1
        17, 16, 18, // tri2
        19, 18, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 20, 22, // tri0
        23, 22, 24, // tri1
        25, 23, 24, // tri2
        25, 24, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 25, 26, // tri0
        28, 29, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c5_3_v[102], 27, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 2, 4, // tri1
        5, 3, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 4, 6, // tri0
        7, 6, 8, // tri1
        9, 10, 11, // tri2
        9, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 12, // tri0
        14, 15, 16, // tri1
        15, 17, 18, // tri2
        17, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 22, // tri0
        21, 23, 24, // tri1
        23, 25, 26, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c5_3_v[129], 28, 0),
    gsSPNTrianglesInit_5b(
        33, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        7, 8, 6, // tri1
        7, 9, 10, // tri2
        9, 11, 10 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 14, // tri0
        13, 15, 14, // tri1
        13, 16, 15, // tri2
        16, 17, 15 // tri3
    ),
    gsSPNTriangles_5b(
        14, 18, 19, // tri0
        14, 15, 18, // tri1
        15, 20, 18, // tri2
        15, 17, 20 // tri3
    ),
    gsSPNTriangles_5b(
        19, 18, 2, // tri0
        18, 0, 2, // tri1
        18, 20, 0, // tri2
        20, 21, 0 // tri3
    ),
    gsSPNTriangles_5b(
        0, 22, 1, // tri0
        0, 21, 22, // tri1
        3, 23, 24, // tri2
        3, 1, 23 // tri3
    ),
    gsSPNTriangles_5b(
        1, 22, 23, // tri0
        22, 25, 23, // tri1
        24, 23, 4, // tri2
        23, 5, 4 // tri3
    ),
    gsSPNTriangles_5b(
        23, 25, 5, // tri0
        25, 26, 5, // tri1
        5, 26, 7, // tri2
        26, 9, 7 // tri3
    ),
    gsSPNTriangles_5b(
        8, 7, 27, // tri0
        7, 10, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c5_3_v[157], 12, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 8, 9, // tri0
        8, 10, 11, // tri1
        10, 3, 11, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
