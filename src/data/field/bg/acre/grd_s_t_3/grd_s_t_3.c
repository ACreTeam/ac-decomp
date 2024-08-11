#include "libforest/gbi_extensions.h"

extern u8 rail_pal_dummy[];
extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 rail_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_t_3_v[] = {
#include "assets/field/bg/grd_s_t_3_v.inc"
};

extern Gfx grd_s_t_3_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_3_v[135], 17, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 0, 6 // tri2
    ),
    gsSPNTriangles_5b(
        0, 2, 6, // tri0
        7, 8, 9, // tri1
        10, 7, 9, // tri2
        11, 10, 12 // tri3
    ),
    gsSPNTriangles_5b(
        7, 13, 8, // tri0
        13, 14, 15, // tri1
        1, 11, 16, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 3, 5 // tri2
    ),
    gsSPNTriangles_5b(
        3, 6, 5, // tri0
        3, 7, 6, // tri1
        8, 4, 9, // tri2
        4, 5, 9 // tri3
    ),
    gsSPNTriangles_5b(
        6, 10, 5, // tri0
        6, 11, 10, // tri1
        12, 13, 14, // tri2
        12, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        19, 20, 18, // tri1
        21, 22, 20, // tri2
        23, 24, 22 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 18, // tri0
        19, 21, 20, // tri1
        21, 23, 22, // tri2
        23, 25, 24 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 28, // tri0
        26, 29, 27, // tri1
        26, 30, 29, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_3_v[31], 29, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 4 // tri2
    ),
    gsSPNTriangles_5b(
        3, 6, 5, // tri0
        6, 7, 8, // tri1
        7, 9, 10, // tri2
        9, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        14, 16, 15, // tri1
        17, 14, 18, // tri2
        17, 16, 14 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 16, // tri0
        20, 21, 22, // tri1
        1, 4, 2, // tri2
        4, 23, 2 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 2, // tri0
        7, 10, 8, // tri1
        25, 13, 15, // tri2
        26, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        27, 21, 28, // tri0
        22, 21, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_3_v[60], 20, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        3, 4, 2, // tri1
        5, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 6, // tri0
        9, 10, 11, // tri1
        12, 9, 7, // tri2
        12, 5, 13 // tri3
    ),
    gsSPNTriangles_5b(
        13, 3, 14, // tri0
        1, 14, 3, // tri1
        3, 13, 5, // tri2
        5, 12, 7 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 11, // tri0
        14, 15, 13, // tri1
        13, 16, 12, // tri2
        12, 17, 9 // tri3
    ),
    gsSPNTriangles_5b(
        9, 18, 10, // tri0
        18, 19, 10, // tri1
        17, 18, 9, // tri2
        16, 17, 12 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 13, // tri0
        1, 3, 2, // tri1
        3, 5, 4, // tri2
        5, 7, 6 // tri3
    ),
    gsSPNTriangles_5b(
        7, 11, 8, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_3_v[80], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        1, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        9, 10, 11, // tri1
        10, 3, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 13, 17, // tri0
        14, 18, 19, // tri1
        18, 20, 21, // tri2
        22, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        23, 16, 25, // tri0
        23, 26, 27, // tri1
        28, 29, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_3_v[111], 7, 0),
    gsSPNTrianglesInit_5b(
        3, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 0, 6 // tri2
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_3_v[118], 17, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        1, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 6, // tri0
        7, 8, 9, // tri1
        10, 11, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        13, 7, 14, // tri0
        11, 13, 15, // tri1
        4, 10, 16, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
