#ifndef BATCONFIG_H
#define BATCONFIG_H

#include "types.h"
#include "dolphin/os/OSMemory.h"
#include "dolphin/os/OSInterrupt.h"


#ifdef __cplusplus
extern "C" {
#endif

void Config24MB();
void Config48MB();
void ReconfigBATs();


#ifdef __cplusplus
}
#endif

#endif