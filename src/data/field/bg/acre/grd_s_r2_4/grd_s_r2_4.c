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

static Vtx grd_s_r2_4_v[] = {
#include "assets/field/bg/grd_s_r2_4_v.inc"
};

extern Gfx grd_s_r2_4_modelT[] = {
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
    gsSPVertex(&grd_s_r2_4_v[196], 17, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 9, 10,  // tri1
                      9, 11, 10, // tri2
                      8, 12, 9   // tri3
                      ),
    gsSPNTriangles_5b(10, 3, 1,  // tri0
                      10, 11, 3, // tri1
                      8, 13, 12, // tri2
                      8, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 13, // tri0
                      15, 16, 13, // tri1
                      15, 4, 16,  // tri2
                      4, 6, 16    // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r2_4_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r2_4_v[185], 11, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 5, 8,  // tri0
                      9, 7, 10, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r2_4_v[0], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 1, // tri0
                      6, 7, 8, // tri1
                      7, 0, 8, // tri2
                      7, 1, 0  // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 6,    // tri0
                      10, 7, 9,   // tri1
                      11, 12, 13, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      16, 13, 17, // tri1
                      17, 18, 15, // tri2
                      17, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 14, // tri0
                      22, 23, 24, // tri1
                      23, 25, 24, // tri2
                      23, 26, 25  // tri3
                      ),
    gsSPNTriangles_5b(23, 21, 26, // tri0
                      27, 28, 29, // tri1
                      28, 30, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r2_4_v[32], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 8,   // tri0
                      7, 9, 8,   // tri1
                      7, 10, 9,  // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      14, 16, 15, // tri1
                      17, 18, 19, // tri2
                      20, 21, 17  // tri3
                      ),
    gsSPNTriangles_5b(5, 8, 6,   // tri0
                      9, 10, 12, // tri1
                      9, 22, 23, // tri2
                      9, 12, 22  // tri3
                      ),
    gsSPNTriangles_5b(24, 23, 22, // tri0
                      25, 23, 24, // tri1
                      25, 26, 23, // tri2
                      27, 26, 25  // tri3
                      ),
    gsSPNTriangles_5b(28, 3, 6,   // tri0
                      4, 28, 29,  // tri1
                      28, 30, 29, // tri2
                      3, 28, 4    // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 31, // tri0
                      30, 26, 31, // tri1
                      27, 31, 26, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r2_4_v[64], 21, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 5, 0  // tri2
                          ),
    gsSPNTriangles_5b(5, 1, 0,   // tri0
                      6, 7, 8,   // tri1
                      9, 10, 11, // tri2
                      10, 12, 5  // tri3
                      ),
    gsSPNTriangles_5b(5, 4, 10,   // tri0
                      12, 13, 14, // tri1
                      15, 16, 17, // tri2
                      18, 8, 19   // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 19,   // tri0
                      20, 10, 9,  // tri1
                      20, 12, 10, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r2_4_v[85], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          2, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 0,   // tri0
                      8, 9, 6,   // tri1
                      10, 11, 8, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 12, // tri0
                      13, 14, 15, // tri1
                      16, 17, 18, // tri2
                      19, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 19, 23, // tri0
                      17, 24, 25, // tri1
                      24, 26, 25, // tri2
                      26, 22, 27  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r2_4_v[116], 9, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 8, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r2_4_v[125], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 2, // tri0
                      4, 6, 5, // tri1
                      4, 7, 6, // tri2
                      4, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 7,   // tri0
                      8, 10, 9,  // tri1
                      10, 11, 9, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 12, // tri0
                      10, 14, 13, // tri1
                      14, 15, 13, // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 15, // tri0
                      16, 18, 17, // tri1
                      18, 19, 17, // tri2
                      18, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(18, 21, 20, // tri0
                      18, 22, 21, // tri1
                      23, 24, 25, // tri2
                      25, 26, 23  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      27, 28, 26, // tri1
                      28, 29, 26, // tri2
                      28, 30, 29  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r2_4_v[157], 17, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      5, 6, 3, // tri1
                      5, 7, 6, // tri2
                      7, 8, 6  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 6,   // tri0
                      9, 10, 6,  // tri1
                      9, 11, 10, // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 10, // tri0
                      12, 14, 13, // tri1
                      14, 15, 13, // tri2
                      14, 16, 15  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r2_4_v[174], 11, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 8, 9,  // tri0
                      8, 3, 10, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPEndDisplayList(),
};
