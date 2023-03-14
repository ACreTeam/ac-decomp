#include "libforest/osreport.h"
#include "dolphin/os/OSInterrupt.h"
#include "dolphin/os/OSThread.h"
#include "dolphin/os/OSRtc.h"
#include "dolphin/os/OSMutex.h"
#include "MSL_C/printf.h"

OSMutex print_mutex;
u8 print_mutex_initialized;
static void* __OSReport_MonopolyThread;
static s32 __OSReport_disable;


void OSReportDisable (void){
    __OSReport_disable = 1;
}

void OSReportEnable (void){
    __OSReport_disable = 0;
}

void OSVReport(const char* fmt, va_list list){

    OSThread* cur_thread;
    u32 enable;
    if(__OSReport_disable == 0){
        cur_thread = OSGetCurrentThread();
        if((cur_thread != NULL) && (cur_thread->state !=2)) {
            cur_thread = NULL;
        }
        if((__OSReport_MonopolyThread == NULL) || (__OSReport_MonopolyThread == cur_thread)){
            enable = OSDisableInterrupts();
            if(print_mutex_initialized == 0){
                OSInitMutex(&print_mutex);
                print_mutex_initialized = 1;
                printf("*** OSVReport - OSInitMutex ***");
            }
            OSRestoreInterrupts(enable);
            if(cur_thread != NULL){
                OSLockMutex(&print_mutex);
            }
            vprintf(fmt, list);
            if(cur_thread != NULL){
                OSUnlockMutex(&print_mutex);
            }
        }
    }
}

void OSReport(const char* fmt,...){
    va_list list;
    va_start(list, fmt);
    OSVReport(fmt, list);
    va_end(list);
}

void OSPanic(const char* file, u32 line, const char* fmt, ...){
    va_list list;
    u32 enable;
    OSThread* thread;
    enable = OSDisableInterrupts();
    

    va_start(list, fmt);
    vprintf(fmt, list);
    va_end(list);
    printf(" in \"%s\" on line %d.\n", file, line);

    thread = OSGetCurrentThread();

    OSSetThreadPriority(thread, 0x1f);
    OSRestoreInterrupts(enable);
    *(int*)0 = 0; //why lol
}

void OSChangeBootMode(u32 mode){
    __OSSetBootMode(mode ? 0x80 : 0);
    
    while(__OSSyncSram() == 0) { }
    
}

void OSDVDFatalError(void){
    OSReport("OSDVDFatalError called.\nExitThread.\n");
    OSExitThread(0);
}


