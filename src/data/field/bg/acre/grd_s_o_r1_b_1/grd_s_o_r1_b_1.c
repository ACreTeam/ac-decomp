#include "libforest/gbi_extensions.h"

extern u8 wave3_tex_dummy[];
extern u8 wave1_tex_dummy[];
extern u8 beach2_tex_dummy2[];

static Vtx grd_s_o_r1_b_1_v[] = {
#include "assets/field/bg/grd_s_o_r1_b_1_v.inc"
};

extern Gfx grd_s_o_r1_b_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_o_r1_b_1_v[0], 15, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        2, 3, 0, // tri1
        3, 4, 0 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 0, // tri0
        2, 6, 3, // tri1
        6, 4, 3, // tri2
        6, 7, 4 // tri3
    ),
    gsSPNTriangles_5b(
        2, 8, 6, // tri0
        9, 10, 11, // tri1
        11, 8, 2, // tri2
        11, 2, 12 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 12, // tri0
        2, 1, 13, // tri1
        12, 2, 13, // tri2
        9, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 9, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_o_r1_b_1_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL1, 0, TEXEL0, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, 0, SHADE, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 60, 120, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_o_r1_b_1_v[15], 15, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        2, 3, 0, // tri1
        3, 4, 0 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 0, // tri0
        2, 6, 3, // tri1
        6, 4, 3, // tri2
        6, 7, 4 // tri3
    ),
    gsSPNTriangles_5b(
        2, 8, 6, // tri0
        4, 7, 9, // tri1
        9, 10, 11, // tri2
        9, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        4, 9, 12, // tri0
        11, 13, 14, // tri1
        12, 11, 14, // tri2
        4, 12, 14 // tri3
    ),
    gsSPNTriangles_5b(
        14, 5, 4, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
