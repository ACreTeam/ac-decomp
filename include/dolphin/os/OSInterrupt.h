#ifndef DOLPHIN_OSINTERRUPT_H
#define DOLPHIN_OSINTERRUPT_H

#include "dolphin/os/OSContext.h"
#include "dolphin/os/OSException.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef s16 __OSInterrupt;
typedef u32 OSInterruptMask;

typedef enum OSInterruptType {
    OS_INTR_MEM_0,
    OS_INTR_MEM_1,
    OS_INTR_MEM_2,
    OS_INTR_MEM_3,
    OS_INTR_MEM_ADDRESS,
    OS_INTR_DSP_AI,
    OS_INTR_DSP_ARAM,
    OS_INTR_DSP_DSP,
    OS_INTR_AI_AI,
    OS_INTR_EXI_0_EXI,
    OS_INTR_EXI_0_TC,
    OS_INTR_EXI_0_EXT,
    OS_INTR_EXI_1_EXI,
    OS_INTR_EXI_1_TC,
    OS_INTR_EXI_1_EXT,
    OS_INTR_EXI_2_EXI,
    OS_INTR_EXI_2_TC,
    OS_INTR_PI_CP,
    OS_INTR_PI_PE_TOKEN,
    OS_INTR_PI_PE_FINISH,
    OS_INTR_PI_SI,
    OS_INTR_PI_DI,
    OS_INTR_PI_RSW,
    OS_INTR_PI_ERROR,
    OS_INTR_PI_VI,
    OS_INTR_PI_DEBUG,
    OS_INTR_PI_HSP,
    OS_INTR_PI_ACR,
    OS_INTR_28,
    OS_INTR_29,
    OS_INTR_30,
    OS_INTR_31,

    OS_INTR_MAX
} OSInterruptType;

#define OS_INTRMASK_MEM_0 (0x80000000U >> OS_INTR_MEM_0)
#define OS_INTRMASK_MEM_1 (0x80000000U >> OS_INTR_MEM_1)
#define OS_INTRMASK_MEM_2 (0x80000000U >> OS_INTR_MEM_2)
#define OS_INTRMASK_MEM_3 (0x80000000U >> OS_INTR_MEM_3)
#define OS_INTRMASK_MEM_ADDRESS (0x80000000U >> OS_INTR_MEM_ADDRESS)
#define OS_INTRMASK_DSP_AI (0x80000000U >> OS_INTR_DSP_AI)
#define OS_INTRMASK_DSP_ARAM (0x80000000U >> OS_INTR_DSP_ARAM)
#define OS_INTRMASK_DSP_DSP (0x80000000U >> OS_INTR_DSP_DSP)
#define OS_INTRMASK_AI_AI (0x80000000U >> OS_INTR_AI_AI)
#define OS_INTRMASK_EXI_0_EXI (0x80000000U >> OS_INTR_EXI_0_EXI)
#define OS_INTRMASK_EXI_0_TC (0x80000000U >> OS_INTR_EXI_0_TC)
#define OS_INTRMASK_EXI_0_EXT (0x80000000U >> OS_INTR_EXI_0_EXT)
#define OS_INTRMASK_EXI_1_EXI (0x80000000U >> OS_INTR_EXI_1_EXI)
#define OS_INTRMASK_EXI_1_TC (0x80000000U >> OS_INTR_EXI_1_TC)
#define OS_INTRMASK_EXI_1_EXT (0x80000000U >> OS_INTR_EXI_1_EXT)
#define OS_INTRMASK_EXI_2_EXI (0x80000000U >> OS_INTR_EXI_2_EXI)
#define OS_INTRMASK_EXI_2_TC (0x80000000U >> OS_INTR_EXI_2_TC)
#define OS_INTRMASK_PI_CP (0x80000000U >> OS_INTR_PI_CP)
#define OS_INTRMASK_PI_PE_TOKEN (0x80000000U >> OS_INTR_PI_PE_TOKEN)
#define OS_INTRMASK_PI_PE_FINISH (0x80000000U >> OS_INTR_PI_PE_FINISH)
#define OS_INTRMASK_PI_SI (0x80000000U >> OS_INTR_PI_SI)
#define OS_INTRMASK_PI_DI (0x80000000U >> OS_INTR_PI_DI)
#define OS_INTRMASK_PI_RSW (0x80000000U >> OS_INTR_PI_RSW)
#define OS_INTRMASK_PI_ERROR (0x80000000U >> OS_INTR_PI_ERROR)
#define OS_INTRMASK_PI_VI (0x80000000U >> OS_INTR_PI_VI)
#define OS_INTRMASK_PI_DEBUG (0x80000000U >> OS_INTR_PI_DEBUG)
#define OS_INTRMASK_PI_HSP (0x80000000U >> OS_INTR_PI_HSP)

#define OS_INTRMASK_MEM                                                        \
    (OS_INTRMASK_MEM_0 | OS_INTRMASK_MEM_1 | OS_INTRMASK_MEM_2 |               \
     OS_INTRMASK_MEM_3 | OS_INTRMASK_MEM_ADDRESS)

#define OS_INTRMASK_AI (OS_INTRMASK_AI_AI)

#define OS_INTRMASK_DSP                                                        \
    (OS_INTRMASK_DSP_AI | OS_INTRMASK_DSP_ARAM | OS_INTRMASK_DSP_DSP)

#define OS_INTRMASK_EXI_0                                                      \
    (OS_INTRMASK_EXI_0_EXI | OS_INTRMASK_EXI_0_TC | OS_INTRMASK_EXI_0_EXT)
#define OS_INTRMASK_EXI_1                                                      \
    (OS_INTRMASK_EXI_1_EXI | OS_INTRMASK_EXI_1_TC | OS_INTRMASK_EXI_1_EXT)
#define OS_INTRMASK_EXI_2 (OS_INTRMASK_EXI_2_EXI | OS_INTRMASK_EXI_2_TC)
#define OS_INTRMASK_EXI                                                        \
    (OS_INTRMASK_EXI_0_EXI | OS_INTRMASK_EXI_0_TC | OS_INTRMASK_EXI_0_EXT |    \
     OS_INTRMASK_EXI_1_EXI | OS_INTRMASK_EXI_1_TC | OS_INTRMASK_EXI_1_EXT |    \
     OS_INTRMASK_EXI_2_EXI | OS_INTRMASK_EXI_2_TC)

#define OS_INTRMASK_PI                                                         \
    (OS_INTRMASK_PI_CP | OS_INTRMASK_PI_SI | OS_INTRMASK_PI_DI |               \
     OS_INTRMASK_PI_RSW | OS_INTRMASK_PI_ERROR | OS_INTRMASK_PI_VI |           \
     OS_INTRMASK_PI_PE_TOKEN | OS_INTRMASK_PI_PE_FINISH |                      \
     OS_INTRMASK_PI_DEBUG | OS_INTRMASK_PI_HSP)

#define OS_INTRMASK_PI_PE (OS_INTRMASK_PI_PE_TOKEN | OS_INTRMASK_PI_PE_FINISH)

typedef void (*__OSInterruptHandler)(__OSInterrupt, OSContext*);

extern volatile u32 __OSLastInterruptSrr0;
extern volatile s16 __OSLastInterrupt;
extern volatile s64 __OSLastInterruptTime;

void __RAS_OSDisableInterrupts_begin(void);
void __RAS_OSDisableInterrupts_end(void);

BOOL OSDisableInterrupts(void);
BOOL OSEnableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL);

__OSInterruptHandler __OSSetInterruptHandler(__OSInterrupt, __OSInterruptHandler);
__OSInterruptHandler __OSGetInterruptHandler(__OSInterrupt);

void __OSInterruptInit(void);

u32 __OSMaskInterrupts(u32);
u32 __OSUnmaskInterrupts(u32);

u32 SetInterruptMask(OSInterruptMask mask, OSInterruptMask current);
void __OSDispatchInterrupt(__OSException exception, OSContext* context);


#ifdef __cplusplus
}
#endif

#endif
