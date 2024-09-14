#ifndef SYSTEM_H
#define SYSTEM_H

#include "types.h"
#include "libultra/libultra.h"

typedef enum SET_EXT_POINTER_TYPE {
    EXT_POINTER_TYPE_ADDR,
    EXT_POINTER_TYPE_SIZE,

    EXT_POINTER_TYPE_NUM
} SET_EXT_POINTER_TYPE;

extern void Nas_InitAudio(u64* acmdBuf, s32 acmdBufSize);
extern void Nas_FastCopy(u8* SrcAddr, u8* DestAdd, size_t size, s32 medium);
extern void Nas_StartMySeq(s32 group, s32 seq, s32 arg);
extern void Nas_StartSeq_Skip(s32 group, s32 seq, s32 skip_ticks);

extern s32 Nas_LoadVoice(s32 progId, s32 instId, s32 percId);

extern void Nas_PreLoadSeq(s32 seq, s32 flags, s32 param, OSMesgQueue* mq);

extern s32 Nas_PreLoadWave_BG(s32 bankId, s32 param2, s32 param3, OSMesgQueue* mq);
extern s32 Nas_PreLoadBank_BG(s32 bankId, s32 param2, s32 param3, OSMesgQueue* mq);
extern s32 Nas_PreLoadSeq_BG(s32 seqId, s32 param2, s32 param3, OSMesgQueue* mq);

extern void Nas_FlushBank(s32 seqId);

extern void Nas_SetExtPointer(s32 type, s32 idx, s32 set_type, s32 param);

extern void Nas_WaveDmaFrameWork(void);
extern void Nas_BgDmaFrameWork(s32 reset_status);
extern void MK_FrameWork(void);

extern BOOL Nas_CheckIDseq(s32 id);
extern BOOL Nas_CheckIDbank(s32 id);

extern void Nas_WriteIDseq(s32 id, s32 type);
extern void Nas_WriteIDbank(s32 id, s32 type);

extern s32 VoiceLoad(s32 bank_id, u32 inst_id, s8* done_p);
extern s32 SeqLoad(s32 seq_id, u8* ram_addr, s8* done_p);
extern void MK_load(s32 type, s32 id, u8* done_p);

extern BOOL AUDIO_SYSTEM_READY;

#endif
