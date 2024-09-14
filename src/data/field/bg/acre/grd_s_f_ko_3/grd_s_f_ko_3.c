#include "libforest/gbi_extensions.h"

extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 stone_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_ko_3_v[] = {
#include "assets/field/bg/grd_s_f_ko_3_v.inc"
};

extern Gfx grd_s_f_ko_3_modelT[] = {
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
    gsSPVertex(&grd_s_f_ko_3_v[242], 7, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 1, // tri0
                      5, 6, 1, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_ko_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_ko_3_v[203], 32, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 7, 4,    // tri0
                      9, 10, 6,   // tri1
                      11, 12, 13, // tri2
                      14, 13, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 15, 6,  // tri0
                      17, 18, 19, // tri1
                      20, 6, 18,  // tri2
                      21, 19, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 22, 24, // tri0
                      25, 26, 27, // tri1
                      28, 29, 26, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_f_ko_3_v[233], 9, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          5, 6, 1  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 6, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_ko_3_v[0], 32, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 7, 4,    // tri0
                      9, 10, 6,   // tri1
                      11, 12, 10, // tri2
                      13, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 6,  // tri0
                      17, 18, 19, // tri1
                      20, 6, 18,  // tri2
                      21, 19, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 22, 24, // tri0
                      25, 26, 27, // tri1
                      28, 27, 29, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_f_ko_3_v[30], 9, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          5, 4, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 6, 8, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_ko_3_v[39], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 4,  // tri0
                      1, 6, 2,  // tri1
                      7, 8, 9,  // tri2
                      8, 10, 11 // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 12, // tri0
                      12, 13, 11, // tri1
                      14, 15, 16, // tri2
                      14, 17, 15  // tri3
                      ),
    gsSPNTriangles_5b(17, 13, 15, // tri0
                      15, 6, 16,  // tri1
                      14, 18, 17, // tri2
                      18, 19, 17  // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 19, // tri0
                      21, 20, 18, // tri1
                      22, 19, 20, // tri2
                      22, 23, 19  // tri3
                      ),
    gsSPNTriangles_5b(23, 22, 24, // tri0
                      24, 25, 23, // tri1
                      26, 25, 24, // tri2
                      26, 27, 25  // tri3
                      ),
    gsSPNTriangles_5b(28, 25, 27, // tri0
                      29, 30, 28, // tri1
                      30, 29, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_f_ko_3_v[71], 32, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          2, 1, 3, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4, // tri0
                      5, 6, 4, // tri1
                      4, 7, 3, // tri2
                      8, 9, 2  // tri3
                      ),
    gsSPNTriangles_5b(8, 10, 9,   // tri0
                      11, 10, 8,  // tri1
                      10, 11, 12, // tri2
                      12, 13, 14  // tri3
                      ),
    gsSPNTriangles_5b(7, 15, 3,   // tri0
                      15, 7, 16,  // tri1
                      17, 18, 19, // tri2
                      20, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 19, // tri0
                      22, 16, 7,  // tri1
                      23, 24, 25, // tri2
                      26, 27, 24  // tri3
                      ),
    gsSPNTriangles_5b(28, 27, 14, // tri0
                      28, 29, 27, // tri1
                      29, 24, 27, // tri2
                      29, 30, 24  // tri3
                      ),
    gsSPNTriangles_5b(30, 25, 24, // tri0
                      28, 16, 29, // tri1
                      16, 22, 29, // tri2
                      31, 29, 22  // tri3
                      ),
    gsSPVertex(&grd_s_f_ko_3_v[103], 5, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 4, 2  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_ko_3_v[108], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3,   // tri0
                      6, 7, 8,   // tri1
                      9, 6, 10,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(12, 9, 14,  // tri0
                      15, 16, 17, // tri1
                      18, 15, 19, // tri2
                      16, 11, 20  // tri3
                      ),
    gsSPNTriangles_5b(2, 21, 22,  // tri0
                      23, 5, 24,  // tri1
                      25, 26, 27, // tri2
                      28, 25, 29  // tri3
                      ),
    gsSPNTriangles_5b(26, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_f_ko_3_v[140], 22, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      12, 9, 13,  // tri1
                      14, 15, 16, // tri2
                      15, 12, 17  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      10, 18, 21, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_ko_3_v[162], 21, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 3, // tri0
                      6, 7, 8, // tri1
                      7, 9, 8, // tri2
                      9, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(11, 10, 12, // tri0
                      11, 13, 14, // tri1
                      13, 15, 14, // tri2
                      16, 17, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 18, 17, // tri0
                      18, 19, 20, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_ko_3_v[183], 20, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 9, 7,   // tri1
                      8, 10, 9,  // tri2
                      11, 12, 10 // tri3
                      ),
    gsSPNTriangles_5b(11, 13, 12, // tri0
                      14, 15, 13, // tri1
                      14, 16, 15, // tri2
                      17, 18, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 18, // tri0
                      1, 0, 3,    // tri1
                      10, 8, 11,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
