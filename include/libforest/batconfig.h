#ifndef BATCONFIG_H
#define BATCONFIG_H

#include "types.h"
#include "dolphin/os/OSMemory.h"
#include "dolphin/os/OSInterrupt.h"

asm void Config24MB();
asm void Config48MB();
void ReconfigBATs();
#endif