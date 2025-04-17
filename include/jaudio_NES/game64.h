#ifndef GAME64_H
#define GAME64_H

#include "types.h"
#include "libc/stdarg.h"

#ifdef __cplusplus
extern "C" {
#endif

f32 distance2vol4KITEKI(f32);
f32 distance2vol4MD(f32);

extern void Na_InitAudio(void (*fatal_callback)(), u8* load_addr, size_t load_size, u8* bootsound, size_t bootsound_size, BOOL cut_flag);
extern void Na_GameFrame();
extern void Na_Reset();
extern void Na_SoftReset();
extern void Na_Tenki(u8);
extern void Na_BgmStart(u8);
extern void Na_BgmCrossfadeStart(u8);
extern void Na_BgmStop(u16);
extern void Na_SysTrgStart(u16);
extern void Na_PlyWalkSe(u16, u16, f32);
extern void Na_PlyWalkSeRoom(u8, u16, f32);
extern void Na_NpcWalkSe(u16, u16, f32);
extern void Na_NpcWalkSeRoom(u8, u16, f32);
// #ifdef BUGFIXES
extern void Na_PlayerStatusLevel(u8, f32);
// #endif // BUGFIXES
extern void Na_VoiceSe(u8, u8, u8, s16, u8, u8);
extern void Na_MessageStatus(u8);
extern void Na_MessageSpeed(u8);
extern u8 Na_MessageSpeedGet();
extern void Na_OngenPos(u32, u8, u16, f32);
extern void Na_OngenTrgStartSpeed(u16, u16, f32, f32);
extern void Na_OngenTrgStart(u16, u16, f32);
extern void Na_SetOutMode(u8);
extern void Na_SetVoiceMode(u8);
extern void Na_FloorTrgStart(u8, u16, f32);
extern void Na_SysLevStart(u8);
extern void Na_SysLevStop(u8);
extern void Na_Pause(u8);
extern void Na_RhythmPos(u32, u8, u16, f32);
extern void Na_SpecChange(int);
extern void Na_MDPlayerPos(u16 a, f32 e, u16 b, u16 c, u32 d);
extern void Na_BGMVolume(f32, u16);
extern void Na_RestartPrepare();
extern u8 Na_CheckRestartReady();
extern void Na_Restart();
extern u8 Na_SubGameOK();
extern void Na_KishaStatusTrg(u8);
extern void Na_KishaStatusLevel(f32 speed, u32 ongenNum1, u16 angle1, f32 distance1, u32 ongenNum2, u16 angle2,
                                f32 distance2);
extern void Na_TTKK_ARM(u8);
extern void Na_BgmMuteClear();
extern u8 Na_BgmFadeoutCheck();
extern u8 Na_SeFadeoutCheck();
extern void Na_BgmTrOn(u8 a);
extern void Na_BgmTrOff(u8 a);
extern void Na_SubGameStart();
extern void Na_SubGameEnd();
extern void Na_SceneMode(u8);
extern u8 Na_RoomIncectPos(int, u8, u16, f32);
extern void Na_FurnitureInstPos(int, u16, f32);
extern void Na_TrgSeEcho(u8);
extern void Na_LevSeEcho(u8);
extern void Na_BGMFilter(u8);
extern void Na_RoomType(u8);
extern u8 Na_CheckNeosBoot();
extern void Na_Museum(u8);
extern int Na_GetSoundFrameCounter();
extern void Na_kazagurumaLevel(f32);

// __declspec(weak) extern int OSAttention(const char* msg, ...) {
//     va_list marker;

//     va_start(marker, msg);

//     return vprintf(msg, marker);
// }

extern u8 sou_now_bgm_handle;
extern u8 sou_chime_status;

#ifdef __cplusplus
}
#endif

#endif
