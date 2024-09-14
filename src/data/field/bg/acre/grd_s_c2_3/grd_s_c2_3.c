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

static Vtx grd_s_c2_3_v[] = {
#include "assets/field/bg/grd_s_c2_3_v.inc"
};

extern Gfx grd_s_c2_3_modelT[] = {
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
    gsSPVertex(&grd_s_c2_3_v[255], 9, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 2, // tri0
                      4, 6, 5, // tri1
                      6, 7, 5, // tri2
                      7, 8, 5  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c2_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c2_3_v[242], 13, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 5, 8,   // tri0
                      9, 7, 10,  // tri1
                      11, 9, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c2_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      7, 8, 6, // tri1
                      4, 6, 9, // tri2
                      7, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      11, 14, 12, // tri1
                      11, 15, 14, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 18, // tri0
                      20, 17, 21, // tri1
                      17, 22, 21, // tri2
                      23, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(23, 26, 24, // tri0
                      23, 20, 26, // tri1
                      24, 27, 25, // tri2
                      25, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 26, // tri0
                      25, 28, 9,  // tri1
                      28, 4, 9,   // tri2
                      29, 30, 31  // tri3
                      ),
    gsSPVertex(&grd_s_c2_3_v[32], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          3, 5, 4  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,  // tri0
                      6, 8, 9,  // tri1
                      8, 10, 9, // tri2
                      8, 11, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 10, // tri0
                      11, 13, 12, // tri1
                      11, 14, 13, // tri2
                      15, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(15, 18, 16, // tri0
                      18, 19, 16, // tri1
                      20, 21, 22, // tri2
                      23, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(23, 26, 24, // tri0
                      26, 27, 24, // tri1
                      28, 1, 29,  // tri2
                      1, 0, 29    // tri3
                      ),
    gsSPNTriangles_5b(3, 12, 5,   // tri0
                      12, 13, 5,  // tri1
                      30, 15, 31, // tri2
                      15, 17, 31  // tri3
                      ),
    gsSPVertex(&grd_s_c2_3_v[64], 30, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 2, 6,  // tri0
                      7, 8, 9,  // tri1
                      10, 7, 9, // tri2
                      9, 11, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 9, 12,  // tri0
                      11, 12, 13, // tri1
                      14, 13, 12, // tri2
                      15, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(15, 18, 16, // tri0
                      18, 19, 16, // tri1
                      20, 21, 22, // tri2
                      23, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 28, // tri0
                      29, 28, 27, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_3_v[94], 32, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(3, 8, 7, // tri0
                      9, 7, 6, // tri1
                      3, 5, 8, // tri2
                      0, 2, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      11, 14, 12, // tri1
                      15, 16, 11, // tri2
                      17, 18, 15  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 17, // tri0
                      19, 21, 20, // tri1
                      19, 22, 21, // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(13, 25, 26, // tri0
                      27, 28, 29, // tri1
                      30, 27, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c2_3_v[126], 22, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 8,    // tri0
                      9, 10, 11,  // tri1
                      12, 13, 14, // tri2
                      10, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      20, 17, 21, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c2_3_v[148], 32, 0),
    gsSPNTrianglesInit_5b(30,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5, // tri0
                      7, 8, 5, // tri1
                      7, 9, 8, // tri2
                      9, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      12, 14, 15, // tri1
                      14, 16, 15, // tri2
                      12, 15, 13  // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 16, // tri0
                      17, 18, 16, // tri1
                      17, 19, 18, // tri2
                      20, 12, 21  // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 21, // tri0
                      20, 14, 12, // tri1
                      20, 17, 14, // tri2
                      20, 22, 17  // tri3
                      ),
    gsSPNTriangles_5b(22, 19, 17, // tri0
                      3, 23, 2,   // tri1
                      24, 25, 1,  // tri2
                      25, 26, 1   // tri3
                      ),
    gsSPNTriangles_5b(1, 27, 24,  // tri0
                      1, 0, 27,   // tri1
                      27, 28, 24, // tri2
                      29, 24, 28  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 29, // tri0
                      31, 24, 29, // tri1
                      31, 25, 24, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c2_3_v[180], 27, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 6, // tri0
                      4, 8, 7, // tri1
                      8, 9, 7, // tri2
                      8, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      12, 14, 13, // tri1
                      12, 15, 14, // tri2
                      12, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 15, // tri0
                      17, 18, 15, // tri1
                      17, 19, 18, // tri2
                      17, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(6, 21, 22, // tri0
                      6, 7, 21,  // tri1
                      7, 9, 21,  // tri2
                      9, 23, 21  // tri3
                      ),
    gsSPNTriangles_5b(13, 24, 25, // tri0
                      13, 14, 24, // tri1
                      14, 26, 24, // tri2
                      14, 15, 26  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_3_v[207], 22, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 5,  // tri0
                      8, 9, 7,  // tri1
                      8, 10, 9, // tri2
                      10, 11, 9 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      14, 15, 13, // tri1
                      16, 17, 15, // tri2
                      18, 19, 17  // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 19, // tri0
                      2, 21, 0,   // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_3_v[229], 13, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 8,   // tri0
                      9, 10, 11, // tri1
                      10, 3, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};
