#ifndef TRK_NUBEVENT
#define TRK_NUBEVENT
#include "types.h"
#include "TRK/trk.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct TRKEventQueue{
    int unk0; 
    int mCurrEvtID;
    int mNextSlotToOverwrite;
    TRKEvent mEvents[2];
    u32 mMax;
}TRKEventQueue;


TRKResult TRKInitializeEventQueue();
BOOL TRKGetNextEvent(TRKEvent*);
TRKResult TRKPostEvent(TRKEvent*);
void TRKConstructEvent(TRKEvent*, int);
void TRKDestructEvent(TRKEvent*);

#ifdef __cplusplus
}
#endif

#endif
