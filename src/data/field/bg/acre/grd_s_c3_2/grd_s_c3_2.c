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
extern u8 cliff_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_c3_2_v[] = {
#include "assets/field/bg/grd_s_c3_2_v.inc"
};

extern Gfx grd_s_c3_2_modelT[] = {
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
    gsSPVertex(&grd_s_c3_2_v[217], 7, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      5, 6, 1, // tri1
                      6, 2, 1, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_c3_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_c3_2_v[200], 17, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 8,   // tri0
                      3, 4, 8,   // tri1
                      9, 10, 11, // tri2
                      12, 9, 11  // tri3
                      ),
    gsSPNTriangles_5b(1, 12, 13,  // tri0
                      9, 14, 10,  // tri1
                      14, 15, 16, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(19,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(2, 4, 7,   // tri0
                      8, 9, 10,  // tri1
                      11, 8, 10, // tri2
                      12, 13, 3  // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 13, // tri0
                      13, 14, 15, // tri1
                      16, 13, 15, // tri2
                      17, 16, 18  // tri3
                      ),
    gsSPNTriangles_5b(19, 17, 20, // tri0
                      21, 19, 22, // tri1
                      21, 22, 23, // tri2
                      24, 21, 23  // tri3
                      ),
    gsSPNTriangles_5b(24, 23, 9,  // tri0
                      25, 26, 27, // tri1
                      26, 28, 29, // tri2
                      28, 30, 31  // tri3
                      ),
    gsSPVertex(&grd_s_c3_2_v[32], 7, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          3, 5, 6  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c3_2_v[39], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 4,  // tri0
                      0, 6, 7,  // tri1
                      6, 8, 7,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(9, 12, 10,  // tri0
                      13, 14, 15, // tri1
                      13, 16, 14, // tri2
                      16, 17, 14  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 14, // tri0
                      18, 19, 14, // tri1
                      20, 16, 13, // tri2
                      19, 21, 14  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      23, 21, 24, // tri1
                      23, 14, 21, // tri2
                      22, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(22, 24, 25, // tri0
                      26, 27, 28, // tri1
                      26, 29, 27, // tri2
                      26, 25, 29  // tri3
                      ),
    gsSPNTriangles_5b(27, 30, 28, // tri0
                      30, 31, 28, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c3_2_v[71], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      5, 8, 6,   // tri1
                      8, 9, 6,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      11, 14, 13, // tri1
                      15, 16, 17, // tri2
                      16, 14, 17  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 15, // tri0
                      0, 14, 16,  // tri1
                      19, 20, 21, // tri2
                      21, 1, 19   // tri3
                      ),
    gsSPNTriangles_5b(0, 2, 14,   // tri0
                      18, 20, 19, // tri1
                      22, 5, 7,   // tri2
                      14, 2, 13   // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 25, // tri0
                      26, 25, 24, // tri1
                      27, 25, 26, // tri2
                      8, 28, 9    // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 9,  // tri0
                      28, 30, 29, // tri1
                      23, 25, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_c3_2_v[103], 10, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 5, // tri0
                      3, 8, 4, // tri1
                      3, 9, 8, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(cliff_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_c3_2_v[113], 32, 0),
    gsSPNTrianglesInit_5b(33,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      6, 8, 7,   // tri1
                      9, 10, 11, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      14, 16, 15, // tri1
                      16, 17, 15, // tri2
                      17, 18, 15  // tri3
                      ),
    gsSPNTriangles_5b(14, 19, 16, // tri0
                      19, 17, 16, // tri1
                      14, 20, 19, // tri2
                      19, 21, 17  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      23, 11, 24, // tri1
                      11, 12, 24, // tri2
                      12, 25, 24  // tri3
                      ),
    gsSPNTriangles_5b(23, 9, 11, // tri0
                      23, 26, 9, // tri1
                      27, 28, 9, // tri2
                      28, 10, 9  // tri3
                      ),
    gsSPNTriangles_5b(29, 2, 27, // tri0
                      29, 30, 2, // tri1
                      2, 28, 27, // tri2
                      2, 3, 28   // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 2, // tri0
                      31, 0, 2,  // tri1
                      31, 14, 0, // tri2
                      31, 20, 14 // tri3
                      ),
    gsSPNTriangles_5b(14, 13, 0, // tri0
                      13, 4, 0,  // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_s_c3_2_v[145], 15, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      1, 6, 3, // tri1
                      1, 7, 6, // tri2
                      6, 8, 3  // tri3
                      ),
    gsSPNTriangles_5b(8, 5, 3,  // tri0
                      7, 9, 6,  // tri1
                      9, 10, 6, // tri2
                      9, 11, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 10, // tri0
                      9, 13, 11,  // tri1
                      11, 14, 12, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_2_v[160], 23, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,   // tri0
                      6, 8, 9,   // tri1
                      8, 10, 11, // tri2
                      11, 12, 8  // tri3
                      ),
    gsSPNTriangles_5b(13, 11, 10, // tri0
                      10, 14, 13, // tri1
                      14, 15, 16, // tri2
                      15, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 7, // tri0
                      7, 4, 18,  // tri1
                      18, 3, 19, // tri2
                      18, 2, 3   // tri3
                      ),
    gsSPNTriangles_5b(17, 20, 21, // tri0
                      20, 22, 21, // tri1
                      12, 9, 8,   // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_c3_2_v[183], 17, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(4, 9, 10,   // tri0
                      11, 3, 12,  // tri1
                      13, 14, 15, // tri2
                      1, 11, 16   // tri3
                      ),
    gsSPNTriangles_5b(13, 6, 14,  // tri0
                      9, 13, 15,  // tri1
                      11, 12, 16, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
