#include "libforest/gbi_extensions.h"

extern u8 rail_pal_dummy[];
extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 tekkyo_tex_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 rail_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_t_r1_5_v[] = {
#include "assets/field/bg/grd_s_t_r1_5_v.inc"
};

extern Gfx grd_s_t_r1_5_modelT[] = {
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
    gsSPVertex(&grd_s_t_r1_5_v[264], 14, 0),
    gsSPNTrianglesInit_5b(12,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          2, 1, 4  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4, // tri0
                      6, 4, 5, // tri1
                      6, 7, 4, // tri2
                      8, 7, 9  // tri3
                      ),
    gsSPNTriangles_5b(7, 6, 9,  // tri0
                      8, 10, 7, // tri1
                      3, 0, 11, // tri2
                      8, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(8, 13, 12, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_r1_5_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_r1_5_v[208], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          2, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 5,    // tri0
                      7, 8, 9,    // tri1
                      10, 11, 12, // tri2
                      0, 10, 13   // tri3
                      ),
    gsSPNTriangles_5b(14, 5, 15,  // tri0
                      16, 7, 17,  // tri1
                      18, 19, 20, // tri2
                      16, 17, 19  // tri3
                      ),
    gsSPNTriangles_5b(11, 18, 20, // tri0
                      21, 22, 23, // tri1
                      22, 24, 25, // tri2
                      24, 26, 27  // tri3
                      ),
    gsSPNTriangles_5b(26, 28, 29, // tri0
                      28, 30, 31, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(tekkyo_tex_dummy, G_IM_FMT_CI, 128, 32, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_r1_5_v[240], 24, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      4, 6, 5, // tri1
                      6, 7, 5, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(8, 11, 9,   // tri0
                      12, 13, 14, // tri1
                      13, 15, 14, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(16, 19, 17, // tri0
                      20, 21, 22, // tri1
                      20, 23, 21, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_r1_5_v[0], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 3, // tri0
                      2, 6, 0, // tri1
                      7, 8, 9, // tri2
                      7, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(7, 11, 10,  // tri0
                      11, 12, 10, // tri1
                      8, 13, 9,   // tri2
                      14, 15, 13  // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 15, // tri0
                      14, 17, 16, // tri1
                      18, 19, 20, // tri2
                      21, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(22, 24, 23, // tri0
                      25, 26, 27, // tri1
                      25, 28, 26, // tri2
                      28, 29, 26  // tri3
                      ),
    gsSPNTriangles_5b(28, 30, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_t_r1_5_v[31], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 1, 4, // tri0
                      5, 4, 6, // tri1
                      6, 7, 5, // tri2
                      7, 8, 5  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,    // tri0
                      8, 9, 10,   // tri1
                      11, 12, 10, // tri2
                      13, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 16, // tri0
                      15, 17, 16, // tri1
                      16, 17, 18, // tri2
                      18, 19, 16  // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 19, // tri0
                      21, 18, 17, // tri1
                      22, 23, 21, // tri2
                      24, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 22, // tri0
                      24, 26, 25, // tri1
                      26, 27, 25, // tri2
                      28, 14, 29  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 28, // tri0
                      30, 31, 28, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_t_r1_5_v[63], 11, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      6, 8, 7,  // tri1
                      2, 9, 10, // tri2
                      2, 1, 9   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_r1_5_v[74], 27, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5, // tri0
                      7, 8, 5, // tri1
                      7, 9, 8, // tri2
                      1, 10, 3 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 3, // tri0
                      12, 7, 4,  // tri1
                      12, 13, 7, // tri2
                      13, 9, 7   // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 9,  // tri0
                      10, 15, 11, // tri1
                      15, 16, 11, // tri2
                      17, 13, 12  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 13, // tri0
                      18, 14, 13, // tri1
                      18, 19, 14, // tri2
                      20, 17, 21  // tri3
                      ),
    gsSPNTriangles_5b(17, 22, 21, // tri0
                      23, 24, 25, // tri1
                      23, 25, 26, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_r1_5_v[101], 32, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 4, // tri1
                          5, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(6, 5, 3,  // tri0
                      7, 8, 6,  // tri1
                      9, 10, 7, // tri2
                      11, 12, 9 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      11, 14, 13, // tri1
                      14, 15, 16, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 17, // tri0
                      20, 17, 22, // tri1
                      23, 21, 24, // tri2
                      25, 26, 27  // tri3
                      ),
    gsSPNTriangles_5b(28, 29, 30, // tri0
                      28, 26, 29, // tri1
                      29, 31, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_t_r1_5_v[133], 3, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          0, 1, 2, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_r1_5_v[136], 32, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          2, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 5,   // tri0
                      7, 8, 9,   // tri1
                      0, 10, 11, // tri2
                      10, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(14, 5, 15,  // tri0
                      16, 7, 17,  // tri1
                      18, 19, 20, // tri2
                      12, 18, 20  // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 19, // tri0
                      21, 22, 23, // tri1
                      24, 21, 25, // tri2
                      26, 24, 27  // tri3
                      ),
    gsSPNTriangles_5b(28, 26, 29, // tri0
                      30, 28, 31, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_r1_5_v[168], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(3, 0, 4, // tri0
                      6, 0, 2, // tri1
                      4, 7, 5, // tri2
                      4, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11, // tri0
                      11, 12, 9, // tri1
                      12, 13, 9, // tri2
                      12, 14, 13 // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 16, // tri0
                      14, 16, 13, // tri1
                      15, 17, 18, // tri2
                      15, 18, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 18, // tri0
                      20, 21, 19, // tri1
                      19, 21, 18, // tri2
                      20, 22, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      23, 25, 26, // tri1
                      23, 26, 24, // tri2
                      22, 24, 21  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 29, // tri0
                      27, 30, 28, // tri1
                      27, 31, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_t_r1_5_v[200], 8, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          1, 0, 3, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(3, 0, 4, // tri0
                      6, 7, 5, // tri1
                      4, 6, 5, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};
