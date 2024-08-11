#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c2_r2_1_v[] = {
#include "assets/field/bg/grd_s_c2_r2_1_v.inc"
};

extern Gfx grd_s_c2_r2_1_modelT[] = {
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
    gsSPVertex(&grd_s_c2_r2_1_v[228], 27, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      5, 8, 7, // tri1
                      5, 9, 8, // tri2
                      5, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(6, 11, 12,  // tri0
                      6, 7, 11,   // tri1
                      12, 13, 14, // tri2
                      12, 11, 13  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      14, 13, 15, // tri1
                      17, 18, 19, // tri2
                      17, 20, 18  // tri3
                      ),
    gsSPNTriangles_5b(20, 0, 2,   // tri0
                      20, 17, 0,  // tri1
                      21, 22, 23, // tri2
                      21, 24, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 25, 26, // tri0
                      23, 22, 25, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c2_r2_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c2_r2_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(6, 5, 7,  // tri0
                      6, 7, 8,  // tri1
                      8, 9, 10, // tri2
                      10, 9, 11 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      11, 9, 12,  // tri1
                      8, 7, 9,    // tri2
                      14, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 16, 15, // tri0
                      18, 19, 17, // tri1
                      20, 19, 18, // tri2
                      21, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(16, 23, 14, // tri0
                      17, 19, 16, // tri1
                      20, 22, 19, // tri2
                      23, 24, 14  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 3, // tri0
                      26, 2, 3,  // tri1
                      27, 28, 1, // tri2
                      29, 30, 31 // tri3
                      ),
    gsSPVertex(&grd_s_c2_r2_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          3, 1, 0, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 3, // tri0
                      5, 6, 4, // tri1
                      7, 6, 5, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 10,  // tri0
                      11, 12, 10, // tri1
                      12, 11, 13, // tri2
                      14, 13, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      16, 15, 17, // tri1
                      19, 20, 21, // tri2
                      21, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 26, // tri0
                      27, 28, 25, // tri1
                      29, 30, 28, // tri2
                      31, 7, 30   // tri3
                      ),
    gsSPNTriangles_5b(25, 24, 27, // tri0
                      28, 27, 29, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c2_r2_1_v[64], 32, 0),
    gsSPNTrianglesInit_5b(36,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 1,  // tri0
                      6, 7, 8,  // tri1
                      9, 10, 8, // tri2
                      10, 6, 8  // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 12, // tri0
                      12, 6, 10,  // tri1
                      10, 13, 11, // tri2
                      10, 5, 13   // tri3
                      ),
    gsSPNTriangles_5b(10, 9, 5, // tri0
                      9, 4, 5,  // tri1
                      5, 1, 13, // tri2
                      3, 14, 1  // tri3
                      ),
    gsSPNTriangles_5b(14, 13, 1,  // tri0
                      3, 15, 14,  // tri1
                      15, 16, 14, // tri2
                      15, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 16, // tri0
                      3, 0, 15,   // tri1
                      15, 19, 17, // tri2
                      17, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 17, // tri0
                      15, 0, 19,  // tri1
                      20, 22, 21, // tri2
                      23, 24, 22  // tri3
                      ),
    gsSPNTriangles_5b(22, 20, 23, // tri0
                      23, 25, 24, // tri1
                      23, 26, 25, // tri2
                      27, 28, 26  // tri3
                      ),
    gsSPNTriangles_5b(27, 29, 28, // tri0
                      26, 23, 27, // tri1
                      25, 30, 24, // tri2
                      25, 31, 30  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c2_r2_1_v[96], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c2_r2_1_v[100], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      5, 8, 7,   // tri1
                      9, 10, 11, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      2, 14, 0,   // tri1
                      2, 9, 14,   // tri2
                      9, 11, 14   // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      18, 19, 20, // tri1
                      21, 22, 23, // tri2
                      22, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 26, // tri0
                      27, 28, 29, // tri1
                      28, 30, 29, // tri2
                      28, 31, 30  // tri3
                      ),
    gsSPNTriangles_5b(7, 24, 6, // tri0
                      4, 3, 5,  // tri1
                      3, 1, 5,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPVertex(&grd_s_c2_r2_1_v[132], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 4, // tri0
                      3, 6, 2, // tri1
                      6, 7, 2, // tri2
                      6, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      10, 12, 11, // tri1
                      9, 13, 10,  // tri2
                      10, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 10, // tri0
                      15, 16, 10, // tri1
                      16, 17, 10, // tri2
                      17, 18, 10  // tri3
                      ),
    gsSPNTriangles_5b(18, 14, 10, // tri0
                      17, 19, 18, // tri1
                      17, 20, 19, // tri2
                      21, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 25, // tri0
                      24, 26, 27, // tri1
                      28, 29, 30, // tri2
                      29, 31, 30  // tri3
                      ),
    gsSPVertex(&grd_s_c2_r2_1_v[164], 6, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          0, 5, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 1, 0, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c2_r2_1_v[170], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 8,   // tri0
                      9, 5, 10,  // tri1
                      11, 9, 12, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 17, // tri0
                      16, 11, 18, // tri1
                      3, 4, 8,    // tri2
                      16, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      22, 23, 24, // tri1
                      19, 25, 20, // tri2
                      26, 19, 21  // tri3
                      ),
    gsSPNTriangles_5b(27, 26, 28, // tri0
                      25, 29, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c2_r2_1_v[201], 27, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 3, 7,   // tri0
                      6, 8, 9,   // tri1
                      8, 10, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 12, 16, // tri0
                      17, 18, 19, // tri1
                      18, 15, 20, // tri2
                      21, 17, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 21, 24, // tri0
                      25, 23, 26, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
