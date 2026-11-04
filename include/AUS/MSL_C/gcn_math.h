#ifndef GCN_MATH_H
#define GCN_MATH_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

double atan2(double, double);
double acos(double);

#ifdef __cplusplus
}
#endif

inline float atan2f(float x, float y) {
    return (float)atan2(x, y);
}

inline float acosf(float x) {
    return (float)acos(x);
}

#endif // GCN_MATH_H
