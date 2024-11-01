#include "libultra/libultra.h"

OSTime __osTimeOffset;

OSTime osGetTime(void){

    OSTime val = OSGetTime();

    return __osTimeOffset + val;
}
