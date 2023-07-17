#ifndef SKIN_MATRIX_H
#define SKIN_MATRIX_H

#include "libultra/ultratypes.h"
#include "libu64/u64types.h"

#ifdef __cplusplus
extern "C"{
#endif

void Skin_Matrix_PrjMulVector(MtxF*, xyz_t*, xyz_t*, f32*);
void Skin_Matrix_MulMatrix(MtxF*, MtxF*, MtxF*);
void Skin_Matrix_SetScale(MtxF* , f32 , f32, f32);
void Skin_Matrix_SetTranslate(MtxF*, f32, f32, f32);
void Skin_Matrix_SetRotateXyz_s(MtxF*, s16, s16, s16);


#ifdef __cplusplus
}
#endif

#endif