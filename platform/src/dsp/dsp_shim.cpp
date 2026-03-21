/* DSP shim: the GC DSP hardware is entirely stubbed.
 * The game's audio uses software ADPCM decode in the AI DMA callback. */
#include "platform/platform.h"
#include <dolphin/dsp.h>
#include <dolphin/ar.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

extern "C" {

void DSPInit(void) {}
void DSPReset(void) {}
void DSPHalt(void)  {}

DSPTaskInfo* DSPAddTask(DSPTaskInfo* task) {
    /* On GC, DSPAddTask queues a task on the DSP.
     * Here we immediately invoke the init callback so the game's audio
     * system can set up its state. */
    if (task && task->init_cb)
        task->init_cb(task);
    return task;
}

DSPTaskInfo* DSPCancelTask(DSPTaskInfo* task) { return task; }
DSPTaskInfo* DSPAssertTask(DSPTaskInfo* task)  { return task; }

void __DSP_exec_task(DSPTaskInfo* a, DSPTaskInfo* b) { (void)a; (void)b; }
void __DSP_boot_task(DSPTaskInfo* t)  { (void)t; }
void __DSP_add_task(DSPTaskInfo* t)   { (void)t; }
void __DSP_remove_task(DSPTaskInfo* t){ (void)t; }
void __DSP_debug_printf(const char* fmt, ...) {
    va_list ap; va_start(ap, fmt); vfprintf(stderr, fmt, ap); va_end(ap);
}

u32 DSPGetDMAStatus(void)  { return 0; }
u16 DSPGetMailFrom(void)   { return 0; }
u16 DSPCheckMailFrom(void) { return 0; }
void DSPSendMailTo(u16 mail) { (void)mail; }
BOOL DSPCheckMailTo(void)    { return TRUE; }

/* AR (ARAM) stubs: we back ARAM with a malloc'd buffer */
static uint8_t* s_aram_buf = nullptr;
static uint32_t s_aram_size = 16 * 1024 * 1024; /* 16 MB */

u32 ARInit(u32* stack_index_addr, u32 num_entries) {
    (void)stack_index_addr; (void)num_entries;
    if (!s_aram_buf) s_aram_buf = (uint8_t*)calloc(1, s_aram_size);
    return 0;
}

void ARQInit(void)  {}
void ARQReset(void) {}

u32 ARGetBaseAddress(void) { return 0; }
u32 ARGetSize(void)        { return s_aram_size; }
u32 ARAlloc(u32 size)      { return 0; /* TODO: real allocator */ }
u32 ARFree(u32* length)    { (void)length; return 0; }
BOOL ARCheckInit(void)     { return s_aram_buf != nullptr ? TRUE : FALSE; }
void ARReset(void)         {}

void ARQPostRequest(ARQRequest* req, u32 owner, u32 type,
                    u32 priority, u32 source, u32 dest, u32 length,
                    ARQCallback callback) {
    (void)req; (void)owner; (void)priority;
    /* Simple synchronous copy between main RAM and ARAM buffer */
    if (type == 0 && s_aram_buf) { /* MAIN → ARAM */
        if (dest + length <= s_aram_size)
            memcpy(s_aram_buf + dest, (void*)(uintptr_t)source, length);
    } else if (s_aram_buf) { /* ARAM → MAIN */
        if (source + length <= s_aram_size)
            memcpy((void*)(uintptr_t)dest, s_aram_buf + source, length);
    }
    if (callback) callback((u32)(uintptr_t)req);
}

void ARQRemoveOwner(u32 owner)        { (void)owner; }
u32 ARQGetChunkSize(void)             { return 0x4000; }
u32 ARCheckFragmentation(u32* a, u32 b){ (void)a; (void)b; return 0; }
u32 ARFreeBlocks(u32 blockSize)       { return s_aram_size / blockSize; }

} /* extern "C" */
