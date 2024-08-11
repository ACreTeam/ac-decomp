#include "libforest/gbi_extensions.h"

extern u8 wave3_tex_dummy[];
extern u8 wave2_tex_dummy[];
extern u8 wave1_tex_dummy[];
extern u8 beach2_tex_dummy2[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];

static Vtx grd_s_e3_m_1_v[] = {
#include "assets/field/bg/grd_s_e3_m_1_v.inc"
};

extern Gfx grd_s_e3_m_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_e3_m_1_v[106], 7, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        0, 4, 1 // tri2
    ),
    gsSPNTriangles_5b(
        5, 3, 6, // tri0
        3, 1, 6, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_e3_m_1_v[0], 14, 0),
    gsSPNTrianglesInit_5b(
        9, // tri count
        0, 1, 2, // tri0
        2, 3, 4, // tri1
        5, 6, 7 // tri2
    ),
    gsSPNTriangles_5b(
        5, 7, 8, // tri0
        9, 5, 8, // tri1
        10, 9, 8, // tri2
        11, 10, 8 // tri3
    ),
    gsSPNTriangles_5b(
        11, 8, 12, // tri0
        11, 12, 13, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_e3_m_1_v[14], 9, 0),
    gsSPNTrianglesInit_5b(
        7, // tri count
        0, 1, 2, // tri0
        0, 3, 1, // tri1
        4, 5, 1 // tri2
    ),
    gsSPNTriangles_5b(
        3, 4, 1, // tri0
        6, 7, 5, // tri1
        5, 4, 6, // tri2
        6, 8, 7 // tri3
    ),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_e3_m_1_v[23], 32, 0),
    gsSPNTrianglesInit_5b(
        26, // tri count
        0, 1, 2, // tri0
        1, 3, 2, // tri1
        4, 0, 5 // tri2
    ),
    gsSPNTriangles_5b(
        0, 2, 5, // tri0
        4, 5, 6, // tri1
        7, 4, 6, // tri2
        7, 6, 8 // tri3
    ),
    gsSPNTriangles_5b(
        9, 7, 8, // tri0
        9, 8, 10, // tri1
        11, 12, 13, // tri2
        14, 11, 13 // tri3
    ),
    gsSPNTriangles_5b(
        14, 13, 15, // tri0
        14, 15, 16, // tri1
        17, 14, 16, // tri2
        18, 17, 16 // tri3
    ),
    gsSPNTriangles_5b(
        19, 20, 21, // tri0
        19, 21, 22, // tri1
        23, 19, 22, // tri2
        23, 22, 24 // tri3
    ),
    gsSPNTriangles_5b(
        25, 23, 24, // tri0
        25, 24, 26, // tri1
        27, 25, 26, // tri2
        27, 26, 28 // tri3
    ),
    gsSPNTriangles_5b(
        29, 28, 30, // tri0
        29, 27, 28, // tri1
        29, 30, 31, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_e3_m_1_v[55], 32, 0),
    gsSPNTrianglesInit_5b(
        32, // tri count
        0, 1, 2, // tri0
        0, 2, 3, // tri1
        3, 4, 5 // tri2
    ),
    gsSPNTriangles_5b(
        0, 3, 5, // tri0
        6, 7, 8, // tri1
        6, 8, 9, // tri2
        10, 6, 9 // tri3
    ),
    gsSPNTriangles_5b(
        10, 9, 11, // tri0
        12, 10, 11, // tri1
        12, 11, 13, // tri2
        14, 12, 13 // tri3
    ),
    gsSPNTriangles_5b(
        15, 14, 13, // tri0
        15, 13, 16, // tri1
        2, 15, 16, // tri2
        2, 16, 17 // tri3
    ),
    gsSPNTriangles_5b(
        3, 2, 17, // tri0
        3, 17, 18, // tri1
        4, 3, 18, // tri2
        19, 20, 21 // tri3
    ),
    gsSPNTriangles_5b(
        22, 19, 21, // tri0
        22, 21, 23, // tri1
        24, 22, 23, // tri2
        25, 24, 23 // tri3
    ),
    gsSPNTriangles_5b(
        25, 23, 26, // tri0
        27, 25, 26, // tri1
        28, 27, 26, // tri2
        28, 26, 1 // tri3
    ),
    gsSPNTriangles_5b(
        29, 28, 1, // tri0
        29, 1, 0, // tri1
        30, 31, 29, // tri2
        30, 29, 0 // tri3
    ),
    gsSPNTriangles_5b(
        30, 0, 5, // tri0
        0, 0, 0, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPVertex(&grd_s_e3_m_1_v[87], 11, 0),
    gsSPNTrianglesInit_5b(
        5, // tri count
        0, 1, 2, // tri0
        3, 4, 5, // tri1
        6, 3, 5 // tri2
    ),
    gsSPNTriangles_5b(
        7, 8, 9, // tri0
        10, 7, 9, // tri1
        0, 0, 0, // tri2
        0, 0, 0 // tri3
    ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_e3_m_1_modelT[] = {
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
    gsSPVertex(&grd_s_e3_m_1_v[98], 3, 0),
    gsSPNTrianglesInit_5b(
        1, // tri count
        0, 1, 2, // tri0
        0, 0, 0, // tri1
        0, 0, 0 // tri2
    ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_e3_m_1_v[101], 5, 0),
    gsSPNTrianglesInit_5b(
        3, // tri count
        0, 1, 2, // tri0
        2, 1, 3, // tri1
        3, 4, 2 // tri2
    ),
    gsSPEndDisplayList(),
};
