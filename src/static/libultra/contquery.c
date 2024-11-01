#include "libultra/libultra.h"
#include "libultra/controller.h"

s32 osContStartQuery(OSMessageQueue* mq){
    osSendMesg(mq, NULL, 0);
    
    return 0;
}

void osContGetQuery(OSContStatus *q){
    u8 pattern;

    __osContGetInitData(&pattern, q);
}
