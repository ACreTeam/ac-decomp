#include "libforest/gbi_extensions.h"

extern u8 wave3_tex_dummy[];
extern u8 wave1_tex_dummy[];
extern u8 beach2_tex_dummy2[];

static Vtx grd_s_o_ta_3_v[] = {
#include "assets/field/bg/grd_s_o_ta_3_v.inc"
};

extern Gfx grd_s_o_ta_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_o_ta_3_v[0], 15, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        0, 2, 9, // tri0
        1, 6, 2, // tri1
        3, 10, 11, // tri2
        1, 0, 7 // tri3
    ),
    gsSPNTriangles_5b(
        0, 12, 7, // tri0
        6, 13, 2, // tri1
        6, 5, 13, // tri2
        3, 14, 10 // tri3
    ),
    gsSPNTriangles_5b(
        14, 6, 10, // tri0
        6, 14, 5, // tri1
        6, 1, 7, // tri2
        6, 8, 10 // tri3
    ),
    gsSPNTriangles_5b(
        14, 3, 5, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_o_ta_3_modelT[] = {
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
    gsSPVertex(&grd_s_o_ta_3_v[15], 32, 0),
    gsSPNTrianglesInit_5b(
        37, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 3, // tri0
        0, 6, 1, // tri1
        6, 4, 1, // tri2
        6, 7, 4 // tri3
    ),
    gsSPNTriangles_5b(
        8, 3, 5, // tri0
        8, 9, 3, // tri1
        9, 2, 3, // tri2
        10, 11, 8 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 8, // tri0
        11, 2, 12, // tri1
        11, 13, 2, // tri2
        14, 15, 10 // tri3
    ),
    gsSPNTriangles_5b(
        14, 16, 15, // tri0
        16, 13, 15, // tri1
        17, 18, 14, // tri2
        18, 19, 14 // tri3
    ),
    gsSPNTriangles_5b(
        18, 13, 19, // tri0
        20, 21, 17, // tri1
        21, 18, 17, // tri2
        21, 13, 18 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 13, // tri0
        23, 21, 20, // tri1
        24, 22, 21, // tri2
        23, 24, 21 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 23, // tri0
        26, 22, 24, // tri1
        26, 24, 23, // tri2
        27, 26, 25 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 26, // tri0
        28, 29, 26, // tri1
        29, 22, 26, // tri2
        30, 31, 27 // tri3
    ),
    gsSPNTriangles_5b(
        31, 28, 27, // tri0
        31, 29, 28, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
