#include "libforest/gbi_extensions.h"

extern u8 sprashC_tex_dummy[];
extern u8 sprashA_tex_dummy[];
extern u8 wave3_tex_dummy[];
extern u8 wave2_tex_dummy[];
extern u8 wave1_tex_dummy[];
extern u8 sand_tex_dummy[];
extern u8 beach_pal_dummy2[];
extern u8 beach2_tex_dummy2[];
extern u8 beach1_tex_dummy2[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_m_r1_1_v[] = {
#include "assets/field/bg/grd_s_m_r1_1_v.inc"
};

extern Gfx grd_s_m_r1_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_r1_1_v[164], 27, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4, // tri0
                      6, 7, 8, // tri1
                      6, 8, 9, // tri2
                      10, 6, 9 // tri3
                      ),
    gsSPNTriangles_5b(10, 9, 11,  // tri0
                      12, 11, 13, // tri1
                      11, 9, 13,  // tri2
                      9, 14, 13   // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 14,   // tri0
                      14, 15, 13, // tri1
                      14, 16, 15, // tri2
                      16, 0, 15   // tri3
                      ),
    gsSPNTriangles_5b(0, 17, 15, // tri0
                      16, 18, 0, // tri1
                      18, 19, 0, // tri2
                      0, 2, 17   // tri3
                      ),
    gsSPNTriangles_5b(2, 20, 17,  // tri0
                      2, 21, 20,  // tri1
                      18, 22, 19, // tri2
                      4, 23, 21   // tri3
                      ),
    gsSPNTriangles_5b(4, 21, 2,   // tri0
                      24, 25, 26, // tri1
                      26, 10, 11, // tri2
                      24, 26, 11  // tri3
                      ),
    gsSPNTriangles_5b(12, 24, 11, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_r1_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      6, 8, 7, // tri1
                      8, 2, 9, // tri2
                      2, 4, 9  // tri3
                      ),
    gsSPNTriangles_5b(8, 6, 2,   // tri0
                      3, 10, 4,  // tri1
                      3, 11, 10, // tri2
                      3, 12, 11  // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      12, 14, 13, // tri1
                      15, 14, 16, // tri2
                      12, 16, 14  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      19, 20, 17, // tri1
                      21, 20, 19, // tri2
                      21, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 22, // tri0
                      23, 24, 22, // tri1
                      24, 25, 22, // tri2
                      25, 26, 22  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 22, // tri0
                      28, 29, 30, // tri1
                      29, 31, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_m_r1_1_v[32], 16, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          2, 3, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      5, 8, 6, // tri1
                      5, 9, 8, // tri2
                      9, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 9,  // tri0
                      12, 10, 9,  // tri1
                      13, 10, 12, // tri2
                      13, 14, 10  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 10, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_1_v[48], 28, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 2, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 3,    // tri0
                      1, 9, 10,   // tri1
                      10, 11, 12, // tri2
                      12, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      18, 19, 15, // tri1
                      20, 21, 18, // tri2
                      22, 23, 20  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 22, // tri0
                      26, 27, 24, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_1_v[76], 18, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      6, 8, 7,   // tri1
                      2, 9, 0,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 10, // tri0
                      12, 14, 15, // tri1
                      15, 13, 12, // tri2
                      14, 16, 8   // tri3
                      ),
    gsSPNTriangles_5b(8, 15, 14, // tri0
                      16, 7, 8,  // tri1
                      5, 17, 6,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_1_v[94], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      5, 6, 4, // tri1
                      6, 7, 4, // tri2
                      6, 8, 9  // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 6,   // tri0
                      8, 10, 9,  // tri1
                      8, 11, 10, // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(13, 10, 11, // tri0
                      12, 14, 13, // tri1
                      15, 16, 17, // tri2
                      18, 19, 16  // tri3
                      ),
    gsSPNTriangles_5b(15, 18, 16, // tri0
                      18, 20, 19, // tri1
                      20, 21, 22, // tri2
                      18, 21, 20  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 22, // tri0
                      21, 23, 22, // tri1
                      23, 25, 24, // tri2
                      26, 27, 25  // tri3
                      ),
    gsSPNTriangles_5b(25, 23, 26, // tri0
                      28, 29, 27, // tri1
                      26, 28, 27, // tri2
                      30, 31, 29  // tri3
                      ),
    gsSPNTriangles_5b(28, 30, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_m_r1_1_v[126], 21, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      5, 8, 7, // tri1
                      3, 5, 4, // tri2
                      1, 0, 3  // tri3
                      ),
    gsSPNTriangles_5b(9, 0, 2,    // tri0
                      10, 11, 12, // tri1
                      12, 13, 14, // tri2
                      12, 15, 10  // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 15, // tri0
                      13, 16, 17, // tri1
                      16, 18, 17, // tri2
                      19, 20, 18  // tri3
                      ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_1_v[147], 17, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 3, 4, // tri0
                      6, 7, 8, // tri1
                      6, 8, 9, // tri2
                      10, 6, 9 // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 9,  // tri0
                      11, 9, 12,  // tri1
                      11, 12, 13, // tri2
                      14, 11, 13  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 14, // tri0
                      15, 14, 13, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_m_r1_1_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 1, 0, TEXEL0, TEXEL1, COMBINED, 0, SHADE, TEXEL0,
                       COMBINED, 0, PRIM_LOD_FRAC, PRIMITIVE),
    gsDPSetPrimColor(0, 50, 255, 255, 255, 50),
    gsDPSetEnvColor(0x00, 0x3C, 0xFF, 0xFF),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(water_1_tex_dummy, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPLoadMultiBlock_4b_Dolphin(water_2_tex_dummy, 1, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x08000000),
    gsSPVertex(&grd_s_m_r1_1_v[191], 12, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 3, 4, // tri0
                      6, 5, 4, // tri1
                      6, 4, 7, // tri2
                      8, 6, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 9,   // tri0
                      10, 8, 9,  // tri1
                      10, 9, 11, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetCombineLERP(TEXEL1, 0, TEXEL0, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, 0, SHADE, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 60, 120, 255, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, wave2_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPDisplayList(0x0B000000),
    gsSPVertex(&grd_s_m_r1_1_v[203], 24, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 3, 4, // tri0
                      6, 7, 8, // tri1
                      6, 8, 9, // tri2
                      10, 6, 9 // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 9,  // tri0
                      11, 9, 12,  // tri1
                      11, 12, 13, // tri2
                      14, 11, 13  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 14, // tri0
                      15, 14, 13, // tri1
                      1, 17, 2,   // tri2
                      2, 17, 18   // tri3
                      ),
    gsSPNTriangles_5b(4, 2, 18,   // tri0
                      18, 19, 4,  // tri1
                      13, 20, 15, // tri2
                      13, 21, 20  // tri3
                      ),
    gsSPNTriangles_5b(13, 12, 21, // tri0
                      12, 22, 21, // tri1
                      12, 9, 22,  // tri2
                      22, 8, 23   // tri3
                      ),
    gsSPNTriangles_5b(22, 9, 8, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_m_r1_1_v[227], 26, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 3, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 4, // tri0
                      6, 3, 4, // tri1
                      7, 6, 5, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 7,  // tri0
                      10, 8, 7,  // tri1
                      11, 10, 9, // tri2
                      12, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 10, // tri0
                      14, 13, 12, // tri1
                      15, 16, 17, // tri2
                      16, 13, 17  // tri3
                      ),
    gsSPNTriangles_5b(18, 16, 15, // tri0
                      18, 19, 16, // tri1
                      19, 20, 16, // tri2
                      21, 22, 18  // tri3
                      ),
    gsSPNTriangles_5b(22, 19, 18, // tri0
                      23, 22, 21, // tri1
                      24, 25, 23, // tri2
                      25, 22, 23  // tri3
                      ),
    gsDPSetCombineLERP(1, 0, PRIMITIVE, TEXEL0, TEXEL1, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, TEXEL1, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 100, 140, 255, 200),
    gsDPLoadTextureBlock_4b_Dolphin(sprashC_tex_dummy, G_IM_FMT_I, 32, 32, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPLoadMultiBlock_4b_Dolphin(sprashA_tex_dummy, 1, G_IM_FMT_I, 32, 32, 15, GX_MIRROR, GX_REPEAT, 0, 1),
    gsSPDisplayList(0x09000000),
    gsSPVertex(&grd_s_m_r1_1_v[253], 7, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 2, // tri0
                      1, 6, 4, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};
