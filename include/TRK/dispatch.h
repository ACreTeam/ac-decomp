#ifndef TRK_DISPATCH
#define TRK_DISPATCH
#include "types.h"
#include "TRK/trk.h"
#include "TRK/msgbuf.h"

#ifdef __cplusplus
extern "C" {
#endif

TRKResult TRKDispatchMessage(MessageBuffer* mBuf);
TRKResult TRKInitializeDispatcher();

#ifdef __cplusplus
}
#endif
#endif
