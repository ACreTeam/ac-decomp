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

static Vtx grd_s_m_wf_1_v[] = {
#include "assets/field/bg/grd_s_m_wf_1_v.inc"
};

extern Gfx grd_s_m_wf_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_wf_1_v[161], 21, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        0, 3, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 0, 4, // tri0
        5, 4, 6, // tri1
        5, 6, 7, // tri2
        8, 5, 7 // tri3
    ),
    gsSPNTriangles_5b(
        8, 7, 9, // tri0
        8, 9, 10, // tri1
        11, 8, 10, // tri2
        12, 11, 10 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        7, 6, 13, // tri1
        7, 13, 15, // tri2
        9, 7, 15 // tri3
    ),
    gsSPNTriangles_5b(
        9, 15, 16, // tri0
        9, 16, 17, // tri1
        10, 9, 17, // tri2
        12, 10, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 12, 17, // tri0
        19, 3, 2, // tri1
        20, 19, 2, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_wf_1_v[144], 17, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        6, 3, 8, // tri0
        3, 4, 8, // tri1
        9, 10, 11, // tri2
        12, 9, 11 // tri3
    ),
    gsSPNTriangles_5b(
        1, 12, 13, // tri0
        9, 14, 10, // tri1
        14, 15, 16, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bridge_2_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bridge_2_tex_dummy, G_IM_FMT_CI, 128, 32, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_m_wf_1_v[231], 32, 0),
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
    gsSPVertex(&grd_s_m_wf_1_v[263], 28, 0),
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
    gsSPVertex(&grd_s_m_wf_1_v[0], 18, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        3, 0, 2, // tri1
        3, 2, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 3, 4, // tri0
        5, 4, 6, // tri1
        7, 5, 6, // tri2
        7, 6, 8 // tri3
    ),
    gsSPNTriangles_5b(
        9, 7, 8, // tri0
        9, 8, 10, // tri1
        9, 10, 11, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 12, 14, // tri0
        15, 14, 16, // tri1
        13, 12, 17, // tri2
        11, 13, 17 // tri3
    ),
    gsSPNTriangles_5b(
        9, 11, 17, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_wf_1_v[18], 21, 0),
    gsSPNTrianglesInit_5b(
        17, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        5, 7, 8, // tri1
        9, 5, 8, // tri2
        9, 8, 10 // tri3
    ),
    gsSPNTriangles_5b(
        1, 11, 4, // tri0
        6, 12, 7, // tri1
        9, 10, 13, // tri2
        14, 9, 13 // tri3
    ),
    gsSPNTriangles_5b(
        15, 14, 13, // tri0
        15, 13, 16, // tri1
        15, 16, 17, // tri2
        18, 15, 17 // tri3
    ),
    gsSPNTriangles_5b(
        19, 18, 17, // tri0
        20, 19, 17, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_wf_1_v[39], 24, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        1, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        9, 10, 11, // tri1
        10, 3, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 18, // tri0
        19, 16, 20, // tri1
        14, 21, 22, // tri2
        21, 19, 23 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_m_wf_1_v[63], 32, 0),
    gsSPNTrianglesInit_5b(
        29, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 0, 2 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 2, // tri0
        6, 7, 8, // tri1
        7, 9, 8, // tri2
        7, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 9, // tri0
        12, 13, 14, // tri1
        13, 15, 14, // tri2
        6, 8, 16 // tri3
    ),
    gsSPNTriangles_5b(
        3, 17, 5, // tri0
        17, 18, 5, // tri1
        5, 16, 2, // tri2
        15, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        19, 18, 21, // tri1
        11, 22, 9, // tri2
        7, 23, 10 // tri3
    ),
    gsSPNTriangles_5b(
        7, 24, 23, // tri0
        22, 4, 9, // tri1
        22, 25, 4, // tri2
        25, 0, 4 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 28, // tri0
        27, 1, 28, // tri1
        27, 29, 1, // tri2
        29, 3, 1 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 3, // tri0
        26, 31, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_m_wf_1_v[95], 15, 0),
    gsSPNTrianglesInit_5b(
        12, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 2, 4 // tri2
    ),
    gsSPNTriangles_5b(
        3, 6, 2, // tri0
        6, 7, 2, // tri1
        7, 8, 2, // tri2
        8, 9, 2 // tri3
    ),
    gsSPNTriangles_5b(
        9, 0, 2, // tri0
        8, 10, 9, // tri1
        8, 11, 10, // tri2
        12, 13, 10 // tri3
    ),
    gsSPNTriangles_5b(
        4, 14, 5, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_wf_1_v[110], 17, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 7, 8 // tri2
    ),
    gsSPNTriangles_5b(
        4, 9, 10, // tri0
        11, 3, 12, // tri1
        13, 14, 15, // tri2
        1, 11, 16 // tri3
    ),
    gsSPNTriangles_5b(
        13, 6, 14, // tri0
        9, 13, 15, // tri1
        11, 12, 16, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_wf_1_v[127], 17, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        4, 0, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        8, 5, 7, // tri1
        8, 7, 9, // tri2
        10, 8, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 9, 11, // tri0
        10, 11, 12, // tri1
        13, 10, 12, // tri2
        13, 12, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 13, // tri0
        15, 13, 14, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_m_wf_1_modelT[] = {
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
    gsSPVertex(&grd_s_m_wf_1_v[182], 24, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        1, 6, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        9, 10, 7, // tri1
        7, 11, 12, // tri2
        13, 14, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 13, 17, // tri0
        5, 4, 7, // tri1
        16, 18, 13, // tri2
        3, 17, 4 // tri3
    ),
    gsSPNTriangles_5b(
        3, 16, 17, // tri0
        17, 13, 15, // tri1
        4, 19, 20, // tri2
        9, 7, 12 // tri3
    ),
    gsSPNTriangles_5b(
        4, 20, 11, // tri0
        4, 17, 19, // tri1
        17, 15, 19, // tri2
        7, 10, 8 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 0, // tri0
        7, 4, 11, // tri1
        22, 1, 0, // tri2
        22, 23, 1 // tri3
    ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_m_wf_1_v[206], 25, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        1, 0, 9, // tri2
        0, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        12, 14, 13, // tri1
        13, 14, 15, // tri2
        14, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        15, 16, 17, // tri0
        9, 17, 16, // tri1
        9, 10, 17, // tri2
        18, 19, 20 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        22, 21, 23, // tri1
        12, 23, 21, // tri2
        12, 11, 23 // tri3
    ),
    gsSPNTriangles_5b(
        7, 8, 24, // tri0
        19, 24, 8, // tri1
        19, 18, 24, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
