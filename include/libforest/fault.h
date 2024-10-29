#ifndef FAULT_H
#define FAULT_H
#include "types.h"
#include "dolphin/os/OSInterrupt.h"
#include "libultra/libultra.h"


#ifdef __cplusplus
extern "C"{
#endif

#define FAULT_MIN_PRIORITY 0

#define FAULT_STAGE_POST 0
#define FAULT_STAGE_PRE 1

#define FAULT_FLAG_POSTEXCEPTION (1 << FAULT_STAGE_POST)
#define FAULT_FLAG_PREEXCEPTION (1 << FAULT_STAGE_PRE)

#define FAULT_FLAG_SKIP_DRAW_SEPARATOR (1 << 2)
#define FAULT_FLAG_SKIP_DRAW_CALLBACK_INFO (1 << 3)

#define FAULT_PAD_READ_SUCCESS 0
#define FAULT_PAD_READ_FAILED -1

typedef void (*FaultCallback)(const char* msg, u32 param);
typedef struct fault_client_s fault_client;

struct fault_client_s { 
	fault_client* next;
	FaultCallback callback;
	const char* msg;
	u32 param;
	u8 priority;
	u8 flags;
};

typedef struct {
	u8 _0, _1, _2, _3;
	u8 num_clients;
	fault_client* first_client;
} fault;


extern void fault_AddClientEx(fault_client* client, FaultCallback callback, const char* msg, u32 param, u8 priority, u8 flags);
extern void fault_AddClient(fault_client* client, FaultCallback callback, const char* msg, u32 param);
extern void fault_Printf(const char* msg, ...);
static void fault_DrawUpdate();
extern void fault_WaitTime(u32 waitTime);
extern int fault_ReadPad(u32* outTriggers, u32* outButtons);
static void fault_CallBackFunc(int stage);

extern void fault_Init();
static void my_PreExceptionCallback();
static void my_PostExceptionCallback();
#ifdef __cplusplus
}
#endif
#endif
