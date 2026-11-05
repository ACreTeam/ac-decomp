#ifndef JUTASSERT_H
#define JUTASSERT_H

#include <stdio.h>
#include <dolphin/os.h>
#include "types.h"

namespace JUTAssertion
{
  void create();
  void flushMessage();
  void flushMessage_dbPrint();
  u32 getSDevice(void);
  void changeDisplayTime(u32 time);
  void changeDevice(u32 device);

  void showAssert_f(u32 device, char const *file, int line, char const *errormsg, ...);
  inline void showAssert(u32 device, char const *file, int line, char const *errormsg) {
    showAssert_f(device, file, line, "%s", errormsg);
  }

  void setConfirmMessage(u32 device, char *file, int line, bool condition, const char *msg);
  void setWarningMessage_f(u32 device, char *file, int line, char const *, ...);
  inline void setWarningMessage(u32 device, char *file, int line, char const *errormsg) {
    setWarningMessage_f(device, file, line, "%s", errormsg);
  }

  void setLogMessage_f(u32 device, char *file, int line, char const *fmt, ...);
  extern "C"
  {
    void showAssert_f_va(u32 device, const char *file, int line, const char *fmt, va_list vl);
    void setWarningMessage_f_va(u32 device, char *file, int line, const char *fmt, va_list vl);
    void setLogMessage_f_va(u32 device, char *file, int line, const char *fmt, va_list vl);
  }
}

#if DEBUG

// Asserts
#define JUT_CONFIRM_MESSAGE(COND) \
  JUTAssertion::setConfirmMessage(JUTAssertion::getSDevice(), __FILE__, __LINE__, COND, #COND);

#define JUT_WARNING(COND) \
  (COND) ? (void)0 : JUTAssertion::setWarningMessage(JUTAssertion::getSDevice(), __FILE__, __LINE__, #COND);

#define JUT_WARNING_F(COND, ...) \
  (COND) ? (void)0 : JUTAssertion::setWarningMessage_f(JUTAssertion::getSDevice(), __FILE__, __LINE__, __VA_ARGS__);

// how about get rid of this and pass true to JUT_WARNING_F instead?
#define JUT_WARNING_F2(...) \
  JUTAssertion::setWarningMessage_f(JUTAssertion::getSDevice(), __FILE__, __LINE__, __VA_ARGS__);

// TODO: refactor
// perhaps "%s" is already added here
#define JUT_CRITICAL_WARNING_F(...) \
  JUTAssertion::setWarningMessage_f(2, __FILE__, __LINE__, __VA_ARGS__);

  // perhaps "%s" is already added here
#define JUT_WARNING_F1(...) \
JUTAssertion::setWarningMessage_f(1, __FILE__, __LINE__, __VA_ARGS__);
// perhaps "%s" is already added here
#define JUT_WARNING_F3(...) \
  JUTAssertion::setWarningMessage_f(3, __FILE__, __LINE__, __VA_ARGS__);

#define JUT_ASSERT(COND) \
  (COND) ? (void)0 : (JUTAssertion::showAssert(JUTAssertion::getSDevice(), __FILE__, __LINE__, #COND), OSHalt("Halt"));

#define JUT_ASSERT_F(COND, ...) \
  (COND) ? (void)0 : (JUTAssertion::showAssert_f(JUTAssertion::getSDevice(), __FILE__, __LINE__, __VA_ARGS__), OSHalt("Halt"));

// could this maybe have used __VA_ARGS__?
#define JUT_ASSERT_MSG(COND, MSG) \
  (COND) ? (void)0 : (JUTAssertion::showAssert(JUTAssertion::getSDevice(), __FILE__, __LINE__, MSG), OSHalt("Halt"));

#define JUT_MINMAX_ASSERT(min, cur, max) \
  JUT_ASSERT_F((((min) <= (cur)) && ((cur) < (max))), "range over: %d <= " #cur "=%d < %d", (min), (cur), (max));

// TODO: might not exist, unsigned comparisons against 0 get discarded
#define JUT_MAX_ASSERT(cur, max) \
  JUT_ASSERT_F(((cur) < (max)), "range over: %d <= " #cur "=%d < %d", 0, (cur), (max));

#define JUT_LOG_F(...) \
  JUTAssertion::setLogMessage_f(JUTAssertion::getSDevice(), __FILE__, __LINE__, __VA_ARGS__);

#define JUT_REPORT_MSG(...) \
  OSReport(__VA_ARGS__);

#else // for non debug build
#define JUT_CONFIRM_MESSAGE(...)
#define JUT_WARNING(...)
#define JUT_WARNING_F(...)
#define JUT_WARNING_F2(...) // remove condintional?
#define JUT_CRITICAL_WARNING_F(...)
#define JUT_ASSERT(...) (void)0;
#define JUT_ASSERT_F(...) (void)0;
#define JUT_ASSERT_MSG(...) (void)0;
#define JUT_MINMAX_ASSERT(...) (void)0;
#define JUT_MAX_ASSERT(...) (void)0;
#define JUT_LOG_F(...)
#define JUT_REPORT_MSG(...) (void)0
#endif

#endif
