#ifndef SYS_MATH3D_H
#define SYS_MATH3D_H

#include "types.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct math_3d_linef_s {
    /* 0x0000 */ xyz_t a;
    /* 0x000C */ xyz_t b;
} Math3D_linef_c; // size = 0x18

typedef struct math_3d_pipe_s {
    s16 radius;
    s16 height;
    s16 offset;
    s_xyz center;
} Math3D_pipe_c;

typedef struct math_3d_sphere_s {
    s_xyz center;
    s16 radius;
} Math3D_sphere_c;

typedef struct math_3d_plane_s {
    xyz_t normal;
    f32 originDist;
} Math3D_plane_c; // size = 0x10

typedef struct math_3d_triangle_s {
    xyz_t vtx[3];
    Math3D_plane_c plane;
} Math3D_triangle_c; // size = 0x34

typedef struct math_3d_spheref_s {
    xyz_t center;
    f32 radius;
} Math3D_sphereF_c;

typedef struct math_3d_pipef_s {
    f32 radius;
    f32 height;
    f32 offset;
    xyz_t center;
} Math3D_pipeF_c;

// extern f32 Math3DVecLength(xyz_t* vec);
// extern f32 Math3DVecLengthSquare2D(f32 x, f32 y);
// extern void sMath_RotateX(xyz_t* pos, f32 rad);
// extern void sMath_RotateY(xyz_t* pos, f32 rad);
// extern void sMath_RotateZ(xyz_t* pos, f32 rad);
// extern f32 Math3d_normalizeXyz_t(xyz_t* vec);
// extern f32 Math3DLength(xyz_t* v0, xyz_t* v1);
// extern void Math3DInDivPos2(const xyz_t* v0, const xyz_t* v1, xyz_t* v2, f32 percent);
// extern void Math3DPlane(xyz_t* va, xyz_t* vb, xyz_t* vc, f32* nox, f32* noy, f32* noz, f32* odist);
// extern int Math3D_sphereCrossSphere_cl(Math3D_sphere_c* a, Math3D_sphere_c* b, f32* in);
// extern int Math3D_sphereVsPipe_cl(Math3D_sphere_c* s, Math3D_pipe_c* c, f32* in);
// extern int Math3D_pipeVsPipe_cl(Math3D_pipe_c* a, Math3D_pipe_c* b, f32* d);
// extern int Math3D_sphereCrossTriangle3_cp(Math3D_sphere_c* s, Math3D_triangle_c* tri, xyz_t* ip);
// extern int Math3D_pipeCrossTriangle_cp(Math3D_pipe_c* c, Math3D_triangle_c* tri, xyz_t* in);
// extern void Math3DVectorProduct2Vec(const xyz_t* a, xyz_t* b, xyz_t* ret);

extern f32 Math3d_normalizeXyz_t(xyz_t* a);
extern void Math3DInDivPos1(const xyz_t* v, const xyz_t* d, f32 t, xyz_t* c);
extern void Math3DInDivPos2(const xyz_t* v, const xyz_t* d, xyz_t* c, f32 t);
extern f32 Math3DVecLengthSquare2D(f32 a, f32 b);
extern f32 Math3DVecLength2D(f32 a, f32 b);
extern f32 Math3DLengthSquare2D(f32 x0, f32 y0, f32 x1, f32 y1);
extern f32 Math3DLength2D(f32 x0, f32 x1, f32 y0, f32 y1);
extern f32 Math3DVecLengthSquare(xyz_t* v);
extern f32 Math3DVecLength(xyz_t* v);
extern f32 Math3DLengthSquare(xyz_t* a, xyz_t* b);
extern f32 Math3DLength(const xyz_t* a, const xyz_t* b);
extern void Math3DVectorProduct2Vec(const xyz_t* a, const xyz_t* b, xyz_t* ret);
extern void Math3DVectorProductXYZ(xyz_t* va, xyz_t* vb, xyz_t* vc, xyz_t* ret);
extern void Math3DPlane(xyz_t* va, xyz_t* vb, xyz_t* vc, f32* nox, f32* noy, f32* noz, f32* odist);
extern f32 Math3DPlaneFunc(f32 nox, f32 noy, f32 noz, f32 odist, const xyz_t* pl);
extern f32 Math3DLengthPlaneAndPos(f32 nox, f32 noy, f32 noz, f32 odist, const xyz_t* pl);
extern f32 Math3DSignedLengthPlaneAndPos(f32 nox, f32 noy, f32 noz, f32 odist, const xyz_t* pl);
extern int Math3DTriangleCrossYCheck_general(xyz_t* v0, xyz_t* v1, xyz_t* v2, f32 z, f32 x, f32 dt, f32 dist, f32 noy);
extern int Math3DTriangleCrossYLine_scope(xyz_t* v0, xyz_t* v1, xyz_t* v2, f32 nox, f32 noy, f32 noz, f32 dst, f32 z,
                                          f32 x, f32* yint, f32 y0, f32 y1);
extern int Math3DTriangleCrossZCheck_general(xyz_t* v0, xyz_t* v1, xyz_t* v2, f32 x, f32 y, f32 dt, f32 dist, f32 noz);
extern int Math3D_sphereCollisionPoint(Math3D_sphere_c* s, xyz_t* p);
extern int Math3D_pointVsLineSegmentLengthSquare2D(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2, f32* lsq);
extern int Math3D_sphereCrossLineSegment(Math3D_sphere_c* s, Math3D_linef_c* l);
extern void Math3D_sphereCrossTriangleCalc_cp(Math3D_sphere_c* s, Math3D_triangle_c* tri, xyz_t* ip);
extern int Math3D_sphereCrossTriangle3_cp(Math3D_sphere_c* s, Math3D_triangle_c* tri, xyz_t* ip);
extern int Math3D_pipeVsPos(Math3D_pipe_c* c, xyz_t* p);
extern int Math3D_pipeCrossLine(Math3D_pipe_c* c, xyz_t* la, xyz_t* lb, xyz_t* ia, xyz_t* ib);
extern int Math3D_pipeCrossTriangle_cp(Math3D_pipe_c* c, Math3D_triangle_c* tri, xyz_t* in);
extern int Math3D_sphereCrossSphere_cl(Math3D_sphere_c* a, Math3D_sphere_c* b, f32* in);
extern int Math3D_sphereCrossSphere_cl_cc(Math3D_sphere_c* a, Math3D_sphere_c* b, f32* in, f32* cdist);
extern int Math3D_sphereVsPipe_cl(Math3D_sphere_c* s, Math3D_pipe_c* c, f32* in);
extern int Math3D_sphereVsPipe_cl_cc(Math3D_sphere_c* s, Math3D_pipe_c* c, f32* in, f32* cdist);
extern int Math3D_pipeVsPipe_cl(Math3D_pipe_c* a, Math3D_pipe_c* b, f32* d);
extern int Math3D_pipeVsPipe_cl_cc(Math3D_pipe_c* a, Math3D_pipe_c* b, f32* d, f32* di);
extern void sMath_RotateY(xyz_t* v, f32 y);
extern void sMath_RotateX(xyz_t* v, f32 x);
extern void sMath_RotateZ(xyz_t* v, f32 z);

extern xyz_t ZeroVec;
extern s_xyz ZeroSVec;

#ifdef __cplusplus
}

#endif
#endif
