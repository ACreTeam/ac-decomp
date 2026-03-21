/* Shadow PR/abi.h — defines N64 audio ABI types for the Apple platform port.
 * The original N64 SDK PR/abi.h is not in this repository; this stub provides
 * the minimal type definitions needed to compile the jaudio_NES audio driver. */
#ifndef _PR_ABI_H
#define _PR_ABI_H

#include <stdint.h>

/* Audio command word — 8 bytes, matching the N64 RSP audio ABI packet format */
typedef union {
    struct { uint32_t w0; uint32_t w1; } words;
    long long int force_structure_alignment;
} Acmd;

#endif /* _PR_ABI_H */
