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
extern u8 stone_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_m_ta_2_v[] = {
#include "assets/field/bg/grd_s_m_ta_2_v.inc"
};

extern Gfx grd_s_m_ta_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_ta_2_v[166], 23, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        5, 6, 4, // tri1
        5, 7, 6, // tri2
        7, 8, 6 // tri3
    ),
    gsSPNTriangles_5b(
        3, 9, 1, // tri0
        9, 5, 1, // tri1
        9, 10, 5, // tri2
        10, 7, 5 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 7, // tri0
        11, 12, 7, // tri1
        11, 13, 12, // tri2
        11, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 13, // tri0
        14, 16, 15, // tri1
        14, 17, 16, // tri2
        17, 18, 16 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 16, // tri0
        19, 20, 16, // tri1
        20, 21, 16, // tri2
        21, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 15, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_ta_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        29, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 2, 4 // tri2
    ),
    gsSPNTriangles_5b(
        2, 5, 4, // tri0
        6, 7, 8, // tri1
        9, 10, 8, // tri2
        7, 9, 8 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 10, // tri0
        11, 12, 10, // tri1
        13, 12, 11, // tri2
        13, 11, 14 // tri3
    ),
    gsSPNTriangles_5b(
        11, 15, 14, // tri0
        6, 16, 17, // tri1
        16, 18, 17, // tri2
        19, 20, 17 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 19, // tri0
        19, 21, 20, // tri1
        22, 21, 5, // tri2
        21, 22, 20 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 15, // tri0
        14, 23, 24, // tri1
        15, 23, 14, // tri2
        25, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 12, // tri0
        27, 26, 25, // tri1
        25, 28, 27, // tri2
        27, 29, 26 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 26, // tri0
        29, 31, 30, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_m_ta_2_v[32], 19, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 2, // tri0
        5, 6, 7, // tri1
        2, 5, 7, // tri2
        8, 9, 1 // tri3
    ),
    gsSPNTriangles_5b(
        8, 10, 9, // tri0
        10, 11, 9, // tri1
        12, 13, 14, // tri2
        13, 15, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 14, // tri0
        16, 17, 14, // tri1
        17, 18, 14, // tri2
        10, 18, 11 // tri3
    ),
    gsSPNTriangles_5b(
        10, 14, 18, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_ta_2_v[51], 18, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 4, 0, // tri1
        5, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 6, // tri0
        6, 5, 7, // tri1
        4, 3, 5, // tri2
        0, 2, 3 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        10, 12, 11, // tri1
        12, 13, 14, // tri2
        14, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 14, // tri0
        13, 16, 15, // tri1
        16, 17, 15, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_ta_2_v[69], 20, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        0, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 3, // tri0
        5, 6, 3, // tri1
        5, 7, 6, // tri2
        5, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 8, // tri0
        11, 12, 10, // tri1
        11, 13, 12, // tri2
        14, 15, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 16, 15, // tri0
        16, 17, 15, // tri1
        16, 18, 17, // tri2
        18, 19, 17 // tri3
    ),
    gsSPNTriangles_5b(
        8, 5, 9, // tri0
        10, 9, 11, // tri1
        13, 11, 14, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_ta_2_v[89], 17, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        5, 6, 3 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        6, 7, 8, // tri1
        7, 9, 10, // tri2
        9, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 14, // tri0
        14, 12, 11, // tri1
        13, 15, 16, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_ta_2_v[106], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        5, 6, 3 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        6, 7, 8, // tri1
        7, 9, 10, // tri2
        9, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 14, // tri0
        14, 12, 11, // tri1
        13, 15, 16, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        18, 20, 21, // tri0
        20, 22, 23, // tri1
        22, 24, 25, // tri2
        24, 26, 27 // tri3
    ),
    gsSPNTriangles_5b(
        26, 28, 29, // tri0
        28, 30, 31, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_m_ta_2_v[138], 11, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 10, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_ta_2_v[149], 17, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        7, 8, 5, // tri1
        9, 10, 11, // tri2
        10, 8, 11 // tri3
    ),
    gsSPNTriangles_5b(
        8, 7, 11, // tri0
        12, 2, 13, // tri1
        2, 1, 13, // tri2
        0, 14, 1 // tri3
    ),
    gsSPNTriangles_5b(
        15, 14, 0, // tri0
        15, 16, 14, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_m_ta_2_modelT[] = {
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
    gsSPVertex(&grd_s_m_ta_2_v[189], 23, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 6, 4 // tri2
    ),
    gsSPNTriangles_5b(
        3, 7, 6, // tri0
        8, 9, 10, // tri1
        11, 12, 13, // tri2
        12, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 16, // tri0
        13, 16, 11, // tri1
        11, 16, 17, // tri2
        9, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        10, 9, 18, // tri0
        19, 7, 3, // tri1
        20, 19, 3, // tri2
        5, 20, 3 // tri3
    ),
    gsSPNTriangles_5b(
        7, 19, 21, // tri0
        0, 7, 21, // tri1
        22, 1, 0, // tri2
        22, 0, 21 // tri3
    ),
    gsSPNTriangles_5b(
        11, 17, 9, // tri0
        0, 2, 6, // tri1
        7, 0, 6, // tri2
        9, 8, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 9, 12, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_m_ta_2_v[212], 20, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        2, 3, 4 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 6, // tri0
        4, 3, 5, // tri1
        6, 5, 7, // tri2
        5, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        9, 10, 11, // tri1
        9, 8, 10, // tri2
        11, 10, 12 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 14, // tri0
        12, 10, 13, // tri1
        14, 13, 15, // tri2
        13, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        18, 17, 16, // tri1
        18, 19, 17, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
