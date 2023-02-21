#include "dolphin/os.h"

asm BOOL OSEnableInterrupts(void){

nofralloc
/* 8007AC38 7C6000A6 */ mfmsr       r3
/* 8007AC3C 60648000 */ ori         r4, r3, 0x8000
/* 8007AC40 7C800124 */ mtmsr       r4
/* 8007AC44 54638FFE */ rlwinm      r3, r3, 0x11, 0x1f, 0x1f
/* 8007AC48 4E800020 */ blr   
}