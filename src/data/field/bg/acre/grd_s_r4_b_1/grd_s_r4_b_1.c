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

static Vtx grd_s_r4_b_1_v[] = {
#include "assets/field/bg/grd_s_r4_b_1_v.inc"
};

extern Gfx grd_s_r4_b_1_modelT[] = {
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
    gsSPVertex(&grd_s_r4_b_1_v[152], 15, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5, // tri0
                      7, 8, 5, // tri1
                      7, 9, 8, // tri2
                      9, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(10, 2, 8, // tri0
                      10, 0, 2, // tri1
                      1, 11, 3, // tri2
                      11, 12, 3 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      13, 14, 12, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r4_b_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r4_b_1_v[125], 15, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 5, 1  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      10, 2, 8,  // tri1
                      11, 9, 12, // tri2
                      13, 12, 14 // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bridge_1_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bridge_1_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&grd_s_r4_b_1_v[140], 12, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 0, 5  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 5, // tri0
                      1, 6, 3, // tri1
                      6, 7, 3, // tri2
                      5, 2, 8  // tri3
                      ),
    gsSPNTriangles_5b(2, 3, 8, // tri0
                      3, 9, 8, // tri1
                      3, 7, 9, // tri2
                      10, 0, 4 // tri3
                      ),
    gsSPNTriangles_5b(10, 1, 0,  // tri0
                      10, 11, 1, // tri1
                      11, 6, 1,  // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r4_b_1_v[0], 15, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 7, 4,    // tri0
                      9, 10, 11,  // tri1
                      12, 13, 10, // tri2
                      14, 11, 6   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r4_b_1_v[15], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 6,    // tri0
                      9, 10, 8,   // tri1
                      11, 12, 10, // tri2
                      13, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      18, 15, 19, // tri1
                      20, 18, 21, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 20, // tri0
                      24, 25, 23, // tri1
                      26, 27, 25, // tri2
                      27, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(28, 30, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r4_b_1_v[46], 3, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r4_b_1_v[49], 32, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      4, 8, 5, // tri1
                      0, 2, 9, // tri2
                      2, 8, 9  // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 12, // tri0
                      10, 13, 11, // tri1
                      10, 14, 13, // tri2
                      15, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(15, 18, 16, // tri0
                      15, 14, 18, // tri1
                      0, 19, 1,   // tri2
                      19, 20, 1   // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 1,  // tri0
                      21, 22, 1,  // tri1
                      23, 24, 25, // tri2
                      24, 26, 25  // tri3
                      ),
    gsSPNTriangles_5b(23, 27, 24, // tri0
                      27, 28, 24, // tri1
                      27, 29, 28, // tri2
                      29, 30, 28  // tri3
                      ),
    gsSPVertex(&grd_s_r4_b_1_v[80], 14, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      5, 6, 4, // tri1
                      6, 7, 4, // tri2
                      6, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(6, 9, 8,   // tri0
                      9, 10, 8,  // tri1
                      9, 11, 10, // tri2
                      0, 12, 13  // tri3
                      ),
    gsSPNTriangles_5b(0, 2, 12, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r4_b_1_v[94], 31, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 2, 1  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,  // tri0
                      7, 9, 8,  // tri1
                      6, 10, 7, // tri2
                      11, 5, 4  // tri3
                      ),
    gsSPNTriangles_5b(0, 12, 13,  // tri0
                      1, 0, 13,   // tri1
                      12, 14, 15, // tri2
                      11, 16, 5   // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 2,    // tri0
                      14, 12, 0,  // tri1
                      14, 17, 15, // tri2
                      18, 19, 8   // tri3
                      ),
    gsSPNTriangles_5b(20, 6, 21,  // tri0
                      22, 21, 23, // tri1
                      24, 23, 25, // tri2
                      26, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(27, 18, 8, // tri0
                      27, 8, 9,  // tri1
                      10, 6, 20, // tri2
                      28, 20, 21 // tri3
                      ),
    gsSPNTriangles_5b(28, 21, 22, // tri0
                      29, 22, 23, // tri1
                      29, 23, 24, // tri2
                      30, 24, 25  // tri3
                      ),
    gsSPEndDisplayList(),
};
