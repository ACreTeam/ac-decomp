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

static Vtx grd_s_il_1_v[] = {
#include "assets/field/bg/grd_s_il_1_v.inc"
};

extern Gfx grd_s_il_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_il_1_v[145], 32, 0),
    gsSPNTrianglesInit_5b(
        28, // tri count
        0, 1, 2, // tri0
        3, 4, 0, // tri1
        3, 0, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 3, 2, // tri0
        6, 5, 2, // tri1
        7, 8, 9, // tri2
        7, 10, 8 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 8, // tri0
        10, 12, 11, // tri1
        10, 13, 12, // tri2
        13, 14, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 14, // tri0
        15, 16, 14, // tri1
        16, 17, 14, // tri2
        16, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 19, 17, // tri0
        19, 20, 17, // tri1
        19, 21, 20, // tri2
        21, 22, 20 // tri3
    ),
    gsSPNTriangles_5b(
        21, 23, 22, // tri0
        23, 24, 22, // tri1
        24, 25, 22, // tri2
        24, 26, 25 // tri3
    ),
    gsSPNTriangles_5b(
        24, 27, 26, // tri0
        27, 28, 26, // tri1
        27, 29, 28, // tri2
        29, 30, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 31, 30, // tri0
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
    gsSPVertex(&grd_s_il_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        28, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        1, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        5, 8, 6, // tri1
        8, 9, 6, // tri2
        8, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        8, 11, 10, // tri0
        11, 12, 10, // tri1
        11, 13, 12, // tri2
        11, 14, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 15, 13, // tri0
        14, 16, 15, // tri1
        16, 17, 15, // tri2
        16, 18, 17 // tri3
    ),
    gsSPNTriangles_5b(
        16, 19, 18, // tri0
        19, 20, 18, // tri1
        19, 21, 20, // tri2
        19, 22, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 21, // tri0
        22, 24, 23, // tri1
        22, 25, 24, // tri2
        25, 26, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 27, 26, // tri0
        25, 28, 27, // tri1
        28, 29, 27, // tri2
        28, 30, 29 // tri3
    ),
    gsSPNTriangles_5b(
        30, 31, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_il_1_v[32], 10, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        6, 7, 8, // tri1
        7, 9, 8, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_il_1_v[42], 6, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        0, 3, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 0, 4, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_il_1_v[48], 32, 0),
    gsSPNTrianglesInit_5b(
        18, // tri count
        0, 1, 2, // tri0
        3, 4, 1, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        6, 8, 9, // tri1
        8, 10, 11, // tri2
        12, 13, 14 // tri3
    ),
    gsSPNTriangles_5b(
        10, 14, 11, // tri0
        15, 16, 17, // tri1
        12, 15, 13, // tri2
        16, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        18, 20, 21, // tri0
        20, 22, 21, // tri1
        23, 24, 25, // tri2
        26, 23, 27 // tri3
    ),
    gsSPNTriangles_5b(
        28, 29, 30, // tri0
        28, 30, 22, // tri1
        29, 26, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_il_1_v[80], 17, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        0, 3, 4, // tri1
        5, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        6, 5, 3, // tri0
        7, 8, 6, // tri1
        9, 10, 7, // tri2
        11, 12, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 13, 12, // tri0
        11, 14, 13, // tri1
        14, 15, 16, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_il_1_v[97], 32, 0),
    gsSPNTrianglesInit_5b(
        31, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        2, 6, 7, // tri1
        2, 3, 6, // tri2
        3, 8, 6 // tri3
    ),
    gsSPNTriangles_5b(
        8, 9, 6, // tri0
        8, 10, 9, // tri1
        10, 11, 9, // tri2
        10, 12, 11 // tri3
    ),
    gsSPNTriangles_5b(
        10, 13, 12, // tri0
        10, 14, 13, // tri1
        10, 15, 14, // tri2
        15, 16, 14 // tri3
    ),
    gsSPNTriangles_5b(
        16, 17, 14, // tri0
        17, 18, 14, // tri1
        18, 19, 14, // tri2
        19, 20, 14 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 14, // tri0
        21, 13, 14, // tri1
        18, 22, 19, // tri2
        18, 23, 22 // tri3
    ),
    gsSPNTriangles_5b(
        18, 24, 23, // tri0
        16, 25, 17, // tri1
        16, 26, 25, // tri2
        26, 27, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 28, 27, // tri0
        26, 29, 28, // tri1
        29, 30, 28, // tri2
        28, 31, 27 // tri3
    ),
    gsSPVertex(&grd_s_il_1_v[129], 10, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        5, 8, 7, // tri1
        8, 9, 7, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_il_1_v[139], 6, 0),
    gsSPNTrianglesInit_5b(
        4, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        0, 3, 4 // tri2
    ),
    gsSPNTriangles_5b(
        5, 0, 4, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_il_1_modelT[] = {
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
    gsSPVertex(&grd_s_il_1_v[177], 9, 0),
    gsSPNTrianglesInit_5b(
        8, // tri count
        0, 1, 2, // tri0
        3, 0, 2, // tri1
        4, 3, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 4, 2, // tri0
        6, 7, 4, // tri1
        7, 3, 4, // tri2
        7, 0, 3 // tri3
    ),
    gsSPNTriangles_5b(
        7, 8, 0, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_il_1_v[186], 24, 0),
    gsSPNTrianglesInit_5b(
        22, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        3, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        7, 3, 6, // tri0
        7, 6, 8, // tri1
        9, 7, 8, // tri2
        9, 8, 10 // tri3
    ),
    gsSPNTriangles_5b(
        10, 11, 12, // tri0
        9, 10, 12, // tri1
        13, 9, 12, // tri2
        13, 12, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 13, 14, // tri0
        15, 14, 0, // tri1
        16, 15, 0, // tri2
        16, 0, 2 // tri3
    ),
    gsSPNTriangles_5b(
        16, 2, 17, // tri0
        18, 16, 17, // tri1
        18, 17, 19, // tri2
        20, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        21, 20, 19, // tri0
        22, 23, 21, // tri1
        22, 21, 19, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
