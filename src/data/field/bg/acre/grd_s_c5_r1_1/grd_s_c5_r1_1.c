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

static Vtx grd_s_c5_r1_1_v[] = {
#include "assets/field/bg/grd_s_c5_r1_1_v.inc"
};

extern Gfx grd_s_c5_r1_1_modelT[] = {
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
    gsSPVertex(&grd_s_c5_r1_1_v[274], 24, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 8,   // tri0
                      4, 8, 5,   // tri1
                      9, 10, 11, // tri2
                      9, 11, 12  // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      16, 17, 18, // tri1
                      16, 18, 11, // tri2
                      13, 19, 14  // tri3
                      ),
    gsSPNTriangles_5b(0, 15, 20, // tri0
                      0, 13, 15, // tri1
                      0, 20, 1,  // tri2
                      21, 2, 22  // tri3
                      ),
    gsSPNTriangles_5b(2, 23, 22, // tri0
                      2, 1, 23,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c5_r1_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c5_r1_1_v[259], 15, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 8,   // tri0
                      1, 9, 10,  // tri1
                      9, 11, 12, // tri2
                      11, 13, 14 // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c5_r1_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(3, 7, 4,   // tri0
                      3, 8, 7,   // tri1
                      8, 9, 7,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      14, 15, 6,  // tri1
                      15, 5, 6,   // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 18, // tri0
                      19, 20, 18, // tri1
                      19, 21, 20, // tri2
                      16, 22, 17  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 17, // tri0
                      22, 24, 23, // tri1
                      25, 26, 27, // tri2
                      25, 28, 26  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 31, // tri0
                      30, 25, 31, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c5_r1_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      5, 6, 7, // tri1
                      6, 8, 7, // tri2
                      5, 9, 6  // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 12, // tri0
                      12, 13, 14, // tri1
                      14, 10, 12, // tri2
                      13, 0, 15   // tri3
                      ),
    gsSPNTriangles_5b(15, 14, 13, // tri0
                      15, 0, 16,  // tri1
                      17, 11, 10, // tri2
                      17, 18, 11  // tri3
                      ),
    gsSPNTriangles_5b(19, 18, 17, // tri0
                      20, 21, 22, // tri1
                      21, 20, 23, // tri2
                      24, 23, 20  // tri3
                      ),
    gsSPNTriangles_5b(25, 22, 21, // tri0
                      24, 26, 27, // tri1
                      26, 28, 27, // tri2
                      27, 28, 29  // tri3
                      ),
    gsSPVertex(&grd_s_c5_r1_1_v[62], 15, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 2, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 2, 4, // tri0
                      6, 7, 8, // tri1
                      6, 9, 7, // tri2
                      10, 9, 6 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      14, 10, 11, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c5_r1_1_v[77], 32, 0),
    gsSPNTrianglesInit_5b(32,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,  // tri0
                      7, 8, 6,  // tri1
                      9, 7, 10, // tri2
                      7, 5, 10  // tri3
                      ),
    gsSPNTriangles_5b(5, 11, 10, // tri0
                      3, 2, 12,  // tri1
                      12, 13, 3, // tri2
                      14, 15, 16 // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 15, // tri0
                      17, 7, 15,  // tri1
                      17, 8, 7,   // tri2
                      5, 18, 19   // tri3
                      ),
    gsSPNTriangles_5b(5, 4, 18,   // tri0
                      20, 21, 22, // tri1
                      20, 23, 21, // tri2
                      23, 24, 21  // tri3
                      ),
    gsSPNTriangles_5b(23, 25, 24, // tri0
                      25, 26, 24, // tri1
                      25, 1, 26,  // tri2
                      25, 27, 1   // tri3
                      ),
    gsSPNTriangles_5b(27, 2, 1,  // tri0
                      27, 28, 2, // tri1
                      28, 29, 2, // tri2
                      29, 12, 2  // tri3
                      ),
    gsSPNTriangles_5b(30, 16, 15, // tri0
                      7, 9, 15,   // tri1
                      15, 9, 30,  // tri2
                      19, 31, 5   // tri3
                      ),
    gsSPNTriangles_5b(5, 31, 11, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_s_c5_r1_1_v[109], 14, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 3, // tri0
                      5, 6, 7, // tri1
                      7, 6, 8, // tri2
                      5, 7, 3  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 7,    // tri0
                      10, 11, 12, // tri1
                      13, 10, 12, // tri2
                      4, 12, 11   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c5_r1_1_v[123], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      9, 12, 10,  // tri1
                      13, 14, 15, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(15, 19, 20, // tri0
                      21, 22, 23, // tri1
                      21, 24, 22, // tri2
                      24, 25, 22  // tri3
                      ),
    gsSPNTriangles_5b(25, 18, 22, // tri0
                      25, 16, 18, // tri1
                      16, 26, 17, // tri2
                      27, 20, 28  // tri3
                      ),
    gsSPNTriangles_5b(20, 29, 28, // tri0
                      20, 19, 29, // tri1
                      15, 30, 19, // tri2
                      15, 14, 30  // tri3
                      ),
    gsSPNTriangles_5b(13, 31, 14, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c5_r1_1_v[155], 31, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          3, 5, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 6, 5, // tri0
                      6, 7, 5, // tri1
                      6, 8, 7, // tri2
                      9, 7, 10 // tri3
                      ),
    gsSPNTriangles_5b(7, 8, 10,   // tri0
                      11, 9, 10,  // tri1
                      12, 11, 13, // tri2
                      14, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 15, // tri0
                      17, 18, 15, // tri1
                      17, 19, 18, // tri2
                      18, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      21, 24, 22, // tri1
                      21, 23, 25, // tri2
                      26, 25, 27  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c5_r1_1_v[186], 32, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,    // tri0
                      8, 9, 10,   // tri1
                      11, 10, 12, // tri2
                      13, 14, 9   // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      18, 19, 16, // tri1
                      20, 12, 19, // tri2
                      21, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(24, 21, 25, // tri0
                      26, 27, 28, // tri1
                      27, 24, 29, // tri2
                      2, 30, 31   // tri3
                      ),
    gsSPVertex(&grd_s_c5_r1_1_v[218], 26, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      12, 13, 14, // tri1
                      13, 15, 16, // tri2
                      15, 9, 16   // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      20, 17, 21, // tri1
                      18, 22, 23, // tri2
                      22, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(18, 23, 19, // tri0
                      9, 11, 16,  // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c5_r1_1_v[244], 15, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      10, 7, 11, // tri1
                      8, 12, 13, // tri2
                      12, 5, 14  // tri3
                      ),
    gsSPEndDisplayList(),
};
