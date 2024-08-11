#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_r6_2_v[] = {
#include "assets/field/bg/grd_s_r6_2_v.inc"
};

extern Gfx grd_s_r6_2_modelT[] = {
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
    gsSPVertex(&grd_s_r6_2_v[169], 12, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(3, 6, 7, // tri0
                      3, 7, 4, // tri1
                      1, 4, 8, // tri2
                      2, 1, 8  // tri3
                      ),
    gsSPNTriangles_5b(0, 2, 9,   // tri0
                      0, 9, 10,  // tri1
                      10, 11, 0, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r6_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r6_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 6,  // tri0
                      8, 9, 10, // tri1
                      8, 11, 9, // tri2
                      9, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(9, 13, 12,  // tri0
                      14, 15, 16, // tri1
                      15, 17, 16, // tri2
                      15, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(15, 19, 18, // tri0
                      15, 20, 19, // tri1
                      14, 21, 15, // tri2
                      21, 22, 15  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 15, // tri0
                      23, 20, 15, // tri1
                      24, 7, 25,  // tri2
                      7, 26, 25   // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 25, // tri0
                      24, 6, 7,   // tri1
                      5, 28, 3,   // tri2
                      29, 30, 31  // tri3
                      ),
    gsSPVertex(&grd_s_r6_2_v[32], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 5, // tri0
                      7, 8, 5, // tri1
                      8, 9, 5, // tri2
                      1, 10, 2 // tri3
                      ),
    gsSPNTriangles_5b(1, 11, 10,  // tri0
                      12, 13, 14, // tri1
                      15, 16, 17, // tri2
                      18, 19, 17  // tri3
                      ),
    gsSPNTriangles_5b(19, 15, 17, // tri0
                      18, 20, 19, // tri1
                      21, 20, 18, // tri2
                      21, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(23, 21, 24, // tri0
                      23, 25, 21, // tri1
                      25, 22, 21, // tri2
                      1, 26, 11   // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 11, // tri0
                      13, 12, 28, // tri1
                      12, 29, 28, // tri2
                      28, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(31, 28, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r6_2_v[64], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 2, // tri0
                      1, 6, 4, // tri1
                      1, 7, 6, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r6_2_v[72], 32, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4,   // tri0
                      6, 8, 9,   // tri1
                      8, 10, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(10, 14, 11, // tri0
                      15, 16, 17, // tri1
                      12, 15, 13, // tri2
                      16, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 21, // tri0
                      20, 22, 21, // tri1
                      23, 24, 25, // tri2
                      26, 23, 27  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 30, // tri0
                      28, 30, 22, // tri1
                      29, 26, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r6_2_v[104], 30, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 5, 9,   // tri0
                      1, 10, 11, // tri1
                      10, 8, 12, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(16, 13, 17, // tri0
                      16, 17, 18, // tri1
                      16, 18, 19, // tri2
                      19, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      23, 24, 25, // tri1
                      24, 26, 25, // tri2
                      27, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r6_2_v[134], 32, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      0, 3, 1, // tri1
                      5, 7, 6, // tri2
                      8, 9, 7  // tri3
                      ),
    gsSPNTriangles_5b(5, 8, 7,    // tri0
                      8, 10, 9,   // tri1
                      11, 12, 10, // tri2
                      10, 8, 11   // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      14, 15, 13, // tri1
                      13, 11, 14, // tri2
                      16, 17, 15  // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 15, // tri0
                      18, 19, 20, // tri1
                      20, 21, 22, // tri2
                      21, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(22, 18, 20, // tri0
                      21, 24, 22, // tri1
                      23, 25, 26, // tri2
                      23, 26, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 28, // tri0
                      25, 28, 26, // tri1
                      27, 29, 30, // tri2
                      27, 30, 28  // tri3
                      ),
    gsSPVertex(&grd_s_r6_2_v[165], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};
