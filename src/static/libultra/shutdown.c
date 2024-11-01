#include "libultra/libultra.h"
#include "dolphin/os.h"
#include "dolphin/dvd.h"
#include "dolphin/pad.h"
#include "dolphin/gx.h"
#include "jaudio_NES/game64.h"
#include "libultra/initialize.h"
#include "libjsys/jsyswrapper.h"
#include "libultra/os_timer.h"
#include "boot.h"
#include "m_nmibuf.h"

void osShutdownStart(int val) {
    s32 dstat;
    OSThread* gthread;
    OSThread* cthread;
    u32 enable;

    OSReport("***osShutdownStart***\n");
    dstat = DVDGetDriveStatus();

    if (dstat == -1) { 
        while (TRUE) {}
    }
        osIsEnableShutdown();
        PADRecalibrate(0xF0000000);
        Na_Reset();

        gthread = GXGetCurrentGXThread();
        enable = OSDisableInterrupts();
        cthread = OSGetCurrentThread();

        if(gthread != cthread){
            OSCancelThread(gthread);
            GXSetCurrentGXThread();
        }
        GXFlush();
        GXAbortFrame();
        GXDrawDone();

        OSRestoreInterrupts(enable);
        JW_JUTXfb_clearIndex();
        VIWaitForRetrace();
        VISetBlack(TRUE);
        VIFlush();
        VIWaitForRetrace();
        osStopTimerAll();
        LCDisable();
        OSReport("リセットしてもこれだけは忘れない。 osAppNMIBuffer[15] = %08x\n", osAppNMIBuffer[15]);

        if((val == 2) && (DVDCheckDisk() == 0)){
            OSReport("蓋空き。ホットリセットします。\n");
            val = 0;
        }

    if (APPNMI_HOTRESET_GET()) {
        OSResetSystem(FALSE, 0, FALSE);
        return;
    }
    switch (val) {     
    case 0:
        OSResetSystem(TRUE,osAppNMIBuffer[15], FALSE);
        break;
    case 1:
        HotResetIplMenu();
        break;
    case 2:
        bcopy(osAppNMIBuffer, (void*)0x811FFFC0, 0x40U);
        OSResetSystem(0, 0x80000000, FALSE);
        break;;
    }
}
