/* Shadow override of include/dolphin/types.h for arm64.
 * Replaces 'signed/unsigned long' (64-bit on arm64) with fixed-width types,
 * and swaps Metrowerks-specific standard headers for system ones. */
#ifndef _DOLPHIN_TYPES_H_
#define _DOLPHIN_TYPES_H_

#include "platform/compat.h"

/* Standard library replacements for MSL_C headers the original pulls in */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* cmath.h defines min/max/clamp macros — include the original */
#include "cmath.h"

#endif /* _DOLPHIN_TYPES_H_ */
