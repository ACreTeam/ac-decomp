#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c1_r1_3_v[] = {
#include "assets/field/bg/grd_s_c1_r1_3_v.inc"
};

extern Gfx grd_s_c1_r1_3_modelT[] = {
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
    gsSPVertex(&grd_s_c1_r1_3_v[247], 27, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      6, 7, 8, // tri1
                      9, 6, 8, // tri2
                      4, 9, 8  // tri3
                      ),
    gsSPNTriangles_5b(4, 8, 5,    // tri0
                      10, 2, 11,  // tri1
                      10, 11, 12, // tri2
                      13, 14, 10  // tri3
                      ),
    gsSPNTriangles_5b(13, 10, 12, // tri0
                      3, 11, 2,   // tri1
                      15, 16, 17, // tri2
                      15, 18, 16  // tri3
                      ),
    gsSPNTriangles_5b(16, 19, 17, // tri0
                      16, 20, 19, // tri1
                      20, 21, 19, // tri2
                      21, 22, 19  // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 22, // tri0
                      23, 24, 22, // tri1
                      23, 25, 24, // tri2
                      23, 26, 25  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c1_r1_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c1_r1_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      5, 8, 7, // tri1
                      6, 9, 4, // tri2
                      9, 10, 4 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      11, 14, 12, // tri1
                      15, 16, 17, // tri2
                      16, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(15, 19, 16, // tri0
                      15, 20, 19, // tri1
                      18, 21, 22, // tri2
                      21, 23, 22  // tri3
                      ),
    gsSPNTriangles_5b(21, 24, 23, // tri0
                      18, 16, 21, // tri1
                      25, 26, 27, // tri2
                      26, 28, 27  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 27, // tri0
                      30, 31, 0,  // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r1_3_v[32], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      7, 8, 6, // tri1
                      7, 9, 8, // tri2
                      9, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      14, 15, 16, // tri1
                      17, 18, 19, // tri2
                      17, 20, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 21, 20, // tri0
                      21, 22, 20, // tri1
                      21, 23, 22, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 27, // tri0
                      27, 28, 24, // tri1
                      27, 13, 28, // tri2
                      29, 30, 31  // tri3
                      ),
    gsSPVertex(&grd_s_c1_r1_3_v[64], 19, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 0  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,  // tri0
                      7, 9, 8,  // tri1
                      7, 10, 9, // tri2
                      11, 12, 7 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 12, // tri0
                      15, 13, 12, // tri1
                      11, 15, 12, // tri2
                      16, 17, 11  // tri3
                      ),
    gsSPNTriangles_5b(17, 15, 11, // tri0
                      18, 0, 5,   // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_r1_3_v[83], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      8, 3, 9,   // tri1
                      8, 10, 3,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      9, 14, 17,  // tri1
                      18, 4, 19,  // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 11, 24, // tri0
                      23, 24, 21, // tri1
                      15, 20, 22, // tri2
                      25, 26, 27  // tri3
                      ),
    gsSPNTriangles_5b(28, 25, 29, // tri0
                      26, 30, 31, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r1_3_v[115], 24, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      7, 10, 11,  // tri1
                      12, 11, 10, // tri2
                      13, 12, 10  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 13, // tri0
                      16, 17, 14, // tri1
                      18, 19, 16, // tri2
                      18, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(18, 21, 20, // tri0
                      21, 22, 23, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c1_r1_3_v[139], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      4, 0, 5, // tri1
                      5, 8, 7, // tri2
                      9, 10, 5 // tri3
                      ),
    gsSPNTriangles_5b(10, 8, 5, // tri0
                      9, 5, 11, // tri1
                      5, 0, 11, // tri2
                      0, 2, 11  // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 14, // tri0
                      12, 15, 13, // tri1
                      15, 16, 13, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 19, // tri0
                      21, 22, 23, // tri1
                      21, 24, 22, // tri2
                      24, 25, 22  // tri3
                      ),
    gsSPNTriangles_5b(24, 17, 25, // tri0
                      17, 19, 25, // tri1
                      26, 15, 27, // tri2
                      18, 28, 20  // tri3
                      ),
    gsSPNTriangles_5b(18, 29, 28, // tri0
                      15, 8, 16,  // tri1
                      8, 10, 16,  // tri2
                      1, 30, 3    // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 3, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_s_c1_r1_3_v[171], 23, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4, // tri0
                      5, 6, 4, // tri1
                      6, 7, 4, // tri2
                      6, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 8,  // tri0
                      9, 11, 10, // tri1
                      6, 9, 8,   // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      13, 14, 15, // tri1
                      13, 16, 14, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(17, 20, 18, // tri0
                      20, 21, 18, // tri1
                      21, 22, 18, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c1_r1_3_v[194], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 3, 6, // tri0
                      5, 2, 3, // tri1
                      4, 6, 7, // tri2
                      6, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 7,    // tri0
                      10, 11, 12, // tri1
                      11, 13, 12, // tri2
                      11, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 13, // tri0
                      14, 16, 15, // tri1
                      14, 17, 16, // tri2
                      17, 18, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 18, // tri0
                      19, 20, 18, // tri1
                      19, 21, 20, // tri2
                      21, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(0, 23, 1,   // tri0
                      23, 24, 1,  // tri1
                      23, 25, 24, // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(27, 29, 28, // tri0
                      29, 30, 28, // tri1
                      29, 31, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c1_r1_3_v[226], 21, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 5,   // tri0
                      8, 9, 7,   // tri1
                      8, 10, 9,  // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 12, // tri0
                      13, 15, 14, // tri1
                      15, 16, 14, // tri2
                      17, 18, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 18, // tri0
                      19, 20, 18, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
