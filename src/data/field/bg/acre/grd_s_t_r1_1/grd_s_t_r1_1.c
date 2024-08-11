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

static Vtx grd_s_t_r1_1_v[] = {
#include "assets/field/bg/grd_s_t_r1_1_v.inc"
};

extern Gfx grd_s_t_r1_1_modelT[] = {
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
    gsSPVertex(&grd_s_t_r1_1_v[226], 13, 0),
    gsSPNTrianglesInit_5b(11,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 2, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 2, // tri0
                      4, 5, 6, // tri1
                      7, 4, 6, // tri2
                      7, 6, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 10,   // tri0
                      7, 8, 10,   // tri1
                      11, 10, 12, // tri2
                      11, 9, 10   // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_r1_1_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_r1_1_v[189], 13, 0),
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
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(tekkyo_tex_dummy, G_IM_FMT_CI, 128, 32, 15, GX_MIRROR, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_r1_1_v[202], 24, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          1, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      4, 6, 7, // tri1
                      4, 7, 5, // tri2
                      8, 9, 10 // tri3
                      ),
    gsSPNTriangles_5b(8, 10, 11,  // tri0
                      12, 13, 14, // tri1
                      12, 14, 15, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(16, 18, 19, // tri0
                      20, 21, 22, // tri1
                      20, 22, 23, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_r1_1_v[0], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 4, 8,   // tri0
                      9, 7, 10,  // tri1
                      5, 11, 12, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      19, 16, 20, // tri1
                      21, 22, 23, // tri2
                      22, 19, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 27, // tri0
                      0, 28, 29,  // tri1
                      28, 21, 30, // tri2
                      19, 20, 24  // tri3
                      ),
    gsSPNTriangles_5b(26, 3, 31, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&grd_s_t_r1_1_v[32], 13, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 3, 8,   // tri0
                      9, 5, 10,  // tri1
                      11, 9, 12, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_r1_1_v[45], 13, 0),
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
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_r1_1_v[58], 32, 0),
    gsSPNTrianglesInit_5b(21,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      6, 7, 8, // tri1
                      6, 9, 7, // tri2
                      7, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(7, 11, 10,  // tri0
                      12, 13, 14, // tri1
                      13, 15, 14, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 18, // tri0
                      19, 20, 18, // tri1
                      21, 22, 23, // tri2
                      22, 24, 23  // tri3
                      ),
    gsSPNTriangles_5b(22, 25, 24, // tri0
                      17, 16, 26, // tri1
                      16, 0, 26,  // tri2
                      27, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(28, 30, 29, // tri0
                      28, 31, 30, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_t_r1_1_v[90], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 2, 5  // tri2
                          ),
    gsSPNTriangles_5b(2, 3, 5,  // tri0
                      6, 7, 8,  // tri1
                      6, 9, 7,  // tri2
                      8, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 9,  // tri0
                      12, 14, 13, // tri1
                      15, 16, 17, // tri2
                      16, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 21, // tri0
                      19, 22, 20, // tri1
                      19, 23, 22, // tri2
                      22, 24, 20  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 27, // tri0
                      26, 28, 27, // tri1
                      26, 29, 28, // tri2
                      26, 30, 29  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_t_r1_1_v[122], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_r1_1_v[126], 28, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      6, 7, 8, // tri1
                      7, 9, 8, // tri2
                      9, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 8, // tri0
                      7, 12, 9,  // tri1
                      7, 13, 12, // tri2
                      12, 10, 9  // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 10, // tri0
                      13, 15, 12, // tri1
                      15, 16, 12, // tri2
                      16, 17, 12  // tri3
                      ),
    gsSPNTriangles_5b(17, 14, 12, // tri0
                      18, 19, 20, // tri1
                      18, 21, 19, // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(22, 25, 23, // tri0
                      26, 0, 27,  // tri1
                      0, 2, 27,   // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_r1_1_v[154], 32, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          3, 5, 4  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 5,  // tri0
                      6, 8, 7,  // tri1
                      9, 10, 8, // tri2
                      9, 11, 10 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      14, 15, 13, // tri1
                      12, 14, 13, // tri2
                      9, 12, 11   // tri3
                      ),
    gsSPNTriangles_5b(6, 9, 8,   // tri0
                      3, 6, 5,   // tri1
                      1, 3, 2,   // tri2
                      16, 17, 18 // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 18, // tri0
                      18, 20, 16, // tri1
                      19, 21, 20, // tri2
                      21, 22, 23  // tri3
                      ),
    gsSPNTriangles_5b(23, 20, 21, // tri0
                      22, 24, 23, // tri1
                      24, 25, 26, // tri2
                      24, 26, 23  // tri3
                      ),
    gsSPNTriangles_5b(25, 27, 26, // tri0
                      27, 28, 29, // tri1
                      27, 29, 26, // tri2
                      28, 30, 29  // tri3
                      ),
    gsSPVertex(&grd_s_t_r1_1_v[185], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};
