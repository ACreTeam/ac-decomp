#ifndef GAME64_CPP_H
#define GAME64_CPP_H

#include "types.h"
#include "jaudio_NES/game64.h"

/* C++ linkage */
extern void Sou_lev_ongen_data_struct_clear();
extern void Sou_BgmFadeoutEndCheck();
extern u8 Sou_BgmTenkiConv(u8);
extern void Sou_GroupControl(u8, u8, f32);
extern void Sou_GroupControl_MD(u8, u8, f32);
extern u8 pan_kochou(u8, f32);
extern u8 angle2pan(u16 angle, f32 dist);
extern f32 distance2vol(f32 distance);
extern void Sou_VoiceStart(u8, u8);
extern void Sou_TrgStart(u16, f32, f32, f32, u8, u8, f32);
extern void Sou_SpecialRoutine00();
extern void Sou_SpecialRoutine02();
extern void Sou_SpecialRoutine03();
extern void Sou_TrgEndCheck();
extern void Sou_LevStart(u8, u8);
extern void Sou_LevStop(u8, u8);
extern void Sou_TrgMake(u8);
extern void Sou_VoiceMake(u8);
extern void Sou_LevMake(u8);
extern void Sou_ChimeMake();
extern void Sou_LevSet(u8);
extern void Sou_Insect_Lev_Cont();
extern void Sou_Ongen_Lev_Cont();
extern void Sou_Ongen_Lev_Prog(u8);
extern void Sou_BgmStart(u8, u16);
extern void Sou_BGMVolMove();
extern void Sou_Na_BgmStart(u8);
extern void Sou_Na_BgmStop(u16);
extern void Sou_SpecialRoutine06();
extern void Sou_SpecialRoutine07();
extern void Sou_SeFadeoutRoutine();
extern void Sou_SeFadeinRoutine();
extern void Sou_SeVolumeReset();
extern void Sou_SeTrFadeout(u8, u16);
extern void Sou_SeFadeout(u16);
extern void Sou_SpecialRoutine08();
extern void Sou_SpecialRoutine10();
extern void Sou_InitAudio();
extern void Sou_DVD_Error(char*, u8*);
extern void Sou_WalkSe(u16, u16, f32, u8, f32);
extern u8 Sou_TanboinHenkan(u8, u8);
extern u8 Sou_ChouboinHenkan(u8, u8);
extern u8 Sou_ConnectCheck(u8, u8, u8);
extern u8 Sou_BoinShiinCheck(u8);
extern void Sou_PosTrgStart(u16, u16, f32, u8, f32);
#endif
