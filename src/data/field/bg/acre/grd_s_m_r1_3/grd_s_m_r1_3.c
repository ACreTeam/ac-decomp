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

static Vtx grd_s_m_r1_3_v[] = {
#include "assets/field/bg/grd_s_m_r1_3_v.inc"
};

extern Gfx grd_s_m_r1_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_r1_3_v[146], 24, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 2, // tri0
                      4, 6, 5, // tri1
                      4, 7, 6, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 10, // tri0
                      9, 12, 11, // tri1
                      3, 13, 1,  // tri2
                      13, 14, 1  // tri3
                      ),
    gsSPNTriangles_5b(14, 4, 1,  // tri0
                      14, 7, 4,  // tri1
                      14, 15, 7, // tri2
                      15, 16, 7  // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 16, // tri0
                      15, 18, 17, // tri1
                      15, 19, 18, // tri2
                      19, 20, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 21, 20, // tri0
                      19, 8, 21,  // tri1
                      19, 22, 8,  // tri2
                      22, 9, 8    // tri3
                      ),
    gsSPNTriangles_5b(22, 12, 9,  // tri0
                      18, 23, 17, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_r1_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 7, // tri0
                      8, 7, 6, // tri1
                      6, 2, 1, // tri2
                      5, 10, 3 // tri3
                      ),
    gsSPNTriangles_5b(5, 11, 10,  // tri0
                      11, 12, 13, // tri1
                      14, 13, 12, // tri2
                      12, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 16,   // tri0
                      17, 18, 16, // tri1
                      8, 17, 16,  // tri2
                      15, 19, 14  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 19, // tri0
                      21, 14, 19, // tri1
                      22, 23, 20, // tri2
                      24, 25, 22  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 24, // tri0
                      28, 29, 26, // tri1
                      28, 30, 29, // tri2
                      28, 31, 30  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 21, // tri0
                      22, 25, 23, // tri1
                      24, 27, 25, // tri2
                      26, 29, 27  // tri3
                      ),
    gsSPVertex(&grd_s_m_r1_3_v[32], 13, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      9, 10, 8,  // tri1
                      10, 11, 8, // tri2
                      8, 7, 9    // tri3
                      ),
    gsSPNTriangles_5b(6, 5, 7, // tri0
                      5, 4, 3, // tri1
                      2, 1, 3, // tri2
                      0, 12, 1 // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_3_v[45], 13, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      6, 8, 9, // tri1
                      6, 7, 8, // tri2
                      8, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(8, 11, 10,  // tri0
                      11, 12, 10, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_3_v[58], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(5, 9, 3,   // tri0
                      10, 2, 9,  // tri1
                      4, 3, 11,  // tri2
                      12, 11, 13 // tri3
                      ),
    gsSPNTriangles_5b(8, 14, 6,   // tri0
                      15, 13, 14, // tri1
                      7, 6, 16,   // tri2
                      17, 16, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      22, 21, 23, // tri1
                      24, 23, 25, // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 25, 27, // tri0
                      30, 28, 31, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_m_r1_3_v[90], 3, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_m_r1_3_v[93], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          2, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 4, 2, // tri0
                      1, 0, 6, // tri1
                      0, 7, 6, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(0, 3, 10,  // tri0
                      10, 9, 0,  // tri1
                      10, 3, 11, // tri2
                      5, 12, 13  // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 13, // tri0
                      14, 15, 13, // tri1
                      14, 16, 15, // tri2
                      16, 17, 15  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 15, // tri0
                      15, 18, 19, // tri1
                      20, 21, 22, // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(22, 21, 23, // tri0
                      25, 26, 20, // tri1
                      27, 26, 25, // tri2
                      27, 28, 26  // tri3
                      ),
    gsSPNTriangles_5b(27, 29, 28, // tri0
                      29, 30, 28, // tri1
                      31, 30, 29, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_m_r1_3_v[125], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 1, 0, // tri1
                          4, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(2, 4, 5, // tri0
                      4, 6, 5, // tri1
                      7, 5, 6, // tri2
                      5, 7, 8  // tri3
                      ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_3_v[134], 12, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      5, 6, 4, // tri1
                      5, 7, 6, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(8, 11, 9, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_m_r1_3_modelT[] = {
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
    gsSPVertex(&grd_s_m_r1_3_v[170], 18, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7, // tri0
                      8, 4, 7, // tri1
                      8, 7, 9, // tri2
                      10, 8, 9 // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 9, // tri0
                      10, 12, 8, // tri1
                      12, 13, 8, // tri2
                      13, 4, 8   // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 4, // tri0
                      14, 5, 4,  // tri1
                      14, 15, 5, // tri2
                      1, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(1, 0, 16, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_m_r1_3_v[188], 27, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 3, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 4, // tri0
                      6, 3, 4, // tri1
                      7, 6, 5, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 7,   // tri0
                      9, 10, 8,  // tri1
                      11, 10, 9, // tri2
                      12, 13, 11 // tri3
                      ),
    gsSPNTriangles_5b(13, 10, 11, // tri0
                      14, 13, 12, // tri1
                      14, 15, 13, // tri2
                      16, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 15, // tri0
                      18, 17, 16, // tri1
                      19, 20, 21, // tri2
                      20, 17, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 20, 19, // tri0
                      22, 23, 20, // tri1
                      24, 23, 22, // tri2
                      25, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 23, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 1, 0, TEXEL0, TEXEL1, COMBINED, 0, SHADE, TEXEL0,
                       COMBINED, 0, PRIM_LOD_FRAC, PRIMITIVE),
    gsDPSetPrimColor(0, 50, 255, 255, 255, 50),
    gsDPSetEnvColor(0x00, 0x3C, 0xFF, 0xFF),
    gsDPLoadTextureBlock_4b_Dolphin(water_1_tex_dummy, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPLoadMultiBlock_4b_Dolphin(water_2_tex_dummy, 1, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x08000000),
    gsSPVertex(&grd_s_m_r1_3_v[215], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 0, 5  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 5, // tri0
                      6, 4, 7, // tri1
                      4, 5, 7, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPSetCombineLERP(1, 0, PRIMITIVE, TEXEL0, TEXEL1, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, TEXEL1, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 100, 140, 255, 200),
    gsDPLoadTextureBlock_4b_Dolphin(sprashC_tex_dummy, G_IM_FMT_I, 32, 32, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPLoadMultiBlock_4b_Dolphin(sprashA_tex_dummy, 1, G_IM_FMT_I, 32, 32, 15, GX_MIRROR, GX_REPEAT, 0, 1),
    gsSPDisplayList(0x09000000),
    gsSPVertex(&grd_s_m_r1_3_v[223], 7, 0),
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
