#ifndef AC_TRAIN1_H
#define AC_TRAIN1_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct train1_s {
    ACTOR actor_class;
    int anim_state;
    cKF_SkeletonInfo_R_c keyframe;
    int timer;
    s_xyz work[15];
    s_xyz morph[15];
    u8 pad4[0x2b4 - 0x2A0];
    int tr_action;
    int player_pass_exists;
    int player_pass_leaving; // Not sure about this one
    int unk2c0;
    ACTOR* tr_actor_p;
    f32 tr_speed;
    f32 tr0_pos;
    u8 pad2[0x2D8 - 0x2CC];
} TRAIN1_ACTOR;

extern ACTOR_PROFILE Train1_Profile;

#ifdef __cplusplus
}
#endif

#endif
