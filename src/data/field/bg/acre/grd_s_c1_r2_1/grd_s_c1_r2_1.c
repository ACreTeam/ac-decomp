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

static Vtx grd_s_c1_r2_1_v[] = {
#include "assets/field/bg/grd_s_c1_r2_1_v.inc"
};

extern Gfx grd_s_c1_r2_1_modelT[] = {
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
    gsSPVertex(&grd_s_c1_r2_1_v[260], 12, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      4, 6, 5, // tri1
                      6, 7, 5, // tri2
                      6, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 7,   // tri0
                      8, 10, 9,  // tri1
                      8, 11, 10, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c1_r2_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c1_r2_1_v[247], 13, 0),
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
    gsSPVertex(&grd_s_c1_r2_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,  // tri0
                      8, 9, 10, // tri1
                      8, 11, 9, // tri2
                      10, 9, 12 // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 12,   // tri0
                      13, 14, 15, // tri1
                      14, 16, 15, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 19, // tri0
                      20, 21, 19, // tri1
                      20, 22, 21, // tri2
                      20, 23, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 22, // tri0
                      1, 25, 3,   // tri1
                      2, 3, 26,   // tri2
                      27, 28, 23  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 28, // tri0
                      30, 24, 28, // tri1
                      24, 23, 28, // tri2
                      17, 31, 18  // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 9, 10,  // tri1
                      8, 11, 9,  // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      18, 19, 20, // tri1
                      12, 21, 18, // tri2
                      22, 23, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 24, 23, // tri0
                      21, 12, 22, // tri1
                      24, 25, 23, // tri2
                      26, 25, 24  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 28, // tri0
                      26, 24, 27, // tri1
                      29, 30, 31, // tri2
                      30, 8, 31   // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_1_v[64], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      5, 8, 6, // tri1
                      8, 9, 6, // tri2
                      3, 7, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 4,  // tri0
                      13, 14, 12, // tri1
                      13, 12, 15, // tri2
                      15, 12, 11  // tri3
                      ),
    gsSPNTriangles_5b(15, 11, 16, // tri0
                      11, 17, 16, // tri1
                      18, 16, 17, // tri2
                      19, 9, 8    // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 22, // tri0
                      21, 14, 22, // tri1
                      5, 7, 1,    // tri2
                      7, 3, 1     // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 25, // tri0
                      26, 27, 19, // tri1
                      28, 29, 30, // tri2
                      28, 31, 29  // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_1_v[96], 10, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(6, 9, 7, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_r2_1_v[106], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      8, 7, 10,  // tri1
                      9, 6, 7,   // tri2
                      11, 10, 12 // tri3
                      ),
    gsSPNTriangles_5b(2, 13, 12,  // tri0
                      14, 15, 0,  // tri1
                      16, 17, 18, // tri2
                      18, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 22, // tri0
                      22, 23, 24, // tri1
                      24, 25, 26, // tri2
                      27, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_1_v[138], 20, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 11, 12, // tri1
                      13, 14, 10, // tri2
                      15, 16, 13  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 15, // tri0
                      9, 19, 17,  // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_r2_1_v[158], 32, 0),
    gsSPNTrianglesInit_5b(38,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          4, 5, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 2, // tri0
                      6, 7, 2, // tri1
                      7, 8, 2, // tri2
                      6, 9, 7  // tri3
                      ),
    gsSPNTriangles_5b(6, 10, 9,  // tri0
                      11, 12, 0, // tri1
                      13, 11, 0, // tri2
                      14, 13, 0  // tri3
                      ),
    gsSPNTriangles_5b(1, 4, 2,  // tri0
                      1, 0, 12, // tri1
                      8, 3, 2,  // tri2
                      0, 3, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      18, 17, 16, // tri1
                      19, 11, 20, // tri2
                      11, 21, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 11, 22, // tri0
                      11, 23, 22, // tri1
                      11, 19, 12, // tri2
                      11, 13, 23  // tri3
                      ),
    gsSPNTriangles_5b(10, 6, 24,  // tri0
                      24, 6, 5,   // tri1
                      18, 25, 17, // tri2
                      25, 26, 17  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 25, // tri0
                      27, 25, 18, // tri1
                      29, 27, 16, // tri2
                      27, 18, 16  // tri3
                      ),
    gsSPNTriangles_5b(30, 29, 31, // tri0
                      29, 16, 31, // tri1
                      31, 16, 15, // tri2
                      10, 24, 31  // tri3
                      ),
    gsSPNTriangles_5b(24, 30, 31, // tri0
                      10, 31, 15, // tri1
                      10, 15, 9,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_r2_1_v[190], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          4, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      6, 7, 5, // tri1
                      7, 4, 5, // tri2
                      8, 7, 6  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 8,  // tri0
                      10, 7, 8,  // tri1
                      11, 12, 9, // tri2
                      9, 12, 10  // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      13, 14, 15, // tri1
                      14, 16, 15, // tri2
                      16, 17, 15  // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 12, // tri0
                      18, 19, 20, // tri1
                      21, 22, 18, // tri2
                      23, 24, 22  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 24, // tri0
                      25, 27, 26, // tri1
                      28, 29, 27, // tri2
                      28, 30, 29  // tri3
                      ),
    gsSPVertex(&grd_s_c1_r2_1_v[221], 13, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          2, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 4,  // tri0
                      7, 8, 6,  // tri1
                      9, 8, 10, // tri2
                      11, 12, 9 // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_r2_1_v[234], 13, 0),
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
