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

static Vtx grd_s_il_3_v[] = {
#include "assets/field/bg/grd_s_il_3_v.inc"
};

extern Gfx grd_s_il_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_il_3_v[142], 32, 0),
    gsSPNTrianglesInit_5b(
        28, // tri count
        0, 1, 2, // tri0
        3, 2, 4, // tri1
        3, 5, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 0, 2, // tri0
        6, 4, 7, // tri1
        6, 3, 4, // tri2
        8, 6, 7 // tri3
    ),
    gsSPNTriangles_5b(
        1, 9, 2, // tri0
        0, 10, 1, // tri1
        11, 12, 13, // tri2
        14, 15, 16 // tri3
    ),
    gsSPNTriangles_5b(
        15, 17, 16, // tri0
        15, 18, 17, // tri1
        18, 19, 17, // tri2
        18, 20, 19 // tri3
    ),
    gsSPNTriangles_5b(
        18, 21, 20, // tri0
        21, 11, 20, // tri1
        21, 12, 11, // tri2
        12, 22, 13 // tri3
    ),
    gsSPNTriangles_5b(
        22, 23, 13, // tri0
        23, 24, 13, // tri1
        23, 25, 24, // tri2
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
    gsSPVertex(&grd_s_il_3_v[174], 8, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        1, 4, 3 // tri2
    ),
    gsSPNTriangles_5b(
        1, 5, 4, // tri0
        5, 6, 4, // tri1
        5, 7, 6, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_il_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(
        28, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 5 // tri2
    ),
    gsSPNTriangles_5b(
        6, 5, 7, // tri0
        6, 7, 8, // tri1
        9, 6, 8, // tri2
        9, 8, 10 // tri3
    ),
    gsSPNTriangles_5b(
        11, 9, 10, // tri0
        11, 10, 12, // tri1
        13, 11, 12, // tri2
        13, 12, 14 // tri3
    ),
    gsSPNTriangles_5b(
        15, 13, 14, // tri0
        15, 14, 16, // tri1
        15, 16, 17, // tri2
        18, 15, 17 // tri3
    ),
    gsSPNTriangles_5b(
        18, 17, 19, // tri0
        18, 19, 20, // tri1
        21, 18, 20, // tri2
        21, 20, 22 // tri3
    ),
    gsSPNTriangles_5b(
        21, 22, 23, // tri0
        24, 21, 23, // tri1
        24, 23, 25, // tri2
        26, 24, 25 // tri3
    ),
    gsSPNTriangles_5b(
        26, 25, 27, // tri0
        28, 26, 27, // tri1
        28, 27, 29, // tri2
        28, 29, 30 // tri3
    ),
    gsSPNTriangles_5b(
        31, 28, 30, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_il_3_v[32], 13, 0),
    gsSPNTrianglesInit_5b(
        9, // tri count
        0, 1, 2, // tri0
        3, 0, 2, // tri1
        3, 2, 4 // tri2
    ),
    gsSPNTriangles_5b(
        3, 4, 5, // tri0
        6, 3, 5, // tri1
        7, 8, 9, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        8, 10, 12, // tri0
        8, 12, 9, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_il_3_v[45], 13, 0),
    gsSPNTrianglesInit_5b(
        11, // tri count
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
        11, 12, 9 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_il_3_v[58], 30, 0),
    gsSPNTrianglesInit_5b(
        16, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        4, 5, 6, // tri0
        7, 8, 9, // tri1
        7, 10, 8, // tri2
        10, 11, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 14, 0, // tri0
        15, 16, 13, // tri1
        7, 9, 15, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 17, 21, // tri0
        22, 23, 24, // tri1
        25, 22, 26, // tri2
        18, 27, 28 // tri3
    ),
    gsSPNTriangles_5b(
        27, 25, 29, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_il_3_v[88], 32, 0),
    gsSPNTrianglesInit_5b(
        31, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 5, 6 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 6, // tri0
        5, 8, 7, // tri1
        8, 9, 7, // tri2
        9, 10, 7 // tri3
    ),
    gsSPNTriangles_5b(
        8, 11, 9, // tri0
        8, 12, 11, // tri1
        8, 13, 12, // tri2
        13, 14, 12 // tri3
    ),
    gsSPNTriangles_5b(
        13, 15, 14, // tri0
        15, 16, 14, // tri1
        15, 2, 16, // tri2
        15, 0, 2 // tri3
    ),
    gsSPNTriangles_5b(
        0, 17, 1, // tri0
        15, 18, 0, // tri1
        18, 19, 0, // tri2
        19, 20, 0 // tri3
    ),
    gsSPNTriangles_5b(
        20, 21, 0, // tri0
        21, 22, 0, // tri1
        22, 17, 0, // tri2
        18, 23, 19 // tri3
    ),
    gsSPNTriangles_5b(
        18, 24, 23, // tri0
        3, 25, 2, // tri1
        3, 26, 25, // tri2
        25, 27, 2 // tri3
    ),
    gsSPNTriangles_5b(
        27, 28, 2, // tri0
        27, 29, 28, // tri1
        26, 30, 25, // tri2
        30, 31, 25 // tri3
    ),
    gsSPVertex(&grd_s_il_3_v[120], 10, 0),
    gsSPNTrianglesInit_5b(
        6, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        3, 4, 2 // tri2
    ),
    gsSPNTriangles_5b(
        5, 6, 7, // tri0
        6, 8, 7, // tri1
        6, 9, 8, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_il_3_v[130], 12, 0),
    gsSPNTrianglesInit_5b(
        10, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        3, 5, 4, // tri0
        5, 6, 4, // tri1
        0, 2, 7, // tri2
        8, 9, 7 // tri3
    ),
    gsSPNTriangles_5b(
        10, 0, 7, // tri0
        5, 11, 6, // tri1
        9, 10, 7, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_il_3_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL1, 0, TEXEL0, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, 0, SHADE, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 60, 120, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, wave2_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPDisplayList(0x0B000000),
    gsSPVertex(&grd_s_il_3_v[182], 17, 0),
    gsSPNTrianglesInit_5b(
        19, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 1, 4, // tri0
        5, 6, 1, // tri1
        6, 2, 1, // tri2
        6, 7, 2 // tri3
    ),
    gsSPNTriangles_5b(
        8, 0, 9, // tri0
        0, 2, 9, // tri1
        7, 9, 2, // tri2
        7, 10, 9 // tri3
    ),
    gsSPNTriangles_5b(
        11, 4, 12, // tri0
        4, 3, 12, // tri1
        5, 4, 11, // tri2
        13, 5, 11 // tri3
    ),
    gsSPNTriangles_5b(
        14, 11, 12, // tri0
        14, 15, 11, // tri1
        15, 16, 11, // tri2
        16, 13, 11 // tri3
    ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_il_3_v[199], 28, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        3, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        3, 0, 4, // tri0
        4, 6, 5, // tri1
        6, 7, 5, // tri2
        7, 8, 5 // tri3
    ),
    gsSPNTriangles_5b(
        9, 10, 11, // tri0
        9, 11, 12, // tri1
        13, 9, 12, // tri2
        14, 13, 12 // tri3
    ),
    gsSPNTriangles_5b(
        14, 12, 15, // tri0
        16, 14, 15, // tri1
        16, 15, 17, // tri2
        17, 18, 19 // tri3
    ),
    gsSPNTriangles_5b(
        20, 16, 17, // tri0
        20, 17, 19, // tri1
        20, 19, 21, // tri2
        22, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        23, 22, 21, // tri0
        23, 21, 24, // tri1
        25, 23, 24, // tri2
        25, 24, 26 // tri3
    ),
    gsSPNTriangles_5b(
        25, 26, 27, // tri0
        8, 25, 27, // tri1
        8, 27, 5, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};
