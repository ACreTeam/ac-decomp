#include "libforest/gbi_extensions.h"

extern u8 wave3_tex_dummy[];
extern u8 wave1_tex_dummy[];
extern u8 beach2_tex_dummy2[];

static Vtx grd_s_o_8_v[] = {
#include "assets/field/bg/grd_s_o_8_v.inc"
};

extern Gfx grd_s_o_8_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_o_8_v[0], 15, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        4, 6, 5, // tri0
        7, 4, 8, // tri1
        4, 9, 8, // tri2
        7, 10, 11 // tri3
    ),
    gsSPNTriangles_5b(
        10, 12, 11, // tri0
        1, 5, 13, // tri1
        1, 0, 5, // tri2
        4, 2, 9 // tri3
    ),
    gsSPNTriangles_5b(
        4, 0, 2, // tri0
        4, 11, 6, // tri1
        4, 7, 11, // tri2
        10, 8, 14 // tri3
    ),
    gsSPNTriangles_5b(
        10, 7, 8, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_o_8_modelT[] = {
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
    gsSPVertex(&grd_s_o_8_v[15], 32, 0),
    gsSPNTrianglesInit_5b(
        36, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 6, // tri0
        5, 2, 6, // tri1
        5, 7, 2, // tri2
        4, 8, 9 // tri3
    ),
    gsSPNTriangles_5b(
        8, 10, 9, // tri0
        10, 7, 9, // tri1
        8, 11, 12, // tri2
        11, 13, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 7, 12, // tri0
        8, 14, 15, // tri1
        14, 13, 15, // tri2
        14, 16, 13 // tri3
    ),
    gsSPNTriangles_5b(
        8, 17, 18, // tri0
        17, 16, 18, // tri1
        17, 19, 16, // tri2
        8, 20, 17 // tri3
    ),
    gsSPNTriangles_5b(
        8, 21, 20, // tri0
        20, 19, 17, // tri1
        21, 22, 20, // tri2
        22, 23, 20 // tri3
    ),
    gsSPNTriangles_5b(
        23, 19, 20, // tri0
        21, 24, 22, // tri1
        24, 25, 22, // tri2
        25, 23, 22 // tri3
    ),
    gsSPNTriangles_5b(
        21, 26, 24, // tri0
        26, 25, 24, // tri1
        26, 27, 25, // tri2
        21, 28, 26 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 26, // tri0
        29, 27, 26, // tri1
        28, 30, 29, // tri2
        30, 31, 29 // tri3
    ),
    gsSPNTriangles_5b(
        31, 27, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_o_8_v[47], 11, 0),
    gsSPNTrianglesInit_5b(
        12, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        0, 5, 1, // tri0
        5, 4, 1, // tri1
        5, 6, 4, // tri2
        0, 7, 5 // tri3
    ),
    gsSPNTriangles_5b(
        0, 8, 7, // tri0
        7, 6, 5, // tri1
        8, 9, 7, // tri2
        9, 10, 7 // tri3
    ),
    gsSPNTriangles_5b(
        10, 6, 7, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
