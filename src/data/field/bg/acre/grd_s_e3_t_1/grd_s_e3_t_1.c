#include "libforest/gbi_extensions.h"

extern u8 tunnel_tex_dummy[];
extern u8 rail_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 station_pal_dummy[];
extern u8 rail_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];

static Vtx grd_s_e3_t_1_v[] = {
#include "assets/field/bg/grd_s_e3_t_1_v.inc"
};

extern Gfx grd_s_e3_t_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_e3_t_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_e3_t_1_v[0], 21, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        6, 7, 5, // tri1
        4, 5, 7, // tri2
        6, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 8, // tri0
        7, 8, 10, // tri1
        9, 11, 10, // tri2
        11, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        14, 15, 16, // tri1
        17, 18, 14, // tri2
        19, 20, 17 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_e3_t_1_v[21], 32, 0),
    gsSPNTrianglesInit_5b(
        35, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        7, 8, 5, // tri1
        7, 9, 8, // tri2
        9, 10, 8 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 10, // tri0
        11, 12, 10, // tri1
        11, 13, 12, // tri2
        11, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 13, // tri0
        14, 16, 15, // tri1
        16, 17, 15, // tri2
        16, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        16, 19, 18, // tri0
        6, 5, 20, // tri1
        5, 21, 20, // tri2
        5, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        5, 8, 22, // tri0
        8, 23, 22, // tri1
        8, 10, 23, // tri2
        10, 12, 23 // tri3
    ),
    gsSPNTriangles_5b(
        12, 24, 23, // tri0
        12, 25, 24, // tri1
        12, 13, 25, // tri2
        13, 15, 25 // tri3
    ),
    gsSPNTriangles_5b(
        15, 26, 25, // tri0
        15, 27, 26, // tri1
        15, 17, 27, // tri2
        17, 28, 27 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 28, // tri0
        18, 29, 28, // tri1
        2, 30, 31, // tri2
        2, 3, 30 // tri3
    ),
    gsSPVertex(&grd_s_e3_t_1_v[53], 32, 0),
    gsSPNTrianglesInit_5b(
        39, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 3, // tri0
        4, 6, 5, // tri1
        6, 7, 5, // tri2
        6, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 7, // tri0
        8, 10, 9, // tri1
        10, 11, 9, // tri2
        11, 12, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        13, 14, 12, // tri1
        14, 15, 12, // tri2
        14, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 15, // tri0
        17, 18, 15, // tri1
        17, 19, 18, // tri2
        19, 20, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        22, 21, 23, // tri1
        21, 19, 23, // tri2
        19, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        19, 17, 24, // tri0
        17, 25, 24, // tri1
        17, 16, 25, // tri2
        16, 26, 25 // tri3
    ),
    gsSPNTriangles_5b(
        16, 14, 26, // tri0
        14, 13, 26, // tri1
        13, 27, 26, // tri2
        13, 28, 27 // tri3
    ),
    gsSPNTriangles_5b(
        13, 11, 28, // tri0
        11, 29, 28, // tri1
        11, 10, 29, // tri2
        10, 30, 29 // tri3
    ),
    gsSPNTriangles_5b(
        10, 8, 30, // tri0
        8, 31, 30, // tri1
        8, 6, 31, // tri2
        6, 4, 31 // tri3
    ),
    gsSPVertex(&grd_s_e3_t_1_v[85], 7, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        5, 6, 4, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, station_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(tunnel_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_e3_t_1_v[92], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        8, 0, 9, // tri1
        8, 3, 0, // tri2
        5, 10, 11 // tri3
    ),
    gsSPNTriangles_5b(
        5, 7, 10, // tri0
        12, 13, 14, // tri1
        12, 15, 13, // tri2
        16, 15, 17 // tri3
    ),
    gsSPNTriangles_5b(
        16, 13, 15, // tri0
        15, 18, 17, // tri1
        19, 17, 20, // tri2
        19, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        21, 19, 22, // tri0
        19, 20, 22, // tri1
        23, 22, 24, // tri2
        23, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        25, 23, 26, // tri0
        23, 24, 26, // tri1
        27, 28, 29, // tri2
        2, 1, 28 // tri3
    ),
    gsSPNTriangles_5b(
        27, 4, 6, // tri0
        29, 4, 27, // tri1
        1, 29, 28, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_e3_t_1_v[122], 8, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        5, 6, 4, // tri1
        6, 7, 4, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_e3_t_1_v[130], 8, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 0, 2, // tri1
        3, 2, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 3, 4, // tri0
        6, 5, 4, // tri1
        6, 4, 7, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
