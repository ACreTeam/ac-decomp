#include "libultra/libultra.h"
#include "libultra/osMesg.h"

int osRecvMesg(OSMessageQueue* mq, OSMessage* msg, int flags){
    return OSReceiveMessage(mq, msg, flags);
}
