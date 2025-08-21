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
static Acmd* Nas_SaveBufferAuto(Acmd* cmd, u16 ofs, u16 size, s32 startAddr);

static void Nas_CpuFX(s32 chunkLen, s32 updateIdx, s32 reverbIdx) {
    delayparam* param_p;
    s32 count;
    delay* del_p;
    s32 t;
    s32 i;
    s32 sample2;
    s32 next_buf_pos;
    s32 t2;
    s32 idx;
    s32 t3;
    s32 sample;
    s32 n;
    s32 s;

    del_p = &AG.synth_delay[reverbIdx];
    param_p = &del_p->params[del_p->cur_frame][updateIdx];
    count = chunkLen / AG.synth_delay[reverbIdx].downsample_rate;
    if (AG.synth_delay[reverbIdx].resample_effect_on && AG.synth_delay[reverbIdx].downsample_rate == 1 && del_p->right_save_resample_buf != NULL) {
        count += del_p->resample_effect_extra_samples;
        param_p->save_resample_num_samples = count;
        param_p->load_resample_pitch = (param_p->save_resample_num_samples << 15) / chunkLen;
        param_p->save_resample_pitch = (chunkLen << 15) / param_p->save_resample_num_samples;
        
        n = 10;
        s = 10;
        for (i = 0; i < 10; i++) {
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
            s--;
            sample = del_p->resample_effect_save_unk + param_p->save_resample_pitch * count * SAMPLE_SIZE;
            sample2 = (sample >> 16);
            if (sample2 != chunkLen && s == 0) {
                param_p->save_resample_pitch = (chunkLen * 0x10000 - del_p->resample_effect_save_unk) / (count * SAMPLE_SIZE);
            } else if (sample2 > chunkLen) {
                param_p->save_resample_pitch--;
            } else if (sample2 < chunkLen) {
                param_p->save_resample_pitch++;
            } else {
                break;
            }
        }

        del_p->resample_effect_save_unk = sample;
    }

    next_buf_pos = del_p->next_reverb_buf_pos;
    t = del_p->next_reverb_buf_pos + count - del_p->delay_num_samples;

    if (t < 0) {
        param_p->size = count * SAMPLE_SIZE;
        param_p->wrapped_size = 0;
        param_p->start_pos = del_p->next_reverb_buf_pos;
        del_p->next_reverb_buf_pos += count;
    } else {
        param_p->size = (count - t) * SAMPLE_SIZE;
        param_p->wrapped_size = t * SAMPLE_SIZE;
        param_p->start_pos = del_p->next_reverb_buf_pos;
        del_p->next_reverb_buf_pos = t;
    }

    param_p->n_samples_after_downsampling = count;
    param_p->n_samples = chunkLen;

    if (del_p->sub_delay != 0) {
        t = del_p->delay_num_samples;
        idx = next_buf_pos + del_p->sub_delay;
        while (idx >= t) {
            idx -= t;
        }

        param_p = del_p->sub_params[del_p->cur_frame] + updateIdx;
        t2 = chunkLen / del_p->downsample_rate;
        t3 = idx + t2 - t;

        if (t3 < 0) {
            param_p->size = t2 * SAMPLE_SIZE;
            param_p->wrapped_size = 0;
            param_p->start_pos = idx;
        } else {
            param_p->size = (t2 - t3) * SAMPLE_SIZE;
            param_p->wrapped_size = t3 * SAMPLE_SIZE;
            param_p->start_pos = idx;
        }

        param_p->n_samples_after_downsampling = t2;
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

static Acmd* Nas_LoadAuxBufferC(Acmd* cmd, s32 samples_per_update, delay* del_p, s16 update_idx) {
    delayparam* param = &del_p->params[del_p->cur_frame][update_idx];
    s16 ofs_size = (param->start_pos & 7) * SAMPLE_SIZE;
    
    cmd = __LoadAuxBuf(cmd, 0x3A0, param->start_pos - (ofs_size / SAMPLE_SIZE), 0x1A0, del_p);
    if (param->wrapped_size != 0) {
        s16 wrapped_ofs_size = ALIGN_NEXT(ofs_size + param->size, 16);
        
        cmd = __LoadAuxBuf(cmd, 0x3A0 + wrapped_ofs_size, 0, 0x1A0 - wrapped_ofs_size, del_p);
    }

    aSetBuffer(cmd++, 0, 0x3A0 + ofs_size, 0xC40, samples_per_update * SAMPLE_SIZE);
    aResample(cmd++, del_p->resample_flags, del_p->downsample_pitch, del_p->left_load_resample_buf);
    aSetBuffer(cmd++, 0, 0x3A0 + 0x1A0 + ofs_size, 0xDE0, samples_per_update * SAMPLE_SIZE);
    aResample(cmd++, del_p->resample_flags, del_p->downsample_pitch, del_p->right_load_resample_buf);
    return cmd;
}

static Acmd* Nas_SaveAuxBufferCH(Acmd* cmd, delay* del_p, s16 update_idx) {
    delayparam* param = &del_p->params[del_p->cur_frame][update_idx];
    s16 samples = param->n_samples;
    u32 size = samples * SAMPLE_SIZE;

    aDMEMMove(cmd++, 0xC40, 0x3A0, size);
    aSetBuffer(cmd++, 0, 0x3A0, 0x6E0, param->save_resample_num_samples * SAMPLE_SIZE);
    aResample(cmd++, del_p->resample_flags, param->save_resample_pitch, del_p->left_save_resample_buf);
    cmd = Nas_SaveBufferAuto(cmd, 0x6E0, param->size, (s32)&del_p->left_reverb_buf[param->start_pos]);
    if (param->wrapped_size != 0) {
        cmd = Nas_SaveBufferAuto(cmd, 0x6E0 + param->size, param->wrapped_size, (s32)&del_p->left_reverb_buf[0]);
    }

    aDMEMMove(cmd++, 0xDE0, 0x3A0, size);
    aSetBuffer(cmd++, 0, 0x3A0, 0x6E0, param->save_resample_num_samples * SAMPLE_SIZE);
    aResample(cmd++, del_p->resample_flags, param->save_resample_pitch, del_p->right_save_resample_buf);
    cmd = Nas_SaveBufferAuto(cmd, 0x6E0, param->size, (s32)&del_p->right_reverb_buf[param->start_pos]);
    if (param->wrapped_size != 0) {
        cmd = Nas_SaveBufferAuto(cmd, 0x6E0 + param->size, param->wrapped_size, (s32)&del_p->right_reverb_buf[0]);
    }

    return cmd;
}

static Acmd* Nas_LoadAuxBufferCH(Acmd* cmd, s32 samples_per_update, delay* del_p, s16 update_idx) {
    delayparam* param = &del_p->params[del_p->cur_frame][update_idx];
    s16 ofs_size = (param->start_pos & 7) * SAMPLE_SIZE;
    
    cmd = __LoadAuxBuf(cmd, 0x3A0, param->start_pos - (ofs_size / SAMPLE_SIZE), 0x1A0, del_p);
    if (param->wrapped_size != 0) {
        s16 wrapped_ofs_size = ALIGN_NEXT(ofs_size + param->size, 16);
        s32 load_size = 0x1A0 - wrapped_ofs_size;

        if (load_size > 0) {
            cmd = __LoadAuxBuf(cmd, 0x3A0 + wrapped_ofs_size, 0, load_size, del_p);
        }
    }

    aSetBuffer(cmd++, 0, 0x3A0 + ofs_size, 0xC40, samples_per_update * SAMPLE_SIZE);
    aResample(cmd++, del_p->resample_flags, param->load_resample_pitch, del_p->left_load_resample_buf);
    aSetBuffer(cmd++, 0, 0x3A0 + 0x1A0 + ofs_size, 0xDE0, samples_per_update * SAMPLE_SIZE);
    aResample(cmd++, del_p->resample_flags, param->load_resample_pitch, del_p->right_load_resample_buf);
    return cmd;
}

static Acmd* Nas_DelayFilter(Acmd* cmd, s32 size, delay* del_p) {
    if (del_p->filter_left != NULL) {
        aFirLoadTable(cmd++, size, del_p->filter_left);
        aFirFilter(cmd++, del_p->resample_flags, 0xC40, del_p->filter_left_state);
    }

    if (del_p->filter_right != NULL) {
        aFirLoadTable(cmd++, size, del_p->filter_right);
        aFirFilter(cmd++, del_p->resample_flags, 0xDE0, del_p->filter_right_state);
    }

    return cmd;
}

static Acmd* Nas_SendLine(Acmd* cmd, delay* del_p, s32 update_idx) {
    delay* mix_delay;

    if (del_p->mix_reverb_idx >= AG.num_synth_reverbs) {
        return cmd;
    }

    mix_delay = &AG.synth_delay[del_p->mix_reverb_idx];
    if (mix_delay->downsample_rate == 1) {
        cmd = Nas_LoadAux2nd(cmd, mix_delay, update_idx);
        aMix(cmd++, 0x34, del_p->mix_reverb_strength, 0xC40, 0x3A0);
        cmd = Nas_LoadAux2nd(cmd, mix_delay, update_idx);
    }

    return cmd;
}

static Acmd* Nas_LoadAuxBuffer1(Acmd* cmd, s32 samples_per_update, delay* del_p, s16 update_idx) {
    delayparam* param_p = &del_p->params[del_p->cur_frame][update_idx];
    
    cmd = __LoadAuxBuf(cmd, 0xC40, param_p->start_pos, param_p->size, del_p);
    if (param_p->wrapped_size != 0) {
        cmd = __LoadAuxBuf(cmd, 0xC40 + param_p->size, 0, param_p->wrapped_size, del_p);
    }

    return cmd;
}

static Acmd* Nas_LoadAuxBuffer1_B(Acmd* cmd, s32 samples_per_update, delay* del_p, s16 update_idx) {
    delayparam* param_p = &del_p->sub_params[del_p->cur_frame][update_idx];
    
    cmd = __LoadAuxBuf(cmd, 0xC40, param_p->start_pos, param_p->size, del_p);
    if (param_p->wrapped_size != 0) {
        cmd = __LoadAuxBuf(cmd, 0xC40 + param_p->size, 0, param_p->wrapped_size, del_p);
    }

    return cmd;
}

static Acmd* Nas_SaveBufferAuto(Acmd* cmd, u16 dmem, u16 size, s32 startAddr) {
    s32 startUnaligned = startAddr & 15;
    s32 endAddr = startAddr + size;
    s32 endUnaligned = endAddr & 15;

    if (endUnaligned != 0) {
        aLoadBuffer2(cmd++, (endAddr - endUnaligned), 0x380, 16);
        aDMEMMove(cmd++, dmem, 0x390, size);
        aDMEMMove(cmd++, 0x380 + endUnaligned, 0x390 + size, 16 - endUnaligned);
        size += 16 - endUnaligned;
        dmem = 0x390;
    }
    
    if (startUnaligned != 0) {
        aLoadBuffer2(cmd++, (startAddr - startUnaligned), 0x380, 16);
        aDMEMMove(cmd++, dmem, 0x380 + startUnaligned, size);

        size += startUnaligned;
        dmem = 0x380;
    }

    aSaveBuffer2(cmd++, startAddr - startUnaligned, dmem, size);
    return cmd;
}

static Acmd* __LoadAuxBuf(Acmd* cmd, u16 dmem, u16 startPos, s32 size, delay* del_p) {
    aLoadBuffer2(cmd++, &del_p->left_reverb_buf[startPos], dmem, size);
    aLoadBuffer2(cmd++, &del_p->right_reverb_buf[startPos], dmem + 0x1A0, size);
    return cmd;
}

static Acmd* __SaveAuxBuf(Acmd* cmd, u16 dmem, u16 startPos, s32 size, delay* del_p) {
    aSaveBuffer2(cmd++, &del_p->left_reverb_buf[startPos], dmem, size);
    aSaveBuffer2(cmd++, &del_p->right_reverb_buf[startPos], dmem + 0x1A0, size);
    return cmd;
}

static Acmd* Nas_LoadAuxBuffer_B(Acmd* cmd, s32 numSamplesPerUpdate, delay* del_p, s16 updateIdx) {
    if (del_p->downsample_rate == 1) {
        cmd = Nas_LoadAuxBuffer1_B(cmd, numSamplesPerUpdate, del_p, updateIdx);
    }

    return cmd;
}

static Acmd* Nas_LoadAuxBuffer(Acmd* cmd, s32 numSamplesPerUpdate, delay* del_p, s16 updateIdx) {
    if (del_p->downsample_rate == 1) {
        if (del_p->resample_effect_on) {
            cmd = Nas_LoadAuxBufferCH(cmd, numSamplesPerUpdate, del_p, updateIdx);
        } else {
            cmd = Nas_LoadAuxBuffer1(cmd, numSamplesPerUpdate, del_p, updateIdx);
        }
    } else {
        cmd = Nas_LoadAuxBufferC(cmd, numSamplesPerUpdate, del_p, updateIdx);
    }

    return cmd;
}

static Acmd* Nas_SaveAuxBuffer(Acmd* cmd, delay* del_p, s16 update_idx) {
    delayparam* param = &del_p->params[del_p->cur_frame][update_idx];
    s32 downsample_rate;
    s32 n_samples;

    switch (del_p->downsample_rate) {
        case 1:
            if (del_p->resample_effect_on) {
                cmd = Nas_SaveAuxBufferCH(cmd, del_p, update_idx);
            } else {
                cmd = __SaveAuxBuf(cmd, 0xC40, param->start_pos, param->size, del_p);
                if (param->wrapped_size != 0) {
                    cmd = __SaveAuxBuf(cmd, 0xC40 + param->size, 0, param->wrapped_size, del_p);
                }
            }
            break;
        default:
            downsample_rate = del_p->downsample_rate;
            n_samples = 13 * 16; // 16 = SAMPLES_PER_FRAME

            while (downsample_rate > 1) {
                aHalfCut(cmd++, 0xC40, 0xC40, n_samples);
                aHalfCut(cmd++, 0xDE0, 0xDE0, n_samples);
                n_samples >>= 1;
                downsample_rate >>= 1;
            }

            if (param->size != 0) {
                cmd = Nas_SaveBufferAuto(cmd, 0xC40, (u16)param->size, (s32)&del_p->left_reverb_buf[param->start_pos]);
                cmd = Nas_SaveBufferAuto(cmd, 0xDE0, (u16)param->size, (s32)&del_p->right_reverb_buf[param->start_pos]);
            }

            if (param->wrapped_size != 0) {
                cmd = Nas_SaveBufferAuto(cmd, 0xC40 + param->size, (u16)param->wrapped_size, (s32)&del_p->left_reverb_buf[0]);
                cmd = Nas_SaveBufferAuto(cmd, 0xDE0 + param->size, (u16)param->wrapped_size, (s32)&del_p->right_reverb_buf[0]);
            }
            break;
    }

    del_p->resample_flags = 0;
    return cmd;
}

static Acmd* Nas_SaveAuxBuffer_B(Acmd* cmd, delay* del_p, s16 update_idx) {
    delayparam* param = &del_p->sub_params[del_p->cur_frame][update_idx];
    
    cmd = __SaveAuxBuf(cmd, 0xC40, param->start_pos, param->size, del_p);
    if (param->wrapped_size != 0) {
        cmd = __SaveAuxBuf(cmd, 0xC40 + param->size, 0, param->wrapped_size, del_p);
    }

    return cmd;
}
