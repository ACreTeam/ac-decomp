#ifndef _DOLPHIN_OS
#define _DOLPHIN_OS

#include "types.h"
#include "dolphin/os/OSContext.h"
#include "va_args.h"
#ifdef __cplusplus
extern "C" {
#endif

void OSPanic(const char *file, int line, const char *message, ...);
void OSReport(const char*, ...);
void OSVReport(const char* format, va_list list);

#define OSErrorLine(line, ...) \
    OSPanic(__FILE__, line, __VA_ARGS__)

asm BOOL OSDisableInterrupts(void);
asm BOOL OSEnableInterrupts(void);
asm BOOL OSRestoreInterrupts(BOOL level);

void __RAS_OSDisableInterrupts_begin(void);
void __RAS_OSDisableInterrupts_end(void);

typedef void (*OSExceptionHandler)(u8, OSContext*);
OSExceptionHandler __OSSetExceptionHandler(u8, OSExceptionHandler);

#ifdef __cplusplus
};
#endif
#endif
