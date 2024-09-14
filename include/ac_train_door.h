#ifndef AC_TRAIN_DOOR_H
#define AC_TRAIN_DOOR_H

#include "types.h"
#include "ac_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aTRD_JOINT_NUM 5

typedef struct traindoor_s {
    /* 0x000 */ CMN_ACTOR common_actor_class;
    /* 0x210 */ s_xyz work[aTRD_JOINT_NUM];
    /* 0x22E */ s_xyz target[aTRD_JOINT_NUM];
    /* 0x24C */ int open_flag;
} TRAINDOOR_ACTOR;

extern ACTOR_PROFILE TrainDoor_Profile;

#ifdef __cplusplus
}
#endif

#endif
