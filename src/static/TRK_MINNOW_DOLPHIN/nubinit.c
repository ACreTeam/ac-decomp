#include "TRK/nubinit.h"
#include "TRK/usr_put.h"
#include "TRK/nubevent.h"
#include "TRK/msgbuf.h"
#include "TRK/dispatch.h"
#include "TRK/dolphin_trk_glue.h"
#include "TRK/targimpl.h"
#include "TRK/serpoll.h"
#include "TRK/dolphin_trk.h"

BOOL gTRKBigEndian;

inline BOOL TRK_InitializeEndian(void)
{
    BOOL res = FALSE;
    u8 bendian[4];
    u32 load;
	gTRKBigEndian = TRUE;
    
    bendian[0] = 0x12;
	bendian[1] = 0x34;
	bendian[2] = 0x56;
	bendian[3] = 0x78;

    load = *(u32*)bendian;
	if (load == 0x12345678) {
		gTRKBigEndian = TRUE;
	} else if (load == 0x78563412) {
		gTRKBigEndian = FALSE;
	} else {
        res = TRUE;
    }
    return res;
}

TRKResult TRKInitializeNub (void){
    int res;
    res = TRK_InitializeEndian();

    if (res == 0){
        usr_put_initialize();
    }
    
    if(res == 0){
        res = TRKInitializeEventQueue();
    }
    
    if(res == TRKSuccess){
        res = TRKInitializeMessageBuffers();
    }
    
    if(res == TRKSuccess){
        res = TRKInitializeDispatcher();
    }
    
    if(res == TRKSuccess){
        TRKResult ures = TRKInitializeIntDrivenUART(0xE100, 1, 0, &gTRKInputPendingPtr);
        TRKTargetSetInputPendingPtr(gTRKInputPendingPtr);
        if(ures != TRKSuccess){
            res = ures;
        }
    }

    if(res == TRKSuccess){
        res = TRKInitializeSerialHandler();
    }

    if(res == TRKSuccess){
        res = TRKInitializeTarget();
    }

    return res;
}

TRKResult TRKTerminateNub(void){

    TRKTerminateSerialHandler();
    return TRKSuccess;
} 

void TRKNubWelcome(void){
    TRK_board_display("MetroTRK for GAMECUBE v0.10");
}

