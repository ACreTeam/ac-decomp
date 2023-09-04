#ifndef _DOLPHIN_GXFIFO
#define _DOLPHIN_GXFIFO

#include <dolphin/gx/GXEnum.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  u8 pad[128];
} GXFifoObj;

typedef void (*GXBreakPtCallback)(void);

void GXInitFifoBase(GXFifoObj* fifo, void* base, u32 size);
void GXInitFifoPtrs(GXFifoObj* fifo, void* readPtr, void* writePtr);
void GXGetFifoPtrs(GXFifoObj* fifo, void** readPtr, void** writePtr);
GXFifoObj* GXGetCPUFifo(void);
GXFifoObj* GXGetGPFifo(void);
void GXSetCPUFifo(GXFifoObj* fifo);
void GXSetGPFifo(GXFifoObj* fifo);
void GXSaveCPUFifo(GXFifoObj* fifo);
void GXGetFifoStatus(GXFifoObj* fifo, GXBool* overhi, GXBool* underlow, u32* fifoCount,
                     GXBool* cpu_write, GXBool* gp_read, GXBool* fifowrap);
void GXGetGPStatus(GXBool* overhi, GXBool* underlow, GXBool* readIdle, GXBool* cmdIdle,
                   GXBool* brkpt);
void GXInitFifoLimits(GXFifoObj* fifo, u32 hiWaterMark, u32 loWaterMark);
GXBreakPtCallback GXSetBreakPtCallback(GXBreakPtCallback cb);
void GXEnableBreakPt(void* breakPt);
void GXDisableBreakPt(void);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GXFIFO
