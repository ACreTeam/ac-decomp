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
extern u8 earth_tex_dummy[];

static Vtx grd_s_r2_1_v[] = {
#include "assets/field/bg/grd_s_r2_1_v.inc"
};

extern Gfx grd_s_r2_1_modelT[] = {
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
    gsSPVertex(&grd_s_r2_1_v[168], 16, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 3, 0  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      6, 5, 4, // tri1
                      6, 7, 5, // tri2
                      8, 7, 6  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 7,   // tri0
                      10, 9, 8,  // tri1
                      10, 11, 9, // tri2
                      12, 11, 10 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      14, 13, 12, // tri1
                      14, 15, 13, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r2_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r2_1_v[155], 13, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          1, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 8,   // tri0
                      7, 9, 10,  // tri1
                      9, 11, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r2_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      0, 2, 6, // tri1
                      2, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      12, 10, 9,  // tri1
                      10, 12, 13, // tri2
                      14, 10, 13  // tri3
                      ),
    gsSPNTriangles_5b(4, 15, 5,  // tri0
                      16, 5, 15, // tri1
                      5, 16, 17, // tri2
                      18, 19, 20 // tri3
                      ),
    gsSPNTriangles_5b(18, 21, 19, // tri0
                      22, 23, 24, // tri1
                      23, 22, 25, // tri2
                      20, 26, 18  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 18, // tri0
                      7, 28, 8,   // tri1
                      29, 27, 3,  // tri2
                      20, 30, 26  // tri3
                      ),
    gsSPVertex(&grd_s_r2_1_v[31], 27, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 6,   // tri0
                      4, 8, 9,   // tri1
                      8, 10, 11, // tri2
                      10, 11, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 11, // tri0
                      12, 13, 14, // tri1
                      14, 11, 12, // tri2
                      8, 11, 9    // tri3
                      ),
    gsSPNTriangles_5b(4, 9, 7,    // tri0
                      15, 16, 17, // tri1
                      16, 18, 19, // tri2
                      20, 5, 21   // tri3
                      ),
    gsSPNTriangles_5b(20, 3, 5,   // tri0
                      22, 6, 7,   // tri1
                      23, 24, 25, // tri2
                      25, 24, 22  // tri3
                      ),
    gsSPNTriangles_5b(26, 20, 21, // tri0
                      1, 26, 24,  // tri1
                      24, 2, 1,   // tri2
                      24, 23, 2   // tri3
                      ),
    gsSPNTriangles_5b(1, 20, 26, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r2_1_v[58], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          2, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(2, 5, 4, // tri0
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
                      13, 15, 14, // tri2
                      15, 16, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 16, // tri0
                      17, 18, 16, // tri1
                      17, 19, 18, // tri2
                      19, 20, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 21, 20, // tri0
                      19, 22, 21, // tri1
                      22, 23, 21, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      25, 28, 27, // tri1
                      28, 29, 27, // tri2
                      29, 30, 27  // tri3
                      ),
    gsSPNTriangles_5b(29, 31, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r2_1_v[90], 17, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      5, 6, 4, // tri1
                      5, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 6,   // tri0
                      8, 10, 9,  // tri1
                      10, 11, 9, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      13, 14, 11, // tri1
                      13, 15, 14, // tri2
                      13, 16, 15  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r2_1_v[107], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      11, 12, 13, // tri1
                      14, 15, 12, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(14, 19, 15, // tri0
                      19, 16, 15, // tri1
                      9, 11, 13,  // tri2
                      11, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(20, 8, 21, // tri0
                      0, 20, 1,  // tri1
                      6, 3, 4,   // tri2
                      3, 0, 2    // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      25, 22, 26, // tri1
                      27, 25, 26, // tri2
                      23, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(28, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r2_1_v[139], 3, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r2_1_v[142], 13, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 8,   // tri0
                      9, 10, 11, // tri1
                      10, 3, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};
