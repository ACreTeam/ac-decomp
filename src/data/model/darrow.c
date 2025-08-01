#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx camera_v[];
extern Vtx darrow_v[];
u8 no_txt[] = {
#include "assets/no_txt.inc"
};

u8 np_txt[] = {
#include "assets/np_txt.inc"
};

u8 nt_txt[] = {
#include "assets/nt_txt.inc"
};

u8 nx_txt[] = {
#include "assets/nx_txt.inc"
};

Gfx darrow_model[] = {
    gsSPVertex(darrow_v, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 11, 9, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSP2Triangles(20, 21, 22, 0, 23, 24, 25, 0),
    gsSP2Triangles(26, 23, 25, 0, 24, 26, 25, 0),
    gsSP2Triangles(27, 28, 29, 0, 30, 31, 29, 0),
    gsSPVertex(&darrow_v[32], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Vtx darrow_v[] = {
#include "assets/darrow_v.inc"
};

Gfx camera_model[] = {
    gsSPVertex(camera_v, 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(3, 4, 2, 0, 5, 0, 2, 0),
    gsSP2Triangles(4, 6, 2, 0, 6, 5, 2, 0),
    gsSP2Triangles(7, 8, 9, 0, 8, 10, 11, 0),
    gsSP2Triangles(8, 11, 12, 0, 7, 10, 8, 0),
    gsSP2Triangles(13, 14, 15, 0, 13, 15, 16, 0),
    gsSP2Triangles(17, 18, 19, 0, 17, 20, 18, 0),
    gsSP2Triangles(21, 22, 23, 0, 22, 24, 23, 0),
    gsSP2Triangles(25, 26, 23, 0, 26, 27, 23, 0),
    gsSP2Triangles(27, 28, 29, 0, 30, 31, 29, 0),
    gsSPVertex(&camera_v[32], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPEndDisplayList(),
};

Vtx camera_v[] = {
#include "assets/camera_v.inc"
};

u8 v_debug_texture[] = {
#include "assets/v_debug_texture.inc"
};

Gfx RCP_debug_texture_16x16_8[] = {
    gsSPVertex(v_debug_texture, 4, 0),
    gsSP2Triangles(0, 2, 1, 0, 1, 2, 3, 0),
    gsSPEndDisplayList(),
};
