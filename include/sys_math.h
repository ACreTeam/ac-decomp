#ifndef SYS_MATH_H
#define SYS_MATH_H

#include "types.h"
#include "MSL_C/math.h"

#ifdef __cplusplus
extern "C" {
#endif

extern s16 atans_table(f32 x, f32 y);
extern f32 atanf_table(f32 x, f32 y);
extern void init_rnd();

#ifdef __cplusplus
}
#endif

#endif
