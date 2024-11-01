#include "dolphin/os/OSMessage.h"
#include "libultra/libultra.h"

void osCreateMesgQueue(OSMessageQueue* mq, OSMessage msg, int msgCount){
    OSInitMessageQueue(mq, msg, msgCount);
}