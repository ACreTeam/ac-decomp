#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_r7_2_v[] = {
#include "assets/field/bg/grd_s_r7_2_v.inc"
};

extern Gfx grd_s_r7_2_modelT[] = {
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
    gsSPVertex(&grd_s_r7_2_v[167], 20, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 0, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 5, // tri0
                      6, 4, 5, // tri1
                      6, 5, 7, // tri2
                      8, 6, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 7, 9,   // tri0
                      10, 8, 9,  // tri1
                      11, 10, 9, // tri2
                      11, 9, 12  // tri3
                      ),
    gsSPNTriangles_5b(13, 11, 12, // tri0
                      13, 12, 14, // tri1
                      15, 13, 14, // tri2
                      15, 14, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 15, 16, // tri0
                      17, 16, 18, // tri1
                      19, 17, 18, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r7_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r7_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(29,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 5, // tri0
                      1, 6, 3, // tri1
                      6, 5, 3, // tri2
                      5, 7, 4  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 10,  // tri0
                      8, 11, 9,  // tri1
                      11, 12, 9, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 15, // tri0
                      8, 17, 16,  // tri1
                      17, 15, 16, // tri2
                      8, 10, 17   // tri3
                      ),
    gsSPNTriangles_5b(13, 18, 14, // tri0
                      14, 18, 19, // tri1
                      18, 20, 19, // tri2
                      21, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(21, 24, 22, // tri0
                      21, 25, 24, // tri1
                      21, 26, 25, // tri2
                      22, 27, 23  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 23, // tri0
                      27, 7, 28,  // tri1
                      7, 5, 28,   // tri2
                      0, 29, 1    // tri3
                      ),
    gsSPNTriangles_5b(0, 30, 29,  // tri0
                      30, 31, 29, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r7_2_v[32], 24, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3,   // tri0
                      6, 7, 8,   // tri1
                      6, 9, 7,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 11, // tri0
                      13, 15, 14, // tri1
                      13, 16, 15, // tri2
                      15, 17, 14  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      8, 21, 22,  // tri1
                      22, 21, 23, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r7_2_v[56], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      10, 11, 12, // tri1
                      8, 13, 9,   // tri2
                      10, 12, 3   // tri3
                      ),
    gsSPNTriangles_5b(10, 14, 11, // tri0
                      14, 15, 16, // tri1
                      0, 17, 18,  // tri2
                      17, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(18, 17, 20, // tri0
                      1, 0, 18,   // tri1
                      21, 22, 23, // tri2
                      21, 9, 13   // tri3
                      ),
    gsSPNTriangles_5b(19, 24, 25, // tri0
                      24, 26, 27, // tri1
                      28, 2, 29,  // tri2
                      30, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(31, 28, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r7_2_v[88], 25, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      6, 0, 8,  // tri1
                      8, 0, 2,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 12, // tri0
                      10, 13, 12, // tri1
                      13, 5, 14,  // tri2
                      15, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      18, 20, 19, // tri1
                      19, 20, 21, // tri2
                      21, 9, 11   // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      23, 16, 15, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r7_2_v[113], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 3, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      6, 8, 7, // tri1
                      8, 2, 7, // tri2
                      8, 0, 2  // tri3
                      ),
    gsSPNTriangles_5b(5, 9, 6,    // tri0
                      10, 11, 12, // tri1
                      11, 13, 12, // tri2
                      13, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      15, 18, 16, // tri1
                      18, 19, 16, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 22, // tri0
                      22, 23, 24, // tri1
                      25, 26, 24, // tri2
                      26, 22, 24  // tri3
                      ),
    gsSPNTriangles_5b(20, 27, 21, // tri0
                      20, 28, 27, // tri1
                      28, 29, 27, // tri2
                      28, 15, 29  // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 29, // tri0
                      18, 14, 19, // tri1
                      14, 13, 19, // tri2
                      10, 30, 11  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 11, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r7_2_v[145], 22, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      7, 8, 6, // tri1
                      4, 9, 5, // tri2
                      7, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 8,  // tri0
                      10, 12, 11, // tri1
                      12, 13, 11, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 13, // tri0
                      14, 16, 15, // tri1
                      16, 17, 15, // tri2
                      18, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(18, 21, 19, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
