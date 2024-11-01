#ifndef INITIALIZE_H
#define INITIALIZE_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void __osInitialize_common();
extern BOOL osIsEnableShutdown(void);

#ifdef __cplusplus
}
#endif

#endif
