#include "libforest/gbi_extensions.h"

extern u8 wave3_tex_dummy[];
extern u8 wave2_tex_dummy[];
extern u8 wave1_tex_dummy[];
extern u8 sand_tex_dummy[];
extern u8 beach_pal_dummy2[];
extern u8 beach2_tex_dummy2[];
extern u8 beach1_tex_dummy2[];
extern u8 earth_pal_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_m_1_v[] = {
#include "assets/field/bg/grd_s_m_1_v.inc"
};

extern Gfx grd_s_m_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_1_v[134], 27, 0),
    gsSPNTrianglesInit_5b(
        33, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 2, // tri0
        5, 6, 2, // tri1
        6, 7, 2, // tri2
        6, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 7, // tri0
        9, 10, 7, // tri1
        9, 11, 10, // tri2
        11, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 10, // tri0
        12, 14, 13, // tri1
        15, 16, 14, // tri2
        15, 14, 12 // tri3
    ),
    gsSPNTriangles_5b(
        17, 15, 12, // tri0
        18, 17, 12, // tri1
        18, 12, 11, // tri2
        18, 11, 9 // tri3
    ),
    gsSPNTriangles_5b(
        19, 18, 9, // tri0
        19, 9, 8, // tri1
        20, 19, 8, // tri2
        21, 20, 8 // tri3
    ),
    gsSPNTriangles_5b(
        21, 8, 6, // tri0
        22, 21, 6, // tri1
        22, 6, 5, // tri2
        23, 4, 1 // tri3
    ),
    gsSPNTriangles_5b(
        23, 1, 3, // tri0
        24, 22, 5, // tri1
        24, 5, 4, // tri2
        25, 24, 4 // tri3
    ),
    gsSPNTriangles_5b(
        23, 25, 4, // tri0
        26, 23, 3, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_1_v[0], 25, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        3, 4, 2, // tri1
        4, 0, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 3, 5, // tri0
        5, 6, 4, // tri1
        0, 7, 1, // tri2
        8, 9, 1 // tri3
    ),
    gsSPNTriangles_5b(
        1, 7, 8, // tri0
        10, 11, 9, // tri1
        9, 8, 10, // tri2
        12, 13, 11 // tri3
    ),
    gsSPNTriangles_5b(
        11, 10, 12, // tri0
        12, 14, 13, // tri1
        15, 16, 13, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 16, // tri0
        16, 15, 17, // tri1
        17, 19, 18, // tri2
        17, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 19, // tri0
        20, 22, 21, // tri1
        22, 23, 21, // tri2
        22, 24, 23 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_m_1_v[25], 32, 0),
    gsSPNTrianglesInit_5b(
        30, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 2, // tri0
        5, 6, 2, // tri1
        5, 7, 6, // tri2
        3, 8, 9 // tri3
    ),
    gsSPNTriangles_5b(
        8, 10, 9, // tri0
        11, 12, 13, // tri1
        11, 14, 12, // tri2
        12, 15, 13 // tri3
    ),
    gsSPNTriangles_5b(
        11, 16, 14, // tri0
        11, 17, 16, // tri1
        17, 18, 16, // tri2
        17, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 18, // tri0
        20, 21, 18, // tri1
        19, 22, 20, // tri2
        22, 23, 20 // tri3
    ),
    gsSPNTriangles_5b(
        22, 24, 23, // tri0
        24, 25, 23, // tri1
        24, 26, 25, // tri2
        26, 27, 25 // tri3
    ),
    gsSPNTriangles_5b(
        6, 28, 29, // tri0
        6, 21, 28, // tri1
        6, 7, 21, // tri2
        7, 18, 21 // tri3
    ),
    gsSPNTriangles_5b(
        25, 30, 23, // tri0
        25, 31, 30, // tri1
        31, 29, 30, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_1_v[57], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        8, 7, 4, // tri0
        9, 10, 11, // tri1
        12, 13, 10, // tri2
        14, 11, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 15, 6, // tri0
        4, 3, 8, // tri1
        6, 5, 16, // tri2
        13, 12, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 17, 19, // tri0
        19, 20, 18, // tri1
        21, 22, 20, // tri2
        23, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 24, // tri0
        28, 29, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_m_1_v[87], 22, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        5, 2, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 6, 8, // tri0
        9, 10, 11, // tri1
        12, 13, 10, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 11, 15, // tri0
        18, 16, 19, // tri1
        20, 19, 21, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_1_v[109], 25, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 2, // tri0
        4, 6, 5, // tri1
        4, 7, 6, // tri2
        7, 8, 6 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 6, // tri0
        8, 10, 9, // tri1
        10, 11, 9, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 12, // tri0
        13, 14, 12, // tri1
        13, 15, 14, // tri2
        15, 16, 14 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 14, // tri0
        16, 18, 17, // tri1
        16, 19, 18, // tri2
        19, 20, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        19, 22, 21, // tri1
        22, 23, 21, // tri2
        23, 24, 21 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_m_1_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL1, 0, TEXEL0, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, 0, SHADE, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 60, 120, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, wave2_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPDisplayList(0x0B000000),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_1_v[161], 32, 0),
    gsSPNTrianglesInit_5b(
        38, // tri count
        0, 1, 2, // tri0
        3, 0, 2, // tri1
        4, 3, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 2, 5, // tri0
        4, 5, 6, // tri1
        7, 4, 6, // tri2
        7, 6, 8 // tri3
    ),
    gsSPNTriangles_5b(
        9, 7, 8, // tri0
        9, 8, 10, // tri1
        11, 9, 10, // tri2
        11, 10, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        14, 11, 13, // tri1
        14, 13, 15, // tri2
        16, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        17, 16, 15, // tri0
        17, 15, 18, // tri1
        17, 18, 19, // tri2
        20, 17, 19 // tri3
    ),
    gsSPNTriangles_5b(
        21, 20, 19, // tri0
        1, 22, 23, // tri1
        2, 1, 23, // tri2
        5, 2, 23 // tri3
    ),
    gsSPNTriangles_5b(
        5, 23, 24, // tri0
        5, 24, 25, // tri1
        6, 5, 25, // tri2
        6, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        6, 26, 27, // tri0
        8, 6, 27, // tri1
        10, 8, 27, // tri2
        10, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        12, 10, 28, // tri0
        12, 28, 29, // tri1
        12, 29, 30, // tri2
        13, 12, 30 // tri3
    ),
    gsSPNTriangles_5b(
        13, 30, 31, // tri0
        15, 13, 31, // tri1
        18, 15, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_m_1_v[193], 7, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 0, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 4, // tri0
        5, 4, 3, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_m_1_v[200], 24, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 3, 0 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 4, // tri0
        6, 3, 4, // tri1
        7, 6, 5, // tri2
        7, 8, 6 // tri3
    ),
    gsSPNTriangles_5b(
        9, 8, 7, // tri0
        10, 11, 9, // tri1
        11, 8, 9, // tri2
        12, 11, 10 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 11, // tri0
        14, 13, 12, // tri1
        15, 16, 14, // tri2
        16, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        17, 16, 15, // tri0
        17, 18, 16, // tri1
        19, 18, 17, // tri2
        19, 20, 18 // tri3
    ),
    gsSPNTriangles_5b(
        21, 20, 19, // tri0
        22, 23, 21, // tri1
        23, 20, 21, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
