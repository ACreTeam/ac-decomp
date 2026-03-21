/* VI (Video Interface) shim.
 * Stage 1: stubs.  Stage 3: SDL2 window + Metal layer. */
#include "platform/platform.h"
#include <dolphin/vi.h>
#include <SDL2/SDL.h>
#include <stdint.h>
#include <string.h>

static VIRetraceCallback s_pre_retrace_cb  = nullptr;
static VIRetraceCallback s_post_retrace_cb = nullptr;
static uint32_t          s_retrace_count   = 0;
static BOOL              s_blanked         = FALSE;

extern "C" void plat_metal_init(void* layer_ptr); /* metal_renderer.mm */
extern "C" void plat_metal_present_frame(void);

/* Called from vi_window.mm once the window and CAMetalLayer are ready */
extern "C" void plat_vi_set_metal_layer(void* layer) {
    plat_metal_init(layer);
}

extern "C" {

void VIInit(void) {
    /* TODO Stage 3: create SDL window + CAMetalLayer via vi_window.mm */
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
        fprintf(stderr, "[VI] SDL_Init video: %s\n", SDL_GetError());
}

void VIConfigure(const struct _GXRenderModeObj* rm) {
    (void)rm;
    /* TODO Stage 3: resize render target to match rm->fbWidth / efbHeight */
}

void VIFlush(void) {
    /* No-op: Metal present happens in GXCopyDisp */
}

void VISetBlack(BOOL black) {
    s_blanked = black;
}

void VIWaitForRetrace(void) {
    /* Stage 1: busy-sleep to ~60 FPS.
     * Stage 4: replace with CVDisplayLink / CADisplayLink semaphore. */
    SDL_Delay(16);
    s_retrace_count++;
    if (s_pre_retrace_cb)  s_pre_retrace_cb(s_retrace_count);
    plat_metal_present_frame();
    if (s_post_retrace_cb) s_post_retrace_cb(s_retrace_count);
}

u32 VIGetRetraceCount(void) { return s_retrace_count; }
u32 VIGetDTVStatus(void)    { return 0; }

VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback cb) {
    VIRetraceCallback old = s_pre_retrace_cb;
    s_pre_retrace_cb = cb;
    return old;
}

VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback cb) {
    VIRetraceCallback old = s_post_retrace_cb;
    s_post_retrace_cb = cb;
    return old;
}

void* VIGetNextFrameBuffer(void)    { return nullptr; }
void* VIGetCurrentFrameBuffer(void) { return nullptr; }
void  VISetNextFrameBuffer(void* fb){ (void)fb; }

void VISetPosition(u16 hsize, u16 left, u16 vsize, u16 top) {
    (void)hsize; (void)left; (void)vsize; (void)top;
}

} /* extern "C" */
