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

static Vtx grd_s_c7_r1_1_v[] = {
#include "assets/field/bg/grd_s_c7_r1_1_v.inc"
};

extern Gfx grd_s_c7_r1_1_modelT[] = {
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
    gsSPVertex(&grd_s_c7_r1_1_v[212], 16, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 2, // tri0
                      6, 7, 8, // tri1
                      6, 9, 7, // tri2
                      7, 4, 8  // tri3
                      ),
    gsSPNTriangles_5b(7, 5, 4,    // tri0
                      10, 11, 12, // tri1
                      10, 13, 11, // tri2
                      11, 1, 12   // tri3
                      ),
    gsSPNTriangles_5b(1, 0, 12,   // tri0
                      10, 14, 13, // tri1
                      14, 15, 13, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c7_r1_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c7_r1_1_v[198], 14, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 0, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 4, 7,   // tri0
                      8, 6, 9,   // tri1
                      10, 8, 11, // tri2
                      12, 10, 13 // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_r1_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 7, 6,   // tri0
                      8, 9, 10,  // tri1
                      9, 11, 10, // tri2
                      12, 8, 13  // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 12,   // tri0
                      14, 12, 13, // tri1
                      0, 2, 15,   // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 18, // tri0
                      20, 3, 21,  // tri1
                      16, 6, 7,   // tri2
                      7, 17, 16   // tri3
                      ),
    gsSPNTriangles_5b(17, 22, 23, // tri0
                      24, 3, 20,  // tri1
                      23, 19, 17, // tri2
                      5, 25, 3    // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 3,  // tri0
                      26, 27, 21, // tri1
                      26, 21, 3,  // tri2
                      28, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(29, 31, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c7_r1_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(6, 8, 9,   // tri0
                      6, 9, 10,  // tri1
                      6, 10, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 12, 14, // tri0
                      16, 17, 18, // tri1
                      16, 19, 17, // tri2
                      16, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      21, 24, 22, // tri1
                      22, 15, 23, // tri2
                      15, 14, 23  // tri3
                      ),
    gsSPNTriangles_5b(12, 25, 13, // tri0
                      12, 18, 25, // tri1
                      16, 26, 20, // tri2
                      19, 20, 27  // tri3
                      ),
    gsSPNTriangles_5b(25, 18, 17, // tri0
                      28, 29, 30, // tri1
                      29, 31, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c7_r1_1_v[64], 16, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(7, 6, 8,   // tri0
                      7, 8, 9,   // tri1
                      10, 9, 8,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 13, // tri0
                      11, 15, 12, // tri1
                      14, 12, 9,  // tri2
                      9, 10, 14   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_r1_1_v[80], 30, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 8, // tri0
                      4, 2, 7, // tri1
                      7, 9, 8, // tri2
                      4, 0, 2  // tri3
                      ),
    gsSPNTriangles_5b(0, 10, 1,   // tri0
                      11, 6, 12,  // tri1
                      10, 13, 14, // tri2
                      13, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      17, 19, 18, // tri1
                      8, 20, 21,  // tri2
                      20, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 22, // tri0
                      19, 24, 25, // tri1
                      24, 4, 25,  // tri2
                      4, 3, 25    // tri3
                      ),
    gsSPNTriangles_5b(26, 12, 27, // tri0
                      12, 6, 27,  // tri1
                      26, 28, 12, // tri2
                      8, 29, 20   // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 29,  // tri0
                      10, 14, 1, // tri1
                      11, 5, 6,  // tri2
                      19, 25, 18 // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_r1_1_v[110], 28, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 4, // tri1
                          5, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 5, 3,  // tri0
                      7, 8, 6,  // tri1
                      9, 10, 7, // tri2
                      11, 12, 9 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      11, 14, 13, // tri1
                      14, 15, 16, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      21, 22, 23, // tri1
                      23, 24, 25, // tri2
                      25, 26, 27  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c7_r1_1_v[138], 32, 0),
    gsSPNTrianglesInit_5b(37,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 4,  // tri0
                      6, 7, 8,  // tri1
                      6, 8, 9,  // tri2
                      7, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(7, 11, 8,  // tri0
                      9, 8, 12,  // tri1
                      8, 13, 12, // tri2
                      8, 11, 14  // tri3
                      ),
    gsSPNTriangles_5b(8, 14, 13,  // tri0
                      12, 13, 15, // tri1
                      13, 16, 15, // tri2
                      16, 17, 15  // tri3
                      ),
    gsSPNTriangles_5b(13, 18, 16, // tri0
                      13, 14, 18, // tri1
                      17, 19, 20, // tri2
                      17, 16, 19  // tri3
                      ),
    gsSPNTriangles_5b(16, 18, 21, // tri0
                      16, 21, 19, // tri1
                      20, 19, 22, // tri2
                      19, 23, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 22, // tri0
                      23, 25, 24, // tri1
                      19, 21, 26, // tri2
                      19, 26, 23  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 25, // tri0
                      26, 25, 23, // tri1
                      24, 25, 28, // tri2
                      25, 29, 28  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 30, // tri0
                      25, 30, 29, // tri1
                      28, 29, 1,  // tri2
                      29, 2, 1    // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 31, // tri0
                      29, 31, 2,  // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c7_r1_1_v[170], 14, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 4, 5, // tri0
                      6, 7, 8, // tri1
                      6, 5, 7, // tri2
                      5, 4, 9  // tri3
                      ),
    gsSPNTriangles_5b(5, 9, 7,   // tri0
                      8, 10, 11, // tri1
                      8, 7, 10,  // tri2
                      7, 12, 10  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 12,   // tri0
                      12, 13, 10, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c7_r1_1_v[184], 14, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,    // tri0
                      8, 5, 9,    // tri1
                      10, 11, 12, // tri2
                      11, 3, 13   // tri3
                      ),
    gsSPEndDisplayList(),
};
