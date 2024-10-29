#ifndef OS_MEMORY_H
#define OS_MEMORY_H
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SIM_MEM *(u32 *)0x800000f0 
static void Config24MB();
static void Config48MB();
u32 OSGetConsoleSimulatedMemSize(void);

#ifdef __cplusplus
}
#endif
#endif