#include "dolphin/os/OSInterrupt.h"

asm BOOL OSDisableInterrupts(void) {
    // clang-format off
    nofralloc

    entry __RAS_OSDisableInterrupts_begin
    mfmsr r3
    rlwinm r4, r3, 0, 17, 15
    mtmsr r4
    entry __RAS_OSDisableInterrupts_end
    rlwinm r3, r3, 17, 31, 31
    blr
    // clang-format on       
}

asm BOOL OSEnableInterrupts(void) {
    // clang-format off
    nofralloc
    /* 8007AC38 7C6000A6 */ mfmsr       r3
    /* 8007AC3C 60648000 */ ori         r4, r3, 0x8000
    /* 8007AC40 7C800124 */ mtmsr       r4
    /* 8007AC44 54638FFE */ rlwinm      r3, r3, 0x11, 0x1f, 0x1f
    /* 8007AC48 4E800020 */ blr   
    // clang-format on       
}

asm BOOL OSRestoreInterrupts(register BOOL level) {
    // clang-format off
    nofralloc
    /* 8007AC4C 2C030000 */ cmpwi       level, 0x0
    /* 8007AC50 7C8000A6 */ mfmsr       r4
    /* 8007AC54 4182000C */ beq-        lbl_8007ac60
    /* 8007AC58 60858000 */ ori         r5, r4, 0x8000
    /* 8007AC5C 48000008 */ b           lbl_8007ac64
    lbl_8007ac60:
    /* 8007AC60 5485045E */ rlwinm      r5, r4, 0, 0x11, 0xf
    lbl_8007ac64:
    /* 8007AC64 7CA00124 */ mtmsr       r5
    /* 8007AC68 54838FFE */ rlwinm      r3, r4, 0x11, 0x1f, 0x1f
    /* 8007AC6C 4E800020 */ blr 
    // clang-format on       
}