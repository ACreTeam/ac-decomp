/* Shadow: replaces include/dolphin/os.h for arm64.
 * Fixes two issues:
 *  1. __OSBusClock / __OSCoreClock dereference fixed MMIO addresses — redirect to constants.
 *  2. Metrowerks AT_ADDRESS globals for hardware registers — already handled by compat.h.
 */
#ifndef _DOLPHIN_OS
#define _DOLPHIN_OS

#include "types.h"
#include "dolphin/os/OSAlloc.h"
#include "dolphin/os/OSArena.h"
#include "dolphin/os/OSCache.h"
#include "dolphin/os/OSContext.h"
#include "dolphin/os/OSError.h"
#include "dolphin/os/OSInterrupt.h"
#include "dolphin/os/OSModule.h"
#include "dolphin/os/OSLink.h"
#include "dolphin/os/OSMemory.h"
#include "dolphin/os/OSMessage.h"
#include "libforest/osreport.h"
#include "dolphin/os/OSReset.h"
#include "dolphin/os/OSFont.h"
#include <dolphin/os/OSTime.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSRtc.h>
#include <dolphin/hw_regs.h>  /* shadow version redirects to dummy arrays */

#ifdef __cplusplus
extern "C" {
#endif

extern void __OSPSInit(void);
extern void __OSFPRInit(void);
extern void __OSCacheInit(void);

void OSPanic(const char* file, int line, const char* message, ...);
void OSVReport(const char* fmt, va_list list);
void OSReport(const char* fmt, ...);

#define OSErrorLine(line, ...) OSPanic(__FILE__, line, __VA_ARGS__)

#ifdef DOLPHIN_DEBUG
#define DOLPHIN_ASSERTLINE(assertion, line) \
    (void)((assertion) || (OSErrorLine(line, "Failed assertion " #assertion), 0))
#define DOLPHIN_ASSERT(assertion) \
    (void)((assertion) || (OSPanic(__FILE__, __LINE__, "Failed assertion " #assertion), 0))
#else
#define DOLPHIN_ASSERTLINE(assertion, line)
#define DOLPHIN_ASSERT(assertion)
#endif

void OSInit(void);

#define OS_CONSOLE_RETAIL4       0x00000004
#define OS_CONSOLE_RETAIL3       0x00000003
#define OS_CONSOLE_RETAIL2       0x00000002
#define OS_CONSOLE_RETAIL1       0x00000001
#define OS_CONSOLE_RETAIL        0x00000000
#define OS_CONSOLE_DEVHW4        0x10000007
#define OS_CONSOLE_DEVHW3        0x10000006
#define OS_CONSOLE_DEVHW2        0x10000005
#define OS_CONSOLE_DEVHW1        0x10000004
#define OS_CONSOLE_MINNOW        0x10000003
#define OS_CONSOLE_ARTHUR        0x10000002
#define OS_CONSOLE_PC_EMULATOR   0x10000001
#define OS_CONSOLE_EMULATOR      0x10000000
#define OS_CONSOLE_DEVELOPMENT   0x10000000
#define OS_CONSOLE_DEVKIT        0x10000000
#define OS_CONSOLE_TDEVKIT       0x20000000
#define OS_CONSOLE_DEV_MASK      0x10000000

u32 OSGetConsoleType(void);
#define OS_CONSOLE_IS_DEV() ((OSGetConsoleType() & OS_CONSOLE_DEV_MASK) != 0)

#define OSHalt(msg) OSPanic(__FILE__, __LINE__, msg)

typedef void (*OSExceptionHandler)(u8, OSContext*);
OSExceptionHandler __OSSetExceptionHandler(u8, OSExceptionHandler);

#include <dolphin/dvd.h>

typedef struct OSBootInfo_s {
    DVDDiskID DVDDiskID;
    unsigned long magic;
    unsigned long version;
    unsigned long memorySize;
    unsigned long consoleType;
    void * arenaLo;
    void * arenaHi;
    void * FSTLocation;
    unsigned long FSTMaxLength;
} OSBootInfo;

/* Physical/cached region prefixes — GC memory map constants (safe to keep as defines) */
#define OS_CACHED_REGION_PREFIX   0x8000
#define OS_UNCACHED_REGION_PREFIX 0xC000
#define OS_PHYSICAL_MASK          0x3FFF
#define OS_BASE_CACHED   (OS_CACHED_REGION_PREFIX   << 16)
#define OS_BASE_UNCACHED (OS_UNCACHED_REGION_PREFIX << 16)

typedef struct BI2Debug {
    s32 debugMonSize;
    s32 simMemSize;
    u32 argOffset;
    u32 debugFlag;
    int trackLocation;
    int trackSize;
    u32 countryCode;
    u8  unk[8];
    u32 padSpec;
} BI2Debug;

/* PLATFORM: replace MMIO derefs with compile-time constants */
#ifndef __OSBusClock
#define __OSBusClock   162000000UL
#endif
#ifndef __OSCoreClock
#define __OSCoreClock  486000000UL
#endif

#define OS_BUS_CLOCK   __OSBusClock
#define OS_CORE_CLOCK  __OSCoreClock
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)

#define OSTicksToSeconds(ticks)      ((ticks)   / (OS_TIMER_CLOCK))
#define OSTicksToMilliseconds(ticks) ((ticks)   / (OS_TIMER_CLOCK / 1000))
#define OSTicksToMicroseconds(ticks) ((ticks)*8 / (OS_TIMER_CLOCK / 125000))
#define OSSecondsToTicks(sec)        ((sec) * (OS_TIMER_CLOCK))
#define OSMillisecondsToTicks(msec)  ((msec) * (OS_TIMER_CLOCK / 1000))
#define OSNanosecondsToTicks(nsec)   (((nsec) * (OS_TIMER_CLOCK / 125000)) / 8000)
#define OSMicrosecondsToTicks(usec)  (((usec) * (OS_TIMER_CLOCK / 125000)) / 8)

/* Avoid external-linkage duplicates on Apple by using local inline forms below. */
#if !defined(__APPLE__)
void *OSPhysicalToCached(u32 paddr);
void *OSPhysicalToUncached(u32 paddr);
u32 OSCachedToPhysical(void *caddr);
u32 OSUncachedToPhysical(void *ucaddr);
void *OSCachedToUncached(void *caddr);
void *OSUncachedToCached(void *ucaddr);
#endif
/* In release builds, these are macros — use inline functions instead to avoid
 * dereferencing GC physical addresses as pointers */
#if !DEBUG
#undef OSPhysicalToCached
#undef OSPhysicalToUncached
#undef OSCachedToPhysical
#undef OSUncachedToPhysical
#undef OSCachedToUncached
#undef OSUncachedToCached
static inline void* OSPhysicalToCached(u32 p)   { return (void*)(uintptr_t)p; }
static inline void* OSPhysicalToUncached(u32 p) { return (void*)(uintptr_t)p; }
static inline u32   OSCachedToPhysical(void* p) { return (u32)(uintptr_t)p; }
static inline u32   OSUncachedToPhysical(void* p){ return (u32)(uintptr_t)p; }
static inline void* OSCachedToUncached(void* p) { return p; }
static inline void* OSUncachedToCached(void* p) { return p; }
#endif

#define OFFSET(addr, align) (((u32)(uintptr_t)(addr) & ((align)-1)))

#ifdef __cplusplus
}
#endif
#endif /* _DOLPHIN_OS */
