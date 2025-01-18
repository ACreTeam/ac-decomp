#ifndef OSREPORT_H
#define OSREPORT_H

#include "types.h"
// #include "va_args.h"
#include "dolphin/os/OSMutex.h"
#include "dolphin/os/OSThread.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG_MODE 0
#define RETAIL_MODE 1

/* Causes DSI exception */
#define OSThrow() (*(int*)0 = 0)

extern void my_fopen(); /* @unused */
extern void my_fgets(); /* @unused */
extern void my_fclose(); /* @unused */
extern void print_section(); /* @unused */
extern void* OSGetCallerPC(); /* @unused */
extern void OSDumpStackTrace(); /* @unused */
extern s32 OSGetActiveThreadID(); /* @unused */
extern void OSReportMonopoly(); /* @unused */

extern void OSReportDisable();
extern void OSReportEnable();
//void OSVReport(const char* fmt, va_list list);
//void OSReport(const char* fmt, ...);
//void OSPanic(const char* file, u32 line, const char* fmt, ...);
extern void OSChangeBootMode(u32 mode);
extern void OSDVDFatalError();

#define OSChangeToRetail() (OSChangeBootMode(RETAIL_MODE))
#define OSChangeToDebug() (OSChangeBootMode(DEBUG_MODE))

#ifdef __cplusplus
}
#endif

#endif
