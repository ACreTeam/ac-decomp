#pragma once
/* Master platform umbrella header.
 * Include this first (or rely on CMake compile definitions) to activate the
 * Metal port shim layer. */

#define PLATFORM_APPLE  1
#define TARGET_PC       1   /* activates #ifdef TARGET_PC seams in GX headers */

/* Silence Metrowerks-specific GCC extension warnings */
#ifndef __GNUC__
#define __GNUC__ 1
#endif

#include "platform/compat.h"
#include "platform/endian.h"
/* Pre-include shadow headers so their guards are set before any original GC
 * header does a relative include and bypasses the shadow. */
#include <dolphin/types.h>  /* sets _DOLPHIN_TYPES_H_ */
#include <types.h>           /* sets TYPES_H (shadow: no MSL_C/w_math.h) */
#include <dolphin/card.h>    /* sets _DOLPHIN_CARD (shadow: no long sub-headers) */

/* Shared platform constants */
#define PLATFORM_SCREEN_WIDTH  640
#define PLATFORM_SCREEN_HEIGHT 480

/* GC timer frequency (OSTime ticks per second) — 486 MHz / 4 = ~162 MHz bus / 4 */
#define GC_TIMER_CLOCK  40500000ULL   /* ~40.5 MHz timebase */

/* OS_TIMER_CLOCK must be available before os.h for tick conversion macros */
#define __OSBusClock   162000000UL
#define __OSCoreClock  486000000UL
