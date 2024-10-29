#include "libultra/gu.h"

void guMtxIdent(Mtx *m) {
    float mf[4][4];
    guMtxIdentF(mf);
    guMtxF2L(mf, m);
}
