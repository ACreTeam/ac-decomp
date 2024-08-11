#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c4_r2_2_v[] = {
#include "assets/field/bg/grd_s_c4_r2_2_v.inc"
};

extern Gfx grd_s_c4_r2_2_modelT[] = {
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
    gsSPVertex(&grd_s_c4_r2_2_v[212], 12, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      5, 6, 4, // tri1
                      5, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 6,   // tri0
                      8, 10, 9,  // tri1
                      8, 11, 10, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c4_r2_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c4_r2_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          3, 5, 4  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      7, 9, 8,   // tri1
                      9, 10, 11, // tri2
                      5, 12, 13  // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 13, // tri0
                      15, 16, 14, // tri1
                      17, 18, 16, // tri2
                      18, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(19, 21, 20, // tri0
                      21, 22, 20, // tri1
                      22, 6, 8,   // tri2
                      23, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 28, // tri0
                      27, 23, 28, // tri1
                      29, 30, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c4_r2_2_v[32], 26, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 6, 8,    // tri0
                      10, 9, 11,  // tri1
                      12, 10, 13, // tri2
                      3, 14, 4    // tri3
                      ),
    gsSPNTriangles_5b(14, 12, 4,  // tri0
                      15, 16, 17, // tri1
                      16, 18, 19, // tri2
                      18, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 23, // tri0
                      22, 24, 25, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_r2_2_v[58], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          2, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(2, 5, 4, // tri0
                      2, 6, 5, // tri1
                      6, 7, 5, // tri2
                      6, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 7,   // tri0
                      8, 10, 9,  // tri1
                      10, 11, 9, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 12, // tri0
                      13, 14, 12, // tri1
                      13, 15, 14, // tri2
                      15, 16, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 16, // tri0
                      18, 19, 20, // tri1
                      20, 21, 18, // tri2
                      20, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 21, // tri0
                      22, 24, 23, // tri1
                      24, 25, 23, // tri2
                      25, 26, 23  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      27, 28, 26, // tri1
                      28, 29, 26, // tri2
                      29, 30, 26  // tri3
                      ),
    gsSPNTriangles_5b(29, 31, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c4_r2_2_v[90], 7, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      5, 6, 4, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_r2_2_v[97], 28, 0),
    gsSPNTrianglesInit_5b(32,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      5, 8, 6,   // tri1
                      8, 9, 6,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      13, 14, 11, // tri1
                      15, 16, 17, // tri2
                      15, 10, 16  // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 16, // tri0
                      5, 18, 8,   // tri1
                      5, 19, 18,  // tri2
                      9, 8, 0     // tri3
                      ),
    gsSPNTriangles_5b(8, 1, 0,   // tri0
                      8, 18, 1,  // tri1
                      18, 20, 1, // tri2
                      1, 21, 3   // tri3
                      ),
    gsSPNTriangles_5b(1, 20, 21, // tri0
                      4, 3, 17,  // tri1
                      3, 15, 17, // tri2
                      3, 21, 15  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 15, // tri0
                      15, 22, 10, // tri1
                      22, 23, 10, // tri2
                      10, 24, 13  // tri3
                      ),
    gsSPNTriangles_5b(10, 23, 24, // tri0
                      14, 25, 26, // tri1
                      14, 13, 25, // tri2
                      13, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(24, 27, 25, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_r2_2_v[125], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 9, 10,  // tri1
                      10, 11, 8, // tri2
                      12, 13, 9  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 13, // tri0
                      16, 17, 15, // tri1
                      17, 16, 18, // tri2
                      2, 19, 0    // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 0,  // tri0
                      19, 21, 20, // tri1
                      21, 22, 23, // tri2
                      22, 24, 23  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 23, // tri0
                      26, 27, 28, // tri1
                      27, 29, 30, // tri2
                      29, 7, 30   // tri3
                      ),
    gsSPVertex(&grd_s_c4_r2_2_v[156], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 7,   // tri0
                      3, 8, 7,   // tri1
                      9, 10, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 12, // tri0
                      15, 12, 14, // tri1
                      17, 18, 19, // tri2
                      17, 20, 18  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 17, // tri0
                      22, 23, 24, // tri1
                      24, 25, 26, // tri2
                      25, 27, 26  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 26, // tri0
                      26, 28, 29, // tri1
                      26, 29, 20, // tri2
                      2, 1, 30    // tri3
                      ),
    gsSPNTriangles_5b(1, 31, 30, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_s_c4_r2_2_v[188], 24, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          4, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 1, 5, // tri0
                      5, 6, 3, // tri1
                      6, 5, 7, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(8, 11, 12,  // tri0
                      13, 12, 11, // tri1
                      14, 13, 15, // tri2
                      16, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(9, 6, 10, // tri0
                      6, 7, 10, // tri1
                      6, 9, 17, // tri2
                      9, 18, 17 // tri3
                      ),
    gsSPNTriangles_5b(19, 18, 9,  // tri0
                      20, 21, 22, // tri1
                      20, 23, 21, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
