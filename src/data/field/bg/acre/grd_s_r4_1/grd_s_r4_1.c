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
extern u8 earth_tex_dummy[];

static Vtx grd_s_r4_1_v[] = {
#include "assets/field/bg/grd_s_r4_1_v.inc"
};

extern Gfx grd_s_r4_1_modelT[] = {
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
    gsSPVertex(&grd_s_r4_1_v[189], 13, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          2, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 0, // tri0
                      6, 7, 1, // tri1
                      7, 8, 1, // tri2
                      8, 9, 1  // tri3
                      ),
    gsSPNTriangles_5b(9, 3, 1,   // tri0
                      4, 10, 5,  // tri1
                      10, 11, 5, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r4_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r4_1_v[172], 17, 0),
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
    gsSPVertex(&grd_s_r4_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 7, // tri0
                      7, 0, 2, // tri1
                      8, 1, 9, // tri2
                      0, 9, 1  // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 3,  // tri0
                      3, 11, 12,  // tri1
                      13, 12, 11, // tri2
                      14, 12, 13  // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 15, // tri0
                      16, 15, 14, // tri1
                      17, 15, 16, // tri2
                      18, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(19, 21, 20, // tri0
                      22, 8, 21,  // tri1
                      8, 23, 21,  // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      25, 28, 27, // tri1
                      25, 29, 28, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r4_1_v[30], 32, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      8, 5, 9,   // tri1
                      10, 9, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      17, 16, 18, // tri1
                      12, 19, 20, // tri2
                      20, 13, 12  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 13, // tri0
                      22, 23, 24, // tri1
                      23, 25, 24, // tri2
                      23, 26, 27  // tri3
                      ),
    gsSPNTriangles_5b(26, 28, 27, // tri0
                      28, 29, 6,  // tri1
                      29, 30, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r4_1_v[62], 13, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(3, 9, 4,    // tri0
                      10, 11, 12, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r4_1_v[75], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 3, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,    // tri0
                      8, 6, 10,   // tri1
                      11, 12, 13, // tri2
                      14, 11, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      19, 20, 21, // tri1
                      22, 23, 20, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(25, 14, 26, // tri0
                      12, 19, 21, // tri1
                      16, 27, 17, // tri2
                      24, 26, 28  // tri3
                      ),
    gsSPNTriangles_5b(27, 29, 28, // tri0
                      29, 24, 28, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r4_1_v[105], 10, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 8, 9, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r4_1_v[115], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      4, 6, 5, // tri1
                      6, 7, 5, // tri2
                      7, 8, 5  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,   // tri0
                      9, 10, 8,  // tri1
                      10, 11, 8, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      13, 16, 14, // tri1
                      13, 17, 16, // tri2
                      13, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 17, // tri0
                      18, 20, 19, // tri1
                      20, 21, 19, // tri2
                      21, 22, 19  // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 22, // tri0
                      21, 24, 23, // tri1
                      21, 25, 24, // tri2
                      25, 26, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      27, 28, 26, // tri1
                      29, 30, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r4_1_v[147], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      4, 6, 5, // tri1
                      6, 7, 5, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r4_1_v[155], 17, 0),
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
