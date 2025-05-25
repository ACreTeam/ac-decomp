#include "PowerPC_EABI_Support/MetroTRK/trk.h"

static TRKFramingState gTRKFramingState;

void* gTRKInputPendingPtr;

static inline BOOL serpoll_inline_00(TRKBuffer* buffer) {
    if (buffer->length < 2) {
        TRKStandardACK(buffer, DSMSG_ReplyNAK, DSREPLY_PacketSizeError);
        if (gTRKFramingState.msgBufID != -1) {
            TRKReleaseBuffer(gTRKFramingState.msgBufID);
            gTRKFramingState.msgBufID = -1;
        }
        gTRKFramingState.buffer = NULL;
        gTRKFramingState.receiveState = DSRECV_Wait;
        return FALSE;
    }
    buffer->position = 0;
    buffer->length--;
    return TRUE;
}

int TRKTestForPacket(void) {
    s32 var_r29;
    s32 var_r3;
    s8 sp8;
    s32 temp_r3;

    var_r29 = 0;
    var_r3 = TRKReadUARTPoll(&sp8);
    while (var_r3 == 0 && var_r29 == 0) {
        if (gTRKFramingState.receiveState != DSRECV_InFrame) {
            gTRKFramingState.isEscape = FALSE;
        }
        switch (gTRKFramingState.receiveState) {
            case DSRECV_Wait:
                if (sp8 == 0x7E) {
                    var_r29 = TRKGetFreeBuffer(&gTRKFramingState.msgBufID, &gTRKFramingState.buffer);
                    gTRKFramingState.fcsType = 0;
                    gTRKFramingState.receiveState = DSRECV_Found;
                }
                break;
            case DSRECV_Found:
                if (sp8 == 0x7E) {
                    break;
                }
                gTRKFramingState.receiveState = DSRECV_InFrame;
                /* fallthrough */
            case DSRECV_InFrame:
                if (sp8 == 0x7E) {
                    if (gTRKFramingState.isEscape) {
                        TRKStandardACK(gTRKFramingState.buffer, DSMSG_ReplyNAK, DSREPLY_EscapeError);
                        if (gTRKFramingState.msgBufID != -1) {
                            TRKReleaseBuffer(gTRKFramingState.msgBufID);
                            gTRKFramingState.msgBufID = -1;
                        }
                        gTRKFramingState.buffer = NULL;
                        gTRKFramingState.receiveState = DSRECV_Wait;
                        break;
                    }
                    if (serpoll_inline_00(gTRKFramingState.buffer)) {
                        temp_r3 = gTRKFramingState.msgBufID;
                        gTRKFramingState.msgBufID = -1;
                        gTRKFramingState.buffer = NULL;
                        gTRKFramingState.receiveState = DSRECV_Wait;
                        return temp_r3;
                    }
                    gTRKFramingState.receiveState = DSRECV_Wait;
                } else {
                    if (gTRKFramingState.isEscape) {
                        sp8 ^= 0x20;
                        gTRKFramingState.isEscape = FALSE;
                    } else if (sp8 == 0x7D) {
                        gTRKFramingState.isEscape = TRUE;
                        break;
                    }
                    var_r29 = TRKAppendBuffer1_ui8(gTRKFramingState.buffer, sp8);
                    gTRKFramingState.fcsType += sp8;
                }
                break;
            case DSRECV_FrameOverflow:
                if (sp8 == 0x7E) {
                    if (gTRKFramingState.msgBufID != -1) {
                        TRKReleaseBuffer(gTRKFramingState.msgBufID);
                        gTRKFramingState.msgBufID = -1;
                    }
                    gTRKFramingState.buffer = NULL;
                    gTRKFramingState.receiveState = DSRECV_Wait;
                }
                break;
        }
        var_r3 = TRKReadUARTPoll(&sp8);
    }
    return -1;
}

void TRKGetInput(void)
{
    TRKBuffer* msgBuffer;
    int id;
    u8 command;

    id = TRKTestForPacket();
    if (id == -1)
        return;

    msgBuffer = TRKGetBuffer(id);
    TRKSetBufferPosition(msgBuffer, 0);
    TRKReadBuffer1_ui8(msgBuffer, &command);
    if (command < DSMSG_ReplyACK) {
        TRKProcessInput(id);
    } else {
        TRKReleaseBuffer(id);
    }
}

void TRKProcessInput(int bufferIdx)
{
    TRKEvent event;

    TRKConstructEvent(&event, NUBEVENT_Request);
    gTRKFramingState.msgBufID = -1;
    event.msgBufID            = bufferIdx;
    TRKPostEvent(&event);
}

DSError TRKInitializeSerialHandler(void)
{
    gTRKFramingState.msgBufID     = -1;
    gTRKFramingState.receiveState = DSRECV_Wait;
    gTRKFramingState.isEscape     = FALSE;

    return DS_NoError;
}

DSError TRKTerminateSerialHandler(void) { return DS_NoError; }
