#include "dolphin/os/OSMessage.h"
#include "libultra/libultra.h"
#include "libultra/osMesg.h"

int osSendMesg(OSMessageQueue* mq, OSMessage msg, int flags){
    return OSSendMessage(mq, msg, flags);
}
