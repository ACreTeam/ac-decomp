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

static Vtx grd_s_c3_r2_1_v[] = {
#include "assets/field/bg/grd_s_c3_r2_1_v.inc"
};

extern Gfx grd_s_c3_r2_1_modelT[] = {
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
    gsSPVertex(&grd_s_c3_r2_1_v[281], 24, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 1, 0, // tri0
                      6, 7, 8, // tri1
                      6, 9, 7, // tri2
                      10, 9, 6 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 9,  // tri0
                      12, 13, 10, // tri1
                      13, 11, 10, // tri2
                      14, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 14, 16, // tri0
                      18, 17, 16, // tri1
                      19, 15, 20, // tri2
                      21, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(16, 15, 19, // tri0
                      16, 19, 22, // tri1
                      16, 22, 23, // tri2
                      18, 16, 23  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c3_r2_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c3_r2_1_v[245], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      12, 13, 9,  // tri1
                      14, 15, 16, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 13, 12, // tri0
                      2, 19, 20,  // tri1
                      7, 1, 8,    // tri2
                      10, 21, 11  // tri3
                      ),
    gsSPNTriangles_5b(22, 15, 14, // tri0
                      23, 22, 24, // tri1
                      21, 25, 26, // tri2
                      25, 23, 27  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 30, // tri0
                      17, 28, 18, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c3_r2_1_v[276], 5, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c3_r2_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(35,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 1, // tri0
                      0, 6, 5, // tri1
                      7, 8, 9, // tri2
                      7, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 8,  // tri0
                      11, 12, 8,  // tri1
                      11, 13, 12, // tri2
                      13, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 14, // tri0
                      15, 16, 14, // tri1
                      1, 17, 18,  // tri2
                      18, 3, 1    // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 3,  // tri0
                      18, 20, 21, // tri1
                      18, 21, 19, // tri2
                      20, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 22, // tri0
                      20, 24, 23, // tri1
                      20, 25, 24, // tri2
                      25, 26, 24  // tri3
                      ),
    gsSPNTriangles_5b(15, 27, 16, // tri0
                      9, 8, 28,   // tri1
                      8, 29, 28,  // tri2
                      29, 8, 12   // tri3
                      ),
    gsSPNTriangles_5b(14, 30, 12, // tri0
                      12, 30, 29, // tri1
                      30, 14, 16, // tri2
                      27, 31, 16  // tri3
                      ),
    gsSPNTriangles_5b(16, 31, 30, // tri0
                      27, 5, 31,  // tri1
                      5, 6, 31,   // tri2
                      19, 4, 3    // tri3
                      ),
    gsSPVertex(&grd_s_c3_r2_1_v[32], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          2, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 4, // tri0
                      5, 7, 6, // tri1
                      4, 6, 3, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_r2_1_v[40], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,  // tri0
                      8, 9, 10, // tri1
                      8, 11, 9, // tri2
                      8, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      13, 15, 16, // tri1
                      17, 14, 13, // tri2
                      7, 18, 15   // tri3
                      ),
    gsSPNTriangles_5b(19, 17, 13, // tri0
                      16, 15, 18, // tri1
                      18, 7, 20,  // tri2
                      20, 7, 4    // tri3
                      ),
    gsSPNTriangles_5b(11, 21, 22, // tri0
                      11, 12, 21, // tri1
                      22, 23, 0,  // tri2
                      22, 21, 23  // tri3
                      ),
    gsSPNTriangles_5b(0, 23, 1,   // tri0
                      24, 25, 26, // tri1
                      24, 27, 25, // tri2
                      28, 27, 24  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 27, // tri0
                      30, 29, 28, // tri1
                      30, 31, 29, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c3_r2_1_v[72], 14, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 6,  // tri0
                      6, 7, 8,  // tri1
                      9, 8, 10, // tri2
                      9, 11, 8  // tri3
                      ),
    gsSPNTriangles_5b(2, 3, 4,    // tri0
                      12, 13, 11, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c3_r2_1_v[86], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      6, 8, 7,   // tri1
                      0, 9, 5,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      14, 16, 15, // tri1
                      17, 18, 19, // tri2
                      18, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(21, 0, 22, // tri0
                      0, 2, 22,  // tri1
                      21, 9, 0,  // tri2
                      23, 24, 25 // tri3
                      ),
    gsSPNTriangles_5b(23, 26, 24, // tri0
                      27, 28, 29, // tri1
                      28, 30, 29, // tri2
                      27, 31, 28  // tri3
                      ),
    gsSPVertex(&grd_s_c3_r2_1_v[118], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4,  // tri0
                      5, 6, 7,  // tri1
                      8, 9, 10, // tri2
                      8, 11, 9  // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 9,  // tri0
                      12, 13, 9,  // tri1
                      14, 15, 16, // tri2
                      15, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(15, 18, 17, // tri0
                      19, 20, 21, // tri1
                      22, 23, 24, // tri2
                      22, 25, 23  // tri3
                      ),
    gsSPNTriangles_5b(22, 26, 25, // tri0
                      25, 27, 23, // tri1
                      27, 28, 23, // tri2
                      27, 21, 28  // tri3
                      ),
    gsSPNTriangles_5b(22, 29, 26, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c3_r2_1_v[148], 16, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3,  // tri0
                      3, 6, 2,  // tri1
                      7, 8, 9,  // tri2
                      10, 9, 11 // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 11,   // tri0
                      8, 12, 11,  // tri1
                      13, 14, 15, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_r2_1_v[164], 32, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 8,    // tri0
                      9, 5, 10,   // tri1
                      11, 12, 13, // tri2
                      14, 11, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      17, 14, 19, // tri1
                      20, 21, 22, // tri2
                      23, 20, 24  // tri3
                      ),
    gsSPNTriangles_5b(21, 16, 25, // tri0
                      0, 26, 27,  // tri1
                      28, 0, 29,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c3_r2_1_v[194], 16, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 5, 9,   // tri0
                      6, 10, 11, // tri1
                      10, 0, 12, // tri2
                      13, 8, 14  // tri3
                      ),
    gsSPNTriangles_5b(3, 15, 4, // tri0
                      5, 7, 9,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_r2_1_v[210], 32, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 3, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      9, 6, 11,   // tri1
                      12, 13, 14, // tri2
                      15, 12, 16  // tri3
                      ),
    gsSPNTriangles_5b(13, 17, 18, // tri0
                      17, 19, 20, // tri1
                      21, 15, 22, // tri2
                      23, 2, 24   // tri3
                      ),
    gsSPNTriangles_5b(0, 25, 26,  // tri0
                      25, 27, 28, // tri1
                      29, 8, 10,  // tri2
                      20, 19, 29  // tri3
                      ),
    gsSPNTriangles_5b(28, 27, 30, // tri0
                      30, 21, 22, // tri1
                      31, 23, 24, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c3_r2_1_v[242], 3, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};
