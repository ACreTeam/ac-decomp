#include "libforest/gbi_extensions.h"

static u16 room[] = {
#include "assets/field/bg/room.inc"
};

static u8 room_floor[] = {
#include "assets/field/bg/room_floor.inc"
};

static u8 room_wall[] = {
#include "assets/field/bg/room_wall.inc"
};

static u8 room_window[] = {
#include "assets/field/bg/room_window.inc"
};

static Vtx room01_v[] = {
#include "assets/field/bg/room01_v.inc"
};

static Gfx room01_grp_room01__edge[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_pal16(15, room),
    gsDPLoadTextureBlock_4b(room_window, G_IM_FMT_CI, 64, 64, 15, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                            6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&room01_v[80], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPEndDisplayList(),
};

static Gfx room01_grp_room_out01[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PASS2),
    gsSPVertex(&room01_v[72], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
    gsSPEndDisplayList(),
};

static Gfx room01_grp_room01[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_pal16(15, room),
    gsDPLoadTextureBlock_4b(room_wall, G_IM_FMT_CI, 64, 64, 15, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 6,
                            6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&room01_v[0], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 0, 0),
    gsSP2Triangles(0, 5, 1, 0, 0, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 7, 9, 8, 0),
    gsSP2Triangles(10, 11, 12, 0, 11, 13, 12, 0),
    gsSP2Triangles(14, 15, 16, 0, 15, 17, 16, 0),
    gsSP2Triangles(18, 19, 20, 0, 19, 21, 20, 0),
    gsSP2Triangles(22, 23, 24, 0, 23, 25, 24, 0),
    gsSP2Triangles(23, 26, 25, 0, 26, 27, 25, 0),
    gsSP2Triangles(26, 28, 27, 0, 29, 30, 31, 0),
    gsSPVertex(&room01_v[32], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(1, 4, 3, 0, 4, 5, 3, 0),
    gsSP2Triangles(6, 7, 8, 0, 6, 9, 7, 0),
    gsSP2Triangles(9, 10, 7, 0, 10, 11, 7, 0),
    gsDPLoadTLUT_pal16(15, room),
    gsDPLoadTextureBlock_4b(room_floor, G_IM_FMT_CI, 64, 32, 15, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                            6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&room01_v[44], 28, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 7, 8, 0, 8, 7, 9, 0),
    gsSP2Triangles(4, 10, 11, 0, 6, 11, 12, 0),
    gsSP2Triangles(13, 11, 6, 0, 4, 11, 13, 0),
    gsSP2Triangles(14, 15, 13, 0, 16, 17, 14, 0),
    gsSP2Triangles(17, 18, 19, 0, 17, 19, 14, 0),
    gsSP2Triangles(19, 15, 14, 0, 20, 21, 22, 0),
    gsSP2Triangles(20, 23, 21, 0, 17, 24, 22, 0),
    gsSP2Triangles(5, 15, 25, 0, 5, 13, 15, 0),
    gsSP2Triangles(5, 26, 13, 0, 15, 21, 25, 0),
    gsSP2Triangles(15, 19, 21, 0, 19, 18, 21, 0),
    gsSP2Triangles(27, 8, 13, 0, 8, 14, 13, 0),
    gsSP2Triangles(8, 16, 14, 0, 17, 9, 24, 0),
    gsSPEndDisplayList(),
};

extern Gfx room01_model[] = {
    gsDPPipeSync(),
    gsSPTexture(65535, 65535, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_AA_ZB_TEX_EDGE2),
    gsSPClearGeometryMode(G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSPDisplayList(room01_grp_room01),
    gsSPDisplayList(room01_grp_room_out01),
    gsSPDisplayList(room01_grp_room01__edge),
    gsSPEndDisplayList(),
};
