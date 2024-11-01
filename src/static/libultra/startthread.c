#include "libultra/libultra.h"

void osStartThread(OSThread* t){
    if(t == NULL){
        t = OSGetCurrentThread();
    }

    OSResumeThread(t);
}
