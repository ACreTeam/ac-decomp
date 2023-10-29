#ifndef AC_TOUDAI_H
#define AC_TOUDAI_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Toudai_Profile;

typedef void (*TOUDAI_PROC)(ACTOR*, GAME_PLAY*);

typedef struct actor_toudai_s{
    ACTOR actor_class;
    int keyframe_state;
    cKF_SkeletonInfo_R_c keyframe;
    int current_frame;
    s_xyz work[15];
    s_xyz target[15];
    TOUDAI_PROC proc;
    u8 unk2A4[0x10];
    int current_proc;
    u8 unk2B8[0x4];
    int ready_flag;
    u8 unk2C0[0x8];
    f32 unk2C8;
    f32 unk2CC;
    f32 unk2D0;
    u8 unk2D4[0x4];
    int season;
}TOUDAI_ACTOR;    

#ifdef __cplusplus
}
#endif

#endif

