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

static Vtx grd_s_r6_b_1_v[] = {
#include "assets/field/bg/grd_s_r6_b_1_v.inc"
};

extern Gfx grd_s_r6_b_1_modelT[] = {
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
    gsSPVertex(&grd_s_r6_b_1_v[172], 16, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 3, 5  // tri2
                          ),
    gsSPNTriangles_5b(3, 0, 5, // tri0
                      6, 4, 5, // tri1
                      6, 5, 7, // tri2
                      8, 6, 7  // tri3
                      ),
    gsSPNTriangles_5b(9, 8, 7,   // tri0
                      9, 7, 10,  // tri1
                      11, 9, 10, // tri2
                      12, 13, 10 // tri3
                      ),
    gsSPNTriangles_5b(13, 11, 10, // tri0
                      14, 12, 15, // tri1
                      14, 13, 12, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r6_b_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r6_b_1_v[143], 17, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 8,   // tri0
                      9, 10, 11, // tri1
                      12, 9, 13, // tri2
                      10, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(14, 5, 16,  // tri0
                      3, 4, 8,    // tri1
                      10, 15, 11, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bridge_1_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bridge_1_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&grd_s_r6_b_1_v[160], 12, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          2, 1, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 3, 5, // tri0
                      6, 1, 0, // tri1
                      7, 4, 5, // tri2
                      7, 5, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 2, 4,  // tri0
                      9, 4, 7,  // tri1
                      10, 0, 2, // tri2
                      10, 2, 9  // tri3
                      ),
    gsSPNTriangles_5b(11, 6, 0,  // tri0
                      11, 0, 10, // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r6_b_1_v[0], 17, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 8,   // tri0
                      9, 10, 11, // tri1
                      12, 9, 13, // tri2
                      10, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(14, 5, 16,  // tri0
                      3, 4, 8,    // tri1
                      10, 15, 11, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r6_b_1_v[17], 31, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 3, // tri0
                      5, 7, 6, // tri1
                      7, 8, 6, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 12, // tri0
                      12, 13, 14, // tri1
                      14, 15, 16, // tri2
                      15, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 17, // tri0
                      18, 20, 19, // tri1
                      20, 21, 22, // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(24, 23, 25, // tri0
                      26, 27, 25, // tri1
                      26, 28, 27, // tri2
                      28, 29, 30  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r6_b_1_v[48], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 4, // tri0
                      3, 8, 6, // tri1
                      3, 9, 8, // tri2
                      8, 10, 6 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 13, // tri0
                      11, 14, 12, // tri1
                      11, 15, 14, // tri2
                      14, 16, 12  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 12, // tri0
                      16, 18, 17, // tri1
                      18, 19, 17, // tri2
                      18, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 19, // tri0
                      22, 23, 24, // tri1
                      23, 25, 24, // tri2
                      23, 26, 25  // tri3
                      ),
    gsSPNTriangles_5b(23, 27, 26, // tri0
                      27, 28, 26, // tri1
                      27, 7, 28,  // tri2
                      27, 4, 7    // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r6_b_1_v[80], 25, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 0, // tri0
                      5, 7, 6, // tri1
                      7, 8, 6, // tri2
                      8, 9, 6  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 6,   // tri0
                      9, 11, 10,  // tri1
                      11, 12, 10, // tri2
                      11, 13, 12  // tri3
                      ),
    gsSPNTriangles_5b(5, 14, 7,   // tri0
                      5, 15, 14,  // tri1
                      16, 17, 18, // tri2
                      17, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 20, 19, // tri0
                      20, 21, 19, // tri1
                      22, 23, 24, // tri2
                      23, 13, 24  // tri3
                      ),
    gsSPNTriangles_5b(23, 12, 13, // tri0
                      22, 4, 23,  // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r6_b_1_v[105], 32, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          5, 4, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 1, 0, // tri0
                      8, 0, 2, // tri1
                      8, 2, 3, // tri2
                      9, 10, 3 // tri3
                      ),
    gsSPNTriangles_5b(9, 3, 4,  // tri0
                      5, 9, 4,  // tri1
                      11, 5, 6, // tri2
                      12, 11, 6 // tri3
                      ),
    gsSPNTriangles_5b(13, 6, 14,  // tri0
                      15, 14, 16, // tri1
                      12, 6, 13,  // tri2
                      13, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      18, 19, 20, // tri1
                      18, 21, 19, // tri2
                      22, 23, 21  // tri3
                      ),
    gsSPNTriangles_5b(21, 18, 22, // tri0
                      22, 24, 23, // tri1
                      25, 26, 24, // tri2
                      24, 22, 25  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 26, // tri0
                      26, 25, 27, // tri1
                      28, 29, 30, // tri2
                      30, 29, 31  // tri3
                      ),
    gsSPVertex(&grd_s_r6_b_1_v[137], 6, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          1, 0, 5  // tri2
                          ),
    gsSPEndDisplayList(),
};
