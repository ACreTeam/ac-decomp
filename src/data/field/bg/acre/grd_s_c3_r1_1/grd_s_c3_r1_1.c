#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c3_r1_1_v[] = {
#include "assets/field/bg/grd_s_c3_r1_1_v.inc"
};

extern Gfx grd_s_c3_r1_1_modelT[] = {
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
    gsSPVertex(&grd_s_c3_r1_1_v[222], 12, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          4, 3, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 2, 5, // tri0
                      6, 4, 5, // tri1
                      6, 5, 7, // tri2
                      6, 7, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 6, 8,   // tri0
                      10, 11, 9, // tri1
                      10, 9, 8,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c3_r1_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c3_r1_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 0, 2,   // tri0
                      5, 4, 6,   // tri1
                      7, 8, 9,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      11, 14, 12, // tri1
                      11, 15, 16, // tri2
                      11, 13, 15  // tri3
                      ),
    gsSPNTriangles_5b(17, 11, 16, // tri0
                      17, 18, 11, // tri1
                      17, 19, 18, // tri2
                      14, 20, 12  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 12, // tri0
                      22, 23, 24, // tri1
                      23, 25, 24, // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(27, 29, 28, // tri0
                      30, 31, 29, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c3_r1_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 5,   // tri0
                      8, 9, 10,  // tri1
                      9, 11, 10, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(8, 15, 9,   // tri0
                      16, 17, 18, // tri1
                      16, 19, 17, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 25, // tri0
                      23, 26, 24, // tri1
                      24, 27, 25, // tri2
                      27, 28, 25  // tri3
                      ),
    gsSPNTriangles_5b(29, 2, 1,  // tri0
                      2, 30, 31, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_s_c3_r1_1_v[64], 29, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,    // tri0
                      8, 9, 10,   // tri1
                      11, 12, 13, // tri2
                      11, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      18, 19, 20, // tri1
                      19, 21, 20, // tri2
                      18, 0, 19   // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      22, 25, 23, // tri1
                      25, 26, 23, // tri2
                      27, 25, 22  // tri3
                      ),
    gsSPNTriangles_5b(28, 25, 27, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_r1_1_v[93], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 1, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 1,    // tri0
                      7, 8, 9,    // tri1
                      10, 11, 12, // tri2
                      5, 10, 13   // tri3
                      ),
    gsSPNTriangles_5b(14, 3, 15,  // tri0
                      16, 17, 18, // tri1
                      19, 7, 20,  // tri2
                      19, 20, 17  // tri3
                      ),
    gsSPNTriangles_5b(11, 16, 18, // tri0
                      21, 22, 23, // tri1
                      24, 21, 25, // tri2
                      22, 26, 27  // tri3
                      ),
    gsSPNTriangles_5b(26, 28, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c3_r1_1_v[123], 29, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 5, 9,    // tri0
                      6, 10, 11,  // tri1
                      10, 12, 13, // tri2
                      14, 8, 15   // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      19, 16, 20, // tri1
                      21, 22, 23, // tri2
                      24, 21, 25  // tri3
                      ),
    gsSPNTriangles_5b(17, 26, 27, // tri0
                      26, 24, 28, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_r1_1_v[152], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 1, 0, // tri0
                      3, 6, 4, // tri1
                      7, 8, 9, // tri2
                      8, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(8, 11, 10,  // tri0
                      11, 12, 10, // tri1
                      11, 13, 12, // tri2
                      13, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(13, 6, 14, // tri0
                      6, 3, 14,  // tri1
                      5, 15, 1,  // tri2
                      5, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      17, 20, 18, // tri1
                      18, 21, 19, // tri2
                      21, 22, 19  // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 22, // tri0
                      23, 24, 22, // tri1
                      23, 25, 24, // tri2
                      25, 26, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      27, 28, 26, // tri1
                      27, 29, 28, // tri2
                      29, 30, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 31, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c3_r1_1_v[184], 32, 0),
    gsSPNTrianglesInit_5b(37,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 6,   // tri0
                      7, 8, 6,   // tri1
                      2, 9, 10,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 13, // tri0
                      12, 9, 14,  // tri1
                      9, 15, 14,  // tri2
                      11, 16, 12  // tri3
                      ),
    gsSPNTriangles_5b(16, 10, 12, // tri0
                      10, 9, 12,  // tri1
                      1, 9, 2,    // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(17, 20, 18, // tri0
                      1, 19, 18,  // tri1
                      1, 0, 19,   // tri2
                      21, 4, 3    // tri3
                      ),
    gsSPNTriangles_5b(11, 3, 16,  // tri0
                      11, 21, 3,  // tri1
                      22, 20, 23, // tri2
                      20, 17, 23  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 23, // tri0
                      25, 22, 23, // tri1
                      26, 27, 4,  // tri2
                      27, 7, 4    // tri3
                      ),
    gsSPNTriangles_5b(28, 4, 21,  // tri0
                      28, 26, 4,  // tri1
                      13, 28, 11, // tri2
                      28, 21, 11  // tri3
                      ),
    gsSPNTriangles_5b(29, 9, 1,   // tri0
                      29, 15, 9,  // tri1
                      30, 29, 18, // tri2
                      29, 1, 18   // tri3
                      ),
    gsSPNTriangles_5b(31, 18, 20, // tri0
                      31, 30, 18, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c3_r1_1_v[216], 6, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 0, 5  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 5, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};
