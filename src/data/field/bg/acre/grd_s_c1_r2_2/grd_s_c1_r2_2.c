#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c1_r2_2_v[] = {
#include "assets/field/bg/grd_s_c1_r2_2_v.inc"
};

extern Gfx grd_s_c1_r2_2_modelT[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 1, 0, TEXEL0, TEXEL1, COMBINED, 0, SHADE, TEXEL0,
                       COMBINED, 0, PRIM_LOD_FRAC, PRIMITIVE),
    gsDPSetPrimColor(0, 50, 255, 255, 255, 50),
    gsDPSetEnvColor(0x00, 0x3C, 0xFF, 0xFF),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(water_1_tex_dummy, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPLoadMultiBlock_4b_Dolphin(water_2_tex_dummy, 1, G_IM_FMT_I, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPDisplayList(0x08000000),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c1_r2_2_v[267], 13, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 8,  // tri0
                      9, 1, 3,  // tri1
                      7, 0, 10, // tri2
                      5, 8, 6   // tri3
                      ),
    gsSPNTriangles_5b(7, 10, 11, // tri0
                      0, 2, 10,  // tri1
                      12, 9, 3,  // tri2
                      7, 11, 8   // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c1_r2_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c1_r2_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          1, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,  // tri0
                      8, 10, 11, // tri1
                      9, 12, 10, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(6, 16, 7,   // tri0
                      12, 17, 18, // tri1
                      12, 9, 17,  // tri2
                      1, 7, 19    // tri3
                      ),
    gsSPNTriangles_5b(14, 8, 11,  // tri0
                      20, 13, 15, // tri1
                      21, 22, 23, // tri2
                      1, 19, 2    // tri3
                      ),
    gsSPNTriangles_5b(4, 24, 5,  // tri0
                      6, 25, 26, // tri1
                      16, 6, 26, // tri2
                      26, 3, 5   // tri3
                      ),
    gsSPNTriangles_5b(26, 25, 3, // tri0
                      27, 28, 3, // tri1
                      3, 28, 29, // tri2
                      24, 4, 30  // tri3
                      ),
    gsSPNTriangles_5b(24, 30, 31, // tri0
                      3, 29, 4,   // tri1
                      25, 27, 3,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_2_v[32], 30, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,  // tri0
                      7, 10, 8, // tri1
                      3, 2, 11, // tri2
                      12, 13, 5 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 5, // tri0
                      5, 15, 16, // tri1
                      5, 14, 15, // tri2
                      16, 15, 17 // tri3
                      ),
    gsSPNTriangles_5b(15, 18, 17, // tri0
                      17, 19, 3,  // tri1
                      17, 18, 19, // tri2
                      3, 19, 0    // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 0,  // tri0
                      20, 21, 0,  // tri1
                      21, 20, 22, // tri2
                      20, 23, 22  // tri3
                      ),
    gsSPNTriangles_5b(22, 24, 25, // tri0
                      22, 23, 24, // tri1
                      26, 27, 7,  // tri2
                      27, 28, 7   // tri3
                      ),
    gsSPNTriangles_5b(7, 29, 10, // tri0
                      7, 28, 29, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_r2_2_v[62], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(7, 9, 8,    // tri0
                      10, 11, 12, // tri1
                      13, 14, 15, // tri2
                      14, 0, 15   // tri3
                      ),
    gsSPNTriangles_5b(16, 5, 17,  // tri0
                      17, 5, 4,   // tri1
                      18, 19, 20, // tri2
                      21, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(24, 23, 22, // tri0
                      24, 22, 19, // tri1
                      22, 21, 25, // tri2
                      24, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 16, // tri0
                      28, 29, 25, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_2_v[92], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 5, 4  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 11, 12, // tri1
                      13, 14, 15, // tri2
                      13, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(2, 17, 18,  // tri0
                      19, 20, 21, // tri1
                      19, 21, 22, // tri2
                      20, 13, 16  // tri3
                      ),
    gsSPNTriangles_5b(20, 16, 21, // tri0
                      23, 24, 25, // tri1
                      26, 11, 10, // tri2
                      26, 10, 27  // tri3
                      ),
    gsSPNTriangles_5b(23, 28, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_2_v[122], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 2, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 6, 8,   // tri0
                      9, 0, 6,   // tri1
                      10, 9, 6,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      17, 18, 12, // tri1
                      19, 20, 21, // tri2
                      11, 22, 12  // tri3
                      ),
    gsSPNTriangles_5b(22, 17, 12, // tri0
                      18, 23, 12, // tri1
                      24, 14, 16, // tri2
                      25, 11, 13  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 28, // tri0
                      29, 30, 27, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_2_v[153], 27, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      12, 9, 13,  // tri1
                      14, 15, 16, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 17, 21, // tri0
                      18, 22, 19, // tri1
                      11, 20, 23, // tri2
                      24, 25, 26  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_r2_2_v[180], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 2, 6,   // tri0
                      7, 8, 9,   // tri1
                      0, 10, 11, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(8, 13, 14, // tri0
                      8, 14, 9,  // tri1
                      13, 4, 15, // tri2
                      16, 7, 17  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      19, 21, 22, // tri1
                      21, 23, 24, // tri2
                      23, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 28, // tri0
                      27, 29, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_2_v[211], 13, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 8,   // tri0
                      7, 9, 10,  // tri1
                      9, 11, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_r2_2_v[224], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          3, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 5, // tri0
                      5, 6, 4, // tri1
                      5, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,   // tri0
                      7, 10, 9,  // tri1
                      10, 11, 9, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 12, // tri0
                      13, 14, 12, // tri1
                      14, 15, 12, // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 16, // tri0
                      18, 19, 20, // tri1
                      18, 21, 19, // tri2
                      19, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 20, // tri0
                      24, 25, 26, // tri1
                      24, 27, 28, // tri2
                      24, 28, 25  // tri3
                      ),
    gsSPNTriangles_5b(25, 29, 26, // tri0
                      23, 30, 20, // tri1
                      23, 31, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_2_v[256], 11, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      4, 6, 5, // tri1
                      7, 8, 9, // tri2
                      6, 10, 5 // tri3
                      ),
    gsSPEndDisplayList(),
};
