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

static Vtx grd_s_r5_p_1_v[] = {
#include "assets/field/bg/grd_s_r5_p_1_v.inc"
};

extern Gfx grd_s_r5_p_1_modelT[] = {
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
    gsSPVertex(&grd_s_r5_p_1_v[255], 23, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 1,  // tri0
                      6, 7, 8,  // tri1
                      9, 6, 8,  // tri2
                      10, 11, 4 // tri3
                      ),
    gsSPNTriangles_5b(12, 10, 4, // tri0
                      8, 12, 4,  // tri1
                      9, 8, 4,   // tri2
                      13, 9, 4   // tri3
                      ),
    gsSPNTriangles_5b(4, 11, 14, // tri0
                      4, 14, 3,  // tri1
                      0, 2, 15,  // tri2
                      0, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(0, 16, 17, // tri0
                      0, 17, 18, // tri1
                      0, 18, 19, // tri2
                      20, 0, 19  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 20, // tri0
                      21, 20, 19, // tri1
                      13, 4, 5,   // tri2
                      0, 20, 1    // tri3
                      ),
    gsSPNTriangles_5b(5, 1, 20, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r5_p_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bridge_2_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bridge_2_tex_dummy, G_IM_FMT_CI, 128, 32, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r5_p_1_v[211], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1,   // tri0
                      6, 7, 8,   // tri1
                      7, 9, 8,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      14, 15, 10, // tri1
                      15, 13, 10, // tri2
                      15, 16, 13  // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 16, // tri0
                      18, 19, 20, // tri1
                      18, 21, 19, // tri2
                      22, 18, 23  // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 23, // tri0
                      23, 24, 25, // tri1
                      23, 20, 24, // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(26, 29, 27, // tri0
                      30, 31, 26, // tri1
                      31, 29, 26, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r5_p_1_v[243], 12, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,  // tri0
                      8, 4, 9,  // tri1
                      4, 6, 9,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(9, 6, 10, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r5_p_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5, // tri0
                      5, 8, 6, // tri1
                      0, 2, 9, // tri2
                      2, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(0, 11, 1,   // tri0
                      12, 13, 14, // tri1
                      13, 15, 14, // tri2
                      15, 16, 14  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 14, // tri0
                      15, 18, 16, // tri1
                      19, 20, 21, // tri2
                      20, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 21, // tri0
                      24, 25, 26, // tri1
                      25, 27, 26, // tri2
                      26, 28, 24  // tri3
                      ),
    gsSPNTriangles_5b(24, 28, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r5_p_1_v[30], 32, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      6, 7, 8, // tri1
                      7, 9, 8, // tri2
                      7, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 9,  // tri0
                      10, 12, 11, // tri1
                      11, 5, 9,   // tri2
                      5, 11, 4    // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 2,  // tri0
                      13, 15, 14, // tri1
                      13, 16, 15, // tri2
                      13, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 16, // tri0
                      17, 19, 18, // tri1
                      19, 20, 18, // tri2
                      19, 12, 20  // tri3
                      ),
    gsSPNTriangles_5b(14, 21, 2,  // tri0
                      21, 0, 2,   // tri1
                      14, 22, 21, // tri2
                      22, 23, 21  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 21, // tri0
                      23, 25, 24, // tri1
                      26, 27, 28, // tri2
                      27, 29, 28  // tri3
                      ),
    gsSPVertex(&grd_s_r5_p_1_v[60], 5, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r5_p_1_v[65], 17, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
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
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r5_p_1_v[82], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      5, 8, 6, // tri1
                      6, 9, 7, // tri2
                      6, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      12, 14, 13, // tri1
                      12, 15, 14, // tri2
                      12, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      20, 19, 18, // tri1
                      20, 21, 19, // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(23, 25, 24, // tri0
                      24, 26, 22, // tri1
                      26, 27, 22, // tri2
                      24, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 28, // tri0
                      30, 26, 29, // tri1
                      26, 24, 29, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r5_p_1_v[113], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4, // tri0
                      6, 7, 1, // tri1
                      7, 5, 1, // tri2
                      6, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(3, 6, 1,    // tri0
                      9, 10, 11,  // tri1
                      12, 11, 13, // tri2
                      12, 9, 11   // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      14, 17, 15, // tri1
                      18, 19, 16, // tri2
                      19, 14, 16  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 9,  // tri0
                      21, 22, 9,  // tri1
                      21, 23, 22, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(24, 27, 25, // tri0
                      27, 28, 25, // tri1
                      24, 26, 29, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r5_p_1_v[143], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 6,  // tri0
                      5, 7, 6,  // tri1
                      8, 9, 10, // tri2
                      9, 11, 10 // tri3
                      ),
    gsSPNTriangles_5b(9, 12, 11,  // tri0
                      13, 14, 15, // tri1
                      14, 16, 15, // tri2
                      16, 12, 15  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      18, 16, 19, // tri1
                      18, 20, 16, // tri2
                      21, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(22, 20, 23, // tri0
                      22, 24, 20, // tri1
                      25, 26, 27, // tri2
                      26, 28, 27  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 27, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r5_p_1_v[173], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      6, 8, 7,  // tri1
                      8, 4, 7,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 8, 11,  // tri0
                      10, 12, 8,  // tri1
                      13, 14, 15, // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 12, 15, // tri0
                      17, 18, 19, // tri1
                      18, 20, 19, // tri2
                      20, 16, 19  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      22, 24, 23, // tri1
                      24, 25, 23, // tri2
                      25, 26, 23  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 29, // tri0
                      30, 27, 29, // tri1
                      30, 31, 27, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r5_p_1_v[205], 6, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};
