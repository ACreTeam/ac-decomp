#ifndef JGEOMETRY_QUAT_H
#define JGEOMETRY_QUAT_H

#include "dolphin/mtx.h"

#include <JSystem/JGeometry/Vec.h>
#include "JSystem/JGeometry/Util.h"
#include "JSystem/JMath/JMath.h"

#include "types.h"

namespace JGeometry {
    template <typename T>
    struct TQuat4 : public TVec4< T > {
    public:
        TQuat4() {}
        TQuat4(f32 _x, f32 _y, f32 _z, f32 _w)
        {
            this->x = _x;
            this->y = _y;
            this->z = _z;
            this->w = _w;
        }
        
        template <typename A>
        void set(A _x, A _y, A _z, A _w) {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }
        /* General operations */
        void scale(f32 s) {
            PSQUATScale(this, this, s);
        }
        
        void scale(f32 s, const TQuat4 &rSrc) {
            PSQUATScale(&rSrc, this, s);
        }

        f32 squared() const {
            return PSQUATDotProduct(this, this);
        }

        f32 squared(const TQuat4 &rOther) const {
            return PSQUATDotProduct(this, &rOther);
        }

        f32 normalize() { // TODO: OK?
            f32 sq = squared();
            if (sq <= TUtilf::epsilon())
                return 0.0f;
            else
            {
                f32 invsqrt = TUtilf::inv_sqrt(sq);
                scale(invsqrt);
                return invsqrt * sq;
            }
        }

        f32 normalize(const TQuat4 &other) {
            f32 sq = other.squared();
            if (sq <= TUtilf::epsilon()) {
                set(0.0f, 0.0f, 0.0f, 1.0f);
                return 0.0f;
            }
            
            f32 invsqrt = TUtilf::inv_sqrt(sq);
            scale(invsqrt, other);
            return invsqrt * sq;
        }

        void getXDir(TVec3f &rDest) const;
        void getYDir(TVec3f &rDest) const;
        void getZDir(TVec3f &rDest) const;

        void getEuler(TVec3f &rDest) const;
        void setEuler(f32 _x, f32 _y, f32 _z);
        void setEulerZ(f32 _z);

        // void setRotate(const TVec3f &, const TVec3f &, f32);
        // void setRotate(const TVec3f &, const TVec3f &);
        // void setRotate(const TVec3f &, f32);
        // void rotate(TVec3f &rDest) const;

        void setRotate(const TVec3f& pVec, f32 pAngle)
        {
            this->xyz().scale(sinf(pAngle * 0.5f), pVec);
            this->w = cosf(pAngle * 0.5f);
        }

        void setRotate(const TVec3f& from, const TVec3f& to)
        {
            TVec3<T> axis;
            axis.cross(from, to);

            f32 len = axis.length();
            if (len <= JGeometry::TUtilf::epsilon()) {
                this->set(0.0f, 0.0f, 0.0f, 1.0f);
                return;
            }

            f32 halfAngle = 0.5f * (JMAAtan2Radian(len, from.dot(to)));
            this->xyz().scale(::sinf(halfAngle) / len, axis);
            this->w = cosf(halfAngle);
        }

        // Assumes unit quaternion. These were renamed to "transform" in SMG.
        void rotate(const TVec3f& v, TVec3f& rDest) const
        {
            // Incollect regalloc
            f32 vx = v.x;
            f32 vy = v.y;
            f32 vz = v.z;

            T w = this->w;
            T z = this->z;
            T y = this->y;
            T x = this->x;

            // clang-format off
            JGeometry::TQuat4f q;
            q.x =  w *  0 + y * vz - z * vy + w * vx;
            q.y = -x * vz + y *  0 + z * vx + w * vy;
            q.z =  x * vy - y * vx + z *  0 + w * vz;
            q.w = -x * vx - y * vy - z * vz + w *  0;

            JGeometry::TQuat4f q2;
            q2.x =  q.x *  w + q.y * -z - q.z * -y + q.w * -x;
            q2.y = -q.x * -z + q.y *  w + q.z * -x + q.w * -y;
            q2.z =  q.x * -y - q.y * -x + q.z *  w + q.w * -z;
            // clang-format on

            // This set wasn't inlined in SMG, so should be real?
            rDest.set(q2.x, q2.y, q2.z);
        }

        void rotate(TVec3f& rDest) const { rotate(rDest, rDest); }


        void slerp(const TQuat4 &a1, const TQuat4 &a2, f32 a3) {
            this->x = a1.x;
            this->y = a1.y;
            this->z = a1.z;
            this->w = a1.w;
            this->slerp(a2, a3);
        }
        
        void slerp(const TQuat4 &other, f32 t) {
            // Normalize both quaternions
            TQuat4f q1;
            q1.normalize(*this);

            TQuat4f q2;
            q2.normalize(other);

            // Compute the cosine of the angle between them
            f32 dot = q1.squared(q2);

            // If dot < 0, negate q2 for shortest path
            if (dot < 0.0f) {
                dot = -dot;
                q2.x = -q2.x;
                q2.y = -q2.y;
                q2.z = -q2.z;
                q2.w = -q2.w;
            }

            f32 s0, s1;
            if (1.0f - dot > TUtilf::epsilon()) {
                // Standard slerp
                f32 theta = acos(dot);
                f32 sinTheta = sin(theta);
                s0 = sin((1.0f - t) * theta) / sinTheta;
                s1 = sin(t * theta) / sinTheta;
            } else {
                // Quaternions are very close, use linear interpolation
                s0 = 1.0f - t;
                s1 = t;
            }

            this->x = s0 * q1.x + s1 * q2.x;
            this->y = s0 * q1.y + s1 * q2.y;
            this->z = s0 * q1.z + s1 * q2.z;
            this->w = s0 * q1.w + s1 * q2.w;
        }

        void transform(const JGeometry::TVec3f& v, JGeometry::TVec3f& rDest) const {
            // transformation via hamiltonian multiplication of a unit quaternion
            // q*v*q`
            // where v is the input vector converted into a quaternion with w=0
            // and q` is the multiplicative inverse of q
            // (eg: q = w + xi + yj + zk, q` = w - xi - yj - zk)

            TQuat4 r;
            r.x = ( this->y * v.z) - (this->z * v.y) + (this->w * v.x);
            r.y = (-this->x * v.z) + (this->z * v.x) + (this->w * v.y);
            r.z = ( this->x * v.y) - (this->y * v.x) + (this->w * v.z);
            r.w = (-this->x * v.x) - (this->y * v.y) - (this->z * v.z);

            rDest.template set<T>(
                 r.x *  this->w + r.y * -this->z - r.z * -this->y + r.w * -this->x,
                -r.x * -this->z + r.y *  this->w + r.z * -this->x + r.w * -this->y,
                 r.x * -this->y - r.y * -this->x + r.z *  this->w + r.w * -this->z
            );
        }

        void transform(JGeometry::TVec3f& v) const {
            transform(v, v);
        }

        bool equals(const TQuat4 &other) 
        {
            return (x == other.x && y == other.y && z == other.z && w == other.w);
        }
    };

    typedef TQuat4<f32> TQuat4f;
}

#endif
