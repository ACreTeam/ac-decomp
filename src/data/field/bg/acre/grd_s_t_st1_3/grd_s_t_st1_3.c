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

static Vtx grd_s_t_st1_3_v[] = {
#include "assets/field/bg/grd_s_t_st1_3_v.inc"
};

extern Gfx grd_s_t_st1_3_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_st1_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_st1_3_v[190], 13, 0),
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
    gsSPVertex(&grd_s_t_st1_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 5, // tri0
        9, 10, 11, // tri1
        12, 13, 14, // tri2
        13, 15, 14 // tri3
    ),
    gsSPNTriangles_5b(
        16, 12, 17, // tri0
        6, 16, 17, // tri1
        18, 19, 20, // tri2
        21, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        7, 6, 21, // tri0
        22, 23, 0, // tri1
        5, 16, 6, // tri2
        13, 24, 15 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 20, // tri0
        26, 27, 28, // tri1
        27, 9, 11, // tri2
        29, 30, 31 // tri3
    ),
    gsSPVertex(&grd_s_t_st1_3_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        0, 3, 1, // tri1
        3, 5, 4, // tri2
        5, 7, 6 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        10, 11, 12, // tri1
        13, 14, 11, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        18, 21, 19, // tri1
        22, 23, 24, // tri2
        24, 23, 25 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 26, // tri0
        19, 27, 20, // tri1
        28, 29, 26, // tri2
        29, 15, 30 // tri3
    ),
    gsSPNTriangles_5b(
        17, 30, 15, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_st1_3_v[63], 3, 0),
    gsSPNTrianglesInit_5b(
        1, // tri count
        0, 1, 2, // tri0
        0, 0, 0, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_st1_3_v[66], 25, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        2, 3, 4, // tri1
        2, 1, 3 // tri2
    ),
    gsSPNTriangles_5b(
        0, 5, 1, // tri0
        3, 6, 4, // tri1
        7, 8, 6, // tri2
        7, 9, 8 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        12, 13, 11, // tri1
        14, 15, 13, // tri2
        15, 14, 16 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 15, // tri0
        17, 18, 19, // tri1
        18, 20, 19, // tri2
        20, 21, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 22, 21, // tri0
        22, 23, 21, // tri1
        22, 24, 23, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_st1_3_v[91], 31, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        2, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 0, // tri0
        8, 9, 6, // tri1
        10, 11, 8, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 12, // tri0
        13, 14, 15, // tri1
        16, 17, 18, // tri2
        19, 16, 20 // tri3
    ),
    gsSPNTriangles_5b(
        17, 21, 22, // tri0
        21, 23, 24, // tri1
        23, 25, 24, // tri2
        26, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        27, 29, 30, // tri0
        29, 19, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_st1_3_v[122], 21, 0),
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
    gsDPLoadTLUT_Dolphin(15, 16, 1, station_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(station_tex_dummy, G_IM_FMT_CI, 128, 32, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_st1_3_v[143], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 6, 7, // tri0
        8, 9, 10, // tri1
        8, 11, 9, // tri2
        10, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        10, 14, 12, // tri0
        12, 15, 13, // tri1
        10, 9, 14, // tri2
        16, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 18, // tri0
        20, 2, 1, // tri1
        12, 21, 22, // tri2
        21, 23, 22 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 26, // tri0
        24, 26, 27, // tri1
        28, 29, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_st1_3_v[174], 3, 0),
    gsSPNTrianglesInit_5b(
        1, // tri count
        0, 1, 2, // tri0
        0, 0, 0, // tri1
        0, 0, 0 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_st1_3_v[177], 13, 0),
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
