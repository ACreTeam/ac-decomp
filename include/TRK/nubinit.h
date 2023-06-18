#ifndef TRK_NUBINIT
#define TRK_NUBINIT
#include "types.h"
#include "TRK/trk.h"
#ifdef __cplusplus
extern "C" {
#endif

TRKResult TRKInitializeNub(void);
TRKResult TRKTerminateNub(void);
void TRKNubWelcome(void);


#ifdef __cplusplus
}
#endif

#endif
