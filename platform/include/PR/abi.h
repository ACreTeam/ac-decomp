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

/* ADPCM frame size constant */
#define ADPCMFSIZE 9

/* N64 RSP audio command flags */
#define A_INIT        0x01
#define A_CONTINUE    0x00
#define A_LOOP        0x02
#define A_OUT         0x04
#define A_LEFT        0x02
#define A_RIGHT       0x00
#define A_VOL         0x04
#define A_RATE        0x08
#define A_EXP         0x10
#define A_INTERLEAVE  0x00
#define A_STEREO      0x02
#define A_ADPCM_SHORT 0x04

/* Note: true/false are defined in platform/compat.h which is force-included */

/* N64 RSP audio command macros — no-ops on non-RSP platforms.
 * These build command lists consumed by the platform audio mixer. */
#define aSetBuffer(pkt, f, in, out, c)   do { (void)(pkt); (void)(f); (void)(in); (void)(out); (void)(c); } while(0)
#define aClearBuffer(pkt, s, c)          do { (void)(pkt); (void)(s); (void)(c); } while(0)
#define aDMEMMove(pkt, in, out, c)       do { (void)(pkt); (void)(in); (void)(out); (void)(c); } while(0)
#define aMix(pkt, f, g, in, out)         do { (void)(pkt); (void)(f); (void)(g); (void)(in); (void)(out); } while(0)
#define aResample(pkt, f, p, buf)        do { (void)(pkt); (void)(f); (void)(p); (void)(buf); } while(0)
#define aADPCMdec(pkt, f, s)             do { (void)(pkt); (void)(f); (void)(s); } while(0)
#define aSetLoop(pkt, s)                 do { (void)(pkt); (void)(s); } while(0)
#define aLoadADPCM(pkt, n, d)            do { (void)(pkt); (void)(n); (void)(d); } while(0)
#define aS8Dec(pkt, f, d)                do { (void)(pkt); (void)(f); (void)(d); } while(0)
#define aHalfRate(pkt, in, out)          do { (void)(pkt); (void)(in); (void)(out); } while(0)
#define aInterleave(pkt, l, r)           do { (void)(pkt); (void)(l); (void)(r); } while(0)
#define aSaveBuffer(pkt, s, d, c)        do { (void)(pkt); (void)(s); (void)(d); (void)(c); } while(0)
#define aLoadBuffer(pkt, s, d, c)        do { (void)(pkt); (void)(s); (void)(d); (void)(c); } while(0)
#define aEnvMixer(pkt, in, out)          do { (void)(pkt); (void)(in); (void)(out); } while(0)
#define aSetVol(pkt, f, v, t, r)         do { (void)(pkt); (void)(f); (void)(v); (void)(t); (void)(r); } while(0)
#define aFilter(pkt, f, v, d)            do { (void)(pkt); (void)(f); (void)(v); (void)(d); } while(0)
#define aReverbFilter(pkt, f, v, d)      do { (void)(pkt); (void)(f); (void)(v); (void)(d); } while(0)

#endif /* _PR_ABI_H */
