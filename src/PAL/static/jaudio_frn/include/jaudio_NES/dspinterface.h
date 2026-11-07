#ifndef _JAUDIO_DSPINTERFACE_H
#define _JAUDIO_DSPINTERFACE_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"

typedef struct DSPMixerChannel DSPMixerChannel;
typedef struct DSPchannel_ DSPchannel_;
typedef struct FXDestination FXDestination;
typedef struct FXBuffer FXBuffer;

// A lot of u16s in these DSP structs act like BOOL, so lets codify it.
typedef u16 DSPBOOL;
#define DSP_TRUE  ((DSPBOOL)1)
#define DSP_FALSE ((DSPBOOL)0)

/////////// JAUDIO DSP INTERFACE DEFINITIONS ///////////
// Global functions (all C++, so no extern C wrap).

DSPchannel_* GetDspHandle(u8 idx);
FXBuffer* GetFxHandle(u8 idx);
void DSP_SetPitch(u8 idx, u16 pitch);
void DSP_SetMixerInitDelayMax(u8 idx, u8 initDelayMax);
void DSP_SetMixerInitVolume(u8 idx, u8 mixer, s16 volume, u8 param_4);
void DSP_SetMixerVolume(u8 idx, u8 mixer, s16 volume, u8 param_4);
void DSP_SetOscInfo(u8 idx, u32 samplesSourceType);
void DSP_SetPauseFlag(u8 idx, u8 pauseFlag);
void DSP_SetWaveInfo(u8 idx, Wave_* wave, u32 baseAddress);
void DSP_SetBusConnect(u8 idx, u8 mixer, u8 busConnect);
void DSP_PlayStop(u8 idx);
void DSP_AllocInit(u8 idx);
void DSP_PlayStart(u8 idx);
void DSP_SetDistFilter(u8 idx, s16 distFilter);
void DSP_SetFilterTable(s16* dst, s16* src, u32 len);
void DSP_SetIIRFilterParam(u8 idx, s16* param_2);
void DSP_SetFIR8FilterParam(u8 idx, s16* param_2);
void DSP_SetFilterMode(u8 idx, u16 filterMode);
void DSP_InitFilter(u8 idx);
void DSP_FlushBuffer();
void DSP_FlushChannel(u8 idx);
void DSP_InvalChannelAll();
void DSP_ClearBuffer();
void DSP_SetupBuffer();
void DSP_InitBuffer();

///////////////////////////////////////////////////////////////////////////////
// Based on `ZeldaAudioRenderer::VPB` from Dolphin Emulator. Thank you all!

/**
 * @brief TODO.
 */
struct DSPMixerChannel {
	u16 id;            // _00
	u16 targetVolume;  // _02
	u16 currentVolume; // _04
	u16 level;         // _06
};

/**
 * @brief TODO.
 */
struct DSPchannel_ {
	DSPBOOL enabled;                // _00 - DSP_AllocInit, DSP_PlayStop, DSP_PlayStart
	DSPBOOL done;                   // _02 - DSP_AllocInit
	u16 resamplingRatio;            // _04 - DSP_SetPitch
	u16 _06;                        // _06
	DSPBOOL resetVpb;               // _08 - DSP_PlayStart
	DSPBOOL endReached;             // _0A
	DSPBOOL useConstantSample;      // _0C - DSP_SetPauseFlag
	u16 samplesToKeepCount;         // _0E - DSP_SetMixerInitDelayMax
	DSPMixerChannel mixChannels[6]; // _10 - DSP_SetMixerInitVolume, DSP_SetMixerVolume, DSP_SetBusConnect
	u8 _40[0x50 - 0x40];            // _40
	u16 dolbyVoicePosition;         // _50
	s16 dolbyReverbFactor;          // _52
	s16 dolbyVolumeCurrent;         // _54
	s16 dolbyVolumeTarget;          // _56
	DSPBOOL useDolbyVolume;         // _58
	u16 _5A;                        // _5A
	u16 _5C;                        // _5C
	u16 _5E;                        // _5E
	u16 currentPosFrac;             // _60 - DSP_PlayStart
	u16 _62;                        // _62
	u16 afcRemainingDecodedSamples; // _64 - DSP_SetOscInfo, DSP_SetWaveInfo
	s16 constantSample;             // _66 - DSP_PlayStart
	u32 currentPosition;            // _68 - DSP_PlayStart
	u16 samplesBeforeLoop;          // _6C
	u16 _6E;                        // _6E
	u32 currentAramAddr;            // _70
	u32 remainingLength;            // _74
	s16 resampleBuffer[4];          // _78 - DSP_PlayStart
	u16 variableFirHistory[20];     // _80 - DSP_PlayStart
	s16 biquadHistory[4];           // _A8 - DSP_PlayStart
	u16 afcRemainingSamples[16];    // _B0 - DSP_SetWaveInfo
	s16 lowPassHistory[2];          // _D0
	u8 _D4[0x100 - 0xD4];           // _D4
	u16 samplesSourceType;          // _100 - DSP_SetOscInfo, DSP_SetWaveInfo
	DSPBOOL isLooping;              // _102 - DSP_SetWaveInfo
	s16 loopYN1;                    // _104 - DSP_SetWaveInfo
	s16 loopYN2;                    // _106 - DSP_SetWaveInfo
	s16 filterMode;                 // _108 - DSP_SetFilterMode
	DSPBOOL endRequested;           // _10A - DSP_AllocInit, DSP_SetMixerVolume
	u32 _10C;                       // _10C - DSP_PlayStart
	u32 loopAddress;                // _110 - DSP_SetWaveInfo
	u32 loopStartPosition;          // _114 - DSP_SetWaveInfo
	u32 baseAddress;                // _118 - DSP_SetOscInfo, DSP_SetWaveInfo
	u32 _11C;                       // _11C - DSP_SetWaveInfo
	s16 variableFirCoeffs[20];      // _120 - DSP_InitFilter, DSP_SetFIR8FilterParam
	s16 biquadFilterCoeffs[4];      // _148 - DSP_InitFilter, DSP_SetIIRFilterParam
	s16 lowPassCoeff;               // _150 - DSP_InitFilter, DSP_SetDistFilter
	u8 padding[0x180 - 0x152];      // _152
};

///////////////////////////////////////////////////////////////////////////////
// Based on `DSP::HLE::ReverbPB` from Dolphin Emulator. Thank you all!

/**
 * @brief TODO. Does this name make sense?  Dolphin calls this "Destination"
 */
struct FXDestination {
	u16 bufferId; // _00 - See DSPMixerChannel::id
	s16 volume;   // _02 - 1.15 format.
};

/**
 * @brief TODO.
 */
struct FXBuffer {
	DSPBOOL enabled;         // _00
	u16 circularBufferSize;  // _02
	s16* circularBufferBase; // _04
	FXDestination dest[2];   // _08
	s16 filterCoeffs[8];     // _10
};

#endif
