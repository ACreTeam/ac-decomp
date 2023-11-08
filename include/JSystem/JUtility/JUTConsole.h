#ifndef _JSYSTEM_JUT_JUTCONSOLE_H
#define _JSYSTEM_JUT_JUTCONSOLE_H

#include "va_args.h"

class JUTConsole; // TODO

#ifdef __cplusplus
extern "C"
{
#endif
void JUTConsole_print_f_va_(JUTConsole*, const char*, va_list);

JUTConsole* JUTGetReportConsole();
void JUTSetReportConsole(JUTConsole*);
JUTConsole* JUTGetWarningConsole();
void JUTSetWarningConsole(JUTConsole*);
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
