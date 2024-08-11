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

static Vtx grd_s_c7_3_v[] = {
#include "assets/field/bg/grd_s_c7_3_v.inc"
};

extern Gfx grd_s_c7_3_modelT[] = {
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
    gsSPVertex(&grd_s_c7_3_v[259], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 3, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 2, 3, // tri0
                      4, 6, 2, // tri1
                      1, 7, 3, // tri2
                      2, 8, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c7_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c7_3_v[241], 18, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      4, 6, 5, // tri1
                      7, 8, 9, // tri2
                      7, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(0, 11, 12,  // tri0
                      13, 6, 14,  // tri1
                      11, 10, 15, // tri2
                      8, 16, 17   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      8, 6, 9, // tri1
                      8, 7, 6, // tri2
                      8, 10, 7 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 7,  // tri0
                      12, 13, 14, // tri1
                      13, 15, 14, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(16, 19, 17, // tri0
                      8, 20, 10,  // tri1
                      21, 16, 22, // tri2
                      21, 19, 16  // tri3
                      ),
    gsSPNTriangles_5b(16, 23, 22, // tri0
                      24, 25, 22, // tri1
                      25, 26, 22, // tri2
                      22, 26, 21  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 21, // tri0
                      28, 29, 30, // tri1
                      29, 31, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c7_3_v[32], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      8, 10, 9,  // tri1
                      10, 11, 9, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 16, // tri0
                      1, 17, 2,   // tri1
                      18, 5, 19,  // tri2
                      5, 6, 20    // tri3
                      ),
    gsSPNTriangles_5b(4, 21, 22, // tri0
                      18, 23, 7, // tri1
                      0, 11, 10, // tri2
                      0, 15, 11  // tri3
                      ),
    gsSPNTriangles_5b(7, 23, 8,   // tri0
                      24, 25, 26, // tri1
                      25, 27, 26, // tri2
                      28, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(29, 31, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c7_3_v[64], 21, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      10, 12, 11, // tri1
                      12, 13, 11, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(12, 15, 14, // tri0
                      15, 16, 14, // tri1
                      17, 18, 19, // tri2
                      18, 20, 19  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_3_v[85], 32, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 3, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,   // tri0
                      8, 10, 11, // tri1
                      10, 6, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 12, 16, // tri0
                      13, 17, 18, // tri1
                      17, 19, 20, // tri2
                      21, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(22, 15, 24, // tri0
                      25, 26, 27, // tri1
                      28, 25, 29, // tri2
                      26, 30, 31  // tri3
                      ),
    gsSPVertex(&grd_s_c7_3_v[117], 21, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 5, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      1, 11, 12,  // tri1
                      13, 14, 15, // tri2
                      16, 17, 14  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      16, 18, 17, // tri1
                      11, 13, 15, // tri2
                      13, 16, 14  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_3_v[138], 32, 0),
    gsSPNTrianglesInit_5b(35,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      7, 8, 5,  // tri1
                      8, 9, 5,  // tri2
                      10, 11, 9 // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 11, // tri0
                      11, 5, 9,   // tri1
                      13, 14, 12, // tri2
                      14, 15, 12  // tri3
                      ),
    gsSPNTriangles_5b(15, 11, 12, // tri0
                      16, 13, 10, // tri1
                      13, 12, 10, // tri2
                      17, 7, 18   // tri3
                      ),
    gsSPNTriangles_5b(7, 6, 18,  // tri0
                      19, 0, 20, // tri1
                      0, 2, 20,  // tri2
                      7, 17, 8   // tri3
                      ),
    gsSPNTriangles_5b(17, 21, 8,  // tri0
                      17, 22, 21, // tri1
                      22, 23, 21, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      25, 4, 27,  // tri1
                      25, 2, 4,   // tri2
                      0, 28, 3    // tri3
                      ),
    gsSPNTriangles_5b(0, 22, 28,  // tri0
                      22, 17, 28, // tri1
                      17, 18, 28, // tri2
                      5, 29, 6    // tri3
                      ),
    gsSPNTriangles_5b(5, 15, 29,  // tri0
                      5, 11, 15,  // tri1
                      13, 30, 14, // tri2
                      13, 31, 30  // tri3
                      ),
    gsSPVertex(&grd_s_c7_3_v[170], 14, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4,   // tri0
                      6, 7, 8,   // tri1
                      6, 9, 7,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_3_v[184], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          5, 6, 3  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 5,   // tri0
                      9, 10, 7,  // tri1
                      9, 11, 10, // tri2
                      12, 11, 9  // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      14, 13, 12, // tri1
                      15, 16, 14, // tri2
                      17, 18, 15  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 17, // tri0
                      21, 22, 19, // tri1
                      23, 24, 21, // tri2
                      25, 26, 23  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      28, 27, 25, // tri1
                      29, 27, 28, // tri2
                      29, 30, 27  // tri3
                      ),
    gsSPNTriangles_5b(31, 30, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c7_3_v[216], 7, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          5, 6, 3  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_3_v[223], 18, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      4, 6, 5, // tri1
                      7, 8, 9, // tri2
                      7, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(11, 6, 12, // tri0
                      0, 13, 14, // tri1
                      8, 15, 16, // tri2
                      13, 10, 17 // tri3
                      ),
    gsSPEndDisplayList(),
};
