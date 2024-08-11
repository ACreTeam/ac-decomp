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

static Vtx grd_s_f_5_v[] = {
#include "assets/field/bg/grd_s_f_5_v.inc"
};

extern Gfx grd_s_f_5_modelT[] = {
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
    gsSPVertex(&grd_s_f_5_v[239], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_5_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_5_v[218], 21, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,  // tri0
                      8, 9, 4,  // tri1
                      9, 10, 4, // tri2
                      11, 12, 3 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      2, 14, 15,  // tri1
                      16, 13, 17, // tri2
                      8, 16, 18   // tri3
                      ),
    gsSPNTriangles_5b(19, 6, 20, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_5_v[0], 32, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 4, 9,   // tri1
                      4, 10, 9,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      17, 18, 19, // tri1
                      5, 4, 8,    // tri2
                      20, 21, 1   // tri3
                      ),
    gsSPNTriangles_5b(21, 3, 1,   // tri0
                      22, 23, 14, // tri1
                      22, 24, 23, // tri2
                      23, 25, 14  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 17, // tri0
                      26, 28, 27, // tri1
                      28, 29, 27, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_f_5_v[30], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 1, // tri0
                      6, 7, 8, // tri1
                      7, 9, 8, // tri2
                      9, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 10, // tri0
                      0, 12, 5,  // tri1
                      0, 13, 12, // tri2
                      14, 15, 12 // tri3
                      ),
    gsSPNTriangles_5b(4, 16, 3,   // tri0
                      4, 17, 16,  // tri1
                      18, 19, 20, // tri2
                      10, 11, 21  // tri3
                      ),
    gsSPNTriangles_5b(11, 22, 21, // tri0
                      22, 23, 21, // tri1
                      23, 24, 25, // tri2
                      6, 26, 7    // tri3
                      ),
    gsSPNTriangles_5b(6, 27, 26,  // tri0
                      28, 29, 30, // tri1
                      31, 28, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_f_5_v[62], 28, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,  // tri0
                      8, 11, 9,  // tri1
                      11, 12, 9, // tri2
                      13, 14, 12 // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      15, 18, 16, // tri1
                      19, 18, 15, // tri2
                      15, 17, 13  // tri3
                      ),
    gsSPNTriangles_5b(17, 20, 21, // tri0
                      17, 22, 20, // tri1
                      22, 23, 24, // tri2
                      25, 26, 27  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_5_v[90], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3,  // tri0
                      6, 7, 8,  // tri1
                      9, 6, 10, // tri2
                      6, 8, 10  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      12, 9, 11,  // tri1
                      13, 14, 15, // tri2
                      16, 13, 15  // tri3
                      ),
    gsSPNTriangles_5b(13, 12, 14, // tri0
                      7, 17, 18,  // tri1
                      19, 20, 21, // tri2
                      20, 16, 22  // tri3
                      ),
    gsSPNTriangles_5b(0, 23, 1,   // tri0
                      19, 21, 23, // tri1
                      24, 5, 25,  // tri2
                      26, 27, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 26, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_f_5_v[121], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 8, 9,    // tri0
                      10, 11, 12, // tri1
                      13, 14, 11, // tri2
                      15, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 14, // tri0
                      16, 18, 19, // tri1
                      18, 20, 21, // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(20, 24, 21, // tri0
                      25, 26, 27, // tri1
                      22, 25, 23, // tri2
                      26, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(28, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_f_5_v[153], 12, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 3, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10, // tri0
                      8, 10, 1, // tri1
                      9, 6, 11, // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_5_v[165], 21, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          2, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(2, 6, 4,   // tri0
                      7, 8, 9,   // tri1
                      7, 10, 8,  // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      9, 14, 15,  // tri1
                      0, 16, 17,  // tri2
                      16, 13, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 5, 20, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_5_v[186], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      7, 8, 6, // tri1
                      7, 9, 8, // tri2
                      7, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 9,  // tri0
                      10, 12, 11, // tri1
                      12, 13, 11, // tri2
                      14, 15, 13  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 15, // tri0
                      18, 19, 20, // tri1
                      18, 21, 19, // tri2
                      21, 22, 19  // tri3
                      ),
    gsSPNTriangles_5b(19, 23, 20, // tri0
                      23, 24, 25, // tri1
                      24, 17, 26, // tri2
                      22, 27, 19  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 27, // tri0
                      30, 31, 29, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
