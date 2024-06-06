#ifndef AUDIOSTRUCT_H
#define AUDIOSTRUCT_H

#include "types.h"
#include "jaudio_NES/audiocommon.h"
#include "PR/abi.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct chnode_ chnode;
typedef struct link_ link;

/* sizeof(struct link_) == 0x10 */
struct link_ {
    /* 0x00 */ link* next;
    /* 0x04 */ link* prev;
    union {
        /* 0x08 */ int numAfter; /* when link is head */
        /* 0x08 */ void* pData;  /* when link is node */
    };
    /* 0x0C */ chnode* pNode;
};

/* sizeof(struct chnode_) == 0x40 */
struct chnode_ {
    /* 0x00 */ link globalUse;
    /* 0x10 */ link globalFree;
    /* 0x20 */ link globalRelease;
    /* 0x30 */ link globalReleaseWait;
};

/* forward declared */
typedef struct note_ note;
typedef struct channel_ channel;
typedef struct group_ group;

/* sizeof(struct AudioPort_) == 0x8 */
typedef struct AudioPort_ {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 groupID;
    /* 0x02 */ u8 subtrackID;
    /* 0x03 */ u8 _03;
    /* 0x04 */ u32 param;
} AudioPort;

/* sizeof(ALHeap) == 0x14 */
typedef struct ALHeap {
    /* 0x00 */ u8* base;
    /* 0x04 */ u8* current;
    /* 0x08 */ int length;
    /* 0x0C */ u32 count;
    /* 0x10 */ u8* last;
} ALHeap;

/* sizeof(ArcEntry) == 0x10 */
typedef struct ArcEntry_ {
    /* 0x00 */ u32 addr;
    /* 0x04 */ size_t size;
    /* 0x08 */ s8 medium;
    /* 0x09 */ s8 cacheType;
    /* 0x0A */ s16 param0;
    /* 0x0C */ s16 param1;
    /* 0x0E */ s16 param2;
} ArcEntry;

/* sizeof(ArcHeader) == [0x10, 0x10+entries*0x10] */
typedef struct ArcHeader_ {
    /* 0x00 */ s16 numEntries;
    /* 0x02 */ s16 _02;
    /* 0x04 */ u8* pData;
    /* 0x08 */ u8 copy;
    /* 0x09 */ u8 pad[7];
    /* 0x10 */ ArcEntry entries[]; /* variable size */
} ArcHeader;

/* sizeof(AutoHeapstrc) == 0xC */
typedef struct AutoHeapstrc_ {
    /* 0x00 */ int seqLen;
    /* 0x04 */ int bankLen;
    /* 0x08 */ int waveLen;
} AutoHeapstrc;

/* sizeof(DataHeapstrc) == 0x8 */
typedef struct DataHeapstrc_ {
    /* 0x00 */ int dataLen;
    /* 0x04 */ int autoLen;
} DataHeapstrc;

/* sizeof(delay) == 0x30 */
typedef struct delay_ {
    /* 0x00 */ u8 _00[0x30 - 0x00]; /* TODO */
} delay;

/* sizeof(commonch) == 0x20 */
typedef struct commonch_ {
    /* 0x00 */ u8 _00;
    /* 0x01 */ u8 _01;
    /* 0x02 */ u8 _02;
    /* 0x03 */ u8 _03;
    /* 0x04 */ u8 _04;
    /* 0x05 */ u8 _05;
    /* 0x06 */ u8 _06;
    /* 0x07 */ u8 _07;
    /* 0x08 */ u16 _08;
    /* 0x0A */ u16 _0A;
    /* 0x0C */ u16 _0C;
    /* 0x0E */ u16 _0E;
    /* 0x10 */ void* _10;
    /* 0x14 */ int _14;
    /* 0x18 */ u8 _18;
    /* 0x19 */ u8 _19;
    /* 0x1A */ u8 _1A;
    /* 0x1B */ u8 _1B[4];
} commonch;

/* sizeof(driverch) == 0x18 */
typedef struct driverch_ {
    /* 0x00 */ u8 _00;
    /* 0x01 */ u8 _01;
    /* 0x02 */ u8 _02;
    /* 0x03 */ u8 _03;
    /* 0x04 */ u8 _04;
    /* 0x05 */ u8 _05;
    /* 0x06 */ u8 _06;
    /* 0x07 */ u8 _07;
    /* 0x08 */ u16 _08;
    /* 0x0A */ u16 _0A;
    /* 0x0C */ u32 _0C;
    /* 0x10 */ u8* _10;
    /* 0x14 */ s16 _14;
    /* 0x16 */ s16 _16;
} driverch;

/* sizeof(phase) == 0x01 */
typedef struct phase_ {
    /* 0x00 */ u8 _00;
} phase;

/* sizeof(drvparam) == 0x1C */
typedef struct drvparam_ {
    /* 0x00 */ u8 _00;
    /* 0x01 */ u8 _01;
    /* 0x02 */ u8 _02;
    /* 0x03 */ u8 _03;
    /* 0x04 */ phase phase;
    /* 0x08 */ f32 pitch;
    /* 0x0C */ f32 volume;
    /* 0x10 */ int _10;
    /* 0x14 */ int _14;
    /* 0x18 */ u8 _18;
    /* 0x19 */ u8 _19;
    /* 0x1A */ u16 _1A;
} drvparam;

/* sizeof(envdat) == 0x04 */
typedef struct envdat_ {
    /* 0x00 */ s16 delay;
    /* 0x02 */ s16 value;
} envdat;

/* sizeof(envp) == 0x20 */
typedef struct envp_ {
    /* 0x00 */ u8 state;
    /* 0x01 */ u8 envelope_table_row;
    /* 0x02 */ s16 key;
    /* 0x04 */ f32 min_vol;
    /* 0x08 */ f32 attack;
    /* 0x0C */ f32 decay_release;
    /* 0x10 */ f32 volume;
    /* 0x14 */ f32 target_volume;
    /* 0x18 */ f32 _18;
    /* 0x1C */ envdat* pEnvData;
} envp;

/* sizeof(env) == 0x08 */
typedef struct env_ {
    /* 0x00 */ u8 decay_idx;
    /* 0x01 */ u8 sustain;
    /* 0x04 */ envdat* envelope;
} env;

/* sizeof(vibparam) == 0x0E */
typedef struct vibparam_ {
    /* 0x00 */ u16 rate_start;
    /* 0x02 */ u16 depth_start;
    /* 0x04 */ u16 rate_target;
    /* 0x06 */ u16 depth_target;
    /* 0x08 */ u16 rate_change_delay;
    /* 0x0A */ u16 depth_change_delay;
    /* 0x0C */ u16 delay;
} vibparam;

typedef struct voicetable_ {

} voicetable;

/* sizeof(seqplayer) == 0x1C */
typedef struct seqplayer_ {
    /* 0x00 */ u8* pc;
    /* 0x04 */ u8* stack[4];
    /* 0x14 */ u8 remaining_loop_iters[4];
    /* 0x18 */ u8 depth;
    /* 0x19 */ s8 value;
} seqplayer;

/* SubTrack struct */
/* sizeof(sub) == 0xE0 */
typedef struct sub_ {
    /* 0x00 */ u8 enabled : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 stop_script : 1;
    /* 0x00 */ u8 muted : 1;
    /* 0x00 */ u8 has_instrument : 1;
    /* 0x00 */ u8 stereo_effects : 1;
    /* 0x00 */ u8 large_notes : 1;
    /* 0x00 */ u8 unused : 1;

    union {
        struct {
            /* 0x01 */ u8 frequency_scale : 1;
            /* 0x01 */ u8 volume : 1;
            /* 0x01 */ u8 pan : 1;
        } flags;
        /* 0x01 */ u8 as_byte;
    } changes;

    /* 0x02 */ u8 note_alloc_policy;
    /* 0x03 */ u8 mute_flags;
    /* 0x04 */ u8 target_reverb_vol;
    /* 0x05 */ u8 note_priority;
    /* 0x06 */ u8 priority2;
    /* 0x07 */ u8 inst_id;
    /* 0x08 */ u8 reverb_idx;
    /* 0x09 */ u8 book_ofs;
    /* 0x0A */ u8 new_pan;
    /* 0x0B */ u8 pan_channel_weight;
    /* 0x0C */ u8 gain;
    /* 0x0D */ u8 velocity_random_variance;
    /* 0x0E */ u8 gate_time_random_variance;
    /* 0x0F */ u8 comb_filter_size;
    /* 0x10 */ u8 surround_effect_idx;
    /* 0x11 */ u8 channel_idx;
    /* 0x12 */ vibparam vibrato_params;
    /* 0x20 */ u16 delay;
    /* 0x22 */ u16 comb_filter_gain;
    /* 0x24 */ u16 unk24;
    /* 0x26 */ s16 inst_or_wave;
    /* 0x28 */ s16 transposition;
    /* 0x2C */ f32 volume_scale;
    /* 0x30 */ f32 volume;
    /* 0x34 */ s32 pan;
    /* 0x38 */ f32 applied_volume;
    /* 0x3C */ f32 frequency_scale;
    /* 0x40 */ u8 (*dyn_tbl)[][2];
    /* 0x44 */ channel* channel;
    /* 0x48 */ note* note;
    /* 0x4C */ voicetable* voicetable;
    /* 0x50 */ group* group;
    /* 0x54 */ struct note_* note_layers[4];
    /* 0x64 */ seqplayer seq_player;
    /* 0x80 */ env asdr_env;
    /* 0x88 */ chnode channel_node;
    /* 0xC8 */ s8 seq_script_io[8];
    /* 0xD0 */ u8* sfx_state;
    /* 0xD4 */ s16* filter;
    /* 0xD8 */ phase stereo_phase;
    /* 0xDC */ s32 sample_start_pos;
} sub;

/* sizeof(group) == 0x160 */
struct group_ {
    struct flags_ {
        /* 0x000 */ u8 enabled : 1;
        /* 0x000 */ u8 finished : 1;
        /* 0x000 */ u8 muted : 1;
        /* 0x000 */ u8 sequence_dma_in_progress : 1;
        /* 0x000 */ u8 bank_dma_in_progress : 1;
        /* 0x000 */ u8 recalculate_volume : 1;
        /* 0x000 */ u8 stop_seq_script : 1;
        /* 0x000 */ u8 apply_bend : 1;
    } flags;

    /* 0x001 */ u8 state;
    /* 0x002 */ u8 note_alloc_policy;
    /* 0x003 */ u8 mute_flags;
    /* 0x004 */ u8 seq_id;
    /* 0x005 */ u8 default_bank;
    /* 0x006 */ u8 unk006;
    /* 0x007 */ s8 group_idx;
    /* 0x008 */ u16 tempo;
    /* 0x00A */ u16 tempo_acceleration;
    /* 0x00C */ s16 tempo_change;
    /* 0x00E */ s16 transposition;
    /* 0x010 */ u16 delay;
    /* 0x012 */ u16 fade_timer;
    /* 0x014 */ u16 stored_fade_timer;
    /* 0x016 */ u16 unk016;
    /* 0x018 */ u8* seq_data;
    /* 0x01C */ f32 fade_volume;
    /* 0x020 */ f32 fade_velocity;
    /* 0x024 */ f32 volume;
    /* 0x028 */ f32 mute_volume_scale;
    /* 0x02C */ f32 fade_volume_scale;
    /* 0x030 */ f32 applied_fade_volume;
    /* 0x034 */ f32 bend;
    /* 0x038 */ sub* subtracks[16];
    /* 0x078 */ seqplayer seq_player;
    /* 0x094 */ u8* short_note_velocity_tbl;
    /* 0x098 */ u8* short_note_gate_time_tbl;
    /* 0x09C */ u8 note_pool[0x40]; /* TODO: this is a struct according to MM decomp */
    /* 0x0DC */ s32 skip_ticks;
    /* 0x0E0 */ s32 script_counter; /* is u32 in MM decomp */
    /* 0x0E4 */ u8 unkE4[0x158 - 0x0E4];
    /* 0x158 */ s8 seq_script_io[8];
};

/* sizeof(note) == 0x90 */
struct note_ {
    u8 _00[0x90 - 0x00];
};

/* sizeof(AudioGlobals) == 0x92b0 */
typedef struct AudioGlobals {
    /* 0x0000 */ u8 unk0[0x2850 - 0x0000];
    /* 0x2850 */ ArcHeader* seq_header;
    /* 0x2854 */ ArcHeader* bank_header;
    /* 0x2858 */ ArcHeader* wave_header;
    /* 0x285C */ ArcHeader* data_header;
    /* 0x2860 */ u16* map_header;
    /* 0x2864 */ u8 unk2864[0x3788 - 0x2864];
    /* 0x3788 */ group groups[5];
    /* 0x3E68 */ u8 unk3E68[0x5448];
} AudioGlobals;

typedef union SOUNDID_ {
    struct {
        u8 wave_id;
        u8 inst_id;
        u8 _02;
        u8 _03;
    };

    u32 uint32;
} SOUNDID;

#ifdef __cplusplus
}
#endif

#endif
