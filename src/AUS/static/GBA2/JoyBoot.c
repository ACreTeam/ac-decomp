#include "GBA2/gba2.h"
#include "JSystem/JUtility/JUTGba.h"
#include "boot.h"
#include "_mem.h"
#include "dolphin/si.h"

#if VERSION == VER_GAFP01_00
#define JOY_GAME_ID_RECV "gafp"
#define JOY_GAME_ID_SEND "GAFP"
#if GAME_LANGUAGE == GAME_LANG_FR
#define JOY_LOADER_MAGIC "PSaP"
#elif GAME_LANGUAGE == GAME_LANG_DE
#define JOY_LOADER_MAGIC "PSAp"
#elif GAME_LANGUAGE == GAME_LANG_IT
#define JOY_LOADER_MAGIC "PsAP"
#elif GAME_LANGUAGE == GAME_LANG_ES
#define JOY_LOADER_MAGIC "pSAP"
#else
#define JOY_LOADER_MAGIC "PSAP"
#endif
#else
#define JOY_GAME_ID_RECV "gafu"
#define JOY_GAME_ID_SEND "GAFU"
#define JOY_LOADER_MAGIC "PSAE"
#endif

// Joy SIO command words. Device byte 1 is GC; device byte 2 is GBA.
// The island-loader-mb and island-program-mb JoybootHandler implementations
// confirm the island type, ready responses, and checksum acknowledgements.
#define JOYBUS_GC_RECEIVE_DATA 0xFFFE0102
#define JOYBUS_GC_READY_TO_RECEIVE 0xFFFE0104
#define JOYBUS_GC_QUERY_APPLICATION 0xFFFE0105
#define JOYBUS_GC_CHECKSUM_OK 0xFFFE0106
#define JOYBUS_GC_CHECKSUM_ERROR 0xFFFE0107
#define JOYBUS_GC_SCAN_DESIGN_CARD 0xFFFE0108
#define JOYBUS_GC_START_CARD_TRANSFER 0xFFFE0109
#define JOYBUS_GC_RECEIVE_CARD_DATA 0xFFFE010A
#define JOYBUS_GC_SCAN_MUSIC_CARD 0xFFFE010B
#define JOYBUS_GC_SCAN_TERMINAL_CARD 0xFFFE010C
#define JOYBUS_GBA_RECEIVE_DATA 0xFFFE0202
#define JOYBUS_GBA_READY_TO_SEND 0xFFFE0204
#define JOYBUS_GBA_DESIGN_EDITOR 0xFFFE0206
#define JOYBUS_GBA_ISLAND 0xFFFE0207
#define JOYBUS_GBA_ACK 0xFFFE0208
#define JOYBUS_GBA_CHECKSUM_ERROR 0xFFFE0209
#define JOYBUS_GBA_EAPPLI 0xFFFE020A
#define JOYBUS_GBA_EDITOR_APPLICATION 0xFFFE020B
#define JOYBUS_GBA_RECEIVE_TYPED_DATA 0xFFFE020C

// Private asynchronous transaction limits and packet framing.
// JUTGba uses -2 for a pending command; synchronous GBA_BUSY is positive.
#define JOY_COMMAND_PENDING (-2)
#define JOY_PORT_NONE (-1)
#define JOY_BOOT_TIMEOUT 1000
#define JOY_TYPE_TIMEOUT 30
#define JOY_RECEIVE_TIMEOUT 300
#define JOY_PACKET_DATA_WORDS 255
#define JOY_TRANSFER_WORD_SIZE 4
#define JOY_CHECKSUM_VALID 0xFFFFFFFF
#define JOY_BOOT_PALETTE_COLOR 3
#define JOY_BOOT_PALETTE_SPEED (-1)

enum JoyTransactionState {
    JOY_STATE_START = 0,
    JOY_STATE_CONNECTING = 1,
    JOY_STATE_TRANSFERRING = 2,
};

enum JoyConnectionStage {
    JOY_CONNECT_RESET = 0,
    JOY_CONNECT_READ_ID = 1,
    JOY_CONNECT_WRITE_ID = 2,
};

enum JoyTypeStage {
    JOY_TYPE_SEND_READY = 0,
    JOY_TYPE_COMMAND_WRITTEN = 1,
    JOY_TYPE_RECV_READY = 2,
    JOY_TYPE_RESPONSE_READ = 3,
};

enum JoyCardStage {
    JOY_CARD_COMMAND_WRITTEN = 0,
    JOY_CARD_COMMAND_STATUS = 1,
    JOY_CARD_COMMAND_RESPONSE = 2,
    JOY_CARD_START_WRITTEN = 3,
    JOY_CARD_START_STATUS = 4,
    JOY_CARD_START_RESPONSE = 5,
};

enum JoyRecvStage {
    JOY_RECV_COMMAND_WRITTEN = 0,
    JOY_RECV_COMMAND_STATUS = 1,
    JOY_RECV_COMMAND_RESPONSE = 2,
    JOY_RECV_DATA_REQUEST_WRITTEN = 3,
    JOY_RECV_DATA_STATUS = 4,
    JOY_RECV_DATA_READ = 5,
    JOY_RECV_CHECKSUM_WRITTEN = 6,
    JOY_RECV_CHECKSUM_STATUS = 7,
    JOY_RECV_RESULT_READ = 8,
};

enum JoySendStage {
    JOY_SEND_COMMAND_WRITTEN = 0,
    JOY_SEND_COMMAND_STATUS = 1,
    JOY_SEND_COMMAND_RESPONSE = 2,
    JOY_SEND_WORD_WRITTEN = 3,
    JOY_SEND_WORD_STATUS = 4,
    JOY_SEND_CHECKSUM_WRITTEN = 5,
    JOY_SEND_CHECKSUM_STATUS = 6,
    JOY_SEND_FINISH_WRITTEN = 7,
    JOY_SEND_FINISH_STATUS = 8,
    JOY_SEND_RESULT_READ = 9,
    JOY_SEND_TYPED_COMMAND_WRITTEN = 10,
    JOY_SEND_TYPED_COMMAND_STATUS = 11,
    JOY_SEND_TYPED_COMMAND_RESPONSE = 12,
    JOY_SEND_TYPE_WRITTEN = 13,
    JOY_SEND_TYPE_STATUS = 14,
    JOY_SEND_TYPED_WORD_WRITTEN = 15,
    JOY_SEND_TYPED_WORD_STATUS = 16,
    JOY_SEND_TYPED_CHECKSUM_WRITTEN = 17,
    JOY_SEND_TYPED_CHECKSUM_STATUS = 18,
    JOY_SEND_TYPED_FINISH_WRITTEN = 19,
    JOY_SEND_TYPED_FINISH_STATUS = 20,
    JOY_SEND_TYPED_RESULT_READ = 21,
};

enum JoyLoaderStage {
    JOY_LOADER_RESET = 0,
    JOY_LOADER_READ_MAGIC = 1,
    JOY_LOADER_ACK_READY = 2,
    JOY_LOADER_ACK_WRITTEN = 3,
    JOY_LOADER_SIZE_READY = 4,
    JOY_LOADER_SIZE_WRITTEN = 5,
    JOY_LOADER_ECHO_READY = 6,
    JOY_LOADER_ECHO_READ = 7,
    JOY_LOADER_DATA_READY = 8,
    JOY_LOADER_DATA_WRITTEN = 9,
};

enum JoyEappliState {
    JOY_EAPPLI_START = 0,
    JOY_EAPPLI_LOADING = 1,
    JOY_EAPPLI_CONNECT = 2,
    JOY_EAPPLI_CONNECTING = 3,
    JOY_EAPPLI_CHECKING_TYPE = 4,
};

// Australian JoyBoot transactions are advanced by the JUTGba worker callbacks.
struct JoyWork {
    /* 0x00 */ JUTGba* manager;
    /* 0x04 */ u32* data;
    /* 0x08 */ s32 size;
    /* 0x0C */ s32 attempts;
    /* 0x10 */ u32 command;
    /* 0x14 */ u32 other_type;
    /* 0x18 */ u32 checksum;
    /* 0x1C */ u32 block_checksum;
    /* 0x20 */ u32 send;
    /* 0x24 */ u32 recv;
    /* 0x28 */ u8 state;
    /* 0x29 */ u8 stage;
    /* 0x2A */ bool active;
    /* 0x2B */ s8 result;
    /* 0x2C */ u8 packets;
}; // size = 0x30

static JoyWork g_Joy_wrk;
int g_port;

static u32 mJOYSIO_ConvData(u8* data) {
    u8 conv_buf[sizeof(u32)];
    conv_buf[0] = data[3];
    conv_buf[1] = data[2];
    conv_buf[2] = data[1];
    conv_buf[3] = data[0];
    return *(u32*)conv_buf;
}
extern void mGcgba_Init() {
}
extern void mGcgba_InitVar() {
    memset(&g_Joy_wrk, 0, sizeof(JoyWork));
    g_Joy_wrk.manager = JUTGba::getManager();
    if (g_Joy_wrk.manager == NULL) {
        static u8 mGcgba_work_for_JUTGba[sizeof(JUTGba)] ATTRIBUTE_ALIGN(32);
        memset(mGcgba_work_for_JUTGba, 0, sizeof(mGcgba_work_for_JUTGba));
        SoftResetEnable = false;
        g_Joy_wrk.manager = JUTGba::create((JUTGba*)mGcgba_work_for_JUTGba);
        SoftResetEnable = true;
    }
}
extern void mGcgba_EndComm() {
    g_port = JOY_PORT_NONE;
}
extern int mGcgba_ConnectEnabled() {
    int state = GBA2_GBA_STATE_TRANSMITTING;
    int port;
    if (g_Joy_wrk.state == JOY_STATE_START) {
        for (port = 0; port < GBA_MAX_CHAN; port++) {
            g_Joy_wrk.manager->doInitProbe(port, NULL, NULL);
        }
        g_port = JOY_PORT_NONE;
        g_Joy_wrk.attempts = 0;
        g_Joy_wrk.state++;
    } else {
        int complete = true;
        g_port = JOY_PORT_NONE;
        for (port = 0; port < GBA_MAX_CHAN; port++) {
            u32 type;
            int result = g_Joy_wrk.manager->resultInitProbe(port, &type);
            if (result == GBA_READY && type == SI_GBA && g_port == JOY_PORT_NONE) {
                g_port = port;
            }
            if (result == JOY_COMMAND_PENDING) {
                complete = false;
            }
        }
        if (complete && g_port != JOY_PORT_NONE) {
            state = GBA2_GBA_STATE_SUCCESS;
            g_Joy_wrk.state = JOY_STATE_START;
        }
        if (state == GBA2_GBA_STATE_TRANSMITTING) {
            if (++g_Joy_wrk.attempts > GBA2_DEFAULT_TRIES) {
                g_port = JOY_PORT_NONE;
                state = GBA2_GBA_STATE_ERROR;
                g_Joy_wrk.state = JOY_STATE_START;
            }
        }
    }
    return state;
}
extern int mGcgba_Boot(u8* data_buf, size_t buf_size) {
    int state = GBA2_GBA_STATE_TRANSMITTING;
    if (g_Joy_wrk.state == JOY_STATE_START) {
        if (g_port > GBA_CHAN0 && g_port < GBA_MAX_CHAN) {
            g_Joy_wrk.manager->doJoyBoot(g_port, JOY_BOOT_PALETTE_COLOR, JOY_BOOT_PALETTE_SPEED, data_buf, buf_size,
                                         NULL, NULL);
            g_Joy_wrk.attempts = 0;
            g_Joy_wrk.state++;
        } else {
            state = GBA2_GBA_STATE_ERROR;
        }
    } else {
        u8 status;
        int result = g_Joy_wrk.manager->resultJoyBoot(g_port, &status);
        if (result == GBA_READY) {
            state = GBA2_GBA_STATE_SUCCESS;
            g_Joy_wrk.state = JOY_STATE_START;
        } else if (result != JOY_COMMAND_PENDING) {
            state = GBA2_GBA_STATE_ERROR;
            g_Joy_wrk.state = JOY_STATE_START;
        }
        if (state == GBA2_GBA_STATE_TRANSMITTING && ++g_Joy_wrk.attempts > JOY_BOOT_TIMEOUT) {
            state = GBA2_GBA_STATE_ERROR;
            g_Joy_wrk.state = JOY_STATE_START;
        }
    }
    return state;
}

// Reset and exchange the game identifiers before issuing commands.
static void CallBack_Connection(JUTGbaParam* param, void* arg) {
    u8 status;
    if (g_Joy_wrk.active == TRUE) {
        switch (g_Joy_wrk.stage) {
            case JOY_CONNECT_RESET: {
                if (g_Joy_wrk.manager->resultReset(g_port, &status) != GBA_READY) {
                    goto error;
                }
                g_Joy_wrk.stage++;
                g_Joy_wrk.recv = 0;
                g_Joy_wrk.manager->doRead(g_port, (u8*)&g_Joy_wrk.recv, CallBack_Connection, arg);
                return;
            }
            case JOY_CONNECT_READ_ID: {
                if (g_Joy_wrk.manager->resultRead(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (g_Joy_wrk.recv == *(u32*)JOY_GAME_ID_RECV) {
                    g_Joy_wrk.stage++;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)JOY_GAME_ID_SEND);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_Connection, arg);
                } else {
                    g_Joy_wrk.stage--;
                    g_Joy_wrk.manager->doReset(g_port, CallBack_Connection, arg);
                }
                return;
            }
            case JOY_CONNECT_WRITE_ID: {
                if (g_Joy_wrk.manager->resultWrite(g_port, &status) != GBA_READY) {
                    goto error;
                }
                g_Joy_wrk.result = GBA2_GBA_STATE_SUCCESS;
                g_Joy_wrk.active = FALSE;
                g_Joy_wrk.stage = JOY_CONNECT_RESET;
                return;
            }
        }
    }
error:
    g_Joy_wrk.result = GBA2_GBA_STATE_ERROR;
    g_Joy_wrk.active = FALSE;
    g_Joy_wrk.stage = JOY_CONNECT_RESET;
}

// Ask the GBA which application is running.
static void CallBack_TypeCheck(JUTGbaParam* param, void* arg) {
    u8 status;
    u32 data;
    if (g_Joy_wrk.active == TRUE) {
        switch (g_Joy_wrk.stage) {
            case JOY_TYPE_SEND_READY: {
                if (g_Joy_wrk.manager->resultGetStatus(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if ((status & GBA_JSTAT_RECV) == 0) {
                    g_Joy_wrk.stage++;
                    data = JOYBUS_GC_QUERY_APPLICATION;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&data);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_TypeCheck, arg);
                } else {
                    g_Joy_wrk.manager->doGetStatus(g_port, CallBack_TypeCheck, arg);
                }
                return;
            }
            case JOY_TYPE_COMMAND_WRITTEN: {
                if (g_Joy_wrk.manager->resultWrite(g_port, &status) != GBA_READY) {
                    goto error;
                }
                g_Joy_wrk.stage++;
                g_Joy_wrk.manager->doGetStatus(g_port, CallBack_TypeCheck, arg);
                return;
            }
            case JOY_TYPE_RECV_READY: {
                if (g_Joy_wrk.manager->resultGetStatus(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (status & GBA_JSTAT_SEND) {
                    g_Joy_wrk.stage++;
                    g_Joy_wrk.recv = 0;
                    g_Joy_wrk.manager->doRead(g_port, (u8*)&g_Joy_wrk.recv, CallBack_TypeCheck, arg);
                } else {
                    g_Joy_wrk.stage--;
                    data = JOYBUS_GC_QUERY_APPLICATION;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&data);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_TypeCheck, arg);
                }
                return;
            }
            case JOY_TYPE_RESPONSE_READ: {
                if (g_Joy_wrk.manager->resultRead(g_port, &status) != GBA_READY) {
                    goto error;
                }
                data = mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv);
                if (data == g_Joy_wrk.command) {
                    g_Joy_wrk.result = GBA2_GBA_STATE_SUCCESS;
                } else if (data == g_Joy_wrk.other_type) {
                    g_Joy_wrk.result = GBA2_GBA_STATE_ALREADY_EXIST;
                } else {
                    goto error;
                }
                g_Joy_wrk.active = FALSE;
                g_Joy_wrk.stage = JOY_TYPE_SEND_READY;
                return;
            }
        }
    }
error:
    g_Joy_wrk.result = GBA2_GBA_STATE_ERROR;
    g_Joy_wrk.active = FALSE;
    g_Joy_wrk.stage = JOY_TYPE_SEND_READY;
}

extern int mGcgba_IsEditor() {
    int state = GBA2_GBA_STATE_TRANSMITTING;
    switch (g_Joy_wrk.state) {
        case JOY_STATE_START: {
            if (g_port > GBA_CHAN0 && g_port < GBA_MAX_CHAN) {
                g_Joy_wrk.stage = JOY_CONNECT_RESET;
                g_Joy_wrk.active = TRUE;
                g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
                g_Joy_wrk.attempts = 0;
                g_Joy_wrk.state++;
                g_Joy_wrk.manager->doReset(g_port, CallBack_Connection, NULL);
            } else {
                state = GBA2_GBA_STATE_ERROR;
            }
            break;
        }
        case JOY_STATE_CONNECTING: {
            if (g_Joy_wrk.active == FALSE) {
                if (g_Joy_wrk.result == GBA2_GBA_STATE_SUCCESS) {
                    g_Joy_wrk.command = JOYBUS_GBA_DESIGN_EDITOR;
                    g_Joy_wrk.other_type = JOYBUS_GBA_EDITOR_APPLICATION;
                    g_Joy_wrk.stage = JOY_TYPE_SEND_READY;
                    g_Joy_wrk.active = TRUE;
                    g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
                    g_Joy_wrk.attempts = 0;
                    g_Joy_wrk.state++;
                    g_Joy_wrk.manager->doGetStatus(g_port, CallBack_TypeCheck, NULL);
                } else {
                    state = GBA2_GBA_STATE_ERROR;
                    g_Joy_wrk.state = JOY_STATE_START;
                }
            }
            break;
        }
        case JOY_STATE_TRANSFERRING: {
            if (g_Joy_wrk.active == FALSE) {
                state = g_Joy_wrk.result;
                g_Joy_wrk.state = JOY_STATE_START;
            }
            break;
        }
    }
    if (state == GBA2_GBA_STATE_TRANSMITTING && ++g_Joy_wrk.attempts > JOY_TYPE_TIMEOUT) {
        g_Joy_wrk.active = FALSE;
        state = GBA2_GBA_STATE_ERROR;
        g_Joy_wrk.state = JOY_STATE_START;
    }
    return state;
}

extern int mGcgba_IsIsland() {
    int state = GBA2_GBA_STATE_TRANSMITTING;
    switch (g_Joy_wrk.state) {
        case JOY_STATE_START: {
            if (g_port > GBA_CHAN0 && g_port < GBA_MAX_CHAN) {
                g_Joy_wrk.stage = JOY_CONNECT_RESET;
                g_Joy_wrk.active = TRUE;
                g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
                g_Joy_wrk.attempts = 0;
                g_Joy_wrk.state++;
                g_Joy_wrk.manager->doReset(g_port, CallBack_Connection, NULL);
            } else {
                state = GBA2_GBA_STATE_ERROR;
            }
            break;
        }
        case JOY_STATE_CONNECTING: {
            if (g_Joy_wrk.active == FALSE) {
                if (g_Joy_wrk.result == GBA2_GBA_STATE_SUCCESS) {
                    g_Joy_wrk.command = JOYBUS_GBA_ISLAND;
                    g_Joy_wrk.other_type = JOYBUS_GBA_DESIGN_EDITOR;
                    g_Joy_wrk.stage = JOY_TYPE_SEND_READY;
                    g_Joy_wrk.active = TRUE;
                    g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
                    g_Joy_wrk.attempts = 0;
                    g_Joy_wrk.state++;
                    g_Joy_wrk.manager->doGetStatus(g_port, CallBack_TypeCheck, NULL);
                } else {
                    state = GBA2_GBA_STATE_ERROR;
                    g_Joy_wrk.state = JOY_STATE_START;
                }
            }
            break;
        }
        case JOY_STATE_TRANSFERRING: {
            if (g_Joy_wrk.active == FALSE) {
                state = g_Joy_wrk.result;
                g_Joy_wrk.state = JOY_STATE_START;
            }
            break;
        }
    }
    if (state == GBA2_GBA_STATE_TRANSMITTING && ++g_Joy_wrk.attempts > JOY_TYPE_TIMEOUT) {
        g_Joy_wrk.active = FALSE;
        state = GBA2_GBA_STATE_ERROR;
        g_Joy_wrk.state = JOY_STATE_START;
    }
    return state;
}

static void CallBack_Recv(JUTGbaParam*, void*);

// Wait for a scanned card, then hand its data transfer to CallBack_Recv.
static void CallBack_CardScan(JUTGbaParam* param, void* arg) {
    u8 status;
    if (g_Joy_wrk.active == TRUE) {
        switch (g_Joy_wrk.stage) {
            case JOY_CARD_COMMAND_WRITTEN:
            case JOY_CARD_START_WRITTEN: {
                if (g_Joy_wrk.manager->resultWrite(g_port, &status) != GBA_READY) {
                    goto error;
                }
                g_Joy_wrk.stage++;
                g_Joy_wrk.manager->doGetStatus(g_port, CallBack_CardScan, arg);
                return;
            }
            case JOY_CARD_COMMAND_STATUS:
            case JOY_CARD_START_STATUS: {
                if (g_Joy_wrk.manager->resultGetStatus(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (status & GBA_JSTAT_SEND) {
                    g_Joy_wrk.stage++;
                    g_Joy_wrk.recv = 0;
                    g_Joy_wrk.manager->doRead(g_port, (u8*)&g_Joy_wrk.recv, CallBack_CardScan, arg);
                } else {
                    g_Joy_wrk.stage--;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&g_Joy_wrk.command);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_CardScan, arg);
                }
                return;
            }
            case JOY_CARD_COMMAND_RESPONSE: {
                if (g_Joy_wrk.manager->resultRead(g_port, &status) != GBA_READY) {
                    goto error;
                }
                u32 data = mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv);
                if (data == JOYBUS_GBA_ACK) {
                    g_Joy_wrk.stage++;
                    g_Joy_wrk.command = JOYBUS_GC_START_CARD_TRANSFER;
                } else if (data == JOYBUS_GBA_EAPPLI) {
                    g_Joy_wrk.stage = JOY_CARD_COMMAND_WRITTEN;
                } else {
                    goto error;
                }
                g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&g_Joy_wrk.command);
                g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_CardScan, arg);
                return;
            }
            case JOY_CARD_START_RESPONSE: {
                if (g_Joy_wrk.manager->resultRead(g_port, &status) != GBA_READY) {
                    goto error;
                }
                u32 data = mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv);
                if (data == JOYBUS_GBA_ACK) {
                    g_Joy_wrk.command = JOYBUS_GC_RECEIVE_CARD_DATA;
                    g_Joy_wrk.stage = JOY_RECV_COMMAND_WRITTEN;
                    g_Joy_wrk.attempts = -GBA2_READ_TRIES;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&g_Joy_wrk.command);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_Recv, NULL);
                } else if (data == JOYBUS_GBA_EAPPLI) {
                    g_Joy_wrk.stage = JOY_CARD_START_WRITTEN;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&g_Joy_wrk.command);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_CardScan, arg);
                } else {
                    goto error;
                }
                return;
            }
        }
    }
error:
    g_Joy_wrk.result = GBA2_GBA_STATE_ERROR;
    g_Joy_wrk.active = FALSE;
    g_Joy_wrk.stage = JOY_CARD_COMMAND_WRITTEN;
}

// Receive data with a checksum after every 255 data words and at completion.
static void CallBack_Recv(JUTGbaParam* param, void* arg) {
    u8 status;
    if (g_Joy_wrk.active == TRUE) {
        switch (g_Joy_wrk.stage) {
            case JOY_RECV_COMMAND_WRITTEN:
            case JOY_RECV_DATA_REQUEST_WRITTEN:
            case JOY_RECV_CHECKSUM_WRITTEN: {
                if (g_Joy_wrk.manager->resultWrite(g_port, &status) != GBA_READY) {
                    goto error;
                }
                g_Joy_wrk.stage++;
                g_Joy_wrk.manager->doGetStatus(g_port, CallBack_Recv, arg);
                return;
            }
            case JOY_RECV_COMMAND_STATUS:
            case JOY_RECV_DATA_STATUS:
            case JOY_RECV_CHECKSUM_STATUS: {
                if (g_Joy_wrk.manager->resultGetStatus(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (status & GBA_JSTAT_SEND) {
                    g_Joy_wrk.stage++;
                    g_Joy_wrk.recv = 0;
                    g_Joy_wrk.manager->doRead(g_port, (u8*)&g_Joy_wrk.recv, CallBack_Recv, arg);
                } else {
                    g_Joy_wrk.stage--;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&g_Joy_wrk.command);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_Recv, arg);
                }
                return;
            }
            case JOY_RECV_COMMAND_RESPONSE: {
                if (g_Joy_wrk.manager->resultRead(g_port, &status) != GBA_READY) {
                    goto error;
                }
                u32 data = mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv);
                if (data == JOYBUS_GBA_READY_TO_SEND) {
                    g_Joy_wrk.stage++;
                    g_Joy_wrk.checksum = 0;
                    g_Joy_wrk.block_checksum = 0;
                    g_Joy_wrk.packets = 0;
                } else {
                    g_Joy_wrk.stage = JOY_RECV_COMMAND_WRITTEN;
                }
                g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&g_Joy_wrk.command);
                g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_Recv, arg);
                return;
            }
            case JOY_RECV_DATA_READ: {
                if (g_Joy_wrk.manager->resultRead(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (g_Joy_wrk.size <= 0) {
                    g_Joy_wrk.stage++;
                    u32 data = g_Joy_wrk.checksum + mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv) == JOY_CHECKSUM_VALID
                                   ? JOYBUS_GC_CHECKSUM_OK
                                   : JOYBUS_GC_CHECKSUM_ERROR;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&data);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_Recv, arg);
                } else {
                    if (g_Joy_wrk.packets == JOY_PACKET_DATA_WORDS) {
                        if (g_Joy_wrk.block_checksum + mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv) != JOY_CHECKSUM_VALID) {
                            goto error;
                        }
                        g_Joy_wrk.block_checksum = 0;
                    } else {
                        *g_Joy_wrk.data = g_Joy_wrk.recv;
                        g_Joy_wrk.data++;
                        g_Joy_wrk.size -= JOY_TRANSFER_WORD_SIZE;
                        g_Joy_wrk.checksum += mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv);
                        g_Joy_wrk.block_checksum += mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv);
                    }
                    g_Joy_wrk.packets++;
                    g_Joy_wrk.stage--;
                    g_Joy_wrk.manager->doGetStatus(g_port, CallBack_Recv, arg);
                }
                return;
            }
            case JOY_RECV_RESULT_READ: {
                if (g_Joy_wrk.manager->resultRead(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv) == JOYBUS_GBA_ACK) {
                    g_Joy_wrk.result = GBA2_GBA_STATE_SUCCESS;
                    g_Joy_wrk.active = FALSE;
                    g_Joy_wrk.stage = JOY_RECV_COMMAND_WRITTEN;
                } else if (mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv) != JOYBUS_GBA_CHECKSUM_ERROR) {
                    g_Joy_wrk.manager->doGetStatus(g_port, CallBack_Recv, arg);
                } else {
                    goto error;
                }
                return;
            }
        }
    }
error:
    g_Joy_wrk.result = GBA2_GBA_STATE_ERROR;
    g_Joy_wrk.active = FALSE;
    g_Joy_wrk.stage = JOY_RECV_COMMAND_WRITTEN;
}

extern int mGcgba_Recv(u8* recv_bufp, size_t recv_buf_size) {
    int state = GBA2_GBA_STATE_TRANSMITTING;
    switch (g_Joy_wrk.state) {
        case JOY_STATE_START: {
            if (g_port > GBA_CHAN0 && g_port < GBA_MAX_CHAN) {
                g_Joy_wrk.stage = JOY_CONNECT_RESET;
                g_Joy_wrk.active = TRUE;
                g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
                g_Joy_wrk.attempts = 0;
                g_Joy_wrk.state++;
                g_Joy_wrk.manager->doReset(g_port, CallBack_Connection, NULL);
            } else {
                state = GBA2_GBA_STATE_ERROR;
            }
            break;
        }
        case JOY_STATE_CONNECTING: {
            if (g_Joy_wrk.active == FALSE) {
                if (g_Joy_wrk.result == GBA2_GBA_STATE_SUCCESS) {
                    g_Joy_wrk.data = (u32*)recv_bufp;
                    g_Joy_wrk.size = recv_buf_size;
                    g_Joy_wrk.command = JOYBUS_GC_RECEIVE_DATA;
                    g_Joy_wrk.stage = JOY_RECV_COMMAND_WRITTEN;
                    g_Joy_wrk.active = TRUE;
                    g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
                    g_Joy_wrk.attempts = 0;
                    g_Joy_wrk.state++;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&g_Joy_wrk.command);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_Recv, NULL);
                } else {
                    state = GBA2_GBA_STATE_ERROR;
                    g_Joy_wrk.state = JOY_STATE_START;
                }
            }
            break;
        }
        case JOY_STATE_TRANSFERRING: {
            if (g_Joy_wrk.active == FALSE) {
                state = g_Joy_wrk.result;
                g_Joy_wrk.state = JOY_STATE_START;
            }
            break;
        }
    }
    if (state == GBA2_GBA_STATE_TRANSMITTING) {
        int count = ++g_Joy_wrk.attempts;
        if (count > (g_Joy_wrk.state == JOY_STATE_START ? GBA2_DEFAULT_TRIES : JOY_RECEIVE_TIMEOUT)) {
            g_Joy_wrk.state = JOY_STATE_START;
            g_Joy_wrk.active = FALSE;
            state = GBA2_GBA_STATE_ERROR;
        }
    }
    return state;
}

extern int mGcgba_CheckRecv(u8* recv_bufp, size_t recv_buf_size) {
    return mGcgba_Recv(recv_bufp, recv_buf_size);
}

extern int mGcgba_Read(u8* read_buf, size_t read_buf_size, u8 prog_type) {
    int state = GBA2_GBA_STATE_TRANSMITTING;
    switch (g_Joy_wrk.state) {
        case JOY_STATE_START: {
            if (g_port > GBA_CHAN0 && g_port < GBA_MAX_CHAN) {
                g_Joy_wrk.stage = JOY_CONNECT_RESET;
                g_Joy_wrk.active = TRUE;
                g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
                g_Joy_wrk.attempts = 0;
                g_Joy_wrk.state++;
                g_Joy_wrk.manager->doReset(g_port, CallBack_Connection, NULL);
            } else {
                state = GBA2_GBA_STATE_ERROR;
            }
            break;
        }
        case JOY_STATE_CONNECTING: {
            if (g_Joy_wrk.active == FALSE) {
                if (g_Joy_wrk.result == GBA2_GBA_STATE_SUCCESS) {
                    g_Joy_wrk.data = (u32*)read_buf;
                    g_Joy_wrk.size = read_buf_size;
                    switch (prog_type) {
                        case GBA2_EAPPLI_TYPE_NEEDLEWORK:
                            g_Joy_wrk.command = JOYBUS_GC_SCAN_DESIGN_CARD;
                            break;
                        case GBA2_EAPPLI_TYPE_MUSICSCORE:
                            g_Joy_wrk.command = JOYBUS_GC_SCAN_MUSIC_CARD;
                            break;
                        default:
                            g_Joy_wrk.command = JOYBUS_GC_SCAN_TERMINAL_CARD;
                            break;
                    }
                    g_Joy_wrk.stage = JOY_CARD_COMMAND_WRITTEN;
                    g_Joy_wrk.active = TRUE;
                    g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
                    g_Joy_wrk.attempts = -GBA2_READ_TRIES;
                    g_Joy_wrk.state++;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&g_Joy_wrk.command);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_CardScan, NULL);
                } else {
                    state = GBA2_GBA_STATE_ERROR;
                    g_Joy_wrk.state = JOY_STATE_START;
                }
            }
            break;
        }
        case JOY_STATE_TRANSFERRING: {
            if (g_Joy_wrk.active == FALSE) {
                state = g_Joy_wrk.result;
                g_Joy_wrk.state = JOY_STATE_START;
            }
            break;
        }
    }
    if (state == GBA2_GBA_STATE_TRANSMITTING && ++g_Joy_wrk.attempts > GBA2_DEFAULT_TRIES) {
        g_Joy_wrk.active = FALSE;
        state = GBA2_GBA_STATE_ERROR;
        g_Joy_wrk.state = JOY_STATE_START;
    }
    return state;
}

// Send data and checksum words, then wait for the GBA acknowledgement.
static void CallBack_Send(JUTGbaParam* param, void* arg) {
    u8 status;
    u32 data;
    if (g_Joy_wrk.active == TRUE) {
        switch (g_Joy_wrk.stage) {
            case JOY_SEND_COMMAND_WRITTEN:
            case JOY_SEND_TYPED_COMMAND_WRITTEN: {
                if (g_Joy_wrk.manager->resultWrite(g_port, &status) != GBA_READY) {
                    goto error;
                }
                g_Joy_wrk.stage++;
                g_Joy_wrk.manager->doGetStatus(g_port, CallBack_Send, arg);
                return;
            }
            case JOY_SEND_COMMAND_STATUS: {
                if (g_Joy_wrk.manager->resultGetStatus(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (status & GBA_JSTAT_SEND) {
                    g_Joy_wrk.stage++;
                    g_Joy_wrk.recv = 0;
                    g_Joy_wrk.manager->doRead(g_port, (u8*)&g_Joy_wrk.recv, CallBack_Send, arg);
                } else {
                    g_Joy_wrk.stage--;
                    data = JOYBUS_GBA_RECEIVE_DATA;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&data);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_Send, arg);
                }
                return;
            }
            case JOY_SEND_COMMAND_RESPONSE: {
                if (g_Joy_wrk.manager->resultRead(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv) == JOYBUS_GC_READY_TO_RECEIVE) {
                    g_Joy_wrk.stage += JOY_SEND_WORD_STATUS - JOY_SEND_COMMAND_RESPONSE;
                    g_Joy_wrk.checksum = 0;
                    g_Joy_wrk.block_checksum = 0;
                    g_Joy_wrk.packets = 0;
                    g_Joy_wrk.manager->doGetStatus(g_port, CallBack_Send, arg);
                } else {
                    g_Joy_wrk.stage = JOY_SEND_COMMAND_WRITTEN;
                    data = JOYBUS_GBA_RECEIVE_DATA;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&data);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_Send, arg);
                }
                return;
            }
            case JOY_SEND_WORD_WRITTEN:
            case JOY_SEND_CHECKSUM_WRITTEN:
            case JOY_SEND_FINISH_WRITTEN:
            case JOY_SEND_TYPE_WRITTEN:
            case JOY_SEND_TYPED_WORD_WRITTEN:
            case JOY_SEND_TYPED_CHECKSUM_WRITTEN:
            case JOY_SEND_TYPED_FINISH_WRITTEN: {
                if (g_Joy_wrk.manager->resultWrite(g_port, &status) != GBA_READY) {
                    goto error;
                }
                g_Joy_wrk.stage++;
                g_Joy_wrk.manager->doGetStatus(g_port, CallBack_Send, arg);
                return;
            }
            case JOY_SEND_WORD_STATUS:
            case JOY_SEND_TYPED_WORD_STATUS: {
                if (g_Joy_wrk.manager->resultGetStatus(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if ((status & GBA_JSTAT_RECV) == 0) {
                    if (g_Joy_wrk.size <= 0) {
                        g_Joy_wrk.stage++;
                        g_Joy_wrk.send = ~g_Joy_wrk.checksum;
                    } else {
                        if (g_Joy_wrk.packets == JOY_PACKET_DATA_WORDS) {
                            g_Joy_wrk.stage--;
                            g_Joy_wrk.send = ~g_Joy_wrk.block_checksum;
                            g_Joy_wrk.block_checksum = 0;
                            g_Joy_wrk.packets++;
                        } else {
                            g_Joy_wrk.stage--;
                            g_Joy_wrk.send = *g_Joy_wrk.data;
                            g_Joy_wrk.data++;
                            g_Joy_wrk.size -= JOY_TRANSFER_WORD_SIZE;
                            g_Joy_wrk.checksum += g_Joy_wrk.send;
                            g_Joy_wrk.block_checksum += g_Joy_wrk.send;
                            g_Joy_wrk.packets++;
                        }
                    }
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_Send, arg);
                } else {
                    g_Joy_wrk.manager->doGetStatus(g_port, CallBack_Send, arg);
                }
                return;
            }
            case JOY_SEND_CHECKSUM_STATUS:
            case JOY_SEND_TYPED_CHECKSUM_STATUS: {
                if (g_Joy_wrk.manager->resultGetStatus(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if ((status & GBA_JSTAT_RECV) == 0) {
                    g_Joy_wrk.stage++;
                    data = JOYBUS_GBA_RECEIVE_DATA;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&data);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_Send, arg);
                }
                return;
            }
            case JOY_SEND_FINISH_STATUS:
            case JOY_SEND_TYPED_FINISH_STATUS: {
                if (g_Joy_wrk.manager->resultGetStatus(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (status & GBA_JSTAT_SEND) {
                    g_Joy_wrk.stage++;
                    g_Joy_wrk.recv = 0;
                    g_Joy_wrk.manager->doRead(g_port, (u8*)&g_Joy_wrk.recv, CallBack_Send, arg);
                } else {
                    g_Joy_wrk.manager->doGetStatus(g_port, CallBack_Send, arg);
                }
                return;
            }
            case JOY_SEND_RESULT_READ:
            case JOY_SEND_TYPED_RESULT_READ: {
                if (g_Joy_wrk.manager->resultRead(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv) != JOYBUS_GBA_ACK) {
                    goto error;
                }
                g_Joy_wrk.result = GBA2_GBA_STATE_SUCCESS;
                g_Joy_wrk.active = FALSE;
                g_Joy_wrk.stage = JOY_SEND_COMMAND_WRITTEN;
                return;
            }
            case JOY_SEND_TYPED_COMMAND_STATUS: {
                if (g_Joy_wrk.manager->resultGetStatus(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (status & GBA_JSTAT_SEND) {
                    g_Joy_wrk.stage++;
                    g_Joy_wrk.recv = 0;
                    g_Joy_wrk.manager->doRead(g_port, (u8*)&g_Joy_wrk.recv, CallBack_Send, arg);
                } else {
                    g_Joy_wrk.stage--;
                    data = JOYBUS_GBA_RECEIVE_TYPED_DATA;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&data);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_Send, arg);
                }
                return;
            }
            case JOY_SEND_TYPED_COMMAND_RESPONSE: {
                if (g_Joy_wrk.manager->resultRead(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv) == JOYBUS_GC_READY_TO_RECEIVE) {
                    g_Joy_wrk.stage += JOY_SEND_TYPE_STATUS - JOY_SEND_TYPED_COMMAND_RESPONSE;
                    g_Joy_wrk.checksum = 0;
                    g_Joy_wrk.block_checksum = 0;
                    g_Joy_wrk.packets = 0;
                    g_Joy_wrk.manager->doGetStatus(g_port, CallBack_Send, arg);
                } else {
                    g_Joy_wrk.stage = JOY_SEND_TYPED_COMMAND_WRITTEN;
                    data = JOYBUS_GBA_RECEIVE_TYPED_DATA;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&data);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_Send, arg);
                }
                return;
            }
            case JOY_SEND_TYPE_STATUS: {
                if (g_Joy_wrk.manager->resultGetStatus(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if ((status & GBA_JSTAT_RECV) == 0) {
                    g_Joy_wrk.stage++;
                    g_Joy_wrk.send = g_Joy_wrk.command;
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_Send, arg);
                } else {
                    g_Joy_wrk.manager->doGetStatus(g_port, CallBack_Send, arg);
                }
                return;
            }
        }
    }
error:
    g_Joy_wrk.result = GBA2_GBA_STATE_ERROR;
    g_Joy_wrk.active = FALSE;
    g_Joy_wrk.stage = JOY_SEND_COMMAND_WRITTEN;
}

extern int mGcgba_Send(u8* send_bufp, size_t send_buf_size) {
    int state = GBA2_GBA_STATE_TRANSMITTING;
    switch (g_Joy_wrk.state) {
        case JOY_STATE_START: {
            if (g_port > GBA_CHAN0 && g_port < GBA_MAX_CHAN) {
                g_Joy_wrk.stage = JOY_CONNECT_RESET;
                g_Joy_wrk.active = TRUE;
                g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
                g_Joy_wrk.attempts = 0;
                g_Joy_wrk.state++;
                g_Joy_wrk.manager->doReset(g_port, CallBack_Connection, NULL);
            } else {
                state = GBA2_GBA_STATE_ERROR;
            }
            break;
        }
        case JOY_STATE_CONNECTING: {
            if (g_Joy_wrk.active == FALSE) {
                if (g_Joy_wrk.result == GBA2_GBA_STATE_SUCCESS) {
                    g_Joy_wrk.data = (u32*)send_bufp;
                    g_Joy_wrk.size = send_buf_size;
                    g_Joy_wrk.stage = JOY_SEND_COMMAND_WRITTEN;
                    g_Joy_wrk.active = TRUE;
                    g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
                    g_Joy_wrk.attempts = -GBA2_READ_TRIES;
                    g_Joy_wrk.state++;
                    u32 data = JOYBUS_GBA_RECEIVE_DATA;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&data);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_Send, NULL);
                } else {
                    state = GBA2_GBA_STATE_ERROR;
                    g_Joy_wrk.state = JOY_STATE_START;
                }
            }
            break;
        }
        case JOY_STATE_TRANSFERRING: {
            if (g_Joy_wrk.active == FALSE) {
                state = g_Joy_wrk.result;
                g_Joy_wrk.state = JOY_STATE_START;
            }
            break;
        }
    }
    if (state == GBA2_GBA_STATE_TRANSMITTING && ++g_Joy_wrk.attempts > GBA2_DEFAULT_TRIES) {
        g_Joy_wrk.active = FALSE;
        state = GBA2_GBA_STATE_ERROR;
        g_Joy_wrk.state = JOY_STATE_START;
    }
    return state;
}

// Transfer the e-Application through its loader protocol before opening Joy SIO.
static void CallBack_SendEAppri(JUTGbaParam* param, void* arg) {
    u8 status;
    if (g_Joy_wrk.active == TRUE) {
        switch (g_Joy_wrk.stage) {
            case JOY_LOADER_RESET: {
                if (g_Joy_wrk.manager->resultReset(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if ((status & GBA_JSTAT_SEND) && (status & GBA_JSTAT_PSF1)) {
                    g_Joy_wrk.stage++;
                    g_Joy_wrk.recv = 0;
                    g_Joy_wrk.manager->doRead(g_port, (u8*)&g_Joy_wrk.recv, CallBack_SendEAppri, arg);
                } else {
                    g_Joy_wrk.manager->doReset(g_port, CallBack_SendEAppri, arg);
                }
                return;
            }
            case JOY_LOADER_READ_MAGIC: {
                if (g_Joy_wrk.manager->resultRead(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (g_Joy_wrk.recv == *(u32*)JOY_LOADER_MAGIC) {
                    g_Joy_wrk.stage++;
                    g_Joy_wrk.manager->doGetStatus(g_port, CallBack_SendEAppri, arg);
                } else {
                    g_Joy_wrk.stage--;
                    g_Joy_wrk.manager->doReset(g_port, CallBack_SendEAppri, arg);
                }
                return;
            }
            case JOY_LOADER_ACK_READY: {
                if (g_Joy_wrk.manager->resultGetStatus(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (status == GBA_JSTAT_PSF1) {
                    g_Joy_wrk.stage++;
                    g_Joy_wrk.send = *(u32*)JOY_LOADER_MAGIC;
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_SendEAppri, arg);
                } else {
                    g_Joy_wrk.manager->doGetStatus(g_port, CallBack_SendEAppri, arg);
                }
                return;
            }
            case JOY_LOADER_ACK_WRITTEN:
            case JOY_LOADER_SIZE_WRITTEN: {
                if (g_Joy_wrk.manager->resultWrite(g_port, &status) != GBA_READY) {
                    goto error;
                }
                g_Joy_wrk.stage++;
                g_Joy_wrk.manager->doGetStatus(g_port, CallBack_SendEAppri, arg);
                return;
            }
            case JOY_LOADER_SIZE_READY: {
                if (g_Joy_wrk.manager->resultGetStatus(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (status == GBA_JSTAT_FLAGS_MASK) {
                    g_Joy_wrk.stage++;
                    g_Joy_wrk.send = mJOYSIO_ConvData((u8*)&g_Joy_wrk.size);
                    g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_SendEAppri, arg);
                } else {
                    g_Joy_wrk.manager->doGetStatus(g_port, CallBack_SendEAppri, arg);
                }
                return;
            }
            case JOY_LOADER_ECHO_READY: {
                if (g_Joy_wrk.manager->resultGetStatus(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (status & GBA_JSTAT_SEND) {
                    g_Joy_wrk.stage++;
                    g_Joy_wrk.recv = 0;
                    g_Joy_wrk.manager->doRead(g_port, (u8*)&g_Joy_wrk.recv, CallBack_SendEAppri, arg);
                } else {
                    g_Joy_wrk.manager->doGetStatus(g_port, CallBack_SendEAppri, arg);
                }
                return;
            }
            case JOY_LOADER_ECHO_READ: {
                if (g_Joy_wrk.manager->resultRead(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (g_Joy_wrk.size == mJOYSIO_ConvData((u8*)&g_Joy_wrk.recv)) {
                    g_Joy_wrk.stage++;
                } else {
                    g_Joy_wrk.stage--;
                }
                g_Joy_wrk.manager->doGetStatus(g_port, CallBack_SendEAppri, arg);
                return;
            }
            case JOY_LOADER_DATA_READY: {
                if (g_Joy_wrk.manager->resultGetStatus(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if ((status & GBA_JSTAT_PSF0) && (status & GBA_JSTAT_PSF1)) {
                    if ((status & GBA_JSTAT_RECV) == 0) {
                        g_Joy_wrk.attempts = 0;
                        g_Joy_wrk.stage++;
                        g_Joy_wrk.send = *g_Joy_wrk.data;
                        g_Joy_wrk.data++;
                        g_Joy_wrk.size -= JOY_TRANSFER_WORD_SIZE;
                        g_Joy_wrk.manager->doWrite(g_port, (u8*)&g_Joy_wrk.send, CallBack_SendEAppri, arg);
                    } else {
                        g_Joy_wrk.manager->doGetStatus(g_port, CallBack_SendEAppri, arg);
                    }
                } else {
                    goto error;
                }
                return;
            }
            case JOY_LOADER_DATA_WRITTEN: {
                if (g_Joy_wrk.manager->resultWrite(g_port, &status) != GBA_READY) {
                    goto error;
                }
                if (g_Joy_wrk.size <= 0) {
                    g_Joy_wrk.result = GBA2_GBA_STATE_SUCCESS;
                    g_Joy_wrk.active = FALSE;
                    g_Joy_wrk.stage = JOY_LOADER_RESET;
                } else {
                    g_Joy_wrk.stage--;
                    g_Joy_wrk.manager->doGetStatus(g_port, CallBack_SendEAppri, arg);
                }
                return;
            }
        }
    }
error:
    g_Joy_wrk.result = GBA2_GBA_STATE_ERROR;
    g_Joy_wrk.active = FALSE;
    g_Joy_wrk.stage = JOY_LOADER_RESET;
}

extern int mGcgba_send_eAppri(u8* eappli_p, size_t eappli_size) {
    int state = GBA2_EAPPLI_TRANSMITTING;
    switch (g_Joy_wrk.state) {
        case JOY_EAPPLI_START:
            if (g_port > GBA_CHAN0 && g_port < GBA_MAX_CHAN) {
                g_Joy_wrk.data = (u32*)eappli_p;
                g_Joy_wrk.size = eappli_size;
                g_Joy_wrk.stage = JOY_LOADER_RESET;
                g_Joy_wrk.active = TRUE;
                g_Joy_wrk.result = GBA2_GBA_STATE_TRANSMITTING;
                g_Joy_wrk.attempts = 0;
                g_Joy_wrk.state++;
                g_Joy_wrk.manager->doReset(g_port, CallBack_SendEAppri, NULL);
            } else {
                state = GBA2_EAPPLI_FAILURE_NO_GBA;
            }
            break;
        case JOY_EAPPLI_LOADING:
            if (g_Joy_wrk.active == FALSE) {
                if (g_Joy_wrk.result == GBA2_GBA_STATE_SUCCESS) {
                    g_Joy_wrk.state++;
                } else {
                    state = GBA2_EAPPLI_FAILURE_NO_GBA;
                    g_Joy_wrk.state = JOY_EAPPLI_START;
                }
            }
            break;
        case JOY_EAPPLI_CONNECT:
            g_Joy_wrk.stage = JOY_CONNECT_RESET;
            g_Joy_wrk.active = TRUE;
            g_Joy_wrk.result = GBA2_GBA_STATE_ERROR;
            g_Joy_wrk.attempts = -GBA2_READ_TRIES;
            g_Joy_wrk.state++;
            g_Joy_wrk.manager->doReset(g_port, CallBack_Connection, NULL);
            break;
        case JOY_EAPPLI_CONNECTING:
            if (g_Joy_wrk.active == FALSE) {
                if (g_Joy_wrk.result == GBA2_GBA_STATE_SUCCESS) {
                    g_Joy_wrk.command = JOYBUS_GBA_EAPPLI;
                    g_Joy_wrk.stage = JOY_TYPE_SEND_READY;
                    g_Joy_wrk.active = TRUE;
                    g_Joy_wrk.result = GBA2_GBA_STATE_ERROR;
                    g_Joy_wrk.attempts = 0;
                    g_Joy_wrk.state++;
                    g_Joy_wrk.manager->doGetStatus(g_port, CallBack_TypeCheck, NULL);
                } else {
                    state = GBA2_EAPPLI_FAILURE_NO_GBA;
                    g_Joy_wrk.state = JOY_EAPPLI_START;
                }
            }
            break;
        case JOY_EAPPLI_CHECKING_TYPE:
            if (g_Joy_wrk.active == FALSE) {
                g_Joy_wrk.state = JOY_EAPPLI_START;
                if (g_Joy_wrk.result == GBA2_GBA_STATE_SUCCESS) {
                    state = GBA2_EAPPLI_SUCCESS;
                } else {
                    state = GBA2_EAPPLI_FAILURE_NO_GBA;
                }
            }
            break;
    }
    if (state == GBA2_EAPPLI_TRANSMITTING && ++g_Joy_wrk.attempts > GBA2_DEFAULT_TRIES) {
        g_Joy_wrk.active = FALSE;
        state = GBA2_EAPPLI_FAILURE_NO_GBA;
        g_Joy_wrk.state = JOY_EAPPLI_START;
    }
    return state;
}
