#include "TRK/trk.h"

u32 gTRKDispatchTableSize;

DSError (*gTRKDispatchTable[])(MessageBuffer*) = {
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

DSError TRKInitializeDispatcher() {
    gTRKDispatchTableSize = 32;
    return DS_NoError;
}

DSError  TRKDispatchMessage(MessageBuffer* mbuf) {

    u8 buf;
    s16 val;
    DSError res = DS_DispatchError;

    TRKSetBufferPosition(mbuf, 0);
    TRKReadBuffer1_ui8(mbuf, &buf);
    val = buf;
    if ((val & 0xFF) < gTRKDispatchTableSize) {
        res = gTRKDispatchTable[buf](mbuf);
    }
    return res;
}
