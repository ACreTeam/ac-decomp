#ifndef AUDIOCOMMON_H
#define AUDIOCOMMON_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define S16_MIN (-0x8000)
#define S16_MAX (0x7FFF)

#define AUDIO_ARAM_SIZE 0x400000 /* 4MB */
#define AUDIO_ARAM_HEAP_SIZE 0xC000

typedef enum DSPBUF_EVENTS {
    DSPBUF_EVENTS_0 = 0,
    DSPBUF_EVENTS_1 = 1,
    DSPBUF_EVENTS_2 = 2,
} DSPBUF_EVENTS;

#ifdef __cplusplus
}
#endif

#endif
