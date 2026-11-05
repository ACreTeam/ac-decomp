#ifndef JMATH_H
#define JMATH_H

#include "MSL_C/math.h"
#include <float.h>


#include <dolphin/mtx.h>
#include <JSystem/JMath/Inline.h>

#include "types.h"

namespace JMath
{
    inline void gekko_ps_copy12(register void *pDest, register const void *pSrc)
    {
        register f32 rxxyx;
        register f32 rzxtx;
        register f32 rxyyy;
        register f32 rzyty;
        register f32 rxzyz;
        register f32 rzztz;
        
        __asm {
            // clang-format off
            psq_l     rxxyx, 0(pSrc), 0, 0
            psq_l     rzxtx, 8(pSrc), 0, 0
            psq_l     rxyyy, 0x10(pSrc), 0, 0
            psq_l     rzyty, 0x18(pSrc), 0, 0
            psq_l     rxzyz, 0x20(pSrc), 0, 0
            psq_l     rzztz, 0x28(pSrc), 0, 0
            psq_st    rxxyx, 0(pDest), 0, 0
            psq_st    rzxtx, 8(pDest), 0, 0
            psq_st    rxyyy, 0x10(pDest), 0, 0
            psq_st    rzyty, 0x18(pDest), 0, 0
            psq_st    rxzyz, 0x20(pDest), 0, 0
            psq_st    rzztz, 0x28(pDest), 0, 0
            // clang-format on
        }
    }

    template <typename T>
    struct TAngleConstant_
    {
        static const f32 RADIAN_DEG090() { return (F_PI * 0.5f); }
        static const f32 RADIAN_DEG180() { return F_PI; }
        static const f32 RADIAN_DEG360() { return (F_PI * 2.0f); }
        static const f32 RADIAN_TO_DEGREE_FACTOR() { return 180.0f / RADIAN_DEG180(); }
    };

    template <int N, typename T>
    struct TSinCosTable
    {
        TSinCosTable() { init(); }

        void init()
        {
            for (int i = 0; i < 2048; i++)
            {
                mTable[i].first = sin(((f64)i * TAngleConstant_<f32>::RADIAN_DEG360()) / 2048.0);
                mTable[i].second = cos(((f64)i * TAngleConstant_<f32>::RADIAN_DEG360()) / 2048.0);
            }
        }
        /**
         * elements are pairs of {sine, cosine}
         */
        f32 sinShort(s16 v) const { return mTable[static_cast<u16>(v) >> (16U - N)].first; }
        f32 cosShort(s16 v) const { return mTable[static_cast<u16>(v) >> (16U - N)].second; }
        f32 sinLap(f32 x) const {
            if (x < 0.0f) {
                return -mTable[static_cast<u16>(-(T)(1 << N) * x) & ((1 << N) - 1)].first;
            }
            return mTable[static_cast<u16>((T)(1 << N) * x) & ((1 << N) - 1)].first;
        }
        
        f32 sinRadian(f32 x) const { 
            if (x < 0.0f) {
                return -mTable[static_cast<u16>(-(T)(1 << N) / TAngleConstant_<T>::RADIAN_DEG360() * x) & ((1 << N) - 1)].first;
            }
            return mTable[static_cast<u16>((T)(1 << N) / TAngleConstant_<T>::RADIAN_DEG360() * x) & ((1 << N) - 1)].first;
        }

        struct SinCosPair { f32 first; f32 second; };
        SinCosPair mTable[2048];
    };

    template <int length, typename T>
    struct TAtanTable
    {
        T atan2_(T, T) const;
        T atan_(T) const;
        T mTable[length];
    };

    template <int length, typename T>
    struct TAsinAcosTable
    {
        T acos2_(T, T) const;
        T acos_(T) const;
        T mTable[length];
    };

    template <>
    struct TAtanTable<1024, f32>
    {
        TAtanTable() { init(); }

        void init()
        {
            for (int i = 0; i < (u32)1024; i++)
            {
                mTable[i] = atan(i / 1024.0);
            }
            mTable[0] = 0.0f;
            mTable2[0] = TAngleConstant_<f32>::RADIAN_DEG180() / 4;
        }

        f32 atan_(f32) const;
        f32 atan2_(f32, f32) const;
        f32 atan2Radian(f32 y, f32 x) const { return atan2_(y, x); }
        f32 alignmentHack(f32 x) const;

        f32 calc(f32 y, f32 x) const
        {
            if (x >= 0.0f)
            {
                if (x >= y)
                {
                    return (0.0f == x ? 0.0f : mTable[(int)((y * 1024.0f) / x + 0.5f)]);
                }
                else
                {
                    return (F_PI * 0.5f) - (y == 0.0f ? 0.0f : mTable[(int)((x * 1024.0f) / y + 0.5f)]);
                }
            }
            else
            {
                x = -x;
                if (x < y)
                {
                    return (y == 0.0f ? 0.0f : mTable[(int)((x * 1024.0f) / y + 0.5f)]) + (F_PI * 0.5f);
                }
                else
                {
                    return F_PI - (x == 0.0f ? 0.0f : mTable[(int)((y * 1024.0f) / x + 0.5f)]);
                }
            }
        }

        f32 calcInverse(f32 y, f32 x) const
        {
            y = -y;
            if (x < 0.0f)
            {
                x = -x;
                if (x >= y)
                {
                    return (x == 0.0f ? 0.0f : mTable[(int)((y * 1024.0f) / x + 0.5f)]) + -F_PI;
                }
                else
                {
                    return -(F_PI * 0.5f) - (y == 0.0f ? 0.0f : mTable[(int)((x * 1024.0f) / y + 0.5f)]);
                }
            }
            else
            {
                if (x < y)
                {
                    return (y == 0.0f ? 0.0f : mTable[(int)((x * 1024.0f) / y + 0.5f)]) + -(F_PI * 0.5f);
                }
                else
                {
                    return -(x == 0.0f ? 0.0f : mTable[(int)((y * 1024.0f) / x + 0.5f)]);
                }
            }
        }

        f32 mTable[1024];
        f32 mTable2[8];
    };

    template <>
    struct TAsinAcosTable<1024, f32>
    {
        TAsinAcosTable() { init(); }
        void init()
        {
            for (int i = 0; i < 1024; i++)
            {
                mTable[i] = asin(i / 1024.0);
            }
            mTable[0] = 0.0f;
            mTable2[0] = TAngleConstant_<f32>::RADIAN_DEG180() / 4;
        }
        f32 acos2_(f32, f32) const;
        f32 acos_(f32) const;
        f32 mTable[1024];
        f32 mTable2[8];
    };

    extern const TAsinAcosTable<1024, f32> asinAcosTable_ __attribute__((aligned(32)));
    extern const TSinCosTable<11, f32> sincosTable_ __attribute__((aligned(32)));
    extern const TAtanTable<1024, f32> atanTable_ __attribute__((aligned(32)));

    class TRandom_fast_
    {
    public:
        TRandom_fast_(u32 num); // maybe has a default ctor?
        u32 get()
        {
            seed = (seed * 0x19660d) + 0x3c6ef35f;
            return seed;
        }

        u32 get_bit32(void) { return get(); }

        // from TP decomp
        f32 get_ufloat_1()
        {
            // !@bug UB: in C++ it's not legal to read from an union member other
            // than the last one that was written to.
            union
            {
                f32 f;
                u32 s;
            } out;
            out.s = (this->get() >> 9) | 0x3f800000;
            return out.f - 1;
        }

        void setSeed(u32 Seed)
        {
            seed = Seed;
        }

    protected:
        u32 seed;
    };

    template <typename T>
    class TRandom_ : public T
    {
    public:
        TRandom_(u32 num) : T(num) {}
    };
}

typedef JMath::TRandom_<JMath::TRandom_fast_> JMARandFast;

inline f32 JMAAbs(f32 input) { return __fabsf(input); }

inline f32 JMAAtan2Radian(f32 y, f32 x) { return JMath::atanTable_.atan2Radian(y, x); };

inline f32 JMASSinLap(f32 x) { return JMath::sincosTable_.sinLap(x); }

inline f32 JMASinRadian(f32 x) { return JMath::sincosTable_.sinRadian(x); }

inline f32 JMACosShort(s16 v) { return JMath::sincosTable_.cosShort(v); }
inline f32 JMASinShort(s16 v) { return JMath::sincosTable_.sinShort(v); }

inline f32 JMASCos(s16 v) { return JMACosShort(v); }
inline f32 JMASSin(s16 v) { return JMASinShort(v); }

inline f32 JMAHermiteInterpolation(register f32 p1, register f32 p2, register f32 p3, register f32 p4, register f32 p5, register f32 p6,
                                   register f32 p7)
{
    register f32 ff25;
    register f32 ff31;
    register f32 ff30;
    register f32 ff29;
    register f32 ff28;
    register f32 ff27;
    register f32 ff26;
    // clang-format off
    __asm {
        fsubs   ff31, p1, p2
        fsubs   ff30, p5, p2
        fdivs   ff29, ff31, ff30
        fmuls   ff28,ff29,ff29
        fadds   ff25,ff29,ff29
        fsubs   ff27,ff28,ff29
        fsubs   ff30, p3, p6
        fmsubs  ff26,ff25,ff27,ff28
        fmadds  ff25,p4,ff27,p4
        fmadds  ff26,ff26,ff30,p3
        fmadds  ff25,p7,ff27,ff25
        fmsubs  ff25,ff29,p4,ff25
        fnmsubs ff25,ff31,ff25,ff26

    }
    // clang-format on
    return ff25;
}

inline f32 JMAFastSqrt(register f32 x)
{
    register f32 recip;

    if (x > 0.0f)
    {
        __asm { frsqrte recip, x }
        return recip * x;
    }
    return x;
}

void JMAEulerToQuat(s16, s16, s16, Quaternion *);
void JMAQuatLerp(const Quaternion *, const Quaternion *, f32, Quaternion *);
void JMAVECScaleAdd(const Vec *, const Vec *, Vec *, f32);
void JMAVECLerp(const Vec *, const Vec *, Vec *, f32);
void JMAMTXApplyScale(const Mtx34, Mtx34, f32, f32, f32);

#endif // !JMATH_H
