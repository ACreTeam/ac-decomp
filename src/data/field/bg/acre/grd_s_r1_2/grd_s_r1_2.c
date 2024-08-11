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

static Vtx grd_s_r1_2_v[] = {
#include "assets/field/bg/grd_s_r1_2_v.inc"
};

extern Gfx grd_s_r1_2_modelT[] = {
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
    gsSPVertex(&grd_s_r1_2_v[187], 15, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          3, 4, 0  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 5, // tri0
                      6, 4, 5, // tri1
                      6, 5, 7, // tri2
                      8, 6, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 9,   // tri0
                      10, 8, 9,  // tri1
                      10, 9, 11, // tri2
                      12, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 13, // tri0
                      14, 12, 13, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r1_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r1_2_v[174], 13, 0),
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
    gsSPVertex(&grd_s_r1_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 4, // tri0
                      3, 6, 1, // tri1
                      6, 7, 1, // tri2
                      1, 8, 2  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 2,    // tri0
                      10, 11, 12, // tri1
                      13, 14, 15, // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 16, // tri0
                      8, 11, 9,   // tri1
                      17, 18, 16, // tri2
                      19, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(19, 22, 20, // tri0
                      22, 23, 20, // tri1
                      23, 24, 20, // tri2
                      21, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(22, 25, 23, // tri0
                      13, 26, 14, // tri1
                      26, 27, 14, // tri2
                      26, 28, 27  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_2_v[32], 28, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 4, 3, // tri0
                      2, 6, 7, // tri1
                      6, 8, 7, // tri2
                      8, 9, 7  // tri3
                      ),
    gsSPNTriangles_5b(2, 10, 6,   // tri0
                      8, 11, 9,   // tri1
                      12, 13, 14, // tri2
                      12, 15, 13  // tri3
                      ),
    gsSPNTriangles_5b(10, 16, 17, // tri0
                      18, 19, 20, // tri1
                      21, 22, 23, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(27, 26, 25, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r1_2_v[60], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,    // tri0
                      8, 7, 9,    // tri1
                      10, 11, 12, // tri2
                      13, 14, 11  // tri3
                      ),
    gsSPNTriangles_5b(15, 12, 16, // tri0
                      17, 16, 6,  // tri1
                      18, 19, 20, // tri2
                      18, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 22, 21, // tri0
                      24, 23, 21, // tri1
                      25, 26, 24, // tri2
                      27, 28, 25  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 27, // tri0
                      29, 31, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_2_v[92], 25, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      11, 8, 12,  // tri1
                      13, 14, 15, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      22, 5, 23,  // tri1
                      22, 23, 20, // tri2
                      9, 19, 21   // tri3
                      ),
    gsSPNTriangles_5b(16, 24, 17, // tri0
                      14, 16, 18, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r1_2_v[117], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      5, 8, 6, // tri1
                      8, 2, 6, // tri2
                      7, 9, 5  // tri3
                      ),
    gsSPNTriangles_5b(2, 8, 0,   // tri0
                      10, 4, 3,  // tri1
                      10, 3, 11, // tri2
                      12, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(13, 12, 11, // tri0
                      13, 11, 14, // tri1
                      15, 13, 14, // tri2
                      16, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(16, 14, 17, // tri0
                      18, 16, 17, // tri1
                      19, 18, 17, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 25, // tri0
                      26, 23, 25, // tri1
                      26, 25, 27, // tri2
                      28, 26, 27  // tri3
                      ),
    gsSPNTriangles_5b(28, 27, 29, // tri0
                      30, 28, 29, // tri1
                      30, 29, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_2_v[149], 12, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 3, 4, // tri0
                      5, 4, 6, // tri1
                      7, 5, 6, // tri2
                      7, 6, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 8,   // tri0
                      9, 8, 10,  // tri1
                      11, 9, 10, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r1_2_v[161], 13, 0),
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
