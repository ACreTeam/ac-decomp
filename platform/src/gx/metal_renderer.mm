/* Metal renderer: MTLDevice, MTLCommandQueue, pipeline state management.
 * Stage 1: skeleton only — Metal device created, no actual rendering.
 * Stage 3: wire up to GXCopyDisp and vi_window for a black-screen present. */
#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>
#include "platform/platform.h"

static id<MTLDevice>       g_device       = nil;
static id<MTLCommandQueue> g_cmdQueue     = nil;
static CAMetalLayer*       g_metalLayer   = nil;

extern "C" {

void plat_metal_init(void* layer_ptr) {
    /* layer_ptr is a CAMetalLayer* cast through void* */
    g_metalLayer = (__bridge CAMetalLayer*)layer_ptr;
    g_device     = MTLCreateSystemDefaultDevice();
    if (!g_device) {
        fprintf(stderr, "[Metal] No Metal device available\n");
        return;
    }
    g_metalLayer.device = g_device;
    g_metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    g_metalLayer.displaySyncEnabled = YES;  /* VSync */
    g_cmdQueue = [g_device newCommandQueue];
    fprintf(stderr, "[Metal] Initialised: %s\n",
            [g_device.name UTF8String]);
}

/* Called by GXCopyDisp each frame — Stage 3 fills this in. */
void plat_metal_present_frame(void) {
    if (!g_cmdQueue) return;
    id<CAMetalDrawable> drawable = [g_metalLayer nextDrawable];
    if (!drawable) return;

    MTLRenderPassDescriptor* rpd = [MTLRenderPassDescriptor new];
    rpd.colorAttachments[0].texture     = drawable.texture;
    rpd.colorAttachments[0].loadAction  = MTLLoadActionClear;
    rpd.colorAttachments[0].storeAction = MTLStoreActionStore;
    rpd.colorAttachments[0].clearColor  = MTLClearColorMake(0, 0, 0, 1);

    id<MTLCommandBuffer> cmd = [g_cmdQueue commandBuffer];
    id<MTLRenderCommandEncoder> enc =
        [cmd renderCommandEncoderWithDescriptor:rpd];
    [enc endEncoding];
    [cmd presentDrawable:drawable];
    [cmd commit];
}

void* plat_metal_get_device(void)    { return (__bridge void*)g_device; }
void* plat_metal_get_cmdqueue(void)  { return (__bridge void*)g_cmdQueue; }

} /* extern "C" */
