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

static Vtx grd_s_r1_3_v[] = {
#include "assets/field/bg/grd_s_r1_3_v.inc"
};

extern Gfx grd_s_r1_3_modelT[] = {
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
    gsSPVertex(&grd_s_r1_3_v[195], 20, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 2,  // tri0
                      6, 7, 8,  // tri1
                      7, 9, 8,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 10,   // tri0
                      10, 12, 11, // tri1
                      12, 13, 11, // tri2
                      12, 5, 13   // tri3
                      ),
    gsSPNTriangles_5b(5, 4, 13,  // tri0
                      0, 14, 1,  // tri1
                      0, 15, 14, // tri2
                      15, 16, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 16, // tri0
                      17, 18, 16, // tri1
                      17, 19, 18, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_r1_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_r1_3_v[184], 11, 0),
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
    gsSPVertex(&grd_s_r1_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 0, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      5, 8, 6, // tri1
                      8, 9, 6, // tri2
                      9, 10, 6 // tri3
                      ),
    gsSPNTriangles_5b(10, 7, 6,   // tri0
                      11, 12, 13, // tri1
                      12, 14, 13, // tri2
                      15, 16, 17  // tri3
                      ),
    gsSPNTriangles_5b(15, 18, 16, // tri0
                      19, 20, 21, // tri1
                      22, 23, 20, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(25, 23, 26, // tri0
                      11, 27, 28, // tri1
                      27, 17, 29, // tri2
                      21, 30, 19  // tri3
                      ),
    gsSPNTriangles_5b(7, 10, 31, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_s_r1_3_v[32], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          3, 2, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      8, 9, 10, // tri1
                      11, 9, 8, // tri2
                      9, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 14, // tri0
                      9, 14, 15, // tri1
                      15, 12, 9, // tri2
                      12, 15, 16 // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      20, 21, 17, // tri1
                      18, 17, 21, // tri2
                      22, 18, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 18, // tri0
                      24, 25, 23, // tri1
                      19, 26, 27, // tri2
                      26, 28, 27  // tri3
                      ),
    gsSPNTriangles_5b(29, 28, 26, // tri0
                      24, 30, 25, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_3_v[63], 20, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          0, 3, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      8, 9, 10, // tri1
                      9, 8, 11, // tri2
                      8, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(8, 13, 12,  // tri0
                      13, 14, 12, // tri1
                      14, 15, 16, // tri2
                      14, 13, 15  // tri3
                      ),
    gsSPNTriangles_5b(17, 8, 18,  // tri0
                      16, 15, 19, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r1_3_v[83], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10, // tri0
                      9, 7, 10, // tri1
                      9, 5, 7,  // tri2
                      5, 11, 6  // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 6,  // tri0
                      12, 13, 6,  // tri1
                      12, 14, 13, // tri2
                      12, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 14, // tri0
                      15, 17, 16, // tri1
                      17, 18, 16, // tri2
                      18, 2, 16   // tri3
                      ),
    gsSPNTriangles_5b(18, 0, 2, // tri0
                      0, 19, 1, // tri1
                      19, 3, 1, // tri2
                      3, 20, 4  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      21, 24, 22, // tri1
                      25, 26, 27, // tri2
                      28, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(29, 31, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_3_v[115], 18, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4,  // tri0
                      5, 6, 7,  // tri1
                      6, 8, 7,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(9, 12, 10,  // tri0
                      9, 13, 12,  // tri1
                      13, 14, 12, // tri2
                      14, 15, 12  // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 15, // tri0
                      16, 17, 15, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r1_3_v[133], 32, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 8,   // tri0
                      7, 9, 10,  // tri1
                      9, 11, 12, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 17, // tri0
                      16, 18, 19, // tri1
                      18, 20, 21, // tri2
                      20, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(22, 24, 25, // tri0
                      26, 27, 28, // tri1
                      27, 29, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_r1_3_v[164], 9, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 8, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_r1_3_v[173], 11, 0),
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
