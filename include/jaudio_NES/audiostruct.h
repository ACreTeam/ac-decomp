#ifndef AUDIOSTRUCT_H
#define AUDIOSTRUCT_H

#include "types.h"

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

/* sizeof(Acmd) == 0x4*/
typedef union Acmd {
    struct {
        /* 0x00 */ u8 p0;
        /* 0x01 */ u8 p1;
        /* 0x02 */ u8 p2;
        /* 0x03 */ u8 p3;
    };
    /* 0x00 */ u32 uint32;
} Acmd;

/* sizeof(ALHeap) == 0x14 */
typedef struct ALHeap {
    /* 0x00 */ u8* base;
    /* 0x04 */ u8* current;
    /* 0x08 */ int length;
    /* 0x0C */ u32 count;
    /* 0x10 */ u8* last;
} ALHeap;

/* sizeof(ArcHeader) == 0x10 */
typedef struct ArcHeader_ {
    /* 0x00 */ s16 numEntries;
    /* 0x02 */ u16 _02;
    /* 0x04 */ u8* pData;
    /* 0x08 */ u8 copy;
} ArcHeader ATTRIBUTE_ALIGN(8);

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
