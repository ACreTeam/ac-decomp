#include "libforest/gbi_extensions.h"

extern u8 rail_pal_dummy[];
extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 station_pal_dummy[];
extern u8 stone_tex_dummy[];
extern u8 station_tex_dummy[];
extern u8 rail_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_t_st1_2_v[] = {
#include "assets/field/bg/grd_s_t_st1_2_v.inc"
};

extern Gfx grd_s_t_st1_2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_st1_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_st1_2_v[216], 24, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 7, 10, // tri1
        11, 12, 13, // tri2
        14, 11, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 14, 17, // tri0
        18, 16, 19, // tri1
        20, 18, 21, // tri2
        22, 20, 23 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_st1_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        1, 0, 3, // tri1
        0, 2, 4 // tri2
    ),
    gsSPNTriangles_5b(
        2, 5, 4, // tri0
        4, 5, 6, // tri1
        7, 8, 9, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        15, 16, 13, // tri1
        13, 16, 1, // tri2
        12, 11, 17 // tri3
    ),
    gsSPNTriangles_5b(
        17, 11, 18, // tri0
        17, 18, 19, // tri1
        20, 19, 21, // tri2
        22, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 19, // tri0
        19, 20, 23, // tri1
        25, 8, 23, // tri2
        23, 20, 25 // tri3
    ),
    gsSPNTriangles_5b(
        11, 10, 26, // tri0
        15, 14, 27, // tri1
        14, 28, 27, // tri2
        29, 30, 3 // tri3
    ),
    gsSPNTriangles_5b(
        5, 31, 6, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_st1_2_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 8, 7, // tri0
        9, 10, 11, // tri1
        12, 13, 14, // tri2
        13, 15, 14 // tri3
    ),
    gsSPNTriangles_5b(
        16, 14, 15, // tri0
        15, 17, 16, // tri1
        16, 17, 18, // tri2
        17, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        19, 21, 20, // tri1
        22, 23, 24, // tri2
        22, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 23, // tri0
        28, 29, 27, // tri1
        10, 29, 28, // tri2
        1, 4, 2 // tri3
    ),
    gsSPNTriangles_5b(
        28, 27, 30, // tri0
        26, 30, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_st1_2_v[63], 12, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 5 // tri2
    ),
    gsSPNTriangles_5b(
        8, 6, 5, // tri0
        9, 4, 10, // tri1
        10, 4, 11, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_st1_2_v[75], 11, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 8, 9, // tri0
        8, 6, 10, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_st1_2_v[86], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 9, 10, // tri1
        9, 11, 10, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 16, // tri0
        15, 17, 18, // tri1
        17, 19, 20, // tri2
        19, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        21, 23, 24, // tri0
        25, 26, 27, // tri1
        27, 28, 25, // tri2
        27, 29, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 9, 28, // tri0
        10, 30, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_st1_2_v[118], 17, 0),
    gsSPNTrianglesInit_5b(
        8, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        9, 10, 11, // tri1
        12, 13, 14, // tri2
        15, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        13, 16, 15, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_st1_2_v[135], 20, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        2, 3, 4, // tri1
        3, 5, 4 // tri2
    ),
    gsSPNTriangles_5b(
        1, 3, 2, // tri0
        4, 5, 6, // tri1
        5, 7, 6, // tri2
        6, 7, 8 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        7, 10, 9, // tri1
        5, 11, 7, // tri2
        10, 12, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 10, 7, // tri0
        3, 13, 5, // tri1
        13, 11, 5, // tri2
        1, 14, 3 // tri3
    ),
    gsSPNTriangles_5b(
        14, 13, 3, // tri0
        14, 15, 13, // tri1
        13, 16, 11, // tri2
        15, 16, 13 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 11, // tri0
        11, 17, 10, // tri1
        17, 18, 10, // tri2
        10, 18, 12 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 12, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, station_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(station_tex_dummy, G_IM_FMT_CI, 128, 32, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_st1_2_v[155], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 0, 4 // tri2
    ),
    gsSPNTriangles_5b(
        0, 5, 4, // tri0
        6, 7, 8, // tri1
        6, 9, 7, // tri2
        8, 10, 11 // tri3
    ),
    gsSPNTriangles_5b(
        8, 12, 10, // tri0
        10, 13, 11, // tri1
        8, 7, 12, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 16, // tri0
        18, 19, 20, // tri1
        19, 21, 20, // tri2
        22, 3, 1 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        24, 26, 25, // tri1
        27, 28, 29, // tri2
        27, 29, 30 // tri3
    ),
    gsSPVertex(&grd_s_t_st1_2_v[186], 6, 0),
    gsSPNTrianglesInit_5b(
        2, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_st1_2_v[192], 24, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 8, 9, // tri0
        8, 3, 10, // tri1
        11, 12, 13, // tri2
        14, 11, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        12, 16, 19, // tri1
        20, 21, 22, // tri2
        21, 14, 23 // tri3
    ),
    gsSPEndDisplayList(),
};
