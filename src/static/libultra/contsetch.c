#include "dolphin/pad.h"
#include "libultra/libultra.h"
#include "libultra/controller.h"

s32 osContSetCh(u8 cont){

    if (PAD_MAX_CONTROLLERS >= cont){
        __osMaxControllers = cont;
    }
    else {
     __osMaxControllers = PAD_MAX_CONTROLLERS;
    }
    return 0;
}
