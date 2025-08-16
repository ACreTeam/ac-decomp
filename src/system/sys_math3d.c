#include "sys_math3d.h"

xyz_t ZeroVec = { 0.0f, 0.0f, 0.0f };
s_xyz ZeroSVec = { 0, 0, 0 };

/* Unused function .bss symbols */
#ifdef MUST_MATCH
FORCESTRIP void _bss_func00() {
    static Math3D_linef_c l1;
    static Math3D_linef_c ls1;
    static Math3D_linef_c p2cl;

    l1 = ls1 = p2cl;
}
#endif

extern f32 Math3d_normalizeXyz_t(xyz_t* a) {
    f32 l, v;

    l = Math3DVecLength(a);

    if ((float)fabsf(l) < 0.008f) {
        return 0.0f;
    }
    v = (1.0f / l);
    a->x *= v;
    a->y *= v;
    a->z *= v;
    return l;
}

extern void Math3DInDivPos1(const xyz_t* v, const xyz_t* d, f32 t, xyz_t* c) {
    c->x = (v->x + (d->x * t));
    c->y = (v->y + (d->y * t));
    c->z = (v->z + (d->z * t));
}

extern void Math3DInDivPos2(const xyz_t* v, const xyz_t* d, xyz_t* c, f32 t) {
    xyz_t df;

    xyz_t_sub(d, v, &df);
    Math3DInDivPos1(v, &df, t, c);
}

/* @unused, @fabricated*/
FORCESTRIP f32 Math3D_Check2DInArea() {
    return 2.0f;
}

static int Math3DCheck3PointMinMaxAreaInside2D(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2, f32 cx, f32 cy, f32 r) {
    f32 minx, maxx, miny, maxy;

    minx = maxx = x0;
    miny = maxy = y0;

    if (minx > x1) {
        minx = x1;
    } else if (minx < x1) {
        maxx = x1;
    }

    if (miny > y1) {
        miny = y1;
    } else if (maxy < y1) {
        maxy = y1;
    }

    if (minx > x2) {
        minx = x2;
    } else if (maxx < x2) {
        maxx = x2;
    }

    if (miny > y2) {
        miny = y2;
    } else if (maxy < y2) {
        maxy = y2;
    }

    if ((minx - r) <= cx && (maxx + r) >= cx && (miny - r) <= cy && (maxy + r) >= cy) {
        return 1;
    }

    return 0;
}

static int Math3DCheck3PointMinMaxAreaInside3D(xyz_t* v0, xyz_t* v1, xyz_t* v2, xyz_t* c, f32 r) {
    xyz_t min;
    xyz_t max;

    min.x = max.x = v0->x;
    min.y = max.y = v0->y;
    min.z = max.z = v0->z;

    if (min.x > v1->x) {
        min.x = v1->x;
    } else if (max.x < v1->x) {
        max.x = v1->x;
    }

    if (min.y > v1->y) {
        min.y = v1->y;
    } else if (max.y < v1->y) {
        max.y = v1->y;
    }

    if (min.z > v1->z) {
        min.z = v1->z;
    } else if (max.z < v1->z) {
        max.z = v1->z;
    }

    if (min.x > v2->x) {
        min.x = v2->x;
    } else if (max.x < v2->x) {
        max.x = v2->x;
    }

    if (min.y > v2->y) {
        min.y = v2->y;
    } else if (max.y < v2->y) {
        max.y = v2->y;
    }

    if (min.z > v2->z) {
        min.z = v2->z;
    } else if (max.z < v2->z) {
        max.z = v2->z;
    }

    if (((min.x - r) <= c->x) && ((max.x + r) >= c->x) && ((min.y - r) <= c->y) && ((max.y + r) >= c->y) &&
        ((min.z - r) <= c->z) && ((max.z + r) >= c->z)) {
        return 1;
    }

    return 0;
}

extern f32 Math3DVecLengthSquare2D(f32 a, f32 b) {
    return ((a * a) + (b * b));
}

extern f32 Math3DVecLength2D(f32 a, f32 b) {
    return sqrtf(Math3DVecLengthSquare2D(a, b));
}

extern f32 Math3DLengthSquare2D(f32 x0, f32 y0, f32 x1, f32 y1) {
    return Math3DVecLengthSquare2D(x0 - x1, y0 - y1);
}

extern f32 Math3DLength2D(f32 x0, f32 x1, f32 y0, f32 y1) {
    return sqrtf(Math3DLengthSquare2D(x0, x1, y0, y1));
}

extern f32 Math3DVecLengthSquare(xyz_t* v) {
    return (v->x * v->x) + (v->y * v->y) + (v->z * v->z);
}

extern f32 Math3DVecLength(xyz_t* v) {
    f32 sqr_len = Math3DVecLengthSquare(v);
    return sqrt(sqr_len);
}

extern f32 Math3DLengthSquare(xyz_t* a, xyz_t* b) {
    xyz_t d;
    xyz_t_sub(a, b, &d);
    return Math3DVecLengthSquare(&d);
}

extern f32 Math3DLength(const xyz_t* a, const xyz_t* b) {
    return search_position_distance(a, b);
}

static f32 Math3DLength_s_f(s_xyz* a, xyz_t* b) {
    xyz_t d;

    d.x = a->x - b->x;
    d.y = a->y - b->y;
    d.z = a->z - b->z;
    return Math3DVecLength(&d);
}

extern void Math3DVectorProduct2Vec(const xyz_t* a, const xyz_t* b, xyz_t* ret) {
    ret->x = (a->y * b->z) - (a->z * b->y);
    ret->y = (a->z * b->x) - (a->x * b->z);
    ret->z = (a->x * b->y) - (a->y * b->x);
}

extern void Math3DVectorProductXYZ(xyz_t* va, xyz_t* vb, xyz_t* vc, xyz_t* ret) {
    static xyz_t vec01;
    static xyz_t vec02;

    xyz_t_sub(vb, va, &vec01);
    xyz_t_sub(vc, va, &vec02);
    Math3DVectorProduct2Vec(&vec01, &vec02, ret);
}

/* Unused function .bss symbols */
#ifdef MUST_MATCH
FORCESTRIP void _bss_func01() {
    static xyz_t tp0;
    static xyz_t tp1;
    static xyz_t tp2;
    static xyz_t cross_pos;
    static xyz_t min_p;
    static xyz_t max_p;
    static xyz_t lps_p;
    static xyz_t lpe_p;

    tp0 = tp1 = tp2 = cross_pos = min_p = max_p = lps_p = lpe_p;
}
#endif

extern void Math3DPlane(xyz_t* va, xyz_t* vb, xyz_t* vc, f32* nox, f32* noy, f32* noz, f32* odist) {
    static xyz_t mult_vec;

    f32 nm;
    f32 nminv;
    Math3DVectorProductXYZ(va, vb, vc, &mult_vec);

    nm = sqrtf((mult_vec.x * mult_vec.x) + (mult_vec.y * mult_vec.y) + (mult_vec.z * mult_vec.z));

    if (!(fabsf(nm) < 0.008f)) {
        nminv = 1.0f / nm;
        *nox = mult_vec.x * nminv;
        *noy = mult_vec.y * nminv;
        *noz = mult_vec.z * nminv;
        *odist = -((*nox * va->x) + (*noy * va->y) + (*noz * va->z));
    } else {
        *odist = 0.0f;
        *noz = 0.0f;
        *noy = 0.0f;
        *nox = 0.0f;
    }
}

/* Unused function .bss symbols */
#ifdef MUST_MATCH
FORCESTRIP xyz_t* _bss_func02() {
    static xyz_t pos;

    return &pos;
}
#endif

/* Unused function .bss symbols */
#ifdef MUST_MATCH
FORCESTRIP xyz_t* _bss_func03() {
    static xyz_t pos;

    return &pos;
}
#endif

extern f32 Math3DPlaneFunc(f32 nox, f32 noy, f32 noz, f32 odist, const xyz_t* pl) {
    return ((nox * pl->x) + (noy * pl->y) + (noz * pl->z) + odist);
}

extern f32 Math3DLengthPlaneAndPos(f32 nox, f32 noy, f32 noz, f32 odist, const xyz_t* pl) {
    f32 res = fabsf(Math3DSignedLengthPlaneAndPos(nox, noy, noz, odist, pl));
    return res;
}

extern f32 Math3DSignedLengthPlaneAndPos(f32 nox, f32 noy, f32 noz, f32 odist, const xyz_t* pl) {

    f32 nm;

    nm = sqrtf((nox * nox) + (noy * noy) + (noz * noz));

    if (F32_IS_ZERO(nm)) {
        return 0.0f;
    }

    return Math3DPlaneFunc(nox, noy, noz, odist, pl) / nm;
}

extern int Math3DTriangleCrossYCheck_general(xyz_t* v0, xyz_t* v1, xyz_t* v2, f32 z, f32 x, f32 dt, f32 dist, f32 noy) {
    f32 dvovi;
    f32 dvive;
    f32 dvevo;
    f32 edge;
    f32 dist_sq;

    if (!Math3DCheck3PointMinMaxAreaInside2D(v0->z, v0->x, v1->z, v1->x, v2->z, v2->x, z, x, dist)) {
        return FALSE;
    }

    dist_sq = dist * dist;

    if (((v0->z - z) * (v0->z - z)) + ((v0->x - x) * (v0->x - x)) < dist_sq ||
        ((v1->z - z) * (v1->z - z)) + ((v1->x - x) * (v1->x - x)) < dist_sq ||
        ((v2->z - z) * (v2->z - z)) + ((v2->x - x) * (v2->x - x)) < dist_sq) {
        return TRUE;
    }

    dvovi = (((v0->z - z) * (v1->x - x)) - (v0->x - x) * (v1->z - z));
    dvive = (((v1->z - z) * (v2->x - x)) - (v1->x - x) * (v2->z - z));
    dvevo = (((v2->z - z) * (v0->x - x)) - (v2->x - x) * (v0->z - z));

    if ((dvovi <= dt) && (dvive <= dt) && (dvevo <= dt) || (dvovi >= -dt) && (dvive >= -dt) && (dvevo >= -dt)) {
        return TRUE;
    }

    if (fabsf(noy) > 0.5f) {
        if (Math3D_pointVsLineSegmentLengthSquare2D(z, x, v0->z, v0->x, v1->z, v1->x, &edge) && (edge < dist_sq)) {
            return TRUE;
        }
        if (Math3D_pointVsLineSegmentLengthSquare2D(z, x, v1->z, v1->x, v2->z, v2->x, &edge) && (edge < dist_sq)) {
            return TRUE;
        }
        if (Math3D_pointVsLineSegmentLengthSquare2D(z, x, v2->z, v2->x, v0->z, v0->x, &edge) && (edge < dist_sq)) {
            return TRUE;
        }
    }
    return FALSE;
}

static int Math3DTriangleCrossYCheck_chparam(xyz_t* v0, xyz_t* v1, xyz_t* v2, f32 z, f32 x, f32 dt, f32 noy) {
    return Math3DTriangleCrossYCheck_general(v0, v1, v2, z, x, dt, 1.0f, noy);
}

extern int Math3DTriangleCrossYLine_scope(xyz_t* v0, xyz_t* v1, xyz_t* v2, f32 nox, f32 noy, f32 noz, f32 dst, f32 z,
                                          f32 x, f32* yint, f32 y0, f32 y1) {
    xyz_t pl;
    f32 das, dbs;
    if (F32_IS_ZERO(noy)) {
        return 0;
    }

    pl.x = x;
    pl.y = y0;
    pl.z = z;

    das = Math3DPlaneFunc(nox, noy, noz, dst, &pl);
    pl.y = y1;
    dbs = Math3DPlaneFunc(nox, noy, noz, dst, &pl);

    if ((das > 0.0f) && (dbs > 0.0f) || (das < 0.0f) && (dbs < 0.0f)) {
        return 0;
    }

    if (Math3DTriangleCrossYCheck_general(v0, v1, v2, z, x, 300.0f, 1.0f, noy)) {
        *yint = (((-nox * x) - (noz * z)) - dst) / noy;
        return 1;
    }

    return 0;
}

static int Math3DTriangleCrossXCheck_general(xyz_t* v0, xyz_t* v1, xyz_t* v2, f32 y, f32 z, f32 dt, f32 dist, f32 nox) {
    f32 dvovi, dvive, dvevo;
    f32 edge;
    f32 dist_sq;

    if (!Math3DCheck3PointMinMaxAreaInside2D(v0->y, v0->z, v1->y, v1->z, v2->y, v2->z, y, z, dist)) {
        return 0;
    }
    dist_sq = (dist * dist);

    if ((((v0->y - y) * (v0->y - y)) + ((v0->z - z) * (v0->z - z)) < dist_sq) ||
        (((v1->y - y) * (v1->y - y)) + ((v1->z - z) * (v1->z - z)) < dist_sq) ||
        (((v2->y - y) * (v2->y - y)) + ((v2->z - z) * (v2->z - z)) < dist_sq)) {
        return 1;
    }

    dvovi = (((v0->y - y) * (v1->z - z)) - (v0->z - z) * (v1->y - y));
    dvive = (((v1->y - y) * (v2->z - z)) - (v1->z - z) * (v2->y - y));
    dvevo = (((v2->y - y) * (v0->z - z)) - (v2->z - z) * (v0->y - y));

    if (((dvovi <= dt) && (dvive <= dt) && (dvevo <= dt)) || ((dvovi >= -dt) && (dvive >= -dt) && (dvevo >= -dt))) {
        return 1;
    }

    if (fabsf(nox) > 0.5f) {
        if (Math3D_pointVsLineSegmentLengthSquare2D(y, z, v0->y, v0->z, v1->y, v1->z, &edge) && (edge < dist_sq)) {
            return 1;
        }
        if (Math3D_pointVsLineSegmentLengthSquare2D(y, z, v1->y, v1->z, v2->y, v2->z, &edge) && (edge < dist_sq)) {
            return 1;
        }
        if (Math3D_pointVsLineSegmentLengthSquare2D(y, z, v2->y, v2->z, v0->y, v0->z, &edge) && (edge < dist_sq)) {
            return 1;
        }
    }
    return 0;
}

static int Math3DTriangleCrossXCheck_chparam(xyz_t* v0, xyz_t* v1, xyz_t* v2, f32 y, f32 z, f32 dt, f32 nox) {
    return Math3DTriangleCrossXCheck_general(v0, v1, v2, y, z, dt, 1.0f, nox);
}

extern int Math3DTriangleCrossZCheck_general(xyz_t* v0, xyz_t* v1, xyz_t* v2, f32 x, f32 y, f32 dt, f32 dist, f32 noz) {
    f32 dvovi, dvive, dvevo;
    f32 edge;
    f32 dist_sq;
    f32 v01temp;
    f32 v10temp;

    if (!Math3DCheck3PointMinMaxAreaInside2D(v0->x, v0->y, v1->x, v1->y, v2->x, v2->y, x, y, dist)) {
        return 0;
    }
    dist_sq = (dist * dist);

    if ((SQ(x - v0->x) + SQ(y - v0->y)) < dist_sq || (SQ(x - v1->x) + SQ(y - v1->y)) < dist_sq ||
        (SQ(x - v2->x) + SQ(y - v2->y)) < dist_sq) {
        return 1;
    }

    dvovi = ((v0->x - x) * (v1->y - y)) - ((v0->y - y) * (v1->x - x));
    dvive = ((v1->x - x) * (v2->y - y)) - ((v1->y - y) * (v2->x - x));
    dvevo = ((v2->x - x) * (v0->y - y)) - ((v2->y - y) * (v0->x - x));

    if (((dvovi <= dt) && (dvive <= dt) && (dvevo <= dt)) || ((dvovi >= -dt) && (dvive >= -dt) && (dvevo >= -dt))) {
        return 1;
    }

    if (fabsf(noz) > 0.5f) {
        if (Math3D_pointVsLineSegmentLengthSquare2D(x, y, v0->x, v0->y, v1->x, v1->y, &edge) && (edge < dist_sq)) {
            return 1;
        }
        if (Math3D_pointVsLineSegmentLengthSquare2D(x, y, v1->x, v1->y, v2->x, v2->y, &edge) && (edge < dist_sq)) {
            return 1;
        }
        if (Math3D_pointVsLineSegmentLengthSquare2D(x, y, v2->x, v2->y, v0->x, v0->y, &edge) && (edge < dist_sq)) {
            return 1;
        }
    }
    return 0;
}

static int Math3DTriangleCrossZCheck_chparam(xyz_t* v0, xyz_t* v1, xyz_t* v2, f32 x, f32 y, f32 dt, f32 noz) {
    return Math3DTriangleCrossZCheck_general(v0, v1, v2, x, y, dt, 1.0f, noz);
}

extern int Math3D_sphereCollisionPoint(Math3D_sphere_c* s, xyz_t* p) {
    if (Math3DLength_s_f(&s->center, p) < s->radius) {
        return 1;
    }
    return 0;
}

extern int Math3D_pointVsLineSegmentLengthSquare2D(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2, f32* lsq) {
    static xyz_t h;

    f32 diffx, diffy;
    f32 d;
    f32 pr;
    int r = 0;
    diffx = x2 - x1;
    diffy = y2 - y1;

    d = (diffx * diffx) + (diffy * diffy);

    if (F32_IS_ZERO(d)) {
        *lsq = 0;
        return 0;
    }

    pr = (((x0 - x1) * diffx) + (y0 - y1) * diffy) / d;
    if (pr >= 0.0f && pr <= 1.0f) {
        r = 1;
    }

    h.x = (diffx * pr) + x1;
    h.y = (diffy * pr) + y1;

    *lsq = ((h.x - x0) * (h.x - x0)) + ((h.y - y0) * (h.y - y0));
    return r;
}

extern int Math3D_sphereCrossLineSegment(Math3D_sphere_c* s, Math3D_linef_c* l) {
    static xyz_t h;
    f32 lc;
    xyz_t linediff;
    
    f32 r_sq;
    f32 cen_x_sq;
    f32 cen_y_sq;
    f32 cen_z_sq;
    
    f32 ofs_x;
    f32 ofs_y;
    f32 ofs_z;
    
    f32 x;
    f32 y;
    f32 z;
    f32 delta_sq;

    if ((Math3D_sphereCollisionPoint(s, &l->a)) || Math3D_sphereCollisionPoint(s, &l->b)) {
        return 1;
    }

    x = l->b.x - l->a.x;
    y = l->b.y - l->a.y;
    z = l->b.z - l->a.z;

    delta_sq = SQ(x) + SQ(y) + SQ(z);

    if (fabsf(delta_sq) < 0.008f) {
        return 0;
    }

    lc = (((x * (s->center.x - l->a.x)) + (y * (s->center.y - l->a.y))) + (z * (s->center.z - l->a.z))) / delta_sq;

    if (lc < 0.0f || lc > 1.0f) {
        return 0;
    }

    h.x = (x * lc) + l->a.x;
    h.y = (y * lc) + l->a.y;
    h.z = (z * lc) + l->a.z;

    if (SQ(h.x - s->center.x) + SQ(h.y - s->center.y) + SQ(h.z - s->center.z) <= SQ((f32)s->radius)) {
        return 1;
    }
    return 0;
}

extern void Math3D_sphereCrossTriangleCalc_cp(Math3D_sphere_c* s, Math3D_triangle_c* tri, xyz_t* ip) {
    static xyz_t tr_center;
    static xyz_t sp_center;

    f32 dst, sr;

    tr_center.x = ((tri->vtx[0].x + tri->vtx[1].x) * 0.5f);
    tr_center.y = ((tri->vtx[0].y + tri->vtx[1].y) * 0.5f);
    tr_center.z = ((tri->vtx[0].z + tri->vtx[1].z) * 0.5f);

    sp_center.x = s->center.x;
    sp_center.y = s->center.y;
    sp_center.z = s->center.z;

    dst = Math3DLength(&tr_center, &sp_center);

    if (fabsf(dst) < 0.008f) {
        ip->x = sp_center.x;
        ip->y = sp_center.y;
        ip->z = sp_center.z;
        return;
    }

    sr = s->radius / dst;
    Math3DInDivPos2(&sp_center, &tr_center, ip, sr);
}

extern int Math3D_sphereCrossTriangle3_cp(Math3D_sphere_c* s, Math3D_triangle_c* tri, xyz_t* ip) {
    static xyz_t center;
    static Math3D_linef_c ls;
    static xyz_t cross;

    f32 r, nox, noy, noz, pd;

    center.x = s->center.x;
    center.y = s->center.y;
    center.z = s->center.z;

    r = s->radius;

    if (!Math3DCheck3PointMinMaxAreaInside3D(&tri->vtx[0], &tri->vtx[1], &tri->vtx[2], &center, r)) {
        return 0;
    }

    pd = Math3DLengthPlaneAndPos(tri->plane.normal.x, tri->plane.normal.y, tri->plane.normal.z, tri->plane.originDist,
                                 &center);

    if (pd > r) {
        return 0;
    }
    ls.a = tri->vtx[0];
    ls.b = tri->vtx[1];
    if (Math3D_sphereCrossLineSegment(s, &ls)) {
        Math3D_sphereCrossTriangleCalc_cp(s, tri, ip);
        return 1;
    }

    ls.a = tri->vtx[1];
    ls.b = tri->vtx[2];
    if (Math3D_sphereCrossLineSegment(s, &ls)) {
        Math3D_sphereCrossTriangleCalc_cp(s, tri, ip);
        return 1;
    }

    ls.a = tri->vtx[2];
    ls.b = tri->vtx[0];
    if (Math3D_sphereCrossLineSegment(s, &ls)) {
        Math3D_sphereCrossTriangleCalc_cp(s, tri, ip);
        return 1;
    }

    nox = tri->plane.normal.x * pd;
    noy = tri->plane.normal.y * pd;
    noz = tri->plane.normal.z * pd;

    if (Math3DPlaneFunc(tri->plane.normal.x, tri->plane.normal.y, tri->plane.normal.z, tri->plane.originDist, &center) >
        0.0f) {

        cross.x = center.x - nox;
        cross.y = center.y - noy;
        cross.z = center.z - noz;
    } else {
        cross.x = center.x + nox;
        cross.y = center.y + noy;
        cross.z = center.z + noz;
    }

    if (fabsf(tri->plane.normal.y) > 0.5f) {

        if (Math3DTriangleCrossYCheck_chparam(&tri->vtx[0], &tri->vtx[1], &tri->vtx[2], cross.z, cross.x, 0.0f,
                                              tri->plane.normal.y)) {
            Math3D_sphereCrossTriangleCalc_cp(s, tri, ip);
            return 1;
        }
    } else if (fabsf(tri->plane.normal.x) > 0.5f) {
        if (Math3DTriangleCrossXCheck_chparam(&tri->vtx[0], &tri->vtx[1], &tri->vtx[2], cross.y, cross.z, 0.0f,
                                              tri->plane.normal.x)) {
            Math3D_sphereCrossTriangleCalc_cp(s, tri, ip);
            return 1;
        }
    } else if (Math3DTriangleCrossZCheck_chparam(&tri->vtx[0], &tri->vtx[1], &tri->vtx[2], cross.x, cross.y, 0.0f,
                                                 tri->plane.normal.z)) {
        Math3D_sphereCrossTriangleCalc_cp(s, tri, ip);
        return 1;
    }
    return 0;
}

extern int Math3D_pipeVsPos(Math3D_pipe_c* c, xyz_t* p) {
    f32 l;
    f32 r;
    f32 top;
    f32 bottom;
    f32 d;
    f32 rr;

    l = c->center.x - p->x;
    r = c->center.z - p->z;
    top = c->center.y + (f32)c->offset;
    bottom = top + (f32)c->height;
    d = SQ(l) + SQ(r);
    rr = SQ((f32)c->radius);

    if (d < rr && (top < p->y) && (bottom > p->y)) {
        return 1;
    } else {
        return 0;
    }
}

extern int Math3D_pipeCrossLine(Math3D_pipe_c* c, xyz_t* la, xyz_t* lb, xyz_t* ia, xyz_t* ib) {
#if VERSION >= VER_GAFU01_00
    int sa;
    int sb;
    int i;
    int co;
    int f = 0;
    xyz_t ca;
    xyz_t cb;
    xyz_t ab;
    xyz_t intpos[4];
    f32 z = 0.0f;
    f32 fb;
    f32 bix;
    f32 biz;
    f32 tix;
    f32 tiz;
    f32 iba;
    f32 ibd;
    f32 t2;
    f32 fa = 0.0f;
    f32 fba = 0.0f;
    f32 t;
    f32 rsqd;
    f32 t3;
    f32 rsq;
    f32 dc;
#else
    f32 z = 0.0f;
    int f = 0;
    int sa, sb, i, co;
    xyz_t ca, cb, ab, intpos[4];
    f32 fa = 0.0f;
    f32 fba = 0.0f;
    f32 fb;
    f32 bix;
    f32 biz;
    f32 tix;
    f32 tiz;
    f32 rsqd;
    f32 iba;
    f32 ibd;
    f32 t2;
    f32 t;
    f32 t3;
    f32 rsq;
    f32 dc;
#endif

    if (Math3D_pipeVsPos(c, la) && Math3D_pipeVsPos(c, lb)) {
        *ia = *la;
        *ib = *lb;
        return 2;
    }

    ca.x = la->x - c->center.x;
    ca.y = la->y - c->center.y - c->offset;
    ca.z = la->z - c->center.z;

    cb.x = lb->x - c->center.x;
    cb.y = lb->y - c->center.y - c->offset;
    cb.z = lb->z - c->center.z;

    xyz_t_sub(&cb, &ca, &ab);

    rsq = SQ((f32)c->radius);

    if (!F32_IS_ZERO(ab.y)) {
        fb = -ca.y / ab.y;
        if ((fb >= z) && (fb <= 1.0f)) {
            bix = (ab.x * fb) + ca.x;
            biz = (ab.z * fb) + ca.z;

            if ((SQ(bix) + SQ(biz)) < rsq) {
                intpos[0].x = (f32)bix + (f32)c->center.x;
                intpos[0].y = (f32)c->center.y + (f32)c->offset;
                intpos[0].z = (f32)biz + (f32)c->center.z;
                f |= 1;
            }
        }
        fa = ((f32)c->height - (f32)ca.y) / ab.y;
        if ((fa >= z) && (fa <= 1.0f)) {
            tix = ((f32)ab.x * (f32)fa) + (f32)ca.x;
            tiz = ((f32)ab.z * (f32)fa) + (f32)ca.z;

            if ((SQ(tix) + SQ(tiz)) < rsq) {
                intpos[1].x = (f32)tix + (f32)c->center.x;
                intpos[1].y = (f32)c->center.y + (f32)c->offset + (f32)c->height;
                intpos[1].z = (f32)tiz + (f32)c->center.z;
                f |= 2;
            }
        }
    }

    t3 = (SQ(ab.x) + SQ(ab.z));
    t2 = 2.0f * t3;
    t = 2.0f * (ab.x * ca.x + ab.z * ca.z);
    rsqd = (SQ(ca.x) + SQ(ca.z)) - rsq;

    if (!F32_IS_ZERO(t2)) {
        dc = (SQ(t) - 4.0f * t3 * rsqd);

        if (dc < z) {
            return 0;
        }

        if (dc > z) {
            sa = sb = 1;
        } else {
            sa = 1;
            sb = 0;
        }

        dc = z >= 0.0f ? sqrtf(dc) : 0.0f;

        if (sa == 1) {
            fa = (-t + dc) / t2;
        }
        if (sb == 1) {
            fba = (-t - dc) / t2;
        }
    } else if (!F32_IS_ZERO(t)) {
        fa = -rsqd / t;
        sa = 1;
        sb = 0;
    } else {
        return 0;
    }

    if (sa == 1 && sb == 0) {
        if (z > fa || fa > 1.0f) {
            return 0;
        }
    } else {
        int what = 1;
        int what2;
        if (!(z > fa || fa > 1.0f)) {
            what = 0;
        }

        what2 = 1;
        if (!(z > fba || fba > 1.0f)) {
            what2 = 0;
        }

        if (what && what2) {
            return 0;
        }

        if (what) {
            sa = 0;
        }

        if (what2) {
            sb = 0;
        }
    }
    if ((sa == 1) && ((fa * ab.y + ca.y) < z || (fa * ab.y + ca.y) > c->height)) {
        sa = 0;
    }
    if ((sb == 1) && ((fba * ab.y + ca.y) < z || (fba * ab.y + ca.y) > c->height)) {
        sb = 0;
    }
    if (sa == 0 && sb == 0) {
        return 0;
    }

    if (sa == 1 && sb == 1) {
        intpos[2].x = (fa * ab.x + ca.x) + c->center.x;
        intpos[2].y = (fa * ab.y + ca.y) + c->center.y + c->offset;
        intpos[2].z = (fa * ab.z + ca.z) + c->center.z;
        f |= 4;
        intpos[3].x = (fba * ab.x + ca.x) + c->center.x;
        intpos[3].y = (fba * ab.y + ca.y) + c->center.y + c->offset;
        intpos[3].z = (fba * ab.z + ca.z) + c->center.z;
        f |= 8;
    } else if (sa == 1) {
        intpos[2].x = (fa * ab.x + ca.x) + c->center.x;
        intpos[2].y = (fa * ab.y + ca.y) + c->center.y + c->offset;
        intpos[2].z = (fa * ab.z + ca.z) + c->center.z;
        f |= 4;
    } else if (sb == 1) {
        intpos[2].x = (fba * ab.x + ca.x) + c->center.x;
        intpos[2].y = (fba * ab.y + ca.y) + c->center.y + c->offset;
        intpos[2].z = (fba * ab.z + ca.z) + c->center.z;
        f |= 4;
    }
    co = 0;
    for (i = 0; i < 4; i++) {
        if (f & (1 << i)) {
            if (co == 0) {
                *ia = intpos[i];
            } else if (co == 1) {
                if (Math3DLengthSquare(ia, la) < Math3DLengthSquare(ia, &intpos[i])) {
                    *ib = intpos[i];
                    break;
                } else {
                    *ib = *ia;
                    *ia = intpos[i];
                    break;
                }
            }
            co++;
        }
    }
    return co;
}

extern int Math3D_pipeCrossTriangle_cp(Math3D_pipe_c* c, Math3D_triangle_c* tri, xyz_t* in) {
    static xyz_t cross1;
    static xyz_t cross2;
    static Math3D_sphere_c sph1;
    static Math3D_sphere_c sph2;

    f32 ct;
    f32 cb;
    f32 mind;
    f32 asq;
    f32 yin;
    f32 civovi;
    f32 rdvovi;
    xyz_t cic;
    xyz_t vovi;
    xyz_t dmf;

    cb = c->center.y + (f32)c->offset;
    ct = cb + (f32)c->height;

    if (((cb > tri->vtx[0].y) && (cb > tri->vtx[1].y) && (cb > tri->vtx[2].y)) ||
        ((ct < tri->vtx[0].y) && (ct < tri->vtx[1].y) && (ct < tri->vtx[2].y))) {
        return FALSE;
    }

    mind = 1.e38f;
    if (Math3D_pipeCrossLine(c, &tri->vtx[0], &tri->vtx[1], &cross1, &cross2)) {
        asq = Math3DLengthSquare(&cross1, &tri->vtx[0]);
        mind = asq;
        *in = cross1;
    }
    if (Math3D_pipeCrossLine(c, &tri->vtx[2], &tri->vtx[1], &cross1, &cross2)) {
        asq = Math3DLengthSquare(&cross1, &tri->vtx[2]);
        if (mind > asq) {
            *in = cross1;
            mind = asq;
        }
    }
    if (Math3D_pipeCrossLine(c, &tri->vtx[0], &tri->vtx[2], &cross1, &cross2)) {
        asq = Math3DLengthSquare(&cross1, &tri->vtx[0]);
        if (mind > asq) {
            *in = cross1;
            mind = asq;
        }
    }

    if (mind != 1.e38f) {
        return TRUE;
    }

    if (Math3DTriangleCrossYLine_scope(&tri->vtx[0], &tri->vtx[1], &tri->vtx[2], tri->plane.normal.x,
                                       tri->plane.normal.y, tri->plane.normal.z, tri->plane.originDist, c->center.z,
                                       c->center.x, &yin, cb, ct)) {

        cic.x = c->center.x;
        cic.y = yin;
        cic.z = c->center.z;

        vovi.x = (tri->vtx[0].x + tri->vtx[1].x) * 0.5f;
        vovi.y = (tri->vtx[0].y + tri->vtx[1].y) * 0.5f;
        vovi.z = (tri->vtx[0].z + tri->vtx[1].z) * 0.5f;

        xyz_t_sub(&vovi, &cic, &dmf);

        civovi = sqrtf(SQ(dmf.x) + SQ(dmf.z));

        if (fabsf(civovi) < 0.008f) {
            xyz_t_move(in, &vovi);
        } else {
            rdvovi = c->radius / civovi;
            Math3DInDivPos1(&cic, &dmf, rdvovi, in);
        }

        return TRUE;
    }

    sph1.center.x = sph2.center.x = c->center.x;
    sph1.center.z = sph2.center.z = c->center.z;
    sph1.center.y = ct;
    sph2.center.y = cb;
    sph1.radius = sph2.radius = c->radius;

    if ((Math3D_sphereCrossTriangle3_cp(&sph1, tri, in)) || (Math3D_sphereCrossTriangle3_cp(&sph2, tri, in))) {
        return TRUE;
    }
    return FALSE;
}

extern int Math3D_sphereCrossSphere_cl(Math3D_sphere_c* a, Math3D_sphere_c* b, f32* in) {
    f32 cdist;

    return (Math3D_sphereCrossSphere_cl_cc(a, b, in, &cdist));
}

extern int Math3D_sphereCrossSphere_cl_cc(Math3D_sphere_c* a, Math3D_sphere_c* b, f32* in, f32* cdist) {
    f32 dx = (f32)a->center.x - (f32)b->center.x;
    f32 dy = (f32)a->center.y - (f32)b->center.y;
    f32 dz = (f32)a->center.z - (f32)b->center.z;

    *cdist = sqrt(dx * dx + dy * dy + dz * dz);

    *in = ((f32)a->radius + (f32)b->radius) - *cdist;

    if (*in > 0.008f) {
        return 1;
    }
    *in = 0.0f;
    return 0;
}

extern int Math3D_sphereVsPipe_cl(Math3D_sphere_c* s, Math3D_pipe_c* c, f32* in) {
    f32 cdist;
    return Math3D_sphereVsPipe_cl_cc(s, c, in, &cdist);
}

extern int Math3D_sphereVsPipe_cl_cc(Math3D_sphere_c* s, Math3D_pipe_c* c, f32* in, f32* cdist) {

    static Math3D_sphereF_c sphereF;
    static Math3D_pipeF_c pipeF;

    f32 x;
    f32 z;
    f32 ct;
    f32 cb;
    f32 cr;

    if (s->radius <= 0 || c->radius <= 0) {
        return 0;
    }

    sphereF.center.y = s->center.y;
    sphereF.radius = s->radius;
    pipeF.center.y = c->center.y;
    pipeF.offset = c->offset;
    pipeF.height = c->height;

    x = (f32)s->center.x - c->center.x;
    z = (f32)s->center.z - c->center.z;

    cb = pipeF.center.y + pipeF.offset;
    ct = pipeF.center.y + pipeF.offset + pipeF.height;
    cr = (f32)s->radius + c->radius;

    *cdist = sqrtf(SQ(x) + SQ(z));

    if (cr < *cdist) {
        return FALSE;
    }

    if ((sphereF.center.y + sphereF.radius >= cb) && (sphereF.center.y - sphereF.radius <= ct)) {
        *in = cr - *cdist;
        return TRUE;
    }

    return FALSE;
}

extern int Math3D_pipeVsPipe_cl(Math3D_pipe_c* a, Math3D_pipe_c* b, f32* d) {
    f32 di;

    return Math3D_pipeVsPipe_cl_cc(a, b, d, &di);
}

extern int Math3D_pipeVsPipe_cl_cc(Math3D_pipe_c* a, Math3D_pipe_c* b, f32* d, f32* di) {
    static Math3D_pipeF_c pipe1f;
    static Math3D_pipeF_c pipe2f;

    xyz_t_move_s_xyz(&pipe1f.center, &a->center);
    pipe1f.radius = a->radius;
    pipe1f.offset = a->offset;
    pipe1f.height = a->height;

    xyz_t_move_s_xyz(&pipe2f.center, &b->center);
    pipe2f.radius = b->radius;
    pipe2f.offset = b->offset;
    pipe2f.height = b->height;

    *di = sqrtf((pipe1f.center.x - pipe2f.center.x) * (pipe1f.center.x - pipe2f.center.x) +
                (pipe1f.center.z - pipe2f.center.z) * (pipe1f.center.z - pipe2f.center.z));

    if (*di > (pipe1f.radius + pipe2f.radius)) {
        return 0;
    }

    if (((pipe1f.center.y + pipe1f.offset) + pipe1f.height) < (pipe2f.center.y + pipe2f.offset) ||
        (((pipe1f.center.y + pipe1f.offset) > (pipe2f.center.y + pipe2f.offset) + pipe2f.height))) {
        return 0;
    }
    *d = pipe1f.radius + pipe2f.radius - *di;
    return 1;
}

extern void sMath_RotateY(xyz_t* v, f32 y) {
    f32 cos = cosf_table(y);
    f32 sin = sinf_table(y);
    xyz_t temp = *v;

    v->x = temp.x * cos + temp.z * sin;
    v->z = -temp.x * sin + temp.z * cos;
}

extern void sMath_RotateX(xyz_t* v, f32 x) {
    f32 cos = cosf_table(x);
    f32 sin = sinf_table(x);
    xyz_t temp = *v;

    v->y = temp.y * cos - temp.z * sin;
    v->z = temp.y * sin + temp.z * cos;
}

extern void sMath_RotateZ(xyz_t* v, f32 z) {
    f32 cos = cosf_table(z);
    f32 sin = sinf_table(z);
    xyz_t temp = *v;

    v->x = temp.x * cos - temp.y * sin;
    v->y = temp.x * sin + temp.y * cos;
}
