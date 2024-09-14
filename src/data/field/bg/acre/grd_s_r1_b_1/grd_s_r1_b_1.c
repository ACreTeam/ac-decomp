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

static Vtx grd_s_r1_b_1_v[] = {
#include "assets/field/bg/grd_s_r1_b_1_v.inc"
};

extern Gfx grd_s_r1_b_1_modelT[] = {
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
    gsSPVertex(&grd_s_r1_b_1_v[199], 15, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 4, // tri0
                      6, 0, 7, // tri1
                      0, 2, 7, // tri2
                      1, 8, 3  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 3,   // tri0
                      8, 10, 9,  // tri1
                      10, 11, 9, // tri2
                      11, 12, 9  // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      11, 14, 13, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r1_b_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r1_b_1_v[172], 15, 0),
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
    gsSPVertex(&grd_s_r1_b_1_v[187], 12, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(3, 4, 5, // tri0
                      5, 4, 6, // tri1
                      5, 6, 7, // tri2
                      7, 6, 8  // tri3
                      ),
    gsSPNTriangles_5b(7, 8, 9,  // tri0
                      1, 10, 2, // tri1
                      6, 11, 8, // tri2
                      4, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(4, 11, 6, // tri0
                      2, 10, 4, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r1_b_1_v[0], 15, 0),
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
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r1_b_1_v[15], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 5,   // tri0
                      3, 8, 4,   // tri1
                      3, 9, 8,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      10, 14, 13, // tri1
                      11, 15, 12, // tri2
                      15, 16, 12  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 12, // tri0
                      16, 18, 17, // tri1
                      16, 19, 18, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(21, 17, 22, // tri0
                      17, 18, 22, // tri1
                      23, 24, 20, // tri2
                      24, 25, 20  // tri3
                      ),
    gsSPNTriangles_5b(24, 26, 25, // tri0
                      25, 21, 20, // tri1
                      27, 28, 29, // tri2
                      27, 30, 28  // tri3
                      ),
    gsSPVertex(&grd_s_r1_b_1_v[46], 27, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 5,   // tri0
                      7, 8, 5,   // tri1
                      9, 10, 11, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(10, 2, 12,  // tri0
                      10, 13, 2,  // tri1
                      10, 14, 13, // tri2
                      10, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      17, 19, 15, // tri1
                      16, 19, 17, // tri2
                      19, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(20, 2, 13, // tri0
                      20, 0, 2,  // tri1
                      21, 0, 20, // tri2
                      21, 22, 23 // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 22, // tri0
                      26, 25, 24, // tri1
                      25, 23, 22, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r1_b_1_v[73], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      8, 7, 9,   // tri1
                      8, 9, 10,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      15, 16, 0,  // tri1
                      0, 16, 1,   // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 18, // tri0
                      22, 23, 21, // tri1
                      24, 25, 23, // tri2
                      26, 27, 25  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 27, // tri0
                      30, 31, 29, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_b_1_v[105], 19, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 8,   // tri0
                      9, 10, 11, // tri1
                      12, 9, 13, // tri2
                      10, 5, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      16, 12, 18, // tri1
                      3, 4, 8,    // tri2
                      9, 11, 13   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r1_b_1_v[124], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 6, // tri0
                      0, 9, 8, // tri1
                      0, 2, 9, // tri2
                      1, 10, 3 // tri3
                      ),
    gsSPNTriangles_5b(1, 11, 10,  // tri0
                      12, 13, 11, // tri1
                      14, 15, 13, // tri2
                      16, 17, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 18, 17, // tri0
                      19, 20, 18, // tri1
                      5, 7, 6,    // tri2
                      7, 0, 8     // tri3
                      ),
    gsSPNTriangles_5b(1, 12, 11,  // tri0
                      12, 14, 13, // tri1
                      14, 16, 15, // tri2
                      16, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      24, 25, 22, // tri1
                      26, 27, 25, // tri2
                      26, 28, 27  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 28, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_b_1_v[155], 17, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 5,    // tri0
                      8, 9, 7,    // tri1
                      10, 11, 12, // tri2
                      13, 12, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 14, 16, // tri0
                      2, 16, 0,   // tri1
                      0, 4, 3,    // tri2
                      5, 4, 6     // tri3
                      ),
    gsSPNTriangles_5b(7, 6, 8, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};
