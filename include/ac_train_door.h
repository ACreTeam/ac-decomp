#ifndef AC_TRAIN_DOOR_H
#define AC_TRAIN_DOOR_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aTRD_JOINT_NUM 5

typedef struct traindoor_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x178 */ u8 pad[0x17C - 0x174];
    /* 0x17C */ cKF_SkeletonInfo_R_c keyframe;
    /* 0x1EC */ u8 pad2[0x210 - 0x1EC];
    /* 0x210 */ s_xyz work[aTRD_JOINT_NUM];
    /* 0x22E */ s_xyz target[aTRD_JOINT_NUM];
    /* 0x24C */ int open_flag;
} TRAINDOOR_ACTOR;

extern ACTOR_PROFILE TrainDoor_Profile;

#ifdef __cplusplus
}
#endif

#endif
