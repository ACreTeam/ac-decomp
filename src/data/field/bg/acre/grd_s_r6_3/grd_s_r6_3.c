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

static Vtx grd_s_r6_3_v[] = {
#include "assets/field/bg/grd_s_r6_3_v.inc"
};

extern Gfx grd_s_r6_3_modelT[] = {
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
    gsSPVertex(&grd_s_r6_3_v[167], 10, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      8, 1, 9, // tri1
                      1, 0, 9, // tri2
                      4, 8, 9  // tri3
                      ),
    gsSPNTriangles_5b(4, 6, 8, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r6_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r6_3_v[154], 13, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 5, 8,   // tri0
                      9, 7, 10,  // tri1
                      11, 9, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_r6_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      2, 3, 8,   // tri1
                      9, 10, 11, // tri2
                      9, 12, 10  // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      14, 15, 16, // tri1
                      15, 17, 16, // tri2
                      18, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(0, 19, 1,   // tri0
                      1, 13, 3,   // tri1
                      20, 21, 22, // tri2
                      21, 23, 22  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 7,  // tri0
                      25, 26, 7,  // tri1
                      27, 28, 29, // tri2
                      29, 30, 27  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 27, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r6_3_v[32], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      8, 9, 9,    // tri1
                      10, 11, 12, // tri2
                      11, 13, 12  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      17, 18, 15, // tri1
                      15, 18, 16, // tri2
                      19, 9, 20   // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      24, 25, 18, // tri1
                      17, 24, 18, // tri2
                      26, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(27, 26, 28, // tri0
                      27, 29, 26, // tri1
                      29, 19, 26, // tri2
                      13, 28, 12  // tri3
                      ),
    gsSPNTriangles_5b(30, 10, 12, // tri0
                      30, 31, 10, // tri1
                      20, 31, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r6_3_v[64], 10, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 4, 8, // tri0
                      4, 7, 9, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r6_3_v[74], 32, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,    // tri0
                      8, 9, 10,   // tri1
                      10, 11, 12, // tri2
                      12, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      18, 19, 20, // tri1
                      21, 18, 22, // tri2
                      16, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(23, 21, 25, // tri0
                      26, 27, 28, // tri1
                      29, 26, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r6_3_v[105], 10, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 8, 9, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r6_3_v[115], 26, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 3, 6,  // tri0
                      7, 8, 9,  // tri1
                      9, 10, 7, // tri2
                      10, 11, 7 // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 12, // tri0
                      11, 12, 13, // tri1
                      12, 14, 13, // tri2
                      14, 15, 13  // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 15, // tri0
                      16, 17, 15, // tri1
                      18, 19, 20, // tri2
                      20, 21, 18  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 21, // tri0
                      22, 23, 21, // tri1
                      23, 24, 21, // tri2
                      24, 6, 21   // tri3
                      ),
    gsSPNTriangles_5b(24, 4, 6, // tri0
                      5, 25, 3, // tri1
                      25, 0, 3, // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r6_3_v[141], 13, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 8,   // tri0
                      9, 10, 11, // tri1
                      10, 3, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};
