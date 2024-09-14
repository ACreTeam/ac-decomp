#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_r1_1_v[] = {
#include "assets/field/bg/grd_s_r1_1_v.inc"
};

extern Gfx grd_s_r1_1_modelT[] = {
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
    gsSPVertex(&grd_s_r1_1_v[175], 13, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
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
                      11, 12, 9  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r1_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r1_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      7, 8, 6, // tri1
                      8, 9, 6, // tri2
                      9, 4, 6  // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 12, // tri0
                      11, 13, 12, // tri1
                      1, 14, 15,  // tri2
                      1, 15, 2    // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 15, // tri0
                      17, 18, 19, // tri1
                      18, 20, 19, // tri2
                      12, 21, 10  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 10, // tri0
                      21, 23, 22, // tri1
                      5, 24, 7,   // tri2
                      24, 25, 7   // tri3
                      ),
    gsSPNTriangles_5b(18, 17, 26, // tri0
                      18, 3, 20,  // tri1
                      3, 0, 20,   // tri2
                      14, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(27, 29, 28, // tri0
                      27, 30, 29, // tri1
                      30, 31, 29, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      10, 12, 11, // tri1
                      13, 14, 15, // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      8, 19, 20,  // tri1
                      19, 13, 21, // tri2
                      19, 21, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 20, // tri0
                      8, 20, 23,  // tri1
                      24, 25, 26, // tri2
                      25, 27, 26  // tri3
                      ),
    gsSPNTriangles_5b(24, 23, 25, // tri0
                      25, 28, 27, // tri1
                      15, 16, 28, // tri2
                      29, 30, 31  // tri3
                      ),
    gsSPVertex(&grd_s_r1_1_v[64], 9, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5, // tri0
                      4, 8, 7, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r1_1_v[73], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,   // tri0
                      8, 9, 10,  // tri1
                      9, 5, 10,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      10, 14, 17, // tri1
                      18, 7, 19,  // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 11, 24, // tri0
                      23, 24, 21, // tri1
                      15, 20, 22, // tri2
                      25, 26, 27  // tri3
                      ),
    gsSPNTriangles_5b(0, 28, 29,  // tri0
                      26, 30, 31, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_1_v[105], 22, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 3, 7  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 6,   // tri0
                      8, 9, 6,   // tri1
                      9, 10, 11, // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      17, 14, 18, // tri1
                      19, 17, 18, // tri2
                      18, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 13, 21, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r1_1_v[127], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 0, 9,   // tri1
                      0, 10, 9,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(12, 1, 13,  // tri0
                      14, 15, 16, // tri1
                      15, 17, 16, // tri2
                      18, 11, 19  // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 19, // tri0
                      20, 18, 21, // tri1
                      18, 19, 21, // tri2
                      22, 14, 16  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 14, // tri0
                      22, 24, 23, // tri1
                      9, 25, 8,   // tri2
                      25, 26, 8   // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      28, 7, 29,  // tri1
                      7, 30, 29,  // tri2
                      30, 31, 29  // tri3
                      ),
    gsSPVertex(&grd_s_r1_1_v[159], 16, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 11, 12, // tri1
                      11, 13, 12, // tri2
                      11, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 13, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
