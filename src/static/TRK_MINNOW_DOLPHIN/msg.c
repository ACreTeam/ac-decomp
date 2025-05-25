#include "PowerPC_EABI_Support/MetroTRK/trk.h"

// Incorrect signature? Should be u8.
UARTError WriteUART1(s8 arg0);

DSError TRKMessageSend(TRKBuffer* msg)
{
    u8 var_r30;
    u8 var_r28;
    u8 var_r28_2;
    s32 var_r3;
    s32 i;

    var_r30 = 0;
    for (i = 0; i < msg->length; i++) {
        var_r30 = var_r30 + msg->data[i];
    }
    var_r30 = var_r30 ^ 0xFF;
    var_r3 = WriteUART1(0x7E);
    if (var_r3 == 0) {
        for (i = 0; i < msg->length; i++) {
            var_r28 = msg->data[i];
            if (var_r28 == 0x7E || var_r28 == 0x7D) {
                var_r3 = WriteUART1(0x7D);
                var_r28 ^= 0x20;
                if (var_r3 != 0) {
                    break;
                }
            }
            var_r3 = WriteUART1(var_r28);
            if (var_r3 != 0) {
                break;
            }
        }
    }
    if (var_r3 == 0) {
        var_r28_2 = var_r30;
        for (i = 0; i < 1; i++) {
            if (var_r28_2 == 0x7E || var_r28_2 == 0x7D) {
                var_r3 = WriteUART1(0x7D);
                var_r28_2 ^= 0x20;
                if (var_r3 != 0) {
                    break;
                }
            }
            var_r3 = WriteUART1(var_r28_2);
            if (var_r3 != 0) {
                break;
            }
        }
    }
    if (var_r3 == 0) {
        var_r3 = WriteUART1(0x7E);
    }
    if (var_r3 == 0) {
        var_r3 = WriteUARTFlush();
    }
    return var_r3;
}
