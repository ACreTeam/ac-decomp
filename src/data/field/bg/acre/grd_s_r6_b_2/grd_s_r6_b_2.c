#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 bridge_2_pal_dummy[];
extern u8 bridge_2_tex_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_r6_b_2_v[] = {
#include "assets/field/bg/grd_s_r6_b_2_v.inc"
};

extern Gfx grd_s_r6_b_2_modelT[] = {
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
    gsSPVertex(&grd_s_r6_b_2_v[264], 27, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      6, 7, 8, // tri1
                      6, 5, 7, // tri2
                      5, 4, 7  // tri3
                      ),
    gsSPNTriangles_5b(3, 9, 10,   // tri0
                      3, 10, 2,   // tri1
                      11, 12, 10, // tri2
                      9, 11, 10   // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      13, 14, 12, // tri1
                      13, 15, 14, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(16, 19, 17, // tri0
                      20, 21, 22, // tri1
                      20, 22, 8,  // tri2
                      22, 6, 8    // tri3
                      ),
    gsSPNTriangles_5b(8, 23, 20,  // tri0
                      8, 24, 23,  // tri1
                      14, 16, 18, // tri2
                      14, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(18, 25, 14, // tri0
                      18, 26, 25, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r6_b_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bridge_2_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bridge_2_tex_dummy, G_IM_FMT_CI, 128, 32, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r6_b_2_v[186], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          2, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(2, 1, 4, // tri0
                      1, 6, 4, // tri1
                      6, 7, 4, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 10,  // tri0
                      12, 10, 13, // tri1
                      12, 8, 10,  // tri2
                      14, 8, 12   // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 8,  // tri0
                      16, 17, 18, // tri1
                      16, 19, 17, // tri2
                      18, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(18, 17, 20, // tri0
                      17, 22, 20, // tri1
                      22, 23, 20, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      28, 26, 29, // tri1
                      28, 24, 26, // tri2
                      30, 24, 28  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 24, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r6_b_2_v[218], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 2, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 2, // tri0
                      6, 7, 8, // tri1
                      6, 9, 7, // tri2
                      9, 10, 7 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 10,  // tri0
                      12, 13, 14, // tri1
                      12, 15, 13, // tri2
                      14, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(14, 13, 16, // tri0
                      13, 18, 16, // tri1
                      18, 19, 16, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 22, // tri0
                      24, 22, 25, // tri1
                      24, 20, 22, // tri2
                      26, 20, 24  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 20, // tri0
                      28, 29, 30, // tri1
                      28, 31, 29, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r6_b_2_v[250], 14, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1,  // tri0
                      6, 7, 8,  // tri1
                      7, 9, 8,  // tri2
                      10, 8, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 6, 8,  // tri0
                      12, 6, 10, // tri1
                      12, 13, 6, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r6_b_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      6, 7, 8, // tri1
                      7, 9, 8, // tri2
                      9, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 8, // tri0
                      12, 13, 8, // tri1
                      13, 14, 8, // tri2
                      14, 15, 8  // tri3
                      ),
    gsSPNTriangles_5b(15, 6, 8,   // tri0
                      16, 17, 18, // tri1
                      17, 19, 18, // tri2
                      19, 20, 18  // tri3
                      ),
    gsSPNTriangles_5b(11, 8, 10,  // tri0
                      21, 13, 22, // tri1
                      13, 23, 22, // tri2
                      23, 24, 22  // tri3
                      ),
    gsSPNTriangles_5b(21, 25, 26, // tri0
                      21, 22, 25, // tri1
                      25, 27, 26, // tri2
                      27, 16, 26  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 30, // tri0
                      29, 31, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r6_b_2_v[32], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,    // tri0
                      8, 9, 10,   // tri1
                      11, 12, 13, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(15, 9, 16, // tri0
                      15, 10, 9, // tri1
                      3, 17, 2,  // tri2
                      17, 18, 2  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 2,  // tri0
                      20, 21, 19, // tri1
                      22, 23, 24, // tri2
                      22, 25, 23  // tri3
                      ),
    gsSPNTriangles_5b(22, 26, 25, // tri0
                      22, 27, 26, // tri1
                      22, 28, 27, // tri2
                      29, 30, 31  // tri3
                      ),
    gsSPVertex(&grd_s_r6_b_2_v[64], 11, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r6_b_2_v[75], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      6, 8, 7,   // tri1
                      8, 9, 7,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 10, 14, // tri0
                      15, 16, 17, // tri1
                      18, 15, 19, // tri2
                      11, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(20, 18, 22, // tri0
                      23, 24, 9,  // tri1
                      25, 26, 27, // tri2
                      28, 5, 26   // tri3
                      ),
    gsSPNTriangles_5b(29, 4, 30,  // tri0
                      31, 30, 24, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r6_b_2_v[107], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 7, 9,   // tri1
                      7, 10, 9,  // tri2
                      11, 10, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 12, // tri0
                      14, 13, 15, // tri1
                      13, 16, 15, // tri2
                      17, 16, 18  // tri3
                      ),
    gsSPNTriangles_5b(16, 19, 18, // tri0
                      1, 20, 3,   // tri1
                      1, 21, 20,  // tri2
                      21, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 22, // tri0
                      23, 24, 22, // tri1
                      23, 25, 24, // tri2
                      25, 26, 24  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 29, // tri0
                      27, 30, 28, // tri1
                      27, 31, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r6_b_2_v[139], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
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
                      10, 11, 8, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      13, 14, 11, // tri1
                      13, 15, 14, // tri2
                      15, 16, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 16, // tri0
                      17, 18, 16, // tri1
                      19, 20, 21, // tri2
                      20, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 25, // tri0
                      26, 27, 28, // tri1
                      29, 30, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r6_b_2_v[171], 15, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      5, 8, 7, // tri1
                      8, 9, 7, // tri2
                      8, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(8, 11, 10,  // tri0
                      12, 13, 14, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
