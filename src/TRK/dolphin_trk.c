#include "TRK/_mem_trk.h"

__declspec(section ".init") asm void __TRK_reset(void){
    nofralloc
/* 80005468 9421FFE0 */ stwu        r1, -0x20(r1)
/* 8000546C 7C0802A6 */ mflr        r0
/* 80005470 3C608021 */ lis         r3, lc_base@ha
/* 80005474 90010024 */ stw         r0, 0x24(r1)
/* 80005478 3863B550 */ addi        r3, r3, lc_base@l
/* 8000547C BF61000C */ stmw        r27, 0xc(r1)
/* 80005480 80630000 */ lwz         r3, 0(r3)
/* 80005484 28030044 */ cmplwi      r3, 0x44
/* 80005488 4181002C */ bgt-        lbl_800054b4
/* 8000548C 38034000 */ addi        r0, r3, 0x4000
/* 80005490 28000044 */ cmplwi      r0, 0x44
/* 80005494 40810020 */ ble-        lbl_800054b4
/* 80005498 3C608021 */ lis         r3, gTRKCPUState@ha
/* 8000549C 3863B078 */ addi        r3, r3, gTRKCPUState@l
/* 800054A0 80030238 */ lwz         r0, 0x238(r3)
/* 800054A4 540007BF */ clrlwi.     r0, r0, 0x1e
/* 800054A8 4182000C */ beq-        lbl_800054b4
/* 800054AC 38A00044 */ li          r5, 0x44
/* 800054B0 4800000C */ b           lbl_800054bc
lbl_800054b4:
/* 800054B4 3C608000 */ lis         r3, 0x8000
/* 800054B8 38A30044 */ addi        r5, r3, 0x44
lbl_800054bc:
/* 800054BC 3C80800E */ lis         r4, TRK_ISR_OFFSETS@ha
/* 800054C0 3C608021 */ lis         r3, gTRKCPUState@ha
/* 800054C4 83A50000 */ lwz         r29, 0(r5)
/* 800054C8 3BE42218 */ addi        r31, r4, TRK_ISR_OFFSETS@l
/* 800054CC 3BC3B078 */ addi        r30, r3, gTRKCPUState@l
/* 800054D0 3B800000 */ li          r28, 0x0
lbl_800054d4:
/* 800054D4 38000001 */ li          r0, 0x1
/* 800054D8 7C00E030 */ slw         r0, r0, r28
/* 800054DC 7FA00039 */ and.        r0, r29, r0
/* 800054E0 41820068 */ beq-        lbl_80005548
/* 800054E4 3C608021 */ lis         r3, lc_base@ha
/* 800054E8 80DF0000 */ lwz         r6, 0(r31)
/* 800054EC 3863B550 */ addi        r3, r3, lc_base@l
/* 800054F0 80630000 */ lwz         r3, 0(r3)
/* 800054F4 7C061840 */ cmplw       r6, r3
/* 800054F8 41800024 */ blt-        lbl_8000551c
/* 800054FC 38034000 */ addi        r0, r3, 0x4000
/* 80005500 7C060040 */ cmplw       r6, r0
/* 80005504 40800018 */ bge-        lbl_8000551c
/* 80005508 801E0238 */ lwz         r0, 0x238(r30)
/* 8000550C 540007BF */ clrlwi.     r0, r0, 0x1e
/* 80005510 4182000C */ beq-        lbl_8000551c
/* 80005514 7CDB3378 */ mr          r27, r6
/* 80005518 4800000C */ b           lbl_80005524
lbl_8000551c:
/* 8000551C 54C000BE */ clrlwi      r0, r6, 2
/* 80005520 641B8000 */ oris        r27, r0, 0x8000
lbl_80005524:
/* 80005524 3C808000 */ lis         r4, func_80003534@ha
/* 80005528 7F63DB78 */ mr          r3, r27
/* 8000552C 38043534 */ addi        r0, r4, func_80003534@l
/* 80005530 38A00100 */ li          r5, 0x100
/* 80005534 7C803214 */ add         r4, r0, r6
/* 80005538 4BFFDFD9 */ bl          TRK_memcpy
/* 8000553C 7F63DB78 */ mr          r3, r27
/* 80005540 38800100 */ li          r4, 0x100
/* 80005544 480A125D */ bl          TRK_flush_cache
lbl_80005548:
/* 80005548 3B9C0001 */ addi        r28, r28, 0x1
/* 8000554C 3BFF0004 */ addi        r31, r31, 0x4
/* 80005550 2C1C000E */ cmpwi       r28, 0xe
/* 80005554 4081FF80 */ ble+        lbl_800054d4
/* 80005558 BB61000C */ lmw         r27, 0xc(r1)
/* 8000555C 80010024 */ lwz         r0, 0x24(r1)
/* 80005560 7C0803A6 */ mtlr        r0
/* 80005564 38210020 */ addi        r1, r1, 0x20
/* 80005568 4E800020 */ blr         
}
