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

static Vtx grd_s_r7_b_1_v[] = {
#include "assets/field/bg/grd_s_r7_b_1_v.inc"
};

extern Gfx grd_s_r7_b_1_modelT[] = {
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
    gsSPVertex(&grd_s_r7_b_1_v[189], 18, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          0, 2, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 3, // tri0
                      3, 6, 5, // tri1
                      6, 7, 5, // tri2
                      6, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 7,   // tri0
                      9, 10, 7,  // tri1
                      9, 11, 10, // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      11, 14, 13, // tri1
                      14, 15, 13, // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(14, 17, 16, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r7_b_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r7_b_1_v[162], 15, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 0, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      1, 7, 10,  // tri1
                      8, 11, 12, // tri2
                      11, 13, 14 // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bridge_1_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bridge_1_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&grd_s_r7_b_1_v[177], 12, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          3, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 4, // tri0
                      6, 1, 0, // tri1
                      5, 4, 7, // tri2
                      5, 7, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 6, // tri0
                      9, 6, 11, // tri1
                      10, 1, 6, // tri2
                      11, 6, 0  // tri3
                      ),
    gsSPNTriangles_5b(11, 0, 3, // tri0
                      4, 2, 7,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r7_b_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      4, 6, 5, // tri1
                      7, 2, 3, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 10,  // tri0
                      8, 12, 9,   // tri1
                      13, 14, 15, // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 7, 15,  // tri0
                      17, 13, 18, // tri1
                      13, 19, 18, // tri2
                      17, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 18, // tri0
                      21, 17, 18, // tri1
                      22, 21, 20, // tri2
                      17, 23, 14  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 12, // tri0
                      24, 22, 25, // tri1
                      24, 26, 22, // tri2
                      22, 20, 25  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 22, // tri0
                      26, 28, 27, // tri1
                      0, 2, 29,   // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r7_b_1_v[30], 18, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          0, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 2, 5, // tri0
                      2, 3, 5, // tri1
                      2, 1, 3, // tri2
                      8, 9, 2  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 2,  // tri0
                      10, 11, 2, // tri1
                      6, 12, 13, // tri2
                      12, 14, 13 // tri3
                      ),
    gsSPNTriangles_5b(0, 7, 1,    // tri0
                      15, 16, 17, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r7_b_1_v[48], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      5, 8, 6,   // tri1
                      9, 10, 11, // tri2
                      12, 9, 13  // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 15, // tri0
                      14, 16, 15, // tri1
                      16, 17, 15, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 19, // tri0
                      20, 21, 19, // tri1
                      21, 22, 7,  // tri2
                      8, 23, 24   // tri3
                      ),
    gsSPNTriangles_5b(23, 25, 24, // tri0
                      26, 27, 25, // tri1
                      26, 28, 27, // tri2
                      29, 30, 31  // tri3
                      ),
    gsSPVertex(&grd_s_r7_b_1_v[80], 18, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 0, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 4, 7,   // tri0
                      8, 6, 9,   // tri1
                      10, 8, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r7_b_1_v[98], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,   // tri0
                      6, 8, 7,   // tri1
                      9, 10, 11, // tri2
                      12, 11, 1  // tri3
                      ),
    gsSPNTriangles_5b(13, 2, 14,  // tri0
                      15, 14, 16, // tri1
                      17, 16, 18, // tri2
                      19, 18, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 10, 9, // tri0
                      9, 11, 12, // tri1
                      12, 1, 0,  // tri2
                      2, 13, 3   // tri3
                      ),
    gsSPNTriangles_5b(22, 13, 14, // tri0
                      22, 14, 15, // tri1
                      15, 16, 17, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(23, 19, 20, // tri0
                      24, 25, 26, // tri1
                      27, 26, 28, // tri2
                      29, 28, 5   // tri3
                      ),
    gsSPNTriangles_5b(8, 6, 30, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPVertex(&grd_s_r7_b_1_v[129], 18, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(2, 3, 6, // tri0
                      2, 6, 0, // tri1
                      1, 0, 7, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 12, // tri0
                      13, 11, 12, // tri1
                      14, 15, 13, // tri2
                      16, 14, 17  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r7_b_1_v[147], 15, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 8,   // tri0
                      9, 10, 11, // tri1
                      12, 9, 13, // tri2
                      10, 5, 14  // tri3
                      ),
    gsSPEndDisplayList(),
};
