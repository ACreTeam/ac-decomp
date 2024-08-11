#include "libforest/gbi_extensions.h"

extern u8 wave3_tex_dummy[];
extern u8 wave2_tex_dummy[];
extern u8 wave1_tex_dummy[];
extern u8 sand_tex_dummy[];
extern u8 beach_pal_dummy2[];
extern u8 beach2_tex_dummy2[];
extern u8 beach1_tex_dummy2[];
extern u8 bush_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 stone_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_m_ta_3_v[] = {
#include "assets/field/bg/grd_s_m_ta_3_v.inc"
};

extern Gfx grd_s_m_ta_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_ta_3_v[174], 23, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 5, // tri0
        7, 8, 5, // tri1
        7, 9, 8, // tri2
        9, 2, 8 // tri3
    ),
    gsSPNTriangles_5b(
        2, 10, 8, // tri0
        2, 1, 10, // tri1
        3, 11, 4, // tri2
        12, 13, 0 // tri3
    ),
    gsSPNTriangles_5b(
        13, 1, 0, // tri0
        14, 15, 16, // tri1
        15, 17, 16, // tri2
        17, 18, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 13, 18, // tri0
        13, 12, 18, // tri1
        15, 19, 17, // tri2
        19, 20, 17 // tri3
    ),
    gsSPNTriangles_5b(
        20, 13, 17, // tri0
        20, 1, 13, // tri1
        20, 10, 1, // tri2
        21, 8, 10 // tri3
    ),
    gsSPNTriangles_5b(
        21, 5, 8, // tri0
        21, 22, 5, // tri1
        22, 3, 5, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_ta_3_v[161], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 10, // tri1
        9, 11, 12, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_m_ta_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        27, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        3, 4, 0 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        3, 6, 5, // tri1
        2, 1, 7, // tri2
        1, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        10, 7, 11, // tri1
        7, 8, 11, // tri2
        9, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 10, // tri0
        12, 14, 13, // tri1
        14, 15, 13, // tri2
        14, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        14, 17, 16, // tri0
        17, 18, 16, // tri1
        18, 19, 16, // tri2
        18, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 19, // tri0
        21, 22, 19, // tri1
        21, 23, 22, // tri2
        23, 24, 22 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        25, 28, 26, // tri1
        25, 29, 28, // tri2
        29, 24, 28 // tri3
    ),
    gsSPVertex(&grd_s_m_ta_3_v[30], 14, 0),
    gsSPNTrianglesInit_5b(
        12, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        6, 4, 8, // tri2
        4, 9, 8 // tri3
    ),
    gsSPNTriangles_5b(
        4, 3, 9, // tri0
        3, 10, 9, // tri1
        10, 11, 9, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 11, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_ta_3_v[44], 24, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        3, 4, 0, // tri1
        3, 5, 4 // tri2
    ),
    gsSPNTriangles_5b(
        3, 6, 5, // tri0
        0, 2, 3, // tri1
        7, 8, 5, // tri2
        5, 6, 7 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 8, // tri0
        8, 7, 9, // tri1
        9, 11, 10, // tri2
        11, 12, 10 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 12, // tri0
        12, 11, 13, // tri1
        15, 16, 14, // tri2
        14, 13, 15 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 16, // tri0
        16, 15, 17, // tri1
        19, 20, 18, // tri2
        19, 21, 20 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 21, // tri0
        21, 19, 22, // tri1
        18, 17, 19, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_ta_3_v[68], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 7, 10, // tri1
        1, 11, 12, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_ta_3_v[81], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 10, // tri1
        9, 11, 12, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_ta_3_v[94], 32, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 4, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        6, 4, 3, // tri0
        5, 7, 8, // tri1
        7, 9, 10, // tri2
        11, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 11, // tri0
        9, 13, 12, // tri1
        14, 15, 16, // tri2
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
    gsSPVertex(&grd_s_m_ta_3_v[126], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 7, 10, // tri1
        11, 9, 12, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_ta_3_v[139], 22, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        2, 1, 4 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        6, 4, 5, // tri1
        6, 7, 4, // tri2
        6, 8, 9 // tri3
    ),
    gsSPNTriangles_5b(
        9, 7, 6, // tri0
        8, 10, 11, // tri1
        11, 9, 8, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 12, 10, // tri0
        13, 14, 12, // tri1
        15, 14, 13, // tri2
        15, 16, 14 // tri3
    ),
    gsSPNTriangles_5b(
        16, 15, 17, // tri0
        18, 16, 17, // tri1
        19, 18, 17, // tri2
        20, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        21, 20, 19, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_m_ta_3_modelT[] = {
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
    gsSPVertex(&grd_s_m_ta_3_v[197], 30, 0),
    gsSPNTrianglesInit_5b(
        37, // tri count
        0, 1, 2, // tri0
        3, 0, 2, // tri1
        4, 3, 2 // tri2
    ),
    gsSPNTriangles_5b(
        2, 1, 5, // tri0
        6, 2, 5, // tri1
        7, 4, 2, // tri2
        7, 2, 6 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 10, // tri0
        8, 10, 11, // tri1
        0, 11, 10, // tri2
        10, 1, 0 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 10, // tri0
        10, 13, 5, // tri1
        10, 5, 1, // tri2
        10, 9, 12 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 16, // tri0
        16, 15, 9, // tri1
        8, 16, 9, // tri2
        14, 17, 15 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 18, // tri0
        18, 12, 9, // tri1
        9, 15, 18, // tri2
        19, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 19, // tri0
        19, 14, 20, // tri1
        23, 19, 22, // tri2
        19, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        19, 24, 14, // tri0
        14, 24, 17, // tri1
        25, 26, 27, // tri2
        21, 25, 27 // tri3
    ),
    gsSPNTriangles_5b(
        27, 22, 21, // tri0
        28, 29, 27, // tri1
        26, 28, 27, // tri2
        29, 23, 22 // tri3
    ),
    gsSPNTriangles_5b(
        27, 29, 22, // tri0
        14, 16, 20, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_m_ta_3_v[227], 20, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        3, 4, 0, // tri1
        4, 1, 0 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 2, // tri0
        5, 6, 2, // tri1
        5, 7, 6, // tri2
        5, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 7, // tri0
        8, 10, 9, // tri1
        8, 11, 10, // tri2
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
        16, 18, 17, // tri1
        16, 19, 18, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
