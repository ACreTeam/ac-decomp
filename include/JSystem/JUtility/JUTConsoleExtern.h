#ifndef JUTCONSOLEEXTERN_H
#define JUTCONSOLEEXTERN_H

#include "types.h"
#include "va_args.h"

#ifdef __cplusplus
extern "C"
{
#endif
void JUTReportConsole(const char*);
void JUTReportConsole_f(const char*, ...);
void JUTReportConsole_f_va(const char*, va_list);
void JUTWarningConsole(const char*);
void JUTWarningConsole_f(const char*, ...);
void JUTWarningConsole_f_va(const char*, va_list);
#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
