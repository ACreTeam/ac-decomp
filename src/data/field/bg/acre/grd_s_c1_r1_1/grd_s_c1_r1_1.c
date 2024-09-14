#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c1_r1_1_v[] = {
#include "assets/field/bg/grd_s_c1_r1_1_v.inc"
};

extern Gfx grd_s_c1_r1_1_modelT[] = {
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
    gsSPVertex(&grd_s_c1_r1_1_v[256], 24, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4,  // tri0
                      6, 7, 8,  // tri1
                      7, 9, 8,  // tri2
                      10, 6, 11 // tri3
                      ),
    gsSPNTriangles_5b(6, 8, 11,   // tri0
                      12, 11, 13, // tri1
                      12, 10, 11, // tri2
                      13, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 14, // tri0
                      15, 16, 14, // tri1
                      16, 17, 14, // tri2
                      16, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(16, 19, 18, // tri0
                      5, 20, 21,  // tri1
                      5, 21, 4,   // tri2
                      20, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 21, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c1_r1_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c1_r1_1_v[280], 11, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          1, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 8,  // tri0
                      7, 9, 10, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_r1_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 9, 10,  // tri1
                      9, 11, 10, // tri2
                      0, 12, 1   // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      14, 16, 15, // tri1
                      16, 17, 15, // tri2
                      17, 3, 15   // tri3
                      ),
    gsSPNTriangles_5b(3, 1, 15,   // tri0
                      18, 19, 12, // tri1
                      19, 1, 12,  // tri2
                      18, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(18, 21, 20, // tri0
                      21, 13, 20, // tri1
                      18, 22, 21, // tri2
                      23, 24, 11  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 11, // tri0
                      25, 10, 11, // tri1
                      26, 27, 28, // tri2
                      26, 29, 27  // tri3
                      ),
    gsSPNTriangles_5b(26, 30, 29, // tri0
                      30, 31, 29, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r1_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 1, 5, // tri0
                      6, 7, 1, // tri1
                      7, 2, 1, // tri2
                      3, 8, 4  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      10, 12, 11, // tri1
                      9, 13, 10,  // tri2
                      14, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 15, // tri0
                      17, 18, 15, // tri1
                      19, 20, 21, // tri2
                      20, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 22, // tri0
                      23, 24, 22, // tri1
                      23, 25, 24, // tri2
                      25, 26, 24  // tri3
                      ),
    gsSPNTriangles_5b(22, 27, 21, // tri0
                      27, 28, 21, // tri1
                      28, 29, 30, // tri2
                      29, 31, 30  // tri3
                      ),
    gsSPNTriangles_5b(29, 16, 31, // tri0
                      30, 21, 28, // tri1
                      16, 15, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r1_1_v[64], 9, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      8, 7, 5, // tri1
                      5, 3, 8, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_r1_1_v[73], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 2,   // tri0
                      7, 8, 9,   // tri1
                      8, 10, 9,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 13, // tri0
                      15, 14, 12, // tri1
                      15, 16, 14, // tri2
                      17, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 16, // tri0
                      18, 19, 16, // tri1
                      20, 19, 18, // tri2
                      20, 21, 19  // tri3
                      ),
    gsSPNTriangles_5b(22, 21, 20, // tri0
                      22, 23, 21, // tri1
                      22, 24, 23, // tri2
                      25, 26, 27  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 28, // tri0
                      27, 26, 29, // tri1
                      7, 9, 29,   // tri2
                      29, 26, 7   // tri3
                      ),
    gsSPNTriangles_5b(8, 30, 10, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_s_c1_r1_1_v[104], 32, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 5, // tri0
                      6, 5, 7, // tri1
                      6, 7, 8, // tri2
                      7, 9, 8  // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 9,  // tri0
                      9, 7, 10,   // tri1
                      10, 12, 11, // tri2
                      10, 13, 12  // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 12, // tri0
                      15, 16, 14, // tri1
                      17, 18, 16, // tri2
                      19, 20, 18  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 20, // tri0
                      23, 24, 22, // tri1
                      25, 26, 24, // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(26, 25, 27, // tri0
                      24, 23, 25, // tri1
                      22, 21, 23, // tri2
                      20, 19, 21  // tri3
                      ),
    gsSPNTriangles_5b(18, 17, 19, // tri0
                      16, 15, 17, // tri1
                      14, 13, 15, // tri2
                      29, 30, 31  // tri3
                      ),
    gsSPVertex(&grd_s_c1_r1_1_v[136], 21, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(3, 6, 2, // tri0
                      3, 5, 6, // tri1
                      7, 8, 9, // tri2
                      9, 8, 4  // tri3
                      ),
    gsSPNTriangles_5b(5, 4, 8,   // tri0
                      7, 10, 8,  // tri1
                      10, 11, 8, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 13, // tri0
                      13, 16, 14, // tri1
                      17, 18, 15, // tri2
                      19, 20, 17  // tri3
                      ),
    gsSPNTriangles_5b(17, 20, 18, // tri0
                      15, 18, 16, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_r1_1_v[157], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          2, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 4, // tri0
                      5, 7, 6, // tri1
                      7, 8, 9, // tri2
                      7, 5, 8  // tri3
                      ),
    gsSPNTriangles_5b(4, 2, 5,   // tri0
                      10, 11, 9, // tri1
                      9, 8, 10,  // tri2
                      12, 13, 11 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      15, 14, 16, // tri1
                      14, 17, 16, // tri2
                      17, 18, 16  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 18, // tri0
                      21, 22, 20, // tri1
                      21, 23, 22, // tri2
                      20, 19, 21  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 23, // tri0
                      24, 26, 25, // tri1
                      24, 27, 26, // tri2
                      23, 21, 24  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r1_1_v[188], 14, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 4, // tri1
                          3, 5, 4  // tri2
                          ),
    gsSPNTriangles_5b(4, 1, 0,  // tri0
                      1, 6, 2,  // tri1
                      7, 8, 9,  // tri2
                      8, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      11, 10, 12, // tri1
                      7, 10, 8,   // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_r1_1_v[202], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 7, 4,    // tri0
                      9, 10, 6,   // tri1
                      11, 12, 10, // tri2
                      13, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 14, // tri0
                      18, 19, 20, // tri1
                      21, 20, 17, // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 23, // tri0
                      27, 24, 28, // tri1
                      29, 28, 19, // tri2
                      17, 16, 21  // tri3
                      ),
    gsSPNTriangles_5b(24, 27, 22, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r1_1_v[232], 13, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 4, 6,    // tri0
                      9, 7, 10,   // tri1
                      11, 10, 12, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_r1_1_v[245], 11, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 8,  // tri0
                      9, 5, 10, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};
