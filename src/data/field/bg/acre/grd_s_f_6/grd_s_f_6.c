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

static Vtx grd_s_f_6_v[] = {
#include "assets/field/bg/grd_s_f_6_v.inc"
};

extern Gfx grd_s_f_6_modelT[] = {
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
    gsSPVertex(&grd_s_f_6_v[243], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_6_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_a_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_6_v[207], 32, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 5, 8,   // tri0
                      9, 7, 10,  // tri1
                      11, 9, 12, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      19, 16, 20, // tri1
                      21, 19, 22, // tri2
                      23, 21, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 23, 26, // tri0
                      15, 27, 28, // tri1
                      27, 29, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_f_6_v[238], 5, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_6_v[0], 32, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          5, 2, 6  // tri2
                          ),
    gsSPNTriangles_5b(0, 2, 5, // tri0
                      3, 7, 4, // tri1
                      6, 8, 9, // tri2
                      8, 4, 7  // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,   // tri0
                      7, 10, 9,  // tri1
                      11, 9, 10, // tri2
                      7, 3, 12   // tri3
                      ),
    gsSPNTriangles_5b(10, 7, 12,  // tri0
                      13, 14, 15, // tri1
                      15, 16, 17, // tri2
                      15, 18, 16  // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 16, // tri0
                      19, 20, 16, // tri1
                      21, 22, 23, // tri2
                      21, 24, 22  // tri3
                      ),
    gsSPNTriangles_5b(21, 13, 17, // tri0
                      13, 21, 23, // tri1
                      25, 22, 26, // tri2
                      25, 23, 22  // tri3
                      ),
    gsSPNTriangles_5b(27, 28, 26, // tri0
                      29, 22, 30, // tri1
                      22, 24, 30, // tri2
                      31, 12, 3   // tri3
                      ),
    gsSPVertex(&grd_s_f_6_v[32], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 4, 7,  // tri0
                      4, 8, 7,  // tri1
                      9, 6, 5,  // tri2
                      10, 11, 9 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 11, // tri0
                      13, 14, 11, // tri1
                      15, 16, 14, // tri2
                      15, 17, 16  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 16, // tri0
                      19, 20, 21, // tri1
                      22, 23, 20, // tri2
                      24, 23, 25  // tri3
                      ),
    gsSPNTriangles_5b(18, 17, 26, // tri0
                      15, 14, 13, // tri1
                      13, 12, 27, // tri2
                      28, 27, 12  // tri3
                      ),
    gsSPNTriangles_5b(12, 11, 10, // tri0
                      3, 8, 4,    // tri1
                      3, 29, 8,   // tri2
                      1, 0, 3     // tri3
                      ),
    gsSPNTriangles_5b(30, 0, 2,   // tri0
                      20, 19, 22, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_f_6_v[63], 18, 0),
    gsSPNTrianglesInit_5b(13,      // tri count
                          0, 1, 2, // tri0
                          1, 0, 3, // tri1
                          0, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 4, // tri0
                      6, 5, 7, // tri1
                      4, 6, 3, // tri2
                      8, 7, 9  // tri3
                      ),
    gsSPNTriangles_5b(10, 11, 12, // tri0
                      12, 13, 14, // tri1
                      14, 10, 12, // tri2
                      13, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(16, 15, 17, // tri0
                      13, 17, 15, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_6_v[81], 32, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 3, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 9, 10,   // tri0
                      11, 12, 13, // tri1
                      14, 15, 16, // tri2
                      17, 0, 18   // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 15, // tri0
                      19, 6, 20,  // tri1
                      4, 14, 16,  // tri2
                      11, 21, 12  // tri3
                      ),
    gsSPNTriangles_5b(19, 20, 22, // tri0
                      21, 19, 22, // tri1
                      9, 11, 13,  // tri2
                      23, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(23, 26, 27, // tri0
                      28, 27, 26, // tri1
                      29, 30, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_f_6_v[113], 30, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          3, 4, 5  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 8,   // tri0
                      0, 9, 10,  // tri1
                      9, 6, 10,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(8, 14, 11,  // tri0
                      15, 16, 17, // tri1
                      17, 18, 19, // tri2
                      19, 20, 21  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      23, 24, 25, // tri1
                      25, 26, 27, // tri2
                      27, 28, 29  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_6_v[143], 27, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          2, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 4, // tri0
                      5, 7, 6, // tri1
                      5, 8, 7, // tri2
                      9, 10, 8 // tri3
                      ),
    gsSPNTriangles_5b(9, 11, 10,  // tri0
                      11, 12, 10, // tri1
                      13, 14, 12, // tri2
                      15, 16, 14  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 16, // tri0
                      19, 20, 18, // tri1
                      21, 22, 20, // tri2
                      23, 24, 22  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 24, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, bush_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(bush_b_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_6_v[170], 32, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 0, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 8,   // tri0
                      9, 10, 11, // tri1
                      10, 3, 12, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 18, // tri0
                      19, 20, 21, // tri1
                      20, 22, 23, // tri2
                      17, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(24, 19, 26, // tri0
                      27, 28, 29, // tri1
                      28, 30, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_f_6_v[202], 5, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          0, 0, 0  // tri2
                          ),
    gsSPEndDisplayList(),
};
