#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c5_r3_2_v[] = {
#include "assets/field/bg/grd_s_c5_r3_2_v.inc"
};

extern Gfx grd_s_c5_r3_2_modelT[] = {
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
    gsSPVertex(&grd_s_c5_r3_2_v[226], 15, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      4, 6, 5, // tri1
                      4, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,   // tri0
                      9, 10, 8,  // tri1
                      9, 11, 10, // tri2
                      9, 12, 11  // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      13, 14, 11, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c5_r3_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c5_r3_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 5, 8,   // tri0
                      9, 7, 10,  // tri1
                      11, 9, 12, // tri2
                      1, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 16, // tri0
                      7, 8, 10,   // tri1
                      1, 14, 2,   // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      21, 22, 23, // tri1
                      23, 24, 25, // tri2
                      24, 26, 25  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 28, // tri0
                      28, 29, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c5_r3_2_v[31], 15, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,    // tri0
                      9, 10, 11,  // tri1
                      12, 11, 13, // tri2
                      0, 14, 1    // tri3
                      ),
    gsSPNTriangles_5b(2, 1, 3, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c5_r3_2_v[46], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 4, 9,   // tri1
                      4, 6, 9,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      14, 16, 15, // tri1
                      16, 17, 15, // tri2
                      17, 18, 15  // tri3
                      ),
    gsSPNTriangles_5b(15, 19, 13, // tri0
                      20, 0, 18,  // tri1
                      21, 22, 23, // tri2
                      22, 24, 23  // tri3
                      ),
    gsSPNTriangles_5b(22, 2, 24,  // tri0
                      21, 25, 22, // tri1
                      26, 27, 28, // tri2
                      27, 29, 28  // tri3
                      ),
    gsSPVertex(&grd_s_c5_r3_2_v[76], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          3, 5, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 6, 5, // tri0
                      6, 7, 8, // tri1
                      7, 9, 8, // tri2
                      7, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      14, 15, 16, // tri1
                      17, 18, 19, // tri2
                      17, 20, 18  // tri3
                      ),
    gsSPNTriangles_5b(21, 20, 17, // tri0
                      9, 10, 22,  // tri1
                      9, 22, 23,  // tri2
                      6, 8, 5     // tri3
                      ),
    gsSPNTriangles_5b(1, 4, 2,    // tri0
                      24, 2, 25,  // tri1
                      24, 25, 26, // tri2
                      25, 27, 26  // tri3
                      ),
    gsSPNTriangles_5b(28, 26, 27, // tri0
                      29, 27, 30, // tri1
                      29, 30, 31, // tri2
                      27, 29, 28  // tri3
                      ),
    gsSPVertex(&grd_s_c5_r3_2_v[108], 29, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 2, 3  // tri2
                          ),
    gsSPNTriangles_5b(2, 4, 5, // tri0
                      4, 6, 5, // tri1
                      6, 7, 5, // tri2
                      7, 8, 5  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,    // tri0
                      7, 10, 9,   // tri1
                      11, 12, 13, // tri2
                      13, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 15, // tri0
                      17, 18, 19, // tri1
                      9, 10, 20,  // tri2
                      21, 20, 10  // tri3
                      ),
    gsSPNTriangles_5b(10, 22, 21, // tri0
                      22, 23, 21, // tri1
                      24, 21, 23, // tri2
                      24, 25, 21  // tri3
                      ),
    gsSPNTriangles_5b(24, 26, 25, // tri0
                      27, 26, 24, // tri1
                      28, 26, 27, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c5_r3_2_v[137], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 2, 6, // tri0
                      5, 0, 2, // tri1
                      3, 7, 4, // tri2
                      3, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(3, 9, 8,   // tri0
                      9, 10, 8,  // tri1
                      9, 11, 10, // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      13, 14, 12, // tri1
                      13, 15, 14, // tri2
                      13, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(13, 17, 16, // tri0
                      17, 18, 16, // tri1
                      17, 19, 18, // tri2
                      19, 20, 18  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      23, 24, 21, // tri1
                      23, 25, 24, // tri2
                      25, 26, 24  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 24, // tri0
                      26, 28, 27, // tri1
                      28, 29, 27, // tri2
                      28, 30, 29  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c5_r3_2_v[169], 11, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      5, 6, 4, // tri1
                      5, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 6,  // tri0
                      8, 10, 9, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c5_r3_2_v[180], 32, 0),
    gsSPNTrianglesInit_5b(38,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      5, 7, 8,  // tri1
                      6, 9, 10, // tri2
                      6, 10, 7  // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      12, 14, 13, // tri1
                      12, 15, 14, // tri2
                      12, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 17, // tri0
                      14, 18, 17, // tri1
                      14, 15, 18, // tri2
                      15, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 0, 2,  // tri0
                      17, 18, 0, // tri1
                      18, 20, 0, // tri2
                      18, 19, 20 // tri3
                      ),
    gsSPNTriangles_5b(0, 20, 3,  // tri0
                      20, 21, 3, // tri1
                      4, 5, 8,   // tri2
                      4, 3, 5    // tri3
                      ),
    gsSPNTriangles_5b(3, 22, 5,  // tri0
                      3, 21, 22, // tri1
                      5, 22, 9,  // tri2
                      5, 9, 6    // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      22, 24, 9,  // tri1
                      10, 25, 26, // tri2
                      10, 9, 25   // tri3
                      ),
    gsSPNTriangles_5b(9, 24, 25,  // tri0
                      24, 27, 25, // tri1
                      26, 25, 28, // tri2
                      25, 29, 28  // tri3
                      ),
    gsSPNTriangles_5b(25, 30, 29, // tri0
                      25, 27, 30, // tri1
                      28, 29, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c5_r3_2_v[212], 14, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(2, 5, 6, // tri0
                      2, 1, 5, // tri1
                      1, 7, 5, // tri2
                      1, 4, 7  // tri3
                      ),
    gsSPNTriangles_5b(6, 5, 8, // tri0
                      5, 9, 8, // tri1
                      5, 7, 9, // tri2
                      7, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(8, 11, 12, // tri0
                      8, 9, 11,  // tri1
                      9, 13, 11, // tri2
                      9, 10, 13  // tri3
                      ),
    gsSPEndDisplayList(),
};
