#include "libultra/libultra.h"
#include "dolphin/os.h"

void osStopTimerAll(void){
    BOOL enable;
    OSTimer* prev;
    OSTimer* next;

    enable = OSDisableInterrupts();
    next = __osTimerList->next;
    
    while(next != __osTimerList){
        OSCancelAlarm(&next->alarm);
        prev = next->next;
        prev->prev = next->prev;
        next->prev->next = next->next;
        next->next = NULL;
        next->prev = NULL;
        next = prev;
    }
    OSRestoreInterrupts(enable);
}
