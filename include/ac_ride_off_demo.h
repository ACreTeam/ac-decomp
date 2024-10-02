#ifndef AC_RIDE_OFF_DEMO_H
#define AC_RIDE_OFF_DEMO_H

#include "types.h"
#include "m_actor.h"
#include "ac_train1.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*aROD_INIT_PROC)(ACTOR*, GAME*);

typedef struct ride_off_demo_s {
    ACTOR actor_class;
    int current_action;
    int _178;
    aROD_INIT_PROC current_proc;
    TRAIN1_ACTOR* train_actor;
    ACTOR* station_master_actor;
    int _188;
} RIDE_OFF_DEMO_ACTOR;

extern ACTOR_PROFILE Ride_Off_Demo_Profile;

#ifdef __cplusplus
}
#endif

#endif

