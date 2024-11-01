#include "dolphin/os/OSThread.h"
#include "libultra/libultra.h"
#include "libultra/os_thread.h"

void osDestroyThread(OSThread *t){
    if(t == NULL){
        t = OSGetCurrentThread();
    }

    OSCancelThread(t);
}