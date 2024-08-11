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

static Vtx grd_s_t_po_2_v[] = {
#include "assets/field/bg/grd_s_t_po_2_v.inc"
};

extern Gfx grd_s_t_po_2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_po_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_po_2_v[144], 19, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        5, 8, 6, // tri1
        8, 9, 6, // tri2
        10, 9, 11 // tri3
    ),
    gsSPNTriangles_5b(
        3, 10, 12, // tri0
        7, 13, 14, // tri1
        13, 15, 16, // tri2
        15, 17, 18 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_po_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        28, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 0, 2, // tri1
        3, 9, 2, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 11, // tri0
        13, 14, 11, // tri1
        15, 16, 17, // tri2
        16, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        6, 9, 4, // tri0
        6, 2, 9, // tri1
        19, 20, 21, // tri2
        20, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        16, 15, 23, // tri0
        15, 24, 23, // tri1
        25, 14, 13, // tri2
        26, 19, 27 // tri3
    ),
    gsSPNTriangles_5b(
        19, 28, 27, // tri0
        10, 29, 13, // tri1
        29, 5, 13, // tri2
        29, 7, 5 // tri3
    ),
    gsSPNTriangles_5b(
        3, 1, 30, // tri0
        1, 31, 30, // tri1
        31, 28, 30, // tri2
        18, 25, 17 // tri3
    ),
    gsSPNTriangles_5b(
        21, 28, 19, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_po_2_v[32], 24, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 5, // tri0
        6, 8, 7, // tri1
        8, 9, 7, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 9, // tri0
        10, 12, 11, // tri1
        13, 14, 15, // tri2
        16, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        0, 19, 20, // tri0
        19, 21, 20, // tri1
        0, 2, 19, // tri2
        2, 22, 19 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 19, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_po_2_v[56], 20, 0),
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
    gsSPVertex(&grd_s_t_po_2_v[76], 11, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 8, 9, // tri0
        8, 6, 10, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_po_2_v[87], 19, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        0, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        5, 8, 6, // tri1
        5, 9, 8, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 10, 14, // tri0
        9, 13, 15, // tri1
        4, 16, 17, // tri2
        16, 7, 18 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_po_2_v[106], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        1, 11, 2, // tri1
        8, 5, 9, // tri2
        1, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 14, // tri0
        13, 15, 14, // tri1
        16, 10, 17, // tri2
        13, 18, 15 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 20, // tri0
        19, 21, 22, // tri1
        21, 16, 17, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 23, 27, // tri0
        28, 29, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_t_po_2_v[137], 7, 0),
    gsSPNTrianglesInit_5b(
        3, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 0, 6 // tri2
    ),
    gsSPEndDisplayList(),
};
