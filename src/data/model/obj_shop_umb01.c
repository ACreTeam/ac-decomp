#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u16 obj_shop_umb_01_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_01_pal.inc"
};

u8 obj_shop_umb_01_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb_01_kasa1_tex_txt.inc"
};

u8 obj_shop_umb_01_tuka1_tex_txt[] = {
#include "assets/obj_shop_umb_01_tuka1_tex_txt.inc"
};

Vtx obj_shop_umb01_v[] = {
#include "assets/obj_shop_umb01_v.inc"
};

Gfx obj_shop_umb01_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_01_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb01_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 2, 1, 22, 23, 24, 13, 25, 26, 15),
    gsSPNTriangles_5b(9, 27, 28, 22, 29, 2, 13, 12, 23, 15, 14, 25),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_01_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb01_v[30], 26, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 12, 12, 14, 17),
    gsSPNTriangles_5b(12, 18, 19, 5, 20, 3, 2, 21, 0, 8, 22, 6),
    gsSPNTriangles_5b(19, 15, 12, 23, 24, 25, 11, 25, 9, 25, 11, 23),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb01_modelT[] = {
    gsSPEndDisplayList(),
};

static u16 tol_umb02_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb01/tol_umb02_pal.inc"
};

static u8 tol_umb02_kasa2_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb02_kasa2_tex_txt.inc"
};

static u8 tol_umb02_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb02_kasa1_tex_txt.inc"
};

static u8 tol_umb02_tuka_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb02_tuka_tex_txt.inc"
};

Vtx obj_shop_umb02_v[] = {
#include "assets/obj_shop_umb02_v.inc"
};

Gfx obj_shop_umb02_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_umb02_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb02_v, 13, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 3, 4, 0, 5, 6),
    gsSPNTriangles_5b(0, 7, 8, 0, 9, 10, 11, 12, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_umb02_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb02_v[13], 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 2, 1, 22, 23, 24, 13, 25, 26, 15),
    gsSPNTriangles_5b(9, 27, 28, 22, 29, 2, 13, 12, 23, 15, 14, 25),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb02_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb02_v[43], 19, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 2, 4, 1, 0, 5),
    gsSPNTriangles_5b(6, 5, 7, 8, 9, 10, 11, 12, 8, 8, 10, 13),
    gsSPNTriangles_5b(8, 13, 14, 4, 15, 3, 2, 3, 0, 5, 6, 1),
    gsSPNTriangles_5b(14, 11, 8, 16, 17, 18, 7, 18, 6, 18, 7, 16),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb02_modelT[] = {
    gsSPEndDisplayList(),
};

u16 obj_shop_umb_03_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_03_pal.inc"
};

u8 obj_shop_umb_03_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb_03_kasa1_tex_txt.inc"
};

u8 obj_shop_umb_03_tuka1_tex_txt[] = {
#include "assets/obj_shop_umb_03_tuka1_tex_txt.inc"
};

Vtx obj_shop_umb03_v[] = {
#include "assets/obj_shop_umb03_v.inc"
};

Gfx obj_shop_umb03_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_03_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_shop_umb_03_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb03_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 2, 1, 22, 23, 24, 13, 25, 26, 15),
    gsSPNTriangles_5b(9, 27, 28, 22, 29, 2, 13, 12, 23, 15, 14, 25),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_03_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb03_v[30], 26, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 12, 12, 14, 17),
    gsSPNTriangles_5b(12, 18, 19, 5, 20, 3, 2, 21, 0, 8, 22, 6),
    gsSPNTriangles_5b(19, 15, 12, 23, 24, 25, 11, 25, 9, 25, 11, 23),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb03_modelT[] = {
    gsSPEndDisplayList(),
};

u16 obj_shop_umb_04_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_04_pal.inc"
};

u8 obj_shop_umb_04_kasa2_tex_txt[] = {
#include "assets/obj_shop_umb_04_kasa2_tex_txt.inc"
};

u8 obj_shop_umb_04_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb_04_kasa1_tex_txt.inc"
};

u8 obj_shop_umb_04_tuka1_tex_txt[] = {
#include "assets/obj_shop_umb_04_tuka1_tex_txt.inc"
};

Vtx obj_shop_umb04_v[] = {
#include "assets/obj_shop_umb04_v.inc"
};

Gfx obj_shop_umb04_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_04_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_shop_umb_04_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb04_v, 30, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 3, 4, 5, 4, 6, 7),
    gsSPNTriangles_5b(2, 1, 8, 8, 9, 2, 7, 5, 4, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_shop_umb_04_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 10, 11, 12, 13, 10, 14, 15, 16, 17),
    gsSPNTriangles_5b(18, 19, 20, 21, 22, 23, 16, 24, 25, 26, 27, 20),
    gsSPNTriangles_5b(20, 27, 18, 23, 28, 21, 12, 14, 10, 25, 17, 16),
    gsSPNTriangles_5b(28, 23, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_04_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb04_v[30], 26, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 12, 12, 14, 17),
    gsSPNTriangles_5b(12, 18, 19, 5, 20, 3, 2, 21, 0, 8, 22, 6),
    gsSPNTriangles_5b(19, 15, 12, 23, 24, 25, 11, 25, 9, 25, 11, 23),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb04_modelT[] = {
    gsSPEndDisplayList(),
};

static u16 tol_umb_05_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb01/tol_umb_05_pal.inc"
};

static u8 tol_umb_05_kasa_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb_05_kasa_tex_txt.inc"
};

static u8 tol_umb_05_tuka_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb_05_tuka_tex_txt.inc"
};

Vtx obj_shop_umb05_v[] = {
#include "assets/obj_shop_umb05_v.inc"
};

Gfx obj_shop_umb05_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_05_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_05_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb05_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 2, 1, 22, 23, 24, 13, 25, 26, 15),
    gsSPNTriangles_5b(9, 27, 28, 22, 29, 2, 13, 12, 23, 15, 14, 25),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_05_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb05_v[30], 26, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 12, 12, 14, 17),
    gsSPNTriangles_5b(12, 18, 19, 5, 20, 3, 2, 21, 0, 8, 22, 6),
    gsSPNTriangles_5b(19, 15, 12, 23, 24, 25, 11, 25, 9, 25, 11, 23),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb05_modelT[] = {
    gsSPEndDisplayList(),
};

u16 obj_shop_umb_06_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_06_pal.inc"
};

u8 obj_shop_umb_06_tuka1_tex_txt[] = {
#include "assets/obj_shop_umb_06_tuka1_tex_txt.inc"
};

u8 obj_shop_umb_06_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb_06_kasa1_tex_txt.inc"
};

Vtx obj_shop_umb06_v[] = {
#include "assets/obj_shop_umb06_v.inc"
};

Gfx obj_shop_umb06_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_06_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_06_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb06_v, 26, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 12, 12, 14, 17),
    gsSPNTriangles_5b(12, 18, 19, 5, 20, 3, 2, 21, 0, 8, 22, 6),
    gsSPNTriangles_5b(19, 15, 12, 23, 24, 25, 11, 25, 9, 25, 11, 23),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_06_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb06_v[26], 32, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(21, 22, 23, 24, 25, 26, 27, 28, 29, 0, 0, 0),
    gsSPVertex(&obj_shop_umb06_v[56], 32, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20),
    gsSPNTriangles_5b(5, 21, 3, 22, 23, 24, 2, 25, 0, 26, 27, 28),
    gsSPNTriangles_5b(29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_shop_umb06_v[88], 6, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb06_modelT[] = {
    gsSPEndDisplayList(),
};

static u16 tol_umb07_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb01/tol_umb07_pal.inc"
};

static u8 tol_umb07_kasa2_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb07_kasa2_tex_txt.inc"
};

static u8 tol_umb07_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb07_kasa1_tex_txt.inc"
};

static u8 tol_umb07_tuka_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb07_tuka_tex_txt.inc"
};

Vtx obj_shop_umb07_v[] = {
#include "assets/obj_shop_umb07_v.inc"
};

Gfx obj_shop_umb07_modelT[] = {
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb07_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb07_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_umb07_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb07_v, 19, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tol_umb07_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsSPNTrianglesInit_5b(18, 6, 7, 8, 9, 10, 11, 6, 9, 12),
    gsSPNTriangles_5b(6, 8, 13, 6, 13, 9, 12, 14, 6, 6, 14, 7),
    gsSPNTriangles_5b(14, 15, 16, 8, 7, 16, 17, 10, 9, 11, 15, 14),
    gsSPNTriangles_5b(8, 18, 17, 16, 18, 8, 9, 13, 17, 14, 12, 11),
    gsSPNTriangles_5b(11, 12, 9, 17, 13, 8, 16, 7, 14, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb07_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb07_v[19], 19, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 2, 4, 1, 0, 5),
    gsSPNTriangles_5b(6, 5, 7, 8, 9, 10, 11, 12, 8, 8, 10, 13),
    gsSPNTriangles_5b(8, 13, 14, 4, 15, 3, 2, 3, 0, 5, 6, 1),
    gsSPNTriangles_5b(14, 11, 8, 16, 17, 18, 7, 18, 6, 18, 7, 16),
    gsSPEndDisplayList(),
};

static u16 tol_umb08_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb01/tol_umb08_pal.inc"
};

static u8 tol_umb08_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb08_kasa1_tex_txt.inc"
};

static u8 tol_umb08_kasa2_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb08_kasa2_tex_txt.inc"
};

static u8 tol_umb08_tuka_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb08_tuka_tex_txt.inc"
};

Vtx obj_shop_umb08_v[] = {
#include "assets/obj_shop_umb08_v.inc"
};

Gfx obj_shop_umb08_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb08_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb08_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb08_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 22, 1, 0, 11, 23, 24, 15, 25, 26),
    gsSPNTriangles_5b(9, 27, 28, 0, 29, 22, 24, 12, 11, 26, 16, 15),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, tol_umb08_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb08_v[30], 27, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb08_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(15, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 19, 18, 20, 17, 16, 21),
    gsSPNTriangles_5b(22, 21, 11, 13, 23, 24, 13, 24, 25, 13, 25, 15),
    gsSPNTriangles_5b(20, 26, 19, 18, 19, 16, 21, 22, 17, 11, 9, 22),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb08_modelT[] = {
    gsSPEndDisplayList(),
};

static u16 tol_umb09_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb01/tol_umb09_pal.inc"
};

static u8 tol_umb09_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb09_kasa1_tex_txt.inc"
};

static u8 tol_umb09_kasa2_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb09_kasa2_tex_txt.inc"
};

static u8 tol_umb09_tuka_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb09_tuka_tex_txt.inc"
};

Vtx obj_shop_umb09_v[] = {
#include "assets/obj_shop_umb09_v.inc"
};

Gfx obj_shop_umb09_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb09_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb09_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb09_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 22, 1, 0, 11, 23, 24, 15, 25, 26),
    gsSPNTriangles_5b(9, 27, 28, 0, 29, 22, 24, 12, 11, 26, 16, 15),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, tol_umb09_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb09_v[30], 27, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb09_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(15, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 19, 18, 20, 17, 16, 21),
    gsSPNTriangles_5b(22, 21, 11, 13, 23, 24, 13, 24, 25, 13, 25, 15),
    gsSPNTriangles_5b(20, 26, 19, 18, 19, 16, 21, 22, 17, 11, 9, 22),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb09_modelT[] = {
    gsSPEndDisplayList(),
};

static u16 tol_umb10_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb01/tol_umb10_pal.inc"
};

static u8 tol_umb10_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb10_kasa1_tex_txt.inc"
};

static u8 tol_umb10_kasa2_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb10_kasa2_tex_txt.inc"
};

static u8 tol_umb10_tuka_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb10_tuka_tex_txt.inc"
};

Vtx obj_shop_umb10_v[] = {
#include "assets/obj_shop_umb10_v.inc"
};

Gfx obj_shop_umb10_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb10_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_umb10_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb10_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 22, 1, 0, 11, 23, 24, 15, 25, 26),
    gsSPNTriangles_5b(9, 27, 28, 0, 29, 22, 24, 12, 11, 26, 16, 15),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, tol_umb10_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb10_v[30], 27, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb10_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(15, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 19, 18, 20, 17, 16, 21),
    gsSPNTriangles_5b(22, 21, 11, 13, 23, 24, 13, 24, 25, 13, 25, 15),
    gsSPNTriangles_5b(20, 26, 19, 18, 19, 16, 21, 22, 17, 11, 9, 22),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb10_modelT[] = {
    gsSPEndDisplayList(),
};

static u16 tol_umb11_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb01/tol_umb11_pal.inc"
};

static u8 tol_umb11_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb11_kasa1_tex_txt.inc"
};

static u8 tol_umb11_kasa2_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb11_kasa2_tex_txt.inc"
};

static u8 tol_umb11_tuka_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb11_tuka_tex_txt.inc"
};

Vtx obj_shop_umb11_v[] = {
#include "assets/obj_shop_umb11_v.inc"
};

Gfx obj_shop_umb11_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb11_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_umb11_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb11_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 22, 1, 0, 11, 23, 24, 15, 25, 26),
    gsSPNTriangles_5b(9, 27, 28, 0, 29, 22, 24, 12, 11, 26, 16, 15),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, tol_umb11_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb11_v[30], 27, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb11_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(15, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 19, 18, 20, 17, 16, 21),
    gsSPNTriangles_5b(22, 21, 11, 13, 23, 24, 13, 24, 25, 13, 25, 15),
    gsSPNTriangles_5b(20, 26, 19, 18, 19, 16, 21, 22, 17, 11, 9, 22),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb11_modelT[] = {
    gsSPEndDisplayList(),
};

static u16 tol_umb12_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb01/tol_umb12_pal.inc"
};

static u8 tol_umb12_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb12_kasa1_tex_txt.inc"
};

static u8 tol_umb12_kasa2_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb12_kasa2_tex_txt.inc"
};

static u8 tol_umb12_tuka_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb12_tuka_tex_txt.inc"
};

Vtx obj_shop_umb12_v[] = {
#include "assets/obj_shop_umb12_v.inc"
};

Gfx obj_shop_umb12_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb12_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, tol_umb12_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb12_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 22, 1, 0, 11, 23, 24, 15, 25, 26),
    gsSPNTriangles_5b(9, 27, 28, 0, 29, 22, 24, 12, 11, 26, 16, 15),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, tol_umb12_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb12_v[30], 27, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb12_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(15, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 19, 18, 20, 17, 16, 21),
    gsSPNTriangles_5b(22, 21, 11, 13, 23, 24, 13, 24, 25, 13, 25, 15),
    gsSPNTriangles_5b(20, 26, 19, 18, 19, 16, 21, 22, 17, 11, 9, 22),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb12_modelT[] = {
    gsSPEndDisplayList(),
};

static u16 tol_umb13_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb01/tol_umb13_pal.inc"
};

static u8 tol_umb13_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb13_kasa1_tex_txt.inc"
};

static u8 tol_umb13_kasa2_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb13_kasa2_tex_txt.inc"
};

static u8 tol_umb13_tuka_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb13_tuka_tex_txt.inc"
};

Vtx obj_shop_umb13_v[] = {
#include "assets/obj_shop_umb13_v.inc"
};

Gfx obj_shop_umb13_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb13_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb13_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb13_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 22, 1, 0, 11, 23, 24, 15, 25, 26),
    gsSPNTriangles_5b(9, 27, 28, 0, 29, 22, 24, 12, 11, 26, 16, 15),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 8, 16, tol_umb13_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb13_v[30], 27, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb13_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(15, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 19, 18, 20, 17, 16, 21),
    gsSPNTriangles_5b(22, 21, 11, 13, 23, 24, 13, 24, 25, 13, 25, 15),
    gsSPNTriangles_5b(20, 26, 19, 18, 19, 16, 21, 22, 17, 11, 9, 22),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb13_modelT[] = {
    gsSPEndDisplayList(),
};

static u16 tol_umb_14_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb01/tol_umb_14_pal.inc"
};

static u8 tol_umb_14_kasa_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb_14_kasa_tex_txt.inc"
};

static u8 tol_umb_14_tuka_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb_14_tuka_tex_txt.inc"
};

Vtx obj_shop_umb14_v[] = {
#include "assets/obj_shop_umb14_v.inc"
};

Gfx obj_shop_umb14_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_14_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_14_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb14_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 2, 1, 22, 23, 24, 13, 25, 26, 15),
    gsSPNTriangles_5b(9, 27, 28, 22, 29, 2, 13, 12, 23, 15, 14, 25),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_14_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb14_v[30], 26, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 12, 12, 14, 17),
    gsSPNTriangles_5b(12, 18, 19, 5, 20, 3, 2, 21, 0, 8, 22, 6),
    gsSPNTriangles_5b(19, 15, 12, 23, 24, 25, 11, 25, 9, 25, 11, 23),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb14_modelT[] = {
    gsSPEndDisplayList(),
};

u16 obj_shop_umb_15_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_15_pal.inc"
};

u8 obj_shop_umb_15_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb_15_kasa1_tex_txt.inc"
};

u8 obj_shop_umb_15_kasa2_tex_txt[] = {
#include "assets/obj_shop_umb_15_kasa2_tex_txt.inc"
};

u8 obj_shop_umb_15_tuka1_tex_txt[] = {
#include "assets/obj_shop_umb_15_tuka1_tex_txt.inc"
};

Vtx obj_shop_umb15_v[] = {
#include "assets/obj_shop_umb15_v.inc"
};

Gfx obj_shop_umb15_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_15_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_shop_umb_15_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb15_v, 29, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(20, 21, 13, 22, 23, 15, 24, 25, 26, 19, 27, 17),
    gsSPNTriangles_5b(13, 12, 20, 15, 14, 22, 5, 7, 3, 26, 28, 24),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_15_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb15_v[29], 31, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 0, 4, 2, 4, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_15_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(15, 5, 6, 7, 8, 9, 10, 11, 12, 13),
    gsSPNTriangles_5b(14, 15, 16, 17, 18, 19, 20, 21, 17, 17, 19, 22),
    gsSPNTriangles_5b(17, 23, 24, 10, 25, 8, 7, 26, 5, 13, 27, 11),
    gsSPNTriangles_5b(24, 20, 17, 28, 29, 30, 16, 30, 14, 30, 16, 28),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb15_modelT[] = {
    gsSPEndDisplayList(),
};

u16 obj_shop_umb_16_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_16_pal.inc"
};

u8 obj_shop_umb_16_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb_16_kasa1_tex_txt.inc"
};

u8 obj_shop_umb_16_tuka1_tex_txt[] = {
#include "assets/obj_shop_umb_16_tuka1_tex_txt.inc"
};

Vtx obj_shop_umb16_v[] = {
#include "assets/obj_shop_umb16_v.inc"
};

Gfx obj_shop_umb16_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_16_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_16_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb16_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 2, 1, 22, 23, 24, 13, 25, 26, 15),
    gsSPNTriangles_5b(9, 27, 28, 22, 29, 2, 13, 12, 23, 15, 14, 25),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_16_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb16_v[30], 26, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 12, 12, 14, 17),
    gsSPNTriangles_5b(12, 18, 19, 5, 20, 3, 2, 21, 0, 8, 22, 6),
    gsSPNTriangles_5b(19, 15, 12, 23, 24, 25, 11, 25, 9, 25, 11, 23),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb16_modelT[] = {
    gsSPEndDisplayList(),
};

u16 obj_shop_umb_17_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_17_pal.inc"
};

u8 obj_shop_umb_17_tuka1_tex_txt[] = {
#include "assets/obj_shop_umb_17_tuka1_tex_txt.inc"
};

u8 obj_shop_umb_17_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb_17_kasa1_tex_txt.inc"
};

Vtx obj_shop_umb17_v[] = {
#include "assets/obj_shop_umb17_v.inc"
};

Gfx obj_shop_umb17_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_17_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_17_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb17_v, 19, 0),
    gsSPNTrianglesInit_5b(9, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(14, 17, 15, 8, 18, 9, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_17_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsSPVertex(&obj_shop_umb17_v[19], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 8),
    gsSPNTriangles_5b(2, 1, 20, 21, 22, 17, 23, 24, 14, 11, 10, 25),
    gsSPNTriangles_5b(26, 27, 5, 5, 27, 28, 28, 3, 5, 8, 19, 29),
    gsSPNTriangles_5b(29, 6, 8, 30, 31, 2, 20, 30, 2, 0, 0, 0),
    gsSPVertex(&obj_shop_umb17_v[51], 26, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 2, 3, 0, 4, 5, 6),
    gsSPNTriangles_5b(6, 7, 4, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(15, 16, 17, 0, 18, 19, 20, 21, 22, 10, 9, 23),
    gsSPNTriangles_5b(4, 24, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb17_modelT[] = {
    gsSPEndDisplayList(),
};

static u16 tol_umb18_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb01/tol_umb18_pal.inc"
};

static u8 tol_umb18_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb18_kasa1_tex_txt.inc"
};

static u8 tol_umb18_kasa2_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb18_kasa2_tex_txt.inc"
};

static u8 tol_umb18_tuka_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb18_tuka_tex_txt.inc"
};

Vtx obj_shop_umb18_v[] = {
#include "assets/obj_shop_umb18_v.inc"
};

Gfx obj_shop_umb18_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb18_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, tol_umb18_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb18_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 1, 0, 0, 4, 3),
    gsSPNTriangles_5b(5, 6, 7, 5, 8, 9, 9, 6, 5, 10, 11, 12),
    gsSPNTriangles_5b(11, 13, 14, 14, 12, 11, 15, 16, 17, 18, 15, 19),
    gsSPNTriangles_5b(20, 21, 22, 23, 24, 25, 24, 26, 27, 21, 28, 29),
    gsSPNTriangles_5b(17, 19, 15, 29, 22, 21, 27, 25, 24, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, tol_umb18_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb18_v[30], 27, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(4, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb18_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(15, 8, 9, 10, 9, 11, 10, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 19, 18, 20, 17, 16, 21),
    gsSPNTriangles_5b(22, 21, 11, 13, 23, 24, 13, 24, 25, 13, 25, 15),
    gsSPNTriangles_5b(20, 26, 19, 18, 19, 16, 21, 22, 17, 11, 9, 22),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb18_modelT[] = {
    gsSPEndDisplayList(),
};

u16 obj_shop_umb_19_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_19_pal.inc"
};

u8 obj_shop_umb_19_e_tex_txt[] = {
#include "assets/obj_shop_umb_19_e_tex_txt.inc"
};

u8 obj_shop_umb_19_kasa_tex_txt[] = {
#include "assets/obj_shop_umb_19_kasa_tex_txt.inc"
};

u8 obj_shop_umb_19_tuka_tex_txt[] = {
#include "assets/obj_shop_umb_19_tuka_tex_txt.inc"
};

Vtx obj_shop_umb19_v[] = {
#include "assets/obj_shop_umb19_v.inc"
};

Gfx obj_shop_umb19_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_19_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_shop_umb_19_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb19_v, 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_19_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb19_v[8], 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 10, 11, 8, 11, 10, 12),
    gsSPNTriangles_5b(13, 14, 15, 14, 13, 16, 16, 17, 14, 18, 19, 20),
    gsSPNTriangles_5b(20, 21, 18, 21, 20, 22, 23, 24, 25, 24, 23, 26),
    gsSPNTriangles_5b(26, 27, 24, 28, 29, 30, 30, 31, 28, 0, 0, 0),
    gsSPVertex(&obj_shop_umb19_v[40], 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 3, 4, 5, 4, 3, 6),
    gsSPNTriangles_5b(6, 7, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_19_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 11, 16, 11, 10, 18, 19, 17),
    gsSPNTriangles_5b(18, 17, 16, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb19_modelT[] = {
    gsSPEndDisplayList(),
};

u16 obj_shop_umb_20_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_20_pal.inc"
};

u8 obj_shop_umb_20_e_tex_txt[] = {
#include "assets/obj_shop_umb_20_e_tex_txt.inc"
};

u8 obj_shop_umb_20_kasa_tex_txt[] = {
#include "assets/obj_shop_umb_20_kasa_tex_txt.inc"
};

Vtx obj_shop_umb20_v[] = {
#include "assets/obj_shop_umb20_v.inc"
};

Gfx obj_shop_umb20_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_20_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_shop_umb_20_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb20_v, 28, 0),
    gsSPNTrianglesInit_5b(20, 0, 1, 2, 0, 2, 3, 2, 4, 5),
    gsSPNTriangles_5b(2, 5, 3, 6, 7, 8, 6, 8, 9, 4, 6, 9),
    gsSPNTriangles_5b(4, 9, 5, 10, 11, 12, 10, 12, 13, 12, 14, 15),
    gsSPNTriangles_5b(12, 15, 13, 16, 17, 18, 16, 18, 19, 14, 16, 19),
    gsSPNTriangles_5b(14, 19, 15, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_shop_umb_20_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb20_v[28], 11, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 2, 3, 4, 3, 2, 5),
    gsSPNTriangles_5b(6, 3, 5, 3, 6, 7, 7, 4, 3, 2, 1, 5),
    gsSPNTriangles_5b(5, 1, 8, 9, 10, 7, 7, 6, 9, 5, 9, 6),
    gsSPNTriangles_5b(5, 8, 9, 10, 9, 8, 8, 1, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb20_modelT[] = {
    gsSPEndDisplayList(),
};

u16 obj_shop_umb_21_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_21_pal.inc"
};

u8 obj_shop_umb_21_kasa_tex_txt[] = {
#include "assets/obj_shop_umb_21_kasa_tex_txt.inc"
};

u8 obj_shop_umb_21_tuka_tex_txt[] = {
#include "assets/obj_shop_umb_21_tuka_tex_txt.inc"
};

Vtx obj_shop_umb21_v[] = {
#include "assets/obj_shop_umb21_v.inc"
};

Gfx obj_shop_umb21_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_21_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 64, 32, obj_shop_umb_21_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 252),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb21_v, 32, 0),
    gsSPNTrianglesInit_5b(24, 0, 1, 2, 1, 0, 3, 4, 5, 6),
    gsSPNTriangles_5b(5, 4, 2, 7, 8, 2, 8, 7, 9, 10, 11, 12),
    gsSPNTriangles_5b(11, 10, 2, 13, 14, 2, 14, 13, 15, 16, 17, 18),
    gsSPNTriangles_5b(17, 16, 2, 19, 20, 21, 20, 19, 22, 23, 19, 24),
    gsSPNTriangles_5b(21, 24, 19, 21, 25, 26, 27, 26, 25, 24, 26, 28),
    gsSPNTriangles_5b(26, 24, 21, 29, 25, 21, 25, 29, 30, 31, 29, 20),
    gsSPNTriangles_5b(21, 20, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_21_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb21_v[32], 24, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 3, 8, 3, 2, 10, 11, 9),
    gsSPNTriangles_5b(10, 9, 8, 12, 13, 14, 12, 14, 15, 16, 17, 18),
    gsSPNTriangles_5b(16, 18, 19, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb21_modelT[] = {
    gsSPEndDisplayList(),
};

static u16 tol_umb_22_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb01/tol_umb_22_pal.inc"
};

u16 obj_shop_umb_22_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_22_pal.inc"
};

u8 obj_shop_umb_22_kasa_tex_txt[] = {
#include "assets/obj_shop_umb_22_kasa_tex_txt.inc"
};

u8 obj_shop_umb_22_e_tex_txt[] = {
#include "assets/obj_shop_umb_22_e_tex_txt.inc"
};

Vtx obj_shop_umb22_v[] = {
#include "assets/obj_shop_umb22_v.inc"
};

Gfx obj_shop_umb22_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_22_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_22_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb22_v, 32, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 3, 0, 2, 4, 3, 2),
    gsSPNTriangles_5b(1, 5, 2, 5, 6, 2, 6, 4, 2, 7, 8, 9),
    gsSPNTriangles_5b(10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21),
    gsSPNTriangles_5b(22, 23, 24, 25, 26, 27, 28, 29, 30, 0, 0, 0),
    gsSPVertex(&obj_shop_umb22_v[31], 25, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 12, 15, 13, 12, 14, 16),
    gsSPNTriangles_5b(12, 16, 17, 12, 18, 19, 12, 17, 18, 12, 20, 21),
    gsSPNTriangles_5b(12, 21, 15, 12, 22, 20, 12, 23, 22, 12, 19, 24),
    gsSPNTriangles_5b(12, 24, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_22_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_shop_umb_22_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb22_v[56], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb22_modelT[] = {
    gsSPEndDisplayList(),
};

u16 obj_shop_umb_23_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_23_pal.inc"
};

u8 obj_shop_umb_23_kasa_tex_txt[] = {
#include "assets/obj_shop_umb_23_kasa_tex_txt.inc"
};

u8 obj_shop_umb_23_e_tex_txt[] = {
#include "assets/obj_shop_umb_23_e_tex_txt.inc"
};

u8 obj_shop_umb_23_tuka_tex_txt[] = {
#include "assets/obj_shop_umb_23_tuka_tex_txt.inc"
};

Vtx obj_shop_umb23_v[] = {
#include "assets/obj_shop_umb23_v.inc"
};

Gfx obj_shop_umb23_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_23_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 64, obj_shop_umb_23_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb23_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(7, 2, 1, 1, 8, 7, 9, 10, 11, 11, 12, 9),
    gsSPNTriangles_5b(13, 14, 15, 15, 16, 13, 17, 18, 19, 19, 20, 17),
    gsSPNTriangles_5b(21, 22, 23, 23, 24, 21, 6, 5, 25, 26, 19, 18),
    gsSPNTriangles_5b(22, 21, 27, 28, 9, 12, 14, 13, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_shop_umb_23_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb23_v[30], 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_23_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(10, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 11, 16, 11, 10, 18, 19, 17),
    gsSPNTriangles_5b(18, 17, 16, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb23_modelT[] = {
    gsSPEndDisplayList(),
};

u16 obj_shop_umb_24_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_24_pal.inc"
};

u8 obj_shop_umb_24_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb_24_kasa1_tex_txt.inc"
};

u8 obj_shop_umb_24_kasa2_tex_txt[] = {
#include "assets/obj_shop_umb_24_kasa2_tex_txt.inc"
};

u8 obj_shop_umb_24_tuka1_tex_txt[] = {
#include "assets/obj_shop_umb_24_tuka1_tex_txt.inc"
};

Vtx obj_shop_umb24_v[] = {
#include "assets/obj_shop_umb24_v.inc"
};

Gfx obj_shop_umb24_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_24_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_24_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb24_v, 29, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(20, 21, 13, 22, 23, 15, 24, 25, 26, 19, 27, 17),
    gsSPNTriangles_5b(13, 12, 20, 15, 14, 22, 5, 7, 3, 26, 28, 24),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_24_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb24_v[29], 31, 0),
    gsSPNTrianglesInit_5b(3, 0, 1, 2, 3, 0, 4, 2, 4, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_24_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(15, 5, 6, 7, 8, 9, 10, 11, 12, 13),
    gsSPNTriangles_5b(14, 15, 16, 17, 18, 19, 20, 21, 17, 17, 19, 22),
    gsSPNTriangles_5b(17, 23, 24, 10, 25, 8, 7, 26, 5, 13, 27, 11),
    gsSPNTriangles_5b(24, 20, 17, 28, 29, 30, 16, 30, 14, 30, 16, 28),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb24_modelT[] = {
    gsSPEndDisplayList(),
};

static u16 tol_umb_25_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb01/tol_umb_25_pal.inc"
};

static u8 tol_umb_25_ya_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb_25_ya_tex_txt.inc"
};

static u8 tol_umb_25_kasa_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb_25_kasa_tex_txt.inc"
};

Vtx obj_shop_umb25_v[] = {
#include "assets/obj_shop_umb25_v.inc"
};

Gfx obj_shop_umb25_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_25_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 64, tol_umb_25_ya_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb25_v, 28, 0),
    gsSPNTrianglesInit_5b(16, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 17, 20, 21),
    gsSPNTriangles_5b(17, 21, 18, 22, 23, 24, 22, 24, 25, 23, 26, 27),
    gsSPNTriangles_5b(23, 27, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_25_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_REPEAT, 0, 0),
    gsSPVertex(&obj_shop_umb25_v[28], 25, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16),
    gsSPNTriangles_5b(13, 12, 14, 16, 15, 8, 10, 9, 11, 17, 18, 19),
    gsSPNTriangles_5b(17, 19, 20, 21, 22, 23, 21, 23, 24, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb25_modelT[] = {
    gsSPEndDisplayList(),
};

u16 obj_shop_umb_26_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_26_pal.inc"
};

u8 obj_shop_umb_26_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb_26_kasa1_tex_txt.inc"
};

u8 obj_shop_umb_26_kasa2_tex_txt[] = {
#include "assets/obj_shop_umb_26_kasa2_tex_txt.inc"
};

u8 obj_shop_umb_26_tuka1_tex_txt[] = {
#include "assets/obj_shop_umb_26_tuka1_tex_txt.inc"
};

Vtx obj_shop_umb26_v[] = {
#include "assets/obj_shop_umb26_v.inc"
};

Gfx obj_shop_umb26_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_26_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_shop_umb_26_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb26_v, 24, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 12),
    gsSPNTriangles_5b(19, 20, 21, 16, 22, 14, 12, 11, 17, 5, 7, 3),
    gsSPNTriangles_5b(21, 23, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_26_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb26_v[24], 10, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 2, 1, 3, 3, 4, 2),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 9, 9, 7, 6, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_26_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb26_v[34], 26, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 12, 12, 14, 17),
    gsSPNTriangles_5b(12, 18, 19, 5, 20, 3, 2, 21, 0, 8, 22, 6),
    gsSPNTriangles_5b(19, 15, 12, 23, 24, 25, 11, 25, 9, 25, 11, 23),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb26_modelT[] = {
    gsSPEndDisplayList(),
};

u16 obj_shop_umb_27_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_27_pal.inc"
};

u8 obj_shop_umb_27_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb_27_kasa1_tex_txt.inc"
};

u8 obj_shop_umb_27_kasa2_tex_txt[] = {
#include "assets/obj_shop_umb_27_kasa2_tex_txt.inc"
};

u8 obj_shop_umb_27_e_tex_txt[] = {
#include "assets/obj_shop_umb_27_e_tex_txt.inc"
};

Vtx obj_shop_umb27_v[] = {
#include "assets/obj_shop_umb27_v.inc"
};

Gfx obj_shop_umb27_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_27_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_27_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb27_v, 25, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 0, 2, 4, 3, 2),
    gsSPNTriangles_5b(1, 5, 2, 5, 6, 2, 6, 4, 2, 7, 8, 9),
    gsSPNTriangles_5b(10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21),
    gsSPNTriangles_5b(22, 23, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&obj_shop_umb27_v[25], 31, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 0, 3, 1, 0, 2, 4),
    gsSPNTriangles_5b(0, 4, 5, 0, 6, 7, 0, 5, 6, 0, 8, 9),
    gsSPNTriangles_5b(0, 9, 3, 0, 10, 8, 0, 11, 10, 0, 7, 12),
    gsSPNTriangles_5b(0, 12, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_27_kasa2_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(6, 13, 14, 15, 16, 17, 18, 19, 20, 21),
    gsSPNTriangles_5b(22, 23, 24, 25, 26, 27, 28, 29, 30, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, obj_shop_umb_27_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb27_v[56], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb27_modelT[] = {
    gsSPEndDisplayList(),
};

u16 obj_shop_umb_28_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_28_pal.inc"
};

u8 obj_shop_umb_28_kasa_tex_txt[] = {
#include "assets/obj_shop_umb_28_kasa_tex_txt.inc"
};

u8 obj_shop_umb_28_tuka_tex_txt[] = {
#include "assets/obj_shop_umb_28_tuka_tex_txt.inc"
};

Vtx obj_shop_umb28_v[] = {
#include "assets/obj_shop_umb28_v.inc"
};

Gfx obj_shop_umb28_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_28_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_28_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb28_v, 32, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 2, 3, 0, 1, 0, 4),
    gsSPNTriangles_5b(5, 6, 7, 6, 8, 9, 9, 7, 6, 10, 11, 12),
    gsSPNTriangles_5b(13, 14, 15, 11, 10, 16, 17, 18, 19, 18, 20, 21),
    gsSPNTriangles_5b(21, 19, 18, 22, 23, 24, 24, 25, 22, 23, 22, 26),
    gsSPNTriangles_5b(27, 28, 29, 28, 30, 31, 31, 29, 28, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_28_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb28_v[32], 24, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 18, 16, 18, 19, 5, 4, 17),
    gsSPNTriangles_5b(5, 17, 16, 20, 21, 22, 20, 22, 23, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb28_modelT[] = {
    gsSPEndDisplayList(),
};

u16 obj_shop_umb_29_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_29_pal.inc"
};

u8 obj_shop_umb_29_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb_29_kasa1_tex_txt.inc"
};

u8 obj_shop_umb_29_tuka1_tex_txt[] = {
#include "assets/obj_shop_umb_29_tuka1_tex_txt.inc"
};

Vtx obj_shop_umb29_v[] = {
#include "assets/obj_shop_umb29_v.inc"
};

Gfx obj_shop_umb29_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_29_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_29_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb29_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 2, 1, 22, 23, 24, 13, 25, 26, 15),
    gsSPNTriangles_5b(9, 27, 28, 22, 29, 2, 13, 12, 23, 15, 14, 25),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_29_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb29_v[30], 26, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 12, 12, 14, 17),
    gsSPNTriangles_5b(12, 18, 19, 5, 20, 3, 2, 21, 0, 8, 22, 6),
    gsSPNTriangles_5b(19, 15, 12, 23, 24, 25, 11, 25, 9, 25, 11, 23),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb29_modelT[] = {
    gsSPEndDisplayList(),
};

static u16 obj_shop_umb_30_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb01/obj_shop_umb_30_pal.inc"
};

u8 obj_shop_umb_30_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb_30_kasa1_tex_txt.inc"
};

u8 obj_shop_umb_30_tuka1_tex_txt[] = {
#include "assets/obj_shop_umb_30_tuka1_tex_txt.inc"
};

Vtx obj_shop_umb30_v[] = {
#include "assets/obj_shop_umb30_v.inc"
};

Gfx obj_shop_umb30_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_30_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_30_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 252, 124),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb30_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 2, 1, 22, 23, 24, 13, 25, 26, 15),
    gsSPNTriangles_5b(9, 27, 28, 22, 29, 2, 13, 12, 23, 15, 14, 25),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_30_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb30_v[30], 26, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 12, 12, 14, 17),
    gsSPNTriangles_5b(12, 18, 19, 5, 20, 3, 2, 21, 0, 8, 22, 6),
    gsSPNTriangles_5b(19, 15, 12, 23, 24, 25, 11, 25, 9, 25, 11, 23),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb30_modelT[] = {
    gsSPEndDisplayList(),
};

u16 obj_shop_umb_31_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb_31_pal.inc"
};

u8 obj_shop_umb_31_e_tex_txt[] = {
#include "assets/obj_shop_umb_31_e_tex_txt.inc"
};

u8 obj_shop_umb_31_kasa_tex_txt[] = {
#include "assets/obj_shop_umb_31_kasa_tex_txt.inc"
};

u8 obj_shop_umb_31_tuka_tex_txt[] = {
#include "assets/obj_shop_umb_31_tuka_tex_txt.inc"
};

Vtx obj_shop_umb31_v[] = {
#include "assets/obj_shop_umb31_v.inc"
};

Gfx obj_shop_umb31_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_31_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, obj_shop_umb_31_e_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb31_v, 8, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_31_kasa_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb31_v[8], 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 5, 6, 3),
    gsSPNTriangles_5b(7, 2, 1, 1, 8, 7, 9, 10, 11, 11, 12, 9),
    gsSPNTriangles_5b(13, 14, 15, 15, 16, 13, 17, 18, 19, 19, 20, 17),
    gsSPNTriangles_5b(21, 22, 23, 23, 24, 21, 6, 5, 25, 26, 19, 18),
    gsSPNTriangles_5b(22, 21, 27, 28, 9, 12, 14, 13, 29, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_31_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb31_v[38], 16, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 3, 8, 3, 2, 10, 11, 9),
    gsSPNTriangles_5b(10, 9, 8, 12, 13, 14, 12, 14, 15, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb31_modelT[] = {
    gsSPEndDisplayList(),
};

static u16 obj_shop_umb_32_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb01/obj_shop_umb_32_pal.inc"
};

static u8 obj_shop_umb_32_tuka1_tex_txt[] = {
#include "assets/obj_shop_umb01/obj_shop_umb_32_tuka1_tex_txt.inc"
};

static u8 obj_shop_umb_32_kasa1_tex_txt[] = {
#include "assets/obj_shop_umb01/obj_shop_umb_32_kasa1_tex_txt.inc"
};

Vtx obj_shop_umb32_v[] = {
#include "assets/obj_shop_umb32_v.inc"
};

Gfx obj_shop_umb32_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, obj_shop_umb_32_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_32_tuka1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb32_v, 26, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 12, 12, 14, 17),
    gsSPNTriangles_5b(12, 18, 19, 5, 20, 3, 2, 21, 0, 8, 22, 6),
    gsSPNTriangles_5b(19, 15, 12, 23, 24, 25, 11, 25, 9, 25, 11, 23),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, obj_shop_umb_32_kasa1_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&obj_shop_umb32_v[26], 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 2, 1, 22, 23, 24, 13, 25, 26, 15),
    gsSPNTriangles_5b(9, 27, 28, 22, 29, 2, 13, 12, 23, 15, 14, 25),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx obj_shop_umb32_modelT[] = {
    gsSPEndDisplayList(),
};

static u16 tol_umb_w_tuka_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_shop_umb01/tol_umb_w_tuka_pal.inc"
};

static u8 tol_umb_w_tuka_tex_txt[] = {
#include "assets/obj_shop_umb01/tol_umb_w_tuka_tex_txt.inc"
};

Vtx obj_shop_umb_w_v[] = {
#include "assets/obj_shop_umb_w_v.inc"
};

Gfx obj_shop_umbmy_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, anime_1_txt),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_2_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(obj_shop_umb_w_v, 30, 0),
    gsSPNTrianglesInit_5b(18, 0, 1, 2, 3, 4, 5, 6, 3, 7),
    gsSPNTriangles_5b(8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
    gsSPNTriangles_5b(18, 20, 21, 2, 1, 22, 23, 24, 13, 25, 26, 15),
    gsSPNTriangles_5b(9, 27, 28, 22, 29, 2, 13, 12, 23, 15, 14, 25),
    gsSPNTriangles_5b(5, 7, 3, 28, 10, 9, 21, 19, 18, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, tol_umb_w_tuka_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, tol_umb_w_tuka_tex_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&obj_shop_umb_w_v[30], 26, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 12, 13, 14, 15, 16, 12, 12, 14, 17),
    gsSPNTriangles_5b(12, 18, 19, 5, 20, 3, 2, 21, 0, 8, 22, 6),
    gsSPNTriangles_5b(19, 15, 12, 23, 24, 25, 11, 25, 9, 25, 11, 23),
    gsSPEndDisplayList(),
};
