#ifndef MTX_H
#define MTX_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef float Mtx[3][4];
typedef float Mtx44[4][4];

typedef struct {
  f32 x;
  f32 y;
  f32 z;
} Vec;

void PSMTXConcat(const Mtx, const Mtx, Mtx);
void PSMTXCopy(const Mtx, Mtx);
void PSMTXIdentity(Mtx);
void PSMTXTranspose(const Mtx, Mtx);
u32 PSMTXInverse(const Mtx, Mtx);

#ifdef __cplusplus
}
#endif

#endif
