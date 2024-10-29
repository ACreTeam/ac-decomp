#include "TRK/dispatch.h"
#include "TRK/msghndlr.h"

u32 gTRKDispatchTableSize;

TRKResult (*gTRKDispatchTable[])(MessageBuffer*) = {
    &TRKDoUnsupported,   &TRKDoConnect,        &TRKDoDisconnect,
    &TRKDoReset,         &TRKDoVersions,       &TRKDoSupportMask,
    &TRKDoCPUType,       &TRKDoUnsupported,    &TRKDoUnsupported,
    &TRKDoUnsupported,   &TRKDoUnsupported,    &TRKDoUnsupported,
    &TRKDoUnsupported,   &TRKDoUnsupported,    &TRKDoUnsupported,
    &TRKDoUnsupported,   &TRKDoReadMemory,     &TRKDoWriteMemory,
    &TRKDoReadRegisters, &TRKDoWriteRegisters, &TRKDoUnsupported,
    &TRKDoUnsupported,   &TRKDoFlushCache,     &TRKDoSetOption,
    &TRKDoContinue,      &TRKDoStep,           &TRKDoStop,
    &TRKDoUnsupported,   &TRKDoUnsupported,    &TRKDoUnsupported,
    &TRKDoUnsupported,   &TRKDoUnsupported,    NULL,
};

TRKResult TRKInitializeDispatcher() {
    gTRKDispatchTableSize = 32;
    return TRKSuccess;
}

TRKResult TRKDispatchMessage(MessageBuffer* mbuf) {

    u8 buf;
    s16 val;
    TRKResult res = TRKError500;

    TRKSetBufferPosition(mbuf, 0);
    TRKReadBuffer1_ui8(mbuf, &buf);
    val = buf;
    if ((val & 0xFF) < gTRKDispatchTableSize) {
        res = gTRKDispatchTable[buf](mbuf);
    }
    return res;
}
