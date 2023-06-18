#ifndef TRK_TARGIMPL
#define TRK_TARGIMPL
#include "types.h"
#include "TRK/trk.h"
#ifdef __cplusplus
extern "C" {
#endif

void TRKTargeInterrupt(TRKEvent*);
void TRKTargetSupportRequest();
BOOL TRKTargetStopped();
void TRKTargetContinue();
void TRKTargetSetInputPendingPtr(void*);

#ifdef __cplusplus
}
#endif
#endif
