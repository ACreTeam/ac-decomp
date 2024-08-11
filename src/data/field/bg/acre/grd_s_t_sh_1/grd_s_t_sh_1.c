#include "libforest/gbi_extensions.h"

extern u8 rail_pal_dummy[];
extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 stone_tex_dummy[];
extern u8 rail_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_t_sh_1_v[] = {
#include "assets/field/bg/grd_s_t_sh_1_v.inc"
};

extern Gfx grd_s_t_sh_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_sh_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_sh_1_v[143], 19, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        3, 1, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 6, 3, // tri0
        9, 10, 11, // tri1
        12, 10, 13, // tri2
        11, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 14, 5, // tri0
        17, 12, 18, // tri1
        6, 8, 7, // tri2
        10, 9, 13 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_sh_1_v[0], 19, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        3, 1, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 6, 3, // tri0
        9, 10, 11, // tri1
        12, 10, 13, // tri2
        11, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 14, 5, // tri0
        17, 12, 18, // tri1
        6, 8, 7, // tri2
        10, 9, 13 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_sh_1_v[19], 32, 0),
    gsSPNTrianglesInit_5b(
        28, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        6, 8, 9, // tri1
        6, 7, 8, // tri2
        9, 8, 10 // tri3
    ),
    gsSPNTriangles_5b(
        8, 11, 10, // tri0
        10, 12, 13, // tri1
        10, 11, 12, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 14, // tri0
        17, 18, 14, // tri1
        17, 19, 18, // tri2
        19, 20, 18 // tri3
    ),
    gsSPNTriangles_5b(
        20, 0, 18, // tri0
        20, 1, 0, // tri1
        20, 21, 1, // tri2
        3, 1, 22 // tri3
    ),
    gsSPNTriangles_5b(
        22, 1, 23, // tri0
        22, 24, 3, // tri1
        24, 25, 3, // tri2
        21, 26, 1 // tri3
    ),
    gsSPNTriangles_5b(
        16, 15, 27, // tri0
        15, 28, 27, // tri1
        28, 29, 27, // tri2
        29, 28, 30 // tri3
    ),
    gsSPNTriangles_5b(
        28, 31, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_sh_1_v[51], 27, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        6, 7, 8, // tri1
        7, 9, 8, // tri2
        10, 7, 6 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 7, // tri0
        11, 12, 7, // tri1
        11, 4, 12, // tri2
        4, 13, 12 // tri3
    ),
    gsSPNTriangles_5b(
        5, 13, 4, // tri0
        13, 14, 15, // tri1
        13, 5, 14, // tri2
        15, 14, 16 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        16, 14, 17, // tri1
        19, 20, 18, // tri2
        18, 17, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 22, // tri0
        20, 19, 21, // tri1
        9, 23, 24, // tri2
        24, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        9, 24, 26, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_sh_1_v[78], 20, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 5, 4, // tri1
        8, 9, 5, // tri2
        10, 11, 8 // tri3
    ),
    gsSPNTriangles_5b(
        11, 9, 8, // tri0
        12, 11, 10, // tri1
        12, 13, 11, // tri2
        13, 14, 11 // tri3
    ),
    gsSPNTriangles_5b(
        14, 3, 11, // tri0
        11, 1, 9, // tri1
        11, 3, 1, // tri2
        9, 1, 5 // tri3
    ),
    gsSPNTriangles_5b(
        1, 15, 5, // tri0
        5, 16, 7, // tri1
        5, 15, 16, // tri2
        15, 17, 16 // tri3
    ),
    gsSPNTriangles_5b(
        15, 18, 17, // tri0
        1, 18, 15, // tri1
        1, 0, 18, // tri2
        14, 19, 3 // tri3
    ),
    gsSPNTriangles_5b(
        19, 2, 3, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_sh_1_v[98], 30, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        5, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 9, 11, // tri1
        12, 11, 6, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 14, // tri0
        18, 19, 17, // tri1
        20, 21, 19, // tri2
        22, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 24, 26, // tri0
        27, 26, 28, // tri1
        29, 28, 21, // tri2
        17, 16, 18 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 25, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_sh_1_v[128], 15, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 7, 4, // tri0
        9, 10, 11, // tri1
        12, 13, 10, // tri2
        14, 11, 6 // tri3
    ),
    gsSPEndDisplayList(),
};
