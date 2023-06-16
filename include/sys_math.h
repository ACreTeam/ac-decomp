#ifndef SYS_MATH_H
#define SYS_MATH_H

#include "types.h"
#include "MSL_C/math.h"

#ifdef __cplusplus
extern "C" {
#endif


extern u16 U_GetAtanTable(f32 y, f32 x);
extern s16 atans_table(f32 x, f32 y);
extern f32 atanf_table(f32 x, f32 y);
extern void init_rnd();
extern f32 sinf_table(f32 x);
extern f32 cosf_table(f32 x);

#ifdef __cplusplus
}
#endif

#endif
