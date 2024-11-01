#include "dolphin/pad.h"
#include "libultra/libultra.h"
#include "libultra/controller.h"

s32 osContSetCh(u8 cont){

    if (PAD_CONTROLLER_NUM >= cont){
        __osMaxControllers = cont;
    }
    else {
     __osMaxControllers = PAD_CONTROLLER_NUM;
    }
    return 0;
}