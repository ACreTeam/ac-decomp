#ifndef _DOLPHIN_OS
#define _DOLPHIN_OS

#include "types.h"
#include "dolphin/os/OSContext.h"
#include "dolphin/os/OSMessage.h"
#include "va_args.h"
#ifdef __cplusplus
extern "C" {
#endif

// __ppc_eabi_init
extern void __OSPSInit();
extern void __OSFPRInit();
extern void __OSCacheInit();

void OSPanic(const char *file, int line, const char *message, ...);
void OSReport(const char*, ...);
void OSVReport(const char* format, va_list list);

extern void __OSPSInit();
extern void __OSCacheInit();

#define OSErrorLine(line, ...) \
    OSPanic(__FILE__, line, __VA_ARGS__)


void OSResetSystem(u32, u32, u32); // goes in reset, but eh
void OSInit(void);


typedef void (*OSExceptionHandler)(u8, OSContext*);
OSExceptionHandler __OSSetExceptionHandler(u8, OSExceptionHandler);

#ifdef __cplusplus
};
#endif
#endif
