#ifndef AC_TRAIN0_H
#define AC_TRAIN0_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*aTR0_SETUP_ACTOR_PROC)(GAME_PLAY*, mActor_name_t,int,int,int,int,int,int,int);

typedef struct ac_train0_clip_s{
    aTR0_SETUP_ACTOR_PROC setup_actor_proc;
}aTR0_Clip_c;

typedef struct train0_s{
    ACTOR actor_class;
    int steam_available;
    cKF_SkeletonInfo_R_c keyframe;
    int steam_timer;
    s_xyz work[15];
    s_xyz target[15];
    u8 pad4[0x2b4 - 0x2A0];
    int tr_action;
    u8 pad5[0x2BC - 0x2B8];
    int effect_num;
    int unk2c0;
    ACTOR* tr_actor_p;
    f32 tr1_pos;
    f32 tr_speed;
    u8 pad6[0x2D8 - 0x2CC];
}TRAIN0_ACTOR;

extern ACTOR_PROFILE Train0_Profile;

#ifdef __cplusplus
}
#endif

#endif

