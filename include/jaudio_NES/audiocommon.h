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

#define AUDIO_GROUP_MAX 5
#define AUDIO_SUBTRACK_NUM 16

#define NA_MAKE_COMMAND(a0, a1, a2, a3) \
    (u32)((((a0) & 0xFF) << 24) | (((a1) & 0xFF) << 16) | (((a2) & 0xFF) << 8) | (((a3) & 0xFF) << 0))

typedef enum DSPBUF_EVENTS {
    DSPBUF_EVENT_INIT = 0,
    DSPBUF_EVENT_FRAME_END = 1,
    DSPBUF_EVENT_MIX = 2,
} DSPBUF_EVENTS;

typedef enum SampleMedium {
    /* 0 */ MEDIUM_RAM,
    /* 1 */ MEDIUM_UNK,
    /* 2 */ MEDIUM_CART,
    /* 3 */ MEDIUM_DISK_DRIVE,
    /* 5 */ MEDIUM_RAM_UNLOADED = 5
} SampleMedium;

typedef enum AudioCacheLoadType {
    /* 0 */ CACHE_LOAD_PERMANENT,
    /* 1 */ CACHE_LOAD_PERSISTENT,
    /* 2 */ CACHE_LOAD_TEMPORARY,
    /* 3 */ CACHE_LOAD_EITHER,
    /* 4 */ CACHE_LOAD_EITHER_NOSYNC
} AudioCacheLoadType;

#ifdef __cplusplus
}
#endif

#endif
