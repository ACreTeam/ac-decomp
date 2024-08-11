#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];

static Vtx grd_s_e1_r1_1_v[] = {
#include "assets/field/bg/grd_s_e1_r1_1_v.inc"
};

extern Gfx grd_s_e1_r1_1_modelT[] = {
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
    gsSPVertex(&grd_s_e1_r1_1_v[302], 17, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 2, 6, // tri0
                      5, 0, 2, // tri1
                      7, 6, 8, // tri2
                      7, 5, 6  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11, // tri0
                      9, 7, 10,  // tri1
                      7, 8, 10,  // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(12, 9, 13,  // tri0
                      9, 11, 13,  // tri1
                      15, 14, 16, // tri2
                      15, 12, 14  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_e1_r1_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_e1_r1_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 5,  // tri0
                      6, 8, 7,  // tri1
                      9, 10, 8, // tri2
                      9, 11, 10 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      12, 14, 13, // tri1
                      14, 12, 15, // tri2
                      16, 17, 15  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 17, // tri0
                      20, 21, 19, // tri1
                      22, 23, 21, // tri2
                      21, 20, 22  // tri3
                      ),
    gsSPNTriangles_5b(19, 18, 20, // tri0
                      17, 16, 18, // tri1
                      15, 12, 16, // tri2
                      11, 9, 12   // tri3
                      ),
    gsSPNTriangles_5b(8, 24, 9, // tri0
                      8, 6, 24, // tri1
                      5, 4, 6,  // tri2
                      3, 0, 4   // tri3
                      ),
    gsSPNTriangles_5b(2, 25, 0,   // tri0
                      26, 27, 28, // tri1
                      28, 29, 30, // tri2
                      28, 30, 26  // tri3
                      ),
    gsSPVertex(&grd_s_e1_r1_1_v[31], 32, 0),
    gsSPNTrianglesInit_5b(33,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          4, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(2, 5, 0, // tri0
                      5, 6, 0, // tri1
                      5, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 6,    // tri0
                      8, 10, 11,  // tri1
                      12, 13, 10, // tri2
                      10, 13, 11  // tri3
                      ),
    gsSPNTriangles_5b(11, 9, 8,   // tri0
                      12, 14, 13, // tri1
                      12, 15, 14, // tri2
                      16, 17, 15  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 17, // tri0
                      19, 20, 21, // tri1
                      22, 23, 21, // tri2
                      21, 20, 22  // tri3
                      ),
    gsSPNTriangles_5b(19, 18, 20, // tri0
                      17, 16, 18, // tri1
                      15, 12, 16, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(24, 26, 4, // tri0
                      26, 27, 4, // tri1
                      27, 2, 4,  // tri2
                      27, 28, 2  // tri3
                      ),
    gsSPNTriangles_5b(28, 5, 2,  // tri0
                      28, 29, 5, // tri1
                      29, 7, 5,  // tri2
                      29, 30, 7  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 7, // tri0
                      7, 31, 8,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_s_e1_r1_1_v[63], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          4, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      3, 6, 5, // tri1
                      5, 6, 7, // tri2
                      6, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 7,   // tri0
                      9, 10, 7,  // tri1
                      9, 11, 10, // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      13, 14, 12, // tri1
                      12, 14, 15, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 18, // tri0
                      19, 20, 18, // tri1
                      21, 22, 23, // tri2
                      17, 16, 23  // tri3
                      ),
    gsSPNTriangles_5b(16, 24, 23, // tri0
                      24, 25, 23, // tri1
                      23, 25, 21, // tri2
                      26, 27, 22  // tri3
                      ),
    gsSPNTriangles_5b(22, 21, 26, // tri0
                      28, 29, 30, // tri1
                      27, 30, 29, // tri2
                      27, 26, 30  // tri3
                      ),
    gsSPNTriangles_5b(29, 28, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_e1_r1_1_v[95], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 2, // tri1
                          2, 1, 3  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      5, 6, 4, // tri1
                      5, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 6,    // tri0
                      9, 10, 6,   // tri1
                      11, 12, 13, // tri2
                      12, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 15, // tri0
                      16, 18, 17, // tri1
                      18, 19, 20, // tri2
                      19, 21, 20  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 21, // tri0
                      24, 25, 23, // tri1
                      26, 27, 25, // tri2
                      26, 28, 27  // tri3
                      ),
    gsSPNTriangles_5b(26, 29, 28, // tri0
                      26, 30, 29, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_e1_r1_1_v[126], 32, 0),
    gsSPNTrianglesInit_5b(29,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(3, 0, 4, // tri0
                      2, 6, 0, // tri1
                      7, 8, 6, // tri2
                      9, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      12, 10, 13, // tri1
                      14, 15, 11, // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      18, 16, 19, // tri1
                      20, 17, 21, // tri2
                      3, 22, 1    // tri3
                      ),
    gsSPNTriangles_5b(5, 23, 3,  // tri0
                      3, 23, 22, // tri1
                      2, 24, 25, // tri2
                      2, 1, 24   // tri3
                      ),
    gsSPNTriangles_5b(1, 22, 24,  // tri0
                      25, 24, 26, // tri1
                      24, 27, 26, // tri2
                      28, 29, 7   // tri3
                      ),
    gsSPNTriangles_5b(29, 26, 27, // tri0
                      29, 28, 26, // tri1
                      7, 30, 9,   // tri2
                      9, 31, 13   // tri3
                      ),
    gsSPNTriangles_5b(9, 30, 31, // tri0
                      7, 29, 30, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_s_e1_r1_1_v[158], 32, 0),
    gsSPNTrianglesInit_5b(31,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(5, 2, 1, // tri0
                      4, 6, 7, // tri1
                      7, 5, 4, // tri2
                      6, 8, 9  // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 6,   // tri0
                      8, 10, 11, // tri1
                      11, 9, 8,  // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      14, 15, 16, // tri1
                      16, 17, 18, // tri2
                      18, 14, 16  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      18, 17, 19, // tri1
                      19, 21, 20, // tri2
                      21, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 22, // tri0
                      22, 24, 25, // tri1
                      25, 26, 27, // tri2
                      27, 28, 3   // tri3
                      ),
    gsSPNTriangles_5b(3, 29, 1,   // tri0
                      22, 23, 24, // tri1
                      25, 24, 26, // tri2
                      27, 26, 28  // tri3
                      ),
    gsSPNTriangles_5b(3, 28, 29, // tri0
                      29, 30, 4, // tri1
                      4, 1, 29,  // tri2
                      30, 31, 4  // tri3
                      ),
    gsSPVertex(&grd_s_e1_r1_1_v[190], 32, 0),
    gsSPNTrianglesInit_5b(34,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          4, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(2, 5, 0, // tri0
                      6, 7, 8, // tri1
                      6, 8, 9, // tri2
                      4, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 10, // tri0
                      8, 10, 9, // tri1
                      11, 6, 9, // tri2
                      11, 9, 12 // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 12,  // tri0
                      3, 13, 10,  // tri1
                      10, 13, 12, // tri2
                      0, 14, 1    // tri3
                      ),
    gsSPNTriangles_5b(1, 13, 3,  // tri0
                      1, 14, 13, // tri1
                      0, 15, 14, // tri2
                      0, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 15, // tri0
                      16, 18, 17, // tri1
                      19, 20, 21, // tri2
                      20, 17, 21  // tri3
                      ),
    gsSPNTriangles_5b(21, 17, 18, // tri0
                      22, 23, 19, // tri1
                      23, 20, 19, // tri2
                      22, 24, 23  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 23, // tri0
                      26, 27, 28, // tri1
                      25, 28, 27, // tri2
                      25, 24, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 27, // tri0
                      27, 26, 29, // tri1
                      29, 31, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_e1_r1_1_v[222], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_e1_r1_1_v[226], 30, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      6, 8, 9, // tri1
                      6, 9, 7, // tri2
                      10, 1, 0 // tri3
                      ),
    gsSPNTriangles_5b(3, 11, 4,   // tri0
                      12, 13, 11, // tri1
                      12, 14, 13, // tri2
                      12, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 14, // tri0
                      14, 15, 16, // tri1
                      18, 19, 17, // tri2
                      17, 16, 18  // tri3
                      ),
    gsSPNTriangles_5b(11, 3, 12, // tri0
                      8, 20, 9,  // tri1
                      5, 21, 22, // tri2
                      21, 23, 22 // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 23, // tri0
                      24, 26, 25, // tri1
                      27, 28, 26, // tri2
                      27, 29, 28  // tri3
                      ),
    gsSPNTriangles_5b(28, 25, 26, // tri0
                      25, 22, 23, // tri1
                      22, 6, 5,   // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_e1_r1_1_v[256], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      8, 5, 9,   // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      13, 15, 11, // tri1
                      12, 16, 13, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(17, 12, 18, // tri0
                      12, 20, 18, // tri1
                      12, 11, 20, // tri2
                      19, 18, 21  // tri3
                      ),
    gsSPNTriangles_5b(21, 18, 22, // tri0
                      23, 24, 25, // tri1
                      26, 27, 24, // tri2
                      27, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(27, 29, 25, // tri0
                      24, 27, 25, // tri1
                      30, 28, 27, // tri2
                      30, 31, 28  // tri3
                      ),
    gsSPVertex(&grd_s_e1_r1_1_v[288], 14, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 4, // tri0
                      5, 8, 9, // tri1
                      9, 3, 5, // tri2
                      3, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 10,  // tri0
                      11, 12, 10, // tri1
                      10, 12, 13, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
