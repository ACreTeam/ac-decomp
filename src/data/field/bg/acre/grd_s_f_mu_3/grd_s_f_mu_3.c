#include "libforest/gbi_extensions.h"

extern u8 cliff_pal_dummy[];
extern u8 earth_pal_dummy[];
extern u8 water_2_tex_dummy[];
extern u8 water_1_tex_dummy[];
extern u8 river_tex_dummy[];
extern u8 stone_tex_dummy[];
extern u8 grass_tex_dummy[];
extern u8 earth_tex_dummy[];

static Vtx grd_s_f_mu_3_v[] = {
#include "assets/field/bg/grd_s_f_mu_3_v.inc"
};

extern Gfx grd_s_f_mu_3_modelT[] = {
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
    gsSPVertex(&grd_s_f_mu_3_v[145], 7, 0),
    gsSPNTrianglesInit_5b(5,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4, // tri0
                      1, 6, 5, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsSPEndDisplayList(),
};

extern Gfx grd_s_f_mu_3_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, cliff_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(river_tex_dummy, G_IM_FMT_CI, 64, 32, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&grd_s_f_mu_3_v[0], 22, 0),
    gsSPNTrianglesInit_5b(15,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 1, 3, // tri0
                      6, 7, 5, // tri1
                      8, 9, 7, // tri2
                      8, 10, 9 // tri3
                      ),
    gsSPNTriangles_5b(11, 12, 10, // tri0
                      10, 8, 11,  // tri1
                      13, 14, 12, // tri2
                      13, 15, 14  // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      17, 18, 19, // tri1
                      18, 20, 19, // tri2
                      16, 21, 17  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, earth_pal_dummy),
    gsDPLoadTextureBlock_4b_Dolphin(stone_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_mu_3_v[22], 14, 0),
    gsSPNTrianglesInit_5b(7,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          3, 5, 4  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7,   // tri0
                      6, 8, 9,   // tri1
                      8, 10, 11, // tri2
                      10, 12, 13 // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(earth_tex_dummy, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&grd_s_f_mu_3_v[36], 32, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          3, 5, 4  // tri2
                          ),
    gsSPNTriangles_5b(6, 7, 5,  // tri0
                      6, 8, 7,  // tri1
                      8, 9, 10, // tri2
                      9, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 15, // tri0
                      13, 15, 16, // tri1
                      11, 13, 16, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(17, 20, 18, // tri0
                      14, 17, 19, // tri1
                      20, 21, 22, // tri2
                      23, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(24, 26, 27, // tri0
                      26, 28, 29, // tri1
                      28, 30, 31, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_f_mu_3_v[68], 20, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 4, // tri1
                          3, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 9,    // tri0
                      8, 10, 11,  // tri1
                      10, 12, 13, // tri2
                      12, 14, 15  // tri3
                      ),
    gsSPNTriangles_5b(14, 16, 17, // tri0
                      16, 18, 19, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&grd_s_f_mu_3_v[88], 32, 0),
    gsSPNTrianglesInit_5b(30,      // tri count
                          0, 1, 2, // tri0
                          3, 2, 1, // tri1
                          4, 3, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 6, 7, // tri0
                      4, 1, 5, // tri1
                      1, 6, 5, // tri2
                      8, 2, 3  // tri3
                      ),
    gsSPNTriangles_5b(9, 2, 8,   // tri0
                      10, 9, 11, // tri1
                      10, 12, 9, // tri2
                      9, 12, 2   // tri3
                      ),
    gsSPNTriangles_5b(13, 12, 10, // tri0
                      14, 15, 13, // tri1
                      15, 12, 13, // tri2
                      16, 6, 17   // tri3
                      ),
    gsSPNTriangles_5b(18, 7, 19, // tri0
                      19, 7, 6,  // tri1
                      16, 19, 6, // tri2
                      20, 18, 19 // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 21, // tri0
                      17, 22, 23, // tri1
                      23, 22, 24, // tri2
                      22, 25, 24  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 26, // tri0
                      27, 28, 29, // tri1
                      28, 26, 29, // tri2
                      26, 25, 29  // tri3
                      ),
    gsSPNTriangles_5b(26, 28, 20, // tri0
                      20, 28, 21, // tri1
                      28, 30, 21, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&grd_s_f_mu_3_v[119], 26, 0),
    gsSPNTrianglesInit_5b(23,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 1, // tri1
                          3, 1, 0  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      6, 4, 5, // tri1
                      6, 7, 4, // tri2
                      7, 6, 8  // tri3
                      ),
    gsSPNTriangles_5b(9, 10, 11,  // tri0
                      9, 12, 10,  // tri1
                      10, 13, 14, // tri2
                      11, 10, 14  // tri3
                      ),
    gsSPNTriangles_5b(14, 13, 15, // tri0
                      15, 16, 14, // tri1
                      15, 17, 16, // tri2
                      16, 17, 18  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 18, // tri0
                      19, 8, 18,  // tri1
                      20, 21, 22, // tri2
                      23, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(20, 25, 21, // tri0
                      20, 23, 25, // tri1
                      19, 24, 23, // tri2
                      19, 17, 24  // tri3
                      ),
    gsSPEndDisplayList(),
};
