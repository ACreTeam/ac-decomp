#ifndef RSPSIM_H
#define RSPSIM_H

#include "types.h"

#define RSPSIM_MODE_INIT 0
#define RSPSIM_MODE_MOVE 1

extern s32 RspStart(u32* pTaskCmds, s32 allTasks);
extern void RspStart2(u32* pTaskCmds, s32 allTasks, s32 mode);

#endif
