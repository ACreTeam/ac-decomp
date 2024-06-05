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
    /* 0x00 */ s16 key;
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

/* sizeof(group) == 0x160 */
typedef struct group_ {
    struct flags_ {
    /* 0x000 */ u32 flag0 : 1;
    } flags;

    /* 0x004 */ u8 state;
    /* 0x005 */ u8 unk4;
    /* 0x006 */ u8 unk5;
    /* 0x007 */ u16 tempo;
    /* 0x00C */ u8 unkC[0xD4];
    /* 0x0E0 */ int unkE0;
    /* 0x0E4 */ u8 E4[0x77];
    /* 0x15B */ s8 unk15B;
    /* 0x15C */ s8 unk15C;
} group;

/* sizeof(AudioGlobals) == 0x92b0 */
typedef struct AudioGlobals {
    /* 0x0000 */ u8 unk0[0x3788];
    /* 0x3788 */ group groups[5];
    /* 0x3E68 */ u8 unk3E68[0x5448];
} AudioGlobals;

/* sizeof(sub) >= 0xCD */
typedef struct sub_ {
 /* 0x00 */ s8 unk0[0xCB];
 /* 0xCB */ s8 unkCB;
 /* 0xCD */ s8 unkCC;
} sub; 


typedef union SOUNDID_ {
    struct {
        u8 wave_id;
        u8 inst_id;
        u8 _02;
        u8 _03;
    };

    u32 uint32;
} SOUNDID;

typedef struct note_ note;

#ifdef __cplusplus
}
#endif

#endif
