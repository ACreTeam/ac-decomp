#include "TRK/nubevent.h"
#include "TRK/mutex_trk.h"
#include "TRK/_mem_trk.h"
#include "TRK/msgbuf.h"

TRKEventQueue gTRKEventQueue;

TRKResult TRKInitializeEventQueue(){
    TRKInitializeMutex(&gTRKEventQueue);
    TRKAcquireMutex(&gTRKEventQueue);
    gTRKEventQueue.mCurrEvtID = 0;
	gTRKEventQueue.mNextSlotToOverwrite = 0;
	gTRKEventQueue.mMax = 0x100;
    TRKReleaseMutex(&gTRKEventQueue);
    return TRKSuccess;
}

BOOL TRKGetNextEvent(TRKEvent* event){

    BOOL res = FALSE;
    TRKAcquireMutex(&gTRKEventQueue);

        if(gTRKEventQueue.mCurrEvtID > 0){
            TRK_memcpy(event, &gTRKEventQueue.mEvents[gTRKEventQueue.mNextSlotToOverwrite], sizeof(TRKEvent));
            gTRKEventQueue.mCurrEvtID--;
            if(++gTRKEventQueue.mNextSlotToOverwrite == 2){
                gTRKEventQueue.mNextSlotToOverwrite = 0;
            }
            res = TRUE;
        }
    TRKReleaseMutex(&gTRKEventQueue);
    return res;
}

TRKResult TRKPostEvent(TRKEvent* event){

    TRKResult res = 0;
    int evId;

    TRKAcquireMutex(&gTRKEventQueue);

    if(gTRKEventQueue.mCurrEvtID == 2){
        res = 0x100;
    }
    else{
        evId = (gTRKEventQueue.mNextSlotToOverwrite + gTRKEventQueue.mCurrEvtID) % 2;
        TRK_memcpy(&gTRKEventQueue.mEvents[evId], event, sizeof(TRKEvent));
        gTRKEventQueue.mEvents[evId].mMax = gTRKEventQueue.mMax;
        gTRKEventQueue.mMax++;
        if(gTRKEventQueue.mMax < 256){
            gTRKEventQueue.mMax = 256;
        }
         gTRKEventQueue.mCurrEvtID++;
    }
    TRKReleaseMutex(&gTRKEventQueue);
    return res;
}
void TRKConstructEvent(TRKEvent* event, int type){

    event->mEventType = type;
    event->mMax = 0;
    event->mBufferIndex = -1;
}
void TRKDestructEvent(TRKEvent* event){
    TRKReleaseBuffer(event->mBufferIndex);
}