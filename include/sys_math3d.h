#ifndef SYS_MATH3D_H
#define SYS_MATH3D_H

#include "types.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct math_3d_pipe_s {
  s16 radius;
  s16 height;
  s16 offset;
  s_xyz center;
} Math3D_pipe_c;

extern f32 Math3DVecLength(xyz_t* vec);

extern xyz_t ZeroVec;

#ifdef __cplusplus
}

#endif
#endif