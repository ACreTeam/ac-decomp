#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"
#include "dolphin/os.h"

#define AUDIO_THREAD_FLAG_DVD (1 << 0)
#define AUDIO_THREAD_FLAG_AUDIO (1 << 1)
#define AUDIO_THREAD_FLAG_NEOS (1 << 2)

extern volatile int intcount;

extern void NeosSync(void);

#ifdef __cplusplus
extern "C" {
#endif

extern void DspSyncCountClear(int count);
extern int DspSyncCountCheck(void);
extern void StartAudioThread(void* pHeap, s32 heapSize, u32 aramSize, u32 flags);

#ifdef __cplusplus
}
#endif

#endif
