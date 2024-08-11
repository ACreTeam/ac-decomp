#include "libforest/gbi_extensions.h"

extern u8 rail_pal_dummy[];
extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 rail_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_t_8_v[] = {
#include "assets/field/bg/grd_s_t_8_v.inc"
};

extern Gfx grd_s_t_8_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_8_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_8_v[166], 30, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 3, 8, // tri0
        3, 4, 8, // tri1
        9, 10, 11, // tri2
        12, 9, 11 // tri3
    ),
    gsSPNTriangles_5b(
        1, 12, 13, // tri0
        9, 14, 10, // tri1
        14, 15, 16, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 17, 21, // tri0
        22, 20, 23, // tri1
        24, 22, 25, // tri2
        26, 24, 27 // tri3
    ),
    gsSPNTriangles_5b(
        28, 26, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_8_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        5, 6, 4, // tri1
        7, 8, 9, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 9, // tri0
        9, 12, 7, // tri1
        12, 13, 7, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 16, // tri0
        18, 3, 19, // tri1
        3, 0, 19, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        21, 23, 22, // tri0
        23, 24, 22, // tri1
        23, 25, 24, // tri2
        25, 26, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 27, 26, // tri0
        27, 28, 26, // tri1
        27, 29, 28, // tri2
        17, 30, 31 // tri3
    ),
    gsSPVertex(&grd_s_t_8_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 6, // tri0
        4, 6, 3, // tri1
        5, 7, 6, // tri2
        0, 8, 9 // tri3
    ),
    gsSPNTriangles_5b(
        8, 10, 9, // tri0
        10, 11, 9, // tri1
        12, 11, 13, // tri2
        11, 10, 13 // tri3
    ),
    gsSPNTriangles_5b(
        10, 14, 13, // tri0
        13, 14, 15, // tri1
        15, 14, 16, // tri2
        16, 7, 17 // tri3
    ),
    gsSPNTriangles_5b(
        5, 17, 7, // tri0
        18, 19, 20, // tri1
        19, 21, 20, // tri2
        19, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        26, 27, 28, // tri1
        12, 29, 30, // tri2
        29, 31, 30 // tri3
    ),
    gsSPVertex(&grd_s_t_8_v[64], 7, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        2, 5, 6, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_8_v[71], 20, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        5, 6, 4, // tri1
        5, 7, 6, // tri2
        7, 8, 6 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        1, 10, 3, // tri1
        10, 11, 3, // tri2
        11, 5, 3 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 5, // tri0
        12, 7, 5, // tri1
        12, 13, 7, // tri2
        13, 9, 7 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 9, // tri0
        10, 15, 11, // tri1
        15, 16, 11, // tri2
        16, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 12, // tri0
        17, 13, 12, // tri1
        17, 18, 13, // tri2
        18, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 14, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_8_v[91], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 5, 9, // tri1
        10, 8, 11, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        6, 12, 15, // tri0
        13, 16, 17, // tri1
        16, 18, 19, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        26, 23, 27, // tri1
        21, 28, 29, // tri2
        28, 26, 30 // tri3
    ),
    gsSPVertex(&grd_s_t_8_v[122], 14, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 3 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 6, // tri0
        8, 10, 9, // tri1
        8, 11, 10, // tri2
        11, 12, 13 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_8_v[136], 30, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        4, 9, 10, // tri0
        11, 3, 12, // tri1
        13, 14, 15, // tri2
        1, 11, 16 // tri3
    ),
    gsSPNTriangles_5b(
        13, 6, 14, // tri0
        9, 13, 15, // tri1
        11, 12, 16, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 17, 21, // tri0
        22, 23, 24, // tri1
        18, 22, 25, // tri2
        26, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        27, 20, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
