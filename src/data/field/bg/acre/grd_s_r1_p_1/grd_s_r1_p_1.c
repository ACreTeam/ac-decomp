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

static Vtx grd_s_r1_p_1_v[] = {
#include "assets/field/bg/grd_s_r1_p_1_v.inc"
};

extern Gfx grd_s_r1_p_1_modelT[] = {
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
    gsSPVertex(&grd_s_r1_p_1_v[229], 22, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 0, 5  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 5, // tri0
                      6, 4, 7, // tri1
                      4, 5, 7, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 8, 10,  // tri0
                      12, 11, 10, // tri1
                      10, 9, 13,  // tri2
                      14, 12, 10  // tri3
                      ),
    gsSPNTriangles_5b(14, 10, 15, // tri0
                      7, 14, 15,  // tri1
                      6, 7, 15,   // tri2
                      16, 6, 15   // tri3
                      ),
    gsSPNTriangles_5b(17, 16, 15, // tri0
                      18, 17, 15, // tri1
                      18, 15, 10, // tri2
                      18, 10, 13  // tri3
                      ),
    gsSPNTriangles_5b(19, 18, 13, // tri0
                      19, 13, 20, // tri1
                      21, 19, 20, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r1_p_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bridge_2_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bridge_2_tex_dummy, G_IM_FMT_CI, 128, 32, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r1_p_1_v[191], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      6, 7, 8, // tri1
                      6, 8, 9, // tri2
                      9, 8, 10 // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11, // tri0
                      8, 12, 13, // tri1
                      8, 13, 10, // tri2
                      14, 15, 16 // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 17, // tri0
                      18, 14, 17, // tri1
                      18, 17, 19, // tri2
                      20, 21, 14  // tri3
                      ),
    gsSPNTriangles_5b(20, 14, 18, // tri0
                      22, 23, 24, // tri1
                      22, 24, 25, // tri2
                      25, 24, 26  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 27, // tri0
                      24, 28, 29, // tri1
                      24, 29, 26, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_p_1_v[221], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 0, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 5, // tri0
                      6, 7, 0, // tri1
                      6, 0, 4, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r1_p_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 0, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      4, 5, 8,  // tri1
                      9, 10, 1, // tri2
                      9, 11, 10 // tri3
                      ),
    gsSPNTriangles_5b(9, 12, 11,  // tri0
                      12, 13, 11, // tri1
                      14, 13, 15, // tri2
                      16, 14, 17  // tri3
                      ),
    gsSPNTriangles_5b(18, 16, 19, // tri0
                      19, 20, 18, // tri1
                      20, 21, 18, // tri2
                      22, 21, 23  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 22, // tri0
                      25, 22, 24, // tri1
                      25, 26, 22, // tri2
                      27, 26, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_p_1_v[32], 12, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10, // tri0
                      9, 0, 11, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r1_p_1_v[44], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 2, 6, // tri0
                      2, 3, 6, // tri1
                      7, 8, 9, // tri2
                      10, 9, 8 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 9,  // tri0
                      12, 13, 14, // tri1
                      13, 15, 14, // tri2
                      5, 16, 2    // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 2,  // tri0
                      18, 19, 20, // tri1
                      19, 21, 20, // tri2
                      19, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 20, // tri0
                      24, 25, 26, // tri1
                      25, 27, 26, // tri2
                      25, 28, 27  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_p_1_v[76], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          5, 0, 4  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,  // tri0
                      7, 9, 8,  // tri1
                      9, 10, 8, // tri2
                      7, 11, 9  // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 14, // tri0
                      14, 15, 12, // tri1
                      15, 1, 12,  // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      20, 21, 22, // tri1
                      21, 23, 22, // tri2
                      21, 18, 23  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 22, // tri0
                      6, 8, 25,   // tri1
                      26, 27, 28, // tri2
                      27, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(26, 29, 27, // tri0
                      29, 31, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_p_1_v[108], 28, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 5,   // tri0
                      5, 4, 7,   // tri1
                      9, 10, 11, // tri2
                      12, 13, 10 // tri3
                      ),
    gsSPNTriangles_5b(10, 9, 12,  // tri0
                      14, 15, 16, // tri1
                      15, 17, 16, // tri2
                      17, 13, 16  // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 16, // tri0
                      12, 16, 13, // tri1
                      18, 19, 20, // tri2
                      19, 21, 20  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      25, 26, 23, // tri1
                      23, 22, 25, // tri2
                      27, 14, 12  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r1_p_1_v[136], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      6, 8, 7,  // tri1
                      9, 10, 8, // tri2
                      10, 7, 8  // tri3
                      ),
    gsSPNTriangles_5b(5, 11, 6,   // tri0
                      12, 13, 14, // tri1
                      12, 15, 13, // tri2
                      12, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 15, // tri0
                      16, 0, 17,  // tri1
                      4, 18, 13,  // tri2
                      18, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(1, 19, 3,  // tri0
                      1, 20, 19, // tri1
                      1, 21, 20, // tri2
                      21, 22, 20 // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 22, // tri0
                      21, 24, 23, // tri1
                      21, 25, 24, // tri2
                      25, 26, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      28, 29, 30, // tri1
                      29, 31, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_p_1_v[168], 23, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          4, 5, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 0, // tri0
                      5, 7, 6, // tri1
                      5, 8, 7, // tri2
                      8, 9, 7  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 7,   // tri0
                      8, 11, 9,   // tri1
                      12, 13, 10, // tri2
                      14, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 16, // tri0
                      15, 18, 17, // tri1
                      15, 19, 18, // tri2
                      17, 20, 16  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 16, // tri0
                      20, 22, 21, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
