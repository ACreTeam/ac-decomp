/* Alarm shim: OSAlarm → dispatch_after (stub for Stage 1). */
#include "platform/platform.h"
#include <dolphin/os/OSAlarm.h>
#include <string.h>

extern "C" {

void OSCreateAlarm(OSAlarm* alarm) {
    if (alarm) memset(alarm, 0, sizeof(*alarm));
}

void OSSetAlarm(OSAlarm* alarm, OSTime tick, OSAlarmHandler handler) {
    (void)alarm; (void)tick; (void)handler;
    /* TODO Stage 4: implement using dispatch_after */
}

void OSSetPeriodicAlarm(OSAlarm* alarm, OSTime start, OSTime period,
                        OSAlarmHandler handler) {
    (void)alarm; (void)start; (void)period; (void)handler;
    /* TODO Stage 4 */
}

void OSCancelAlarm(OSAlarm* alarm) {
    (void)alarm;
}

} /* extern "C" */
