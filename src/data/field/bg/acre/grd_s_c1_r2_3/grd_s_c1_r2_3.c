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

static Vtx grd_s_c1_r2_3_v[] = {
#include "assets/field/bg/grd_s_c1_r2_3_v.inc"
};

extern Gfx grd_s_c1_r2_3_modelT[] = {
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
    gsSPVertex(&grd_s_c1_r2_3_v[288], 16, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4, // tri0
                      5, 6, 4, // tri1
                      6, 7, 4, // tri2
                      6, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(6, 9, 8,   // tri0
                      9, 10, 8,  // tri1
                      9, 11, 10, // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 10, // tri0
                      12, 14, 13, // tri1
                      12, 15, 14, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c1_r2_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c1_r2_3_v[271], 17, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      5, 8, 6,  // tri1
                      6, 9, 7,  // tri2
                      0, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 4, 13, // tri0
                      10, 8, 14, // tri1
                      9, 15, 16, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_r2_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      6, 8, 7,   // tri1
                      5, 9, 6,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      14, 16, 15, // tri1
                      16, 17, 15, // tri2
                      0, 18, 19   // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 19, // tri0
                      20, 21, 19, // tri1
                      22, 23, 24, // tri2
                      23, 17, 24  // tri3
                      ),
    gsSPNTriangles_5b(11, 4, 1,   // tri0
                      11, 10, 4,  // tri1
                      11, 25, 12, // tri2
                      25, 26, 12  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 12, // tri0
                      28, 5, 7,   // tri1
                      28, 29, 5,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_3_v[30], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      4, 8, 5,   // tri1
                      9, 10, 11, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 8, 12,  // tri0
                      13, 14, 15, // tri1
                      14, 16, 15, // tri2
                      14, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 16, // tri0
                      17, 19, 18, // tri1
                      19, 20, 18, // tri2
                      21, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(22, 24, 23, // tri0
                      9, 25, 7,   // tri1
                      12, 26, 11, // tri2
                      27, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(27, 30, 28, // tri0
                      28, 31, 29, // tri1
                      30, 0, 2,   // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_3_v[62], 30, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4, // tri0
                      1, 6, 5, // tri1
                      5, 7, 4, // tri2
                      5, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      10, 12, 11, // tri1
                      10, 13, 12, // tri2
                      14, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 15, // tri0
                      18, 19, 20, // tri1
                      21, 22, 23, // tri2
                      24, 23, 25  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 28, // tri0
                      26, 29, 27, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_r2_3_v[92], 17, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      5, 8, 6,  // tri1
                      6, 9, 7,  // tri2
                      10, 4, 11 // tri3
                      ),
    gsSPNTriangles_5b(0, 12, 13, // tri0
                      9, 14, 15, // tri1
                      12, 8, 16, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_r2_3_v[109], 32, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      6, 8, 7,   // tri1
                      9, 10, 11, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(9, 13, 10,  // tri0
                      9, 14, 13,  // tri1
                      15, 16, 17, // tri2
                      15, 18, 16  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      19, 22, 23, // tri1
                      24, 23, 22, // tri2
                      25, 24, 22  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 25, // tri0
                      17, 28, 26, // tri1
                      15, 29, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_3_v[140], 32, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          2, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      11, 12, 13, // tri1
                      14, 15, 16, // tri2
                      17, 14, 18  // tri3
                      ),
    gsSPNTriangles_5b(12, 19, 20, // tri0
                      19, 17, 21, // tri1
                      22, 23, 24, // tri2
                      22, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(27, 26, 25, // tri0
                      28, 27, 25, // tri1
                      29, 30, 28, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_3_v[171], 6, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_r2_3_v[177], 32, 0),
    gsSPNTrianglesInit_5b(29,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      5, 2, 6, // tri1
                      6, 4, 7, // tri2
                      4, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11, // tri0
                      9, 2, 10,  // tri1
                      2, 5, 10,  // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(12, 15, 13, // tri0
                      15, 16, 13, // tri1
                      17, 18, 19, // tri2
                      17, 20, 18  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      22, 12, 23, // tri1
                      22, 24, 12, // tri2
                      21, 23, 25  // tri3
                      ),
    gsSPNTriangles_5b(23, 12, 25, // tri0
                      26, 21, 25, // tri1
                      21, 27, 22, // tri2
                      21, 28, 27  // tri3
                      ),
    gsSPNTriangles_5b(28, 26, 29, // tri0
                      28, 21, 26, // tri1
                      18, 9, 11,  // tri2
                      18, 20, 9   // tri3
                      ),
    gsSPNTriangles_5b(30, 19, 31, // tri0
                      30, 17, 19, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_3_v[209], 24, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      8, 9, 10, // tri1
                      8, 11, 9, // tri2
                      8, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(8, 13, 12, // tri0
                      14, 0, 2,  // tri1
                      14, 15, 0, // tri2
                      3, 16, 4   // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 4, // tri0
                      18, 8, 10, // tri1
                      18, 19, 8, // tri2
                      19, 20, 8  // tri3
                      ),
    gsSPNTriangles_5b(20, 13, 8,  // tri0
                      21, 22, 5,  // tri1
                      21, 23, 22, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_r2_3_v[233], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      5, 8, 6, // tri1
                      5, 9, 8, // tri2
                      10, 7, 6 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      12, 14, 13, // tri1
                      15, 12, 16, // tri2
                      12, 11, 16  // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 13, // tri0
                      14, 18, 17, // tri1
                      18, 19, 17, // tri2
                      18, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(18, 21, 20, // tri0
                      21, 22, 20, // tri1
                      21, 23, 22, // tri2
                      21, 24, 23  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 23, // tri0
                      24, 26, 25, // tri1
                      24, 27, 26, // tri2
                      28, 29, 3   // tri3
                      ),
    gsSPNTriangles_5b(29, 4, 3, // tri0
                      0, 30, 1, // tri1
                      30, 5, 1, // tri2
                      30, 9, 5  // tri3
                      ),
    gsSPNTriangles_5b(10, 31, 7, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_3_v[265], 6, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};
