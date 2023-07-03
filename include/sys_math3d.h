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
extern void sMath_RotateX(xyz_t* pos, f32 rad);
extern void sMath_RotateY(xyz_t* pos, f32 rad);
extern void sMath_RotateZ(xyz_t* pos, f32 rad);

extern xyz_t ZeroVec;
extern s_xyz ZeroSVec;

#ifdef __cplusplus
}

#endif
#endif