#ifndef STREAMCTRL_H
#define STREAMCTRL_H

#include "types.h"

/* @unused */
// Jac_PlayStreamBGM(s32, s32, s32);
// Jac_StopStreamBGM(s32, s32);
// Jac_VolMoveStreamBGM(s32, s32);

#define JSTREAM_NO_TRACK_ID (-1)
#define JSTREAM_FADEOUT_TIMER (120)

typedef struct JSTREAM_ {
    s32 state;
    s32 req_stream_id;
    s32 now_stream_id;
    f32 fadein_vol;
    s32 fadein_vol_timer;
    s32 _14;
    s32 fadeout_timer;
    f32 target_vol1;
    s32 change_vol_timer1;
    f32 stream_vol;
    u32 total_samples;
} JSTREAM;

typedef enum JSTREAM_STATE_ {
    JSTREAM_STATE_STOPPED,
    JSTREAM_STATE_REQUEST_STREAM,
    JSTREAM_STATE_START,
    JSTREAM_STATE_PLAYING,
    JSTREAM_STATE_CANCELLED,
    JSTREAM_STATE_FADEOUT,
    JSTREAM_STATE_STOP,
    JSTREAM_STATE_CLEANUP,

    JSTREAM_STATE_NUM
} JSTREAM_STATE;

extern char J_STREAMNAME[][16];
extern JSTREAM J_STREAM;

extern void StreamMain(void);

#endif
