#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c4_r3_2_v[] = {
#include "assets/field/bg/grd_s_c4_r3_2_v.inc"
};

extern Gfx grd_s_c4_r3_2_modelT[] = {
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
    gsSPVertex(&grd_s_c4_r3_2_v[199], 12, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          4, 3, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 2, 5, // tri0
                      6, 4, 5, // tri1
                      6, 5, 7, // tri2
                      8, 6, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 9,   // tri0
                      10, 11, 8, // tri1
                      10, 8, 9,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c4_r3_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c4_r3_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 0, 6, // tri0
                      0, 2, 6, // tri1
                      7, 8, 9, // tri2
                      8, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(11, 7, 12, // tri0
                      7, 13, 12, // tri1
                      3, 14, 4,  // tri2
                      15, 1, 16  // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 1,  // tri0
                      15, 18, 17, // tri1
                      18, 19, 17, // tri2
                      18, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 19, // tri0
                      8, 22, 23,  // tri1
                      22, 24, 23, // tri2
                      22, 25, 24  // tri3
                      ),
    gsSPNTriangles_5b(22, 26, 25, // tri0
                      1, 17, 3,   // tri1
                      21, 27, 19, // tri2
                      14, 28, 4   // tri3
                      ),
    gsSPNTriangles_5b(14, 29, 28, // tri0
                      29, 30, 28, // tri1
                      30, 31, 28, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c4_r3_2_v[32], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4,   // tri0
                      6, 7, 8,   // tri1
                      9, 10, 11, // tri2
                      9, 12, 10  // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      14, 12, 15, // tri1
                      14, 10, 12, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 17, // tri0
                      21, 22, 23, // tri1
                      21, 24, 22, // tri2
                      21, 25, 24  // tri3
                      ),
    gsSPNTriangles_5b(22, 26, 23, // tri0
                      26, 27, 23, // tri1
                      26, 28, 27, // tri2
                      28, 29, 27  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 27, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c4_r3_2_v[63], 19, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 11, 12, // tri1
                      13, 14, 15, // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(3, 17, 18, // tri0
                      2, 3, 18,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_r3_2_v[82], 32, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 5, 9,   // tri0
                      1, 10, 11, // tri1
                      10, 8, 12, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(13, 16, 14, // tri0
                      17, 18, 19, // tri1
                      20, 21, 22, // tri2
                      15, 20, 23  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 26, // tri0
                      27, 28, 29, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c4_r3_2_v[112], 23, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 1  // tri2
                          ),
    gsSPNTriangles_5b(6, 0, 2,   // tri0
                      7, 8, 9,   // tri1
                      10, 7, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      18, 15, 19, // tri1
                      13, 20, 21, // tri2
                      20, 18, 22  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_r3_2_v[135], 32, 0),
    gsSPNTrianglesInit_5b(38,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 3, // tri0
                      6, 7, 8, // tri1
                      7, 9, 8, // tri2
                      9, 4, 8  // tri3
                      ),
    gsSPNTriangles_5b(4, 10, 8,   // tri0
                      4, 2, 10,   // tri1
                      11, 12, 13, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(6, 12, 7,   // tri0
                      6, 15, 12,  // tri1
                      15, 16, 12, // tri2
                      16, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 14, // tri0
                      17, 18, 14, // tri1
                      17, 19, 18, // tri2
                      11, 7, 12   // tri3
                      ),
    gsSPNTriangles_5b(11, 20, 7,  // tri0
                      21, 19, 22, // tri1
                      21, 18, 19, // tri2
                      5, 23, 3    // tri3
                      ),
    gsSPNTriangles_5b(5, 24, 23,  // tri0
                      21, 25, 18, // tri1
                      25, 26, 18, // tri2
                      26, 13, 18  // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 18, // tri0
                      20, 27, 7,  // tri1
                      27, 9, 7,   // tri2
                      27, 4, 9    // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 4, // tri0
                      28, 29, 4, // tri1
                      29, 0, 4,  // tri2
                      29, 5, 0   // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 5, // tri0
                      30, 31, 5, // tri1
                      31, 24, 5, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_r3_2_v[167], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 1, // tri0
                      6, 4, 3, // tri1
                      7, 8, 9, // tri2
                      8, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 9,  // tri0
                      10, 12, 11, // tri1
                      12, 13, 11, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 13, // tri0
                      14, 16, 15, // tri1
                      16, 17, 15, // tri2
                      16, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(16, 19, 18, // tri0
                      19, 20, 18, // tri1
                      20, 21, 18, // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(23, 25, 24, // tri0
                      25, 5, 0,   // tri1
                      25, 0, 24,  // tri2
                      6, 26, 4    // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 4,  // tri0
                      26, 28, 27, // tri1
                      28, 29, 27, // tri2
                      28, 30, 29  // tri3
                      ),
    gsSPNTriangles_5b(22, 31, 23, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
