#ifndef LIBULTRA_OS_THREAD_H
#define LIBULTRA_OS_THREAD_H

#include "libultra/osThread.h"
#include "types.h"
#include "dolphin/os/OSThread.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void osCreateThread2(OSThread* t, OSId id, void(*entry)(void*), void* arg, void* stack_pointer, size_t stack_size, OSPriority priority);
extern void osStartThread(OSThread* t);
extern void osDestroyThread(OSThread* t);

#ifdef __cplusplus
}
#endif

#endif
