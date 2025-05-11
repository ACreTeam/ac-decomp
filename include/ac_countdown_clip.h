#ifndef AC_COUNTDOWN_CLIP_H
#define AC_COUNTDOWN_CLIP_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*aCOU_ANIME_PLAY_PROC)(void);

typedef struct countdown_clip_s {
    aCOU_ANIME_PLAY_PROC anime_play_proc;
    int anime_play_flag;
} aCOU_Clip_c;

#ifdef __cplusplus
}
#endif

#endif /* AC_COUNTDOWN_CLIP_H */
