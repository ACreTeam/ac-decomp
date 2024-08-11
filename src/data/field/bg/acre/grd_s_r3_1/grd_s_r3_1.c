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
extern u8 earth_tex_dummy[];

static Vtx grd_s_r3_1_v[] = {
#include "assets/field/bg/grd_s_r3_1_v.inc"
};

extern Gfx grd_s_r3_1_modelT[] = {
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
    gsSPVertex(&grd_s_r3_1_v[206], 16, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      7, 0, 6, // tri1
                      0, 2, 6, // tri2
                      1, 8, 3  // tri3
                      ),
    gsSPNTriangles_5b(1, 9, 8,   // tri0
                      9, 10, 8,  // tri1
                      10, 11, 8, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      12, 14, 13, // tri1
                      14, 15, 13, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r3_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r3_1_v[176], 30, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 8,   // tri0
                      3, 4, 8,   // tri1
                      9, 10, 11, // tri2
                      12, 9, 11  // tri3
                      ),
    gsSPNTriangles_5b(1, 12, 13,  // tri0
                      9, 14, 10,  // tri1
                      14, 15, 16, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 17, 21, // tri0
                      22, 20, 23, // tri1
                      24, 22, 25, // tri2
                      26, 24, 27  // tri3
                      ),
    gsSPNTriangles_5b(28, 26, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r3_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5, // tri0
                      4, 8, 7, // tri1
                      4, 9, 8, // tri2
                      9, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(5, 11, 6,   // tri0
                      11, 12, 6,  // tri1
                      11, 13, 12, // tri2
                      0, 2, 14    // tri3
                      ),
    gsSPNTriangles_5b(2, 15, 14,  // tri0
                      16, 17, 18, // tri1
                      19, 20, 16, // tri2
                      18, 0, 14   // tri3
                      ),
    gsSPNTriangles_5b(3, 21, 2,   // tri0
                      3, 22, 21,  // tri1
                      22, 23, 21, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      27, 28, 26, // tri1
                      27, 29, 28, // tri2
                      24, 30, 25  // tri3
                      ),
    gsSPNTriangles_5b(24, 31, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r3_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 3, 5  // tri2
                          ),
    gsSPNTriangles_5b(3, 6, 5,   // tri0
                      3, 1, 6,   // tri1
                      7, 8, 9,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      13, 14, 12, // tri1
                      13, 15, 14, // tri2
                      13, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 15, // tri0
                      17, 18, 15, // tri1
                      19, 20, 21, // tri2
                      20, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(19, 23, 20, // tri0
                      23, 24, 20, // tri1
                      22, 25, 21, // tri2
                      25, 26, 21  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      28, 26, 29, // tri1
                      28, 4, 26,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r3_1_v[62], 10, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r3_1_v[72], 31, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 2  // tri2
                          ),
    gsSPNTriangles_5b(6, 8, 7,  // tri0
                      8, 9, 7,  // tri1
                      8, 10, 9, // tri2
                      5, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 12, 11, // tri0
                      14, 13, 11, // tri1
                      15, 16, 14, // tri2
                      10, 17, 15  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      21, 18, 22, // tri1
                      19, 23, 24, // tri2
                      23, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 29, // tri0
                      28, 21, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r3_1_v[103], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 2, // tri0
                      4, 6, 5, // tri1
                      4, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,   // tri0
                      7, 10, 9,  // tri1
                      10, 11, 9, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 12, // tri0
                      13, 14, 12, // tri1
                      13, 15, 14, // tri2
                      13, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 15, // tri0
                      16, 18, 17, // tri1
                      16, 19, 18, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 21, // tri0
                      21, 24, 22, // tri1
                      21, 25, 24, // tri2
                      25, 26, 24  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 24, // tri0
                      26, 28, 27, // tri1
                      28, 29, 27, // tri2
                      29, 30, 27  // tri3
                      ),
    gsSPNTriangles_5b(29, 31, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r3_1_v[135], 11, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      5, 6, 4, // tri1
                      6, 7, 4, // tri2
                      6, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 7,  // tri0
                      9, 10, 7, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r3_1_v[146], 30, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(4, 9, 10,   // tri0
                      11, 12, 13, // tri1
                      14, 11, 15, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(12, 16, 19, // tri0
                      20, 21, 22, // tri1
                      21, 14, 23, // tri2
                      24, 3, 25   // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 28, // tri0
                      1, 24, 29,  // tri1
                      26, 6, 27,  // tri2
                      9, 26, 28   // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
