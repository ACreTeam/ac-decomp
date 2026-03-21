/* RTC shim: maps GC real-time-clock reads to system clock. */
#include "platform/platform.h"
#include <dolphin/os/OSRtc.h>
#include <time.h>
#include <string.h>

extern "C" {

/* OSSram: the GC SRAM stores language, sound mode, etc.
 * Return a zeroed struct with sensible defaults. */
static OSSramEx s_sram_ex = {};
static bool s_sram_init = false;

OSSram* __OSLockSram(void) {
    static OSSram s;
    if (!s_sram_init) {
        memset(&s, 0, sizeof(s));
        s.checkSum    = 0;
        s.checkSumInv = 0xFFFF;
        s.ead0        = 0;
        s.ead1        = 0;
        s.counterBias = 0;
        s.displayOffsetH = 0;
        s.ntd         = 0;
        s.language    = 1; /* English */
        s.flags       = 0;
        s_sram_init   = true;
    }
    return &s;
}

OSSramEx* __OSLockSramEx(void) {
    return &s_sram_ex;
}

void __OSUnlockSram(BOOL flush) { (void)flush; }
void __OSUnlockSramEx(BOOL flush) { (void)flush; }

BOOL __OSReadROM(void* buf, u32 length, u32 offset) {
    (void)buf; (void)length; (void)offset;
    return FALSE;
}

u32 __OSGetRTCBias(void) { return 0; }

} /* extern "C" */
