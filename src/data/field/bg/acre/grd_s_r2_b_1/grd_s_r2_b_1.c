#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 bridge_1_pal_dummy[];
extern u8 bridge_1_tex_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_r2_b_1_v[] = {
#include "assets/field/bg/grd_s_r2_b_1_v.inc"
};

extern Gfx grd_s_r2_b_1_modelT[] = {
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
    gsSPVertex(&grd_s_r2_b_1_v[270], 30, 0),
    gsSPNTrianglesInit_5b(31,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 2, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 8, 9,   // tri0
                      1, 10, 11, // tri1
                      12, 3, 11, // tri2
                      11, 2, 1   // tri3
                      ),
    gsSPNTriangles_5b(11, 3, 2,  // tri0
                      13, 0, 2,  // tri1
                      13, 14, 0, // tri2
                      13, 15, 14 // tri3
                      ),
    gsSPNTriangles_5b(13, 16, 15, // tri0
                      16, 17, 15, // tri1
                      16, 5, 17,  // tri2
                      16, 6, 5    // tri3
                      ),
    gsSPNTriangles_5b(4, 18, 2,   // tri0
                      4, 19, 18,  // tri1
                      19, 20, 18, // tri2
                      21, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(22, 18, 20, // tri0
                      21, 8, 22,  // tri1
                      8, 6, 22,   // tri2
                      6, 23, 7    // tri3
                      ),
    gsSPNTriangles_5b(6, 9, 23,  // tri0
                      23, 24, 7, // tri1
                      9, 25, 23, // tri2
                      23, 26, 24 // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 23, // tri0
                      23, 27, 26, // tri1
                      27, 28, 26, // tri2
                      27, 29, 28  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r2_b_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r2_b_1_v[229], 13, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 4, 6,    // tri0
                      9, 7, 10,   // tri1
                      11, 10, 12, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bridge_1_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bridge_1_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&grd_s_r2_b_1_v[242], 14, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          4, 1, 0  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      5, 6, 2, // tri1
                      7, 8, 9, // tri2
                      7, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 12, // tri0
                      11, 12, 13, // tri1
                      7, 10, 11,  // tri2
                      2, 6, 8     // tri3
                      ),
    gsSPNTriangles_5b(2, 8, 7,  // tri0
                      0, 2, 7,  // tri1
                      0, 7, 11, // tri2
                      3, 0, 11  // tri3
                      ),
    gsSPNTriangles_5b(3, 11, 13, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_s_r2_b_1_v[256], 14, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      4, 6, 7, // tri1
                      4, 7, 5, // tri2
                      5, 8, 2  // tri3
                      ),
    gsSPNTriangles_5b(2, 9, 3,  // tri0
                      2, 8, 9,  // tri1
                      5, 10, 8, // tri2
                      5, 7, 10  // tri3
                      ),
    gsSPNTriangles_5b(11, 6, 4,  // tri0
                      12, 11, 4, // tri1
                      13, 12, 1, // tri2
                      0, 13, 1   // tri3
                      ),
    gsSPNTriangles_5b(1, 12, 4, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r2_b_1_v[0], 13, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 7, 4,    // tri0
                      9, 10, 6,   // tri1
                      11, 12, 10, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r2_b_1_v[13], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 9, 10,  // tri1
                      11, 12, 9, // tri2
                      0, 2, 12   // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 3,  // tri0
                      15, 16, 14, // tri1
                      4, 6, 16,   // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 17, 21, // tri0
                      22, 23, 24, // tri1
                      23, 20, 25, // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 26, 30, // tri0
                      27, 22, 31, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r2_b_1_v[45], 16, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 0, 7,  // tri0
                      8, 9, 10, // tri1
                      1, 8, 11, // tri2
                      9, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 15, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r2_b_1_v[61], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      9, 10, 7,  // tri1
                      11, 12, 9, // tri2
                      13, 14, 11 // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 13, // tri0
                      17, 18, 15, // tri1
                      17, 19, 20, // tri2
                      18, 17, 20  // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 21, // tri0
                      16, 15, 18, // tri1
                      14, 13, 16, // tri2
                      12, 11, 14  // tri3
                      ),
    gsSPNTriangles_5b(10, 9, 22, // tri0
                      9, 12, 22, // tri1
                      8, 7, 10,  // tri2
                      4, 6, 8    // tri3
                      ),
    gsSPNTriangles_5b(23, 5, 4,   // tri0
                      24, 25, 26, // tri1
                      27, 28, 29, // tri2
                      30, 31, 29  // tri3
                      ),
    gsSPVertex(&grd_s_r2_b_1_v[93], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,   // tri0
                      8, 9, 10,  // tri1
                      11, 12, 9, // tri2
                      11, 13, 12 // tri3
                      ),
    gsSPNTriangles_5b(11, 14, 13, // tri0
                      15, 16, 14, // tri1
                      14, 16, 13, // tri2
                      15, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 16, // tri0
                      17, 19, 18, // tri1
                      20, 21, 19, // tri2
                      20, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      22, 24, 21, // tri1
                      21, 18, 19, // tri2
                      25, 26, 1   // tri3
                      ),
    gsSPNTriangles_5b(1, 0, 25,   // tri0
                      25, 27, 26, // tri1
                      28, 29, 27, // tri2
                      25, 28, 27  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 29, // tri0
                      29, 28, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r2_b_1_v[125], 10, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 4, // tri0
                      4, 3, 5, // tri1
                      7, 8, 9, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r2_b_1_v[135], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      6, 8, 7,   // tri1
                      9, 10, 11, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      14, 16, 15, // tri1
                      15, 17, 13, // tri2
                      17, 18, 13  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      19, 22, 20, // tri1
                      23, 21, 24, // tri2
                      21, 20, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 12, 26, // tri0
                      12, 27, 26, // tri1
                      28, 2, 4,   // tri2
                      29, 30, 31  // tri3
                      ),
    gsSPVertex(&grd_s_r2_b_1_v[167], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      8, 10, 9,  // tri1
                      8, 11, 10, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 14, // tri0
                      16, 17, 18, // tri1
                      16, 19, 17, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 21, // tri0
                      21, 24, 22, // tri1
                      20, 25, 23, // tri2
                      25, 26, 27  // tri3
                      ),
    gsSPNTriangles_5b(26, 28, 27, // tri0
                      26, 29, 28, // tri1
                      26, 30, 29, // tri2
                      26, 31, 30  // tri3
                      ),
    gsSPVertex(&grd_s_r2_b_1_v[199], 30, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 6, // tri0
                      4, 8, 7, // tri1
                      8, 9, 7, // tri2
                      9, 10, 7 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      12, 14, 13, // tri1
                      14, 15, 13, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 18, // tri0
                      19, 20, 18, // tri1
                      19, 21, 20, // tri2
                      21, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 22, // tri0
                      23, 24, 22, // tri1
                      25, 26, 27, // tri2
                      28, 29, 26  // tri3
                      ),
    gsSPEndDisplayList(),
};
