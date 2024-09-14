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

static Vtx grd_s_c6_r1_2_v[] = {
#include "assets/field/bg/grd_s_c6_r1_2_v.inc"
};

extern Gfx grd_s_c6_r1_2_modelT[] = {
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
    gsSPVertex(&grd_s_c6_r1_2_v[245], 13, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      7, 8, 6,   // tri1
                      9, 10, 11, // tri2
                      12, 9, 11  // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 10, // tri0
                      9, 8, 7,  // tri1
                      4, 3, 5,  // tri2
                      4, 2, 3   // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c6_r1_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c6_r1_2_v[232], 13, 0),
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
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c6_r1_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(38,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,  // tri0
                      7, 8, 6,  // tri1
                      4, 9, 10, // tri2
                      4, 6, 9   // tri3
                      ),
    gsSPNTriangles_5b(6, 11, 9,  // tri0
                      6, 8, 11,  // tri1
                      8, 12, 11, // tri2
                      0, 2, 13   // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      15, 17, 16, // tri1
                      15, 18, 17, // tri2
                      15, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(16, 20, 21, // tri0
                      16, 17, 20, // tri1
                      17, 18, 20, // tri2
                      18, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 20, 13, // tri0
                      20, 23, 13, // tri1
                      20, 24, 23, // tri2
                      20, 22, 24  // tri3
                      ),
    gsSPNTriangles_5b(13, 23, 0, // tri0
                      23, 24, 0, // tri1
                      24, 25, 0, // tri2
                      0, 26, 1   // tri3
                      ),
    gsSPNTriangles_5b(0, 25, 26, // tri0
                      3, 4, 10,  // tri1
                      3, 1, 4,   // tri2
                      1, 26, 4   // tri3
                      ),
    gsSPNTriangles_5b(26, 5, 4,   // tri0
                      12, 27, 28, // tri1
                      12, 8, 27,  // tri2
                      8, 7, 27    // tri3
                      ),
    gsSPNTriangles_5b(7, 29, 27,  // tri0
                      28, 27, 30, // tri1
                      27, 31, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c6_r1_2_v[32], 11, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 2, 5, // tri0
                      2, 1, 5, // tri1
                      1, 7, 5, // tri2
                      6, 5, 8  // tri3
                      ),
    gsSPNTriangles_5b(5, 9, 8,  // tri0
                      5, 10, 9, // tri1
                      5, 7, 10, // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c6_r1_2_v[43], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 4, 8,   // tri0
                      3, 9, 10,  // tri1
                      9, 11, 10, // tri2
                      11, 7, 12  // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      13, 16, 17, // tri1
                      18, 17, 16, // tri2
                      19, 18, 16  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 19, // tri0
                      22, 23, 20, // tri1
                      24, 25, 22, // tri2
                      24, 26, 25  // tri3
                      ),
    gsSPNTriangles_5b(24, 27, 26, // tri0
                      27, 28, 29, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c6_r1_2_v[73], 16, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 4, 8,   // tri0
                      1, 7, 9,   // tri1
                      10, 3, 11, // tri2
                      5, 12, 13  // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 15, // tri0
                      5, 13, 6,   // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c6_r1_2_v[89], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 7,   // tri0
                      3, 5, 8,   // tri1
                      9, 10, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      15, 13, 16, // tri1
                      15, 14, 13, // tri2
                      16, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 17, // tri0
                      20, 21, 22, // tri1
                      20, 23, 21, // tri2
                      20, 24, 23  // tri3
                      ),
    gsSPNTriangles_5b(20, 25, 24, // tri0
                      20, 26, 25, // tri1
                      27, 28, 26, // tri2
                      27, 29, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 28, // tri0
                      29, 31, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c6_r1_2_v[121], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5, // tri0
                      4, 8, 7, // tri1
                      4, 9, 8, // tri2
                      4, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      12, 10, 13, // tri1
                      12, 14, 10, // tri2
                      15, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(15, 18, 16, // tri0
                      19, 20, 0,  // tri1
                      20, 1, 0,   // tri2
                      19, 21, 20  // tri3
                      ),
    gsSPNTriangles_5b(19, 22, 21, // tri0
                      15, 23, 18, // tri1
                      11, 24, 25, // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 29, // tri0
                      11, 25, 29, // tri1
                      26, 28, 30, // tri2
                      31, 30, 28  // tri3
                      ),
    gsSPVertex(&grd_s_c6_r1_2_v[153], 31, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      0, 8, 10,   // tri1
                      11, 12, 13, // tri2
                      11, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 11, // tri0
                      12, 16, 17, // tri1
                      12, 11, 16, // tri2
                      18, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 17, // tri0
                      20, 21, 22, // tri1
                      23, 24, 25, // tri2
                      24, 26, 25  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 29, // tri0
                      28, 30, 29, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c6_r1_2_v[184], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 6, 8, // tri0
                      7, 4, 6, // tri1
                      2, 4, 0, // tri2
                      2, 5, 4  // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 8,    // tri0
                      9, 10, 7,   // tri1
                      11, 12, 13, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      15, 18, 16, // tri1
                      18, 19, 16, // tri2
                      18, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(18, 21, 20, // tri0
                      21, 22, 20, // tri1
                      21, 23, 22, // tri2
                      21, 24, 23  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 23, // tri0
                      24, 11, 25, // tri1
                      11, 13, 25, // tri2
                      12, 26, 14  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 14, // tri0
                      9, 28, 10,  // tri1
                      28, 29, 10, // tri2
                      28, 30, 29  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c6_r1_2_v[216], 3, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c6_r1_2_v[219], 13, 0),
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
