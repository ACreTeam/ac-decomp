#include "libc64/math64.h"
#include "MSL_C/gcn_math.h"
#include "MSL_C/w_math.h"

f32 fatan2(f32 x, f32 y) {
    return atan2f(x, y);
}

f32 fsqrt(f32 x) {
    return sqrtf(x);
}

f32 facos(f32 x) {
    return acosf(x);
}
