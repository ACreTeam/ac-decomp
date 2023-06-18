#ifndef DOLPHIN_TRK_H
#define DOLPHIN_TRK_H
#include "types.h"
#include "TRK/trk.h"
#ifdef __cplusplus
extern "C"{
#endif

void InitMetroTRK(void);
void exit(void);
TRKResult TRKInitializeTarget();

#ifdef __cplusplus
}
#endif
#endif
