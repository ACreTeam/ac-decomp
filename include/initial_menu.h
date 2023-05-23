#ifndef INITIAL_MENU_H
#define INITIAL_MENU_H

#include "types.h"
#include "PR/mbi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define INITIAL_MENU_STACK_SIZE 0x2800

#define INITIAL_MENU_LIMIT_TIME (OSMicrosecondsToTicks(10000000ull))
#define INITIAL_MENU_SELECT_WAIT_TIME (OSMicrosecondsToTicks(3000000ull))

#define INITIAL_MENU_OSMESG_INIT_DONE 0x1234
#define INITIAL_MENU_OSMESG_FADEOUT_STEP 0x8888
#define INITIAL_MENU_OSMESG_LOAD_GAME_DONE 0x9999

extern void make_dl_nintendo_logo(Gfx** gpp, u32 alpha);
extern void initial_menu_init();
extern void initial_menu_cleanup();

#ifdef __cplusplus
}
#endif

#endif
