#ifndef AUDIOCOMMON_H
#define AUDIOCOMMON_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define S16_MIN (-0x8000)
#define S16_MAX (0x7FFF)

#define AUDIO_PRELOAD_SEQ (1 << 0)
#define AUDIO_PRELOAD_BANK (1 << 1)

#define AUDIO_ARAM_SIZE 0x400000 /* 4MB */
#define AUDIO_ARAM_HEAP_SIZE 0xC000

#define AUDIO_GROUP_MAX 5
#define AUDIO_SUBTRACK_NUM 16
#define AUDIO_NOTE_MAX 128

#define AUDIO_TATUMS_PER_BEAT 48

#define AUDIO_GROUP_ALL_SUBTRACKS (0xFFFF)

#define AUDIO_MUTE_FLAG_STOP_SAMPLES (1 << 3)
#define AUDIO_MUTE_FLAG_STOP_SUBTRACK (1 << 4)
#define AUDIO_MUTE_FLAG_SOFTEN (1 << 5)
#define AUDIO_MUTE_FLAG_STOP_NOTE (1 << 6)
#define AUDIO_MUTE_FLAG_STOP_SCRIPT (1 << 7)

#define NA_MAKE_COMMAND(a0, a1, a2, a3) \
    (u32)((((a0) & 0xFF) << 24) | (((a1) & 0xFF) << 16) | (((a2) & 0xFF) << 8) | (((a3) & 0xFF) << 0))

typedef enum DSPBUF_EVENTS {
    DSPBUF_EVENT_INIT = 0,
    DSPBUF_EVENT_FRAME_END = 1,
    DSPBUF_EVENT_MIX = 2,
} DSPBUF_EVENTS;

typedef enum SampleMedium {
    /* 0 */ MEDIUM_RAM,
    /* 1 */ MEDIUM_DISK,
    /* 2 */ MEDIUM_CART,
    /* 3 */ MEDIUM_DISK_DRIVE,
    /* 5 */ MEDIUM_RAM_UNLOADED = 5
} SampleMedium;

typedef enum AudioCacheType {
    /* 0 */ CACHE_TEMPORARY,
    /* 1 */ CACHE_PERSISTENT,
    /* 2 */ CACHE_EITHER,
    /* 3 */ CACHE_PERMANENT
} AudioCacheType;

typedef enum AudioCacheLoadType {
    /* 0 */ CACHE_LOAD_PERMANENT,
    /* 1 */ CACHE_LOAD_PERSISTENT,
    /* 2 */ CACHE_LOAD_TEMPORARY,
    /* 3 */ CACHE_LOAD_EITHER,
    /* 4 */ CACHE_LOAD_EITHER_NOSYNC
} AudioCacheLoadType;

typedef enum AudioLoadStatus {
    /* 0 */ LOAD_STATUS_NOT_LOADED,
    /* 1 */ LOAD_STATUS_IN_PROGRESS,
    /* 2 */ LOAD_STATUS_COMPLETE,
    /* 3 */ LOAD_STATUS_DISCARDABLE,
    /* 4 */ LOAD_STATUS_MAYBE_DISCARDABLE,
    /* 5 */ LOAD_STATUS_PERMANENT
} AudioLoadStatus;

typedef enum AdsrStatus {
    /* 0 */ ADSR_STATUS_DISABLED,
    /* 1 */ ADSR_STATUS_INITIAL,
    /* 2 */ ADSR_STATUS_START_LOOP,
    /* 3 */ ADSR_STATUS_LOOP,
    /* 4 */ ADSR_STATUS_FADE,
    /* 5 */ ADSR_STATUS_HANG,
    /* 6 */ ADSR_STATUS_DECAY,
    /* 7 */ ADSR_STATUS_RELEASE,
    /* 8 */ ADSR_STATUS_SUSTAIN
} AdsrStatus;

typedef enum PortamentoMode {
    /* 0 */ PORTAMENTO_MODE_OFF,
    /* 1 */ PORTAMENTO_MODE_1,
    /* 2 */ PORTAMENTO_MODE_2,
    /* 3 */ PORTAMENTO_MODE_3,
    /* 4 */ PORTAMENTO_MODE_4,
    /* 5 */ PORTAMENTO_MODE_5,
    /* 6 */ PORTAMENTO_MODE_6,
    /* 7 */ PORTAMENTO_MODE_7,
    /* 8 */ PORTAMENTO_MODE_8, // might be PORTAMENTO_MODE_NUM
} PortamentoMode;

typedef enum SampleBankTableType {
    /* 0 */ SEQUENCE_TABLE,
    /* 1 */ BANK_TABLE,
    /* 2 */ WAVE_TABLE
} SampleBankTableType;

typedef enum ExtDataType {
    EXT_TYPE_DATA,
    EXT_TYPE_SIZE,

    EXT_TYPE_NUM
} ExtDataType;

typedef enum SoundOutputMode {
    /* 0 */ SOUND_OUTPUT_STEREO,
    /* 1 */ SOUND_OUTPUT_HEADSET,
    /* 2 */ SOUND_OUTPUT_SURROUND,
    /* 3 */ SOUND_OUTPUT_MONO
} SoundOutputMode;

typedef enum SampleCodec {
    /* 0 */ CODEC_ADPCM, // 16 2-byte samples (32 bytes) compressed into 4-bit samples (8 bytes) + 1 header byte
    /* 1 */ CODEC_S8,    // 16 2-byte samples (32 bytes) compressed into 8-bit samples (16 bytes)
    /* 2 */ CODEC_S16_INMEMORY,
    /* 3 */ CODEC_SMALL_ADPCM, // 16 2-byte samples (32 bytes) compressed into 2-bit samples (4 bytes) + 1 header byte
    /* 4 */ CODEC_REVERB,
    /* 5 */ CODEC_S16
} SampleCodec;

typedef enum LpsCacheState {
    /* 0 */ LPS_CACHE_STATE_WAITING,
    /* 1 */ LPS_CACHE_STATE_START,
    /* 2 */ LPS_CACHE_STATE_LOADING,
    /* 3 */ LPS_CACHE_STATE_DONE
} LpsCacheState;

#define VOICE_TYPE_PERCUSSION 0
#define VOICE_TYPE_SOUND_EFF 1
#define VOICE_TYPE_INSTRUMENT_START 2

#define AUDIO_SWEEP_IS_SPECIAL(s) ((s).mode & 0x80)
#define AUDIO_SWEEP_MODE(s) ((s).mode & ~0x80)

#define AUDIO_NOTE_RELEASE (1 << 0)
#define AUDIO_NOTE_SAMPLE_NOTES (1 << 1)

#define AUDIOCMD_ALL_GROUPS 0xFF
#define AUDIOCMD_ALL_SUBTRACKS 0xFF

typedef enum GroupState {
    /* 0 */ GROUP_STATE_0,
    /* 1 */ GROUP_STATE_FADE_IN,
    /* 2 */ GROUP_STATE_FADE_OUT
} GroupState;

/* Most of these are from the MM decomp */
typedef enum AudioCmd {
    /* 0x00 */ AUDIOCMD_NOOP,

    // SubTrack Commands
    /* 0x01 */ AUDIOCMD_OP_SUB_SET_VOL_SCALE,
    /* 0x02 */ AUDIOCMD_OP_SUB_SET_VOL,
    /* 0x03 */ AUDIOCMD_OP_SUB_SET_PAN,
    /* 0x04 */ AUDIOCMD_OP_SUB_SET_FREQ_SCALE,
    /* 0x05 */ AUDIOCMD_OP_SUB_SET_REVERB_VOLUME,
    /* 0x06 */ AUDIOCMD_OP_SUB_SET_PORT,
    /* 0x07 */ AUDIOCMD_OP_SUB_SET_PAN_WEIGHT,
    /* 0x08 */ AUDIOCMD_OP_SUB_SET_MUTE,
    /* 0x09 */ AUDIOCMD_OP_SUB_SET_MUTE_FLAGS,
    /* 0x0A */ AUDIOCMD_OP_SUB_SET_VIBRATO_DEPTH,
    /* 0x0B */ AUDIOCMD_OP_SUB_SET_VIBRATO_RATE,
    /* 0x0C */ AUDIOCMD_OP_SUB_SET_COMB_FILTER_SIZE,
    /* 0x0D */ AUDIOCMD_OP_SUB_SET_COMB_FILTER_GAIN,
    /* 0x0E */ AUDIOCMD_OP_SUB_SET_STEREO,
    /* 0x0F */ AUDIOCMD_OP_SUB_SET_SET_START_POS,
    /* 0x10 */ AUDIOCMD_OP_SUB_SET_SFX_STATE,
    /* 0x11 */ AUDIOCMD_OP_SUB_SET_REVERB_INDEX,
    /* 0x12 */ AUDIOCMD_OP_SUB_SET_SURROUND_EFFECT_INDEX,
    /* 0x13 */ AUDIOCMD_OP_SUB_SET_FILTER,
    /* 0x14 */ AUDIOCMD_OP_SUB_SET_GAIN,
    /* 0x15 */ AUDIOCMD_OP_SUB_SET_TRANSPOSITION,

    // Group Commands
    /* 0x41 */ AUDIOCMD_OP_GRP_FADE_VOLUME_SCALE = 0x41,
    /* 0x46 */ AUDIOCMD_OP_GRP_SET_PORT = 0x46,
    /* 0x47 */ AUDIOCMD_OP_GRP_SET_TEMPO,
    /* 0x48 */ AUDIOCMD_OP_GRP_SET_TRANSPOSITION,
    /* 0x49 */ AUDIOCMD_OP_GRP_CHANGE_TEMPO,
    /* 0x4A */ AUDIOCMD_OP_GRP_FADE_TO_SET_VOLUME,
    /* 0x4B */ AUDIOCMD_OP_GRP_FADE_TO_SCALED_VOLUME,
    /* 0x4C */ AUDIOCMD_OP_GRP_RESET_VOLUME,
    /* 0x4D */ AUDIOCMD_OP_GRP_SET_BEND,
    /* 0x4E */ AUDIOCMD_OP_GRP_CHANGE_TEMPO_TICKS,

    // System Commands
    /* 0x81 */ AUDIOCMD_PRELOAD_SEQ = 0x81,
    /* 0x82 */ AUDIOCMD_START_SEQ,
    /* 0x83 */ AUDIOCMD_STOP_SEQ,
    /* 0x85 */ AUDIOCMD_START_SEQ_SKIP = 0x85,
    /* 0x90 */ AUDIOCMD_SET_GROUP_MASK = 0x90,

    /* 0xE0 */ AUDIOCMD_SET_PERC_BANK = 0xE0,
    /* 0xE1 */ AUDIOCMD_SET_EFFECT_BANK,
    /* 0xE2 */ AUDIOCMD_SET_VOICE_BANK,
    /* 0xE3 */ AUDIOCMD_CLEAR_STAY_CACHE,
    /* 0xE4 */ AUDIOCMD_SET_CALLBACK,
    /* 0xE5 */ AUDIOCMD_SET_EXTERNAL_POINTER,
    /* 0xE6 */ AUDIOCMD_SET_DELAY_LINE_PARAM,

    /* 0xF0 */ AUDIOCMD_SET_SOUND_MODE = 0xF0,
    /* 0xF1 */ AUDIOCMD_MUTE,
    /* 0xF2 */ AUDIOCMD_UNMUTE,
    /* 0xF3 */ AUDIOCMD_LOAD_VOICE_INSTRUMENT,
    /* 0xF4 */ AUDIOCMD_PRELOADWAVE_BG,
    /* 0xF5 */ AUDIOCMD_PRELOADBANK_BG,
    /* 0xF6 */ AUDIOCMD_FLUSH_BANKS,
    /* 0xF8 */ AUDIOCMD_SYS_STOP_PROCESSING = 0xF8,
    /* 0xF9 */ AUDIOCMD_RESET_AUDIO_HEAP,
    /* 0xFA */ AUDIOCMD_MAIN_GROUP_SUBPORT_CMD,
    /* 0xFB */ AUDIOCMD_SET_VFRAME_CALLBACK,
    /* 0xFC */ AUDIOCMD_PRELOADSEQ_BG,
    /* 0xFD */ AUDIOCMD_MAIN_GROUP_SET_FREQ_SCALE,
    /* 0xFE */ AUDIOCMD_FORCE_STOP_ALL_GROUPS,
    /* 0xFF */ AUDIOCMD_MAIN_GROUP_SET_VOL_SCALE
} AudioCmd;

typedef enum SeqCmd {
    SEQCMD_BRANCH_REL_NOT_EQ_ZERO = 0xF2,
    SEQCMD_BRANCH_REL_EQ_ZERO = 0xF3,
    SEQCMD_BRANCH_REL = 0xF4,
    SEQCMD_BRANCH_ABS_GREQ_ZERO = 0xF5,
    SEQCMD_BREAK = 0xF6,
    SEQCMD_LOOP_END = 0xF7,
    SEQCMD_LOOP = 0xF8,
    SEQCMD_BRANCH_ABS_NOT_EQ_ZERO = 0xF9,
    SEQCMD_BRANCH_ABS_EQ_ZERO = 0xFA,
    SEQCMD_BRANCH_ABS = 0xFB,
    SEQCMD_CALL = 0xFC,
    SEQCMD_DELAY_N_FRAMES = 0xFD,
    SEQCMD_DELAY_1_FRAME = 0xFE,
    SEQCMD_STOP_SCRIPT = 0xFF,
} SeqCmd;

typedef enum AUDIO_CALLBACKS {
    /* 0x00 */ AUDIO_CALLBACK_SEQ_0,
    /* 0x01 */ AUDIO_CALLBACK_SEQ_1,
    /* 0x02 */ AUDIO_CALLBACK_SEQ_2,
    /* 0x03 */ AUDIO_CALLBACK_SEQ_3,
    /* 0xFE */ AUDIO_CALLBACK_DACOUT = 0xFE,
    /* 0xFF */ AUDIO_CALLBACK_SOUND
} AUDIO_CALLBACKS;

#define NA_COMMAND_AUDIO_START_SEQ(groupID, seqID, fadeinTime) \
    Nap_SetS32(NA_MAKE_COMMAND(AUDIOCMD_START_SEQ, groupID, seqID, 0), fadeinTime)

#define NA_COMMAND_AUDIO_STOP_SEQ(groupID, fadeoutTime) \
    Nap_SetS32(NA_MAKE_COMMAND(AUDIOCMD_STOP_SEQ, groupID, 0, 0), fadeoutTime)

#define NA_COMMAND_AUDIO_GRP_FADE_VOLUME_SCALE(groupID, volumeScale) \
    Nap_SetF32(NA_MAKE_COMMAND(AUDIOCMD_OP_GRP_FADE_VOLUME_SCALE, groupID, 0, 0), volumeScale)

#define NA_COMMAND_AUDIO_SET_SOUND_MODE(mode) Nap_SetS32(NA_MAKE_COMMAND(AUDIOCMD_SET_SOUND_MODE, 0, 0, 0), mode)

#define NA_COMMAND_AUDIO_CLEAR_STAY_CACHE(type) Nap_SetS32(NA_MAKE_COMMAND(AUDIOCMD_CLEAR_STAY_CACHE, 0, 0, 0), type)

#define NA_COMMAND_AUDIO_SUBTRACK_SET_MUTE(groupMask, subtrack, muted) \
    Nap_SetS8(NA_MAKE_COMMAND(AUDIOCMD_OP_SUB_SET_MUTE, groupMask, subtrack, 0), muted)

#define NA_COMMAND_AUDIO_SUBTRACK_SET_VOL_SCALE(group, subtrack, volume) \
    Nap_SetF32(NA_MAKE_COMMAND(AUDIOCMD_OP_SUB_SET_VOL_SCALE, group, subtrack, 0), volume)

#define NA_COMMAND_AUDIO_SUBTRACK_SET_FREQ_SCALE(group, subtrack, freqScale) \
    Nap_SetF32(NA_MAKE_COMMAND(AUDIOCMD_OP_SUB_SET_FREQ_SCALE, group, subtrack, 0), freqScale)

#define NA_COMMAND_AUDIO_SUBTRACK_SET_PAN(group, subtrack, pan) \
    Nap_SetS8(NA_MAKE_COMMAND(AUDIOCMD_OP_SUB_SET_PAN, group, subtrack, 0), pan)

#define NA_COMMAND_AUDIO_SUBTRACK_SET_PORT(group, subtrack, port, value) \
    Nap_SetS8(NA_MAKE_COMMAND(AUDIOCMD_OP_SUB_SET_PORT, group, subtrack, port), value)

#define NA_COMMAND_AUDIO_SUBTRACK_REVERB_VOLUME(group, subtrack, reverb) \
    Nap_SetS8(NA_MAKE_COMMAND(AUDIOCMD_OP_SUB_SET_REVERB_VOLUME, group, subtrack, 0), reverb)

#define NA_COMMAND_AUDIO_GROUP_SET_PORT(group, port, value) \
    Nap_SetS8(NA_MAKE_COMMAND(AUDIOCMD_OP_GRP_SET_PORT, group, 0, port), value)

#define NA_COMMAND_AUDIO_GROUP_SET_MASK(group, mask) \
    Nap_SetU16(NA_MAKE_COMMAND(AUDIOCMD_SET_GROUP_MASK, group, 0, 0), mask)

#define NA_COMMAND_AUDIO_SUBTRACK_SET_FILTER(group, subtrack, filterCutoff, pFilter) \
    Nap_SetS32(NA_MAKE_COMMAND(AUDIOCMD_OP_SUB_SET_FILTER, group, subtrack, filterCutoff), (s32)pFilter)

#ifdef __cplusplus
}
#endif

#endif
