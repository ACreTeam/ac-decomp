#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c3_s_1_v[] = {
#include "assets/field/bg/grd_s_c3_s_1_v.inc"
};

extern Gfx grd_s_c3_s_1_modelT[] = {
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
    gsSPVertex(&grd_s_c3_s_1_v[329], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c3_s_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c3_s_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          1, 0, 3  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 1,  // tri0
                      6, 7, 8,  // tri1
                      7, 9, 8,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 8,   // tri0
                      12, 13, 14, // tri1
                      12, 15, 13, // tri2
                      15, 16, 13  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      17, 20, 18, // tri1
                      20, 21, 18, // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 27, // tri0
                      28, 29, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c3_s_1_v[31], 32, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 11, 12, // tri1
                      13, 14, 15, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(15, 19, 13, // tri0
                      20, 21, 22, // tri1
                      8, 7, 23,   // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(27, 4, 6,   // tri0
                      28, 24, 19, // tri1
                      29, 30, 17, // tri2
                      24, 13, 19  // tri3
                      ),
    gsSPVertex(&grd_s_c3_s_1_v[62], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 5,    // tri0
                      9, 7, 5,    // tri1
                      10, 11, 12, // tri2
                      7, 13, 8    // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      17, 18, 19, // tri1
                      20, 21, 10, // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(13, 17, 8,  // tri0
                      18, 22, 24, // tri1
                      13, 25, 17, // tri2
                      13, 26, 25  // tri3
                      ),
    gsSPNTriangles_5b(27, 14, 16, // tri0
                      10, 12, 20, // tri1
                      28, 22, 25, // tri2
                      29, 30, 31  // tri3
                      ),
    gsSPVertex(&grd_s_c3_s_1_v[94], 28, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          1, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      11, 12, 13, // tri1
                      1, 14, 6,   // tri2
                      14, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(2, 17, 0,   // tri0
                      18, 19, 20, // tri1
                      19, 18, 21, // tri2
                      22, 19, 21  // tri3
                      ),
    gsSPNTriangles_5b(15, 23, 16, // tri0
                      22, 21, 24, // tri1
                      25, 26, 27, // tri2
                      26, 22, 27  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c3_s_1_v[122], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      6, 8, 7,   // tri1
                      9, 10, 11, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(9, 13, 10,  // tri0
                      3, 1, 14,   // tri1
                      15, 16, 17, // tri2
                      18, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      24, 25, 26, // tri1
                      27, 28, 29, // tri2
                      21, 27, 22  // tri3
                      ),
    gsSPNTriangles_5b(27, 29, 22, // tri0
                      25, 14, 1,  // tri1
                      30, 12, 23, // tri2
                      25, 1, 26   // tri3
                      ),
    gsSPNTriangles_5b(30, 11, 12, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c3_s_1_v[153], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 6, 8,   // tri0
                      10, 5, 11, // tri1
                      2, 1, 12,  // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(6, 16, 7,   // tri0
                      13, 10, 14, // tri1
                      2, 12, 7,   // tri2
                      7, 12, 17   // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      21, 10, 13, // tri1
                      22, 23, 24, // tri2
                      25, 26, 27  // tri3
                      ),
    gsSPNTriangles_5b(25, 28, 26, // tri0
                      22, 24, 29, // tri1
                      29, 3, 21,  // tri2
                      24, 30, 4   // tri3
                      ),
    gsSPVertex(&grd_s_c3_s_1_v[184], 32, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,  // tri0
                      10, 2, 11, // tri1
                      12, 13, 6, // tri2
                      10, 11, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      18, 19, 20, // tri1
                      21, 22, 23, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 21, // tri0
                      20, 29, 30, // tri1
                      20, 30, 18, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c3_s_1_v[215], 29, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 3, 5  // tri2
                          ),
    gsSPNTriangles_5b(7, 2, 8,   // tri0
                      9, 10, 11, // tri1
                      12, 8, 13, // tri2
                      0, 2, 7    // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      17, 18, 9,  // tri1
                      19, 0, 7,   // tri2
                      19, 7, 12   // tri3
                      ),
    gsSPNTriangles_5b(20, 1, 0,   // tri0
                      21, 22, 23, // tri1
                      23, 24, 20, // tri2
                      18, 25, 9   // tri3
                      ),
    gsSPNTriangles_5b(26, 17, 9,  // tri0
                      27, 28, 21, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_s_1_v[244], 32, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 5,  // tri0
                      6, 7, 8,  // tri1
                      7, 9, 8,  // tri2
                      10, 9, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 10, 13, // tri0
                      6, 14, 15,  // tri1
                      16, 17, 18, // tri2
                      19, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 18, // tri0
                      23, 16, 18, // tri1
                      1, 24, 4,   // tri2
                      24, 25, 4   // tri3
                      ),
    gsSPNTriangles_5b(20, 26, 21, // tri0
                      27, 28, 29, // tri1
                      19, 30, 25, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c3_s_1_v[275], 26, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 11, 12, // tri1
                      13, 14, 15, // tri2
                      14, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 11, // tri0
                      20, 2, 19,  // tri1
                      21, 22, 23, // tri2
                      24, 25, 22  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_s_1_v[301], 28, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 11, 12, // tri1
                      13, 14, 15, // tri2
                      16, 17, 14  // tri3
                      ),
    gsSPNTriangles_5b(13, 16, 14, // tri0
                      10, 18, 11, // tri1
                      13, 15, 18, // tri2
                      4, 19, 5    // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 5,  // tri0
                      20, 22, 21, // tri1
                      20, 7, 22,  // tri2
                      7, 9, 22    // tri3
                      ),
    gsSPNTriangles_5b(4, 6, 23,   // tri0
                      19, 20, 5,  // tri1
                      24, 23, 25, // tri2
                      24, 26, 3   // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 26, // tri0
                      27, 12, 8,  // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
