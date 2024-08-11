#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_r1_4_v[] = {
#include "assets/field/bg/grd_s_r1_4_v.inc"
};

extern Gfx grd_s_r1_4_modelT[] = {
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
    gsSPVertex(&grd_s_r1_4_v[158], 16, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4, // tri0
                      5, 6, 4, // tri1
                      5, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 6,   // tri0
                      8, 10, 9,  // tri1
                      10, 11, 9, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 12, // tri0
                      13, 14, 12, // tri1
                      14, 15, 12, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r1_4_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r1_4_v[0], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      9, 11, 10, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 14, // tri0
                      16, 17, 18, // tri1
                      17, 19, 18, // tri2
                      4, 14, 2    // tri3
                      ),
    gsSPNTriangles_5b(14, 20, 2,  // tri0
                      17, 21, 19, // tri1
                      22, 18, 23, // tri2
                      18, 19, 23  // tri3
                      ),
    gsSPNTriangles_5b(24, 0, 2,  // tri0
                      24, 25, 0, // tri1
                      25, 26, 0, // tri2
                      25, 23, 26 // tri3
                      ),
    gsSPNTriangles_5b(23, 19, 26, // tri0
                      23, 27, 22, // tri1
                      14, 15, 20, // tri2
                      15, 28, 20  // tri3
                      ),
    gsSPNTriangles_5b(15, 29, 28, // tri0
                      29, 30, 28, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_4_v[31], 28, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 6, // tri0
                      3, 5, 2, // tri1
                      0, 7, 1, // tri2
                      7, 8, 1  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,   // tri0
                      9, 10, 8,  // tri1
                      9, 11, 10, // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      16, 17, 18, // tri1
                      16, 19, 17, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 21, // tri0
                      23, 24, 21, // tri1
                      21, 25, 22, // tri2
                      24, 26, 21  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 22, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r1_4_v[59], 32, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 3, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 2, 3, // tri0
                      0, 6, 1, // tri1
                      7, 8, 9, // tri2
                      8, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 9,  // tri0
                      10, 12, 11, // tri1
                      7, 13, 8,   // tri2
                      5, 14, 4    // tri3
                      ),
    gsSPNTriangles_5b(12, 15, 11, // tri0
                      13, 16, 8,  // tri1
                      17, 18, 19, // tri2
                      17, 20, 18  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 18, // tri0
                      22, 23, 24, // tri1
                      22, 6, 23,  // tri2
                      6, 25, 23   // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 21, // tri0
                      22, 24, 21, // tri1
                      6, 0, 25,   // tri2
                      5, 26, 14   // tri3
                      ),
    gsSPNTriangles_5b(5, 27, 26,  // tri0
                      27, 28, 26, // tri1
                      27, 29, 28, // tri2
                      29, 30, 28  // tri3
                      ),
    gsSPVertex(&grd_s_r1_4_v[90], 15, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4, // tri0
                      5, 6, 4, // tri1
                      6, 7, 4, // tri2
                      6, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      9, 12, 10,  // tri1
                      12, 13, 10, // tri2
                      12, 14, 13  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r1_4_v[105], 32, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,   // tri0
                      8, 9, 4,   // tri1
                      8, 10, 9,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      14, 17, 15, // tri1
                      12, 16, 13, // tri2
                      18, 6, 19   // tri3
                      ),
    gsSPNTriangles_5b(8, 20, 21,  // tri0
                      20, 11, 22, // tri1
                      17, 23, 24, // tri2
                      25, 26, 27  // tri3
                      ),
    gsSPNTriangles_5b(28, 25, 29, // tri0
                      28, 29, 30, // tri1
                      28, 30, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_4_v[137], 21, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      9, 11, 12,  // tri1
                      13, 14, 15, // tri2
                      11, 13, 16  // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 18, // tri0
                      17, 19, 20, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
