/* Shadow: replaces PowerPC-specific MSL w_math.h with system math.h.
 * The original uses __frsqrte / __fabs PowerPC intrinsics not available on arm64. */
#ifndef W_MATH_H
#define W_MATH_H
#endif
#include <math.h>
#ifndef SQRTF_LINKAGE
#define SQRTF_LINKAGE extern
#endif
