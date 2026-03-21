/* GX initialisation and lifecycle. Stage 1: stubs. */
#include "gx_state.h"
#include <dolphin/gx.h>
#include <string.h>

/* Global GX state singleton */
static GXState s_gx;
GXState& gx_state(void) { return s_gx; }

void GXState::reset() {
    memset(this, 0, sizeof(*this));
    numTevStages = 1;
    numTexGens   = 1;
    numChans     = 1;
    colorUpdate  = TRUE;
    alphaUpdate  = TRUE;
    cullMode     = GX_CULL_BACK;
    scissorW     = 640;
    scissorH     = 480;
}

extern "C" {

static uint8_t s_dummy_fifo_buf[256];
static GXFifoObj s_dummy_fifo;

GXFifoObj* GXInit(void* base, u32 size) {
    (void)base; (void)size;
    gx_state().reset();
    /* TODO Stage 3: initialise Metal device/command queue here */
    return &s_dummy_fifo;
}

void GXFlush(void)          { /* TODO Stage 3: commit Metal command buffer */ }
void GXAbortFrame(void)     { /* TODO Stage 3: discard pending draws */ }
void GXDrawDone(void)       { /* TODO Stage 3: wait for GPU */ }
void GXWaitDrawDone(void)   { /* TODO Stage 3: wait for GPU */ }
void GXSetDrawDone(void)    { /* TODO Stage 3: signal draw-done */ }

BOOL IsWriteGatherBufferEmpty(void) { return TRUE; }

void GXSetMisc(GXMiscToken token, u32 val) { (void)token; (void)val; }

void GXSetVerifyLevel(GXWarningLevel l) { (void)l; }
GXVerifyCallback GXSetVerifyCallback(GXVerifyCallback cb) { (void)cb; return nullptr; }
void GXReadXfRasMetric(u32* a, u32* b, u32* c, u32* d) {
    if (a) *a = 0; if (b) *b = 0; if (c) *c = 0; if (d) *d = 0;
}

void GXSetPixelFmt(GXPixelFmt pfmt, GXZFmt16 zfmt) { (void)pfmt; (void)zfmt; }
void GXSetNumTexGens(u8 n)  { gx_state().numTexGens = n; }
void GXSetNumTevStages(u8 n){ gx_state().numTevStages = n; }
void GXSetNumChans(u8 n)    { gx_state().numChans = n; }

void GXSetTexCoordGen2(GXTexCoordID dst, GXTexGenType type, GXTexGenSrc src,
                       u32 mtx, GXBool normalize, u32 postMtx) {
    (void)dst; (void)type; (void)src; (void)mtx; (void)normalize; (void)postMtx;
}

/* Render mode globals — NTSC 480i */
GXRenderModeObj GXNtsc480IntDf = {
    VI_TVMODE_NTSC_INT, 640, 480, 480,
    40, 16, 640, 480,
    VI_XFBMODE_DF, FALSE, FALSE,
    { {6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6},{6,6} },
    { 8, 8, 10, 12, 10, 8, 8 }
};
GXRenderModeObj GXNtsc480Int      = GXNtsc480IntDf;
GXRenderModeObj GXMpal480IntDf    = GXNtsc480IntDf;
GXRenderModeObj GXPal528IntDf     = GXNtsc480IntDf;
GXRenderModeObj GXEurgb60Hz480IntDf = GXNtsc480IntDf;

} /* extern "C" */
