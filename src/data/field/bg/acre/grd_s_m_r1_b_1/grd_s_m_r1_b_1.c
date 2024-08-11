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
extern u8 bridge_1_pal_dummy[];
extern u8 bridge_1_tex_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_m_r1_b_1_v[] = {
#include "assets/field/bg/grd_s_m_r1_b_1_v.inc"
};

extern Gfx grd_s_m_r1_b_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 32, 48, 144, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach2_tex_dummy2, G_IM_FMT_I, 32, 16, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_r1_b_1_v[163], 22, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 3, 5  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 3,   // tri0
                      7, 3, 6,   // tri1
                      9, 10, 11, // tri2
                      12, 9, 11  // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 9, // tri0
                      14, 10, 9, // tri1
                      9, 13, 15, // tri2
                      14, 9, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 2, 17,  // tri0
                      18, 10, 14, // tri1
                      17, 18, 14, // tri2
                      16, 17, 14  // tri3
                      ),
    gsSPNTriangles_5b(19, 5, 20, // tri0
                      0, 2, 16,  // tri1
                      20, 0, 16, // tri2
                      19, 20, 16 // tri3
                      ),
    gsSPNTriangles_5b(6, 5, 19,  // tri0
                      21, 7, 6,  // tri1
                      21, 6, 19, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bridge_1_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bridge_1_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_r1_b_1_v[151], 12, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 4, 5, // tri0
                      5, 4, 6, // tri1
                      5, 6, 7, // tri2
                      7, 6, 8  // tri3
                      ),
    gsSPNTriangles_5b(7, 8, 9,  // tri0
                      1, 10, 2, // tri1
                      6, 11, 8, // tri2
                      4, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(4, 11, 6, // tri0
                      2, 10, 4, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_b_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      10, 11, 6, // tri1
                      11, 4, 6,  // tri2
                      12, 13, 10 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      14, 15, 12, // tri1
                      12, 15, 13, // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 16, // tri0
                      16, 18, 15, // tri1
                      19, 20, 17, // tri2
                      21, 22, 19  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 21, // tri0
                      3, 25, 23,  // tri1
                      2, 26, 0,   // tri2
                      1, 25, 3    // tri3
                      ),
    gsSPNTriangles_5b(23, 25, 24, // tri0
                      21, 24, 22, // tri1
                      19, 22, 20, // tri2
                      17, 20, 18  // tri3
                      ),
    gsSPNTriangles_5b(7, 27, 28,  // tri0
                      28, 29, 30, // tri1
                      30, 29, 31, // tri2
                      9, 27, 7    // tri3
                      ),
    gsSPNTriangles_5b(28, 27, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_m_r1_b_1_v[32], 17, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 4,  // tri0
                      4, 6, 7,  // tri1
                      7, 8, 9,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      11, 10, 12, // tri1
                      9, 8, 10,   // tri2
                      6, 8, 7     // tri3
                      ),
    gsSPNTriangles_5b(4, 5, 6,    // tri0
                      12, 14, 13, // tri1
                      12, 15, 14, // tri2
                      15, 16, 14  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_b_1_v[49], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
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
                      16, 18, 21, // tri2
                      19, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(22, 24, 25, // tri0
                      19, 23, 20, // tri1
                      13, 15, 26, // tri2
                      27, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(28, 13, 26, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_m_r1_b_1_v[79], 15, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      4, 6, 9,   // tri1
                      7, 10, 11, // tri2
                      10, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 13, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_m_r1_b_1_v[94], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 4, // tri0
                      7, 8, 6, // tri1
                      6, 5, 7, // tri2
                      9, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 8,  // tri0
                      10, 9, 11, // tri1
                      9, 12, 11, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(13, 16, 14, // tri0
                      16, 17, 14, // tri1
                      18, 19, 17, // tri2
                      17, 19, 14  // tri3
                      ),
    gsSPNTriangles_5b(14, 19, 20, // tri0
                      19, 21, 20, // tri1
                      21, 22, 20, // tri2
                      23, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 22, // tri0
                      22, 24, 25, // tri1
                      23, 26, 27, // tri2
                      27, 26, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 26, // tri0
                      26, 31, 28, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_m_r1_b_1_v[126], 5, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 3, 1  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, beach_pal_dummy2),
    gsDPLoadTextureBlock_4b_Dolphin(sand_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_b_1_v[131], 10, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5, // tri0
                      3, 8, 9, // tri1
                      3, 1, 8, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 206, 189, 148, 255),
    gsSPDisplayList(0x0C000000),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(beach1_tex_dummy2, G_IM_FMT_I, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_m_r1_b_1_v[141], 10, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      7, 8, 6, // tri1
                      8, 9, 6, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_m_r1_b_1_modelT[] = {
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
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_m_r1_b_1_v[185], 15, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      6, 7, 8, // tri1
                      9, 6, 8, // tri2
                      10, 9, 8 // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 8, // tri0
                      12, 13, 9, // tri1
                      13, 6, 9,  // tri2
                      10, 14, 9  // tri3
                      ),
    gsSPNTriangles_5b(14, 12, 9, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave1_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, wave3_tex_dummy),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 0, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x0D000000),
    gsSPVertex(&grd_s_m_r1_b_1_v[200], 15, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 0, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 3, // tri0
                      5, 3, 6, // tri1
                      7, 5, 6, // tri2
                      8, 7, 6  // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 6,    // tri0
                      9, 6, 10,   // tri1
                      11, 12, 13, // tri2
                      14, 9, 10   // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 10, // tri0
                      11, 13, 10, // tri1
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
    gsSPVertex(&grd_s_m_r1_b_1_v[215], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      4, 6, 5, // tri1
                      4, 7, 6, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPSetCombineLERP(1, 0, PRIMITIVE, TEXEL0, TEXEL1, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, TEXEL1, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 100, 140, 255, 200),
    gsDPLoadTextureBlock_4b_Dolphin(sprashC_tex_dummy, G_IM_FMT_I, 32, 32, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsDPLoadMultiBlock_4b_Dolphin(sprashA_tex_dummy, 1, G_IM_FMT_I, 32, 32, 15, GX_MIRROR, GX_REPEAT, 0, 1),
    gsSPDisplayList(0x09000000),
    gsSPVertex(&grd_s_m_r1_b_1_v[223], 7, 0),
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
