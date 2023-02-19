#ifndef _JSYSTEM_JUT_JUTASSERTION_H
#define _JSYSTEM_JUT_JUTASSERTION_H

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

void JC_JUTAssertion_changeDevice(u32);

#define JUT_PANIC(...)
#define JUT_PANIC_F(...)
#define JUT_CONFIRM_MESSAGE(...)
#define JUT_WARNING(...)
#define JUT_WARNING_F(...)
#define JUT_ASSERT(...)
#define JUT_ASSERT_F(...)
#define JUT_ASSERT_MSG(...)
#define JUT_MINMAX_ASSERT(...)
#define JUT_MAX_ASSERT(...)
#define JUT_LOG_F(...)

#ifdef __cplusplus
}
#endif

#endif
