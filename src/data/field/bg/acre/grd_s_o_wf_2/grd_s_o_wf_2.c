#include "libforest/gbi_extensions.h"

extern u8 wave3_tex_dummy[];
extern u8 wave1_tex_dummy[];
extern u8 beach2_tex_dummy2[];

static Vtx grd_s_o_wf_2_v[] = {
#include "assets/field/bg/grd_s_o_wf_2_v.inc"
};

extern Gfx grd_s_o_wf_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_o_wf_2_v[0], 15, 0),
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

extern Gfx grd_s_o_wf_2_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL1, 0, TEXEL0, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, 0, SHADE, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 60, 120, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_o_wf_2_v[15], 32, 0),
    gsSPNTrianglesInit_5b(
        31, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 2, 1, // tri0
        5, 6, 2, // tri1
        4, 7, 1, // tri2
        7, 5, 1 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 5, // tri0
        9, 10, 5, // tri1
        7, 8, 5, // tri2
        11, 12, 8 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        7, 11, 8, // tri1
        14, 15, 11, // tri2
        15, 16, 11 // tri3
    ),
    gsSPNTriangles_5b(
        7, 14, 11, // tri0
        7, 17, 14, // tri1
        18, 19, 14, // tri2
        19, 20, 14 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 14, // tri0
        21, 22, 18, // tri1
        22, 23, 18, // tri2
        17, 21, 18 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 21, // tri0
        24, 26, 25, // tri1
        17, 24, 21, // tri2
        27, 26, 24 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 26, // tri0
        17, 27, 24, // tri1
        29, 30, 27, // tri2
        29, 31, 30 // tri3
    ),
    gsSPVertex(&grd_s_o_wf_2_v[47], 19, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 3, // tri0
        1, 4, 3, // tri1
        7, 8, 4, // tri2
        7, 9, 8 // tri3
    ),
    gsSPNTriangles_5b(
        1, 7, 4, // tri0
        10, 11, 7, // tri1
        10, 12, 11, // tri2
        1, 10, 7 // tri3
    ),
    gsSPNTriangles_5b(
        13, 12, 10, // tri0
        13, 14, 12, // tri1
        1, 13, 10, // tri2
        1, 15, 13 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 13, // tri0
        17, 18, 13, // tri1
        15, 16, 13, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
