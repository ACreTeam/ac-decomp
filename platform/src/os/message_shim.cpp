/* Message queue shim: OSMessageQueue → condvar + circular buffer. */
#include "platform/platform.h"
#include <dolphin/os/OSMessage.h>
#include <dolphin/os/OSThread.h>
#include <pthread.h>
#include <string.h>
#include <map>
#include <mutex>

/* We store a pthread condvar + mutex per OSMessageQueue using a side-table.
 * The OSMessageQueue struct fields msgArray / msgCount / firstIndex /
 * usedCount are used directly; the queue's sendQueue / receiveQueue
 * pointers are repurposed to hold our pthread objects.              */

struct QueueExtra {
    pthread_mutex_t mtx;
    pthread_cond_t  not_full;
    pthread_cond_t  not_empty;
};

static std::map<OSMessageQueue*, QueueExtra*> s_extras;
static std::mutex s_extras_lock;

static QueueExtra* get_extra(OSMessageQueue* q) {
    std::lock_guard<std::mutex> lk(s_extras_lock);
    auto it = s_extras.find(q);
    if (it != s_extras.end()) return it->second;
    QueueExtra* e = new QueueExtra{};
    pthread_mutex_init(&e->mtx, nullptr);
    pthread_cond_init(&e->not_full, nullptr);
    pthread_cond_init(&e->not_empty, nullptr);
    s_extras[q] = e;
    return e;
}

extern "C" {

void OSInitMessageQueue(OSMessageQueue* q, OSMessage* msgArray, s32 msgCount) {
    memset(q, 0, sizeof(*q));
    q->msgArray   = msgArray;
    q->msgCount   = msgCount;
    q->firstIndex = 0;
    q->usedCount  = 0;
    get_extra(q); /* allocate extra up front */
}

BOOL OSSendMessage(OSMessageQueue* q, OSMessage msg, s32 flags) {
    QueueExtra* e = get_extra(q);
    pthread_mutex_lock(&e->mtx);
    if (flags == OS_MESSAGE_NOBLOCK) {
        if (q->usedCount >= q->msgCount) {
            pthread_mutex_unlock(&e->mtx);
            return FALSE;
        }
    } else {
        while (q->usedCount >= q->msgCount)
            pthread_cond_wait(&e->not_full, &e->mtx);
    }
    s32 idx = (q->firstIndex + q->usedCount) % q->msgCount;
    q->msgArray[idx] = msg;
    q->usedCount++;
    pthread_cond_signal(&e->not_empty);
    pthread_mutex_unlock(&e->mtx);
    return TRUE;
}

BOOL OSJamMessage(OSMessageQueue* q, OSMessage msg, s32 flags) {
    /* Jam: insert at front */
    QueueExtra* e = get_extra(q);
    pthread_mutex_lock(&e->mtx);
    if (flags == OS_MESSAGE_NOBLOCK && q->usedCount >= q->msgCount) {
        pthread_mutex_unlock(&e->mtx);
        return FALSE;
    }
    while (q->usedCount >= q->msgCount)
        pthread_cond_wait(&e->not_full, &e->mtx);
    q->firstIndex = (q->firstIndex - 1 + q->msgCount) % q->msgCount;
    q->msgArray[q->firstIndex] = msg;
    q->usedCount++;
    pthread_cond_signal(&e->not_empty);
    pthread_mutex_unlock(&e->mtx);
    return TRUE;
}

BOOL OSReceiveMessage(OSMessageQueue* q, OSMessage* msg, s32 flags) {
    QueueExtra* e = get_extra(q);
    pthread_mutex_lock(&e->mtx);
    if (flags == OS_MESSAGE_NOBLOCK) {
        if (q->usedCount == 0) {
            pthread_mutex_unlock(&e->mtx);
            return FALSE;
        }
    } else {
        while (q->usedCount == 0)
            pthread_cond_wait(&e->not_empty, &e->mtx);
    }
    if (msg) *msg = q->msgArray[q->firstIndex];
    q->firstIndex = (q->firstIndex + 1) % q->msgCount;
    q->usedCount--;
    pthread_cond_signal(&e->not_full);
    pthread_mutex_unlock(&e->mtx);
    return TRUE;
}

/* ---- libultra message queue wrappers ---- */
void osCreateMesgQueue(OSMessageQueue* mq, OSMessage* msg, s32 count) {
    OSInitMessageQueue(mq, msg, count);
}

s32 osSendMesg(OSMessageQueue* mq, OSMessage m, s32 flags) {
    return OSSendMessage(mq, m, flags) ? 0 : -1;
}

s32 osRecvMesg(OSMessageQueue* mq, OSMessage* m, s32 flags) {
    return OSReceiveMessage(mq, m, flags) ? 0 : -1;
}

} /* extern "C" */
