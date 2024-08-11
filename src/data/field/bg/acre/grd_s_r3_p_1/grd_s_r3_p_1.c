#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 bridge_2_pal_dummy[];
extern u8 bridge_2_tex_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_r3_p_1_v[] = {
#include "assets/field/bg/grd_s_r3_p_1_v.inc"
};

extern Gfx grd_s_r3_p_1_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 1, 0, TEXEL0, TEXEL1, COMBINED, 0, SHADE, TEXEL0,
                       COMBINED, 0, PRIM_LOD_FRAC, PRIMITIVE),
    gsDPSetPrimColor(0, 50, 255, 255, 255, 50),
    gsDPSetEnvColor(0x00, 0x64, 0xFF, 0xFF),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(water_1_tex_dummy, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPLoadMultiBlock_4b_Dolphin(water_2_tex_dummy, 1, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x08000000),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r3_p_1_v[292], 19, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 0, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 4, // tri0
                      5, 4, 7, // tri1
                      8, 5, 7, // tri2
                      9, 8, 10 // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11, // tri0
                      12, 13, 9, // tri1
                      12, 9, 11, // tri2
                      14, 6, 5   // tri3
                      ),
    gsSPNTriangles_5b(15, 14, 5, // tri0
                      8, 7, 10,  // tri1
                      7, 16, 10, // tri2
                      8, 17, 15  // tri3
                      ),
    gsSPNTriangles_5b(5, 8, 15,  // tri0
                      18, 16, 7, // tri1
                      18, 7, 4,  // tri2
                      3, 18, 4   // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r3_p_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bridge_2_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bridge_2_tex_dummy, G_IM_FMT_CI, 128, 32, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r3_p_1_v[254], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          2, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(2, 3, 4, // tri0
                      3, 6, 4, // tri1
                      6, 7, 4, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 10,  // tri0
                      12, 10, 13, // tri1
                      12, 8, 10,  // tri2
                      14, 15, 12  // tri3
                      ),
    gsSPNTriangles_5b(15, 8, 12,  // tri0
                      16, 17, 18, // tri1
                      17, 19, 18, // tri2
                      18, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      19, 22, 20, // tri1
                      22, 23, 20, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      28, 26, 29, // tri1
                      28, 24, 26, // tri2
                      30, 31, 28  // tri3
                      ),
    gsSPNTriangles_5b(31, 24, 28, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r3_p_1_v[286], 6, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 2, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 2, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r3_p_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      8, 7, 5, // tri1
                      6, 9, 4, // tri2
                      9, 10, 4 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 4, // tri0
                      12, 13, 6, // tri1
                      9, 6, 13,  // tri2
                      3, 14, 2   // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 2, // tri0
                      2, 16, 0,  // tri1
                      15, 17, 2, // tri2
                      18, 19, 20 // tri3
                      ),
    gsSPNTriangles_5b(18, 21, 19, // tri0
                      22, 23, 24, // tri1
                      25, 26, 27, // tri2
                      26, 28, 27  // tri3
                      ),
    gsSPNTriangles_5b(1, 29, 3,  // tri0
                      1, 30, 29, // tri1
                      31, 23, 8, // tri2
                      23, 7, 8   // tri3
                      ),
    gsSPVertex(&grd_s_r3_p_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      4, 6, 5, // tri1
                      6, 7, 5, // tri2
                      2, 8, 0  // tri3
                      ),
    gsSPNTriangles_5b(2, 9, 8,    // tri0
                      10, 11, 12, // tri1
                      13, 14, 15, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 18, // tri0
                      20, 21, 22, // tri1
                      23, 24, 25, // tri2
                      26, 0, 27   // tri3
                      ),
    gsSPNTriangles_5b(0, 28, 27,  // tri0
                      0, 8, 28,   // tri1
                      29, 26, 24, // tri2
                      26, 27, 24  // tri3
                      ),
    gsSPNTriangles_5b(19, 30, 18, // tri0
                      19, 14, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r3_p_1_v[63], 14, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      9, 10, 11, // tri1
                      12, 13, 9, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r3_p_1_v[77], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3,   // tri0
                      6, 7, 8,   // tri1
                      7, 9, 8,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      13, 14, 12, // tri1
                      15, 16, 17, // tri2
                      16, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      22, 19, 23, // tri1
                      24, 22, 25, // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(20, 26, 29, // tri0
                      27, 30, 31, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r3_p_1_v[109], 25, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 6,   // tri0
                      11, 12, 13, // tri1
                      14, 15, 16, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      22, 23, 24, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r3_p_1_v[134], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,  // tri0
                      3, 8, 4,  // tri1
                      1, 9, 10, // tri2
                      10, 2, 1  // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 2, // tri0
                      12, 9, 13, // tri1
                      9, 1, 13,  // tri2
                      1, 0, 13   // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      15, 17, 16, // tri1
                      17, 18, 16, // tri2
                      17, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 18, // tri0
                      19, 20, 18, // tri1
                      22, 21, 20, // tri2
                      23, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 28, // tri0
                      26, 29, 27, // tri1
                      27, 30, 28, // tri2
                      31, 23, 25  // tri3
                      ),
    gsSPVertex(&grd_s_r3_p_1_v[166], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 5  // tri2
                          ),
    gsSPNTriangles_5b(7, 3, 5,   // tri0
                      8, 9, 10,  // tri1
                      9, 11, 10, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(9, 12, 14,  // tri0
                      9, 15, 12,  // tri1
                      15, 16, 17, // tri2
                      16, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 17, // tri0
                      11, 20, 10, // tri1
                      1, 6, 21,   // tri2
                      6, 22, 21   // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 21, // tri0
                      24, 0, 25,  // tri1
                      0, 26, 25,  // tri2
                      27, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(28, 30, 29, // tri0
                      28, 31, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r3_p_1_v[198], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          3, 1, 0, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 3, // tri0
                      6, 7, 3, // tri1
                      7, 5, 3, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(7, 11, 10,  // tri0
                      11, 8, 10,  // tri1
                      11, 12, 13, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(11, 15, 12, // tri0
                      15, 16, 12, // tri1
                      15, 17, 16, // tri2
                      16, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 16, // tri0
                      17, 19, 18, // tri1
                      19, 20, 18, // tri2
                      20, 21, 18  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      25, 26, 27, // tri1
                      25, 28, 26, // tri2
                      28, 29, 26  // tri3
                      ),
    gsSPVertex(&grd_s_r3_p_1_v[228], 26, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5, // tri0
                      7, 8, 5, // tri1
                      7, 9, 8, // tri2
                      7, 0, 9  // tri3
                      ),
    gsSPNTriangles_5b(0, 3, 9,    // tri0
                      10, 11, 12, // tri1
                      11, 13, 12, // tri2
                      14, 13, 15  // tri3
                      ),
    gsSPNTriangles_5b(13, 16, 12, // tri0
                      17, 14, 15, // tri1
                      14, 18, 13, // tri2
                      19, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 21, // tri0
                      22, 18, 21, // tri1
                      19, 23, 20, // tri2
                      23, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 22, // tri0
                      23, 25, 24, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
