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

static Vtx grd_s_t_r1_2_v[] = {
#include "assets/field/bg/grd_s_t_r1_2_v.inc"
};

extern Gfx grd_s_t_r1_2_modelT[] = {
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
    gsSPVertex(&grd_s_t_r1_2_v[262], 13, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          3, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 4, // tri0
                      3, 5, 6, // tri1
                      7, 3, 6, // tri2
                      7, 6, 8  // tri3
                      ),
    gsSPNTriangles_5b(7, 8, 9,   // tri0
                      10, 7, 9,  // tri1
                      11, 10, 9, // tri2
                      11, 9, 12  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_r1_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_r1_2_v[216], 22, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 0,   // tri0
                      5, 7, 6,   // tri1
                      8, 9, 10,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(5, 11, 14, // tri0
                      15, 4, 16, // tri1
                      17, 8, 18, // tri2
                      19, 20, 21 // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 20, // tri0
                      12, 19, 21, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(tekkyo_tex_dummy, G_IM_FMT_CI, 128, 32, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_r1_2_v[238], 24, 0),
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
    gsSPVertex(&grd_s_t_r1_2_v[0], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 0, 5  // tri2
                          ),
    gsSPNTriangles_5b(0, 6, 5, // tri0
                      4, 1, 0, // tri1
                      7, 8, 9, // tri2
                      8, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(8, 11, 10, // tri0
                      12, 13, 6, // tri1
                      13, 5, 6,  // tri2
                      14, 13, 12 // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 13, // tri0
                      13, 16, 5,  // tri1
                      16, 17, 5,  // tri2
                      1, 4, 18    // tri3
                      ),
    gsSPNTriangles_5b(4, 19, 18, // tri0
                      20, 9, 21, // tri1
                      9, 10, 21, // tri2
                      22, 17, 16 // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 25, // tri0
                      23, 26, 24, // tri1
                      24, 27, 25, // tri2
                      27, 28, 25  // tri3
                      ),
    gsSPNTriangles_5b(27, 18, 28, // tri0
                      29, 30, 31, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_t_r1_2_v[32], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 4,   // tri0
                      6, 8, 7,   // tri1
                      9, 10, 11, // tri2
                      10, 12, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      12, 14, 13, // tri1
                      9, 15, 10,  // tri2
                      9, 16, 15   // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 15, // tri0
                      17, 18, 15, // tri1
                      17, 19, 18, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(22, 21, 23, // tri0
                      24, 25, 26, // tri1
                      25, 27, 26, // tri2
                      28, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(29, 31, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_t_r1_2_v[64], 11, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 4, 6, // tri0
                      5, 7, 4, // tri1
                      4, 3, 6, // tri2
                      8, 9, 10 // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_r1_2_v[75], 27, 0),
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
    gsSPVertex(&grd_s_t_r1_2_v[102], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      8, 9, 10, // tri1
                      9, 5, 10, // tri2
                      6, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 14, // tri0
                      15, 16, 17, // tri1
                      16, 8, 18,  // tri2
                      19, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 24, // tri0
                      25, 22, 26, // tri1
                      20, 27, 28, // tri2
                      27, 25, 29  // tri3
                      ),
    gsSPNTriangles_5b(4, 30, 31, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_s_t_r1_2_v[134], 11, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          5, 6, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,  // tri0
                      5, 8, 7,  // tri1
                      8, 9, 10, // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_r1_2_v[145], 22, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 0,  // tri0
                      5, 7, 6,  // tri1
                      8, 9, 10, // tri2
                      5, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 14, // tri0
                      15, 4, 16,  // tri1
                      17, 8, 18,  // tri2
                      19, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(13, 19, 21, // tri0
                      17, 18, 20, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_r1_2_v[167], 32, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,  // tri0
                      6, 8, 7,  // tri1
                      8, 0, 7,  // tri2
                      9, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(9, 12, 10,  // tri0
                      9, 11, 13,  // tri1
                      11, 14, 13, // tri2
                      0, 8, 1     // tri3
                      ),
    gsSPNTriangles_5b(12, 15, 10, // tri0
                      12, 16, 15, // tri1
                      17, 18, 19, // tri2
                      17, 20, 18  // tri3
                      ),
    gsSPNTriangles_5b(20, 3, 18,  // tri0
                      20, 4, 3,   // tri1
                      21, 22, 23, // tri2
                      22, 19, 23  // tri3
                      ),
    gsSPNTriangles_5b(22, 17, 19, // tri0
                      5, 24, 6,   // tri1
                      5, 25, 24,  // tri2
                      25, 26, 24  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 24, // tri0
                      26, 28, 27, // tri1
                      28, 29, 27, // tri2
                      28, 30, 29  // tri3
                      ),
    gsSPVertex(&grd_s_t_r1_2_v[198], 18, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      5, 8, 6, // tri1
                      5, 9, 8, // tri2
                      9, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 10,  // tri0
                      9, 12, 11,  // tri1
                      12, 13, 11, // tri2
                      12, 14, 13  // tri3
                      ),
    gsSPNTriangles_5b(14, 15, 13, // tri0
                      14, 16, 15, // tri1
                      16, 17, 15, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
