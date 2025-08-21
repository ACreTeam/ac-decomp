#ifndef MATH_H
#define MATH_H

#include "types.h"
#include "MSL_C/w_math.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PI 3.14159265358979323846
#define F_PI ((f32)PI)

#define SQRT2 (1.4142135623730950488016887242097)
#define F_SQRT2 ((f32)SQRT2)
#define F_SQRT2_DIV2 (0.707106f)

#define SQRTF(f) (__frsqrte(f))

extern double sin(double deg);
extern double cos(double deg);
extern double tan(double deg);

float sinf(float);
float cosf(float);

inline float sinf(float x) {
    return (float)sin((double)x);
}

inline float cosf(float x) {
    return (float)cos((double)x);
}

extern double ceil(double);

#ifdef __cplusplus
}
#endif

#endif
