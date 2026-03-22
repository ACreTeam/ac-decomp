/* Thread shim: maps GameCube OSThread / libultra threading to pthreads. */
#include "platform/platform.h"
#include <dolphin/os/OSThread.h>
#include <dolphin/os/OSMutex.h>
/* OSCond is defined in OSMutex.h */
#include <pthread.h>
#include <map>
#include <mutex>
#include <stdint.h>
#include <assert.h>

/* We store the pthread_t corresponding to each OSThread* in a side-table
 * because GCube's OSThread struct has no room for a pthread_t field. */
static std::map<OSThread*, pthread_t> s_thread_map;
static std::mutex s_thread_map_lock;
static OSThread* s_current_thread_main = nullptr; /* set for the main thread */

/* Thread-local pointer to the current OSThread */
static pthread_key_t s_current_thread_key;
static pthread_once_t s_key_once = PTHREAD_ONCE_INIT;

static void make_key(void) {
    pthread_key_create(&s_current_thread_key, nullptr);
}

extern "C" {

/* ---- OSThread ---- */

BOOL OSCreateThread(OSThread* t, void*(*func)(void*), void* param,
                    void* stack, u32 stackSize, OSPriority pri, u16 attr) {
    (void)stack; (void)stackSize;
    pthread_once(&s_key_once, make_key);
    memset(t, 0, sizeof(*t));
    t->state    = OS_THREAD_STATE_WAITING;
    t->priority = pri;
    t->attr     = attr;

    pthread_attr_t pa;
    pthread_attr_init(&pa);
    pthread_attr_setstacksize(&pa, stackSize > 16384 ? stackSize : 65536);
    pthread_attr_setdetachstate(&pa, PTHREAD_CREATE_JOINABLE);

    /* Wrap the function so we can set the TLS key */
    struct Ctx { OSThread* t; void*(*fn)(void*); void* arg; };
    Ctx* ctx = new Ctx{ t, func, param };
    auto wrapper = [](void* v) -> void* {
        Ctx* c = reinterpret_cast<Ctx*>(v);
        pthread_setspecific(s_current_thread_key, c->t);
        c->t->state = OS_THREAD_STATE_RUNNING;
        void* ret = c->fn(c->arg);
        c->t->state = OS_THREAD_STATE_MORIBUND;
        delete c;
        return ret;
    };

    pthread_t tid;
    int r = pthread_create(&tid, &pa, wrapper, ctx);
    pthread_attr_destroy(&pa);
    if (r != 0) { delete ctx; return FALSE; }

    /* Leave thread suspended until OSResumeThread is called if ATTR_DETACH not set */
    { std::lock_guard<std::mutex> lk(s_thread_map_lock);
      s_thread_map[t] = tid; }

    /* If not marked to run immediately, suspend (we use a condition in the wrapper).
     * For simplicity in Stage 1: thread starts immediately. */
    return TRUE;
}

void OSExitThread(void* val) {
    pthread_exit(val);
}

BOOL OSJoinThread(OSThread* t, void** val) {
    pthread_t tid;
    { std::lock_guard<std::mutex> lk(s_thread_map_lock);
      auto it = s_thread_map.find(t);
      if (it == s_thread_map.end()) return FALSE;
      tid = it->second; }
    return pthread_join(tid, val) == 0 ? TRUE : FALSE;
}

s32 OSResumeThread(OSThread* t) {
    t->state = OS_THREAD_STATE_RUNNING;
    return 1;
}

s32 OSSuspendThread(OSThread* t) {
    /* Cooperative suspend not yet implemented */
    (void)t;
    return 0;
}

void OSYieldThread(void) { pthread_yield_np(); }

OSThread* OSGetCurrentThread(void) {
    pthread_once(&s_key_once, make_key);
    return reinterpret_cast<OSThread*>(pthread_getspecific(s_current_thread_key));
}

void OSSleepThread(OSThreadQueue* queue) {
    /* Stub: yield — real implementation waits on a condvar */
    (void)queue;
    pthread_yield_np();
}

void OSWakeupThread(OSThreadQueue* queue) {
    (void)queue;
}

void OSInitThreadQueue(OSThreadQueue* queue) {
    if (queue) { queue->head = nullptr; queue->tail = nullptr; }
}

BOOL OSSetThreadPriority(OSThread* t, OSPriority pri) {
    if (t) t->priority = pri;
    return TRUE;
}

OSPriority OSGetThreadPriority(OSThread* t) {
    return t ? t->priority : 0;
}

void OSCancelThread(OSThread* t) {
    pthread_t tid;
    { std::lock_guard<std::mutex> lk(s_thread_map_lock);
      auto it = s_thread_map.find(t);
      if (it == s_thread_map.end()) return;
      tid = it->second;
      s_thread_map.erase(it); }
    pthread_cancel(tid);
}

/* ---- OSMutex → pthread_mutex ---- */
/* OSMutex has a 'link' field we repurpose to stash a pthread_mutex_t*.
 * The struct layout on arm64 has enough padding. */

static pthread_mutex_t* get_or_create_mutex(OSMutex* m) {
    /* Use 'link.next' (first pointer field) as storage for the pthread_mutex_t* */
    pthread_mutex_t** pp = reinterpret_cast<pthread_mutex_t**>(&m->link.next);
    if (*pp == nullptr) {
        *pp = new pthread_mutex_t;
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(*pp, &attr);
        pthread_mutexattr_destroy(&attr);
    }
    return *pp;
}

void OSInitMutex(OSMutex* m) {
    memset(m, 0, sizeof(*m));
}

void OSLockMutex(OSMutex* m) {
    pthread_mutex_lock(get_or_create_mutex(m));
}

void OSUnlockMutex(OSMutex* m) {
    pthread_mutex_unlock(get_or_create_mutex(m));
}

BOOL OSTryLockMutex(OSMutex* m) {
    return pthread_mutex_trylock(get_or_create_mutex(m)) == 0 ? TRUE : FALSE;
}

/* ---- OSCond → pthread_cond ---- */

static pthread_cond_t* get_or_create_cond(OSCond* c) {
    pthread_cond_t** pp = reinterpret_cast<pthread_cond_t**>(&c->queue.head);
    if (*pp == nullptr) {
        *pp = new pthread_cond_t;
        pthread_cond_init(*pp, nullptr);
    }
    return *pp;
}

void OSInitCond(OSCond* c) { memset(c, 0, sizeof(*c)); }

void OSWaitCond(OSCond* c, OSMutex* m) {
    pthread_cond_wait(get_or_create_cond(c), get_or_create_mutex(m));
}

void OSSignalCond(OSCond* c) {
    pthread_cond_signal(get_or_create_cond(c));
}

/* ---- libultra wrappers ---- */

void __attribute__((weak)) osCreateThread2(OSThread* t, s32 id, void(*entry)(void*), void* arg,
                     void* sp, size_t stack_size, OSPriority pri) {
    (void)id;
    OSCreateThread(t, reinterpret_cast<void*(*)(void*)>(entry), arg,
                   sp, (u32)stack_size, pri, 0);
}

void __attribute__((weak)) osStartThread(OSThread* t) {
    OSResumeThread(t);
}

void __attribute__((weak)) osDestroyThread(OSThread* t) {
    OSCancelThread(t);
}

void __attribute__((weak)) osSetThreadPri(OSThread* t, int pri) {
    if (t) t->priority = (OSPriority)pri;
}

OSThread* GXSetCurrentGXThread(void) {
    return OSGetCurrentThread();
}

} /* extern "C" */
