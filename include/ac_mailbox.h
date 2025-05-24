#ifndef AC_MAILBOX_H
#define AC_MAILBOX_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aMBX_PLAYER_OPEN_ANGLE DEG2SHORT_ANGLE2(38.2379150390625f)

typedef struct mailbox_actor_s MAILBOX_ACTOR;

typedef void (*aMBX_ACT_PROC)(MAILBOX_ACTOR* actor, GAME_PLAY* play);

#define aMBX_JOINT_NUM 6

enum {
    aMBX_REQUEST_NONE, // no current request
    aMBX_REQUEST_DELIVERY, // delivery by Pete, open -> close
    aMBX_REQUEST_OPEN, // player opens mailbox, hold state for submenu

    aMBX_REQUEST_NUM
};

struct mailbox_actor_s {
    ACTOR actor_class;
    void* segp;
    
    int kf0_state;
    cKF_SkeletonInfo_R_c kf0;
    s_xyz joint0[aMBX_JOINT_NUM+1];
    s_xyz morph0[aMBX_JOINT_NUM+1];
    int anim_idx0;

    int kf1_state;
    cKF_SkeletonInfo_R_c kf1;
    s_xyz joint1[aMBX_JOINT_NUM+1];
    s_xyz morph1[aMBX_JOINT_NUM+1];
    int anim_idx1;

    int action;
    aMBX_ACT_PROC act_proc;
    int arrange_idx;
    int req;
};

extern ACTOR_PROFILE MailBox_Profile;

#ifdef __cplusplus
}
#endif

#endif
