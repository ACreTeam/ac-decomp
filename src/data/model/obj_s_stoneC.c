#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"

Vtx obj_s_stoneC_v[] = {
#include "assets/obj_s_stoneC_v.inc"
};

Gfx obj_s_stoneC_gfx_model[] = {
    gsSPVertex(obj_s_stoneC_v, 12, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 3, 4, 0, 3, 0, 2),
    gsSPNTriangles_5b(5, 6, 7, 8, 9, 5, 8, 5, 7, 10, 4, 3),
    gsSPNTriangles_5b(7, 6, 10, 7, 10, 3, 11, 8, 7, 11, 7, 3),
    gsSPNTriangles_5b(11, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
