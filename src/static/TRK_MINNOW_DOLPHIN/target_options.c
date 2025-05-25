#include "PowerPC_EABI_Support/MetroTRK/trk.h"

static u8 bUseSerialIO;

void SetUseSerialIO(u8 sio) {
    bUseSerialIO = sio;
}

u8 GetUseSerialIO(void) {
    return bUseSerialIO;
}
