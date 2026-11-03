/**
 * MWCriticalSection_gc.c
 * Description:
 */

#include "TRK_MINNOW_DOLPHIN/utils/gc/MWCriticalSection_gc.h"

extern "C" BOOL OSRestoreInterrupts(unsigned int);
extern "C" unsigned int OSDisableInterrupts();

extern void MWInitializeCriticalSection(unsigned int*) {}

extern void MWEnterCriticalSection(unsigned int* section) {
    *section = OSDisableInterrupts();
}

extern void MWExitCriticalSection(unsigned int* section) {
    OSRestoreInterrupts(*section);
}
