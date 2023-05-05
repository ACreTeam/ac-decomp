#ifndef ULTRATYPES_H
#define ULTRATYPES_H

#include "types.h"

typedef float MtxF_t[4][4];



typedef union {
    struct {


        float xx, yx, zx, wx,
              xy, yy, zy, wy,
              xz, yz, zz, wz,
              xw, yw, zw, ww;
    };
    MtxF_t mf;
} MtxF;

typedef struct {
    f32 x, y, z;
} Vec3f;

#endif
