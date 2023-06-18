#ifndef TRK_MSGHNDLR
#define TRK_MSGHNDLR
#include "types.h"
#include "TRK/trk.h"
#include "TRK/msgbuf.h"

#ifdef __cplusplus
extern "C" {
#endif

TRKResult TRKDoUnsupported(MessageBuffer*);
TRKResult TRKDoConnect(MessageBuffer*);
TRKResult TRKDoDisconnect(MessageBuffer*);
TRKResult TRKDoReset(MessageBuffer*);
TRKResult TRKDoVersions(MessageBuffer*);
TRKResult TRKDoSupportMask(MessageBuffer*);
TRKResult TRKDoCPUType(MessageBuffer*);
TRKResult TRKDoReadMemory(MessageBuffer*);
TRKResult TRKDoWriteMemory(MessageBuffer*);
TRKResult TRKDoReadRegisters(MessageBuffer*);
TRKResult TRKDoWriteRegisters(MessageBuffer*);
TRKResult TRKDoFlushCache(MessageBuffer*);
TRKResult TRKDoSetOption(MessageBuffer*);
TRKResult TRKDoContinue(MessageBuffer*);
TRKResult TRKDoStep(MessageBuffer*);
TRKResult TRKDoStop(MessageBuffer*);










#ifdef __cplusplus
}
#endif

#endif