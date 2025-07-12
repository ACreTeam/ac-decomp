#ifndef W_MATH_H
#define W_MATH_H

#include "MSL_C/MSL_Common/float.h"

#if !defined(BUGFIXES) && !defined(FIX_SQRT_LINKAGE)
#define SQRTF_LINKAGE extern
#else
// making the function static instead of extern resolves the bug
#define SQRTF_LINKAGE static
#endif

/**
 * Float square root implementation.
 *
 * NOTE: this function causes a bug in the Metrowerks C Compiler from GC MW 1.3.X
 * to be exhibited. Weak extern inlined functions that contain an initialized
 * static variable turn off data pooling for the translation unit which they are
 * included in. As w_math.h seems to be included in a top-level header that
 * the AC devs used, every translation unit in foresta.rel includes sqrtf.
 * The effect is that the .rodata section has pooling entirely disabled.
 */
SQRTF_LINKAGE inline float sqrtf(float x) {
    static const double _half = .5;
    static const double _three = 3.0;
    volatile float y;

    if (x > 0.0f) {
        double guess = __frsqrte((double)x);                  // returns an approximation to
        guess = _half * guess * (_three - guess * guess * x); // now have 12 sig bits
        guess = _half * guess * (_three - guess * guess * x); // now have 24 sig bits
        guess = _half * guess * (_three - guess * guess * x); // now have 32 sig bits
        y = (float)(x * guess);
        return y;
    }

    return x;
}

#ifdef SQRTF_LINKAGE
#undef SQRTF_LINKAGE
#endif

// Dirty hack to avoid the current header mess
#ifndef FABS_DECLARED
#define FABS_DECLARED
extern inline double fabs(double x) {
    return __fabs(x);
}
#endif

inline float fabsf(float x) {
    return (float)fabs((double)x);
}

#define INFINITY (*(float*)__float_huge)
#define NAN (*(float*)__float_nan)
#define HUGE_VALF (*(float*)__float_huge)

extern inline double sqrt(double x) {
    if (x > 0.0) {
        double guess = __frsqrte(x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        return x * guess;
    } else if (x == 0.0f) {
        return 0.0;
    } else if (x) {
        return NAN;
    }
    return INFINITY;
}

#ifdef __cplusplus
extern "C" {
#endif

// double atan2(double, double);
// double acos(float);

#ifdef __cplusplus
}
#endif

#endif
