#include "libforest/batconfig.h"

asm void Config24MB(){
nofralloc
/* 8005ADAC 7C6000A6 */ mfmsr       r3
/* 8005ADB0 54630734 */ rlwinm      r3, r3, 0, 0x1c, 0x1a
/* 8005ADB4 7C600124 */ mtmsr       r3
/* 8005ADB8 4C00012C */ isync       
/* 8005ADBC 38E00000 */ li          r7, 0x0
/* 8005ADC0 3C800000 */ lis         r4, 0
/* 8005ADC4 38840002 */ addi        r4, r4, 0x2
/* 8005ADC8 3C608000 */ lis         r3, 0x8000
/* 8005ADCC 386301FF */ addi        r3, r3, 0x1ff
/* 8005ADD0 3CC00100 */ lis         r6, 0x100
/* 8005ADD4 38C60002 */ addi        r6, r6, 0x2
/* 8005ADD8 3CA08100 */ lis         r5, 0x8100
/* 8005ADDC 38A500FF */ addi        r5, r5, 0xff
/* 8005ADE0 4C00012C */ isync       
/* 8005ADE4 7CF883A6 */ mtdbatu     0, r7
/* 8005ADE8 7C9983A6 */ mtdbatl     0, r4
/* 8005ADEC 7C7883A6 */ mtdbatu     0, r3
/* 8005ADF0 4C00012C */ isync       
/* 8005ADF4 7CFC83A6 */ mtdbatu     2, r7
/* 8005ADF8 7CDD83A6 */ mtdbatl     2, r6
/* 8005ADFC 7CBC83A6 */ mtdbatu     2, r5
/* 8005AE00 4C00012C */ isync       
/* 8005AE04 7C6000A6 */ mfmsr       r3
/* 8005AE08 60630010 */ ori         r3, r3, 0x10
/* 8005AE0C 7C600124 */ mtmsr       r3
/* 8005AE10 4C00012C */ isync       
/* 8005AE14 4E800020 */ blr         
}
asm void Config48MB(){
nofralloc
/* 8005AE18 7C6000A6 */ mfmsr       r3
/* 8005AE1C 54630734 */ rlwinm      r3, r3, 0, 0x1c, 0x1a
/* 8005AE20 7C600124 */ mtmsr       r3
/* 8005AE24 4C00012C */ isync       
/* 8005AE28 38E00000 */ li          r7, 0x0
/* 8005AE2C 3C800000 */ lis         r4, 0
/* 8005AE30 38840002 */ addi        r4, r4, 0x2
/* 8005AE34 3C608000 */ lis         r3, 0x8000
/* 8005AE38 386303FF */ addi        r3, r3, 0x3ff
/* 8005AE3C 3CC00200 */ lis         r6, 0x200
/* 8005AE40 38C60002 */ addi        r6, r6, 0x2
/* 8005AE44 3CA08200 */ lis         r5, 0x8200
/* 8005AE48 38A501FF */ addi        r5, r5, 0x1ff
/* 8005AE4C 4C00012C */ isync       
/* 8005AE50 7CF883A6 */ mtdbatu     0, r7
/* 8005AE54 7C9983A6 */ mtdbatl     0, r4
/* 8005AE58 7C7883A6 */ mtdbatu     0, r3
/* 8005AE5C 4C00012C */ isync       
/* 8005AE60 7CFC83A6 */ mtdbatu     2, r7
/* 8005AE64 7CDD83A6 */ mtdbatl     2, r6
/* 8005AE68 7CBC83A6 */ mtdbatu     2, r5
/* 8005AE6C 4C00012C */ isync       
/* 8005AE70 7C6000A6 */ mfmsr       r3
/* 8005AE74 60630010 */ ori         r3, r3, 0x10
/* 8005AE78 7C600124 */ mtmsr       r3
/* 8005AE7C 4C00012C */ isync       
/* 8005AE80 4E800020 */ blr
}
void ReconfigBATs(){
    BOOL rest = OSDisableInterrupts();
    if (OSGetConsoleSimulatedMemSize() <= 0x1800000){
        Config24MB();
    }
    else {
        Config48MB();
    }
    OSRestoreInterrupts(rest);
}