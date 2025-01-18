#include "TRK/trk.h"

TRKEventQueue gTRKEventQueue;

DSError TRKInitializeEventQueue(){
    TRKInitializeMutex(&gTRKEventQueue);
    TRKAcquireMutex(&gTRKEventQueue);
    gTRKEventQueue.count = 0;
	gTRKEventQueue.next = 0;
	gTRKEventQueue.eventID = 0x100;
    TRKReleaseMutex(&gTRKEventQueue);
    return DS_NoError;
}

BOOL TRKGetNextEvent(TRKEvent* event){

    BOOL res = FALSE;
    TRKAcquireMutex(&gTRKEventQueue);

        if(gTRKEventQueue.count > 0){
            TRK_memcpy(event, &gTRKEventQueue.events[gTRKEventQueue.next], sizeof(TRKEvent));
            gTRKEventQueue.count--;
            if(++gTRKEventQueue.next == 2){
                gTRKEventQueue.next = 0;
            }
            res = TRUE;
        }
    TRKReleaseMutex(&gTRKEventQueue);
    return res;
}

DSError TRKPostEvent(TRKEvent* event){

    DSError res = 0;
    int evId;

    TRKAcquireMutex(&gTRKEventQueue);

    if(gTRKEventQueue.count == 2){
        res = 0x100;
    }
    else{
        evId = (gTRKEventQueue.next + gTRKEventQueue.count) % 2;
        TRK_memcpy(&gTRKEventQueue.events[evId], event, sizeof(TRKEvent));
        gTRKEventQueue.events[evId].eventID = gTRKEventQueue.eventID;
        gTRKEventQueue.eventID++;
        if(gTRKEventQueue.eventID < 256){
            gTRKEventQueue.eventID = 256;
        }
         gTRKEventQueue.count++;
    }
    TRKReleaseMutex(&gTRKEventQueue);
    return res;
}
void TRKConstructEvent(TRKEvent* event, int type){

    event->eventType = type;
    event->eventID = 0;
    event->msgBufID = -1;
}
void TRKDestructEvent(TRKEvent* event){
    TRKReleaseBuffer(event->msgBufID);
}
