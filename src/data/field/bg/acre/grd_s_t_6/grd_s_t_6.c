#include "libforest/gbi_extensions.h"

extern u8 rail_pal_dummy[];
extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 rail_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_t_6_v[] = {
#include "assets/field/bg/grd_s_t_6_v.inc"
};

extern Gfx grd_s_t_6_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_6_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_6_v[204], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        9, 10, 11, // tri1
        10, 4, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        14, 9, 16, // tri0
        17, 18, 19, // tri1
        20, 17, 21, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 22, 24, // tri0
        25, 23, 24, // tri1
        26, 25, 27, // tri2
        28, 29, 30 // tri3
    ),
    gsSPNTriangles_5b(
        29, 26, 31, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_6_v[236], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        1, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 8, // tri1
        10, 11, 9, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 16, // tri0
        15, 17, 16, // tri1
        3, 4, 17, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 23, // tri0
        24, 21, 25, // tri1
        26, 27, 28, // tri2
        29, 18, 30 // tri3
    ),
    gsSPVertex(&grd_s_t_6_v[267], 11, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 9, 6, // tri1
        10, 5, 7, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_6_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 1, 5 // tri2
    ),
    gsSPNTriangles_5b(
        1, 0, 5, // tri0
        3, 6, 2, // tri1
        7, 8, 9, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 9, // tri0
        12, 6, 3, // tri1
        12, 13, 6, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 16, // tri0
        17, 18, 16, // tri1
        17, 19, 18, // tri2
        19, 20, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        21, 22, 20, // tri1
        21, 23, 22, // tri2
        24, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        24, 27, 25, // tri0
        27, 28, 25, // tri1
        28, 27, 8, // tri2
        7, 28, 8 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 26, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_6_v[31], 27, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 3, 4, // tri0
        4, 6, 7, // tri1
        7, 5, 4, // tri2
        8, 5, 7 // tri3
    ),
    gsSPNTriangles_5b(
        6, 9, 7, // tri0
        6, 10, 9, // tri1
        9, 11, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        17, 19, 18, // tri1
        17, 20, 19, // tri2
        16, 14, 17 // tri3
    ),
    gsSPNTriangles_5b(
        14, 13, 17, // tri0
        21, 22, 23, // tri1
        21, 18, 22, // tri2
        18, 19, 22 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 8, // tri0
        26, 25, 24, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_6_v[58], 20, 0),
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
    gsSPVertex(&grd_s_t_6_v[78], 32, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 5, 9, // tri1
        6, 10, 11, // tri2
        10, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        15, 8, 17, // tri1
        18, 19, 20, // tri2
        21, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        2, 21, 24, // tri0
        25, 26, 27, // tri1
        28, 29, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_6_v[109], 25, 0),
    gsSPNTrianglesInit_5b(
        12, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 5, 1 // tri2
    ),
    gsSPNTriangles_5b(
        6, 0, 2, // tri0
        7, 8, 9, // tri1
        10, 7, 11, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 12, 16, // tri0
        17, 18, 19, // tri1
        20, 17, 21, // tri2
        13, 22, 23 // tri3
    ),
    gsSPNTriangles_5b(
        22, 20, 24, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_6_v[134], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        0, 7, 8, // tri0
        9, 10, 11, // tri1
        10, 12, 13, // tri2
        14, 2, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 4, 17, // tri0
        18, 19, 20, // tri1
        7, 9, 21, // tri2
        12, 18, 20 // tri3
    ),
    gsSPNTriangles_5b(
        7, 21, 8, // tri0
        16, 17, 19, // tri1
        22, 23, 24, // tri2
        25, 26, 27 // tri3
    ),
    gsSPNTriangles_5b(
        28, 25, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_6_v[164], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 0, 9, // tri0
        3, 10, 11, // tri1
        12, 13, 14, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        8, 9, 21, // tri1
        22, 20, 23, // tri2
        12, 5, 13 // tri3
    ),
    gsSPNTriangles_5b(
        24, 22, 23, // tri0
        16, 21, 17, // tri1
        18, 25, 19, // tri2
        10, 14, 11 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 28, // tri0
        29, 26, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_6_v[195], 9, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 0, 8, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
