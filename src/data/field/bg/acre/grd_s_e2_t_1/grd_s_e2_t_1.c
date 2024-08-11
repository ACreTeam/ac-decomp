#include "libforest/gbi_extensions.h"

extern u8 tunnel_tex_dummy[];
extern u8 rail_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 station_pal_dummy[];
extern u8 rail_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];

static Vtx grd_s_e2_t_1_v[] = {
#include "assets/field/bg/grd_s_e2_t_1_v.inc"
};

extern Gfx grd_s_e2_t_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_e2_t_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_e2_t_1_v[0], 21, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        3, 4, 2, // tri1
        2, 4, 0 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        6, 7, 5, // tri1
        5, 7, 4, // tri2
        8, 9, 10 // tri3
    ),
    gsSPNTriangles_5b(
        11, 9, 8, // tri0
        12, 8, 10, // tri1
        13, 10, 7, // tri2
        12, 10, 13 // tri3
    ),
    gsSPNTriangles_5b(
        7, 6, 13, // tri0
        14, 15, 16, // tri1
        17, 18, 14, // tri2
        19, 20, 17 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_e2_t_1_v[21], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        3, 2, 1, // tri1
        2, 3, 4 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 3, // tri0
        2, 4, 6, // tri1
        4, 7, 6, // tri2
        8, 9, 10 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 10, // tri0
        12, 13, 14, // tri1
        15, 16, 12, // tri2
        14, 15, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 17, 14, // tri0
        18, 17, 13, // tri1
        16, 15, 19, // tri2
        19, 15, 20 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 11, // tri0
        21, 10, 11, // tri1
        11, 19, 20, // tri2
        17, 18, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 17, 22, // tri0
        24, 21, 25, // tri1
        10, 21, 24, // tri2
        23, 22, 26 // tri3
    ),
    gsSPNTriangles_5b(
        25, 27, 24, // tri0
        28, 29, 30, // tri1
        30, 29, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_e2_t_1_v[53], 32, 0),
    gsSPNTrianglesInit_5b(
        35, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        2, 4, 0 // tri2
    ),
    gsSPNTriangles_5b(
        5, 0, 6, // tri0
        7, 1, 5, // tri1
        5, 1, 0, // tri2
        7, 8, 1 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        10, 11, 8, // tri1
        12, 11, 10, // tri2
        10, 8, 9 // tri3
    ),
    gsSPNTriangles_5b(
        13, 0, 14, // tri0
        13, 6, 0, // tri1
        15, 16, 17, // tri2
        15, 18, 16 // tri3
    ),
    gsSPNTriangles_5b(
        15, 19, 18, // tri0
        13, 14, 20, // tri1
        21, 22, 8, // tri2
        11, 23, 21 // tri3
    ),
    gsSPNTriangles_5b(
        8, 11, 21, // tri0
        22, 1, 8, // tri1
        3, 1, 22, // tri2
        23, 11, 24 // tri3
    ),
    gsSPNTriangles_5b(
        24, 11, 16, // tri0
        16, 18, 25, // tri1
        18, 26, 25, // tri2
        25, 24, 16 // tri3
    ),
    gsSPNTriangles_5b(
        2, 3, 27, // tri0
        2, 27, 28, // tri1
        4, 28, 29, // tri2
        2, 28, 4 // tri3
    ),
    gsSPNTriangles_5b(
        4, 29, 30, // tri0
        22, 27, 3, // tri1
        21, 31, 22, // tri2
        22, 31, 27 // tri3
    ),
    gsSPVertex(&grd_s_e2_t_1_v[85], 21, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 6, 7, // tri0
        8, 7, 1, // tri1
        4, 7, 8, // tri2
        8, 1, 3 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        10, 12, 11, // tri1
        11, 12, 13, // tri2
        11, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 6, 5, // tri0
        15, 16, 6, // tri1
        17, 18, 16, // tri2
        17, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        5, 20, 15, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, station_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(tunnel_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_e2_t_1_v[106], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 2, 9, // tri1
        2, 3, 9, // tri2
        10, 11, 5 // tri3
    ),
    gsSPNTriangles_5b(
        11, 7, 5, // tri0
        12, 13, 14, // tri1
        13, 15, 14, // tri2
        16, 15, 17 // tri3
    ),
    gsSPNTriangles_5b(
        15, 13, 17, // tri0
        16, 18, 15, // tri1
        19, 16, 20, // tri2
        16, 17, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 20, 22, // tri0
        21, 19, 20, // tri1
        23, 21, 24, // tri2
        21, 22, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 24, 26, // tri0
        25, 23, 24, // tri1
        27, 28, 29, // tri2
        28, 1, 0 // tri3
    ),
    gsSPNTriangles_5b(
        4, 6, 29, // tri0
        29, 6, 27, // tri1
        28, 27, 1, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_e2_t_1_v[136], 8, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 1, // tri0
        4, 6, 5, // tri1
        4, 7, 6, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_e2_t_1_v[144], 8, 0),
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
