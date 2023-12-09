#include "libforest/osreport.h"
#include "dolphin/os/OSInterrupt.h"
#include "dolphin/os/OSRtc.h"

#include "MSL_C/printf.h"

static BOOL __OSReport_disable;
static OSThread* __OSReport_MonopolyThread;
static u8 print_mutex_initialized;
static OSMutex print_mutex;

extern void OSReportDisable() {
    __OSReport_disable = TRUE;
}

extern void OSReportEnable() {
    __OSReport_disable = FALSE;
}

void OSVReport(const char* fmt, va_list list) {
    OSThread* cur_thread;
    u32 enable;

    if (__OSReport_disable == FALSE) {
        cur_thread = OSGetCurrentThread();
        if ((cur_thread != NULL) && (cur_thread->state != (u32)OS_THREAD_STATE_RUNNING)) {
            cur_thread = NULL;
        }
        if ((__OSReport_MonopolyThread == NULL) || (__OSReport_MonopolyThread == cur_thread)) {
            enable = OSDisableInterrupts();
            if (print_mutex_initialized == FALSE) {
                OSInitMutex(&print_mutex);
                print_mutex_initialized = TRUE;
                printf("*** OSVReport - OSInitMutex ***");
            }
            OSRestoreInterrupts(enable);
            if (cur_thread != NULL) {
                OSLockMutex(&print_mutex);
            }
            vprintf(fmt, list);
            if (cur_thread != NULL) {
                OSUnlockMutex(&print_mutex);
            }
        }
    }
}

void OSReport(const char* fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    OSVReport(fmt, arg);
    va_end(arg);
}

void OSPanic(const char* file, int line, const char* fmt, ...) {
    va_list list;
    u32 enable;
    OSThread* thread;
    enable = OSDisableInterrupts();
    

    va_start(list, fmt);
    vprintf(fmt, list);
    va_end(list);
    printf(" in \"%s\" on line %d.\n", file, line);

    thread = OSGetCurrentThread();

    OSSetThreadPriority(thread, OS_PRIORITY_IDLE);
    OSRestoreInterrupts(enable);
    OSThrow(); /* Stop processor execution forcefully */
}

extern void OSChangeBootMode(u32 mode) {
    __OSSetBootMode(mode ? OS_BOOT_MODE_RETAIL : OS_BOOT_MODE_DEBUG);
    
    while(__OSSyncSram() == FALSE) { }
}

extern void OSDVDFatalError(void) {
    OSReport("OSDVDFatalError called.\nExitThread.\n");
    OSExitThread(NULL);
}
