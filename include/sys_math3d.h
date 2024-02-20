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

typedef struct math_3d_sphere_s{
  s_xyz center;
  s16 radius;
}Math3D_sphere_c;

typedef struct math_3d_plane_s {
  xyz_t normal;
  f32 originDist;
} Math3D_plane_c; // size = 0x10

typedef struct math_3d_triangle_s {
  xyz_t vtx[3];
  Math3D_plane_c plane;
} Math3D_triangle_c; // size = 0x34

extern f32 Math3DVecLength(xyz_t* vec);
extern f32 Math3DVecLengthSquare2D(f32 x, f32 y);
extern void sMath_RotateX(xyz_t* pos, f32 rad);
extern void sMath_RotateY(xyz_t* pos, f32 rad);
extern void sMath_RotateZ(xyz_t* pos, f32 rad);
extern f32 Math3d_normalizeXyz_t(xyz_t* vec);
extern f32 Math3DLength(xyz_t* v0, xyz_t* v1);
extern void Math3DInDivPos2(const xyz_t* v0, const xyz_t* v1, xyz_t* v2, f32 percent);
extern void Math3DPlane(xyz_t* va, xyz_t* vb, xyz_t* vc, f32* nox, f32* noy, f32* noz, f32* odist);
extern int Math3D_sphereCrossSphere_cl(Math3D_sphere_c* a, Math3D_sphere_c* b, f32* in);
extern int Math3D_sphereVsPipe_cl(Math3D_sphere_c* s, Math3D_pipe_c* c, f32* in);
extern int Math3D_pipeVsPipe_cl(Math3D_pipe_c* a, Math3D_pipe_c* b , f32* d);
extern int Math3D_sphereCrossTriangle3_cp(Math3D_sphere_c* s, Math3D_triangle_c* tri, xyz_t* ip);
extern int Math3D_pipeCrossTriangle_cp(Math3D_pipe_c* c,Math3D_triangle_c* tri, xyz_t* in);
extern void Math3DVectorProduct2Vec(const xyz_t* a, xyz_t* b, xyz_t* ret);

extern xyz_t ZeroVec;
extern s_xyz ZeroSVec;

#ifdef __cplusplus
}

#endif
#endif