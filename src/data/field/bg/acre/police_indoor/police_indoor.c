#include "libforest/gbi_extensions.h"

static u16 rom_koban_tel_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_tel_pal.inc"
};

static u16 rom_koban_win_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_win_pal.inc"
};

static u16 rom_koban_us_pos_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_us_pos_pal.inc"
};

static u16 rom_koban_jim_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_jim_pal.inc"
};

static u16 rom_koban_kabe_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_kabe_pal.inc"
};

static u16 rom_koban_roc_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_roc_pal.inc"
};

static u8 rom_koban_tel[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_tel.inc"
};

static u8 rom_koban_win[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_win.inc"
};

static u8 rom_koban_desk_front[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_desk_front.inc"
};

static u8 rom_koban_desk_side[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_desk_side.inc"
};

static u8 rom_koban_desk_top[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_desk_top.inc"
};

static u8 rom_koban_yuka[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_yuka.inc"
};

static u8 rom_koban_us_pos1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_us_pos1.inc"
};

static u8 rom_koban_us_pos2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_us_pos2.inc"
};

static u8 rom_koban_kage1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_kage1.inc"
};

static u8 rom_koban_kage2[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_kage2.inc"
};

static u8 rom_koban_ent[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_ent.inc"
};

static u8 rom_koban_jim_front[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_jim_front.inc"
};

static u8 rom_koban_jim_side[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_jim_side.inc"
};

static u8 rom_koban_jim_top[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_jim_top.inc"
};

static u8 rom_koban_kabe1[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_kabe1.inc"
};

static u8 rom_koban_telcode[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_telcode.inc"
};

static u8 rom_koban_book[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_book.inc"
};

static u8 rom_koban_roc_s[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_roc_s.inc"
};

static u8 rom_koban_roc_t[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_roc_t.inc"
};

static u8 rom_koban_kabe3[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_kabe3.inc"
};

static u8 rom_koban_isu[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_isu.inc"
};

static u8 rom_koban_roc_i[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_roc_i.inc"
};

static u8 rom_koban_roc_f3[] ATTRIBUTE_ALIGN(32) = {
#include "assets/field/bg/rom_koban_roc_f3.inc"
};

static Vtx police_indoor_v[] = {
#include "assets/field/bg/police_indoor_v.inc"
};

extern Gfx police_indoor_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx police_indoor_model[] = {
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_win_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_win, G_IM_FMT_CI, 32, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&police_indoor_v[268], 8, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_us_pos_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_us_pos2, G_IM_FMT_CI, 32, 48, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&police_indoor_v[276], 8, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_us_pos1, G_IM_FMT_CI, 48, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          4, 5, 6, // tri0
                          5, 7, 6, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_win_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_desk_side, G_IM_FMT_CI, 16, 16, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsSPVertex(&police_indoor_v[336], 16, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 9, 10,  // tri1
                      8, 11, 9,  // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 14, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_desk_front, G_IM_FMT_CI, 32, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&police_indoor_v[352], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,   // tri0
                      8, 9, 10,  // tri1
                      8, 11, 9,  // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(13, 15, 14, // tri0
                      16, 17, 18, // tri1
                      16, 19, 17, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 21, // tri0
                      24, 25, 26, // tri1
                      24, 27, 25, // tri2
                      28, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(29, 31, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&police_indoor_v[384], 8, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_roc_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_roc_f3, G_IM_FMT_CI, 32, 64, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&police_indoor_v[392], 7, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 1, 6, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_jim_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_isu, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&police_indoor_v[399], 14, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 4, 1  // tri2
                          ),
    gsSPNTriangles_5b(3, 5, 4, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_jim_side, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          6, 7, 8, // tri0
                          6, 9, 7, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_jim_front, G_IM_FMT_CI, 32, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2,          // tri count
                          10, 11, 12, // tri0
                          10, 12, 13, // tri1
                          0, 0, 0     // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_tel_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_book, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&police_indoor_v[413], 12, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_telcode, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(1,       // tri count
                          4, 5, 6, // tri0
                          0, 0, 0, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_tel, G_IM_FMT_CI, 32, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(3,        // tri count
                          7, 8, 9,  // tri0
                          7, 9, 10, // tri1
                          8, 7, 11  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_win_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_ent, G_IM_FMT_CI, 64, 32, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&police_indoor_v[0], 5, 0),
    gsSPNTrianglesInit_5b(3,       // tri count
                          0, 1, 2, // tri0
                          2, 3, 0, // tri1
                          0, 4, 1  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_kabe_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_kabe1, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_MIRROR, 0, 0),
    gsSPVertex(&police_indoor_v[5], 32, 0),
    gsSPNTrianglesInit_5b(24,      // tri count
                          0, 1, 2, // tri0
                          3, 2, 1, // tri1
                          2, 3, 4  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 6,  // tri0
                      5, 7, 6,  // tri1
                      8, 9, 10, // tri2
                      9, 11, 10 // tri3
                      ),
    gsSPNTriangles_5b(4, 12, 13,  // tri0
                      12, 14, 13, // tri1
                      15, 16, 17, // tri2
                      16, 18, 17  // tri3
                      ),
    gsSPNTriangles_5b(17, 19, 10, // tri0
                      20, 1, 6,   // tri1
                      1, 0, 6,    // tri2
                      8, 10, 19   // tri3
                      ),
    gsSPNTriangles_5b(21, 12, 3,  // tri0
                      12, 4, 3,   // tri1
                      17, 18, 19, // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(25, 22, 24, // tri0
                      26, 27, 28, // tri1
                      29, 26, 28, // tri2
                      22, 30, 31  // tri3
                      ),
    gsSPNTriangles_5b(23, 22, 31, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&police_indoor_v[37], 32, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          4, 3, 6  // tri2
                          ),
    gsSPNTriangles_5b(7, 6, 3,   // tri0
                      7, 0, 2,   // tri1
                      8, 9, 10,  // tri2
                      11, 12, 13 // tri3
                      ),
    gsSPNTriangles_5b(11, 14, 12, // tri0
                      14, 15, 12, // tri1
                      15, 13, 12, // tri2
                      14, 16, 15  // tri3
                      ),
    gsSPNTriangles_5b(17, 18, 19, // tri0
                      17, 8, 18,  // tri1
                      8, 10, 18,  // tri2
                      10, 19, 18  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 14, // tri0
                      20, 22, 21, // tri1
                      22, 23, 21, // tri2
                      23, 14, 21  // tri3
                      ),
    gsSPNTriangles_5b(23, 24, 14, // tri0
                      8, 25, 9,   // tri1
                      25, 26, 9,  // tri2
                      8, 27, 25   // tri3
                      ),
    gsSPNTriangles_5b(27, 26, 25, // tri0
                      16, 14, 24, // tri1
                      28, 29, 30, // tri2
                      31, 30, 29  // tri3
                      ),
    gsSPVertex(&police_indoor_v[69], 10, 0),
    gsSPNTrianglesInit_5b(9,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 2, 3  // tri2
                          ),
    gsSPNTriangles_5b(4, 0, 2, // tri0
                      3, 5, 6, // tri1
                      3, 6, 7, // tri2
                      6, 8, 7  // tri3
                      ),
    gsSPNTriangles_5b(9, 7, 8, // tri0
                      9, 3, 7, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_tel_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_yuka, G_IM_FMT_CI, 64, 64, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&police_indoor_v[79], 32, 0),
    gsSPNTrianglesInit_5b(20,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          3, 0, 4  // tri2
                          ),
    gsSPNTriangles_5b(0, 5, 4,   // tri0
                      6, 7, 1,   // tri1
                      8, 9, 6,   // tri2
                      10, 11, 12 // tri3
                      ),
    gsSPNTriangles_5b(10, 13, 11, // tri0
                      14, 15, 16, // tri1
                      14, 17, 15, // tri2
                      17, 18, 19  // tri3
                      ),
    gsSPNTriangles_5b(20, 21, 22, // tri0
                      23, 17, 14, // tri1
                      24, 25, 2,  // tri2
                      24, 26, 25  // tri3
                      ),
    gsSPNTriangles_5b(26, 27, 25, // tri0
                      27, 12, 25, // tri1
                      28, 26, 24, // tri2
                      27, 26, 29  // tri3
                      ),
    gsSPNTriangles_5b(30, 31, 5, // tri0
                      0, 0, 0,   // tri1
                      0, 0, 0,   // tri2
                      0, 0, 0    // tri3
                      ),
    gsSPVertex(&police_indoor_v[111], 32, 0),
    gsSPNTrianglesInit_5b(25,      // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 4, 3  // tri2
                          ),
    gsSPNTriangles_5b(5, 1, 6, // tri0
                      7, 1, 3, // tri1
                      8, 9, 0, // tri2
                      9, 10, 0 // tri3
                      ),
    gsSPNTriangles_5b(8, 11, 9,  // tri0
                      12, 9, 13, // tri1
                      8, 0, 14,  // tri2
                      0, 10, 4   // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 11, // tri0
                      17, 15, 18, // tri1
                      17, 16, 15, // tri2
                      17, 19, 16  // tri3
                      ),
    gsSPNTriangles_5b(2, 20, 14, // tri0
                      5, 6, 21,  // tri1
                      22, 5, 21, // tri2
                      23, 22, 21 // tri3
                      ),
    gsSPNTriangles_5b(24, 25, 13, // tri0
                      26, 27, 28, // tri1
                      24, 29, 28, // tri2
                      27, 24, 28  // tri3
                      ),
    gsSPNTriangles_5b(4, 30, 3, // tri0
                      31, 7, 3, // tri1
                      0, 0, 0,  // tri2
                      0, 0, 0   // tri3
                      ),
    gsSPVertex(&police_indoor_v[143], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PASS2),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsSPVertex(&police_indoor_v[147], 8, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_win_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_desk_top, G_IM_FMT_CI, 32, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&police_indoor_v[155], 32, 0),
    gsSPNTrianglesInit_5b(16,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(5, 7, 6,   // tri0
                      8, 9, 10,  // tri1
                      8, 11, 9,  // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(12, 15, 13, // tri0
                      16, 17, 18, // tri1
                      17, 19, 18, // tri2
                      20, 21, 22  // tri3
                      ),
    gsSPNTriangles_5b(20, 23, 21, // tri0
                      24, 25, 26, // tri1
                      24, 27, 25, // tri2
                      28, 29, 30  // tri3
                      ),
    gsSPNTriangles_5b(29, 31, 30, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&police_indoor_v[187], 8, 0),
    gsSPNTrianglesInit_5b(4,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5, // tri0
                      0, 0, 0, // tri1
                      0, 0, 0, // tri2
                      0, 0, 0  // tri3
                      ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_roc_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_roc_i, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&police_indoor_v[195], 12, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          0, 3, 1, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_roc_t, G_IM_FMT_CI, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          4, 5, 6, // tri0
                          4, 7, 5, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_roc_s, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(2,         // tri count
                          8, 9, 10,  // tri0
                          9, 11, 10, // tri1
                          0, 0, 0    // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_jim_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_jim_top, G_IM_FMT_CI, 32, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&police_indoor_v[207], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTLUT_Dolphin(15, 16, 1, rom_koban_kabe_pal),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_kabe3, G_IM_FMT_CI, 32, 64, 15, GX_CLAMP, GX_REPEAT, 0, 0),
    gsSPVertex(&police_indoor_v[211], 32, 0),
    gsSPNTrianglesInit_5b(27,      // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 1  // tri2
                          ),
    gsSPNTriangles_5b(5, 3, 1, // tri0
                      5, 6, 3, // tri1
                      6, 7, 3, // tri2
                      3, 7, 2  // tri3
                      ),
    gsSPNTriangles_5b(7, 8, 2,   // tri0
                      9, 10, 11, // tri1
                      9, 11, 12, // tri2
                      12, 11, 13 // tri3
                      ),
    gsSPNTriangles_5b(12, 13, 14, // tri0
                      15, 12, 14, // tri1
                      15, 14, 16, // tri2
                      9, 12, 15   // tri3
                      ),
    gsSPNTriangles_5b(9, 15, 17,  // tri0
                      18, 19, 20, // tri1
                      19, 21, 20, // tri2
                      21, 22, 20  // tri3
                      ),
    gsSPNTriangles_5b(22, 23, 20, // tri0
                      24, 21, 25, // tri1
                      24, 22, 21, // tri2
                      21, 26, 25  // tri3
                      ),
    gsSPNTriangles_5b(21, 19, 26, // tri0
                      27, 28, 29, // tri1
                      27, 30, 28, // tri2
                      28, 31, 29  // tri3
                      ),
    gsSPVertex(&police_indoor_v[243], 25, 0),
    gsSPNTrianglesInit_5b(17,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          3, 6, 4  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,  // tri0
                      4, 2, 7,  // tri1
                      8, 9, 10, // tri2
                      11, 8, 10 // tri3
                      ),
    gsSPNTriangles_5b(10, 12, 13, // tri0
                      11, 10, 13, // tri1
                      14, 15, 12, // tri2
                      14, 12, 10  // tri3
                      ),
    gsSPNTriangles_5b(14, 10, 9,  // tri0
                      14, 9, 16,  // tri1
                      17, 18, 19, // tri2
                      18, 20, 19  // tri3
                      ),
    gsSPNTriangles_5b(21, 22, 23, // tri0
                      21, 24, 22, // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPTexture(0, 0, 0, 0, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 0, 0, 0, 115),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_kage2, G_IM_FMT_I, 16, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&police_indoor_v[284], 4, 0),
    gsSPNTrianglesInit_5b(2,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          0, 0, 0  // tri2
                          ),
    gsDPLoadTextureBlock_4b_Dolphin(rom_koban_kage1, G_IM_FMT_I, 32, 16, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&police_indoor_v[288], 32, 0),
    gsSPNTrianglesInit_5b(14,      // tri count
                          0, 1, 2, // tri0
                          3, 4, 5, // tri1
                          6, 7, 8  // tri2
                          ),
    gsSPNTriangles_5b(7, 9, 8,    // tri0
                      10, 11, 12, // tri1
                      11, 13, 12, // tri2
                      14, 15, 16  // tri3
                      ),
    gsSPNTriangles_5b(15, 17, 16, // tri0
                      18, 19, 20, // tri1
                      18, 21, 19, // tri2
                      22, 23, 24  // tri3
                      ),
    gsSPNTriangles_5b(23, 25, 24, // tri0
                      26, 27, 28, // tri1
                      26, 29, 27, // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPVertex(&police_indoor_v[318], 18, 0),
    gsSPNTrianglesInit_5b(8,       // tri count
                          0, 1, 2, // tri0
                          1, 3, 2, // tri1
                          4, 5, 6  // tri2
                          ),
    gsSPNTriangles_5b(4, 7, 5,   // tri0
                      8, 9, 10,  // tri1
                      9, 11, 10, // tri2
                      12, 13, 14 // tri3
                      ),
    gsSPNTriangles_5b(15, 16, 17, // tri0
                      0, 0, 0,    // tri1
                      0, 0, 0,    // tri2
                      0, 0, 0     // tri3
                      ),
    gsSPEndDisplayList(),
};
