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

static Vtx grd_s_t_po_1_v[] = {
#include "assets/field/bg/grd_s_t_po_1_v.inc"
};

extern Gfx grd_s_t_po_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_po_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_po_1_v[157], 11, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 7, 4, // tri0
        9, 10, 6, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_po_1_v[0], 11, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 2, 4 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 8, 10, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_po_1_v[11], 20, 0),
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
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_po_1_v[31], 32, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        5, 6, 7, // tri1
        8, 7, 9, // tri2
        7, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 12, // tri0
        9, 10, 11, // tri1
        13, 14, 15, // tri2
        16, 17, 2 // tri3
    ),
    gsSPNTriangles_5b(
        0, 18, 19, // tri0
        1, 0, 19, // tri1
        20, 19, 21, // tri2
        19, 18, 21 // tri3
    ),
    gsSPNTriangles_5b(
        18, 22, 21, // tri0
        21, 22, 23, // tri1
        22, 24, 23, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 24, // tri0
        24, 27, 25, // tri1
        28, 29, 30, // tri2
        28, 31, 29 // tri3
    ),
    gsSPVertex(&grd_s_t_po_1_v[63], 28, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        3, 2, 1, // tri1
        4, 3, 5 // tri2
    ),
    gsSPNTriangles_5b(
        2, 4, 6, // tri0
        2, 3, 4, // tri1
        7, 8, 6, // tri2
        9, 10, 7 // tri3
    ),
    gsSPNTriangles_5b(
        10, 8, 7, // tri0
        11, 12, 13, // tri1
        12, 11, 14, // tri2
        10, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        10, 9, 15, // tri0
        9, 17, 15, // tri1
        17, 14, 15, // tri2
        14, 11, 15 // tri3
    ),
    gsSPNTriangles_5b(
        11, 18, 15, // tri0
        16, 15, 18, // tri1
        5, 19, 20, // tri2
        19, 21, 20 // tri3
    ),
    gsSPNTriangles_5b(
        19, 22, 21, // tri0
        23, 22, 19, // tri1
        23, 24, 22, // tri2
        24, 25, 22 // tri3
    ),
    gsSPNTriangles_5b(
        26, 24, 23, // tri0
        26, 27, 24, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_po_1_v[91], 32, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 3, 8, // tri0
        9, 10, 11, // tri1
        12, 9, 13, // tri2
        10, 5, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        18, 15, 19, // tri1
        20, 21, 22, // tri2
        21, 18, 23 // tri3
    ),
    gsSPNTriangles_5b(
        20, 22, 24, // tri0
        25, 24, 26, // tri1
        27, 28, 29, // tri2
        28, 30, 31 // tri3
    ),
    gsSPNTriangles_5b(
        30, 25, 26, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_po_1_v[123], 6, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 1, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_po_1_v[129], 28, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 3, 8, // tri0
        9, 5, 10, // tri1
        11, 9, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 13, 17, // tri0
        18, 19, 20, // tri1
        19, 16, 21, // tri2
        22, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 22, 26, // tri0
        23, 18, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
