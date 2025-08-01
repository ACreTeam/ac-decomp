#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u16 nam_win_enpitu_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/nam_win_enpitu_pal.inc"
};

u16 nam_win_uzu_tex_rgb_ci4_pal[] = {
#include "assets/nam_win_uzu_tex_rgb_ci4_pal.inc"
};

u16 nam_win_sw1_tex_rgb_ci4_pal[] = {
#include "assets/nam_win_sw1_tex_rgb_ci4_pal.inc"
};

u16 nam_win_sw2_tex_rgb_ci4_pal[] = {
#include "assets/nam_win_sw2_tex_rgb_ci4_pal.inc"
};

u16 nam_win_sw3_tex_rgb_ci4_pal[] = {
#include "assets/nam_win_sw3_tex_rgb_ci4_pal.inc"
};

u16 nam_win_sw4_tex_rgb_ci4_pal[] = {
#include "assets/nam_win_sw4_tex_rgb_ci4_pal.inc"
};

u16 nam_win_sw5_tex_rgb_ci4_pal[] = {
#include "assets/nam_win_sw5_tex_rgb_ci4_pal.inc"
};

u16 nam_win_sw6_tex_rgb_ci4_pal[] = {
#include "assets/nam_win_sw6_tex_rgb_ci4_pal.inc"
};

u16 nam_win_sw7_tex_rgb_ci4_pal[] = {
#include "assets/nam_win_sw7_tex_rgb_ci4_pal.inc"
};

u8 nam_win_w1_tex[] = {
#include "assets/nam_win_w1_tex.inc"
};

u8 nam_win_w2_tex[] = {
#include "assets/nam_win_w2_tex.inc"
};

u8 nam_win_w3_tex[] = {
#include "assets/nam_win_w3_tex.inc"
};

u8 nam_win_w4_tex[] = {
#include "assets/nam_win_w4_tex.inc"
};

u8 nam_win_w5_tex[] = {
#include "assets/nam_win_w5_tex.inc"
};

static u8 nam_win_fuki_tex[] = {
#include "assets/nam_win/nam_win_fuki_tex.inc"
};

u8 nam_win_enpitu_tex[] = {
#include "assets/nam_win_enpitu_tex.inc"
};

u8 nam_win_waku1_tex[] = {
#include "assets/nam_win_waku1_tex.inc"
};

u8 nam_win_waku2_tex[] = {
#include "assets/nam_win_waku2_tex.inc"
};

u8 nam_win_uzu_tex_rgb_ci4[] = {
#include "assets/nam_win_uzu_tex_rgb_ci4.inc"
};

u8 nam_win_sw1_tex_rgb_ci4[] = {
#include "assets/nam_win_sw1_tex_rgb_ci4.inc"
};

u8 nam_win_sw2_tex_rgb_ci4[] = {
#include "assets/nam_win_sw2_tex_rgb_ci4.inc"
};

u8 nam_win_sw3_tex_rgb_ci4[] = {
#include "assets/nam_win_sw3_tex_rgb_ci4.inc"
};

u8 nam_win_sw4_tex_rgb_ci4[] = {
#include "assets/nam_win_sw4_tex_rgb_ci4.inc"
};

u8 nam_win_sw5_tex_rgb_ci4[] = {
#include "assets/nam_win_sw5_tex_rgb_ci4.inc"
};

u8 nam_win_sw6_tex_rgb_ci4[] = {
#include "assets/nam_win_sw6_tex_rgb_ci4.inc"
};

u8 nam_win_sw7_tex_rgb_ci4[] = {
#include "assets/nam_win_sw7_tex_rgb_ci4.inc"
};

Vtx nam_win_v[] = {
#include "assets/nam_win_v.inc"
};

Gfx nam_win_nm_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 80, 185, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 16, nam_win_waku2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(nam_win_v, 8, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, nam_win_waku1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(2, 4, 5, 6, 5, 7, 6, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_ueT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 215, 255, 235, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, nam_win_w5_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&nam_win_v[8], 27, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(7, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, nam_win_w4_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(6, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 12, 14, 16, 17, 11, 17, 18, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 32, nam_win_w3_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(4, 19, 20, 21, 20, 22, 21, 23, 24, 25),
    gsSPNTriangles_5b(24, 26, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, nam_win_w2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&nam_win_v[35], 16, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 6, 3, 5),
    gsSPNTriangles_5b(7, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 32, 64, nam_win_w1_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_fukiT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 0, 25, 20, 170),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 128, 32, nam_win_fuki_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&nam_win_v[51], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_enpituT_model[] = {
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_enpitu_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 64, nam_win_enpitu_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPVertex(&nam_win_v[55], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_sw1T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&nam_win_v[59], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_sw2T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&nam_win_v[63], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_sw3T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&nam_win_v[67], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_sw4T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw4_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw4_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&nam_win_v[71], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_sw5T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw5_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw5_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&nam_win_v[75], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_sw6T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw6_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw6_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&nam_win_v[79], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_sw7T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw7_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw7_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&nam_win_v[83], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_sw8T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw1_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw1_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&nam_win_v[87], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_sw9T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw2_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw2_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&nam_win_v[91], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_sw10T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&nam_win_v[95], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_sw11T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw3_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw3_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&nam_win_v[99], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_sw12T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw5_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw5_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&nam_win_v[103], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_sw13T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw6_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw6_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&nam_win_v[107], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 2, 3, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_sw14T_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, nam_win_sw7_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, nam_win_sw7_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 1, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&nam_win_v[111], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 0, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_mode[] = {
    gsDPLoadTLUT_Dolphin(14, 16, 1, nam_win_uzu_tex_rgb_ci4_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, nam_win_uzu_tex_rgb_ci4),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 14, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPEndDisplayList(),
};

Gfx nam_win_model[] = {
    gsSPDisplayList(nam_win_sw1T_model),  gsSPDisplayList(nam_win_sw2T_model),
    gsSPDisplayList(nam_win_sw3T_model),  gsSPDisplayList(nam_win_sw4T_model),
    gsSPDisplayList(nam_win_sw5T_model),  gsSPDisplayList(nam_win_sw6T_model),
    gsSPDisplayList(nam_win_sw7T_model),  gsSPDisplayList(nam_win_sw8T_model),
    gsSPDisplayList(nam_win_sw9T_model),  gsSPDisplayList(nam_win_sw10T_model),
    gsSPDisplayList(nam_win_sw11T_model), gsSPDisplayList(nam_win_sw12T_model),
    gsSPDisplayList(nam_win_sw13T_model), gsSPDisplayList(nam_win_sw14T_model),
    gsDPSetCycleType(G_CYC_1CYCLE),       gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureLUT(G_TT_NONE),         gsSPDisplayList(nam_win_ueT_model),
    gsSPDisplayList(nam_win_fukiT_model), gsSPDisplayList(nam_win_enpituT_model),
    gsSPDisplayList(nam_win_nm_model),    gsSPEndDisplayList(),
};
