#include "dolphin/os.h"

asm BOOL OSRestoreInterrupts(register BOOL level){

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
}