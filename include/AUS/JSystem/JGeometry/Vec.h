#include "types.h"
#include <dolphin/mtx.h>
extern "C" f32 PSVECMag(const Vec*);
extern "C" void PSVECCrossProduct(const Vec*, const Vec*, Vec*);
#ifndef JGEOMETRY_VEC_H
#define JGEOMETRY_VEC_H

#include "JSystem/JGeometry/Util.h"
#include "JSystem/JGeometry/Vec.h"

namespace JGeometry {
    inline void setTVec3f(register const f32 *src, register f32 *dst)
    {
#ifdef __MWERKS__
        register f32 xy, z;
        __asm {
            // clang-format off
            psq_l xy, 0(src), 0, 0
            lfs z, 8(src)
            psq_st xy, 0(dst), 0, 0
            stfs z, 8(dst)
            // clang-format on
        }
#endif
    }

    inline void negateInternal(register const f32 *src, register f32 *dst)
    {
#ifdef __MWERKS__
        register f32 xy;
        __asm {
            // clang-format off
            psq_l xy, 0(src), 0, 0
            ps_neg xy, xy
            psq_st xy, 0(dst), 0, 0
            // clang-format on
        }
        dst[2] = -src[2];
#endif
    }

    inline void mulInternal(register const f32 *vec1, register const f32 *vec2, register f32 *dst) 
    {
#ifdef __MWERKS__
        register f32 xy1, xy2, res;
        __asm {
            // clang-format off
            psq_l xy1, 0(vec1), 0, 0
            psq_l xy2, 0(vec2), 0, 0
            ps_mul res, xy1, xy2
            psq_st res, 0(dst), 0, 0
            // clang-format on
        }
        dst[2] = vec1[2] * vec2[2];
#endif
    }

    template <typename T>
    class TVec2
    {
    public:
        TVec2() {}

        template <typename TY>
        TVec2(TY X, TY Y) { set(X, Y); }

        template <typename TY>
        void set(TY X, TY Y)
        {
            x = X;
            y = Y;
        }

        void set(const TVec2 &other)
        {
            x = other.x;
            y = other.y;
        }

        template <typename TY>
        void setAll(TY val)
        {
            x = val;
            y = val;
        }

        void setMin(const TVec2<f32> &min)
        {
            if (x >= min.x)
                x = min.x;
            if (y >= min.y)
                y = min.y;
        }

        void setMax(const TVec2<f32> &max)
        {
            if (x <= max.x)
                x = max.x;
            if (y <= max.y)
                y = max.y;
        }

        void add(const TVec2<T> &other)
        {
            x += other.x;
            y += other.y;
        }

        void scale(T scalar) {
            x *= scalar;
            y *= scalar;
        }

        void zero() { x = y = 0; }

        f32 dot(const TVec2<T> &other) const { return x * other.x + y * other.y; }
        f32 length() const { return TUtilf::sqrt(squared()); }
        f32 squared() const { return dot(*this); }

        f32 normalize()
        {
            f32 this_squared = squared();
            if (this_squared <= TUtilf::epsilon())
                return 0.0f;
            else
            {
                f32 invsqrt = TUtilf::inv_sqrt(this_squared);
                scale(invsqrt);
                return invsqrt * this_squared;
            }
        }

        /** @fabricated */
        // TVec2<T> adding(const TVec2<T>& other) { return TVec2<T>(x + other.x, y + other.y); }

        bool isAbove(const TVec2<T> &other) const { return (x >= other.x) && (y >= other.y) ? true : false; }

        T x, y;
    };

    template <typename T>
    class TVec3 {
    public:
        TVec3() {}

        template <typename TY>
        TVec3(TY X, TY Y, TY Z) { set(X, Y, Z); }

        template <typename TY>
        void set(TY X, TY Y, TY Z)
        {
            x = X;
            y = Y;
            z = Z;
        }

        template <typename TY>
        void set(const TVec3<TY> &src)
        {
            x = src.x;
            y = src.y;
            z = src.z;
        }

        template <typename TY>
        void setAll(TY val)
        {
            x = val;
            y = val;
            z = val;
        }

        T x, y, z;
    };

    template <>
    class TVec3<f32> : public Vec
    {
    public:
        // constructors
        TVec3() {}
        TVec3(const TVec3<f32> &other) { setTVec3f(&other.x, &x); }
        TVec3(const Vec &other) { setTVec3f(&other.x, &x); }

        template <typename TY>
        TVec3(TY X, TY Y, TY Z) { set(X, Y, Z); }

        // getters/setters
        template <typename TY>
        void set(TY X, TY Y, TY Z)
        {
            x = X;
            y = Y;
            z = Z;
        }

        template <typename TY>
        void set(const TVec3<TY> &src)
        {
            x = src.x;
            y = src.y;
            z = src.z;
        }

        template <typename TY>
        void setAll(TY val)
        {
            x = val;
            y = val;
            z = val;
        }
    
        bool equals(const TVec3<f32> &other) const 
        {
            bool equal = false;
            if (x == other.x && y == other.y && z == other.z)
            {
                equal = true;
            }
            return equal;
        }

        bool isZero() const { return (squared() <= TUtilf::epsilon()); }

        f32 setLength(f32 length)
        {
            f32 sq = squared();
            if (sq <= TUtilf::epsilon())
                return 0.0f;

            f32 invsqrt = TUtilf::inv_sqrt(sq);
            scale(invsqrt * length);
            return invsqrt * sq;
        }


        f32 setLength(const JGeometry::TVec3<f32> &other, f32 length)
        {
            f32 sq = other.squared();
            if (sq <= TUtilf::epsilon()) {
                zero();
                return 0.0f;
            }
               

            f32 invsqrt = TUtilf::inv_sqrt(sq);
            scale(invsqrt * length, other);
            return invsqrt * sq;
        }

        void setMax(const TVec3 &other);
        void setMin(const TVec3 &other);
        void setNormal(const TVec3 &vA, const TVec3 &vB, const TVec3 &vC) {
            TVec3 edge1, edge2;
            edge1.sub(vB, vA);
            edge2.sub(vC, vB);
            cross(edge2, edge1);
            normalize();
        }

        void zero() { x = y = z = 0; }        

        // operators
        TVec3 &operator=(const TVec3 &other) {
            setTVec3f(&other.x, &x);
            return *this;
        }

        TVec3 operator-(const TVec3 &operand)
        {
            TVec3 tmp(*this);
            tmp -= operand;
            return tmp;
        }

        TVec3 operator+(const TVec3 &operand)
        {
            TVec3 tmp(*this);
            tmp += operand;
            return tmp;
        }

        TVec3 operator*(f32 scalar) const
        {
            TVec3 scaled(*this);
            scaled *= scalar;
            return scaled;
        }

        TVec3 &operator+=(const TVec3 &operand)
        {
            add(operand);
            return *this;
        }

        TVec3 &operator-=(const TVec3 &operand)
        {
            sub(operand);
            return *this;
        }

        TVec3 &operator*=(f32 scalar)
        {
            scale(scalar);
            return *this;
        }

        TVec3 &operator/=(f32 divisor)
        {
            div(divisor);
            return *this;
        }

        // simple math operations

        void add(const TVec3 &operand) { JMathInlineVEC::PSVECAdd(this, &operand, this); }
        void add(const TVec3 &vec1, const TVec3 &vec2) { JMathInlineVEC::PSVECAdd(&vec1, &vec2, this); }
        
        void sub(const TVec3 &translate) { JMathInlineVEC::PSVECSubtract(this, &translate, this); }
        void sub(const TVec3 &base, const TVec3 &translate) { JMathInlineVEC::PSVECSubtract(&base, &translate, this); }

        void negate() { negateInternal(&x, &x); }
        void negate(const TVec3 &other) { negateInternal(&other.x, &x); }

        void mul(const TVec3 &multiplier) { mulInternal(&x, &multiplier.x, &x); }
        void mul(const TVec3 &vec1, const TVec3 &vec2) { mulInternal(&vec1.x, &vec2.x, &x); }

        void scale(f32 scalar) { JMathInlineVEC::PSVECScale(this, this, scalar); }
        void scale(f32 scalar, const TVec3 &operand) { JMathInlineVEC::PSVECScale(&operand, this, scalar); }

        void scaleAdd(f32 scalar, const TVec3 &operand, const TVec3 &translate) { JMAVECScaleAdd(&operand, &translate, this, scalar); }
        void scaleAdd(f32 scalar, const TVec3 &operand) { JMAVECScaleAdd(&operand, this, this, scalar); }

        void div(f32 divisor) { scale(TUtilf::invert(divisor)); }
        void div(f32 divisor, const TVec3 &operand) { scale(TUtilf::invert(divisor), operand); }

        f32 squared() const { return JMathInlineVEC::PSVECSquareMag(this); }
        f32 squaredZX() const { return dotZX(*this); }
        // more complex math operations

        void cross(const TVec3 &vec1, const TVec3 &vec2) { PSVECCrossProduct(&vec1, &vec2, this); }
        f32 dot(const TVec3 &operand) const { return JMathInlineVEC::PSVECDotProduct(this, &operand); }
        f32 dotZX(const TVec3 &operand) const { return x * operand.x + z * operand.z; }
        f32 length() const { return PSVECMag(this); }

        f32 angle(const TVec3 &vec2) const
        {
            TVec3 crossp;
            crossp.cross(*this, vec2);
            f32 len = crossp.length();
            f32 ang = TUtilf::atan2(len, dot(vec2));

            return TUtilf::abs(ang);
        }

        f32 normalize()
        {
            f32 this_squared = squared();
            if (this_squared <= TUtilf::epsilon())
                return 0.0f;

            f32 invsqrt = TUtilf::inv_sqrt(this_squared);
            this->scale(invsqrt);
            return invsqrt * this_squared;
        }

        f32 normalize(f32 scalar) // fabricated
        {
            f32 this_squared = squared();
            if (this_squared <= TUtilf::epsilon())
                return 0.0f;

            f32 invsqrt = TUtilf::inv_sqrt(this_squared);
            this->scale(invsqrt * scalar);
            return invsqrt * this_squared;
        }

        f32 normalize(const TVec3 &other)
        {
            f32 sq = other.squared();
            if (sq <= TUtilf::epsilon()) {
                this->zero();
                return 0.0f;
            }
            
            f32 invsqrt = TUtilf::inv_sqrt(sq);
            this->scale(invsqrt, other);
            return invsqrt * sq;
        }
    };

    template < typename T >
    class TVec4 : public Quaternion {
    public:
        /* Constructors */
        TVec4() {}

        template < typename A >
        TVec4(A _x, A _y, A _z, A _h) {
            x = _x;
            y = _y;
            z = _z;
            w = _h;
        }

        /* General operations */
        template < typename A >
        void set(const JGeometry::TVec4< A > &rVec) {
            this->x = rVec.x;
            this->y = rVec.y;
            this->z = rVec.z;
            this->w = rVec.w;
        }

        template < typename A >
        void set(A _x, A _y, A _z, A _w) {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }

        void scale(T val);

        TVec3<T>& xyz() { return (JGeometry::TVec3f&)*this; }
    };

    typedef TVec2<f64> TVec2d;
    typedef TVec2<f32> TVec2f;
    typedef TVec2<s16> TVec2s;
    typedef TVec3<f64> TVec3d;
    typedef TVec3<f32> TVec3f;
    typedef TVec3<s16> TVec3s;
    typedef TVec4<f64> TVec4d;
    typedef TVec4<f32> TVec4f;
    typedef TVec4<s16> TVec4s;


    // These need to be specialized or explicitly instantiated here to emit them in the right order in RaceMgr, and
    // MWCC doesn't allow explicitly instantiating template constructors, so they're probably both specialized
    template <> template <> inline TVec3f::TVec3(f32 X, f32 Y, f32 Z) { set(X, Y, Z); }
    template <> template <> inline void TVec3f::set(f32 X, f32 Y, f32 Z) { x = X; y = Y; z = Z; }
}

#endif
