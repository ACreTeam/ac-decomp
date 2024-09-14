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

static Vtx grd_s_c4_r1_1_v[] = {
#include "assets/field/bg/grd_s_c4_r1_1_v.inc"
};

extern Gfx grd_s_c4_r1_1_modelT[] = {
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
    gsSPVertex(&grd_s_c4_r1_1_v[244], 12, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 2, 1, // tri0
                      0, 6, 3, // tri1
                      6, 7, 3, // tri2
                      5, 4, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 5, 8,   // tri0
                      10, 11, 9, // tri1
                      10, 9, 8,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c4_r1_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c4_r1_1_v[227], 17, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
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
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_r1_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      6, 8, 7, // tri1
                      8, 9, 7, // tri2
                      2, 4, 10 // tri3
                      ),
    gsSPNTriangles_5b(4, 11, 10,  // tri0
                      12, 13, 14, // tri1
                      14, 15, 12, // tri2
                      16, 12, 17  // tri3
                      ),
    gsSPNTriangles_5b(17, 12, 15, // tri0
                      18, 17, 19, // tri1
                      17, 15, 19, // tri2
                      13, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(21, 20, 22, // tri0
                      23, 24, 22, // tri1
                      23, 25, 24, // tri2
                      25, 26, 24  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c4_r1_1_v[30], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          3, 1, 0, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      3, 6, 5, // tri1
                      2, 7, 0, // tri2
                      2, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 7,    // tri0
                      9, 10, 7,   // tri1
                      11, 12, 13, // tri2
                      14, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 16, // tri0
                      18, 19, 20, // tri1
                      19, 21, 20, // tri2
                      22, 23, 2   // tri3
                      ),
    gsSPNTriangles_5b(23, 8, 2,   // tri0
                      22, 24, 23, // tri1
                      25, 12, 26, // tri2
                      25, 27, 12  // tri3
                      ),
    gsSPNTriangles_5b(22, 28, 24, // tri0
                      22, 29, 28, // tri1
                      29, 30, 28, // tri2
                      29, 31, 30  // tri3
                      ),
    gsSPVertex(&grd_s_c4_r1_1_v[62], 21, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          1, 6, 2  // tri2
                          ),
    gsSPNTriangles_5b(7, 4, 8,   // tri0
                      8, 3, 9,   // tri1
                      8, 4, 3,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 13, // tri0
                      10, 14, 11, // tri1
                      15, 16, 17, // tri2
                      18, 19, 20  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_r1_1_v[83], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      6, 8, 7,   // tri1
                      9, 10, 11, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(9, 13, 10,  // tri0
                      14, 15, 16, // tri1
                      15, 17, 16, // tri2
                      17, 18, 16  // tri3
                      ),
    gsSPNTriangles_5b(8, 19, 20,  // tri0
                      19, 21, 20, // tri1
                      8, 6, 19,   // tri2
                      1, 0, 22    // tri3
                      ),
    gsSPNTriangles_5b(0, 23, 22,  // tri0
                      23, 24, 22, // tri1
                      25, 24, 23, // tri2
                      15, 14, 26  // tri3
                      ),
    gsSPNTriangles_5b(14, 27, 26, // tri0
                      14, 28, 27, // tri1
                      29, 30, 31, // tri2
                      30, 13, 31  // tri3
                      ),
    gsSPVertex(&grd_s_c4_r1_1_v[115], 23, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      8, 3, 4,   // tri1
                      9, 10, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      8, 4, 18,   // tri1
                      14, 13, 19, // tri2
                      4, 20, 21   // tri3
                      ),
    gsSPNTriangles_5b(4, 21, 22, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_r1_1_v[138], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      7, 8, 9,   // tri1
                      9, 10, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      15, 14, 16, // tri1
                      18, 15, 17, // tri2
                      19, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 20, 19, // tri0
                      23, 22, 24, // tri1
                      25, 26, 24, // tri2
                      27, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(30, 29, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c4_r1_1_v[170], 17, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          5, 4, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,    // tri0
                      8, 9, 10,   // tri1
                      11, 12, 13, // tri2
                      10, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(10, 16, 14, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_r1_1_v[187], 23, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 4, // tri0
                      0, 6, 5, // tri1
                      7, 8, 9, // tri2
                      7, 2, 8  // tri3
                      ),
    gsSPNTriangles_5b(8, 10, 9,   // tri0
                      10, 11, 9,  // tri1
                      12, 11, 13, // tri2
                      11, 10, 13  // tri3
                      ),
    gsSPNTriangles_5b(14, 10, 15, // tri0
                      10, 8, 15,  // tri1
                      8, 3, 15,   // tri2
                      8, 2, 3     // tri3
                      ),
    gsSPNTriangles_5b(16, 13, 14, // tri0
                      13, 10, 14, // tri1
                      17, 0, 2,   // tri2
                      0, 17, 6    // tri3
                      ),
    gsSPNTriangles_5b(7, 17, 2,  // tri0
                      17, 18, 6, // tri1
                      19, 6, 18, // tri2
                      6, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(6, 19, 20,  // tri0
                      22, 19, 18, // tri1
                      6, 21, 5,   // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_r1_1_v[210], 17, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(4, 9, 10,   // tri0
                      11, 3, 12,  // tri1
                      13, 14, 15, // tri2
                      1, 11, 16   // tri3
                      ),
    gsSPNTriangles_5b(13, 6, 14,  // tri0
                      9, 13, 15,  // tri1
                      11, 12, 16, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
