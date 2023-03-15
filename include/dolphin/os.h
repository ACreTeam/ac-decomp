#ifndef _DOLPHIN_OS
#define _DOLPHIN_OS

#include "types.h"
#include "dolphin/os/OSContext.h"
#include "dolphin/os/OSInterrupt.h"
#include "dolphin/os/OSMessage.h"
#include "libforest/osreport.h" /* OSReport funcs */
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

void OSResetSystem(u32, u32, u32); // goes in reset, but eh
void OSInit(void);


typedef void (*OSExceptionHandler)(u8, OSContext*);
OSExceptionHandler __OSSetExceptionHandler(u8, OSExceptionHandler);

#ifdef __cplusplus
}
#endif
#endif
