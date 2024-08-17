#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 bridge_2_pal_dummy[];
extern u8 bridge_2_tex_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_r7_b_2_v[] = {
#include "assets/field/bg/grd_s_r7_b_2_v.inc"
};

extern Gfx grd_s_r7_b_2_modelT[] = {
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
    gsSPVertex(&grd_s_r7_b_2_v[273], 20, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      6, 8, 7, // tri1
                      5, 9, 6, // tri2
                      5, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(10, 2, 9, // tri0
                      2, 1, 9,  // tri1
                      0, 11, 4, // tri2
                      0, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      12, 14, 13, // tri1
                      14, 15, 13, // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 16, // tri0
                      17, 18, 16, // tri1
                      19, 16, 18, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r7_b_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r7_b_2_v[222], 13, 0),
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
    gsDPLoadTLUT_Dolphin(15, 16, 1, bridge_2_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bridge_2_tex_dummy, G_IM_FMT_CI, 128, 32, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r7_b_2_v[235], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      6, 7, 8, // tri1
                      6, 9, 7, // tri2
                      10, 9, 6 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 9, // tri0
                      11, 12, 9, // tri1
                      12, 13, 9, // tri2
                      14, 15, 16 // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 16, // tri0
                      18, 16, 19, // tri1
                      18, 14, 16, // tri2
                      19, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(19, 16, 20, // tri0
                      22, 23, 24, // tri1
                      22, 25, 23, // tri2
                      26, 25, 22  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 25, // tri0
                      27, 28, 25, // tri1
                      28, 29, 25, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r7_b_2_v[265], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 2, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 2, // tri0
                      5, 6, 7, // tri1
                      5, 2, 6, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r7_b_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 2, 1, // tri1
                          4, 2, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      6, 8, 7,   // tri1
                      7, 8, 9,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      14, 10, 15, // tri1
                      16, 17, 18, // tri2
                      19, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 19, 21, // tri0
                      23, 24, 25, // tri1
                      26, 27, 24, // tri2
                      28, 29, 27  // tri3
                      ),
    gsSPVertex(&grd_s_r7_b_2_v[30], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,   // tri0
                      7, 8, 9,   // tri1
                      7, 10, 8,  // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      10, 14, 11, // tri1
                      14, 15, 16, // tri2
                      15, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(0, 18, 1,   // tri0
                      19, 20, 21, // tri1
                      22, 23, 24, // tri2
                      23, 20, 24  // tri3
                      ),
    gsSPNTriangles_5b(22, 25, 23, // tri0
                      26, 27, 25, // tri1
                      28, 29, 6,  // tri2
                      30, 29, 28  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r7_b_2_v[62], 20, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          3, 5, 4  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      9, 10, 11, // tri1
                      6, 12, 7,  // tri2
                      11, 12, 6  // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 12, // tri0
                      10, 13, 12, // tri1
                      14, 15, 16, // tri2
                      17, 18, 19  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r7_b_2_v[82], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 6, 10,  // tri0
                      4, 11, 12, // tri1
                      11, 9, 13, // tri2
                      14, 15, 16 // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 15, // tri0
                      17, 18, 15, // tri1
                      18, 19, 20, // tri2
                      19, 21, 20  // tri3
                      ),
    gsSPNTriangles_5b(18, 22, 19, // tri0
                      2, 23, 24,  // tri1
                      25, 26, 27, // tri2
                      25, 28, 26  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r7_b_2_v[114], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          3, 5, 4  // tri2
                          ),
    gsSPNTriangles_5b(6, 0, 7,   // tri0
                      8, 9, 10,  // tri1
                      8, 10, 11, // tri2
                      12, 6, 13  // tri3
                      ),
    gsSPNTriangles_5b(0, 3, 1,    // tri0
                      14, 15, 5,  // tri1
                      14, 16, 15, // tri2
                      17, 11, 16  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      21, 22, 19, // tri1
                      23, 24, 25, // tri2
                      24, 26, 27  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r7_b_2_v[145], 3, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r7_b_2_v[148], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 0, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      8, 5, 7, // tri1
                      9, 8, 7, // tri2
                      9, 7, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 9, 10,  // tri0
                      12, 11, 10, // tri1
                      12, 10, 2,  // tri2
                      1, 12, 2    // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 13,   // tri0
                      14, 4, 13,  // tri1
                      14, 13, 15, // tri2
                      16, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 15, 17, // tri0
                      18, 16, 17, // tri1
                      19, 18, 17, // tri2
                      19, 17, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 19, 20, // tri0
                      22, 21, 20, // tri1
                      22, 20, 23, // tri2
                      24, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(25, 24, 23, // tri0
                      25, 23, 26, // tri1
                      25, 26, 27, // tri2
                      27, 28, 25  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r7_b_2_v[180], 29, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4, // tri0
                      5, 6, 4, // tri1
                      5, 7, 6, // tri2
                      6, 7, 8  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 6,   // tri0
                      8, 10, 9,  // tri1
                      8, 11, 10, // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      11, 14, 13, // tri1
                      14, 15, 13, // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 16, // tri0
                      17, 18, 16, // tri1
                      17, 19, 18, // tri2
                      17, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 19, // tri0
                      20, 22, 21, // tri1
                      20, 23, 22, // tri2
                      23, 24, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 25, 24, // tri0
                      23, 26, 25, // tri1
                      26, 27, 25, // tri2
                      26, 28, 27  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r7_b_2_v[209], 13, 0),
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