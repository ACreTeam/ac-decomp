#ifndef _METROTRK_TRKTYPES_H
#define _METROTRK_TRKTYPES_H

#include "dolphin/os/OSInterrupt.h"
#include "PowerPC_EABI_Support/MetroTRK/trkenum.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

/////// TRK STRUCTS AND TYPES //////
// Function types for DB communications.
typedef int (*DBCommFunc)();
typedef void (*DBCommInitFunc)(volatile u8**, __OSInterruptHandler);
typedef int (*DBCommReadFunc)(void*, u32);
typedef int (*DBCommWriteFunc)(const void*, u32);

// Message buffer ID type.
typedef int TRKBufferID;

// Nub event ID type.
typedef u32 NubEventID;

// UART Error type.
typedef int UARTError;

// Size of message buffer.
#define TRKMSGBUF_SIZE (0x800 + 0x80)

// Struct for sending and receiving messages (size 0x88C).
typedef struct TRKBuffer {
	u32 mutex;               // _00
	BOOL isInUse;            // _04
	u32 length;              // _08
	u32 position;            // _0C
	u8 data[TRKMSGBUF_SIZE]; // _10
} TRKBuffer;

// Struct for storing DB communication functions (size 0x1C).
typedef struct DBCommTable {
	DBCommInitFunc initialize_func;  // _00
	DBCommFunc init_interrupts_func; // _04
	DBCommFunc peek_func;            // _08
	DBCommReadFunc read_func;        // _0C
	DBCommWriteFunc write_func;      // _10
	DBCommFunc open_func;            // _14
	DBCommFunc close_func;           // _18
} DBCommTable;

// Struct for information on DS versions (kernel and protocol) (size 0x4)
typedef struct DSVersions {
	u8 kernelMajor;   // _00
	u8 kernelMinor;   // _01
	u8 protocolMajor; // _02
	u8 protocolMinor; // _03
} DSVersions;

// Struct for packet information (size 0x8).
typedef struct TRKPacketSeq {
	u16 _00;   // _00, unknown
	u8 _02[6]; // _02, unknown
} TRKPacketSeq;

// Struct for receiving packets from serial poll (size 0x14).
typedef struct TRKFramingState {
	TRKBufferID msgBufID; // _00
	TRKBuffer* buffer;    // _04
	u8 receiveState;      // _08
	BOOL isEscape;        // _0C
	u8 fcsType;           // _10
} TRKFramingState;

// Command reply information (size 0x40).
typedef struct CommandReply {
	u32 _00; // _00
	union {
		u8 b;
		MessageCommandID m;
	} commandID; // _04, use MessageCommandID enum
	union {
		u8 b;
		DSReplyError r;
	} replyError; // _08, use DSReplyError enum - should be enum type? check size.
	u32 _0C;      // _0C
	u8 _10[0x30]; // _10, unknown
} CommandReply;

// Nub event information (size 0xC).
typedef struct TRKEvent {
	u8 eventType;         // _00
	NubEventID eventID;   // _04
	TRKBufferID msgBufID; // _08
} TRKEvent;

// Event queue (size 0x28).
typedef struct TRKEventQueue {
	u8 _00[4];          // _00, unknown
	int count;          // _04, number of events in queue
	int next;           // _08, next event in `events` to handle (0 or 1)
	TRKEvent events[2]; // _0C
	NubEventID eventID; // _24, ID to assign next event, min 0x100
} TRKEventQueue;

// Struct for state information (size 0xB0).
typedef struct TRKState {
	u32 gpr[32];           // _00
	u32 lr;                // _80
	u32 ctr;               // _84
	u32 xer;               // _88
	u32 msr;               // _8C
	u32 dar;               // _90
	u32 dsisr;             // _94
	BOOL isStopped;        // _98
	BOOL inputActivated;   // _9C
	void* inputPendingPtr; // _A0
} TRKState;

typedef struct TRKState_PPC {
	u32 GPR[32];         // 0x0
	u32 LR;              // 0x80
	u32 CTR;             // 0x84
	u32 XER;             // 0x88
	u32 MSR;             // 0x8c
	u32 DAR;             // 0x90
	u32 DSISR;           // 0x94
	BOOL stopped;        // 0x98
	BOOL inputActivated; // 0x9c
	u8* inputPendingPtr; // 0xA0
} TRKState_PPC;

typedef struct ProcessorRestoreFlags_PPC {
	u8 TBR;
	u8 DEC;
	u8 linker_padding[0x9 - 0x2];
} ProcessorRestoreFlags_PPC;

////////////////////////////////////

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
