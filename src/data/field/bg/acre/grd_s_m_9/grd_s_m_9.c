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

static Vtx grd_s_m_9_v[] = {
#include "assets/field/bg/grd_s_m_9_v.inc"
};

extern Gfx grd_s_m_9_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_9_v[108], 23, 0),
    gsSPNTrianglesInit_5b(
        25, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        3, 6, 5, // tri1
        6, 7, 5, // tri2
        6, 8, 7 // tri3
    ),
    gsSPNTriangles_5b(
        6, 9, 8, // tri0
        9, 10, 8, // tri1
        9, 11, 10, // tri2
        9, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        12, 13, 11, // tri0
        12, 14, 13, // tri1
        12, 15, 14, // tri2
        12, 16, 15 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 15, // tri0
        0, 18, 3, // tri1
        18, 19, 3, // tri2
        19, 9, 3 // tri3
    ),
    gsSPNTriangles_5b(
        9, 6, 3, // tri0
        19, 20, 9, // tri1
        20, 12, 9, // tri2
        20, 21, 12 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 12, // tri0
        22, 16, 12, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_9_v[0], 25, 0),
    gsSPNTrianglesInit_5b(
        23, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        6, 7, 8, // tri1
        7, 9, 8, // tri2
        8, 10, 6 // tri3
    ),
    gsSPNTriangles_5b(
        8, 11, 10, // tri0
        11, 5, 10, // tri1
        11, 4, 5, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 14, // tri0
        16, 17, 12, // tri1
        14, 16, 12, // tri2
        15, 13, 18 // tri3
    ),
    gsSPNTriangles_5b(
        19, 15, 18, // tri0
        19, 18, 20, // tri1
        21, 19, 20, // tri2
        22, 21, 20 // tri3
    ),
    gsSPNTriangles_5b(
        22, 20, 23, // tri0
        24, 22, 23, // tri1
        24, 23, 0, // tri2
        2, 24, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_9_v[25], 30, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
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
        4, 18, 19, // tri2
        20, 21, 0 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 20, // tri0
        24, 25, 22, // tri1
        24, 26, 25, // tri2
        24, 27, 26 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_m_9_v[55], 29, 0),
    gsSPNTrianglesInit_5b(
        28, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        2, 1, 4 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        6, 7, 8, // tri1
        7, 9, 8, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        13, 14, 12, // tri1
        13, 15, 14, // tri2
        15, 8, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 6, 8, // tri0
        15, 16, 6, // tri1
        10, 17, 18, // tri2
        17, 19, 18 // tri3
    ),
    gsSPNTriangles_5b(
        8, 20, 21, // tri0
        20, 22, 21, // tri1
        3, 23, 24, // tri2
        23, 22, 24 // tri3
    ),
    gsSPNTriangles_5b(
        8, 21, 14, // tri0
        20, 25, 22, // tri1
        25, 24, 22, // tri2
        10, 18, 11 // tri3
    ),
    gsSPNTriangles_5b(
        19, 26, 18, // tri0
        7, 27, 9, // tri1
        27, 28, 9, // tri2
        20, 8, 9 // tri3
    ),
    gsSPNTriangles_5b(
        1, 3, 24, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_9_v[84], 24, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        5, 8, 6, // tri1
        8, 9, 6, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 9, // tri0
        10, 12, 11, // tri1
        12, 13, 11, // tri2
        12, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 13, // tri0
        14, 16, 15, // tri1
        16, 17, 15, // tri2
        16, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 17, // tri0
        18, 2, 19, // tri1
        2, 3, 19, // tri2
        0, 20, 1 // tri3
    ),
    gsSPNTriangles_5b(
        0, 21, 20, // tri0
        21, 22, 20, // tri1
        21, 23, 22, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_m_9_modelT[] = {
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
    gsSPVertex(&grd_s_m_9_v[131], 32, 0),
    gsSPNTrianglesInit_5b(
        38, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        4, 7, 5, // tri0
        5, 8, 6, // tri1
        8, 9, 6, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 9, // tri0
        10, 12, 11, // tri1
        12, 13, 11, // tri2
        12, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 13, // tri0
        14, 16, 15, // tri1
        16, 17, 15, // tri2
        16, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 17, // tri0
        18, 1, 19, // tri1
        1, 0, 19, // tri2
        3, 20, 2 // tri3
    ),
    gsSPNTriangles_5b(
        3, 21, 20, // tri0
        21, 22, 20, // tri1
        21, 23, 22, // tri2
        7, 24, 5 // tri3
    ),
    gsSPNTriangles_5b(
        24, 25, 5, // tri0
        25, 8, 5, // tri1
        25, 26, 8, // tri2
        26, 10, 8 // tri3
    ),
    gsSPNTriangles_5b(
        26, 27, 10, // tri0
        27, 12, 10, // tri1
        27, 14, 12, // tri2
        27, 28, 14 // tri3
    ),
    gsSPNTriangles_5b(
        28, 16, 14, // tri0
        28, 29, 16, // tri1
        29, 30, 16, // tri2
        30, 18, 16 // tri3
    ),
    gsSPNTriangles_5b(
        30, 31, 18, // tri0
        31, 1, 18, // tri1
        31, 3, 1, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_m_9_v[163], 7, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        3, 6, 5, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_m_9_v[170], 26, 0),
    gsSPNTrianglesInit_5b(
        24, // tri count
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
        9, 10, 8, // tri1
        11, 10, 9, // tri2
        12, 13, 11 // tri3
    ),
    gsSPNTriangles_5b(
        13, 10, 11, // tri0
        14, 13, 12, // tri1
        14, 15, 13, // tri2
        16, 15, 14 // tri3
    ),
    gsSPNTriangles_5b(
        17, 18, 16, // tri0
        18, 15, 16, // tri1
        19, 20, 17, // tri2
        20, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        21, 20, 19, // tri0
        21, 22, 20, // tri1
        23, 22, 21, // tri2
        24, 25, 23 // tri3
    ),
    gsSPNTriangles_5b(
        25, 22, 23, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
