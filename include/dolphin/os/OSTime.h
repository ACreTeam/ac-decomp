#ifndef OS_TIME_H
#define OS_TIME_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

#define OSDiffTick(tick1, tick0) ((s32)(tick1) - (s32)(tick0))

typedef s64 OSTime;
typedef u32 OSTick;

OSTime OSGetTime(void);
OSTick OSGetTick(void);

#ifdef __cplusplus
}
#endif
#endif