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

static Vtx grd_s_r4_3_v[] = {
#include "assets/field/bg/grd_s_r4_3_v.inc"
};

extern Gfx grd_s_r4_3_modelT[] = {
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
    gsSPVertex(&grd_s_r4_3_v[169], 16, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      8, 9, 0, // tri1
                      9, 1, 0, // tri2
                      5, 2, 7  // tri3
                      ),
    gsSPNTriangles_5b(2, 3, 7,   // tri0
                      6, 10, 4,  // tri1
                      11, 12, 8, // tri2
                      12, 9, 8   // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 4,  // tri0
                      10, 14, 13, // tri1
                      10, 15, 14, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r4_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r4_3_v[158], 11, 0),
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
    gsSPVertex(&grd_s_r4_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 1, // tri0
                      7, 6, 1, // tri1
                      8, 7, 1, // tri2
                      8, 1, 9  // tri3
                      ),
    gsSPNTriangles_5b(0, 9, 1,    // tri0
                      10, 11, 12, // tri1
                      12, 13, 10, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      15, 17, 18, // tri1
                      17, 19, 20, // tri2
                      19, 21, 20  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      22, 24, 25, // tri1
                      24, 26, 25, // tri2
                      26, 27, 25  // tri3
                      ),
    gsSPNTriangles_5b(26, 28, 27, // tri0
                      29, 30, 28, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r4_3_v[31], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 6, // tri0
                      4, 8, 7, // tri1
                      3, 1, 4, // tri2
                      2, 9, 0  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 0,   // tri0
                      11, 12, 13, // tri1
                      14, 11, 15, // tri2
                      16, 17, 14  // tri3
                      ),
    gsSPNTriangles_5b(16, 18, 17, // tri0
                      19, 20, 18, // tri1
                      21, 22, 20, // tri2
                      23, 22, 24  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 23, // tri0
                      26, 27, 28, // tri1
                      26, 29, 27, // tri2
                      30, 29, 31  // tri3
                      ),
    gsSPNTriangles_5b(30, 27, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r4_3_v[63], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,  // tri0
                      8, 9, 10, // tri1
                      5, 8, 11, // tri2
                      12, 2, 13 // tri3
                      ),
    gsSPNTriangles_5b(14, 12, 15, // tri0
                      16, 17, 18, // tri1
                      19, 20, 21, // tri2
                      0, 22, 3    // tri3
                      ),
    gsSPNTriangles_5b(0, 7, 22,   // tri0
                      23, 18, 20, // tri1
                      16, 24, 17, // tri2
                      24, 14, 17  // tri3
                      ),
    gsSPNTriangles_5b(23, 25, 18, // tri0
                      25, 16, 18, // tri1
                      26, 27, 21, // tri2
                      27, 19, 21  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r4_3_v[94], 9, 0),
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
    gsSPVertex(&grd_s_r4_3_v[103], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          2, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      4, 6, 5, // tri1
                      6, 7, 5, // tri2
                      6, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 7,   // tri0
                      8, 10, 9,  // tri1
                      8, 11, 10, // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      13, 14, 12, // tri1
                      14, 13, 15, // tri2
                      15, 16, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 16, // tri0
                      15, 18, 17, // tri1
                      18, 19, 17, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(21, 23, 22, // tri0
                      23, 24, 22, // tri1
                      23, 25, 24, // tri2
                      25, 26, 24  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 24, // tri0
                      26, 28, 27, // tri1
                      28, 29, 27, // tri2
                      29, 30, 27  // tri3
                      ),
    gsSPNTriangles_5b(29, 31, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r4_3_v[135], 12, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      4, 6, 5, // tri1
                      6, 7, 5, // tri2
                      7, 8, 5  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,   // tri0
                      9, 10, 8,  // tri1
                      9, 11, 10, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r4_3_v[147], 11, 0),
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
