#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

Vtx obj_w_stoneD_v[] = {
#include "assets/obj_w_stoneD_v.inc"
};

Gfx obj_w_stoneD_gfx_model[] = {
    gsSPVertex(obj_w_stoneD_v, 15, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 3, 8, 1, 8, 9, 1, 3, 10, 8),
    gsSPNTriangles_5b(5, 10, 7, 5, 11, 10, 4, 12, 5, 12, 11, 5),
    gsSPNTriangles_5b(1, 13, 2, 1, 9, 13, 0, 10, 3, 0, 14, 10),
    gsSPNTriangles_5b(7, 14, 6, 7, 10, 14, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
