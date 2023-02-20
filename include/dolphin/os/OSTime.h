#ifndef OS_TIME_H
#define OS_TIME_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef s64 OSTime;
OSTime OSGetTime(void);

#ifdef __cplusplus
}
#endif
#endif