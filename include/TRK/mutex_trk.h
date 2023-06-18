#ifndef TRK_MUTEX_TRK
#define TRK_MUTEX_TRK
#include "types.h"
#include "TRK/trk.h"
#ifdef __cplusplus
extern "C" {
#endif

TRKResult TRKAcquireMutex(void*);
TRKResult TRKReleaseMutex(void*);
TRKResult TRKInitializeMutex(void*);


#ifdef __cplusplus
}
#endif

#endif