#ifndef BATCONFIG_H
#define BATCONFIG_H

#include "types.h"
#include "dolphin/os/OSMemory.h"
#include "dolphin/os/OSInterrupt.h"


#ifdef __cplusplus
extern "C" {
#endif

asm void Config24MB();
asm void Config48MB();
void ReconfigBATs();


#ifdef __cplusplus
}
#endif

#endif