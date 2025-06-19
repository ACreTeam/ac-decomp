#ifndef INITIALIZE_H
#define INITIALIZE_H

#include "types.h"
#include "dolphin/os/OSTime.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void __osInitialize_common();
extern BOOL osIsEnableShutdown(void);
extern BOOL osIsDisableShutdown(void);
extern OSTime osGetDisableShutdownTime(void);

extern OSTime __osShutdownTime;
extern OSTime __osDisableShutdownTime;
extern int __osShutdownDisable;

#ifdef __cplusplus
}
#endif

#endif
