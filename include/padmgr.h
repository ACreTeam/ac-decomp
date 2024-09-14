#ifndef PADMGR_H
#define PADMGR_H

#include "types.h"
#include "irqmgr.h"
#include "libu64/pad.h"
#include "dolphin/os/OSMessage.h"
#include "libultra/osThread.h"
#include "libu64/pad.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PADMSGBUFCNT 8

#define PADMGR_FLAG_HANDLE_RETRACE (1 << 0)
#define PADMGR_FLAG_HANDLE_PRENMI (1 << 1)
#define PADMGR_FLAG_DONE (1 << 2)

enum pads {
    PAD0,
    PAD1,
    PAD2,
    PAD3,

    PAD_NUM
};

enum {
    PADMGR_PAK_NONE,
    PADMGR_PAK_RUMBLE,
    PADMGR_PAK_CONTROLLER,
    PADMGR_PAK_UNK,

    PADMGR_PAK_NUM
};

enum {
    PADMGR_TYPE_NONE,
    PADMGR_TYPE_CONTROLLER,
    PADMGR_TYPE_2,
    PADMGR_TYPE_MOUSE,
    PADMGR_TYPE_VOICE_UNINTIALIZED,
    PADMGR_TYPE_VOICE_INITIALIZED,

    PADMGR_TYPE_UNK = 255
};

typedef struct {
    u8 last_command; // PAD_MOTOR_*
    u8 now_command;  // PAD_MOTOR_*
    u8 frames;
    u8 _pad;
} Motor_t;

typedef struct {
    Motor_t motors[MAXCONTROLLERS];
    s16 cooldown_frames;
    u8 rumble_frames;
    u8 _pad0;
    u8 reset;
} Rumble_t;

typedef struct {
    /* 0x0000 */ u8 pad_pattern;
    /* 0x0004 */ void (*callback)(void*);
    /* 0x0008 */ void* callback_param;
    /* 0x000C */ void (*callback2)(void*);
    /* 0x0010 */ void* callback2_param;
    /* 0x0014 */ OSContStatus pad_status[MAXCONTROLLERS];
    /* 0x0024 */ OSMessage _msg24;
    /* 0x0028 */ OSMessage _msg28;
    /* 0x002C */ OSMessage _msgBuf2C[PADMSGBUFCNT];
    /* 0x004C */ OSMessageQueue serial_mq;
    /* 0x006C */ OSMessageQueue controller_lock_mq;
    /* 0x008C */ OSMessageQueue _msgQueue8C;
    /* 0x00AC */ irqmgr_client_t irqclient;
    /* 0x00B4 */ u32 _unk0; /* maybe additional value in irqmgr_client_t? */
    /* 0x00B8 */ OSThread thread;
    /* 0x03C8 */ pad_t pads[MAXCONTROLLERS];
    /* 0x0428 */ OSContPad cur_pads[MAXCONTROLLERS]; /* Converted from PADStatus via JUTGamePad */
    /* 0x0440 */ u8 num_controllers;
    /* 0x0441 */ u8 device_type[MAXCONTROLLERS];
    /* 0x0445 */ u8 pak_type[MAXCONTROLLERS];
    /* 0x044A */ Rumble_t rumble;
} padmgr;

extern padmgr padmgr_class;

extern int padmgr_isConnectedController(int pad);
extern void padmgr_force_stop_ON();
extern void padmgr_force_stop_OFF();
extern void padmgr_RumbleSet(int pad, int intensity);
extern void padmgr_Create(OSMessageQueue* queue, OSId id, OSPri priority, void* stack, size_t stackSize);
extern void padmgr_Init(OSMessageQueue* queue);
extern void padmgr_RequestPadData(pad_t* pad, int count);
extern void padmgr_ClearPadData(pad_t* pad);

#define padmgr_setClient(callback_proc, param) \
    do {                                       \
        padmgr* mgr = &padmgr_class;           \
        mgr->callback = callback_proc;         \
        mgr->callback_param = param;           \
    } while (0)

#define padmgr_removeClient(callback_proc, param)                                 \
    do {                                                                          \
        padmgr* mgr = &padmgr_class;                                              \
        if (mgr->callback == (callback_proc) && mgr->callback_param == (param)) { \
            mgr->callback = NULL;                                                 \
            mgr->callback_param = NULL;                                           \
        }                                                                         \
    } while (0)

#define padmgr_setClient2(callback, param) \
    do {                                   \
        padmgr* mgr = &padmgr_class;       \
        mgr->callback2 = callback;         \
        mgr->callback2_param = param;      \
    } while (0)

#define padmgr_removeClient2(callback, param)                                  \
    do {                                                                       \
        padmgr* mgr = &padmgr_class;                                           \
        if (mgr->callback2 == (callback) && mgr->callback2_param == (param)) { \
            mgr->callback2 = NULL;                                             \
            mgr->callback2_param = NULL;                                       \
        }                                                                      \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif
