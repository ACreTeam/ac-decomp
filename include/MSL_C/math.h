#ifndef MATH_H
#define MATH_H

#include "types.h"
#include "MSL_C/w_math.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PI 3.14159265358979323846
#define F_PI ((f32)PI)

#define SQRTF(f) (__frsqrte(f))

extern double sin(double deg);
extern double cos(double deg);
extern double tan(double deg);

#ifdef __cplusplus
}
#endif

#endif
