#ifndef OS_CONTEXT_H
#define OS_CONTEXT_H
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSContext{
	u32 gprs[32];
	u32 cr;
	u32 lr;
	u32 ctr;
	u32 xer;
	f64 fprs[32];
	u32 fpscr_tmp;
	u32 fpscr;
	u32 srr0;
	u32 srr1;
	u16 mode;
	u16 state;
	u32 gqrs[8];
	char UNK_0x1C4;
	f64 psfs[32];
} OSContext;

OSContext* OS_CURRENT_CONTEXT_PHYS AT_ADDRESS(0x800000C0);
OSContext* OS_CURRENT_CONTEXT AT_ADDRESS(0x800000D4);
OSContext* OS_CURRENT_FPU_CONTEXT AT_ADDRESS(0x800000D8);

void OSSaveFPUContext(OSContext*);
void OSSetCurrentContext(OSContext*);
OSContext* OSGetCurrentContext(void);
BOOL OSSaveContext(OSContext*);
void OSLoadContext(OSContext*);
void* OSGetStackPointer(void);
void OSClearContext(OSContext*);
void OSInitContext(register OSContext*, register u32 srr, register u32 sp);
void OSDumpContext(const OSContext*);

void __OSContextInit(void);
#ifdef __cplusplus
};
#endif
#endif
