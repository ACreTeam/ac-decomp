#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

Vtx obj_s_stoneE_v[] = {
#include "assets/obj_s_stoneE_v.inc"
};

Gfx obj_s_stoneE_gfx_model[] = {
    gsSPVertex(obj_s_stoneE_v, 15, 0),
    gsSPNTrianglesInit_5b(17, 0, 1, 2, 0, 3, 1, 4, 3, 5),
    gsSPNTriangles_5b(4, 1, 3, 3, 6, 5, 3, 0, 6, 4, 7, 1),
    gsSPNTriangles_5b(7, 2, 1, 8, 6, 9, 6, 0, 9, 10, 11, 12),
    gsSPNTriangles_5b(10, 13, 11, 9, 14, 10, 9, 0, 14, 14, 13, 10),
    gsSPNTriangles_5b(8, 9, 12, 9, 10, 12, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
