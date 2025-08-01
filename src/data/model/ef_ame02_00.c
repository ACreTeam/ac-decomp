#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 ef_ame02_0[] = {
#include "assets/ef_ame02_0.inc"
};

Vtx ef_ame02_00_v[] = {
#include "assets/ef_ame02_00_v.inc"
};

Gfx ef_ame02_setmode[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 50, 50, 80),
    gsDPSetEnvColor(100, 225, 225, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 16, ef_ame02_0),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx ef_ame02_00_modelT[] = {
    gsSPVertex(ef_ame02_00_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Vtx ef_ame02_01_v[] = {
#include "assets/ef_ame02_01_v.inc"
};

Gfx ef_ame02_01_modelT[] = {
    gsSPVertex(ef_ame02_01_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Vtx ef_ame02_02_v[] = {
#include "assets/ef_ame02_02_v.inc"
};

Gfx ef_ame02_02_modelT[] = {
    gsSPVertex(ef_ame02_02_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Vtx ef_ame02_03_v[] = {
#include "assets/ef_ame02_03_v.inc"
};

Gfx ef_ame02_03_modelT[] = {
    gsSPVertex(ef_ame02_03_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Vtx ef_ame02_04_v[] = {
#include "assets/ef_ame02_04_v.inc"
};

Gfx ef_ame02_04_modelT[] = {
    gsSPVertex(ef_ame02_04_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};
