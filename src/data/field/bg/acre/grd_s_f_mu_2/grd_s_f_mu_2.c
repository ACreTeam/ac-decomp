#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 stone_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_mu_2_v[] = {
#include "assets/field/bg/grd_s_f_mu_2_v.inc"
};

extern Gfx grd_s_f_mu_2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_mu_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_mu_2_v[146], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 10, // tri1
        9, 11, 12, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_mu_2_v[0], 19, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        3, 6, 4, // tri0
        5, 7, 8, // tri1
        7, 9, 10, // tri2
        9, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        13, 15, 16, // tri1
        11, 13, 16, // tri2
        14, 17, 18 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_mu_2_v[19], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 10, // tri1
        9, 11, 12, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_mu_2_v[32], 32, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        1, 3, 6, // tri0
        4, 7, 8, // tri1
        7, 9, 8, // tri2
        7, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 12, // tri0
        10, 12, 9, // tri1
        11, 13, 14, // tri2
        13, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 18, // tri0
        17, 19, 20, // tri1
        19, 21, 20, // tri2
        19, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 24, // tri0
        23, 25, 24, // tri1
        26, 27, 25, // tri2
        26, 28, 27 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_mu_2_v[63], 24, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 10, // tri1
        9, 11, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        14, 16, 17, // tri0
        16, 18, 19, // tri1
        18, 20, 21, // tri2
        20, 22, 23 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_mu_2_v[87], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 4, // tri0
        7, 8, 5, // tri1
        0, 9, 7, // tri2
        4, 10, 3 // tri3
    ),
    gsSPNTriangles_5b(
        6, 10, 4, // tri0
        11, 12, 6, // tri1
        12, 10, 6, // tri2
        12, 13, 10 // tri3
    ),
    gsSPNTriangles_5b(
        12, 14, 13, // tri0
        14, 15, 13, // tri1
        15, 16, 13, // tri2
        17, 18, 15 // tri3
    ),
    gsSPNTriangles_5b(
        15, 18, 16, // tri0
        7, 9, 8, // tri1
        8, 19, 20, // tri2
        8, 9, 19 // tri3
    ),
    gsSPNTriangles_5b(
        9, 21, 19, // tri0
        9, 22, 21, // tri1
        23, 24, 25, // tri2
        26, 27, 25 // tri3
    ),
    gsSPNTriangles_5b(
        27, 23, 25, // tri0
        28, 27, 29, // tri1
        30, 31, 28, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_mu_2_v[119], 27, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        2, 1, 3, // tri1
        4, 1, 0 // tri2
    ),
    gsSPNTriangles_5b(
        1, 4, 5, // tri0
        6, 7, 8, // tri1
        7, 6, 9, // tri2
        6, 5, 9 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        10, 5, 4, // tri1
        9, 5, 10, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 12, // tri0
        12, 14, 15, // tri1
        15, 11, 12, // tri2
        15, 14, 16 // tri3
    ),
    gsSPNTriangles_5b(
        14, 17, 16, // tri0
        18, 19, 8, // tri1
        19, 20, 21, // tri2
        22, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 22, // tri0
        26, 23, 22, // tri1
        18, 20, 19, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
