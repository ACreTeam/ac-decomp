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

static Vtx grd_s_r2_p_1_v[] = {
#include "assets/field/bg/grd_s_r2_p_1_v.inc"
};

extern Gfx grd_s_r2_p_1_modelT[] = {
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
    gsSPVertex(&grd_s_r2_p_1_v[321], 19, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 2, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      10, 7, 9,  // tri1
                      11, 3, 12, // tri2
                      11, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(8, 11, 12, // tri0
                      8, 12, 9,  // tri1
                      13, 0, 6,  // tri2
                      11, 15, 13 // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      3, 5, 12,   // tri1
                      13, 6, 14,  // tri2
                      16, 12, 17  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r2_p_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bridge_2_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bridge_2_tex_dummy, G_IM_FMT_CI, 128, 32, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r2_p_1_v[277], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2,   // tri0
                      6, 7, 8,   // tri1
                      6, 8, 9,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 13, // tri0
                      13, 12, 14, // tri1
                      13, 14, 15, // tri2
                      12, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(12, 17, 14, // tri0
                      18, 19, 20, // tri1
                      18, 20, 21, // tri2
                      22, 18, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 21, 23, // tri0
                      24, 25, 18, // tri1
                      24, 18, 22, // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(26, 28, 29, // tri0
                      29, 28, 30, // tri1
                      29, 30, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r2_p_1_v[309], 12, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,  // tri0
                      8, 4, 7,  // tri1
                      8, 7, 9,  // tri2
                      10, 11, 4 // tri3
                      ),
    gsSPNTriangles_5b(10, 4, 8, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r2_p_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 4,    // tri0
                      9, 0, 3,    // tri1
                      10, 11, 12, // tri2
                      13, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      19, 20, 12, // tri1
                      21, 22, 23, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(27, 15, 14, // tri0
                      26, 25, 28, // tri1
                      26, 29, 24, // tri2
                      30, 21, 26  // tri3
                      ),
    gsSPNTriangles_5b(11, 19, 12, // tri0
                      16, 31, 17, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r2_p_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(3, 9, 10,   // tri0
                      11, 12, 13, // tri1
                      7, 6, 14,   // tri2
                      15, 11, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      20, 21, 22, // tri1
                      18, 23, 19, // tri2
                      24, 25, 15  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 28, // tri0
                      29, 30, 31, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r2_p_1_v[64], 31, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      12, 13, 14, // tri1
                      15, 16, 9,  // tri2
                      1, 5, 2     // tri3
                      ),
    gsSPNTriangles_5b(17, 12, 18, // tri0
                      9, 19, 20,  // tri1
                      21, 22, 23, // tri2
                      24, 12, 14  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 27, // tri0
                      28, 29, 16, // tri1
                      23, 30, 6,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r2_p_1_v[95], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(1, 9, 10,   // tri0
                      11, 12, 13, // tri1
                      12, 14, 13, // tri2
                      1, 0, 9     // tri3
                      ),
    gsSPNTriangles_5b(15, 11, 16, // tri0
                      17, 15, 16, // tri1
                      7, 18, 8,   // tri2
                      3, 8, 18    // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 6,  // tri0
                      10, 21, 19, // tri1
                      2, 22, 23,  // tri2
                      24, 17, 25  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 28, // tri0
                      14, 26, 29, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r2_p_1_v[125], 11, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 3, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,  // tri0
                      8, 6, 10, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r2_p_1_v[136], 32, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,    // tri0
                      8, 9, 10,   // tri1
                      11, 12, 13, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 16, // tri0
                      17, 18, 19, // tri1
                      20, 21, 22, // tri2
                      23, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 7,  // tri0
                      24, 28, 29, // tri1
                      24, 29, 30, // tri2
                      24, 30, 25  // tri3
                      ),
    gsSPVertex(&grd_s_r2_p_1_v[167], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      10, 1, 11, // tri1
                      10, 2, 1,  // tri2
                      12, 7, 9   // tri3
                      ),
    gsSPNTriangles_5b(13, 11, 14, // tri0
                      11, 1, 14,  // tri1
                      15, 16, 17, // tri2
                      15, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      0, 14, 1,   // tri1
                      0, 22, 14,  // tri2
                      5, 6, 23    // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 26, // tri0
                      24, 26, 27, // tri1
                      28, 29, 30, // tri2
                      28, 30, 23  // tri3
                      ),
    gsSPNTriangles_5b(31, 21, 20, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r2_p_1_v[199], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      7, 10, 8,  // tri1
                      11, 12, 2, // tri2
                      11, 2, 1   // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      13, 15, 16, // tri1
                      17, 18, 19, // tri2
                      18, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 16, // tri0
                      21, 16, 23, // tri1
                      24, 25, 0,  // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 4, 3,  // tri0
                      30, 8, 10, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_s_r2_p_1_v[230], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 1, 0, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(0, 4, 3, // tri0
                      4, 6, 3, // tri1
                      7, 8, 9, // tri2
                      7, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      11, 13, 14, // tri1
                      12, 15, 16, // tri2
                      12, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(15, 18, 19, // tri0
                      15, 19, 20, // tri1
                      21, 22, 23, // tri2
                      22, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(22, 25, 23, // tri0
                      26, 27, 28, // tri1
                      27, 26, 29, // tri2
                      29, 30, 27  // tri3
                      ),
    gsSPNTriangles_5b(29, 31, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r2_p_1_v[262], 15, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      8, 6, 9,    // tri1
                      10, 11, 12, // tri2
                      10, 13, 11  // tri3
                      ),
    gsSPNTriangles_5b(10, 14, 13, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
