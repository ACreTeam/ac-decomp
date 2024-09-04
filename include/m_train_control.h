#ifndef M_TRAIN_CONTROL_H
#define M_TRAIN_CONTROL_H

#include "types.h"
#include "game_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mTRC_SLOW_SPEED 2.0f // speed stopping/starting
#define mTRC_FAST_SPEED 6.0f // speed when farther away from station

enum {
    mTRC_ACTION_NONE,
    mTRC_ACTION_SPAWN_MOVING,
    mTRC_ACTION_BEGIN_SLOWDOWN,
    mTRC_ACTION_BEGIN_STOP,
    mTRC_ACTION_SIGNAL_STOPPED,
    mTRC_ACTION_WAIT_STOPPED,
    mTRC_ACTION_SIGNAL_STARTING,
    mTRC_ACTION_BEGIN_PULL_OUT,
    mTRC_ACTION_SPEED_UP,

    mTRC_ACTION_NUM
};

extern void mTRC_init(GAME* game);
extern void mTRC_move(GAME* game);

#ifdef __cplusplus
}
#endif

#endif
