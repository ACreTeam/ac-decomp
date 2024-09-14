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

static Vtx grd_s_m_r1_2_v[] = {
#include "assets/field/bg/grd_s_m_r1_2_v.inc"
};

extern Gfx grd_s_m_r1_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_r1_2_v[166], 24, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 2, // tri0
                      5, 6, 2, // tri1
                      5, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 6,   // tri0
                      9, 10, 6,  // tri1
                      9, 11, 10, // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      7, 14, 8,   // tri1
                      3, 15, 1,   // tri2
                      15, 16, 1   // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 1, // tri0
                      17, 4, 1,  // tri1
                      17, 5, 4,  // tri2
                      17, 18, 5  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 18, // tri0
                      20, 21, 22, // tri1
                      21, 11, 22, // tri2
                      11, 9, 22   // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 11, // tri0
                      23, 13, 11, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_r1_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 9,    // tri0
                      6, 10, 7,   // tri1
                      11, 12, 13, // tri2
                      14, 15, 12  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 13, // tri0
                      17, 11, 13, // tri1
                      8, 18, 6,   // tri2
                      19, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 21, 18, // tri0
                      23, 24, 25, // tri1
                      26, 27, 28, // tri2
                      27, 29, 28  // tri3
                      ),
    gsSPNTriangles_5b(14, 12, 11, // tri0
                      4, 1, 5,    // tri1
                      20, 19, 30, // tri2
                      26, 28, 31  // tri3
                      ),
    gsSPVertex(&grd_s_m_r1_2_v[32], 32, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 11, 12, // tri1
                      13, 14, 15, // tri2
                      4, 6, 16    // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      6, 5, 20,   // tri1
                      21, 22, 23, // tri2
                      14, 24, 17  // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 19, // tri0
                      7, 9, 25,   // tri1
                      26, 25, 27, // tri2
                      24, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 28, // tri0
                      29, 30, 31, // tri1
                      28, 11, 10, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_2_v[64], 16, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          2, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      7, 8, 9,  // tri1
                      10, 9, 8, // tri2
                      11, 5, 7  // tri3
                      ),
    gsSPNTriangles_5b(10, 8, 12, // tri0
                      5, 13, 6,  // tri1
                      9, 11, 7,  // tri2
                      14, 2, 15  // tri3
                      ),
    gsSPNTriangles_5b(14, 4, 2, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_m_r1_2_v[80], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,  // tri0
                      5, 8, 7,  // tri1
                      5, 9, 8,  // tri2
                      10, 5, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 9, 5,  // tri0
                      5, 4, 11,  // tri1
                      12, 13, 7, // tri2
                      13, 6, 7   // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      17, 13, 12, // tri1
                      18, 19, 20, // tri2
                      11, 18, 10  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 18, // tri0
                      21, 23, 22, // tri1
                      11, 21, 18, // tri2
                      18, 20, 10  // tri3
                      ),
    gsSPNTriangles_5b(17, 24, 13, // tri0
                      25, 26, 27, // tri1
                      28, 14, 29, // tri2
                      14, 16, 29  // tri3
                      ),
    gsSPNTriangles_5b(16, 30, 29, // tri0
                      30, 31, 29, // tri1
                      25, 27, 15, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_m_r1_2_v[112], 20, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      5, 6, 3, // tri1
                      5, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(4, 9, 5,    // tri0
                      10, 11, 12, // tri1
                      13, 14, 15, // tri2
                      13, 16, 14  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 14, // tri0
                      15, 18, 19, // tri1
                      18, 8, 19,  // tri2
                      8, 7, 19    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_2_v[132], 19, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(2, 5, 6,   // tri0
                      7, 8, 9,   // tri1
                      9, 10, 3,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      13, 15, 14, // tri1
                      14, 16, 7,  // tri2
                      17, 18, 11  // tri3
                      ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_2_v[151], 15, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4, // tri0
                      5, 6, 4, // tri1
                      6, 7, 4, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 10,  // tri0
                      9, 12, 11,  // tri1
                      12, 13, 11, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_m_r1_2_modelT[] = {
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
    gsSPVertex(&grd_s_m_r1_2_v[190], 22, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4, // tri0
                      5, 6, 4, // tri1
                      6, 7, 4, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 10,  // tri0
                      9, 12, 11,  // tri1
                      12, 13, 11, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 11, // tri0
                      15, 16, 11, // tri1
                      16, 17, 11, // tri2
                      17, 10, 11  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 7, // tri0
                      19, 4, 7,  // tri1
                      19, 2, 4,  // tri2
                      19, 20, 2  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 2, // tri0
                      21, 0, 2,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_m_r1_2_v[212], 25, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 4, // tri0
                      6, 2, 4, // tri1
                      6, 7, 2, // tri2
                      8, 6, 5  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 8,  // tri0
                      10, 6, 8,  // tri1
                      11, 12, 9, // tri2
                      12, 10, 9  // tri3
                      ),
    gsSPNTriangles_5b(13, 12, 11, // tri0
                      13, 14, 12, // tri1
                      15, 14, 13, // tri2
                      16, 17, 15  // tri3
                      ),
    gsSPNTriangles_5b(17, 14, 15, // tri0
                      18, 19, 16, // tri1
                      19, 17, 16, // tri2
                      20, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 19, // tri0
                      22, 21, 20, // tri1
                      23, 21, 22, // tri2
                      23, 24, 21  // tri3
                      ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 1, 0, TEXEL0, TEXEL1, COMBINED, 0, SHADE, TEXEL0,
                       COMBINED, 0, PRIM_LOD_FRAC, PRIMITIVE),
    gsDPSetPrimColor(0, 50, 255, 255, 255, 50),
    gsDPSetEnvColor(0x00, 0x3C, 0xFF, 0xFF),
    gsDPLoadTextureBlock_4b_Dolphin(water_1_tex_dummy, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPLoadMultiBlock_4b_Dolphin(water_2_tex_dummy, 1, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x08000000),
    gsSPVertex(&grd_s_m_r1_2_v[237], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 0, 6  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 6, // tri0
                      7, 6, 8, // tri1
                      7, 5, 6, // tri2
                      0, 3, 1  // tri3
                      ),
    gsDPSetCombineLERP(1, 0, PRIMITIVE, TEXEL0, TEXEL1, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, TEXEL1, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 100, 140, 255, 200),
    gsDPLoadTextureBlock_4b_Dolphin(sprashC_tex_dummy, G_IM_FMT_I, 32, 32, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPLoadMultiBlock_4b_Dolphin(sprashA_tex_dummy, 1, G_IM_FMT_I, 32, 32, 15, GX_MIRROR, GX_REPEAT, 0, 1),
    gsSPDisplayList(0x09000000),
    gsSPVertex(&grd_s_m_r1_2_v[246], 7, 0),
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
