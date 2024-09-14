#include "libforest/gbi_extensions.h"

extern u8 wave3_tex_dummy[];
extern u8 wave1_tex_dummy[];
extern u8 beach2_tex_dummy2[];

static Vtx grd_s_o_2_v[] = {
#include "assets/field/bg/grd_s_o_2_v.inc"
};

extern Gfx grd_s_o_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_o_2_v[0], 15, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        4, 8, 9, // tri1
        8, 10, 9, // tri2
        0, 8, 11 // tri3
    ),
    gsSPNTriangles_5b(
        8, 12, 11, // tri0
        5, 9, 13, // tri1
        5, 4, 9, // tri2
        8, 6, 12 // tri3
    ),
    gsSPNTriangles_5b(
        8, 4, 6, // tri0
        8, 2, 10, // tri1
        8, 0, 2, // tri2
        1, 11, 14 // tri3
    ),
    gsSPNTriangles_5b(
        1, 0, 11, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_o_2_modelT[] = {
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
    gsSPVertex(&grd_s_o_2_v[15], 32, 0),
    gsSPNTrianglesInit_5b(
        36, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        6, 7, 4, // tri1
        6, 8, 7, // tri2
        8, 2, 7 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 6, // tri0
        9, 11, 10, // tri1
        11, 2, 10, // tri2
        12, 13, 9 // tri3
    ),
    gsSPNTriangles_5b(
        13, 11, 9, // tri0
        13, 2, 11, // tri1
        14, 15, 12, // tri2
        15, 13, 12 // tri3
    ),
    gsSPNTriangles_5b(
        15, 2, 13, // tri0
        16, 17, 14, // tri1
        17, 15, 14, // tri2
        17, 2, 15 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 2, // tri0
        19, 20, 16, // tri1
        20, 17, 16, // tri2
        20, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        21, 20, 19, // tri0
        21, 22, 20, // tri1
        22, 23, 20, // tri2
        23, 18, 20 // tri3
    ),
    gsSPNTriangles_5b(
        24, 22, 21, // tri0
        24, 25, 22, // tri1
        25, 23, 22, // tri2
        26, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        27, 25, 28, // tri0
        27, 23, 25, // tri1
        29, 30, 26, // tri2
        30, 31, 26 // tri3
    ),
    gsSPNTriangles_5b(
        30, 23, 31, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_o_2_v[47], 7, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        6, 1, 4, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
