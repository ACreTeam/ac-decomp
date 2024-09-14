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

static Vtx grd_s_m_6_v[] = {
#include "assets/field/bg/grd_s_m_6_v.inc"
};

extern Gfx grd_s_m_6_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_6_v[164], 30, 0),
    gsSPNTrianglesInit_5b(
        32, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 2, 1, // tri0
        6, 5, 4, // tri1
        6, 7, 5, // tri2
        8, 9, 6 // tri3
    ),
    gsSPNTriangles_5b(
        8, 10, 9, // tri0
        9, 7, 6, // tri1
        11, 12, 13, // tri2
        12, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        12, 15, 14, // tri0
        16, 17, 8, // tri1
        17, 18, 8, // tri2
        18, 19, 8 // tri3
    ),
    gsSPNTriangles_5b(
        19, 10, 8, // tri0
        3, 20, 1, // tri1
        20, 21, 1, // tri2
        21, 4, 1 // tri3
    ),
    gsSPNTriangles_5b(
        21, 6, 4, // tri0
        21, 22, 6, // tri1
        22, 8, 6, // tri2
        22, 16, 8 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 16, // tri0
        22, 24, 23, // tri1
        24, 25, 23, // tri2
        24, 15, 25 // tri3
    ),
    gsSPNTriangles_5b(
        24, 26, 15, // tri0
        26, 14, 15, // tri1
        18, 27, 19, // tri2
        27, 28, 19 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 19, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_6_v[0], 25, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        5, 7, 8, // tri1
        6, 9, 7, // tri2
        6, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 9, // tri0
        11, 12, 9, // tri1
        11, 13, 12, // tri2
        13, 14, 12 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 12, // tri0
        14, 16, 15, // tri1
        16, 17, 15, // tri2
        16, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 17, // tri0
        18, 20, 19, // tri1
        20, 21, 19, // tri2
        20, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 21, // tri0
        22, 24, 23, // tri1
        24, 2, 23, // tri2
        24, 0, 2 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_6_v[25], 17, 0),
    gsSPNTrianglesInit_5b(
        13, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        5, 6, 4, // tri1
        5, 7, 6, // tri2
        5, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 7, // tri0
        8, 10, 9, // tri1
        11, 0, 2, // tri2
        11, 12, 0 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 15, // tri0
        13, 16, 14, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_6_v[42], 32, 0),
    gsSPNTrianglesInit_5b(
        15, // tri count
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
        14, 16, 15, // tri0
        17, 18, 19, // tri1
        20, 21, 22, // tri2
        23, 20, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 14, 26, // tri0
        27, 28, 29, // tri1
        30, 17, 31, // tri2
        30, 31, 28 // tri3
    ),
    gsSPVertex(&grd_s_m_6_v[74], 19, 0),
    gsSPNTrianglesInit_5b(
        9, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        0, 2, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 0, 6, // tri0
        8, 9, 10, // tri1
        11, 12, 13, // tri2
        14, 11, 15 // tri3
    ),
    gsSPNTriangles_5b(
        9, 16, 17, // tri0
        16, 14, 18, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_m_6_v[93], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        5, 8, 7, // tri1
        8, 9, 7, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 10, 13, // tri0
        14, 13, 15, // tri1
        16, 17, 1, // tri2
        1, 17, 3 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 16, // tri0
        20, 21, 19, // tri1
        21, 20, 22, // tri2
        21, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 21, // tri0
        23, 21, 26, // tri1
        22, 26, 21, // tri2
        3, 17, 27 // tri3
    ),
    gsSPNTriangles_5b(
        17, 25, 28, // tri0
        28, 27, 17, // tri1
        29, 7, 9, // tri2
        12, 30, 6 // tri3
    ),
    gsSPNTriangles_5b(
        30, 4, 6, // tri0
        13, 31, 11, // tri1
        13, 14, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_m_6_v[125], 21, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        4, 6, 5 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 6, // tri0
        8, 9, 10, // tri1
        10, 9, 11, // tri2
        11, 9, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 12, 14, // tri0
        15, 16, 17, // tri1
        17, 18, 19, // tri2
        19, 18, 0 // tri3
    ),
    gsSPNTriangles_5b(
        18, 1, 0, // tri0
        15, 17, 19, // tri1
        20, 5, 6, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_6_v[146], 18, 0),
    gsSPNTrianglesInit_5b(
        14, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 2, // tri0
        5, 6, 2, // tri1
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
        14, 15, 16, // tri1
        14, 17, 15, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_m_6_modelT[] = {
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
    gsSPVertex(&grd_s_m_6_v[194], 27, 0),
    gsSPNTrianglesInit_5b(
        29, // tri count
        0, 1, 2, // tri0
        3, 0, 2, // tri1
        4, 3, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 2, 5, // tri0
        4, 5, 6, // tri1
        7, 4, 6, // tri2
        8, 7, 6 // tri3
    ),
    gsSPNTriangles_5b(
        8, 6, 9, // tri0
        10, 8, 9, // tri1
        11, 10, 9, // tri2
        11, 9, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 12, 13, // tri0
        14, 11, 13, // tri1
        15, 16, 17, // tri2
        18, 15, 17 // tri3
    ),
    gsSPNTriangles_5b(
        15, 18, 19, // tri0
        15, 19, 20, // tri1
        11, 14, 21, // tri2
        11, 21, 22 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 22, // tri0
        10, 22, 23, // tri1
        8, 10, 23, // tri2
        8, 23, 24 // tri3
    ),
    gsSPNTriangles_5b(
        7, 8, 24, // tri0
        7, 24, 25, // tri1
        4, 7, 25, // tri2
        3, 4, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 0, 3, // tri0
        26, 3, 25, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_m_6_v[221], 26, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        0, 5, 3, // tri0
        3, 6, 4, // tri1
        6, 7, 4, // tri2
        6, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        6, 9, 8, // tri0
        9, 10, 8, // tri1
        9, 11, 10, // tri2
        9, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        9, 13, 12, // tri0
        13, 14, 12, // tri1
        13, 15, 14, // tri2
        12, 16, 11 // tri3
    ),
    gsSPNTriangles_5b(
        12, 17, 16, // tri0
        17, 18, 16, // tri1
        17, 19, 18, // tri2
        19, 20, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 21, 20, // tri0
        19, 22, 21, // tri1
        22, 23, 21, // tri2
        22, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 23, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
