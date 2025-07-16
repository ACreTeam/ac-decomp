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

    if (gthread != cthread) {
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

    if ((val == 2) && (DVDCheckDisk() == 0)) {
        OSReport("蓋空き。ホットリセットします。\n");
        val = 0;
    }

    if (APPNMI_HOTRESET_GET()) {
        OSResetSystem(OS_RESET_RESTART, 0, FALSE);
        return;
    }
    switch (val) {
        case OS_RESET_RESTART:
            OSResetSystem(OS_RESET_HOTRESET, osAppNMIBuffer[15], FALSE);
            break;
        case OS_RESET_HOTRESET:
            HotResetIplMenu();
            break;
        case OS_RESET_SHUTDOWN:
            bcopy(osAppNMIBuffer, NMISaveArea, sizeof(osAppNMIBuffer));
            OSResetSystem(OS_RESET_RESTART, 0x80000000, FALSE);
            break;
    }
}
