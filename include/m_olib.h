#ifndef M_OLIB_H
#define M_OLIB_H

#include "types.h"
#include "libu64/u64types.h"
#include "libc64/math64.h"

#ifdef __cplusplus
extern "C" {
#endif

//gotta put these somewhere else
#define TRUNCF_BINANG(f) (s16)(s32)(f)
#define CAM_DEG_TO_BINANG(degrees) (s16)TRUNCF_BINANG((degrees) * 182.04167f + .5f)
#define RAD_TO_DEG(radians) ((radians) * (180.0f / M_PI))

typedef struct rect_s {
  int top, bottom;
  int l, r;
} rect;

typedef struct generic_unit_s {
  int z;
  int x;
} BlockOrUnit_c;

extern void radianxy_by_2pos(xyz_t* dest, xyz_t* sub, xyz_t* min);
extern s_xyz sanglexy_by_2pos(xyz_t* sub, xyz_t* min); 

#ifdef __cplusplus
}
#endif

#endif
