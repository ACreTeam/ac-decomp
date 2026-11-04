#ifndef _JSYSTEM_JUT_JUTASSERTION_H
#define _JSYSTEM_JUT_JUTASSERTION_H

#include "types.h"
#include "dolphin/os.h"

#ifdef __cplusplus
extern "C" {

namespace JUTAssertion {
void create();
void flushMessage();
void flushMessage_dbPrint();
u32 getSDevice(void);

void changeDisplayTime(u32 time);
void changeDevice(u32 device);

void showAssert_f(u32 device, char const* file, int line, char const* errormsg, ...);
inline void showAssert(u32 device, char const* file, int line, char const* errormsg) {
    showAssert_f(device, file, line, "%s", errormsg);
}

void setConfirmMessage(u32 device, char* file, int line, bool condition, const char* msg);
void setWarningMessage_f(u32 device, char* file, int line, char const*, ...);
inline void setWarningMessage(u32 device, char* file, int line, char const* errormsg) {
    setWarningMessage_f(device, file, line, "%s", errormsg);
}

void setLogMessage_f(u32 device, char* file, int line, char const* fmt, ...);
extern "C" {
void showAssert_f_va(u32 device, const char* file, int line, const char* fmt, va_list vl);
void setWarningMessage_f_va(u32 device, char* file, int line, const char* fmt, va_list vl);
void setLogMessage_f_va(u32 device, char* file, int line, const char* fmt, va_list vl);
}
} // namespace JUTAssertion

#define JUT_PANIC(...)
#define JUT_PANIC_F(...)
#define JUT_CONFIRM_MESSAGE(...)
#define JUT_WARNING(...)
#define JUT_WARNING_F(...)
#define JUT_ASSERT_MSG(...)
#define JUT_MINMAX_ASSERT(...)
#define JUT_MAX_ASSERT(...)
#define JUT_LOG_F(...)
#define JUT_ASSERT(...)
#define JUT_ASSERT_F(...)
}
#endif

#endif
