#ifndef SYS_MATRIX_H
#define SYS_MATRIX_H

#include "types.h"
#include "libultra/ultratypes.h"
#include "PR/mbi.h"

#ifdef __cplusplus
extern "C" {
#endif

extern MtxF MtxF_clear;
extern Mtx Mtx_clear;

extern void Matrix_push();
extern void Matrix_pull();
extern void Matrix_get(MtxF* m);
extern void Matrix_put(MtxF* m);
extern void new_Matrix(GAME* game);

#ifdef __cplusplus
}
#endif

#endif
