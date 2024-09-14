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

static Vtx grd_s_c7_r3_1_v[] = {
#include "assets/field/bg/grd_s_c7_r3_1_v.inc"
};

extern Gfx grd_s_c7_r3_1_modelT[] = {
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
    gsSPVertex(&grd_s_c7_r3_1_v[257], 31, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 0, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 5, // tri0
                      6, 4, 5, // tri1
                      7, 6, 5, // tri2
                      7, 5, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 8,    // tri0
                      9, 8, 10,   // tri1
                      11, 12, 13, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      14, 16, 15, // tri1
                      17, 18, 19, // tri2
                      18, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 19, // tri0
                      22, 23, 24, // tri1
                      23, 25, 24, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      27, 28, 26, // tri1
                      29, 30, 28, // tri2
                      28, 27, 29  // tri3
                      ),
    gsSPNTriangles_5b(29, 10, 30, // tri0
                      29, 9, 10,  // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c7_r3_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c7_r3_1_v[242], 15, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 0, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      1, 7, 10,  // tri1
                      8, 11, 12, // tri2
                      11, 13, 14 // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_r3_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 4, 8,   // tri0
                      9, 10, 11, // tri1
                      10, 7, 12, // tri2
                      0, 9, 13   // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      15, 17, 18, // tri1
                      19, 20, 21, // tri2
                      17, 19, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 24, // tri0
                      23, 25, 26, // tri1
                      27, 14, 28, // tri2
                      29, 27, 30  // tri3
                      ),
    gsSPVertex(&grd_s_c7_r3_1_v[31], 23, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          5, 0, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 5, 8,    // tri0
                      9, 10, 11,  // tri1
                      12, 13, 14, // tri2
                      15, 14, 16  // tri3
                      ),
    gsSPNTriangles_5b(7, 8, 17,   // tri0
                      5, 6, 8,    // tri1
                      18, 17, 19, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(21, 18, 19, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_r3_1_v[54], 29, 0),
    gsSPNTrianglesInit_5b(33,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          2, 3, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      4, 5, 6, // tri1
                      5, 7, 6, // tri2
                      6, 7, 8  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,   // tri0
                      8, 10, 11, // tri1
                      8, 9, 10,  // tri2
                      11, 10, 12 // tri3
                      ),
    gsSPNTriangles_5b(12, 10, 13, // tri0
                      13, 14, 12, // tri1
                      14, 15, 16, // tri2
                      14, 13, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 15, 17, // tri0
                      15, 18, 17, // tri1
                      17, 19, 20, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(16, 21, 14, // tri0
                      16, 22, 21, // tri1
                      16, 17, 22, // tri2
                      20, 23, 17  // tri3
                      ),
    gsSPNTriangles_5b(17, 23, 22, // tri0
                      11, 24, 8,  // tri1
                      24, 25, 8,  // tri2
                      25, 6, 8    // tri3
                      ),
    gsSPNTriangles_5b(6, 26, 4,  // tri0
                      6, 25, 26, // tri1
                      26, 2, 4,  // tri2
                      26, 27, 2  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 2, // tri0
                      28, 0, 2,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_r3_1_v[83], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 8,  // tri0
                      3, 7, 2,  // tri1
                      5, 8, 6,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(9, 12, 13,  // tri0
                      13, 14, 15, // tri1
                      13, 12, 14, // tri2
                      9, 11, 12   // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      19, 20, 17, // tri1
                      19, 21, 20, // tri2
                      22, 23, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 24, 23, // tri0
                      25, 26, 24, // tri1
                      25, 27, 26, // tri2
                      28, 29, 27  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c7_r3_1_v[115], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 2, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 7, 9,    // tri0
                      10, 9, 11,  // tri1
                      11, 12, 13, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 13, // tri0
                      2, 1, 3,    // tri1
                      3, 16, 4,   // tri2
                      17, 18, 16  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 18, // tri0
                      19, 21, 20, // tri1
                      22, 23, 21, // tri2
                      22, 24, 23  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 24, // tri0
                      27, 28, 26, // tri1
                      28, 27, 29, // tri2
                      28, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(29, 31, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c7_r3_1_v[147], 12, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 5, 8,   // tri0
                      9, 10, 11, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_r3_1_v[159], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      6, 7, 8, // tri1
                      6, 9, 7, // tri2
                      9, 10, 7 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 7,  // tri0
                      7, 13, 8,   // tri1
                      14, 15, 16, // tri2
                      15, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 16, // tri0
                      18, 19, 16, // tri1
                      20, 21, 22, // tri2
                      21, 23, 22  // tri3
                      ),
    gsSPNTriangles_5b(21, 24, 23, // tri0
                      24, 25, 23, // tri1
                      25, 26, 13, // tri2
                      26, 8, 13   // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 29, // tri0
                      27, 30, 28, // tri1
                      27, 31, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c7_r3_1_v[191], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      8, 2, 3, // tri1
                      9, 0, 2, // tri2
                      9, 10, 0 // tri3
                      ),
    gsSPNTriangles_5b(11, 5, 12,  // tri0
                      13, 14, 11, // tri1
                      15, 16, 13, // tri2
                      16, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 14, // tri0
                      17, 18, 14, // tri1
                      19, 12, 20, // tri2
                      12, 5, 20   // tri3
                      ),
    gsSPNTriangles_5b(21, 7, 22, // tri0
                      22, 7, 23, // tri1
                      21, 5, 7,  // tri2
                      5, 21, 20  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 26, // tri0
                      27, 26, 25, // tri1
                      28, 26, 27, // tri2
                      28, 29, 26  // tri3
                      ),
    gsSPNTriangles_5b(28, 30, 29, // tri0
                      30, 31, 29, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c7_r3_1_v[223], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_r3_1_v[227], 15, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 8,   // tri0
                      9, 10, 11, // tri1
                      12, 9, 13, // tri2
                      10, 5, 14  // tri3
                      ),
    gsSPEndDisplayList(),
};
