#include "TRK/mainloop.h"
#include "TRK/nubevent.h"
#include "TRK/dispatch.h"
#include "TRK/targimpl.h"
#include "TRK/serpoll.h"

void TRKNubMainLoop(void){
    
    MessageBuffer* msg;
    TRKEvent event;
    BOOL loop = FALSE;
    BOOL statInput = FALSE;
    
    while(loop == FALSE){
        if(TRKGetNextEvent(&event) != FALSE){
            statInput = FALSE;
            switch(event.mEventType){
                case 0:
                break;
                case 2:
                    msg = TRKGetBuffer(event.mBufferIndex);
                    TRKDispatchMessage(msg);
                break;
                case 1:
                    loop = TRUE;
                break;
                case 3:
                case 4:
                    TRKTargetInterrupt(&event);
                break;
                case 5:
                TRKTargetSupportRequest();
                break;
            }
            TRKDestructEvent(&event);
        }
        else if((statInput == FALSE) || ((u8)*gTRKInputPendingPtr != 0)){
            statInput = TRUE;
            TRKGetInput();
        }
        else{
            if(TRKTargetStopped() == FALSE){
                TRKTargetContinue();
            }
            statInput = FALSE;
        }
    }
}
