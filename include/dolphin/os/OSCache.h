#ifndef OS_CACHE_H
#define OS_CACHE_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

asm void DCEnable(void);
asm void DCInvalidateRange(void*, u32);
asm void DCFlushRange(void*, u32);
asm void DCStoreRange(void*, u32);
asm void DCFlushRangeNoSync(void*, u32);
asm void DCStoreRangeNoSync(void*, u32);
asm void DCZeroRange(void*, u32);
asm void DCTouchRange(void*, u32 len);
asm void ICInvalidateRange(void*, u32);
asm void ICFlashInvalidate(void);
asm void ICEnable(void);
asm void LCDisable(void);

//void L2GlobalInvalidate(void);

//void DMAErrorHandler(u8, struct OSContext*, u32, u32, ...);

//void __OSCacheInit(void);

#ifdef __cplusplus
}
#endif
#endif
