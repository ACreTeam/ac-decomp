#include "libforest/gbi_extensions.h"

extern u8 rail_pal_dummy[];
extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 rail_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_t_7_v[] = {
#include "assets/field/bg/grd_s_t_7_v.inc"
};

extern Gfx grd_s_t_7_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_7_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_7_v[196], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 9, 10, // tri1
        8, 11, 9, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 14, // tri0
        16, 3, 17, // tri1
        18, 19, 20, // tri2
        21, 20, 8 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 24, // tri0
        25, 24, 26, // tri1
        27, 28, 29, // tri2
        30, 31, 19 // tri3
    ),
    gsSPVertex(&grd_s_t_7_v[228], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        1, 6, 2 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        7, 10, 8, // tri1
        11, 12, 13, // tri2
        14, 13, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 15, 17, // tri0
        18, 17, 19, // tri1
        20, 19, 21, // tri2
        22, 21, 23 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 26, // tri0
        27, 24, 26, // tri1
        28, 29, 25, // tri2
        30, 27, 31 // tri3
    ),
    gsSPVertex(&grd_s_t_7_v[260], 17, 0),
    gsSPNTrianglesInit_5b(
        8, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        9, 2, 10, // tri0
        7, 11, 12, // tri1
        11, 10, 12, // tri2
        6, 8, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_7_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        8, 9, 10, // tri1
        11, 12, 9, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        15, 17, 16, // tri1
        13, 15, 14, // tri2
        11, 13, 12 // tri3
    ),
    gsSPNTriangles_5b(
        8, 11, 9, // tri0
        18, 19, 20, // tri1
        21, 22, 19, // tri2
        23, 24, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 25, 24, // tri0
        25, 26, 24, // tri1
        27, 28, 26, // tri2
        29, 30, 28 // tri3
    ),
    gsSPVertex(&grd_s_t_7_v[31], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        1, 0, 3, // tri1
        4, 5, 3 // tri2
    ),
    gsSPNTriangles_5b(
        6, 5, 7, // tri0
        4, 8, 9, // tri1
        4, 3, 8, // tri2
        3, 0, 8 // tri3
    ),
    gsSPNTriangles_5b(
        0, 2, 10, // tri0
        10, 2, 11, // tri1
        12, 6, 7, // tri2
        6, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        15, 14, 17, // tri1
        18, 19, 20, // tri2
        13, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 21, 17, // tri0
        21, 23, 22, // tri1
        24, 25, 26, // tri2
        25, 24, 27 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        29, 31, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_7_v[63], 20, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        2, 3, 4, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        7, 9, 8, // tri1
        5, 7, 6, // tri2
        3, 5, 4 // tri3
    ),
    gsSPNTriangles_5b(
        1, 3, 2, // tri0
        1, 10, 3, // tri1
        10, 11, 3, // tri2
        3, 11, 5 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 5, // tri0
        5, 12, 7, // tri1
        12, 13, 7, // tri2
        13, 14, 9 // tri3
    ),
    gsSPNTriangles_5b(
        7, 13, 9, // tri0
        10, 15, 11, // tri1
        15, 16, 11, // tri2
        11, 16, 12 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 12, // tri0
        12, 17, 13, // tri1
        17, 18, 13, // tri2
        13, 18, 14 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 14, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_7_v[83], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        3, 2, 4, // tri1
        5, 6, 1 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 6, // tri0
        9, 10, 11, // tri1
        12, 4, 10, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        19, 20, 21, // tri1
        22, 15, 23, // tri2
        24, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 17, // tri0
        20, 25, 21, // tri1
        26, 27, 25, // tri2
        28, 29, 30 // tri3
    ),
    gsSPVertex(&grd_s_t_7_v[114], 10, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 2, 7 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 8, // tri0
        9, 6, 7, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_7_v[124], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
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
        13, 15, 14, // tri0
        16, 0, 17, // tri1
        18, 11, 2, // tri2
        3, 18, 2 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 21, // tri0
        22, 21, 23, // tri1
        24, 23, 9, // tri2
        25, 26, 27 // tri3
    ),
    gsSPNTriangles_5b(
        19, 25, 20, // tri0
        26, 28, 27, // tri1
        26, 29, 28, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_7_v[154], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 2, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 7, 9, // tri0
        10, 11, 12, // tri1
        13, 12, 6, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 9, 15, // tri0
        18, 19, 20, // tri1
        21, 22, 23, // tri2
        24, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 24, 26, // tri0
        28, 29, 25, // tri1
        21, 27, 22, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_7_v[184], 12, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        0, 6, 1 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        6, 10, 11, // tri1
        10, 9, 11, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
