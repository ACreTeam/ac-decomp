#include "dolphin/os/OSThread.h"
#include "libultra/libultra.h"


OSId osGetThreadId(OSThread* t){
    if(t == NULL){
        t = OSGetCurrentThread();
    }

    return 0;
}