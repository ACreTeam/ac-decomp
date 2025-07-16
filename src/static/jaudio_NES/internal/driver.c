#include "jaudio_NES/driver.h"

#include "jaudio_NES/audiostruct.h"
#include "jaudio_NES/astest.h"
#include "jaudio_NES/track.h"

static u16 NOISE_TABLE[] = { 0, 1, 2, 4, 8, 12, 16, 20, 24, 32, 36, 40, 46, 52, 56, 53 };
static dspch_ DSPCH[64];
static u32 STOP_VELOCONV = 0;

static u32 Env_DataH = (A_ENVMIXER << 24) | (0x00 << 16) | (0x00 << 8) | (0x00);
static u32 Env_DataL1 = 0x58AAC4DE;
static u32 Env_DataL2 = 0x9058C4DE;
static u32 Env_DataL3 = 0x9058C4DE;

#define SAMPLE_SIZE (s32)sizeof(s16)

static Acmd* __LoadAuxBuf(Acmd* cmd, u16 ofs, u16 startPos, s32 size, delay* del_p);
static Acmd* __SaveAuxBuf(Acmd* cmd, u16 ofs, u16 startPos, s32 size, delay* del_p);

static void Nas_CpuFX(s32 chunkLen, s32 updateIdx, s32 reverbIdx) {
    delay* del_p = &AG.synth_delay[reverbIdx];
    delayparam* param_p = &del_p->params[del_p->cur_frame][updateIdx];
    s32 count = chunkLen / del_p->downsample_rate;
    s32 i;
    
    if (del_p->resample_effect_on && (u32)count == 1 && del_p->right_save_resample_buf != NULL) {
        s32 sample;
        s32 n = 10;
        s32 s = 10;

        count += del_p->resample_effect_extra_samples;
        param_p->save_resample_num_samples = count;
        param_p->load_resample_pitch = (param_p->save_resample_num_samples << 15) / chunkLen;
        param_p->save_resample_pitch = (chunkLen << 15) / param_p->save_resample_num_samples;
        
        for (i = 0; i < 10; i++) {
            s32 sample2;

            n--;
            sample = del_p->resample_effect_load_unk + param_p->load_resample_pitch * chunkLen * SAMPLE_SIZE;
            sample2 = (sample >> 16);
            if (sample2 != count && n == 0) {
                param_p->load_resample_pitch = (count * 0x10000 - del_p->resample_effect_load_unk) / (chunkLen * SAMPLE_SIZE);
            } else if (sample2 > count) {
                param_p->load_resample_pitch--;
            } else if (sample2 < count) {
                param_p->load_resample_pitch++;
            } else {
                break;
            }
        }

        del_p->resample_effect_load_unk = sample;

        for (i = 0; i < 10; i++) {
            s32 sample2;

            s--;
            sample = del_p->resample_effect_save_unk + param_p->save_resample_pitch * chunkLen * SAMPLE_SIZE;
            sample2 = (sample >> 16);
            if (sample2 != count && s == 0) {
                param_p->save_resample_pitch = (chunkLen * 0x10000 - del_p->resample_effect_save_unk) / (count * SAMPLE_SIZE);
            } else if (sample2 > count) {
                param_p->save_resample_pitch--;
            } else if (sample2 < count) {
                param_p->save_resample_pitch++;
            } else {
                break;
            }
        }

        del_p->resample_effect_save_unk = sample;
    }

    s32 next_buf_pos = del_p->next_reverb_buf_pos;
    {
        s32 t = del_p->next_reverb_buf_pos + count - del_p->delay_num_samples;

        if (t < 0) {
            param_p->size = count * SAMPLE_SIZE;
            param_p->wrapped_size = 0;
            param_p->start_pos = del_p->next_reverb_buf_pos;
            del_p->next_reverb_buf_pos += t;
        } else {
            param_p->size = (count - t) * SAMPLE_SIZE;
            param_p->wrapped_size = t * SAMPLE_SIZE;
            param_p->start_pos = del_p->next_reverb_buf_pos;
            del_p->next_reverb_buf_pos = t;
        }
    }

    param_p->n_samples_after_downsampling = count;
    param_p->n_samples = chunkLen;

    if (del_p->sub_delay != 0) {
        s32 t = del_p->delay_num_samples;
        
        next_buf_pos += del_p->sub_delay;
        while (next_buf_pos >= t) {
            next_buf_pos -= t;
        }

        param_p = del_p->sub_params[del_p->cur_frame] + updateIdx;
        s32 t2 = chunkLen / del_p->downsample_rate;
        s32 t3 = next_buf_pos + t2 - t;

        if (t3 < 0) {
            param_p->size = t2 * SAMPLE_SIZE;
            param_p->wrapped_size = 0;
            param_p->start_pos = next_buf_pos;
        } else {
            param_p->size = (t2 - t3) * SAMPLE_SIZE;
            param_p->wrapped_size = t3 * SAMPLE_SIZE;
            param_p->start_pos = next_buf_pos;
        }

        param_p->n_samples_after_downsampling = count;
        param_p->n_samples = chunkLen;
    }
}

static void __Nas_PushDrvReg(s32 updateIdx) {
    s32 i;
    commonch* common0;
    commonch* common1;
    s32 baseIdx = updateIdx * AG.num_channels;

    for (i = 0; i < AG.num_channels; i++) {
        common0 = &AG.channels[i].common_ch;
        common1 = &AG.common_channel[baseIdx + i];

        if (common0->enabled) {
            CopyStc(common1, common0);
            common0->needs_init = FALSE;
        } else {
            common1->enabled = FALSE;
        }

        common0->harmonic_idx_cur_and_prev = 0;
    }
}

extern Acmd* Nas_smzAudioFrame(Acmd* cmdStart, s32* cmdCount, s16* aiStart, s32 aiBufLen) {
    Acmd* cmdP;
    s16* aiBufP;
    s32 chunkLen;
    s32 i;
    s32 j;

    cmdP = cmdStart;
    for (i = AG.audio_params.updates_per_frame; i > 0; i--) {
        Nas_MySeqMain(i - 1);
        __Nas_PushDrvReg(AG.audio_params.updates_per_frame - i);
    }

    aiBufP = aiStart;
    AG.adpcm_code_book = NULL;

    for (i = AG.audio_params.updates_per_frame; i > 0; i--) {
        chunkLen = AG.audio_params.num_samples_per_update;

        for (j = 0; j < AG.num_synth_reverbs; j++) {
            if (AG.synth_delay[j].use_reverb) {
                Nas_CpuFX(chunkLen, AG.audio_params.updates_per_frame - i, j);
            }
        }

        cmdP = Nas_DriveRsp(aiBufP, chunkLen, cmdP, AG.audio_params.updates_per_frame - i);
        aiBufLen -= chunkLen;
        aiBufP += (JAC_FRAMESAMPLES >> 1) & ~1;
    }

    for (j = 0; j < AG.num_synth_reverbs; j++) {
        if (AG.synth_delay[j].frames_to_ignore != 0) {
            AG.synth_delay[j].frames_to_ignore--;
        }
        AG.synth_delay[j].cur_frame ^= 1;
    }

    *cmdCount = cmdP - cmdStart;
    return cmdP;
}

static void __Nas_WaveTerminateProcess(s32 updateIdx, s32 chanIdx) {
    commonch* common;
    s32 i;

    for (i = updateIdx + 1; i < AG.audio_params.updates_per_frame; i++) {
        common = &AG.common_channel[i * AG.num_channels + chanIdx];
        if (!common->needs_init) {
            common->enabled = FALSE;
        } else {
            break;
        }
    }
}

static Acmd* Nas_LoadAux2nd(Acmd* cmd, const delay* del_p, s16 updateIdx) {
    const delayparam* param = &del_p->params[del_p->cur_frame][updateIdx];

    cmd = __LoadAuxBuf(cmd, 0x3A0, param->start_pos, param->size, (delay*)del_p);
    if (param->wrapped_size != 0) {
        cmd = __LoadAuxBuf(cmd, 0x3A0 + param->size, 0, param->wrapped_size, (delay*)del_p);
    }

    return cmd;
}

static Acmd* Nas_SaveAux2nd(Acmd* cmd, const delay* del_p, s16 updateIdx) {
    const delayparam* param = &del_p->params[del_p->cur_frame][updateIdx];

    cmd = __SaveAuxBuf(cmd, 0x3A0, param->start_pos, param->size, (delay*)del_p);
    if (param->wrapped_size != 0) {
        cmd = __SaveAuxBuf(cmd, 0x3A0 + param->size, 0, param->wrapped_size, (delay*)del_p);
    }

    return cmd;
}

static void Nas_ClearBuffer(Acmd* cmd, s32 dmem, s32 size) {
    aClearBuffer(cmd, dmem, size);
}

static void Nas_Mix(Acmd* cmd, s32 flags, s32 gain, s32 dmem_in, s32 dmem_out) {
    aMix(cmd, flags, gain, dmem_in, dmem_out);
}

static void Nas_SetBuffer(Acmd* cmd, s32 flags, s32 dmem_in, s32 dmem_out, s32 count) {
    aSetBuffer(cmd, flags, dmem_in, dmem_out, count);
}

static void Nas_DMEMMove(Acmd* cmd, s32 dmem_in, s32 dmem_out, s32 count) {
    aDMEMMove(cmd, dmem_in, dmem_out, count);
}

static void Nas_HalfCut(Acmd* cmd, s32 src, s32 dst, s32 len) {
    aHalfCut(cmd, src, dst, len);
}

static void Nas_SetEnvParam(Acmd* cmd, s32 reverbVol, s32 rampReverb, s32 rampL, s32 rampR) {
    aSetEnvParam(cmd, reverbVol, rampReverb, rampL, rampR);
}

static void Nas_LoadBuffer2(Acmd* cmd, s32 dst, s32 len, s32 src) {
    aLoadBuffer2(cmd, src, dst, len);
}

static void Nas_SaveBuffer2(Acmd* cmd, s32 src, s32 len, s32 dst) {
    aSaveBuffer2(cmd, dst, src, len);
}

static void Nas_SetEnvParam2(Acmd* cmd, s32 volL, s32 volR) {
    aSetEnvParam2(cmd, volL, volR);
}

static void Nas_PCM8dec(Acmd* cmd, s32 flags, s32 state) {
    aPCM8dec(cmd, flags, state);
}

static void Nas_DistFilter(Acmd* cmd, s32 gain, s32 dmem_in, s32 dmem_out, s32 len) {
    aDistFilter(cmd, gain, dmem_in, dmem_out, len);
}

// TODO: check params
static void Nas_NoiseFilter(Acmd* cmd, s32 buf, s32 flags, s32 addr, s32 len) {
    aNoiseFilter(cmd, buf, flags, addr, len);
}

static void Nas_FirFilter(Acmd* cmd, s32 flags, s32 buf, s16* filter) {
    aFirFilter(cmd, flags, buf, filter);
}

static void Nas_FirLoadTable(Acmd* cmd, s32 size, s16* filter) {
    aFirLoadTable(cmd, size, filter);
}

static Acmd* Nas_CrossMix(Acmd* cmd, delay* del_p) {
    aDMEMMove(cmd++, 0xC40, 0x6E0, 0x1A0);
    aMix(cmd++, 0x1A, del_p->leak_rtl, 0xDE0, 0xC40);
    aMix(cmd++, 0x1A, del_p->leak_ltl, 0x6E0, 0xDe0);
    return cmd;
}
