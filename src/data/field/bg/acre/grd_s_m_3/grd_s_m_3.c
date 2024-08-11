#include "libforest/gbi_extensions.h"

extern u8 wave3_tex_dummy[];
extern u8 wave2_tex_dummy[];
extern u8 wave1_tex_dummy[];
extern u8 sand_tex_dummy[];
extern u8 beach_pal_dummy2[];
extern u8 beach2_tex_dummy2[];
extern u8 beach1_tex_dummy2[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_m_3_v[] = {
#include "assets/field/bg/grd_s_m_3_v.inc"
};

extern Gfx grd_s_m_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_3_v[153], 27, 0),
    gsSPNTrianglesInit_5b(
        27, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        0, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 2, // tri0
        5, 6, 2, // tri1
        7, 8, 9, // tri2
        7, 4, 8 // tri3
    ),
    gsSPNTriangles_5b(
        8, 10, 9, // tri0
        10, 11, 9, // tri1
        11, 12, 9, // tri2
        11, 13, 12 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        14, 13, 15, // tri1
        13, 11, 15, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        17, 20, 18, // tri0
        18, 21, 19, // tri1
        20, 22, 18, // tri2
        20, 23, 22 // tri3
    ),
    gsSPNTriangles_5b(
        20, 0, 23, // tri0
        0, 24, 23, // tri1
        0, 2, 24, // tri2
        2, 25, 24 // tri3
    ),
    gsSPNTriangles_5b(
        2, 6, 25, // tri0
        6, 26, 25, // tri1
        0, 20, 4, // tri2
        20, 17, 4 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_3_v[0], 25, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        3, 0, 2, // tri1
        3, 2, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 5, 7, // tri1
        8, 7, 9, // tri2
        8, 9, 10 // tri3
    ),
    gsSPNTriangles_5b(
        11, 8, 10, // tri0
        11, 10, 12, // tri1
        11, 12, 13, // tri2
        14, 11, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 13, 15, // tri0
        16, 14, 15, // tri1
        16, 15, 17, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 18, 20, // tri0
        22, 21, 20, // tri1
        19, 18, 23, // tri2
        17, 19, 23 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 23, // tri0
        3, 4, 24, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_3_v[25], 17, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        3, 2, 1, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        5, 6, 4, // tri1
        7, 8, 9, // tri2
        10, 7, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 0, // tri0
        12, 1, 0, // tri1
        13, 12, 14, // tri2
        12, 11, 14 // tri3
    ),
    gsSPNTriangles_5b(
        5, 15, 6, // tri0
        15, 16, 6, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_3_v[42], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 5, 9, // tri1
        10, 11, 12, // tri2
        6, 10, 13 // tri3
    ),
    gsSPNTriangles_5b(
        11, 14, 15, // tri0
        14, 16, 17, // tri1
        18, 19, 20, // tri2
        21, 18, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        24, 21, 26, // tri1
        27, 28, 29, // tri2
        28, 23, 30 // tri3
    ),
    gsSPVertex(&grd_s_m_3_v[73], 14, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 3 // tri2
    ),
    gsSPNTriangles_5b(
        8, 9, 6, // tri0
        8, 10, 9, // tri1
        8, 11, 10, // tri2
        11, 12, 13 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_m_3_v[87], 32, 0),
    gsSPNTrianglesInit_5b(
        27, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 2, // tri0
        6, 7, 8, // tri1
        7, 9, 8, // tri2
        8, 9, 10 // tri3
    ),
    gsSPNTriangles_5b(
        5, 11, 2, // tri0
        2, 12, 13, // tri1
        2, 14, 12, // tri2
        12, 15, 13 // tri3
    ),
    gsSPNTriangles_5b(
        1, 0, 16, // tri0
        0, 10, 16, // tri1
        6, 17, 7, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        19, 22, 21, // tri1
        20, 23, 18, // tri2
        24, 6, 25 // tri3
    ),
    gsSPNTriangles_5b(
        6, 8, 25, // tri0
        26, 27, 17, // tri1
        27, 7, 17, // tri2
        9, 7, 28 // tri3
    ),
    gsSPNTriangles_5b(
        15, 29, 13, // tri0
        29, 25, 13, // tri1
        29, 24, 25, // tri2
        11, 14, 2 // tri3
    ),
    gsSPVertex(&grd_s_m_3_v[117], 19, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 9, 10, // tri1
        9, 11, 10, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        3, 4, 14, // tri0
        15, 16, 17, // tri1
        16, 18, 17, // tri2
        18, 0, 17 // tri3
    ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_3_v[136], 17, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        7, 8, 6, // tri1
        7, 9, 8, // tri2
        9, 10, 8 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 10, // tri0
        11, 12, 10, // tri1
        11, 13, 12, // tri2
        13, 14, 12 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 12, // tri0
        4, 16, 5, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_m_3_modelT[] = {
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
    gsSPVertex(&grd_s_m_3_v[180], 24, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        9, 6, 8, // tri0
        10, 9, 8, // tri1
        10, 8, 11, // tri2
        1, 10, 11 // tri3
    ),
    gsSPNTriangles_5b(
        1, 11, 12, // tri0
        13, 1, 12, // tri1
        13, 12, 14, // tri2
        5, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        3, 5, 14, // tri0
        15, 16, 17, // tri1
        15, 17, 18, // tri2
        19, 17, 16 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 17, // tri0
        4, 21, 5, // tri1
        21, 2, 5, // tri2
        2, 13, 5 // tri3
    ),
    gsSPNTriangles_5b(
        2, 1, 13, // tri0
        0, 10, 1, // tri1
        0, 22, 10, // tri2
        22, 9, 10 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 9, // tri0
        23, 6, 9, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_m_3_v[204], 26, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 2, // tri0
        3, 6, 4, // tri1
        3, 7, 6, // tri2
        3, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 5, // tri0
        10, 2, 5, // tri1
        11, 12, 9, // tri2
        12, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        13, 12, 11, // tri0
        14, 12, 13, // tri1
        14, 15, 12, // tri2
        8, 16, 7 // tri3
    ),
    gsSPNTriangles_5b(
        8, 17, 16, // tri0
        17, 18, 16, // tri1
        17, 19, 18, // tri2
        17, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 22, // tri0
        20, 23, 21, // tri1
        20, 24, 23, // tri2
        20, 25, 24 // tri3
    ),
    gsSPEndDisplayList(),
};
