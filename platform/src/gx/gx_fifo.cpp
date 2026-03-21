/* GX FIFO stubs: no hardware FIFO on arm64. */
#include "platform/platform.h"
#include <dolphin/gx.h>

extern "C" {

void GXInitFifoBase(GXFifoObj* fifo, void* base, u32 size) {
    (void)fifo; (void)base; (void)size;
}
void GXInitFifoPtrs(GXFifoObj* fifo, void* rd, void* wr) {
    (void)fifo; (void)rd; (void)wr;
}
void GXInitFifoLimits(GXFifoObj* fifo, u32 hi, u32 lo) {
    (void)fifo; (void)hi; (void)lo;
}
void GXSetCPUFifo(GXFifoObj* fifo) { (void)fifo; }
void GXSetGPFifo(GXFifoObj* fifo)  { (void)fifo; }
void GXGetFifoStatus(GXFifoObj* fifo, GXBool* overhi, GXBool* underlow,
                     u32* fifoCount, GXBool* cpu_write, GXBool* gp_read,
                     GXBool* fifowrap) {
    (void)fifo;
    if (overhi)     *overhi     = FALSE;
    if (underlow)   *underlow   = FALSE;
    if (fifoCount)  *fifoCount  = 0;
    if (cpu_write)  *cpu_write  = FALSE;
    if (gp_read)    *gp_read    = FALSE;
    if (fifowrap)   *fifowrap   = FALSE;
}
void GXGetGPStatus(GXBool* overhi, GXBool* underlow, GXBool* readIdle,
                   GXBool* cmdIdle, GXBool* brkpt) {
    if (overhi)    *overhi    = FALSE;
    if (underlow)  *underlow  = FALSE;
    if (readIdle)  *readIdle  = TRUE;
    if (cmdIdle)   *cmdIdle   = TRUE;
    if (brkpt)     *brkpt     = FALSE;
}
void GXEnableBreakPt(void* addr)  { (void)addr; }
void GXDisableBreakPt(void)       {}
void GXSaveCPUFifo(GXFifoObj* f)    { (void)f; }
GXFifoObj* GXGetCPUFifo(void)       { return nullptr; }
GXFifoObj* GXGetGPFifo(void)        { return nullptr; }

} /* extern "C" */
