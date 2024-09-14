#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];

static Vtx grd_s_e5_1_v[] = {
#include "assets/field/bg/grd_s_e5_1_v.inc"
};

extern Gfx grd_s_e5_1_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx grd_s_e5_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_e5_1_v[0], 8, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 0, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 4, 3, // tri0
        5, 3, 6, // tri1
        5, 6, 7, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_e5_1_v[8], 16, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 0, // tri1
        1, 5, 2 // tri2
    ),
    gsSPNTriangles_5b(
        0, 4, 1, // tri0
        3, 6, 4, // tri1
        2, 7, 0, // tri2
        0, 8, 3 // tri3
    ),
    gsSPNTriangles_5b(
        0, 7, 8, // tri0
        7, 9, 10, // tri1
        1, 11, 12, // tri2
        1, 12, 5 // tri3
    ),
    gsSPNTriangles_5b(
        1, 13, 11, // tri0
        13, 4, 14, // tri1
        14, 4, 6, // tri2
        14, 6, 15 // tri3
    ),
    gsSPNTriangles_5b(
        13, 1, 4, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
