#include "libforest/gbi_extensions.h"

static u16 rom_tent_box_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_box_pal.inc"
};

static u16 rom_tent_can_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_can_pal.inc"
};

static u16 rom_tent_mono1_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_mono1_pal.inc"
};

static u16 rom_tent_gas_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_gas_pal.inc"
};

static u8 rom_tent_enter[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_enter.inc"
};

static u8 rom_tent_floor[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_floor.inc"
};

static u8 rom_tent_wall1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_wall1.inc"
};

static u8 rom_tent_wall2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_wall2.inc"
};

static u8 rom_tent_bou[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_bou.inc"
};

static u8 rom_tent_mono1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_mono1.inc"
};

static u8 rom_tent_can[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_can.inc"
};

static u8 rom_tent_conpas[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_conpas.inc"
};

static u8 rom_tent_box[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_box.inc"
};

static u8 rom_tent_kage_m[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_kage_m.inc"
};

static u8 rom_tent_gas[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_gas.inc"
};

static u8 rom_tent_kage_s[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_kage_s.inc"
};

static u8 rom_tent_kage_b[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_tent_kage_b.inc"
};

static Vtx rom_tent_v[] = {
#include "assets/field/bg/rom_tent_v.inc"
};

extern Gfx rom_tent_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx rom_tent_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tent_gas_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tent_gas, G_IM_FMT_CI, 16, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_tent_v[187], 32, 0),
    gsSPNTrianglesInit_5b(26,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 0, // tri1
                          5, 6, 3  // tri2
                          ),
    gsSPNTriangles_5b(7, 8, 5,    // tri0
                      9, 7, 10,   // tri1
                      11, 10, 12, // tri2
                      13, 14, 11  // tri3
                      ),
    gsSPNTriangles_5b(6, 15, 4,  // tri0
                      6, 16, 15, // tri1
                      8, 17, 16, // tri2
                      8, 16, 6   // tri3
                      ),
    gsSPNTriangles_5b(11, 18, 9,  // tri0
                      11, 14, 18, // tri1
                      9, 18, 17,  // tri2
                      9, 17, 8    // tri3
                      ),
    gsSPNTriangles_5b(3, 6, 4,    // tri0
                      10, 11, 9,  // tri1
                      12, 13, 11, // tri2
                      5, 8, 6     // tri3
                      ),
    gsSPNTriangles_5b(7, 9, 8,    // tri0
                      19, 20, 21, // tri1
                      19, 21, 22, // tri2
                      23, 24, 25  // tri3
                      ),
    gsSPNTriangles_5b(23, 25, 26, // tri0
                      27, 28, 29, // tri1
                      27, 29, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_tent_v[218], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          3, 2, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(8, 7, 1,   // tri0
                      9, 10, 11, // tri1
                      12, 4, 10, // tri2
                      13, 14, 15 // tri3
                      ),
    gsSPNTriangles_5b(13, 16, 14, // tri0
                      17, 18, 16, // tri1
                      17, 16, 13, // tri2
                      15, 19, 20  // tri3
                      ),
    gsSPNTriangles_5b(15, 14, 19, // tri0
                      20, 19, 21, // tri1
                      20, 21, 22, // tri2
                      23, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 26, // tri0
                      25, 24, 27, // tri1
                      27, 26, 25, // tri2
                      28, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(28, 30, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_tent_v[250], 30, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          2, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 3, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tent_box_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tent_box, G_IM_FMT_CI, 32, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(16,       // tri count
                          6, 7, 8,  // tri0
                          7, 9, 8,  // tri1
                          10, 11, 7 // tri2
                          ),
    gsSPNTriangles_5b(10, 7, 12, // tri0
                      11, 13, 9, // tri1
                      11, 9, 7,  // tri2
                      6, 14, 7   // tri3
                      ),
    gsSPNTriangles_5b(6, 15, 14, // tri0
                      16, 9, 17, // tri1
                      16, 8, 9,  // tri2
                      18, 19, 20 // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 21, // tri0
                      22, 23, 24, // tri1
                      25, 26, 27, // tri2
                      26, 28, 27  // tri3
                      ),
    gsSPNTriangles_5b(22, 29, 23, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tent_can_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tent_conpas, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tent_v[280], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tent_mono1_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tent_mono1, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tent_v[284], 32, 0),
    gsSPNTrianglesInit_5b(22,      // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 6, 7,   // tri0
                      8, 9, 10,  // tri1
                      8, 10, 11, // tri2
                      12, 4, 7   // tri3
                      ),
    gsSPNTriangles_5b(12, 7, 13,  // tri0
                      14, 15, 16, // tri1
                      14, 16, 17, // tri2
                      16, 12, 13  // tri3
                      ),
    gsSPNTriangles_5b(16, 13, 17, // tri0
                      18, 19, 20, // tri1
                      21, 22, 23, // tri2
                      21, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 21, 24, // tri0
                      25, 24, 26, // tri1
                      27, 25, 26, // tri2
                      27, 26, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 27, 28, // tri0
                      29, 28, 30, // tri1
                      31, 29, 30, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_tent_v[316], 13, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 6, 5  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tent_can_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tent_bou, G_IM_FMT_CI, 8, 8, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4,        // tri count
                          7, 8, 9,  // tri0
                          7, 9, 10, // tri1
                          11, 7, 10 // tri2
                          ),
    gsSPNTriangles_5b(11, 10, 12, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tent_can, G_IM_FMT_CI, 16, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tent_v[0], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      5, 6, 1, // tri1
                      6, 7, 1, // tri2
                      7, 8, 1  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 1,   // tri0
                      9, 10, 1,  // tri1
                      10, 11, 1, // tri2
                      11, 12, 1  // tri3
                      ),
    gsSPNTriangles_5b(12, 2, 1,   // tri0
                      13, 14, 15, // tri1
                      13, 16, 14, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(18, 20, 19, // tri0
                      18, 21, 20, // tri1
                      21, 22, 20, // tri2
                      21, 23, 22  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 22, // tri0
                      15, 25, 13, // tri1
                      15, 26, 25, // tri2
                      26, 27, 25  // tri3
                      ),
    gsSPNTriangles_5b(26, 28, 27, // tri0
                      28, 29, 27, // tri1
                      28, 30, 29, // tri2
                      30, 19, 29  // tri3
                      ),
    gsSPNTriangles_5b(30, 17, 19, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_tent_v[31], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(4, 5, 1, // tri0
                      5, 6, 1, // tri1
                      6, 7, 1, // tri2
                      7, 8, 1  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 1,   // tri0
                      9, 10, 1,  // tri1
                      10, 11, 1, // tri2
                      11, 12, 1  // tri3
                      ),
    gsSPNTriangles_5b(12, 3, 1,   // tri0
                      13, 14, 15, // tri1
                      14, 16, 15, // tri2
                      17, 13, 18  // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 18, // tri0
                      19, 18, 20, // tri1
                      19, 17, 18, // tri2
                      14, 21, 16  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 16, // tri0
                      23, 24, 25, // tri1
                      23, 26, 24, // tri2
                      27, 25, 28  // tri3
                      ),
    gsSPNTriangles_5b(27, 23, 25, // tri0
                      29, 20, 30, // tri1
                      29, 19, 20, // tri2
                      30, 28, 29  // tri3
                      ),
    gsSPNTriangles_5b(30, 27, 28, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_tent_v[62], 32, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          1, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 4, // tri0
                      1, 6, 5, // tri1
                      1, 7, 6, // tri2
                      0, 8, 1  // tri3
                      ),
    gsSPNTriangles_5b(8, 9, 1,   // tri0
                      9, 10, 1,  // tri1
                      10, 11, 1, // tri2
                      11, 12, 1  // tri3
                      ),
    gsSPNTriangles_5b(12, 7, 1,   // tri0
                      13, 14, 15, // tri1
                      13, 16, 14, // tri2
                      16, 17, 14  // tri3
                      ),
    gsSPNTriangles_5b(16, 18, 17, // tri0
                      18, 19, 17, // tri1
                      18, 20, 19, // tri2
                      20, 21, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 22, 21, // tri0
                      15, 23, 13, // tri1
                      15, 24, 23, // tri2
                      24, 25, 23  // tri3
                      ),
    gsSPNTriangles_5b(25, 26, 23, // tri0
                      25, 27, 26, // tri1
                      27, 28, 26, // tri2
                      27, 29, 28  // tri3
                      ),
    gsSPNTriangles_5b(29, 30, 28, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&rom_tent_v[93], 31, 0),
    gsSPNTrianglesInit_5b(28,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 2, 5  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 2, // tri0
                      6, 5, 7, // tri1
                      6, 4, 5, // tri2
                      8, 7, 9  // tri3
                      ),
    gsSPNTriangles_5b(8, 6, 7,    // tri0
                      10, 11, 12, // tri1
                      11, 13, 12, // tri2
                      1, 10, 3    // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 3,  // tri0
                      14, 15, 16, // tri1
                      14, 17, 15, // tri2
                      9, 16, 8    // tri3
                      ),
    gsSPNTriangles_5b(9, 14, 16,  // tri0
                      18, 19, 20, // tri1
                      18, 21, 19, // tri2
                      21, 22, 19  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 19, // tri0
                      23, 24, 19, // tri1
                      24, 25, 19, // tri2
                      25, 26, 19  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 19, // tri0
                      27, 28, 19, // tri1
                      28, 29, 19, // tri2
                      29, 30, 19  // tri3
                      ),
    gsSPNTriangles_5b(30, 20, 19, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tent_wall2, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tent_v[124], 24, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          2, 3, 4, // tri1
                          5, 6, 7  // tri2
                          ),
    gsSPNTriangles_5b(6, 8, 7,    // tri0
                      5, 9, 6,    // tri1
                      10, 11, 12, // tri2
                      10, 13, 11  // tri3
                      ),
    gsSPNTriangles_5b(13, 14, 11, // tri0
                      15, 16, 17, // tri1
                      15, 4, 16,  // tri2
                      4, 3, 16    // tri3
                      ),
    gsSPNTriangles_5b(18, 19, 20, // tri0
                      18, 7, 19,  // tri1
                      7, 8, 19,   // tri2
                      21, 22, 13  // tri3
                      ),
    gsSPNTriangles_5b(22, 14, 13, // tri0
                      21, 23, 22, // tri1
                      0, 2, 4,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tent_wall1, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&rom_tent_v[148], 24, 0),
    gsSPNTrianglesInit_5b(18,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 9, 10,  // tri1
                      9, 7, 10,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(12, 14, 13, // tri0
                      9, 15, 7,   // tri1
                      15, 6, 7,   // tri2
                      1, 16, 3    // tri3
                      ),
    gsSPNTriangles_5b(16, 17, 3,  // tri0
                      13, 18, 11, // tri1
                      18, 19, 11, // tri2
                      20, 21, 19  // tri3
                      ),
    gsSPNTriangles_5b(21, 11, 19, // tri0
                      22, 23, 17, // tri1
                      23, 3, 17,  // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tent_floor, G_IM_FMT_CI, 64, 64, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&rom_tent_v[172], 15, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(1, 5, 2, // tri0
                      6, 7, 0, // tri1
                      0, 7, 3, // tri2
                      7, 8, 3  // tri3
                      ),
    gsSPNTriangles_5b(9, 6, 2, // tri0
                      6, 0, 2, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_tent_box_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tent_enter, G_IM_FMT_CI, 64, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,          // tri count
                          10, 11, 12, // tri0
                          13, 14, 10, // tri1
                          13, 10, 12  // tri2
                          ),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 120, 40, 0, 40, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tent_kage_b, G_IM_FMT_I, 32, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_tent_v[329], 20, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 2, 3, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tent_kage_s, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          4, 5, 6, // tri0
                          4, 6, 7, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_tent_kage_m, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(6,         // tri count
                          8, 9, 10,  // tri0
                          8, 10, 11, // tri1
                          12, 13, 14 // tri2
                          ),
    gsSPNTriangles_5b(12, 14, 15, // tri0
                      16, 17, 18, // tri1
                      16, 18, 19, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
