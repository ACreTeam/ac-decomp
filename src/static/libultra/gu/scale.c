#include "libultra/gu.h"

void guScale(Mtx *m, float x, float y, float z) {
    float mf[4][4];
    guScaleF(mf, x, y, z);
    guMtxF2L(mf, m);
}
