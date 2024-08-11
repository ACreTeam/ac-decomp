#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 bridge_1_pal_dummy[];
extern u8 bridge_1_tex_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_r5_b_1_v[] = {
#include "assets/field/bg/grd_s_r5_b_1_v.inc"
};

extern Gfx grd_s_r5_b_1_modelT[] = {
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
    gsSPVertex(&grd_s_r5_b_1_v[226], 28, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 4,   // tri0
                      5, 8, 6,   // tri1
                      9, 10, 11, // tri2
                      12, 13, 10 // tri3
                      ),
    gsSPNTriangles_5b(10, 9, 12, // tri0
                      7, 14, 12, // tri1
                      9, 4, 7,   // tri2
                      7, 12, 9   // tri3
                      ),
    gsSPNTriangles_5b(7, 15, 14,  // tri0
                      15, 16, 14, // tri1
                      17, 16, 15, // tri2
                      18, 19, 17  // tri3
                      ),
    gsSPNTriangles_5b(15, 18, 17, // tri0
                      18, 20, 21, // tri1
                      20, 22, 21, // tri2
                      21, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(3, 22, 20, // tri0
                      1, 23, 2,  // tri1
                      20, 0, 3,  // tri2
                      1, 24, 23  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 26, // tri0
                      24, 26, 23, // tri1
                      1, 27, 24,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r5_b_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bridge_1_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bridge_1_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r5_b_1_v[199], 27, 0),
    gsSPNTrianglesInit_5b(29,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 2, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8, // tri0
                      9, 0, 2, // tri1
                      9, 2, 6, // tri2
                      8, 7, 5  // tri3
                      ),
    gsSPNTriangles_5b(8, 5, 10,  // tri0
                      10, 5, 4,  // tri1
                      10, 4, 11, // tri2
                      12, 3, 5   // tri3
                      ),
    gsSPNTriangles_5b(7, 12, 5,  // tri0
                      2, 1, 12,  // tri1
                      7, 2, 12,  // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 15, // tri0
                      13, 15, 17, // tri1
                      15, 18, 17, // tri2
                      19, 17, 20  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      22, 13, 17, // tri1
                      22, 17, 19, // tri2
                      23, 24, 14  // tri3
                      ),
    gsSPNTriangles_5b(23, 14, 25, // tri0
                      25, 14, 13, // tri1
                      25, 13, 22, // tri2
                      18, 26, 20  // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 17, // tri0
                      24, 16, 14, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r5_b_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      7, 5, 8,   // tri1
                      5, 9, 8,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 5, 14,  // tri0
                      5, 15, 14,  // tri1
                      15, 16, 14, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 19, // tri0
                      20, 21, 19, // tri1
                      20, 22, 21, // tri2
                      22, 23, 21  // tri3
                      ),
    gsSPNTriangles_5b(3, 24, 18, // tri0
                      17, 3, 18, // tri1
                      0, 2, 25,  // tri2
                      3, 17, 26  // tri3
                      ),
    gsSPNTriangles_5b(16, 15, 27, // tri0
                      13, 28, 5,  // tri1
                      28, 9, 5,   // tri2
                      4, 15, 5    // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r5_b_1_v[32], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          4, 3, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 2, // tri0
                      6, 7, 8, // tri1
                      6, 8, 9, // tri2
                      6, 9, 5  // tri3
                      ),
    gsSPNTriangles_5b(6, 5, 2,    // tri0
                      10, 11, 12, // tri1
                      13, 10, 12, // tri2
                      14, 12, 15  // tri3
                      ),
    gsSPNTriangles_5b(12, 16, 15, // tri0
                      12, 17, 16, // tri1
                      17, 18, 16, // tri2
                      19, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(19, 22, 20, // tri0
                      22, 23, 24, // tri1
                      23, 25, 24, // tri2
                      23, 26, 25  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 29, // tri0
                      28, 30, 29, // tri1
                      30, 26, 29, // tri2
                      31, 27, 29  // tri3
                      ),
    gsSPVertex(&grd_s_r5_b_1_v[64], 10, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 2, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 2, // tri0
                      6, 7, 8, // tri1
                      9, 7, 6, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r5_b_1_v[74], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          1, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 8,    // tri0
                      7, 9, 8,    // tri1
                      10, 11, 12, // tri2
                      11, 3, 13   // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      17, 18, 15, // tri1
                      19, 20, 18, // tri2
                      21, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 25, // tri0
                      26, 25, 27, // tri1
                      28, 27, 29, // tri2
                      30, 29, 22  // tri3
                      ),
    gsSPNTriangles_5b(18, 17, 19, // tri0
                      27, 28, 26, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r5_b_1_v[105], 3, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r5_b_1_v[108], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,   // tri0
                      7, 8, 5,   // tri1
                      9, 10, 11, // tri2
                      9, 4, 10   // tri3
                      ),
    gsSPNTriangles_5b(4, 6, 10,   // tri0
                      12, 13, 14, // tri1
                      13, 15, 14, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(16, 19, 17, // tri0
                      2, 20, 3,   // tri1
                      2, 21, 20,  // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 27, // tri0
                      28, 29, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r5_b_1_v[139], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(5, 8, 6,  // tri0
                      5, 9, 8,  // tri1
                      10, 0, 2, // tri2
                      1, 0, 3   // tri3
                      ),
    gsSPNTriangles_5b(7, 11, 5,   // tri0
                      12, 13, 9,  // tri1
                      12, 14, 13, // tri2
                      9, 5, 12    // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      18, 19, 16, // tri1
                      16, 15, 18, // tri2
                      20, 15, 17  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      24, 25, 22, // tri1
                      26, 27, 28, // tri2
                      28, 29, 26  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 27, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r5_b_1_v[171], 28, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          5, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      9, 10, 11, // tri1
                      12, 13, 0, // tri2
                      14, 15, 16 // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 14, // tri0
                      17, 19, 20, // tri1
                      20, 18, 17, // tri2
                      18, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 21, 16, // tri0
                      19, 22, 20, // tri1
                      23, 20, 22, // tri2
                      24, 25, 23  // tri3
                      ),
    gsSPNTriangles_5b(23, 25, 20, // tri0
                      26, 27, 24, // tri1
                      24, 27, 25, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
