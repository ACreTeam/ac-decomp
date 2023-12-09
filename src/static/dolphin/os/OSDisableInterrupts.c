#include "dolphin/os/OSInterrupt.h"

asm BOOL OSDisableInterrupts(void){
    nofralloc

    entry __RAS_OSDisableInterrupts_begin
    mfmsr r3
    rlwinm r4, r3, 0, 17, 15
    mtmsr r4
    entry __RAS_OSDisableInterrupts_end
    rlwinm r3, r3, 17, 31, 31
    blr
}