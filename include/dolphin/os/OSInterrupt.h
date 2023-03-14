#ifndef OS_INTERRUPT_H
#define OS_INTERRUPT_H
#include "types.h"


BOOL OSDisableInterrupts(void);
BOOL OSEnableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL status);

void __RAS_OSDisableInterrupts_begin(void);
void __RAS_OSDisableInterrupts_end(void);

#endif