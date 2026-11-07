#ifndef _JAUDIO_AICTRL_H
#define _JAUDIO_AICTRL_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

/////////// JAUDIO AI CONTROL DEFINITIONS ///////////
// Callbacks.
typedef s16* (*MixCallback)(s32);
typedef void (*DACCallback)(s16*, s32);

// Enums.
/**
 * @brief TODO
 */
typedef enum _MixMode {
	MixMode_Mono       = 0,
	MixMode_MonoWide   = 1,
	MixMode_Extra      = 2,
	MixMode_Interleave = 3,
	MixMode_Num, // 4
} MixMode;

// Global counters.
extern u32 UNIVERSAL_DACCOUNTER;
extern u32 JAC_VFRAME_COUNTER;
extern u32 JAC_SYSTEM_OUTPUT_MODE;

/////////////////////////////////////////////////////

//////////// JAUDIO AI CONTROL FUNCTIONS ////////////
void Jac_HeapSetup(void* heap, s32 size);
void* OSAlloc2(u32 size);
void Jac_Init();
void Jac_VframeWork();
void Jac_UpdateDAC();
void Jac_SetOutputMode(int mode);
int Jac_GetOutputMode();
void Jac_SetMixerLevel(f32, f32);
void Jac_RegisterMixcallback(MixCallback mixcallback, u8 mixmode);
extern MixCallback Jac_GetMixcallback(u8* mixmode);

/////////////////////////////////////////////////////

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
