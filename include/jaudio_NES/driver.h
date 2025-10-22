#ifndef DRIVER_H
#define DRIVER_H

#include "PR/abi.h"
#include "types.h"
#include "jaudio_NES/audiowork.h"

// size of a single sample point
#define SAMPLE_SIZE (s32)sizeof(s16)

// Samples are processed in groups of 16 called a "frame"
#define SAMPLES_PER_FRAME ADPCMFSIZE

// The length of one left/right channel is 13 frames
#define DMEM_1CH_SIZE (13 * SAMPLES_PER_FRAME * SAMPLE_SIZE) // 0x1A0
// Both left and right channels
#define DMEM_2CH_SIZE (2 * DMEM_1CH_SIZE) // 0x340

extern Acmd* Nas_smzAudioFrame(Acmd* cmds, s32* processed_cmds, s16* pSamples, s32 nSamples);
extern Acmd* Nas_DriveRsp(s16* aiBuf, s32 aiBufLen, Acmd* cmd, s32 updateIndex);
extern Acmd* Nas_SynthMain(s32 chan_id, commonch* common, driverch* driver, s16* samples, s32 samples_per_update, Acmd* cmd, s32 update_idx);
extern Acmd* Nas_Synth_Resample(Acmd* cmd, driverch* driver, s32 size, u16 frequencyFixedPoint, u16 sampleDmemBeforeResampling, s32 flags);
extern Acmd* Nas_DolbySurround(Acmd* cmd, commonch* common, driverch* driver, s32 samples_per_update, s32 dmem, s32 flags);
extern Acmd* Nas_Synth_Envelope(Acmd* cmd, commonch* common, driverch* driver, s32 samples_per_update, u16 dmem, s32 haasEffectDelaySide, s32 flags);
extern Acmd* Nas_Synth_Delay(Acmd* cmd, commonch* common, driverch* driver, s32 size, s32 flags, s32 haasEffectDelaySide);

#endif
