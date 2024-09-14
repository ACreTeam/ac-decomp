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

static Vtx grd_s_m_r1_4_v[] = {
#include "assets/field/bg/grd_s_m_r1_4_v.inc"
};

extern Gfx grd_s_m_r1_4_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_r1_4_v[187], 24, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      3, 6, 5, // tri1
                      3, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,   // tri0
                      7, 10, 9,  // tri1
                      10, 11, 9, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      11, 14, 9,  // tri1
                      5, 15, 4,   // tri2
                      11, 13, 16  // tri3
                      ),
    gsSPNTriangles_5b(11, 16, 17, // tri0
                      11, 17, 18, // tri1
                      14, 11, 18, // tri2
                      14, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(14, 19, 20, // tri0
                      9, 14, 20,  // tri1
                      21, 22, 23, // tri2
                      21, 0, 22   // tri3
                      ),
    gsSPNTriangles_5b(0, 2, 22, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_r1_4_v[0], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          2, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 3, // tri0
                      3, 6, 2, // tri1
                      5, 7, 6, // tri2
                      8, 6, 7  // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 7,   // tri0
                      9, 10, 8,  // tri1
                      10, 11, 8, // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 8,  // tri0
                      12, 14, 13, // tri1
                      15, 14, 12, // tri2
                      16, 17, 15  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 15, // tri0
                      18, 14, 15, // tri1
                      16, 19, 20, // tri2
                      20, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 19, // tri0
                      22, 20, 19, // tri1
                      23, 24, 25, // tri2
                      4, 26, 0    // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 25, // tri0
                      25, 24, 27, // tri1
                      27, 29, 28, // tri2
                      30, 31, 29  // tri3
                      ),
    gsSPNTriangles_5b(29, 27, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_m_r1_4_v[32], 19, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(0, 3, 1, // tri0
                      4, 3, 5, // tri1
                      6, 7, 8, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 12, // tri0
                      12, 13, 14, // tri1
                      14, 15, 16, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 16, 15, // tri0
                      15, 14, 13, // tri1
                      12, 11, 13, // tri2
                      9, 11, 10   // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 9, // tri0
                      6, 5, 7, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_4_v[51], 16, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      8, 5, 4, // tri1
                      8, 9, 5, // tri2
                      8, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 12, // tri0
                      10, 13, 9,  // tri1
                      10, 12, 13, // tri2
                      11, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 12, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_4_v[67], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 8,   // tri0
                      9, 5, 10,  // tri1
                      11, 9, 12, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 17, // tri0
                      18, 19, 20, // tri1
                      16, 21, 22, // tri2
                      19, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(23, 25, 26, // tri0
                      19, 24, 20, // tri1
                      16, 22, 17, // tri2
                      27, 13, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 27, 30, // tri0
                      30, 31, 29, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_m_r1_4_v[99], 23, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          3, 1, 0, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 8,   // tri0
                      9, 10, 11, // tri1
                      7, 9, 12,  // tri2
                      10, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 16, // tri0
                      15, 17, 16, // tri1
                      18, 19, 20, // tri2
                      19, 4, 20   // tri3
                      ),
    gsSPNTriangles_5b(21, 3, 22, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_m_r1_4_v[122], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          3, 1, 0, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      4, 5, 6, // tri1
                      6, 5, 7, // tri2
                      8, 7, 5  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 7,    // tri0
                      10, 11, 12, // tri1
                      11, 13, 12, // tri2
                      12, 3, 0    // tri3
                      ),
    gsSPNTriangles_5b(13, 3, 12,  // tri0
                      10, 14, 11, // tri1
                      15, 14, 10, // tri2
                      16, 17, 15  // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 14, // tri0
                      18, 19, 20, // tri1
                      21, 22, 19, // tri2
                      23, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(24, 26, 25, // tri0
                      26, 27, 25, // tri1
                      27, 28, 25, // tri2
                      29, 25, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 25, // tri0
                      31, 20, 22, // tri1
                      20, 19, 22, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_m_r1_4_v[154], 18, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 3,  // tri0
                      6, 7, 8,  // tri1
                      8, 7, 9,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 12, // tri0
                      10, 13, 12, // tri1
                      12, 13, 14, // tri2
                      13, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 14, // tri0
                      16, 17, 14, // tri1
                      5, 6, 8,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_4_v[172], 15, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          4, 3, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 2, 5, // tri0
                      4, 5, 6, // tri1
                      7, 4, 6, // tri2
                      7, 6, 8  // tri3
                      ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 7, 9,   // tri1
                      11, 12, 13, // tri2
                      14, 11, 13  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_m_r1_4_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL1, 0, TEXEL0, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, 0, SHADE, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 60, 120, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, wave2_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPDisplayList(0x0B000000),
    gsSPVertex(&grd_s_m_r1_4_v[211], 21, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          4, 3, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 2, // tri0
                      5, 2, 6, // tri1
                      5, 6, 7, // tri2
                      5, 7, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      12, 9, 11,  // tri1
                      13, 12, 14, // tri2
                      12, 11, 14  // tri3
                      ),
    gsSPNTriangles_5b(0, 3, 15,  // tri0
                      3, 16, 15, // tri1
                      3, 17, 16, // tri2
                      3, 4, 17   // tri3
                      ),
    gsSPNTriangles_5b(4, 18, 17, // tri0
                      4, 19, 18, // tri1
                      4, 5, 19,  // tri2
                      5, 8, 19   // tri3
                      ),
    gsSPNTriangles_5b(8, 20, 19, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_m_r1_4_v[232], 24, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 2, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 2, 4, // tri0
                      5, 6, 2, // tri1
                      7, 8, 5, // tri2
                      8, 6, 5  // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 7,   // tri0
                      9, 10, 8,  // tri1
                      11, 10, 9, // tri2
                      12, 13, 11 // tri3
                      ),
    gsSPNTriangles_5b(13, 10, 11, // tri0
                      14, 13, 12, // tri1
                      15, 13, 14, // tri2
                      15, 16, 13  // tri3
                      ),
    gsSPNTriangles_5b(17, 16, 15, // tri0
                      17, 18, 16, // tri1
                      19, 20, 17, // tri2
                      20, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(21, 20, 19, // tri0
                      22, 20, 21, // tri1
                      22, 23, 20, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 1, 0, TEXEL0, TEXEL1, COMBINED, 0, SHADE, TEXEL0,
                       COMBINED, 0, PRIM_LOD_FRAC, PRIMITIVE),
    gsDPSetPrimColor(0, 50, 255, 255, 255, 50),
    gsDPSetEnvColor(0x00, 0x3C, 0xFF, 0xFF),
    gsDPLoadTextureBlock_4b_Dolphin(water_1_tex_dummy, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPLoadMultiBlock_4b_Dolphin(water_2_tex_dummy, 1, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x08000000),
    gsSPVertex(&grd_s_m_r1_4_v[256], 13, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      4, 6, 5, // tri1
                      4, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,   // tri0
                      7, 10, 9,  // tri1
                      10, 11, 9, // tri2
                      11, 12, 9  // tri3
                      ),
    gsDPSetCombineLERP(1, 0, PRIMITIVE, TEXEL0, TEXEL1, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, TEXEL1, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 100, 140, 255, 200),
    gsDPLoadTextureBlock_4b_Dolphin(sprashC_tex_dummy, G_IM_FMT_I, 32, 32, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPLoadMultiBlock_4b_Dolphin(sprashA_tex_dummy, 1, G_IM_FMT_I, 32, 32, 15, GX_MIRROR, GX_REPEAT, 0, 1),
    gsSPDisplayList(0x09000000),
    gsSPVertex(&grd_s_m_r1_4_v[269], 7, 0),
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
