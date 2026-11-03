#ifndef _DOLPHIN_AR
#define _DOLPHIN_AR

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AR_STACK_INDEX_ENTRY_SIZE sizeof(u32)

#define ARAM_DIR_MRAM_TO_ARAM 0x00
#define ARAM_DIR_ARAM_TO_MRAM 0x01

#define AR_CLEAR_INTERNAL_ALL 0x00
#define AR_CLEAR_INTERNAL_USER 0x01
#define AR_CLEAR_EXPANSION 0x02

typedef void (*ARCallback)(void);

ARCallback ARRegisterDMACallback(ARCallback callback);
u32 ARGetDMAStatus(void);
void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length);
u32 ARInit(u32* stack_index_addr, u32 num_entries);
u32 ARGetBaseAddress(void);
BOOL ARCheckInit(void);
void ARReset(void);
u32 ARAlloc(u32 length);
u32 ARFree(u32* length);
u32 ARGetSize(void);
u32 ARGetInternalSize(void);
void ARSetSize(void);
void ARClear(u32 flag);

void __ARClearInterrupt(void);
u16 __ARGetInterruptStatus(void);

#define ARStartDMARead(mmem, aram, len) ARStartDMA(ARAM_DIR_ARAM_TO_MRAM, mmem, aram, len)
#define ARStartDMAWrite(mmem, aram, len) ARStartDMA(ARAM_DIR_MRAM_TO_ARAM, mmem, aram, len)

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_AR