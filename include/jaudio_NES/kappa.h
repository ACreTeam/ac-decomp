#ifndef KAPPA_H
#define KAPPA_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct kappa_ {
    u16 unk0;
    f32 unk4;
}kappa;

extern int Na_GetKappaCounter(kappa*);
extern void Na_SetKappaSeqHandle(int flag);

#ifdef __cplusplus
}
#endif


#endif