#include "jaudio_NES/effect.h"

#include "jaudio_NES/system.h"
#include "jaudio_NES/audiostruct.h"
#include "jaudio_NES/audiowork.h"
#include "jaudio_NES/audioconst.h"
#include "jaudio_NES/memory.h"
#include "jaudio_NES/os.h"
#include "jaudio_NES/channel.h"
#include "jaudio_NES/track.h"
#include "jaudio_NES/sub_sys.h"
#include "jaudio_NES/audioheaders.h"
#include <dolphin/os.h>

static void __Nas_CallWaveProcess_Sub(sub* subtrack, s32 recalc_vol, s32 apply_bend) {
    f32 vol;
    f32 freqScale;
    s32 i;
    
    if (subtrack->changes.flags.volume || recalc_vol) {
        vol = subtrack->volume * subtrack->volume_scale * subtrack->group->applied_fade_volume;

        if (subtrack->group->flags.muted && (subtrack->mute_flags & AUDIO_MUTE_FLAG_SOFTEN)) {
            vol *= subtrack->group->mute_volume_scale;
        }

        subtrack->applied_volume = vol * vol;
    }

    if (subtrack->changes.flags.pan) {
        subtrack->pan = subtrack->new_pan * subtrack->pan_channel_weight;
    }

    freqScale = subtrack->frequency_scale;
    if (apply_bend) {
        freqScale *= subtrack->group->bend;
        subtrack->changes.flags.frequency_scale = TRUE;
    }

    for (i = 0; i < AUDIO_SUBTRACK_NOTE_NUM; i++) {
        note* note = subtrack->note_layers[i];

        if (note != NULL && note->enabled && note->channel != NULL) {
            static subtrack_updates updates_all = { { TRUE, TRUE, TRUE } };
            subtrack_updates* updates_p = &subtrack->changes;
            
            if (note->note_properties_need_init) {
                updates_p = &updates_all;
                note->note_properties_need_init = FALSE;
            }

            if (updates_p->flags.frequency_scale) {
                if (!note->_0A.flags.skip_freq_scale_update) {
                    note->note_frequency_scale = note->frequency_scale;
                } else {
                    note->note_frequency_scale = note->frequency_scale * freqScale;
                }
            }

            if (updates_p->flags.volume || recalc_vol) {
                if (!note->_0A.flags.skip_volume_update) {
                    note->note_velocity = note->velocity_square2;
                } else {
                    note->note_velocity = note->velocity_square2 * subtrack->applied_volume;
                }
            }

            if (updates_p->flags.pan) {
                if (!note->_0A.flags.skip_pan_update) {
                    note->note_velocity = note->pan; // @BUG - shouldn't this be note->note_pan??
                } else {
                    note->note_pan = (subtrack->pan + note->pan * (128 - subtrack->pan_channel_weight)) >> 7;
                }
            }
        }
    }

    subtrack->changes.as_byte = 0;
}

extern void Nas_MainCtrl(group* group) {
    s32 i;

    if (group->fade_timer != 0 && group->skip_ticks == 0) {
        group->flags.recalculate_volume = TRUE;
        group->fade_volume += group->fade_velocity;

        if (group->fade_volume > 1.0f) {
            group->fade_volume = 1.0f;
        }
        if (group->fade_volume < 0.0f) {
            group->fade_volume = 0.0f;
        }

        group->fade_timer--;
        if (group->fade_timer == 0) {
            switch (group->state) {
                case GROUP_STATE_FADE_OUT:
                    Nas_ReleaseGroup(group);
                    return;
            }
        }
    }

    if (group->flags.recalculate_volume) {
        group->applied_fade_volume = group->fade_volume * group->fade_volume_scale;
    }

    for (i = 0; i < NA_GROUP_NUM; i++) {
        if (group->subtracks[i]->enabled == TRUE) {
            __Nas_CallWaveProcess_Sub(group->subtracks[i], group->flags.recalculate_volume, group->flags.apply_bend);
        }
    }

    group->flags.recalculate_volume = FALSE;
}

static f32 Nas_SweepCalculator(sweep* sweep) {
    u32 loResCur;
    f32 sweepFreq;

    sweep->current += sweep->speed;
    loResCur = (sweep->current >> 8) & 0xFF;

    if (loResCur >= 127) {
        loResCur = 127;
        sweep->mode = PORTAMENTO_MODE_OFF;
    }

    return 1.0f + sweep->extent * (PCENTTABLE[loResCur + 128] - 1.0f);
}

static s16 Nas_ModTableRead(tmtable* table) {
    int idx;

    table->time += (int)table->rate;
    idx = (table->time >> 10) & 0x3F;
    return table->curve[idx];
}

static f32 Nas_Modulator(tmtable* table) {
    vibparam* param = table->vibrato_params;
    s16 mod;
    f32 depth;
    f32 invDepth;
    f32 result;
    f32 t;

    if (table->delay != 0) {
        table->delay--;
        return 1.0f;
    }

    if (param != NULL) {
        if (table->depth_change_timer != 0) {
            if (table->depth_change_timer == 1) {
                table->depth = (int)param->depth_target;
            } else {
                table->depth += ((int)param->depth_target - table->depth) / (int)table->depth_change_timer;
            }

            table->depth_change_timer--;
        } else if (param->depth_target != (int)table->depth) {
            u32 delay = param->depth_change_delay;
            
            table->depth_change_timer = delay;
            if (delay == 0) {
                table->depth = (s32)param->depth_target;
            }
        }

        if (table->rate_change_timer != 0) {
            if (table->rate_change_timer == 1) {
                table->rate = (int)param->rate_target;
            } else {
                table->rate += ((int)param->rate_target - table->rate) / (int)table->rate_change_timer;
            }

            table->rate_change_timer--;
        } else if (param->rate_target != (int)table->rate) {
            u32 delay = param->rate_change_delay;
            
            table->rate_change_timer = delay;
            if (delay == 0) {
                table->rate = (s32)param->rate_target;
            }
        }
    }

    if (table->depth == 0.0f) {
        return 1.0f;
    }

    mod = Nas_ModTableRead(table);
    t = table->depth;
    depth = 1.0f + (t / 4096.0f);
    invDepth = 1.0f / depth;
    result = 1.0f / ((depth - invDepth) * (mod + 32768.0f) / 65536.0f + invDepth);
    return result;
}

extern void Nas_ChannelModulation(channel* channel) {
    sweep* sweep;
    tmtable* table;

    sweep = &channel->playback_ch.portamento_sweep;
    if (sweep->mode != PORTAMENTO_MODE_OFF) {
        channel->playback_ch.portamento_frequency_scale = Nas_SweepCalculator(sweep);
    }

    table = &channel->playback_ch.vibrato_tmtable;
    if (table->active) {
        channel->playback_ch.vibrato_frequency_scale = Nas_Modulator(table);
    }
}

extern void Nas_ChannelModInit(channel* chan) {
    tmtable* table = &chan->playback_ch.vibrato_tmtable;
    vibparam* param;

    table->active = TRUE;
    table->curve = WAVEMEM_TABLE[2];

    if (chan->playback_ch.current_parent_note->_0A.flags.use_vibrato == TRUE) {
        table->vibrato_params = &chan->playback_ch.current_parent_note->sub_track->vibrato_params;
    } else {
        table->vibrato_params = &chan->playback_ch.current_parent_note->vibrato_params;
    }

    param = table->vibrato_params;
    if ((table->depth_change_timer = param->depth_change_delay) == 0) {
        table->depth = (int)param->depth_target;
    } else {
        table->depth = (int)param->depth_start;
    }

    if ((table->rate_change_timer = param->rate_change_delay) == 0) {
        table->rate = (int)param->rate_target;
    } else {
        table->rate = (int)param->rate_start;
    }

    chan->playback_ch.vibrato_frequency_scale = 1.0f;
    table->time = 0;
    table->delay = param->delay;
}

extern void Nas_SweepInit(channel* chan) {
    chan->playback_ch.portamento_frequency_scale = 1.0f;
    chan->playback_ch.portamento_sweep = chan->playback_ch.current_parent_note->portamento_sweep;
}

extern void Nas_EnvInit(envp* env, envdat* data, s16* vol_out) {
    env->state.as_byte = 0;
    env->delay = 0;
    env->sustain = 0.0f;
    env->current = 0.0f;
    env->velocity = 0.0f;
    env->fadeout_velocity = 0.0f;
    env->pEnvData = data;
}

extern f32 Nas_EnvProcess(envp* process) {
    u8 start_state = process->state.flags.status;

    switch (process->state.flags.status) {
        case ADSR_STATUS_DISABLED:
            return 0.0f;
        case ADSR_STATUS_INITIAL:
            if (process->state.flags.hang) {
                process->state.flags.status = ADSR_STATUS_HANG;
                break;
            }
        // fallthrough
        case ADSR_STATUS_START_LOOP:
            process->envelope_idx = 0;
            process->state.flags.status = ADSR_STATUS_LOOP;
        // fallthrough
        retry:
        case ADSR_STATUS_LOOP:
            process->delay = process->pEnvData[process->envelope_idx].delay;
            switch (process->delay) {
                case ADSR_DISABLE:
                    process->state.flags.status = ADSR_STATUS_DISABLED;
                    break;
                case ADSR_HANG:
                    process->state.flags.status = ADSR_STATUS_HANG;
                    break;
                case ADSR_GOTO:
                    process->envelope_idx = process->pEnvData[process->envelope_idx].value;
                    goto retry;
                case ADSR_RESTART:
                    process->state.flags.status = ADSR_STATUS_INITIAL;
                    break;
                case ADSR_SPECIAL4:
                    process->_18 = (int)process->pEnvData[process->envelope_idx].value / 32767.0f;
                    process->state.flags.unused = TRUE;
                    process->envelope_idx++;
                    goto retry;
                default:
                    process->delay = process->delay * AG.audio_params.updates_per_frame_scaled;
                    if (process->delay == 0) {
                        process->delay = 1;
                    }

                    process->target = process->pEnvData[process->envelope_idx].value / 32767.0f;
                    process->target *= process->target;
                    process->velocity = (process->target - process->current) / process->delay;
                    process->state.flags.status = ADSR_STATUS_FADE;
                    process->envelope_idx++;
                    break;
            }

            if (process->state.flags.status != ADSR_STATUS_FADE) {
                break;
            }
        // fallthrough
        case ADSR_STATUS_FADE:
            process->current += process->velocity;
            if (--process->delay <= 0) {
                process->state.flags.status = ADSR_STATUS_LOOP;
            }
        // fallthrough
        case ADSR_STATUS_HANG:
            break;
        case ADSR_STATUS_DECAY:
        case ADSR_STATUS_RELEASE:
            process->current -= process->fadeout_velocity;
            if (process->sustain != 0.0f && start_state == ADSR_STATUS_DECAY) {
                if (process->current < process->sustain) {
                    process->current = process->sustain;
                    process->delay = 128;
                    process->state.flags.status = ADSR_STATUS_SUSTAIN;
                }
                break;
            }

            if (process->current < 0.00001f) {
                process->current = 0.0f;
                process->state.flags.status = ADSR_STATUS_DISABLED;
            }
            break;
        case ADSR_STATUS_SUSTAIN:
            process->delay--;
            if (process->delay == 0) {
                process->state.flags.status = ADSR_STATUS_RELEASE;
            }
            break;
    }

    if (process->state.flags.decay) {
        process->state.flags.status = ADSR_STATUS_DECAY;
        process->state.flags.decay = FALSE;
    }

    if (process->state.flags.release) {
        process->state.flags.status = ADSR_STATUS_RELEASE;
        process->state.flags.release = FALSE;
    }

    if (process->current < 0.0f) {
        return 0.0f;
    }

    if (process->current > 1.0f) {
        return 1.0f;
    }

    return process->current;
}
