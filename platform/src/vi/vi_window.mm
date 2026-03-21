/* VI window management: create SDL2 window with CAMetalLayer.
 * Stage 1: skeleton.  Stage 3: wire up the full Metal context. */
#if TARGET_OS_IPHONE
#  import <UIKit/UIKit.h>
#else
#  import <AppKit/AppKit.h>
#endif
#import <QuartzCore/QuartzCore.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include "platform/platform.h"

static SDL_Window* g_window = nullptr;

extern "C" void plat_vi_set_metal_layer(void* layer);

extern "C" void plat_vi_create_window(int width, int height, const char* title) {
    if (g_window) return;
    g_window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (!g_window) {
        fprintf(stderr, "[VI] SDL_CreateWindow: %s\n", SDL_GetError());
        return;
    }

#if defined(__APPLE__)
    /* Extract the CAMetalLayer from the SDL window's NSView / UIView */
    SDL_SysWMinfo wm;
    SDL_VERSION(&wm.version);
    if (SDL_GetWindowWMInfo(g_window, &wm)) {
#if TARGET_OS_IPHONE
        UIView* view = wm.info.uikit.window.rootViewController.view;
        if (![view.layer isKindOfClass:[CAMetalLayer class]]) {
            /* Replace the root layer with a CAMetalLayer */
            CAMetalLayer* ml = [CAMetalLayer layer];
            [view.layer addSublayer:ml];
            ml.frame = view.bounds;
            plat_vi_set_metal_layer((__bridge void*)ml);
        } else {
            plat_vi_set_metal_layer((__bridge void*)view.layer);
        }
#else
        /* macOS */
        NSWindow* nswin = wm.info.cocoa.window;
        NSView* view    = [nswin contentView];
        [view setWantsLayer:YES];
        CAMetalLayer* ml = [CAMetalLayer layer];
        [view setLayer:ml];
        ml.contentsScale = [nswin backingScaleFactor];
        plat_vi_set_metal_layer((__bridge void*)ml);
#endif
    }
#endif /* __APPLE__ */
}

extern "C" SDL_Window* plat_vi_get_window(void) { return g_window; }
