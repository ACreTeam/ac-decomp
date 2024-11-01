#include "libultra/libultra.h"

void osSetThreadPri(OSThread* t, OSPri pri){
    OSPri prio = (0x1f - pri);

    if(t == NULL){
        t = OSGetCurrentThread();
    }

    OSSetThreadPriority(t, prio);
}
