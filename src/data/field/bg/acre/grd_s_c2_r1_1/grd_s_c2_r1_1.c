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

static Vtx grd_s_c2_r1_1_v[] = {
#include "assets/field/bg/grd_s_c2_r1_1_v.inc"
};

extern Gfx grd_s_c2_r1_1_modelT[] = {
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
    gsSPVertex(&grd_s_c2_r1_1_v[243], 26, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 2, // tri0
                      4, 6, 5, // tri1
                      7, 8, 9, // tri2
                      7, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      11, 13, 14, // tri1
                      15, 16, 17, // tri2
                      16, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(16, 19, 18, // tri0
                      16, 20, 19, // tri1
                      20, 21, 19, // tri2
                      21, 22, 19  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 25, // tri0
                      23, 21, 24, // tri1
                      23, 22, 21, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c2_r1_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c2_r1_1_v[228], 15, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 8,    // tri0
                      6, 9, 10,   // tri1
                      11, 12, 13, // tri2
                      12, 0, 14   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c2_r1_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(30,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,   // tri0
                      7, 8, 5,   // tri1
                      9, 10, 11, // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      15, 16, 17, // tri1
                      18, 16, 15, // tri2
                      14, 18, 15  // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 13, // tri0
                      10, 12, 11, // tri1
                      19, 20, 4,  // tri2
                      20, 7, 4    // tri3
                      ),
    gsSPNTriangles_5b(21, 12, 10, // tri0
                      21, 14, 12, // tri1
                      21, 22, 14, // tri2
                      22, 23, 14  // tri3
                      ),
    gsSPNTriangles_5b(23, 18, 14, // tri0
                      23, 16, 18, // tri1
                      23, 24, 16, // tri2
                      2, 25, 26   // tri3
                      ),
    gsSPNTriangles_5b(27, 2, 26, // tri0
                      28, 2, 27, // tri1
                      28, 0, 2,  // tri2
                      2, 3, 25   // tri3
                      ),
    gsSPNTriangles_5b(3, 29, 25,  // tri0
                      29, 30, 25, // tri1
                      29, 31, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c2_r1_1_v[32], 6, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          1, 0, 3, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_r1_1_v[38], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 11, 12, // tri1
                      11, 13, 12, // tri2
                      11, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(11, 15, 14, // tri0
                      15, 16, 14, // tri1
                      15, 17, 16, // tri2
                      18, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(18, 21, 19, // tri0
                      21, 21, 19, // tri1
                      21, 22, 19, // tri2
                      21, 23, 22  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 22, // tri0
                      25, 26, 22, // tri1
                      23, 24, 22, // tri2
                      27, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(27, 30, 28, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c2_r1_1_v[69], 28, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 2, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 2, // tri0
                      5, 6, 4, // tri1
                      5, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 6,    // tri0
                      8, 10, 9,   // tri1
                      11, 12, 13, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(12, 15, 14, // tri0
                      15, 16, 14, // tri1
                      16, 17, 14, // tri2
                      16, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      20, 22, 23, // tri1
                      20, 23, 24, // tri2
                      25, 26, 27  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c2_r1_1_v[97], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      2, 3, 4, // tri1
                      3, 5, 4, // tri2
                      2, 8, 0  // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 10,   // tri0
                      9, 6, 7,    // tri1
                      10, 11, 12, // tri2
                      13, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 15, // tri0
                      0, 17, 1,   // tri1
                      0, 18, 17,  // tri2
                      17, 19, 1   // tri3
                      ),
    gsSPNTriangles_5b(20, 15, 16, // tri0
                      14, 21, 16, // tri1
                      14, 22, 21, // tri2
                      14, 23, 22  // tri3
                      ),
    gsSPNTriangles_5b(15, 24, 13, // tri0
                      15, 25, 24, // tri1
                      25, 26, 24, // tri2
                      27, 19, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 6, 30, // tri0
                      6, 9, 30,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_s_c2_r1_1_v[128], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 6,   // tri0
                      7, 8, 6,   // tri1
                      7, 9, 8,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      14, 16, 15, // tri1
                      16, 17, 15, // tri2
                      18, 1, 19   // tri3
                      ),
    gsSPNTriangles_5b(20, 0, 13, // tri0
                      19, 0, 20, // tri1
                      1, 0, 19,  // tri2
                      21, 22, 23 // tri3
                      ),
    gsSPNTriangles_5b(21, 24, 22, // tri0
                      24, 25, 22, // tri1
                      26, 27, 28, // tri2
                      29, 27, 26  // tri3
                      ),
    gsSPVertex(&grd_s_c2_r1_1_v[158], 8, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 6, // tri0
                      4, 7, 6, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_r1_1_v[166], 15, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,  // tri0
                      9, 5, 11,  // tri1
                      12, 8, 13, // tri2
                      1, 12, 14  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_r1_1_v[181], 32, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 8, 9,    // tri0
                      10, 5, 11,  // tri1
                      12, 10, 13, // tri2
                      14, 12, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      19, 14, 20, // tri1
                      17, 19, 21, // tri2
                      4, 22, 3    // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 22,   // tri0
                      21, 19, 20, // tri1
                      13, 15, 12, // tri2
                      23, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(24, 26, 27, // tri0
                      28, 23, 29, // tri1
                      26, 30, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c2_r1_1_v[213], 15, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 8,    // tri0
                      6, 9, 10,   // tri1
                      11, 12, 13, // tri2
                      2, 14, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};
