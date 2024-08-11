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

static Vtx grd_s_c3_r1_2_v[] = {
#include "assets/field/bg/grd_s_c3_r1_2_v.inc"
};

extern Gfx grd_s_c3_r1_2_modelT[] = {
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
    gsSPVertex(&grd_s_c3_r1_2_v[237], 18, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      5, 6, 4, // tri1
                      5, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,   // tri0
                      9, 10, 8,  // tri1
                      9, 11, 10, // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      13, 14, 12, // tri1
                      13, 15, 14, // tri2
                      15, 16, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 16, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c3_r1_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c3_r1_2_v[223], 14, 0),
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
    gsSPVertex(&grd_s_c3_r1_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      5, 7, 8,   // tri1
                      9, 10, 11, // tri2
                      9, 12, 10  // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 7,  // tri0
                      11, 10, 13, // tri1
                      13, 8, 7,   // tri2
                      14, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 15, // tri0
                      14, 18, 17, // tri1
                      14, 19, 18, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 22, // tri0
                      23, 19, 22, // tri1
                      20, 24, 21, // tri2
                      20, 25, 24  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 28, // tri0
                      27, 29, 28, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c3_r1_2_v[30], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 1,   // tri0
                      8, 3, 1,   // tri1
                      3, 9, 2,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      13, 14, 15, // tri1
                      13, 10, 14, // tri2
                      16, 0, 17   // tri3
                      ),
    gsSPNTriangles_5b(16, 1, 0,  // tri0
                      18, 6, 19, // tri1
                      6, 20, 19, // tri2
                      21, 22, 23 // tri3
                      ),
    gsSPNTriangles_5b(21, 24, 22, // tri0
                      24, 25, 22, // tri1
                      26, 27, 28, // tri2
                      27, 29, 28  // tri3
                      ),
    gsSPVertex(&grd_s_c3_r1_2_v[60], 28, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      12, 13, 14, // tri1
                      6, 12, 14,  // tri2
                      15, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      21, 22, 23, // tri1
                      24, 22, 21, // tri2
                      25, 26, 27  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_r1_2_v[88], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 4, 8,   // tri0
                      5, 9, 10,  // tri1
                      9, 11, 12, // tri2
                      13, 7, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      15, 18, 19, // tri1
                      20, 19, 18, // tri2
                      21, 20, 18  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 21, // tri0
                      2, 24, 22,  // tri1
                      0, 25, 26,  // tri2
                      27, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(30, 27, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c3_r1_2_v[120], 10, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 8, 9, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c3_r1_2_v[130], 31, 0),
    gsSPNTrianglesInit_5b(37,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      7, 0, 6, // tri1
                      4, 8, 2, // tri2
                      8, 0, 2  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      10, 12, 11, // tri1
                      12, 13, 11, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      14, 16, 15, // tri1
                      16, 17, 15, // tri2
                      16, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 17, // tri0
                      3, 20, 4,   // tri1
                      3, 21, 20,  // tri2
                      18, 16, 22  // tri3
                      ),
    gsSPNTriangles_5b(16, 23, 22, // tri0
                      16, 24, 23, // tri1
                      16, 14, 24, // tri2
                      14, 12, 24  // tri3
                      ),
    gsSPNTriangles_5b(12, 25, 24, // tri0
                      12, 10, 25, // tri1
                      10, 26, 25, // tri2
                      10, 27, 26  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 26, // tri0
                      28, 29, 26, // tri1
                      28, 7, 29,  // tri2
                      28, 0, 7    // tri3
                      ),
    gsSPNTriangles_5b(4, 30, 5,  // tri0
                      4, 20, 30, // tri1
                      0, 28, 1,  // tri2
                      28, 27, 1  // tri3
                      ),
    gsSPNTriangles_5b(27, 9, 1,  // tri0
                      27, 10, 9, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_r1_2_v[161], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(3, 7, 4,   // tri0
                      7, 8, 4,   // tri1
                      9, 10, 11, // tri2
                      10, 8, 11  // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 14, // tri0
                      13, 15, 14, // tri1
                      16, 17, 18, // tri2
                      17, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 18, // tri0
                      21, 16, 18, // tri1
                      22, 23, 24, // tri2
                      23, 20, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 24, // tri0
                      26, 22, 24, // tri1
                      27, 28, 19, // tri2
                      17, 27, 19  // tri3
                      ),
    gsSPNTriangles_5b(23, 21, 20, // tri0
                      29, 26, 25, // tri1
                      30, 29, 25, // tri2
                      30, 25, 0   // tri3
                      ),
    gsSPNTriangles_5b(2, 30, 0, // tri0
                      31, 1, 0, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPVertex(&grd_s_c3_r1_2_v[193], 16, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 11, 12, // tri1
                      13, 10, 12, // tri2
                      2, 14, 15   // tri3
                      ),
    gsSPNTriangles_5b(0, 2, 15, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_r1_2_v[209], 14, 0),
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
