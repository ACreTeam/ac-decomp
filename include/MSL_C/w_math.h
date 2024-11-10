#ifndef W_MATH_H
#define W_MATH_H

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

double atan2(double, double);
double acos(float);

#ifdef __cplusplus
}
#endif

#endif
