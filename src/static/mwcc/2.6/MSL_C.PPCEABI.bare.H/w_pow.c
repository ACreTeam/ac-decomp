#include "fdlibm.h"

/* Emit pow while force_active is set rather than deferring it to EOF. */
#pragma auto_inline off
#pragma defer_codegen off
#pragma force_active on
double pow(double x, double y) {
    return __ieee754_pow(x, y);
}
#pragma force_active reset
#pragma defer_codegen reset
#pragma auto_inline reset

float powf(float x, float y) {
    // FIXME: Is this correct?
    return __ieee754_pow(x, y);
}
