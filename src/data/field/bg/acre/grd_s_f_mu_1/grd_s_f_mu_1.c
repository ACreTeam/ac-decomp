#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 stone_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_mu_1_v[] = {
#include "assets/field/bg/grd_s_f_mu_1_v.inc"
};

extern Gfx grd_s_f_mu_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_mu_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_mu_1_v[145], 15, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 10, // tri1
        9, 11, 12, // tri2
        11, 13, 14 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_mu_1_v[0], 17, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        1, 3, 5, // tri0
        6, 7, 8, // tri1
        7, 9, 10, // tri2
        9, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 14, // tri0
        11, 14, 12, // tri1
        13, 15, 16, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_mu_1_v[17], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 10, // tri1
        9, 11, 12, // tri2
        11, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 16, // tri0
        17, 18, 19, // tri1
        20, 21, 22, // tri2
        20, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        18, 20, 23, // tri0
        21, 24, 25, // tri1
        24, 26, 27, // tri2
        26, 1, 28 // tri3
    ),
    gsSPNTriangles_5b(
        2, 29, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_mu_1_v[48], 30, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 10, // tri1
        9, 11, 12, // tri2
        11, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        18, 15, 19, // tri1
        20, 18, 21, // tri2
        22, 20, 23 // tri3
    ),
    gsSPNTriangles_5b(
        24, 22, 25, // tri0
        26, 24, 27, // tri1
        28, 26, 29, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_mu_1_v[78], 15, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 10, // tri1
        9, 11, 12, // tri2
        11, 13, 14 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_mu_1_v[93], 32, 0),
    gsSPNTrianglesInit_5b(
        29, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        5, 4, 6, // tri0
        6, 8, 7, // tri1
        7, 8, 9, // tri2
        3, 10, 4 // tri3
    ),
    gsSPNTriangles_5b(
        3, 11, 10, // tri0
        11, 12, 10, // tri1
        13, 14, 12, // tri2
        13, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 12, // tri0
        8, 16, 9, // tri1
        16, 17, 9, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 13, // tri0
        19, 14, 13, // tri1
        19, 20, 14, // tri2
        18, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        21, 18, 16, // tri0
        18, 17, 16, // tri1
        15, 23, 12, // tri2
        15, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 23, // tri0
        25, 24, 26, // tri1
        26, 27, 25, // tri2
        28, 27, 26 // tri3
    ),
    gsSPNTriangles_5b(
        29, 27, 28, // tri0
        29, 30, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_f_mu_1_v[124], 21, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        0, 5, 3, // tri0
        6, 5, 0, // tri1
        7, 8, 9, // tri2
        7, 10, 8 // tri3
    ),
    gsSPNTriangles_5b(
        7, 11, 10, // tri0
        7, 12, 11, // tri1
        13, 9, 8, // tri2
        13, 14, 9 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 14, // tri0
        15, 16, 17, // tri1
        15, 18, 16, // tri2
        19, 20, 18 // tri3
    ),
    gsSPNTriangles_5b(
        20, 16, 18, // tri0
        19, 4, 20, // tri1
        19, 1, 4, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
