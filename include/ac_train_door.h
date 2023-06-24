#ifndef AC_TRAIN_DOOR_H
#define AC_TRAIN_DOOR_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct traindoor_s {
    ACTOR actor_class;
    u8 pad [0x17C - 0x174];
    cKF_SkeletonInfo_R_c keyframe;
    u8 pad2 [0x210 - 0x1ed];
    s_xyz work;
    u8 pad3 [0x22e - 0x216];
    s_xyz target;
    u8 pad4[0x24c - 0x234];
    int idle;
}TRAINDOOR_ACTOR;

extern ACTOR_PROFILE TrainDoor_Profile;

#ifdef __cplusplus
}
#endif

#endif

