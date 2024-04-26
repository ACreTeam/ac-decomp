#ifndef W_MATH_H
#define W_MATH_H
#include "types.h"

/* this is needed to keep $localstatic$ variables out of the rel */
#ifndef OPTIMIZED_SQRTF
extern inline float sqrtf(float x) {
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
#else
extern inline float sqrtf(float x) {
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);            // returns an approximation to
        guess = .5 * guess * (3.0 - guess * guess * x); // now have 12 sig bits
        guess = .5 * guess * (3.0 - guess * guess * x); // now have 24 sig bits
        guess = .5 * guess * (3.0 - guess * guess * x); // now have 32 sig bits
        y = (float)(x * guess);
        return y;
    }
    return x;
}
#endif

// hack to get some functions matching where the static const locals are needed
// disabled until static const locals are resolved
/*
extern inline float sqrtf2(float x)
{
        static const double _half=.5;
        static const double _three=3.0;
        volatile float y;
        if(x > 0.0f)
        {
                double guess = __frsqrte((double)x);   // returns an approximation to
                guess = _half*guess*(_three - guess*guess*x);  // now have 12 sig bits
                guess = _half*guess*(_three - guess*guess*x);  // now have 24 sig bits
                guess = _half*guess*(_three - guess*guess*x);  // now have 32 sig bits
                y=(float)(x*guess);
                return y;
        }
        return x;
}
*/

extern inline double fabs(double x) {
    return __fabs(x);
}

inline float fabsf(float x) {
    return (float)fabs((double)x);
}

int __float_huge[];
int __float_nan[];
int __double_huge[];
int __extended_huge[];

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

f64 atan2(f64, f64);
f64 acos(f32);

#ifdef __cplusplus
}
#endif

#endif
