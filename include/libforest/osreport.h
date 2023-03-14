#ifndef LIB_OS_REPORT_H
#define LIB_OS_REPORT_H

#include "types.h"
#include "va_args.h"

void OSReportDisable(void);
void OSReportEnable(void);

void OSVReport(const char*, va_list);

void OSReport(const char*,...);
void OSPanic(const char*, u32, const char*,...);

void OSChangeBootMode(u32);

void OSDVDFatalError(void);

#endif