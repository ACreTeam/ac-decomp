#ifndef TRK_NUBEVENT
#define TRK_NUBEVENT
#include "types.h"
#include "TRK/trk.h"
#ifdef __cplusplus
extern "C" {
#endif

BOOL TRKGetNextEvent(TRKEvent*);
void TRKDestructEvent(TRKEvent*);

#ifdef __cplusplus
}
#endif

#endif
