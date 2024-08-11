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

static Vtx grd_s_c4_r3_1_v[] = {
#include "assets/field/bg/grd_s_c4_r3_1_v.inc"
};

extern Gfx grd_s_c4_r3_1_modelT[] = {
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
    gsSPVertex(&grd_s_c4_r3_1_v[213], 13, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 0, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 5, // tri0
                      4, 5, 6, // tri1
                      7, 4, 6, // tri2
                      7, 6, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 8,   // tri0
                      9, 8, 10,  // tri1
                      11, 12, 9, // tri2
                      11, 9, 10  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c4_r3_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c4_r3_1_v[202], 11, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 5, 8,  // tri0
                      9, 7, 10, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_r3_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 2,    // tri0
                      7, 8, 9,    // tri1
                      10, 11, 12, // tri2
                      11, 13, 12  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      15, 17, 16, // tri1
                      17, 18, 16, // tri2
                      17, 0, 18   // tri3
                      ),
    gsSPNTriangles_5b(0, 19, 18,  // tri0
                      20, 21, 22, // tri1
                      23, 22, 21, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      25, 28, 27, // tri1
                      29, 30, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c4_r3_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,  // tri0
                      8, 9, 10, // tri1
                      8, 11, 9, // tri2
                      4, 10, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 9, 12,  // tri0
                      11, 13, 14, // tri1
                      13, 6, 14,  // tri2
                      8, 13, 11   // tri3
                      ),
    gsSPNTriangles_5b(7, 14, 6,  // tri0
                      15, 16, 9, // tri1
                      16, 12, 9, // tri2
                      17, 14, 7  // tri3
                      ),
    gsSPNTriangles_5b(5, 18, 7,  // tri0
                      18, 5, 19, // tri1
                      19, 5, 20, // tri2
                      21, 22, 23 // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 26, // tri0
                      3, 27, 2,   // tri1
                      3, 28, 27,  // tri2
                      27, 29, 2   // tri3
                      ),
    gsSPVertex(&grd_s_c4_r3_1_v[62], 19, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 6,  // tri0
                      7, 8, 6,  // tri1
                      1, 9, 2,  // tri2
                      10, 11, 0 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 0, // tri0
                      0, 2, 10,  // tri1
                      13, 10, 2, // tri2
                      14, 13, 15 // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 11, // tri0
                      17, 12, 11, // tri1
                      15, 16, 14, // tri2
                      15, 18, 16  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c4_r3_1_v[81], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 5, // tri0
                      0, 6, 5, // tri1
                      6, 7, 5, // tri2
                      6, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 7,    // tri0
                      10, 11, 12, // tri1
                      11, 13, 12, // tri2
                      14, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 15, // tri0
                      18, 10, 12, // tri1
                      18, 19, 10, // tri2
                      20, 17, 14  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 17, // tri0
                      22, 3, 2,   // tri1
                      22, 23, 3,  // tri2
                      11, 23, 13  // tri3
                      ),
    gsSPNTriangles_5b(23, 22, 13, // tri0
                      15, 24, 16, // tri1
                      24, 25, 16, // tri2
                      26, 25, 27  // tri3
                      ),
    gsSPNTriangles_5b(25, 24, 27, // tri0
                      28, 26, 27, // tri1
                      28, 29, 26, // tri2
                      28, 30, 29  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c4_r3_1_v[113], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_r3_1_v[117], 32, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          4, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4,  // tri0
                      6, 7, 5,  // tri1
                      8, 9, 6,  // tri2
                      10, 11, 8 // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 11, // tri0
                      12, 13, 14, // tri1
                      13, 15, 14, // tri2
                      14, 11, 12  // tri3
                      ),
    gsSPNTriangles_5b(11, 9, 8,  // tri0
                      9, 7, 6,   // tri1
                      7, 4, 5,   // tri2
                      16, 17, 18 // tri3
                      ),
    gsSPNTriangles_5b(16, 19, 17, // tri0
                      16, 20, 19, // tri1
                      16, 21, 20, // tri2
                      21, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 22, // tri0
                      22, 21, 23, // tri1
                      23, 25, 24, // tri2
                      26, 27, 25  // tri3
                      ),
    gsSPNTriangles_5b(26, 25, 23, // tri0
                      26, 28, 27, // tri1
                      26, 29, 28, // tri2
                      30, 31, 29  // tri3
                      ),
    gsSPVertex(&grd_s_c4_r3_1_v[149], 5, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_r3_1_v[154], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(7, 3, 8,    // tri0
                      9, 10, 11,  // tri1
                      12, 13, 14, // tri2
                      15, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(18, 0, 19,  // tri0
                      18, 19, 16, // tri1
                      20, 21, 22, // tri2
                      21, 6, 22   // tri3
                      ),
    gsSPNTriangles_5b(4, 15, 17,  // tri0
                      12, 23, 13, // tri1
                      20, 22, 24, // tri2
                      23, 20, 24  // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 14, // tri0
                      25, 26, 27, // tri1
                      27, 28, 29, // tri2
                      29, 30, 31  // tri3
                      ),
    gsSPVertex(&grd_s_c4_r3_1_v[186], 5, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c4_r3_1_v[191], 11, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,  // tri0
                      8, 3, 10, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};
