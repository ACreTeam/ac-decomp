#include "libforest/gbi_extensions.h"

extern u8 rail_pal_dummy[];
extern u8 bush_pal_dummy[];
extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 stone_tex_dummy[];
extern u8 rail_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 bush_b_tex_dummy[];
extern u8 bush_a_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_t_sh_2_v[] = {
#include "assets/field/bg/grd_s_t_sh_2_v.inc"
};

extern Gfx grd_s_t_sh_2_modelT[] = {
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
    gsSPVertex(&grd_s_t_sh_2_v[197], 7, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          1, 4, 2  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 2, // tri0
                      4, 6, 5, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_t_sh_2_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_t_sh_2_v[180], 17, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 2, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 6, 8,    // tri0
                      9, 10, 4,   // tri1
                      11, 12, 10, // tri2
                      13, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(16, 15, 12, // tri0
                      2, 5, 0,    // tri1
                      12, 11, 16, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_sh_2_v[0], 17, 0),
    gsSPNTrianglesInit_5b(10,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          2, 6, 0  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 6,   // tri0
                      1, 0, 9,   // tri1
                      10, 9, 11, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(4, 3, 13,   // tri0
                      15, 11, 16, // tri1
                      5, 16, 3,   // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_t_sh_2_v[17], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 9, 10,  // tri1
                      9, 11, 10, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(12, 15, 13, // tri0
                      12, 7, 15,  // tri1
                      7, 5, 15,   // tri2
                      15, 16, 9   // tri3
                      ),
    gsSPNTriangles_5b(15, 5, 16, // tri0
                      16, 17, 9, // tri1
                      17, 18, 9, // tri2
                      19, 20, 21 // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 21, // tri0
                      22, 23, 21, // tri1
                      22, 11, 23, // tri2
                      11, 24, 23  // tri3
                      ),
    gsSPNTriangles_5b(20, 25, 22, // tri0
                      10, 11, 26, // tri1
                      9, 27, 11,  // tri2
                      9, 18, 27   // tri3
                      ),
    gsSPNTriangles_5b(27, 24, 11, // tri0
                      6, 28, 4,   // tri1
                      28, 29, 4,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_t_sh_2_v[47], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          2, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(2, 3, 4, // tri0
                      5, 4, 6, // tri1
                      4, 7, 6, // tri2
                      6, 8, 9  // tri3
                      ),
    gsSPNTriangles_5b(6, 7, 8,    // tri0
                      10, 11, 12, // tri1
                      13, 12, 11, // tri2
                      13, 14, 12  // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 14, // tri0
                      16, 17, 18, // tri1
                      19, 16, 18, // tri2
                      20, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(17, 21, 20, // tri0
                      21, 22, 20, // tri1
                      22, 23, 20, // tri2
                      24, 25, 26  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 28, // tri0
                      28, 29, 23, // tri1
                      28, 27, 29, // tri2
                      27, 30, 29  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 29, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_t_sh_2_v[79], 12, 0),
    gsSPNTrianglesInit_5b(6,       // tri count
                          0, 1, 2, // tri0
                          3, 1, 0, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 1, 3,   // tri0
                      6, 7, 8,   // tri1
                      9, 10, 11, // tri2
                      0, 0, 0    // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rail_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(rail_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_sh_2_v[91], 20, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,  // tri0
                      8, 5, 4,  // tri1
                      8, 9, 5,  // tri2
                      10, 11, 8 // tri3
                      ),
    gsSPNTriangles_5b(11, 9, 8,   // tri0
                      12, 11, 10, // tri1
                      12, 13, 11, // tri2
                      13, 14, 11  // tri3
                      ),
    gsSPNTriangles_5b(14, 3, 11, // tri0
                      11, 1, 9,  // tri1
                      11, 3, 1,  // tri2
                      9, 1, 5    // tri3
                      ),
    gsSPNTriangles_5b(1, 15, 5,  // tri0
                      5, 16, 7,  // tri1
                      5, 15, 16, // tri2
                      15, 17, 16 // tri3
                      ),
    gsSPNTriangles_5b(15, 18, 17, // tri0
                      1, 18, 15,  // tri1
                      1, 0, 18,   // tri2
                      14, 19, 3   // tri3
                      ),
    gsSPNTriangles_5b(19, 2, 3, // tri0
                      0, 0, 0,  // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_sh_2_v[111], 27, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          4, 5, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 3,   // tri0
                      7, 8, 6,   // tri1
                      9, 10, 8,  // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      14, 15, 16, // tri1
                      17, 14, 18, // tri2
                      15, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(19, 21, 22, // tri0
                      23, 24, 25, // tri1
                      24, 17, 26, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_sh_2_v[138], 23, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 1, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 6, 9,    // tri0
                      10, 11, 5,  // tri1
                      12, 11, 13, // tri2
                      14, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 15, 18, // tri0
                      19, 20, 12, // tri1
                      18, 20, 21, // tri2
                      3, 4, 22    // tri3
                      ),
    gsSPNTriangles_5b(9, 22, 8,   // tri0
                      12, 13, 19, // tri1
                      18, 21, 17, // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_t_sh_2_v[161], 19, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4,  // tri0
                      6, 7, 8,  // tri1
                      9, 10, 7, // tri2
                      7, 6, 9   // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 10,  // tri0
                      11, 12, 13, // tri1
                      12, 14, 13, // tri2
                      0, 2, 14    // tri3
                      ),
    gsSPNTriangles_5b(3, 15, 5,   // tri0
                      15, 16, 17, // tri1
                      16, 18, 17, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
