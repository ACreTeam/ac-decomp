#include "libultra/gu.h"

void guNormalize(float* x, float* y, float* z) {
    float norm = sqrtf(*x * *x + *y * *y + *z * *z);
    norm = 1.0f / norm;
    *x *= norm;
    *y *= norm;
    *z *= norm;
    // might return norm
}
