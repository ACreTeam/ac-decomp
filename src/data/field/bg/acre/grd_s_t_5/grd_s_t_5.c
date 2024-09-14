#include "libforest/gbi_extensions.h"

extern u8 rail_pal_dummy[];
extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 rail_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_t_5_v[] = {
#include "assets/field/bg/grd_s_t_5_v.inc"
};

extern Gfx grd_s_t_5_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 1, 0, TEXEL0, TEXEL1, COMBINED, 0, SHADE, TEXEL0, COMBINED, 0, PRIM_LOD_FRAC, PRIMITIVE),
    gsDPSetPrimColor(0, 50, 255, 255, 255, 50),
    gsDPSetEnvColor(0x00, 0x64, 0xFF, 0xFF),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(water_1_tex_dummy, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPLoadMultiBlock_4b_Dolphin(water_2_tex_dummy, 1, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x08000000),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_5_v[244], 4, 0),
    gsSPNTrianglesInit_5b(
        2, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        0, 0, 0 // tri2
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_5_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_5_v[228], 16, 0),
    gsSPNTrianglesInit_5b(
        9, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        4, 8, 5, // tri1
        9, 10, 2, // tri2
        7, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 8, 14, // tri0
        11, 3, 15, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_5_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        4, 6, 5, // tri0
        6, 7, 5, // tri1
        2, 8, 0, // tri2
        9, 10, 11 // tri3
    ),
    gsSPNTriangles_5b(
        10, 12, 11, // tri0
        13, 14, 15, // tri1
        14, 16, 15, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        17, 20, 18, // tri0
        6, 21, 7, // tri1
        6, 22, 21, // tri2
        13, 15, 9 // tri3
    ),
    gsSPNTriangles_5b(
        15, 23, 9, // tri0
        24, 25, 26, // tri1
        25, 27, 26, // tri2
        25, 28, 27 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 31, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_5_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        3, 2, 1, // tri1
        2, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        6, 9, 7, // tri1
        9, 10, 7, // tri2
        11, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        11, 14, 12, // tri0
        15, 16, 12, // tri1
        15, 17, 16, // tri2
        2, 18, 4 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 4, // tri0
        20, 21, 22, // tri1
        21, 23, 22, // tri2
        23, 24, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 25, 24, // tri0
        25, 26, 24, // tri1
        25, 27, 26, // tri2
        27, 28, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 29, 28, // tri0
        30, 2, 3, // tri1
        9, 31, 10, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_5_v[64], 27, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 4, // tri0
        8, 7, 9, // tri1
        8, 10, 7, // tri2
        10, 4, 7 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        12, 14, 13, // tri1
        14, 15, 13, // tri2
        15, 16, 13 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 10, // tri0
        17, 19, 18, // tri1
        20, 21, 19, // tri2
        20, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        23, 26, 24, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_5_v[91], 20, 0),
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
    gsSPVertex(&grd_s_t_5_v[111], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 1, 5 // tri2
    ),
    gsSPNTriangles_5b(
        4, 6, 1, // tri0
        7, 8, 9, // tri1
        10, 11, 12, // tri2
        11, 13, 12 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        15, 17, 16, // tri1
        17, 18, 16, // tri2
        19, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 24, // tri0
        5, 22, 25, // tri1
        26, 3, 27, // tri2
        28, 29, 30 // tri3
    ),
    gsSPVertex(&grd_s_t_5_v[142], 32, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 11, 12, // tri1
        13, 14, 10, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        21, 18, 22, // tri1
        19, 23, 24, // tri2
        23, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 29, // tri0
        28, 21, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_5_v[173], 10, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 8, 9, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_5_v[183], 16, 0),
    gsSPNTrianglesInit_5b(
        9, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        4, 8, 5, // tri1
        9, 10, 2, // tri2
        11, 8, 12 // tri3
    ),
    gsSPNTriangles_5b(
        7, 13, 14, // tri0
        13, 3, 15, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_5_v[199], 29, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        5, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 6, // tri0
        9, 10, 8, // tri1
        11, 12, 10, // tri2
        13, 14, 12 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 14, // tri0
        17, 18, 16, // tri1
        19, 20, 18, // tri2
        19, 21, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 20, // tri0
        23, 24, 22, // tri1
        25, 26, 24, // tri2
        27, 28, 26 // tri3
    ),
    gsSPNTriangles_5b(
        6, 5, 7, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
