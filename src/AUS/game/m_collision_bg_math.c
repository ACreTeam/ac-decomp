#include "m_collision_bg.h"
#include "sys_math3d.h"

extern void mCoBG_RotateY(f32* pos, f32 rad) {
    f32 p[2];
    f32 cos;
    f32 sin;

    cos = cosf_table(rad);
    sin = sinf_table(rad);
    p[0] = pos[0];
    p[1] = pos[1];

    pos[0] = p[0] * cos + p[1] * sin;
    pos[1] = -p[0] * sin + p[1] * cos;
}

extern f32 mCoBG_GetVectorProductin2D(f32* vec0_xz, f32* vec1_xz) {
    return vec0_xz[0] * vec1_xz[1] - vec0_xz[1] * vec1_xz[0];
}

static void mCoBG_JudgeCrossTriangleAndLine2D_XY(f32* m0, f32* m1, const xyz_t* v0, const xyz_t* v1, const xyz_t* v2) {
    *m0 = (v0->x * v1->y - v0->y * v1->x) * (v0->x * v2->y - v0->y * v2->x);
    *m1 = (v2->x * v0->y - v2->y * v0->x) * (v2->x * v1->y - v2->y * v1->x);
}

static void mCoBG_JudgeCrossTriangleAndLine2D_XZ(f32* m0, f32* m1, const xyz_t* v0, const xyz_t* v1, const xyz_t* v2) {
    *m0 = (v0->x * v1->z - v0->z * v1->x) * (v0->x * v2->z - v0->z * v2->x);
    *m1 = (v2->x * v0->z - v2->z * v0->x) * (v2->x * v1->z - v2->z * v1->x);
}

static void mCoBG_JudgeCrossTriangleAndLine2D_YZ(f32* m0, f32* m1, const xyz_t* v0, const xyz_t* v1, const xyz_t* v2) {
    *m0 = (v0->y * v1->z - v0->z * v1->y) * (v0->y * v2->z - v0->z * v2->y);
    *m1 = (v2->y * v0->z - v2->z * v0->y) * (v2->y * v1->z - v2->z * v1->y);
}

typedef void (*mCoBG_PRO_DIMENSION_PROC)(f32* m0, f32* m1, const xyz_t* v0, const xyz_t* v1, const xyz_t* v2);

static mCoBG_PRO_DIMENSION_PROC mCoBG_pro_dimension_proc[] = {
    &mCoBG_JudgeCrossTriangleAndLine2D_XY,
    &mCoBG_JudgeCrossTriangleAndLine2D_XZ,
    &mCoBG_JudgeCrossTriangleAndLine2D_YZ,
    NULL,
};

extern int mCoBG_JudgeCrossTriangleAndLine2D(xyz_t v0, xyz_t v1, xyz_t v2, xyz_t p, int dim) {
    xyz_t vec0;
    xyz_t vec1;
    xyz_t vec2;

    vec0.x = v0.x - p.x;
    vec0.y = v0.y - p.y;
    vec0.z = v0.z - p.z;

    vec1.x = v1.x - p.x;
    vec1.y = v1.y - p.y;
    vec1.z = v1.z - p.z;

    vec2.x = v2.x - p.x;
    vec2.y = v2.y - p.y;
    vec2.z = v2.z - p.z;

    // Doesn't this mean the mCoBG_DIM_ALL path can never be hit?
    if (CLAMP(dim, 0, dim) > mCoBG_DIM_YZ) {
        dim = mCoBG_DIM_YZ;
    } else {
        dim = CLAMP(dim, 0, dim);
    }

    if (dim == mCoBG_DIM_ALL) {
        f32 m0;
        f32 m1;

        (*mCoBG_pro_dimension_proc[mCoBG_DIM_XZ])(&m0, &m1, &vec0, &vec1, &vec2);
        if (m0 <= 0.0f && m1 <= 0.0f) {
            (*mCoBG_pro_dimension_proc[mCoBG_DIM_XY])(&m0, &m1, &vec0, &vec1, &vec2);
            if (m0 <= 0.0f && m1 <= 0.0f) {
                (*mCoBG_pro_dimension_proc[mCoBG_DIM_YZ])(&m0, &m1, &vec0, &vec1, &vec2);
                if (m0 <= 0.0f && m1 <= 0.0f) {
                    return TRUE;
                }
            }
        }
    } else {
        f32 m0 = 0.0f;
        f32 m1 = 0.0f;

        (*mCoBG_pro_dimension_proc[dim])(&m0, &m1, &vec0, &vec1, &vec2);
        if (m0 <= 0.0f && m1 <= 0.0f) {
            return TRUE;
        }
    }

    return FALSE;
}

extern int mCoBG_GetDimension2Idx(f32 p0, f32 p1, f32 p2) {
    if (F32_IS_ZERO(p0) && F32_IS_ZERO(p2)) {
        return mCoBG_DIM_XZ;
    }

    if (F32_IS_ZERO(p0) && F32_IS_ZERO(p1)) {
        return mCoBG_DIM_XY;
    }

    if (F32_IS_ZERO(p1) && F32_IS_ZERO(p2)) {
        return mCoBG_DIM_YZ;
    }

    return mCoBG_DIM_ALL;
}

extern int mCoBG_GetCrossTriangleAndLine3D(xyz_t* cross, xyz_t v0, xyz_t v1, xyz_t v2, xyz_t line0, xyz_t line1) {
    f32 x;
    f32 y;
    f32 z;
    f32 nox;
    f32 noy;
    f32 noz;
    f32 dist;
    f32 ldist;
    f32 t;
    f32 scale;

    cross->x = 0.0f;
    cross->y = 0.0f;
    cross->z = 0.0f;

    Math3DPlane(&v0, &v1, &v2, &nox, &noy, &noz, &dist);
    t = (nox * line0.x + noy * line0.y + noz * line0.z) + dist;
    x = line0.x - line1.x;
    y = line0.y - line1.y;
    z = line0.z - line1.z;
    ldist = nox * x + noy * y + noz * z;
    if (!F32_IS_ZERO(ldist)) {
        int dim;

        scale = -(t / ldist);
        cross->x = line0.x + x * scale;
        cross->y = line0.y + y * scale;
        cross->z = line0.z + z * scale;
        dim = mCoBG_GetDimension2Idx(nox, noy, noz);
        return mCoBG_JudgeCrossTriangleAndLine2D(v0, v1, v2, *cross, dim);
    }

    return FALSE;
}

extern f32 mCoBG_GetVectorScalar2D(f32* v0, f32* v1) {
    return v0[0] * v1[0] + v0[1] * v1[1];
}

extern int mCoBG_GetCrossJudge_2Vector(f32* vec0_p0, f32* vec0_p1, f32* vec1_p0, f32* vec1_p1) {
    f32 v0[2];
    f32 v1[2];
    f32 v2[2];
    f32 product0;
    f32 product1;

    v0[0] = vec1_p1[0] - vec0_p0[0];
    v0[1] = vec1_p1[1] - vec0_p0[1];
    v1[0] = vec0_p1[0] - vec0_p0[0];
    v1[1] = vec0_p1[1] - vec0_p0[1];
    v2[0] = vec1_p0[0] - vec0_p0[0];
    v2[1] = vec1_p0[1] - vec0_p0[1];
    product0 = mCoBG_GetVectorProductin2D(v1, v0) * mCoBG_GetVectorProductin2D(v1, v2);

    v0[0] = vec0_p1[0] - vec1_p0[0];
    v0[1] = vec0_p1[1] - vec1_p0[1];
    v1[0] = vec1_p1[0] - vec1_p0[0];
    v1[1] = vec1_p1[1] - vec1_p0[1];
    v2[0] = vec0_p0[0] - vec1_p0[0];
    v2[1] = vec0_p0[1] - vec1_p0[1];
    product1 = mCoBG_GetVectorProductin2D(v1, v0) * mCoBG_GetVectorProductin2D(v1, v2);

    if (product0 < 0.0f && product1 < 0.0f) {
        return TRUE;
    }

    return FALSE;
}

extern void mCoBG_GetCross2Line(f32* cross,
                                f32* line0_p0,
                                f32* line0_p1,
                                f32* line1_p0,
                                f32* line1_p1)
{
    f32 t;
    f32 vec[2];

    vec[0] = line0_p1[0] - line0_p0[0];
    vec[1] = line0_p1[1] - line0_p0[1];

    t = 
      ( 
          ( ( line1_p0[0] - line0_p0[0] ) * ( line1_p1[1] - line1_p0[1] ) ) +
          ( ( line1_p1[0] - line1_p0[0] ) * ( line0_p0[1] - line1_p0[1] ) )
      )
      /
      (
          ( (line1_p1[1] - line1_p0[1]) * ( line0_p1[0] - line0_p0[0] ) ) -
          ( (line0_p1[1] - line0_p0[1]) * ( line1_p1[0] - line1_p0[0] ) )
      );

    cross[0] = line0_p0[0] + t * vec[0];
    cross[1] = line0_p0[1] + t * vec[1];
}

extern f32 mCoBG_Get2VectorAngleF(f32* v0, f32* v1, u8 unit) {
    if (v0[0] != 0.0f || v0[1] != 0.0f || v1[0] != 0.0f || v1[1] != 0.0f) {
        switch (unit) {
            case mCoBG_UNIT_RADIAN:
                return atanf_table(mCoBG_GetVectorScalar2D(v0, v1), mCoBG_GetVectorProductin2D(v0, v1));
            case mCoBG_UNIT_DEGREE:
                return RAD2DEG(atanf_table(mCoBG_GetVectorScalar2D(v0, v1), mCoBG_GetVectorProductin2D(v0, v1)));
            default:
                return 1.0f;
        }
    }

    return 1.0f;
}

// @unused, @fabricated
extern s16 mCoBG_Get2VectorAngleS(f32* v0, f32* v1) {
    if (v0[0] != 0.0f || v0[1] != 0.0f || v1[0] != 0.0f || v1[1] != 0.0f) {
        return atans_table(mCoBG_GetVectorScalar2D(v0, v1), mCoBG_GetVectorProductin2D(v0, v1));
    }

    return 1;
}

extern int mCoBG_GetCrossLineAndPerpendicular(f32* cross, f32* p0, f32* p1, f32* target) {
    f32 vec[2];
    f32 len;
    f32 t;

    vec[0] = p1[0] - p0[0];
    vec[1] = p1[1] - p0[1];
    len = SQ(vec[0]) + SQ(vec[1]);
    if (len != 0.0f) {
        t = (-vec[0] * (p0[0] - target[0]) + -vec[1] * (p0[1] - target[1])) / len;
        cross[0] = p0[0] + t * vec[0];
        cross[1] = p0[1] + t * vec[1];
        return TRUE;
    }

    cross[0] = 0.0f;
    cross[1] = 0.0f;
    return FALSE;
}

extern int mCoBG_GetPointInfoFrontLine(f32* start, f32* point, f32* normal) {
    f32 a = normal[0];
    f32 b = normal[1];
    f32 a2 = a * point[0];
    f32 b2 = b * point[1];
    f32 c = -(a * start[0] + b * start[1]);

    if ((a2 + b2) + c >= 0.0f) {
        return TRUE;
    }

    return FALSE;
}

/* @unused, @fabricated */
extern int mCoBG_GetDistPointAndLine2D(f32* dist, f32* line0, f32* line1, f32* point) {
    f32 cross[2];
    f32 dist_xy[2];

    if (mCoBG_GetCrossLineAndPerpendicular(cross, line0, line1, point)) {
        dist_xy[0] = point[0] - cross[0];
        dist_xy[1] = point[1] - cross[1];

        dist[0] = ABS(sqrtf(SQ(dist_xy[0]) + SQ(dist_xy[1])));
        return TRUE;
    }

    dist[0] = 0.0f;
    dist[1] = 0.0f;
    return FALSE;
}

extern int mCoBG_GetDistPointAndLine2D_Norm(f32* dist, f32* line0, f32* line1, f32* normal, f32* point) {
    f32 a = normal[0];
    f32 b = normal[1];
    f32 a2 = a * point[0];
    f32 b2 = b * point[1];
    f32 c = -(a * line0[0] + b * line0[1]);
    f32 d = (a2 + b2) + c;
    
    dist[0] = ABS(d);
    return TRUE;
}

extern int mCoBG_GetCrossCircleAndLine2Dvector(f32* cross0, f32* cross1, f32* point, f32* vec, f32* center, f32 radius) {
    // a = x^2 + y^2
    f32 A = SQ(vec[0]) + SQ(vec[1]);
    // b = 2 * ((vec.x * point.x) - (vec.x * center.x)) + ((vec.y * point.y) - (vec.y * center.y))
    f32 B = 2.0f * (vec[0] * point[0] - vec[0] * center[0] + vec[1] * point[1] - vec[1] * center[1]);
    // c = (point.x - center.x)^2 + (point.y - center.y)^2 - radius^2
    f32 C = SQ(point[0] - center[0]) + SQ(point[1] - center[1]) - SQ(radius);
    f32 R = SQ(B) - 4.0f*A*C; // b^2 - 4*a*c
    f32 t0;
    f32 t1;

    if (R >= 0.0f) {
        // sqrt(b^2 - 4*a*c)
        f32 root = ABS(sqrtf(R));

        if (A != 0.0f) {
            // (-b +- sqrt(b^2 - 4*a*c)) / 2a
            t0 = (-B + root) / (2.0f * A);
            t1 = (-B - root) / (2.0f * A);

            cross0[0] = point[0] + t0 * vec[0];
            cross0[1] = point[1] + t0 * vec[1];
            cross1[0] = point[0] + t1 * vec[0];
            cross1[1] = point[1] + t1 * vec[1];
            return TRUE;
        }
    }

    return FALSE;
}

extern int mCoBG_GetCrossCircleAndLine2DvectorPlaneXZ_Xyz(xyz_t* cross1, xyz_t* cross2, const xyz_t* point, const xyz_t* vec, const xyz_t* center, f32 radius) {
    static xyz_t cross0 = { 0.0f, 0.0f, 0.0f };
    f32 cross1_xz[2];
    f32 cross2_xz[2];
    f32 point_xz[2];
    f32 vec_xz[2];
    f32 center_xz[2];

    *cross1 = cross0;
    *cross2 = cross0;

    point_xz[0] = point->x;
    point_xz[1] = point->z;
    vec_xz[0] = vec->x;
    vec_xz[1] = vec->z;
    center_xz[0] = center->x;
    center_xz[1] = center->z;

    if (mCoBG_GetCrossCircleAndLine2Dvector(cross1_xz, cross2_xz, point_xz, vec_xz, center_xz, radius)) {
        cross1->x = cross1_xz[0];
        cross1->z = cross1_xz[1];
        cross2->x = cross2_xz[0];
        cross2->z = cross2_xz[1];
        return TRUE;
    }

    return FALSE;
}

// @unused, @fabricated
extern int mCoBG_GetCrossCircleAndLine2D(f32* cross0, f32* cross1, f32* p0, f32* p1, f32* center, f32 radius) {
    f32 vec[2];

    vec[0] = p1[0] - p0[0];
    vec[1] = p1[1] - p0[1];
    return mCoBG_GetCrossCircleAndLine2Dvector(cross0, cross1, p0, vec, center, radius);
}

// @unused, @fabricated
extern void mCoBG_GetReverseVector2D(f32* vec) {
    vec[0] *= -1.0f;
    vec[1] *= -1.0f;
}

// @unused, @fabricated
extern void mCoBG_GetUnitVector2D(f32* vec) {
    f32 len = sqrtf(SQ(vec[0]) + SQ(vec[1]));

    if (!F32_IS_ZERO(len)) {
        vec[0] /= len;
        vec[1] /= len;
    }
}

extern int mCoBG_JudgePointInCircle_Xyz(const xyz_t* p, const xyz_t* center, f32 radius) {
    f32 dx = p->x - center->x;
    f32 dz = p->z - center->z;
    
    if (SQ(dx) + SQ(dz) <= SQ(radius)) {
        return TRUE;
    }

    return FALSE;
}

extern int mCoBG_JudgePointInCircle(f32* p, f32* center, f32 radius) {
    f32 dx = p[0] - center[0];
    f32 dz = p[1] - center[1];
    
    if (SQ(dx) + SQ(dz) <= SQ(radius)) {
        return TRUE;
    }

    return FALSE;
}

// @unused, @fabricated
extern f32 mCoBG_GetAbsBiggerF(f32 a, f32 b) {
    if (ABS(a) > ABS(b)) {
        return a;
    } else {
        return b;
    }
}

static void mCoBG_GetDeffVec(f32* v0, f32* v1, f32* v2, f32* vec0, f32* vec1) {
    vec0[0] = v0[0] - v1[0];
    vec1[0] = v1[0] - v2[0];
    vec0[1] = v0[1] - v1[1];
    vec1[1] = v1[1] - v2[1];
    vec0[2] = v0[2] - v1[2];
    vec1[2] = v1[2] - v2[2];
}

extern void mCoBG_GetNorm_By2Vector(f32* v0, f32* v1, xyz_t* normal) {
    if (normal != NULL) {
        normal->x = v0[1] * v1[2] - v0[2] * v1[1];
        normal->y = v0[2] * v1[0] - v0[0] * v1[2];
        normal->z = v0[0] * v1[1] - v0[1] * v1[0];
    }
}

extern void mCoBG_GetNorm_By3Point(xyz_t* normal, f32* v0, f32* v1, f32* v2) {
    static f32 vec1[3];
    static f32 vec2[3];

    if (normal != NULL) {
        mCoBG_GetDeffVec(v0, v1, v2, vec1, vec2);
        mCoBG_GetNorm_By2Vector(vec1, vec2, normal);
    }
}

extern int mCoBG_RangeCheckLinePoint(f32* start, f32* end, f32* point) {
    f32 normal01[2];

    normal01[0] = end[0] - start[0];
    normal01[1] = end[1] - start[1];
    if (mCoBG_GetPointInfoFrontLine(start, point, normal01)) {
        f32 normal10[2];

        normal10[0] = start[0] - end[0];
        normal10[1] = start[1] - end[1];
        if (mCoBG_GetPointInfoFrontLine(end, point, normal10)) {
            return TRUE;
        }
    }

    return FALSE;
}
