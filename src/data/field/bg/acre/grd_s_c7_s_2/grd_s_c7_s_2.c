#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c7_s_2_v[] = {
#include "assets/field/bg/grd_s_c7_s_2_v.inc"
};

extern Gfx grd_s_c7_s_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c7_s_2_v[183], 17, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 3, 8, // tri0
        3, 4, 8, // tri1
        9, 10, 11, // tri2
        12, 9, 11 // tri3
    ),
    gsSPNTriangles_5b(
        1, 12, 13, // tri0
        9, 14, 10, // tri1
        14, 15, 16, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_s_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        3, 2, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 6, // tri0
        7, 9, 8, // tri1
        5, 7, 6, // tri2
        4, 10, 5 // tri3
    ),
    gsSPNTriangles_5b(
        11, 10, 4, // tri0
        12, 11, 13, // tri1
        12, 10, 11, // tri2
        14, 13, 15 // tri3
    ),
    gsSPNTriangles_5b(
        13, 16, 12, // tri0
        13, 14, 16, // tri1
        17, 18, 19, // tri2
        17, 20, 18 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 18, // tri0
        21, 22, 18, // tri1
        22, 23, 18, // tri2
        22, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        25, 27, 28, // tri1
        14, 15, 29, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_2_v[30], 32, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        9, 10, 11, // tri1
        12, 13, 14, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        15, 5, 16, // tri0
        4, 17, 16, // tri1
        16, 5, 4, // tri2
        18, 10, 19 // tri3
    ),
    gsSPNTriangles_5b(
        18, 11, 10, // tri0
        19, 1, 18, // tri1
        1, 20, 2, // tri2
        1, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        6, 5, 8, // tri0
        21, 22, 23, // tri1
        23, 24, 21, // tri2
        25, 26, 23 // tri3
    ),
    gsSPNTriangles_5b(
        26, 24, 23, // tri0
        27, 25, 28, // tri1
        27, 26, 25, // tri2
        29, 30, 31 // tri3
    ),
    gsSPNTriangles_5b(
        30, 7, 31, // tri0
        30, 8, 7, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_2_v[62], 22, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 4, 7, // tri1
        4, 8, 7, // tri2
        11, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        7, 14, 10, // tri0
        14, 15, 10, // tri1
        15, 16, 10, // tri2
        17, 18, 16 // tri3
    ),
    gsSPNTriangles_5b(
        18, 17, 19, // tri0
        20, 21, 19, // tri1
        21, 18, 19, // tri2
        9, 21, 20 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_s_2_v[84], 32, 0),
    gsSPNTrianglesInit_5b(
        34, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        1, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 2, // tri0
        6, 1, 0, // tri1
        6, 7, 1, // tri2
        7, 8, 4 // tri3
    ),
    gsSPNTriangles_5b(
        7, 4, 1, // tri0
        9, 10, 7, // tri1
        9, 7, 6, // tri2
        10, 11, 8 // tri3
    ),
    gsSPNTriangles_5b(
        10, 8, 7, // tri0
        12, 13, 9, // tri1
        13, 10, 9, // tri2
        13, 14, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 11, 10, // tri0
        15, 16, 12, // tri1
        16, 13, 12, // tri2
        16, 17, 14 // tri3
    ),
    gsSPNTriangles_5b(
        16, 14, 13, // tri0
        18, 19, 16, // tri1
        18, 16, 15, // tri2
        19, 20, 17 // tri3
    ),
    gsSPNTriangles_5b(
        19, 17, 16, // tri0
        21, 22, 19, // tri1
        21, 19, 18, // tri2
        22, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        23, 25, 26, // tri1
        24, 27, 25, // tri2
        28, 29, 24 // tri3
    ),
    gsSPNTriangles_5b(
        28, 24, 23, // tri0
        29, 30, 27, // tri1
        29, 27, 24, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_2_v[115], 9, 0),
    gsSPNTrianglesInit_5b(
        8, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 3, // tri0
        6, 7, 1, // tri1
        6, 1, 0, // tri2
        7, 8, 4 // tri3
    ),
    gsSPNTriangles_5b(
        7, 4, 1, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_s_2_v[124], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
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
        14, 16, 15, // tri0
        17, 18, 19, // tri1
        20, 21, 22, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 13, 27, // tri0
        26, 27, 24, // tri1
        20, 28, 21, // tri2
        29, 30, 31 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 31, // tri0
        18, 20, 22, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_c7_s_2_v[156], 10, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 0, 5 // tri2
    ),
    gsSPNTriangles_5b(
        3, 6, 7, // tri0
        8, 4, 9, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_s_2_v[166], 17, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        4, 9, 10, // tri0
        11, 3, 12, // tri1
        13, 14, 15, // tri2
        1, 11, 16 // tri3
    ),
    gsSPNTriangles_5b(
        13, 6, 14, // tri0
        9, 13, 15, // tri1
        11, 12, 16, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
