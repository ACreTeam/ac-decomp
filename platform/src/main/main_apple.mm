/* Apple entry point.
 * Wraps the game's main() with SDL_main so SDL2 handles UIApplicationMain
 * on iOS, and provides a standard NSApp on macOS.
 * The game's real logic starts at mainproc() in src/main.c.
 *
 * Architecture note: Cocoa requires all SDL event pumping (NSApp
 * nextEventMatchingMask) to happen on the main thread.  The game's main loop
 * blocks the calling thread in osRecvMesg, so we launch the game on a
 * dedicated background thread and leave the main thread free to run the SDL
 * event loop.
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
#include <signal.h>
#include <execinfo.h>
#include <pthread.h>

/* Forward declarations for game entry points (src/main.c) */
#include <dolphin/gx/GXFifo.h>   /* GXFifoObj */
extern "C" {
    void* HotStartEntry = nullptr;
    void* boot_copyDate = nullptr;
    typedef u32 (*EntryFunc)(void);
    void  DVDInit(void);
    void  VIInit(void);
    BOOL  PADInit(void);
    GXFifoObj* GXInit(void* base, u32 size);
    void  AIInit(u8* stack);
    void  dvderr_init(void);   /* normally called from boot.c; we call it here */
    /* ac_main_entry is src/main.c:main() renamed via -Dmain=ac_main_entry in CMake */
    void  ac_main_entry(void);
    }

extern "C" void plat_vi_create_window(int w, int h, const char* title);

#if TARGET_OS_IPHONE
static void configure_audio_session(void) {
    NSError* err = nil;
    AVAudioSession* sess = [AVAudioSession sharedInstance];
    [sess setCategory:AVAudioSessionCategoryPlayback error:&err];
    [sess setActive:YES error:&err];
    if (err) NSLog(@"[Audio] AVAudioSession error: %@", err);
}
#endif

static void crash_handler(int sig) {
    void* bt[64];
    int n = backtrace(bt, 64);
    fprintf(stderr, "\n[CRASH] Signal %d — backtrace (%d frames):\n", sig, n);
    backtrace_symbols_fd(bt, n, 2);
    signal(sig, SIG_DFL);
    raise(sig);
}

/* Game thread: runs ac_main_entry() and the hot-start entry if set. */
static void* game_thread_func(void*) {
    /* Boot the game — src/main.c:main() is renamed ac_main_entry via -Dmain=ac_main_entry. */
    ac_main_entry();

    /* If entry was set, call it (game uses an indirect function pointer) */
    if (HotStartEntry) {
        EntryFunc fn = (EntryFunc)HotStartEntry;
        fn();
    }

    /* Signal quit to the main event loop */
    SDL_Event quit;
    quit.type = SDL_QUIT;
    SDL_PushEvent(&quit);
    return nullptr;
}

/* SDL_main is the real entry point — SDL2 arranges for it to be called
 * correctly on every Apple platform. */
int main(int argc, char* argv[]) {
    signal(SIGSEGV, crash_handler);
    signal(SIGBUS,  crash_handler);
    (void)argc; (void)argv;

#if TARGET_OS_IPHONE
    configure_audio_session();
#endif

    /* Initialise SDL2 core — must happen on the main thread */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0) {
        fprintf(stderr, "[Main] SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    /* Create the game window (640×480, resizable) — must happen on main thread */
    plat_vi_create_window(640, 480, "Animal Crossing");

    /* Initialise platform subsystems in GC boot order */
    DVDInit();
    dvderr_init();   /* boot.c is excluded; init the DVD error handler manually */
    PADInit();

    /* Allocate a dummy GX FIFO and initialise the GX state machine */
    static uint8_t gx_fifo_buf[256 * 1024];
    GXInit(gx_fifo_buf, sizeof(gx_fifo_buf));

    /* Audio */
    static uint8_t ai_stack[4096];
    AIInit(ai_stack);

    /* Launch game on a background thread so the main thread stays free
     * to run the Cocoa/SDL event loop. */
    pthread_t game_thread;
    pthread_attr_t game_attr;
    pthread_attr_init(&game_attr);
    pthread_attr_setstacksize(&game_attr, 4 * 1024 * 1024);
    pthread_create(&game_thread, &game_attr, game_thread_func, nullptr);
    pthread_attr_destroy(&game_attr);

    /* Main thread: SDL event loop — Cocoa requires event pumping here.
     * SDL_WaitEvent blocks until an event arrives, keeping CPU idle. */
    SDL_Event e;
    while (SDL_WaitEvent(&e)) {
        if (e.type == SDL_QUIT) break;
        /* Input events (SDL_KEYDOWN/UP, SDL_CONTROLLERAXIS, etc.) update
         * SDL's internal state tables; PADRead polls those tables from the
         * game thread without needing explicit forwarding here. */
    }

    SDL_Quit();
    return 0;
}
