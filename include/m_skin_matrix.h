#ifndef SKIN_MATRIX_H
#define SKIN_MATRIX_H

#include "types.h"
#include "libultra/ultratypes.h"
#include "libu64/u64types.h"

#ifdef __cplusplus
extern "C"{
#endif

extern void Skin_Matrix_PrjMulVector(MtxF* mf, xyz_t* src, xyz_t* dst, f32* w);
extern void Skin_Matrix_MulMatrix(MtxF* mfA, MtxF* mfB, MtxF* dest);
extern void Skin_Matrix_SetScale(MtxF* mf, f32 x, f32 y, f32 z);
extern void Skin_Matrix_SetRotateXyz_s(MtxF* mf, s16 x, s16 y, s16 z);
extern void Skin_Matrix_SetTranslate(MtxF* mf, f32 x, f32 y, f32 z);

#ifdef __cplusplus
}
#endif

#endif