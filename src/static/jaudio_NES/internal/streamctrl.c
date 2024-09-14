#include "jaudio_NES/streamctrl.h"

#include "jaudio_NES/audiowork.h"
#include "jaudio_NES/rate.h"
#include "dolphin/ai.h"
#include "dolphin/dvd.h"

char J_STREAMNAME[8][16] = {
    "/stream00.adp", "/stream01.adp", "/stream02.adp", "/stream03.adp",
    "/stream04.adp", "/stream05.adp", "/stream06.adp", "/stream07.adp",
};

// clang-format off
JSTREAM J_STREAM = {
    JSTREAM_STATE_STOPPED,
    JSTREAM_NO_TRACK_ID, JSTREAM_NO_TRACK_ID,
    0.0f, 0,
    0,
    0,
    0.0f, 0,
    0.0f,
    0
};
// clang-format on

/* @fabricated -- necessary for float ordering */
#pragma force_active on
MATCH_FORCESTRIP static f32 Jac_VolMoveStreamBGM(s32 l, s32 r) {
    // AISetStreamVolLeft((s32)(f32)l);
    // AISetStreamVolRight((s32)(f32)r);
    return l;
}
#pragma force_active reset

extern void StreamMain(void) {
    static DVDFileInfo finfo;
    static DVDCommandBlock cmd;
    u32 streamed_samples;
    u32 trigger;

    switch (J_STREAM.state) {
        case JSTREAM_STATE_STOPPED:
            break;

        case JSTREAM_STATE_REQUEST_STREAM:
            J_STREAM.now_stream_id = J_STREAM.req_stream_id;
            J_STREAM.req_stream_id = JSTREAM_NO_TRACK_ID;
            if (J_STREAM.now_stream_id == JSTREAM_NO_TRACK_ID) {
                J_STREAM.state = JSTREAM_STATE_STOPPED;
            } else {
                if (DVDOpen(J_STREAMNAME[J_STREAM.now_stream_id], &finfo) == FALSE) {
                    J_STREAM.now_stream_id = JSTREAM_NO_TRACK_ID;
                    J_STREAM.state = JSTREAM_STATE_STOPPED;
                } else {
                    J_STREAM.total_samples = finfo.length;
                    J_STREAM.total_samples =
                        (J_STREAM.total_samples / 256) * 224; // TODO: should probably make these defines
                    AISetStreamSampleRate(AI_SAMPLERATE_48KHZ);
                    if (J_STREAM.fadein_vol_timer == 0) {
                        J_STREAM.stream_vol = J_STREAM.fadein_vol;
                    } else {
                        J_STREAM.stream_vol = 0.0f;
                    }

                    AISetStreamVolLeft((s32)J_STREAM.stream_vol);
                    AISetStreamVolRight((s32)J_STREAM.stream_vol);
                    DVDPrepareStreamAsync(&finfo, 0, 0, nullptr);
                    J_STREAM.state = JSTREAM_STATE_START;
                }
            }
            break;

        case JSTREAM_STATE_START:
            if (DVDGetDriveStatus() == DVD_STATE_END) {
                AIResetStreamSampleCount();
                AISetStreamPlayState(AI_STREAM_START);
                J_STREAM.state = JSTREAM_STATE_PLAYING;
            }
            break;

        case JSTREAM_STATE_PLAYING:
            streamed_samples = AIGetStreamSampleCount();
            trigger = AIGetStreamTrigger();

            if (J_STREAM.fadein_vol_timer != 0) {
                f32 vol = J_STREAM.fadein_vol;
                vol -= J_STREAM.stream_vol;
                vol /= (f32)J_STREAM.fadein_vol_timer;
                J_STREAM.stream_vol += vol;
                J_STREAM.fadein_vol_timer--;
                AISetStreamVolLeft((s32)J_STREAM.stream_vol);
                AISetStreamVolRight((s32)J_STREAM.stream_vol);
            }

            if (J_STREAM.change_vol_timer1 != 0) {
                f32 vol = J_STREAM.target_vol1;
                vol -= J_STREAM.stream_vol;
                vol /= (f32)J_STREAM.change_vol_timer1;
                J_STREAM.stream_vol += vol;
                J_STREAM.change_vol_timer1--;
                AISetStreamVolLeft((s32)J_STREAM.stream_vol);
                AISetStreamVolRight((s32)J_STREAM.stream_vol);
            }

            if ((J_STREAM.total_samples - streamed_samples) < (JAC_FRAMESAMPLES * JSTREAM_FADEOUT_TIMER)) {
                J_STREAM.state = JSTREAM_STATE_FADEOUT;
                J_STREAM.fadeout_timer = JSTREAM_FADEOUT_TIMER;
            }
            break;

        case JSTREAM_STATE_CANCELLED:
        case JSTREAM_STATE_FADEOUT:
            u32 streamed_samples = AIGetStreamSampleCount();
            if (J_STREAM.fadeout_timer != 0 && (J_STREAM.total_samples - streamed_samples) != 0) {
                f32 vol = -J_STREAM.stream_vol;
                vol /= (f32)J_STREAM.fadeout_timer;
                J_STREAM.stream_vol += vol;
                J_STREAM.fadeout_timer--;
                AISetStreamVolLeft((s32)J_STREAM.stream_vol);
                AISetStreamVolRight((s32)J_STREAM.stream_vol);
            } else {
                DVDCancelStream(&cmd);
                J_STREAM.state = JSTREAM_STATE_STOP;
            }
            break;

        case JSTREAM_STATE_STOP:
            if (DVDGetDriveStatus() == DVD_STATE_END) {
                AISetStreamPlayState(AI_STREAM_STOP);
                J_STREAM.state = JSTREAM_STATE_CLEANUP;
            }
            break;

        case JSTREAM_STATE_CLEANUP:
            if (DVDGetDriveStatus() == DVD_STATE_END) {
                DVDClose(&finfo);
                J_STREAM.now_stream_id = -1;
                J_STREAM.state = JSTREAM_STATE_REQUEST_STREAM;
                AISetStreamPlayState(AI_STREAM_STOP);
            }
            break;
    }
}
