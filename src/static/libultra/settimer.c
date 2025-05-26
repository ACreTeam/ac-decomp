#include "libultra/libultra.h"

#include <dolphin/os.h>

static void timer_handler(OSAlarm* alarm, OSContext* context);

static void timer_handler(OSAlarm* volatile alarm, OSContext* context) {
    OSTimer* volatile timer = (OSTimer* volatile)alarm;
    BOOL enabled = OSDisableInterrupts();
    
    if ((OSTime)timer->interval != 0) {
        OSSetAlarm(&timer->alarm, (OSTime)timer->interval, timer_handler);
    } else {
        timer->next->prev = timer->prev;
        timer->prev->next = timer->next;
        timer->next = NULL;
        timer->prev = NULL;
    }
    osSendMesg(timer->mq, timer->msg, OS_MESG_NOBLOCK);
    
    OSRestoreInterrupts(enabled);
}

extern int osSetTimer(OSTimer* timer, OSTime countdown, OSTime interval, OSMessageQueue* volatile mq, volatile OSMessage msg) {
    BOOL enable = OSDisableInterrupts();
    OSTimer* head;

    countdown = countdown == 0 ? interval : countdown;
    OSCreateAlarm(&timer->alarm);
    timer->mq = (OSMessageQueue*)mq;
    timer->msg = msg;
    timer->interval = interval;
    timer->value = countdown;
    head = __osTimerList->next;
    timer->next = head;
    timer->prev = head->prev;
    head->prev->next = timer;
    head->prev = timer;

    if (countdown != 0) {
        OSSetAlarm(&timer->alarm, countdown, timer_handler);
    }

    OSRestoreInterrupts(enable);
    return 0;
}
