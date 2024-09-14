#include "libforest/gbi_extensions.h"

extern u8 wave3_tex_dummy[];
extern u8 wave1_tex_dummy[];
extern u8 beach2_tex_dummy2[];

static Vtx grd_s_o_wf_3_v[] = {
#include "assets/field/bg/grd_s_o_wf_3_v.inc"
};

extern Gfx grd_s_o_wf_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_o_wf_3_v[0], 15, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 1, 5 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 6, // tri0
        4, 7, 8, // tri1
        4, 8, 9, // tri2
        10, 7, 11 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 12, // tri0
        0, 13, 5, // tri1
        1, 0, 5, // tri2
        4, 9, 2 // tri3
    ),
    gsSPNTriangles_5b(
        1, 4, 2, // tri0
        4, 6, 11, // tri1
        7, 4, 11, // tri2
        10, 14, 8 // tri3
    ),
    gsSPNTriangles_5b(
        7, 10, 8, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_o_wf_3_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL1, 0, TEXEL0, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, 0, SHADE, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 60, 120, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_o_wf_3_v[15], 32, 0),
    gsSPNTrianglesInit_5b(
        30, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 0, 2 // tri2
    ),
    gsSPNTriangles_5b(
        2, 3, 5, // tri0
        3, 6, 5, // tri1
        4, 2, 5, // tri2
        5, 7, 8 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        10, 5, 8, // tri1
        10, 4, 5, // tri2
        8, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 11, // tri0
        10, 8, 12, // tri1
        13, 14, 15, // tri2
        13, 16, 14 // tri3
    ),
    gsSPNTriangles_5b(
        17, 13, 15, // tri0
        15, 14, 18, // tri1
        14, 19, 18, // tri2
        17, 15, 18 // tri3
    ),
    gsSPNTriangles_5b(
        18, 20, 21, // tri0
        18, 22, 20, // tri1
        23, 18, 21, // tri2
        23, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        21, 24, 25, // tri0
        21, 26, 24, // tri1
        23, 21, 25, // tri2
        25, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        25, 29, 27, // tri0
        30, 23, 28, // tri1
        23, 25, 28, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_o_wf_3_v[46], 16, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        9, 5, 7, // tri2
        7, 10, 11 // tri3
    ),
    gsSPNTriangles_5b(
        7, 12, 10, // tri0
        13, 9, 11, // tri1
        9, 7, 11, // tri2
        11, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        11, 10, 14, // tri0
        13, 11, 15, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
