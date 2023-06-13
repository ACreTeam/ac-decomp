#ifndef SYS_MATRIX_H
#define SYS_MATRIX_H

#include "types.h"
#include "libultra/ultratypes.h"
#include "PR/mbi.h"
#include "m_lib.h"

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

extern void Matrix_softcv3_mult(xyz_t* src, s_xyz* dest);
extern Mtx* _MtxF_to_Mtx(MtxF* src, Mtx* dest);
extern void Matrix_mult(MtxF* m, s8 flag);
extern void Matrix_Position(xyz_t* wpos, xyz_t* screen_pos);

#ifdef __cplusplus
}
#endif

#endif
