#ifndef TRK_SERPOLL
#define TRK_SERPOLL
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

void TRKGetInput();
TRKResult TRKInitializeSerialHandler();
TRKResult TRKTerminateSerialHandler();

extern u8* gTRKInputPendingPtr;

#ifdef __cplusplus
}
#endif

#endif
