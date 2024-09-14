#include "libforest/gbi_extensions.h"

extern u8 rail_pal_dummy[];
extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 rail_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_t_10_v[] = {
#include "assets/field/bg/grd_s_t_10_v.inc"
};

extern Gfx grd_s_t_10_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_10_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_10_v[173], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        5, 0, 6 // tri2
    ),
    gsSPNTriangles_5b(
        0, 2, 6, // tri0
        5, 6, 7, // tri1
        8, 5, 7, // tri2
        9, 8, 10 // tri3
    ),
    gsSPNTriangles_5b(
        8, 7, 10, // tri0
        11, 9, 12, // tri1
        13, 14, 15, // tri2
        16, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        14, 16, 18, // tri0
        16, 19, 17, // tri1
        19, 20, 17, // tri2
        21, 22, 20 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        23, 11, 24, // tri1
        21, 23, 22, // tri2
        25, 26, 27 // tri3
    ),
    gsSPNTriangles_5b(
        28, 25, 29, // tri0
        30, 28, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_10_v[205], 22, 0),
    gsSPNTrianglesInit_5b(
        12, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 5, 9, // tri0
        10, 11, 12, // tri1
        11, 8, 13, // tri2
        8, 9, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        17, 14, 16, // tri1
        6, 17, 18, // tri2
        14, 19, 15 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 21, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_10_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
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
        10, 11, 12, // tri1
        11, 10, 13, // tri2
        13, 14, 11 // tri3
    ),
    gsSPNTriangles_5b(
        15, 14, 13, // tri0
        16, 14, 15, // tri1
        15, 13, 17, // tri2
        17, 18, 15 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 18, // tri0
        19, 20, 18, // tri1
        20, 21, 18, // tri2
        20, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        23, 20, 19, // tri0
        23, 24, 20, // tri1
        25, 24, 23, // tri2
        26, 27, 25 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 25, // tri0
        27, 29, 28, // tri1
        30, 31, 26, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_10_v[32], 24, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        4, 8, 7, // tri1
        5, 9, 10, // tri2
        5, 7, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 10, 12, // tri0
        10, 9, 12, // tri1
        1, 13, 14, // tri2
        13, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 16, // tri0
        15, 18, 17, // tri1
        17, 11, 16, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 19, // tri0
        19, 21, 17, // tri1
        22, 20, 23, // tri2
        22, 21, 20 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_10_v[56], 20, 0),
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
    gsSPVertex(&grd_s_t_10_v[76], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
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
        23, 26, 27, // tri0
        28, 27, 26, // tri1
        29, 28, 26, // tri2
        30, 31, 29 // tri3
    ),
    gsSPVertex(&grd_s_t_10_v[108], 9, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 4, 0, // tri1
        3, 5, 4 // tri2
    ),
    gsSPNTriangles_5b(
        3, 6, 5, // tri0
        6, 7, 8, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_10_v[117], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        5, 0, 6 // tri2
    ),
    gsSPNTriangles_5b(
        0, 2, 6, // tri0
        5, 6, 7, // tri1
        8, 5, 7, // tri2
        9, 8, 10 // tri3
    ),
    gsSPNTriangles_5b(
        8, 7, 10, // tri0
        11, 9, 12, // tri1
        3, 13, 14, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 17, // tri0
        15, 18, 16, // tri1
        18, 19, 16, // tri2
        20, 21, 19 // tri3
    ),
    gsSPNTriangles_5b(
        18, 20, 19, // tri0
        22, 23, 24, // tri1
        20, 22, 21, // tri2
        25, 26, 27 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_10_v[148], 25, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        10, 12, 13, // tri1
        7, 14, 15, // tri2
        14, 9, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 19, // tri0
        20, 21, 22, // tri1
        23, 17, 24, // tri2
        20, 0, 21 // tri3
    ),
    gsSPNTriangles_5b(
        4, 20, 22, // tri0
        17, 19, 24, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
