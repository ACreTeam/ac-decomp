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

static Vtx grd_s_c7_r3_2_v[] = {
#include "assets/field/bg/grd_s_c7_r3_2_v.inc"
};

extern Gfx grd_s_c7_r3_2_modelT[] = {
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
    gsSPVertex(&grd_s_c7_r3_2_v[285], 24, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      5, 6, 4, // tri1
                      6, 7, 4, // tri2
                      6, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 7,    // tri0
                      9, 10, 7,   // tri1
                      11, 12, 13, // tri2
                      14, 15, 11  // tri3
                      ),
    gsSPNTriangles_5b(16, 14, 11, // tri0
                      17, 13, 18, // tri1
                      19, 17, 18, // tri2
                      20, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(20, 18, 21, // tri0
                      22, 23, 20, // tri1
                      22, 20, 21, // tri2
                      16, 11, 13  // tri3
                      ),
    gsSPNTriangles_5b(17, 16, 13, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c7_r3_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c7_r3_2_v[272], 13, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 5, 8,   // tri0
                      9, 7, 10,  // tri1
                      11, 9, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_r3_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 3, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 1, // tri0
                      6, 4, 1, // tri1
                      5, 1, 7, // tri2
                      8, 9, 0  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 0,   // tri0
                      10, 11, 0,  // tri1
                      12, 13, 14, // tri2
                      13, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(13, 11, 15, // tri0
                      12, 16, 13, // tri1
                      17, 18, 19, // tri2
                      18, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      21, 24, 22, // tri1
                      22, 25, 23, // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(27, 29, 28, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c7_r3_2_v[30], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 9, 10,  // tri1
                      9, 4, 10,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 13, // tri0
                      12, 15, 14, // tri1
                      8, 16, 9,   // tri2
                      13, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 18, // tri0
                      13, 18, 20, // tri1
                      19, 7, 18,  // tri2
                      7, 5, 18    // tri3
                      ),
    gsSPNTriangles_5b(21, 16, 22, // tri0
                      6, 10, 4,   // tri1
                      16, 21, 9,  // tri2
                      23, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 28, // tri0
                      27, 29, 28, // tri1
                      30, 31, 26, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c7_r3_2_v[62], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      10, 12, 11, // tri1
                      10, 13, 12, // tri2
                      10, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(10, 15, 14, // tri0
                      15, 16, 14, // tri1
                      16, 17, 14, // tri2
                      15, 18, 16  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 16, // tri0
                      18, 20, 19, // tri1
                      21, 22, 23, // tri2
                      22, 24, 23  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 27, // tri0
                      25, 28, 26, // tri1
                      25, 29, 28, // tri2
                      25, 30, 29  // tri3
                      ),
    gsSPVertex(&grd_s_c7_r3_2_v[93], 21, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 0,  // tri0
                      7, 9, 8,  // tri1
                      9, 10, 8, // tri2
                      9, 11, 10 // tri3
                      ),
    gsSPNTriangles_5b(7, 12, 9,   // tri0
                      13, 14, 15, // tri1
                      14, 16, 15, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 20, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_r3_2_v[114], 16, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          2, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 0,   // tri0
                      8, 9, 6,   // tri1
                      10, 11, 8, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 12, // tri0
                      13, 14, 15, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_r3_2_v[130], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 4, 6, // tri0
                      7, 6, 8, // tri1
                      9, 7, 8, // tri2
                      9, 8, 10 // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      12, 9, 11,  // tri1
                      12, 11, 13, // tri2
                      14, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 17, // tri0
                      18, 14, 17, // tri1
                      18, 17, 19, // tri2
                      20, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 19, 21, // tri0
                      20, 21, 22, // tri1
                      23, 24, 25, // tri2
                      23, 26, 24  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 24, // tri0
                      26, 28, 27, // tri1
                      28, 29, 27, // tri2
                      28, 30, 29  // tri3
                      ),
    gsSPNTriangles_5b(28, 0, 30, // tri0
                      0, 2, 30,  // tri1
                      1, 31, 3,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_s_c7_r3_2_v[162], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 6,    // tri0
                      9, 10, 8,   // tri1
                      10, 11, 12, // tri2
                      13, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 14, // tri0
                      17, 18, 16, // tri1
                      19, 20, 18, // tri2
                      21, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 22, // tri0
                      23, 25, 24, // tri1
                      25, 26, 24, // tri2
                      26, 27, 24  // tri3
                      ),
    gsSPNTriangles_5b(26, 28, 27, // tri0
                      26, 29, 28, // tri1
                      29, 30, 28, // tri2
                      29, 31, 30  // tri3
                      ),
    gsSPVertex(&grd_s_c7_r3_2_v[194], 6, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_r3_2_v[200], 32, 0),
    gsSPNTrianglesInit_5b(30,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 0, 6,  // tri0
                      7, 8, 9,  // tri1
                      8, 10, 9, // tri2
                      10, 11, 9 // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 11, // tri0
                      10, 13, 12, // tri1
                      13, 14, 12, // tri2
                      13, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 14, // tri0
                      16, 17, 14, // tri1
                      16, 18, 17, // tri2
                      16, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 18, // tri0
                      19, 21, 20, // tri1
                      21, 22, 20, // tri2
                      21, 23, 22  // tri3
                      ),
    gsSPNTriangles_5b(21, 24, 23, // tri0
                      24, 25, 23, // tri1
                      24, 26, 25, // tri2
                      26, 27, 25  // tri3
                      ),
    gsSPNTriangles_5b(27, 5, 25, // tri0
                      27, 1, 5,  // tri1
                      27, 28, 1, // tri2
                      28, 29, 1  // tri3
                      ),
    gsSPNTriangles_5b(29, 3, 1,   // tri0
                      29, 30, 3,  // tri1
                      29, 31, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c7_r3_2_v[232], 27, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      5, 6, 4, // tri1
                      5, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,   // tri0
                      9, 10, 8,  // tri1
                      9, 11, 10, // tri2
                      0, 12, 1   // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      14, 16, 15, // tri1
                      14, 17, 18, // tri2
                      17, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(14, 18, 16, // tri0
                      17, 20, 19, // tri1
                      20, 21, 22, // tri2
                      23, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(24, 26, 25, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_r3_2_v[259], 13, 0),
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
