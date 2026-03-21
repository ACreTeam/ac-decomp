/* Shadow libultra/libultra.h - fixes bcmp/bcopy declarations for arm64.
 * The original uses non-const void* and u32 for bcmp which conflicts with
 * the system libc signatures. */
#ifndef LIBULTRA_H
#define LIBULTRA_H

#include "types.h"
#include <dolphin/os/OSTime.h>
#include <dolphin/os/OSCache.h>
#include "libultra/gu.h"
#include "libultra/osMesg.h"
#include "libultra/shutdown.h"
#include "libultra/os_timer.h"
#include "libultra/os_thread.h"
#include "libultra/os_pi.h"
#include "libultra/initialize.h"
#include "libc64/math64.h"

#define N64_SCREEN_HEIGHT 240
#define N64_SCREEN_WIDTH  320

#ifdef __cplusplus
extern "C" {
#endif

typedef u64 Z_OSTime;

/* bcmp/bcopy use system libc signatures */
#include <strings.h>   /* bcmp, bcopy, bzero */
/* bzero is in <strings.h> too; avoid redeclaration */

void osSyncPrintf(const char* fmt, ...);
void osWritebackDCache(void* vaddr, u32 nbytes);
u32  osGetCount(void);
OSTime osGetTime(void);

extern s32 osAppNMIBuffer[16];
extern int osShutdown;
extern u8  __osResetSwitchPressed;

#ifdef __cplusplus
}
#endif

#endif /* LIBULTRA_H */
