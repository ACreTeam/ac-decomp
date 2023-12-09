#include "m_skin_matrix.h"

#include "m_lib.h"

// #include "orderfloats/80643310_80643318.inc"

extern void Skin_Matrix_PrjMulVector(MtxF* mf, xyz_t* src, xyz_t* dst, f32* w) {
  dst->x = mf->xw + ((src->x * mf->xx) + (src->y * mf->xy) + (src->z * mf->xz));
  dst->y = mf->yw + ((src->x * mf->yx) + (src->y * mf->yy) + (src->z * mf->yz));
  dst->z = mf->zw + ((src->x * mf->zx) + (src->y * mf->zy) + (src->z * mf->zz));
  *w = mf->ww + ((src->x * mf->wx) + (src->y * mf->wy) + (src->z * mf->wz));
}

/* @unused void Skin_matrix_MulVector(MtxF* mf, xyz_t* src, xyz_t* dst) */

extern void Skin_Matrix_MulMatrix(MtxF* mfA, MtxF* mfB, MtxF* dest) {
  f32 cx;
  f32 cy;
  f32 cz;
  f32 cw;
  //---ROW1---
  f32 rx = mfA->xx;
  f32 ry = mfA->xy;
  f32 rz = mfA->xz;
  f32 rw = mfA->xw;
  //--------

  cx = mfB->xx;
  cy = mfB->yx;
  cz = mfB->zx;
  cw = mfB->wx;
  dest->xx = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

  cx = mfB->xy;
  cy = mfB->yy;
  cz = mfB->zy;
  cw = mfB->wy;
  dest->xy = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

  cx = mfB->xz;
  cy = mfB->yz;
  cz = mfB->zz;
  cw = mfB->wz;
  dest->xz = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

  cx = mfB->xw;
  cy = mfB->yw;
  cz = mfB->zw;
  cw = mfB->ww;
  dest->xw = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

  //---ROW2---
  rx = mfA->yx;
  ry = mfA->yy;
  rz = mfA->yz;
  rw = mfA->yw;
  //--------
  cx = mfB->xx;
  cy = mfB->yx;
  cz = mfB->zx;
  cw = mfB->wx;
  dest->yx = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

  cx = mfB->xy;
  cy = mfB->yy;
  cz = mfB->zy;
  cw = mfB->wy;
  dest->yy = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

  cx = mfB->xz;
  cy = mfB->yz;
  cz = mfB->zz;
  cw = mfB->wz;
  dest->yz = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

  cx = mfB->xw;
  cy = mfB->yw;
  cz = mfB->zw;
  cw = mfB->ww;
  dest->yw = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

  //---ROW3---
  rx = mfA->zx;
  ry = mfA->zy;
  rz = mfA->zz;
  rw = mfA->zw;
  //--------
  cx = mfB->xx;
  cy = mfB->yx;
  cz = mfB->zx;
  cw = mfB->wx;
  dest->zx = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

  cx = mfB->xy;
  cy = mfB->yy;
  cz = mfB->zy;
  cw = mfB->wy;
  dest->zy = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

  cx = mfB->xz;
  cy = mfB->yz;
  cz = mfB->zz;
  cw = mfB->wz;
  dest->zz = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

  cx = mfB->xw;
  cy = mfB->yw;
  cz = mfB->zw;
  cw = mfB->ww;
  dest->zw = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

  //---ROW4---
  rx = mfA->wx;
  ry = mfA->wy;
  rz = mfA->wz;
  rw = mfA->ww;
  //--------
  cx = mfB->xx;
  cy = mfB->yx;
  cz = mfB->zx;
  cw = mfB->wx;
  dest->wx = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

  cx = mfB->xy;
  cy = mfB->yy;
  cz = mfB->zy;
  cw = mfB->wy;
  dest->wy = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

  cx = mfB->xz;
  cy = mfB->yz;
  cz = mfB->zz;
  cw = mfB->wz;
  dest->wz = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);

  cx = mfB->xw;
  cy = mfB->yw;
  cz = mfB->zw;
  cw = mfB->ww;
  dest->ww = (rx * cx) + (ry * cy) + (rz * cz) + (rw * cw);
}

/* @unused Skin_Matrix_getUnitMatrixPointer(MtxF* mf_p) */

/* @unused Skin_Matrix_SetUnitMatrix(MtxF* mf_p) */

#ifdef MUST_MATCH
/* @unused | necessary for float ordering, from DnM */
extern void FORCESTRIP Skin_Matrix_SetUnitMatrix(MtxF* mf_p) {
  mf_p->xx = 1.0f;
  mf_p->yx = 0.0f;
  mf_p->zx = 0.0f;
  mf_p->wx = 0.0f;

  mf_p->xy = 0.0f;
  mf_p->yy = 1.0f;
  mf_p->zy = 0.0f;
  mf_p->wy = 0.0f;

  mf_p->xz = 0.0f;
  mf_p->yz = 0.0f;
  mf_p->zz = 1.0f;
  mf_p->wz = 0.0f;

  mf_p->xw = 0.0f;
  mf_p->yw = 0.0f;
  mf_p->zw = 0.0f;
  mf_p->ww = 1.0f;
}
#endif

/* @unused Skin_Matrix_Copy */

/* @unused Skin_Matrix_InverseMatrix */

extern void Skin_Matrix_SetScale(MtxF* mf, f32 x, f32 y, f32 z) {
  mf->yx = 0.0f;
  mf->zx = 0.0f;
  mf->wx = 0.0f;
  mf->xy = 0.0f;
  mf->zy = 0.0f;
  mf->wy = 0.0f;
  mf->xz = 0.0f;
  mf->yz = 0.0f;
  mf->wz = 0.0f;
  mf->xw = 0.0f;
  mf->yw = 0.0f;
  mf->zw = 0.0f;
  mf->ww = 1.0f;
  mf->xx = x;
  mf->yy = y;
  mf->zz = z;
}

extern void Skin_Matrix_SetRotateXyz_s(MtxF* mf, s16 x, s16 y, s16 z) {
  f32 cos;
  f32 sinZ = sin_s(z);
  f32 cosZ = cos_s(z);
  f32 xy;
  f32 sin;
  f32 xz;
  f32 yy;
  f32 yz;
  f32 zz;

  mf->yy = cosZ;
  mf->xy = -sinZ;

  mf->wz = 0.0f;
  mf->wy = 0.0f;
  mf->wx = 0.0f;

  mf->zw = 0.0f;
  mf->yw = 0.0f;
  mf->xw = 0.0f;
  mf->ww = 1.0f;

  if (y != 0) {
    sin = sin_s(y);
    cos = cos_s(y);

    mf->xx = cosZ * cos;
    mf->xz = cosZ * sin;

    mf->yx = sinZ * cos;
    mf->yz = sinZ * sin;
    mf->zx = -sin;
    mf->zz = cos;

  } else {
    mf->xx = cosZ;
    mf->yx = sinZ;
    mf->yz = 0.0f;
    mf->xz = 0.0f;
    mf->zx = 0.0f;
    mf->zz = 1.0f;
  }

  if (x != 0) {
    sin = sin_s(x);
    cos = cos_s(x);

    xy = mf->xy;
    xz = mf->xz;
    mf->xy = (xy * cos) + (xz * sin);
    mf->xz = -(xy * sin) + (xz * cos);

    yy = mf->yy;
    yz = mf->yz;
    mf->yy = (yy * cos) + (yz * sin);
    mf->yz = -(yy * sin) + (yz * cos);

    zz = mf->zz;

    mf->zy = zz * sin;
    mf->zz = zz * cos;
  } else {
    mf->zy = 0.0f;
  }
}

extern void Skin_Matrix_SetTranslate(MtxF* mf, f32 x, f32 y, f32 z) {
  mf->yx = 0.0f;
  mf->zx = 0.0f;
  mf->wx = 0.0f;
  mf->xy = 0.0f;
  mf->zy = 0.0f;
  mf->wy = 0.0f;
  mf->xz = 0.0f;
  mf->yz = 0.0f;
  mf->wz = 0.0f;
  mf->xx = 1.0f;
  mf->yy = 1.0f;
  mf->zz = 1.0f;
  mf->ww = 1.0f;
  mf->xw = x;
  mf->yw = y;
  mf->zw = z;
}