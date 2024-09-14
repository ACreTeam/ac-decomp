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
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_m_7_v[] = {
#include "assets/field/bg/grd_s_m_7_v.inc"
};

extern Gfx grd_s_m_7_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_7_v[123], 23, 0),
    gsSPNTrianglesInit_5b(
        27, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 0, 4 // tri2
    ),
    gsSPNTriangles_5b(
        0, 5, 4, // tri0
        5, 6, 4, // tri1
        1, 4, 7, // tri2
        4, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        4, 9, 8, // tri0
        4, 6, 9, // tri1
        3, 10, 11, // tri2
        3, 1, 10 // tri3
    ),
    gsSPNTriangles_5b(
        1, 7, 10, // tri0
        12, 13, 14, // tri1
        13, 15, 14, // tri2
        15, 16, 14 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 14, // tri0
        16, 11, 17, // tri1
        16, 3, 11, // tri2
        6, 18, 9 // tri3
    ),
    gsSPNTriangles_5b(
        6, 19, 18, // tri0
        6, 20, 19, // tri1
        13, 21, 15, // tri2
        21, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 16, // tri0
        22, 3, 16, // tri1
        22, 2, 3, // tri2
        5, 20, 6 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_7_v[110], 13, 0),
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
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_7_v[0], 23, 0),
    gsSPNTrianglesInit_5b(
        21, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        5, 8, 6, // tri1
        5, 9, 8, // tri2
        9, 10, 8 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 8, // tri0
        12, 2, 13, // tri1
        12, 14, 2, // tri2
        14, 0, 2 // tri3
    ),
    gsSPNTriangles_5b(
        0, 15, 3, // tri0
        15, 16, 3, // tri1
        16, 17, 3, // tri2
        16, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        16, 7, 18, // tri0
        7, 4, 18, // tri1
        10, 19, 11, // tri2
        19, 20, 11 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        19, 22, 21, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_7_v[23], 21, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 7, 8, // tri0
        9, 7, 6, // tri1
        10, 9, 11, // tri2
        12, 13, 0 // tri3
    ),
    gsSPNTriangles_5b(
        8, 14, 15, // tri0
        7, 14, 8, // tri1
        14, 16, 15, // tri2
        16, 17, 18 // tri3
    ),
    gsSPNTriangles_5b(
        17, 19, 20, // tri0
        19, 13, 12, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_m_7_v[44], 32, 0),
    gsSPNTrianglesInit_5b(
        32, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        0, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        9, 10, 11, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 9, 11, // tri0
        14, 10, 15, // tri1
        10, 16, 15, // tri2
        12, 10, 17 // tri3
    ),
    gsSPNTriangles_5b(
        10, 14, 17, // tri0
        18, 19, 1, // tri1
        19, 2, 1, // tri2
        19, 20, 2 // tri3
    ),
    gsSPNTriangles_5b(
        4, 21, 3, // tri0
        4, 22, 21, // tri1
        18, 23, 19, // tri2
        18, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 23, // tri0
        24, 26, 25, // tri1
        26, 11, 25, // tri2
        26, 27, 11 // tri3
    ),
    gsSPNTriangles_5b(
        27, 13, 11, // tri0
        27, 28, 13, // tri1
        3, 28, 1, // tri2
        29, 5, 7 // tri3
    ),
    gsSPNTriangles_5b(
        29, 30, 5, // tri0
        30, 16, 5, // tri1
        30, 15, 16, // tri2
        10, 9, 16 // tri3
    ),
    gsSPNTriangles_5b(
        15, 31, 14, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_7_v[76], 13, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        3, 0, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 8, // tri0
        9, 10, 11, // tri1
        10, 3, 12, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_7_v[89], 21, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
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
        7, 9, 8, // tri0
        9, 10, 8, // tri1
        9, 11, 10, // tri2
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
        18, 19, 17, // tri2
        18, 20, 19 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_m_7_modelT[] = {
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
    gsSPVertex(&grd_s_m_7_v[146], 31, 0),
    gsSPNTrianglesInit_5b(
        37, // tri count
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
        8, 9, 10, // tri1
        11, 8, 10, // tri2
        11, 10, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 11, 12, // tri0
        13, 12, 14, // tri1
        15, 13, 14, // tri2
        15, 14, 16 // tri3
    ),
    gsSPNTriangles_5b(
        17, 15, 16, // tri0
        17, 16, 18, // tri1
        19, 17, 18, // tri2
        20, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 17, // tri0
        21, 22, 17, // tri1
        23, 17, 22, // tri2
        23, 15, 17 // tri3
    ),
    gsSPNTriangles_5b(
        24, 13, 23, // tri0
        13, 15, 23, // tri1
        13, 25, 11, // tri2
        13, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 11, 25, // tri0
        26, 8, 11, // tri1
        27, 6, 26, // tri2
        6, 8, 26 // tri3
    ),
    gsSPNTriangles_5b(
        0, 28, 1, // tri0
        0, 29, 28, // tri1
        0, 4, 29, // tri2
        4, 30, 29 // tri3
    ),
    gsSPNTriangles_5b(
        4, 6, 30, // tri0
        30, 6, 27, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_m_7_v[177], 24, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 2, 3 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 2, // tri0
        6, 5, 4, // tri1
        7, 8, 6, // tri2
        8, 5, 6 // tri3
    ),
    gsSPNTriangles_5b(
        9, 8, 7, // tri0
        9, 10, 8, // tri1
        11, 10, 9, // tri2
        12, 13, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 10, 11, // tri0
        14, 13, 12, // tri1
        15, 13, 14, // tri2
        15, 16, 13 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 15, // tri0
        18, 16, 15, // tri1
        19, 18, 17, // tri2
        20, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 18, // tri0
        22, 23, 20, // tri1
        23, 21, 20, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
