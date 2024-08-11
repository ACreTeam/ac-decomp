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

static Vtx grd_s_t_st1_1_v[] = {
#include "assets/field/bg/grd_s_t_st1_1_v.inc"
};

extern Gfx grd_s_t_st1_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_st1_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_st1_1_v[180], 15, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        3, 2, 4, // tri1
        5, 4, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 11, 8, // tri1
        12, 6, 11, // tri2
        13, 9, 14 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, station_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(station_tex_dummy, G_IM_FMT_CI, 128, 32, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_st1_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        5, 9, 7, // tri1
        7, 10, 8, // tri2
        5, 4, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        12, 14, 13, // tri1
        15, 16, 17, // tri2
        16, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 1, // tri0
        20, 2, 1, // tri1
        1, 0, 21, // tri2
        22, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        23, 25, 24, // tri0
        26, 27, 28, // tri1
        26, 28, 29, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_st1_1_v[30], 6, 0),
    gsSPNTrianglesInit_5b(
        2, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_st1_1_v[36], 15, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        3, 2, 4, // tri1
        5, 4, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 11, 8, // tri1
        12, 6, 11, // tri2
        13, 9, 14 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_st1_1_v[51], 21, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 1, 0 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 1, // tri0
        6, 7, 4, // tri1
        7, 5, 4, // tri2
        8, 7, 6 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 7, // tri0
        9, 10, 7, // tri1
        10, 11, 7, // tri2
        7, 12, 5 // tri3
    ),
    gsSPNTriangles_5b(
        7, 11, 12, // tri0
        5, 12, 1, // tri1
        12, 13, 1, // tri2
        1, 14, 3 // tri3
    ),
    gsSPNTriangles_5b(
        1, 13, 14, // tri0
        13, 15, 14, // tri1
        13, 16, 15, // tri2
        12, 16, 13 // tri3
    ),
    gsSPNTriangles_5b(
        12, 17, 16, // tri0
        11, 18, 12, // tri1
        18, 17, 12, // tri2
        11, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        10, 20, 11, // tri0
        20, 19, 11, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_st1_1_v[72], 32, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 2, // tri0
        1, 6, 3, // tri1
        1, 7, 6, // tri2
        7, 8, 6 // tri3
    ),
    gsSPNTriangles_5b(
        4, 9, 10, // tri0
        9, 11, 10, // tri1
        4, 3, 9, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 14, // tri0
        16, 17, 18, // tri1
        17, 19, 18, // tri2
        18, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        21, 20, 22, // tri1
        20, 23, 22, // tri2
        22, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 24, // tri0
        26, 27, 28, // tri1
        26, 29, 27, // tri2
        29, 30, 27 // tri3
    ),
    gsSPNTriangles_5b(
        12, 31, 13, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_st1_1_v[104], 18, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 5 // tri2
    ),
    gsSPNTriangles_5b(
        3, 6, 7, // tri0
        7, 6, 8, // tri1
        8, 9, 7, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 9, // tri0
        10, 12, 11, // tri1
        12, 13, 11, // tri2
        11, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 14, // tri0
        16, 17, 4, // tri1
        15, 17, 16, // tri2
        15, 14, 17 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_st1_1_v[122], 27, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 7, 4, // tri0
        9, 2, 10, // tri1
        11, 12, 13, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        14, 17, 15, // tri0
        15, 11, 16, // tri1
        18, 17, 19, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        23, 21, 24, // tri1
        24, 18, 26, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_st1_1_v[149], 31, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 9, 6, // tri1
        9, 4, 6, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        13, 14, 12, // tri1
        14, 15, 12, // tri2
        2, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        3, 18, 1, // tri0
        19, 20, 18, // tri1
        19, 21, 20, // tri2
        22, 21, 23 // tri3
    ),
    gsSPNTriangles_5b(
        10, 22, 24, // tri0
        15, 25, 26, // tri1
        26, 27, 28, // tri2
        27, 29, 28 // tri3
    ),
    gsSPNTriangles_5b(
        9, 30, 29, // tri0
        9, 8, 30, // tri1
        2, 17, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
