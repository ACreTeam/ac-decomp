#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 des_win_suuji0_tex_rgb_i4[] ATTRIBUTE_ALIGN(32) = {
#include "assets/des_win_suuji0_tex_rgb_i4.inc"
};

u8 des_win_suuji1_tex_rgb_i4[] = {
#include "assets/des_win_suuji1_tex_rgb_i4.inc"
};

u8 des_win_suuji2_tex_rgb_i4[] = {
#include "assets/des_win_suuji2_tex_rgb_i4.inc"
};

u8 des_win_suuji3_tex_rgb_i4[] = {
#include "assets/des_win_suuji3_tex_rgb_i4.inc"
};

u8 des_win_suuji4_tex_rgb_i4[] = {
#include "assets/des_win_suuji4_tex_rgb_i4.inc"
};

u8 des_win_suuji5_tex_rgb_i4[] = {
#include "assets/des_win_suuji5_tex_rgb_i4.inc"
};

u8 des_win_suuji6_tex_rgb_i4[] = {
#include "assets/des_win_suuji6_tex_rgb_i4.inc"
};

u8 des_win_suuji7_tex_rgb_i4[] = {
#include "assets/des_win_suuji7_tex_rgb_i4.inc"
};

u8 des_win_suuji8_tex_rgb_i4[] = {
#include "assets/des_win_suuji8_tex_rgb_i4.inc"
};

u8 des_win_suuji9_tex_rgb_i4[] = {
#include "assets/des_win_suuji9_tex_rgb_i4.inc"
};

Vtx des_suuji_v[] = {
#include "assets/des_suuji_v.inc"
};

u8 des_win_suuji_before[] = {
#include "assets/des_win_suuji_before.inc"
};

Gfx des_win_suuji1_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(des_suuji_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx des_win_suuji2_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&des_suuji_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx des_win_suuji3_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, des_win_suuji1_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&des_suuji_v[8], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx des_win_suuji4_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, des_win_suuji6_tex_rgb_i4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&des_suuji_v[12], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
