#include "libultra/libultra.h"
#include "libultra/contreaddata.h"
#include "libultra/controller.h"
#include "libultra/timerintr.h"
#include "types.h"

u8 __osInitialized = FALSE;
int osShutdown = FALSE;
OSTime __osShutdownTime;
int __osDisableShutdownLevel;
OSTime __osDisableShutdownTime;
u32 __osShutdown;
int __osShutdownDisable;
u32 __osFinalrom = TRUE;

void __osInitialize_common(void){
    
    __osFinalrom = TRUE;
    osShutdown = FALSE;
    __osShutdownDisable = FALSE;
    __osShutdown = FALSE;
    __osResetKeyStep = 0;
    __osResetSwitchPressed = FALSE;
    
    if(__osInitialized == FALSE){
        __osTimerServicesInit();
        __osContinitialized = FALSE;
        __osInitialized = TRUE;
    }
}

BOOL osIsDisableShutdown(void) {

    return __osDisableShutdownLevel != FALSE;
}

BOOL osIsEnableShutdown(void){
    u32 lev;

    return lev = __osDisableShutdownLevel == FALSE; 
}

OSTime osGetDisableShutdownTime(void){

    return __osDisableShutdownTime;
}
