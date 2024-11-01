#ifndef LOS_THREAD_H
#define LOS_THREAD_H

#include "types.h"
#include "dolphin/os/OSThread.h"

typedef s32 OSPri;
typedef s32 OSId;


OSId osGetThreadId(OSThread*);

#endif
