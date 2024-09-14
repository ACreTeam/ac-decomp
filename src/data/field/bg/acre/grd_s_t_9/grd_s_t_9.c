#include "libforest/gbi_extensions.h"

extern u8 rail_pal_dummy[];
extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 rail_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_t_9_v[] = {
#include "assets/field/bg/grd_s_t_9_v.inc"
};

extern Gfx grd_s_t_9_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_9_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_9_v[180], 24, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 7, 10, // tri1
        11, 9, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 13, 17, // tri0
        18, 16, 19, // tri1
        20, 18, 21, // tri2
        22, 20, 23 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_9_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        9, 10, 11, // tri1
        10, 12, 11, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        6, 8, 7, // tri0
        4, 6, 5, // tri1
        13, 14, 15, // tri2
        14, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        16, 18, 19, // tri0
        18, 20, 21, // tri1
        20, 22, 23, // tri2
        24, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 29, // tri0
        28, 30, 29, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_9_v[31], 32, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 1, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        7, 9, 10, // tri1
        11, 12, 8, // tri2
        12, 11, 13 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        16, 14, 13, // tri1
        17, 18, 16, // tri2
        17, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 10, // tri0
        10, 21, 19, // tri1
        21, 22, 19, // tri2
        23, 22, 24 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 19, // tri0
        25, 23, 26, // tri1
        18, 19, 25, // tri2
        25, 19, 23 // tri3
    ),
    gsSPNTriangles_5b(
        24, 27, 28, // tri0
        27, 29, 28, // tri1
        0, 5, 1, // tri2
        2, 30, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_9_v[62], 17, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        3, 4, 0, // tri1
        5, 6, 3 // tri2
    ),
    gsSPNTriangles_5b(
        7, 6, 8, // tri0
        6, 5, 8, // tri1
        5, 9, 8, // tri2
        10, 9, 2 // tri3
    ),
    gsSPNTriangles_5b(
        10, 2, 1, // tri0
        11, 9, 10, // tri1
        11, 8, 9, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        8, 11, 15, // tri0
        11, 16, 15, // tri1
        16, 12, 15, // tri2
        13, 12, 16 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_9_v[79], 20, 0),
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
        10, 11, 9 // tri3
    ),
    gsSPNTriangles_5b(
        7, 10, 9, // tri0
        5, 12, 7, // tri1
        12, 10, 7, // tri2
        3, 13, 5 // tri3
    ),
    gsSPNTriangles_5b(
        13, 12, 5, // tri0
        3, 5, 4, // tri1
        1, 3, 2, // tri2
        1, 14, 3 // tri3
    ),
    gsSPNTriangles_5b(
        14, 13, 3, // tri0
        14, 15, 13, // tri1
        15, 16, 13, // tri2
        13, 16, 12 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 12, // tri0
        12, 17, 10, // tri1
        17, 18, 10, // tri2
        10, 18, 11 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 11, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_9_v[99], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        0, 3, 4, // tri1
        5, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        6, 5, 3, // tri0
        7, 8, 6, // tri1
        9, 10, 7, // tri2
        11, 12, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        11, 14, 13, // tri1
        14, 15, 16, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 19, 21, // tri0
        22, 23, 24, // tri1
        25, 22, 26, // tri2
        17, 25, 27 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        28, 31, 29, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_9_v[131], 25, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        0, 2, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        7, 9, 10, // tri1
        9, 11, 10, // tri2
        6, 8, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 5, 14, // tri0
        1, 4, 2, // tri1
        3, 15, 16, // tri2
        15, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 13, 14, // tri0
        20, 21, 22, // tri1
        21, 23, 24, // tri2
        9, 20, 11 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_9_v[156], 24, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 8, // tri0
        9, 10, 11, // tri1
        10, 3, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        17, 19, 20, // tri1
        14, 21, 22, // tri2
        21, 16, 23 // tri3
    ),
    gsSPEndDisplayList(),
};
