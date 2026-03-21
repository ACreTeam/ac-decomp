/* Apple entry point.
 * Wraps the game's main() with SDL_main so SDL2 handles UIApplicationMain
 * on iOS, and provides a standard NSApp on macOS.
 * The game's real logic starts at mainproc() in src/main.c.
 */
#import <Foundation/Foundation.h>
#if TARGET_OS_IPHONE
#  import <UIKit/UIKit.h>
#  import <AVFoundation/AVFoundation.h>
#else
#  import <Cocoa/Cocoa.h>
#endif

/* SDL2 must be included after the Apple headers on iOS to get SDL_main */
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>   /* defines: int main() → int SDL_main() */
#include "platform/platform.h"
#include <dolphin/pad.h>
#include <string.h>

/* Forward declarations for game entry points (src/main.c) */
#include <dolphin/gx/GXFifo.h>   /* GXFifoObj */
extern "C" {
    extern void* HotStartEntry;
    typedef u32 (*EntryFunc)(void);
    void  DVDInit(void);
    void  VIInit(void);
    BOOL  PADInit(void);
    GXFifoObj* GXInit(void* base, u32 size);
    void  AIInit(u8* stack);
    /* ac_main_entry is src/main.c:main() renamed via -Dmain=ac_main_entry in CMake */
    void  ac_main_entry(void);
}

extern "C" void plat_vi_create_window(int w, int h, const char* title);

static int wait_for_controller_connection(void) {
    fprintf(stderr, "[PAD] Waiting for physical controller connection...\n");
    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                return 1;
            }
        }

        PADStatus status[PAD_MAX_CONTROLLERS];
        memset(status, 0, sizeof(status));
        u32 connected = PADRead(status);
        if (connected != 0) {
            fprintf(stderr, "[PAD] Controller connected. Continuing boot.\n");
            return 0;
        }
        SDL_Delay(250);
    }
}

#if TARGET_OS_IPHONE
static void configure_audio_session(void) {
    NSError* err = nil;
    AVAudioSession* sess = [AVAudioSession sharedInstance];
    [sess setCategory:AVAudioSessionCategoryPlayback error:&err];
    [sess setActive:YES error:&err];
    if (err) NSLog(@"[Audio] AVAudioSession error: %@", err);
}
#endif

/* SDL_main is the real entry point — SDL2 arranges for it to be called
 * correctly on every Apple platform. */
int main(int argc, char* argv[]) {
    (void)argc; (void)argv;

#if TARGET_OS_IPHONE
    configure_audio_session();
#endif

    /* Initialise SDL2 core */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0) {
        fprintf(stderr, "[Main] SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    /* Create the game window (640×480, resizable) */
    plat_vi_create_window(640, 480, "Animal Crossing");

    /* Initialise platform subsystems in GC boot order */
    DVDInit();
    PADInit();
    if (wait_for_controller_connection() != 0) {
        SDL_Quit();
        return 0;
    }

    /* Allocate a dummy GX FIFO and initialise the GX state machine */
    static uint8_t gx_fifo_buf[256 * 1024];
    GXInit(gx_fifo_buf, sizeof(gx_fifo_buf));

    /* Audio */
    static uint8_t ai_stack[4096];
    AIInit(ai_stack);

    /* Boot the game — src/main.c:main() is renamed ac_main_entry via -Dmain=ac_main_entry.
     * It sets HotStartEntry = &entry, then mainproc() runs the main game loop. */
    ac_main_entry();

    /* If entry was set, call it (game uses an indirect function pointer) */
    if (HotStartEntry) {
        EntryFunc fn = (EntryFunc)HotStartEntry;
        fn();
    }

    SDL_Quit();
    return 0;
}
