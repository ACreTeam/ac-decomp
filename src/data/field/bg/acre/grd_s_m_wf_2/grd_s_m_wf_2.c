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
extern u8 bridge_2_pal_dummy[];
extern u8 bridge_2_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_m_wf_2_v[] = {
#include "assets/field/bg/grd_s_m_wf_2_v.inc"
};

extern Gfx grd_s_m_wf_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_wf_2_v[225], 31, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        0, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        0, 5, 4, // tri0
        5, 6, 4, // tri1
        5, 7, 6, // tri2
        5, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 7, // tri0
        8, 10, 9, // tri1
        10, 11, 9, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 14, // tri0
        13, 16, 15, // tri1
        13, 17, 16, // tri2
        17, 18, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 18, // tri0
        17, 20, 19, // tri1
        17, 21, 20, // tri2
        20, 22, 19 // tri3
    ),
    gsSPNTriangles_5b(
        23, 24, 25, // tri0
        24, 26, 25, // tri1
        24, 27, 26, // tri2
        27, 28, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 29, 28, // tri0
        28, 30, 26, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_wf_2_v[197], 28, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 3, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 5, 8, // tri0
        9, 7, 10, // tri1
        11, 12, 13, // tri2
        14, 11, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        17, 14, 19, // tri1
        14, 15, 19, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        23, 20, 22, // tri0
        12, 23, 24, // tri1
        20, 25, 21, // tri2
        25, 26, 27 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bridge_2_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bridge_2_tex_dummy, G_IM_FMT_CI, 128, 32, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_m_wf_2_v[325], 32, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        1, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 2, // tri0
        6, 7, 8, // tri1
        6, 8, 9, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        10, 12, 13, // tri0
        14, 15, 11, // tri1
        14, 11, 10, // tri2
        15, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 11, // tri0
        18, 19, 20, // tri1
        18, 20, 21, // tri2
        22, 18, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 21, 23, // tri0
        23, 21, 24, // tri1
        23, 24, 25, // tri2
        26, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        26, 28, 29, // tri0
        30, 31, 27, // tri1
        30, 27, 26, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_m_wf_2_v[357], 28, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 6, 7, // tri0
        8, 4, 7, // tri1
        8, 7, 9, // tri2
        9, 7, 10 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        12, 13, 14, // tri1
        12, 14, 15, // tri2
        16, 15, 17 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        19, 12, 15, // tri1
        19, 15, 16, // tri2
        20, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        20, 22, 23, // tri0
        24, 25, 26, // tri1
        24, 26, 21, // tri2
        27, 24, 21 // tri3
    ),
    gsSPNTriangles_5b(
        27, 21, 20, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_wf_2_v[0], 17, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        0, 3, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 0, 4, // tri0
        5, 4, 6, // tri1
        7, 5, 6, // tri2
        7, 6, 8 // tri3
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 7, 9, // tri1
        11, 10, 9, // tri2
        11, 9, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        14, 11, 13, // tri1
        15, 14, 13, // tri2
        16, 15, 13 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_wf_2_v[17], 24, 0),
    gsSPNTrianglesInit_5b(
        20, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        3, 6, 5, // tri1
        6, 7, 5, // tri2
        7, 8, 5 // tri3
    ),
    gsSPNTriangles_5b(
        7, 9, 8, // tri0
        7, 10, 9, // tri1
        10, 11, 9, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 12, // tri0
        13, 14, 12, // tri1
        15, 16, 17, // tri2
        16, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        16, 19, 18, // tri0
        16, 20, 19, // tri1
        20, 21, 19, // tri2
        21, 22, 19 // tri3
    ),
    gsSPNTriangles_5b(
        21, 23, 22, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_wf_2_v[41], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 4, 8, // tri0
        5, 9, 10, // tri1
        11, 12, 13, // tri2
        12, 7, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        18, 19, 16, // tri1
        20, 21, 22, // tri2
        18, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        21, 23, 24, // tri0
        23, 25, 26, // tri1
        27, 28, 29, // tri2
        25, 29, 26 // tri3
    ),
    gsSPVertex(&grd_s_m_wf_2_v[71], 17, 0),
    gsSPNTrianglesInit_5b(
        9, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        1, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        7, 9, 8, // tri1
        10, 11, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 9, // tri0
        14, 10, 16, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_m_wf_2_v[88], 32, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        9, 10, 11, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 11, // tri0
        13, 14, 11, // tri1
        14, 15, 11, // tri2
        14, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 15, // tri0
        17, 18, 15, // tri1
        18, 19, 15, // tri2
        17, 20, 18 // tri3
    ),
    gsSPNTriangles_5b(
        18, 21, 19, // tri0
        21, 7, 19, // tri1
        22, 23, 24, // tri2
        23, 25, 24 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 28, // tri0
        27, 29, 28, // tri1
        29, 30, 28, // tri2
        30, 31, 28 // tri3
    ),
    gsSPVertex(&grd_s_m_wf_2_v[120], 29, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 5, // tri0
        8, 9, 10, // tri1
        8, 10, 11, // tri2
        7, 8, 11 // tri3
    ),
    gsSPNTriangles_5b(
        7, 11, 5, // tri0
        1, 12, 2, // tri1
        1, 13, 12, // tri2
        13, 14, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 14, // tri0
        16, 17, 18, // tri1
        19, 17, 16, // tri2
        19, 20, 17 // tri3
    ),
    gsSPNTriangles_5b(
        21, 20, 19, // tri0
        22, 23, 24, // tri1
        22, 25, 23, // tri2
        25, 26, 23 // tri3
    ),
    gsSPNTriangles_5b(
        10, 27, 15, // tri0
        10, 9, 27, // tri1
        9, 26, 27, // tri2
        9, 23, 26 // tri3
    ),
    gsSPNTriangles_5b(
        0, 2, 28, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_wf_2_v[149], 28, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        4, 9, 10, // tri0
        11, 12, 13, // tri1
        14, 15, 16, // tri2
        15, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        12, 19, 20, // tri0
        19, 14, 21, // tri1
        22, 3, 23, // tri2
        24, 25, 26 // tri3
    ),
    gsSPNTriangles_5b(
        1, 22, 27, // tri0
        24, 6, 25, // tri1
        9, 24, 26, // tri2
        22, 23, 27 // tri3
    ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_wf_2_v[177], 20, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 3, // tri0
        4, 6, 5, // tri1
        4, 7, 6, // tri2
        7, 8, 6 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 6, // tri0
        8, 10, 9, // tri1
        10, 11, 9, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 14, // tri0
        13, 16, 15, // tri1
        13, 17, 16, // tri2
        17, 18, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 18, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_m_wf_2_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL1, 0, TEXEL0, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, 0, SHADE, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 60, 120, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, wave2_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPDisplayList(0x0B000000),
    gsSPVertex(&grd_s_m_wf_2_v[256], 30, 0),
    gsSPNTrianglesInit_5b(
        32, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 1, // tri0
        1, 6, 3, // tri1
        6, 7, 3, // tri2
        6, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        6, 9, 8, // tri0
        10, 6, 1, // tri1
        10, 9, 6, // tri2
        5, 10, 1 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 9, // tri0
        11, 12, 9, // tri1
        12, 13, 9, // tri2
        9, 13, 8 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 8, // tri0
        13, 15, 14, // tri1
        15, 16, 14, // tri2
        12, 15, 13 // tri3
    ),
    gsSPNTriangles_5b(
        12, 17, 15, // tri0
        18, 19, 20, // tri1
        19, 21, 20, // tri2
        19, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 23, // tri0
        21, 24, 23, // tri1
        25, 18, 26, // tri2
        18, 27, 26 // tri3
    ),
    gsSPNTriangles_5b(
        18, 20, 27, // tri0
        27, 28, 26, // tri1
        27, 29, 28, // tri2
        27, 23, 29 // tri3
    ),
    gsSPNTriangles_5b(
        27, 20, 23, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_m_wf_2_v[286], 32, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 2, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 2, 7, // tri1
        8, 6, 9, // tri2
        8, 10, 6 // tri3
    ),
    gsSPNTriangles_5b(
        11, 10, 12, // tri0
        13, 14, 15, // tri1
        14, 10, 15, // tri2
        16, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        17, 14, 18, // tri0
        19, 20, 21, // tri1
        20, 17, 21, // tri2
        22, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 20, // tri0
        24, 23, 25, // tri1
        26, 27, 24, // tri2
        27, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        28, 27, 29, // tri0
        28, 30, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_m_wf_2_v[317], 8, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 1, 0 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 1, 7, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
