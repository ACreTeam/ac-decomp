#include "libforest/gbi_extensions.h"

extern u8 wave3_tex_dummy[];
extern u8 wave2_tex_dummy[];
extern u8 wave1_tex_dummy[];
extern u8 sand_tex_dummy[];
extern u8 beach_pal_dummy2[];
extern u8 beach2_tex_dummy2[];
extern u8 beach1_tex_dummy2[];
extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_m_2_v[] = {
#include "assets/field/bg/grd_s_m_2_v.inc"
};

extern Gfx grd_s_m_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_2_v[163], 27, 0),
    gsSPNTrianglesInit_5b(
        28, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        0, 3, 4 // tri2
    ),
    gsSPNTriangles_5b(
        0, 4, 5, // tri0
        6, 0, 5, // tri1
        6, 5, 7, // tri2
        6, 7, 8 // tri3
    ),
    gsSPNTriangles_5b(
        9, 6, 8, // tri0
        9, 10, 11, // tri1
        9, 8, 10, // tri2
        9, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 9, 12, // tri0
        14, 13, 12, // tri1
        2, 15, 16, // tri2
        3, 2, 16 // tri3
    ),
    gsSPNTriangles_5b(
        3, 16, 17, // tri0
        4, 3, 17, // tri1
        4, 17, 18, // tri2
        11, 10, 19 // tri3
    ),
    gsSPNTriangles_5b(
        11, 19, 20, // tri0
        11, 20, 21, // tri1
        12, 11, 21, // tri2
        12, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        14, 12, 22, // tri0
        23, 14, 22, // tri1
        4, 24, 25, // tri2
        4, 18, 24 // tri3
    ),
    gsSPNTriangles_5b(
        18, 26, 24, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_2_v[148], 15, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 10, 11, // tri1
        10, 12, 13, // tri2
        12, 7, 14 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_2_v[0], 19, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 6, // tri0
        3, 5, 4, // tri1
        7, 8, 6, // tri2
        9, 10, 8 // tri3
    ),
    gsSPNTriangles_5b(
        6, 5, 7, // tri0
        8, 7, 9, // tri1
        11, 12, 10, // tri2
        10, 9, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 12, // tri0
        15, 16, 14, // tri1
        14, 13, 15, // tri2
        12, 11, 13 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 16, // tri0
        17, 18, 16, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_2_v[19], 19, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        0, 3, 4, // tri1
        5, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        8, 9, 7, // tri1
        7, 5, 8, // tri2
        4, 3, 5 // tri3
    ),
    gsSPNTriangles_5b(
        2, 3, 0, // tri0
        10, 11, 12, // tri1
        12, 13, 14, // tri2
        13, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        16, 14, 13, // tri0
        15, 17, 16, // tri1
        12, 18, 10, // tri2
        14, 18, 12 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_2_v[38], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        0, 6, 1, // tri0
        9, 10, 11, // tri1
        10, 0, 2, // tri2
        12, 3, 5 // tri3
    ),
    gsSPNTriangles_5b(
        7, 12, 13, // tri0
        3, 14, 4, // tri1
        14, 15, 16, // tri2
        17, 9, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 21, // tri0
        22, 19, 23, // tri1
        24, 25, 26, // tri2
        20, 24, 27 // tri3
    ),
    gsSPNTriangles_5b(
        25, 28, 29, // tri0
        28, 30, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_m_2_v[70], 32, 0),
    gsSPNTrianglesInit_5b(
        31, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        5, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        4, 6, 7, // tri0
        8, 4, 7, // tri1
        9, 10, 8, // tri2
        10, 9, 11 // tri3
    ),
    gsSPNTriangles_5b(
        2, 1, 10, // tri0
        10, 12, 2, // tri1
        10, 11, 12, // tri2
        10, 1, 4 // tri3
    ),
    gsSPNTriangles_5b(
        4, 8, 10, // tri0
        9, 13, 11, // tri1
        14, 15, 0, // tri2
        14, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 14, 17, // tri0
        15, 16, 18, // tri1
        18, 19, 15, // tri2
        18, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 19, // tri0
        20, 22, 21, // tri1
        22, 23, 21, // tri2
        22, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 22, // tri0
        26, 24, 22, // tri1
        25, 27, 26, // tri2
        28, 27, 25 // tri3
    ),
    gsSPNTriangles_5b(
        17, 29, 28, // tri0
        29, 30, 28, // tri1
        30, 31, 28, // tri2
        31, 27, 28 // tri3
    ),
    gsSPVertex(&grd_s_m_2_v[102], 12, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        3, 6, 5, // tri1
        3, 7, 6, // tri2
        6, 7, 8 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        9, 7, 10, // tri1
        10, 7, 11, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_2_v[114], 15, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        1, 7, 8, // tri0
        7, 9, 10, // tri1
        9, 11, 12, // tri2
        11, 13, 14 // tri3
    ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_2_v[129], 19, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 0, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 3, 5, // tri0
        6, 4, 5, // tri1
        6, 5, 7, // tri2
        8, 6, 7 // tri3
    ),
    gsSPNTriangles_5b(
        8, 7, 9, // tri0
        10, 11, 12, // tri1
        10, 12, 13, // tri2
        14, 10, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 13, 15, // tri0
        16, 14, 15, // tri1
        17, 16, 15, // tri2
        18, 17, 15 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_m_2_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL1, 0, TEXEL0, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, 0, SHADE, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 60, 120, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, wave2_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPDisplayList(0x0B000000),
    gsSPVertex(&grd_s_m_2_v[190], 27, 0),
    gsSPNTrianglesInit_5b(
        29, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 1, 4 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 2, // tri0
        5, 6, 2, // tri1
        3, 4, 7, // tri2
        5, 3, 7 // tri3
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        9, 5, 8, // tri1
        5, 9, 6, // tri2
        9, 10, 6 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 10, // tri0
        11, 9, 8, // tri1
        12, 11, 8, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 13, 15, // tri0
        13, 16, 17, // tri1
        13, 17, 18, // tri2
        16, 19, 17 // tri3
    ),
    gsSPNTriangles_5b(
        16, 20, 19, // tri0
        20, 16, 15, // tri1
        20, 15, 21, // tri2
        22, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        20, 22, 23, // tri0
        20, 23, 19, // tri1
        22, 24, 23, // tri2
        22, 25, 24 // tri3
    ),
    gsSPNTriangles_5b(
        26, 25, 22, // tri0
        26, 22, 21, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_m_2_v[217], 26, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
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
        5, 9, 7, // tri0
        7, 10, 8, // tri1
        7, 11, 10, // tri2
        11, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        11, 14, 13, // tri1
        14, 15, 13, // tri2
        14, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 15, // tri0
        16, 18, 19, // tri1
        16, 20, 18, // tri2
        16, 21, 20 // tri3
    ),
    gsSPNTriangles_5b(
        16, 22, 21, // tri0
        20, 23, 18, // tri1
        20, 24, 23, // tri2
        24, 25, 23 // tri3
    ),
    gsSPEndDisplayList(),
};
