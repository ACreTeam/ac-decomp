#ifndef _DOLPHIN_OS
#define _DOLPHIN_OS

#include "types.h"
#include "dolphin/os/OSContext.h"
#include "dolphin/os/OSInterrupt.h"
#include "dolphin/os/OSMessage.h"
#include "libforest/osreport.h" /* OSReport funcs */
#include "dolphin/os/OSReset.h"
#include "va_args.h"

#ifdef __cplusplus
extern "C" {
#endif

// __ppc_eabi_init
extern void __OSPSInit();
extern void __OSFPRInit();
extern void __OSCacheInit();

void OSPanic(const char *file, int line, const char *message, ...);
void OSVReport(const char* fmt, va_list list);
void OSReport(const char* fmt, ...);

extern void __OSPSInit();
extern void __OSCacheInit();

#define OSErrorLine(line, ...) \
    OSPanic(__FILE__, line, __VA_ARGS__)

#ifdef DOLPHIN_DEBUG
#define DOLPHIN_ASSERTLINE(assertion, line)    \
    (void) ((assertion) || (OSErrorLine(line, "Failed assertion " #assertion), 0))
#define DOLPHIN_ASSERT(assertion)               \
    (void) ((assertion) || (OSPanic(__FILE__, __LINE__, "Failed assertion " #assertion), 0))
#else
#define DOLPHIN_ASSERTLINE(assertion, line)
#define DOLPHIN_ASSERT(assertion)
#endif

//void OSResetSystem(u32, u32, u32); // goes in reset, but eh
void OSInit(void);

#define OS_CONSOLE_RETAIL4     0x00000004
#define OS_CONSOLE_RETAIL3     0x00000003
#define OS_CONSOLE_RETAIL2     0x00000002
#define OS_CONSOLE_RETAIL1     0x00000001
#define OS_CONSOLE_RETAIL      0x00000000
#define OS_CONSOLE_DEVHW4      0x10000007
#define OS_CONSOLE_DEVHW3      0x10000006
#define OS_CONSOLE_DEVHW2      0x10000005
#define OS_CONSOLE_DEVHW1      0x10000004
#define OS_CONSOLE_MINNOW      0x10000003
#define OS_CONSOLE_ARTHUR      0x10000002
#define OS_CONSOLE_PC_EMULATOR 0x10000001
#define OS_CONSOLE_EMULATOR    0x10000000
#define OS_CONSOLE_DEVELOPMENT 0x10000000
#define OS_CONSOLE_DEVKIT      0x10000000
#define OS_CONSOLE_TDEVKIT     0x20000000

#define OS_CONSOLE_DEV_MASK    0x10000000

u32 OSGetConsoleType();
#define OS_CONSOLE_IS_DEV() ((OSGetConsoleType() & OS_CONSOLE_DEV_MASK) != 0)

#define OSHalt(msg) OSPanic(__FILE__, __LINE__, msg)

typedef void (*OSExceptionHandler)(u8, OSContext*);
OSExceptionHandler __OSSetExceptionHandler(u8, OSExceptionHandler);

#ifdef __cplusplus
}
#endif
#endif
