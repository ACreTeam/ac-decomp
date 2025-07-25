#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

Vtx obj_s_tree5_apple_v[] = {
#include "assets/obj_s_tree5_apple_v.inc"
};

Gfx obj_s_tree5_apple_appleT_gfx_model[] = {
    gsSPVertex(obj_s_tree5_apple_v, 12, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 0, 2, 3, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 8, 9, 10, 8, 10, 11, 0, 0, 0),
    gsSPEndDisplayList(),
};
