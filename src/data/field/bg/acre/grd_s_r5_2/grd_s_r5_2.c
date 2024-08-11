#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_r5_2_v[] = {
#include "assets/field/bg/grd_s_r5_2_v.inc"
};

extern Gfx grd_s_r5_2_modelT[] = {
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
    gsSPVertex(&grd_s_r5_2_v[209], 19, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      4, 6, 5, // tri1
                      4, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,   // tri0
                      9, 10, 8,  // tri1
                      10, 11, 8, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      13, 14, 11, // tri1
                      14, 15, 11, // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 15, // tri0
                      17, 18, 15, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r5_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r5_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 0, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,  // tri0
                      7, 3, 8,  // tri1
                      9, 6, 10, // tri2
                      11, 9, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 11, 14, // tri0
                      1, 15, 16,  // tri1
                      15, 17, 18, // tri2
                      9, 10, 12   // tri3
                      ),
    gsSPNTriangles_5b(1, 16, 2,   // tri0
                      19, 20, 21, // tri1
                      20, 22, 23, // tri2
                      22, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(24, 26, 27, // tri0
                      26, 28, 29, // tri1
                      28, 30, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r5_2_v[32], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 8,    // tri0
                      7, 9, 10,   // tri1
                      11, 12, 13, // tri2
                      14, 15, 13  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 13, // tri0
                      17, 18, 19, // tri1
                      20, 21, 18, // tri2
                      20, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      16, 25, 26, // tri1
                      23, 27, 24, // tri2
                      28, 29, 27  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 29, // tri0
                      11, 13, 31, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r5_2_v[64], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 2, 5, // tri0
                      2, 7, 5, // tri1
                      2, 1, 7, // tri2
                      0, 8, 1  // tri3
                      ),
    gsSPNTriangles_5b(0, 9, 8,   // tri0
                      0, 10, 9,  // tri1
                      10, 11, 9, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 12, // tri0
                      13, 14, 12, // tri1
                      13, 15, 14, // tri2
                      13, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(13, 17, 16, // tri0
                      17, 18, 16, // tri1
                      17, 19, 18, // tri2
                      19, 20, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 21, 20, // tri0
                      21, 22, 20, // tri1
                      21, 23, 22, // tri2
                      21, 24, 23  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 27, // tri0
                      25, 28, 26, // tri1
                      28, 29, 26, // tri2
                      29, 30, 26  // tri3
                      ),
    gsSPNTriangles_5b(29, 31, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r5_2_v[96], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      5, 6, 4, // tri1
                      5, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,   // tri0
                      9, 10, 8,  // tri1
                      9, 11, 10, // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 10, // tri0
                      12, 14, 13, // tri1
                      14, 15, 13, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(16, 19, 17, // tri0
                      19, 20, 17, // tri1
                      20, 21, 17, // tri2
                      20, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 21, // tri0
                      22, 24, 23, // tri1
                      24, 25, 23, // tri2
                      24, 26, 25  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 25, // tri0
                      26, 28, 27, // tri1
                      28, 29, 27, // tri2
                      28, 30, 29  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r5_2_v[128], 7, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      5, 6, 4, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r5_2_v[135], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      8, 10, 9,   // tri1
                      11, 12, 10, // tri2
                      12, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(5, 14, 3,   // tri0
                      15, 16, 17, // tri1
                      16, 18, 2,  // tri2
                      18, 0, 2    // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      20, 22, 23, // tri1
                      22, 24, 23, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(25, 6, 27, // tri0
                      28, 29, 1, // tri1
                      29, 2, 1,  // tri2
                      2, 29, 16  // tri3
                      ),
    gsSPNTriangles_5b(16, 29, 17, // tri0
                      15, 17, 30, // tri1
                      19, 21, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r5_2_v[167], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          4, 3, 5  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 3, // tri0
                      3, 6, 5, // tri1
                      5, 6, 7, // tri2
                      8, 7, 6  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      10, 12, 11, // tri1
                      11, 12, 13, // tri2
                      13, 12, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 14, // tri0
                      17, 15, 18, // tri1
                      15, 17, 16, // tri2
                      16, 17, 19  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      21, 20, 22, // tri1
                      23, 22, 20, // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 24, // tri0
                      27, 28, 25, // tri1
                      29, 30, 18, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r5_2_v[198], 11, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 6, // tri0
                      3, 5, 2, // tri1
                      2, 7, 0, // tri2
                      7, 2, 8  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 10, // tri0
                      5, 6, 9,  // tri1
                      9, 8, 5,  // tri2
                      8, 2, 5   // tri3
                      ),
    gsSPEndDisplayList(),
};
