/* OS shim: routes GameCube OS calls to POSIX / Apple platform equivalents.
 * Stage 1: all functions stubbed — returns safe no-op values so the game
 * reaches the first frame without crashing. */
#include "platform/platform.h"
#include <dolphin/os.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <mach/mach_time.h>
#include <time.h>

/* ---- Hardware register dummy buffers (declared in hw_regs.h shadow) ---- */
volatile uint16_t plat_VIRegs[64]    = {0};
volatile uint32_t plat_PIRegs[16]    = {0};
volatile uint16_t plat_MEMRegs[64]   = {0};
volatile uint16_t plat_DSPRegs[32]   = {0};
volatile uint32_t plat_DIRegs[16]    = {0};
volatile uint32_t plat_SIRegs[0x100] = {0};
volatile uint32_t plat_EXIRegs[0x40] = {0};
volatile uint32_t plat_AIRegs[8]     = {0};

/* ---- Arena / heap simulation ---- */
static uint8_t s_arena[32 * 1024 * 1024]; /* 32 MB simulated main RAM */
static void*   s_arenaLo = s_arena;
static void*   s_arenaHi = s_arena + sizeof(s_arena);

/* ---- Basic OS ---- */
extern "C" {

void OSInit(void) {
    /* No-op: hardware init not required on arm64 */
}

u32 OSGetConsoleType(void) {
    return OS_CONSOLE_RETAIL;
}

void __attribute__((weak)) OSReport(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
}

void __attribute__((weak)) OSVReport(const char* fmt, va_list list) {
    vfprintf(stderr, fmt, list);
}

void __attribute__((weak)) OSPanic(const char* file, int line, const char* msg, ...) {
    va_list ap;
    va_start(ap, msg);
    fprintf(stderr, "OSPanic %s:%d: ", file, line);
    vfprintf(stderr, msg, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    abort();
}

/* ---- Interrupts: all no-op on arm64 ---- */
BOOL OSDisableInterrupts(void)          { return TRUE; }
BOOL OSEnableInterrupts(void)           { return TRUE; }
BOOL OSRestoreInterrupts(BOOL level)    { return level; }
u32  __OSMaskInterrupts(u32 mask)       { (void)mask; return 0; }
u32  __OSUnmaskInterrupts(u32 mask)     { (void)mask; return 0; }
void __OSInterruptInit(void)            {}
void __OSPSInit(void)                   {} /* PowerPC paired-singles: no-op */
void __OSFPRInit(void)                  {} /* FPR init: no-op */
void __OSCacheInit(void)                {} /* Cache init: no-op */
void OSSetExceptionHandler(u8, void*)   {}

OSExceptionHandler __OSSetExceptionHandler(u8 idx, OSExceptionHandler h) {
    (void)idx; (void)h; return NULL;
}

/* ---- Time ----
 * GC timebase runs at ~40.5 MHz (OS_TIMER_CLOCK = OS_BUS_CLOCK/4).
 * We use mach_absolute_time() scaled to match. */
static mach_timebase_info_data_t s_tbinfo;
static uint64_t s_startTick = 0;

static void time_init(void) {
    if (s_startTick == 0) {
        mach_timebase_info(&s_tbinfo);
        s_startTick = mach_absolute_time();
    }
}

OSTime OSGetTime(void) {
    time_init();
    /* Convert mach ticks to nanoseconds, then to GC ticks at ~40.5 MHz */
    uint64_t elapsed = mach_absolute_time() - s_startTick;
    uint64_t ns = elapsed * s_tbinfo.numer / s_tbinfo.denom;
    return (OSTime)(ns * GC_TIMER_CLOCK / 1000000000ULL);
}

OSTick OSGetTick(void) {
    return (OSTick)(OSGetTime() & 0xFFFFFFFFu);
}

OSTime __OSGetSystemTime(void) {
    return OSGetTime();
}

void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime* td) {
    if (!td) return;
    /* GC epoch: Jan 1, 2000 00:00:00.
     * Unix epoch: Jan 1, 1970 00:00:00.
     * Delta: 946684800 seconds. */
    uint64_t secs = (uint64_t)ticks / GC_TIMER_CLOCK;
    time_t unix_time = (time_t)(secs + 946684800ULL);
    struct tm* t = localtime(&unix_time);
    if (!t) { memset(td, 0, sizeof(*td)); return; }
    td->sec   = t->tm_sec;
    td->min   = t->tm_min;
    td->hour  = t->tm_hour;
    td->mday  = t->tm_mday;
    td->mon   = t->tm_mon;
    td->year  = t->tm_year + 1900;
    td->wday  = t->tm_wday;
    td->yday  = t->tm_yday;
    td->msec  = 0;
    td->usec  = 0;
}

OSTime OSCalendarTimeToTicks(OSCalendarTime* td) {
    if (!td) return 0;
    struct tm t = {};
    t.tm_sec  = td->sec;
    t.tm_min  = td->min;
    t.tm_hour = td->hour;
    t.tm_mday = td->mday;
    t.tm_mon  = td->mon;
    t.tm_year = td->year - 1900;
    time_t unix_time = mktime(&t);
    if (unix_time < 0) return 0;
    uint64_t secs = (uint64_t)unix_time - 946684800ULL;
    return (OSTime)(secs * GC_TIMER_CLOCK);
}

/* ---- Arena / Memory ---- */
void* OSGetArenaHi(void)              { return s_arenaHi; }
void* OSGetArenaLo(void)              { return s_arenaLo; }
void  OSSetArenaHi(void* p)           { s_arenaHi = p; }
void  OSSetArenaLo(void* p)           { s_arenaLo = p; }

void* OSInitAlloc(void* start, void* end, int maxHeaps) {
    (void)end; (void)maxHeaps; return start;
}
int   OSCreateHeap(void* start, void* end) { (void)start; (void)end; return 0; }
void* OSAllocFromHeap(int heap, unsigned long size) { (void)heap; return malloc(size); }
void  OSFreeToHeap(int heap, void* ptr)    { (void)heap; free(ptr); }
int   OSSetCurrentHeap(int heap)           { return heap; }
void  OSProtectRange(u32, void*, u32, u32) {}

/* Address translation inlined in platform/include/dolphin/os.h */

volatile OSHeapHandle __OSCurrHeap = 0;

} /* extern "C" */
