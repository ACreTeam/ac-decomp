#ifndef AC_T_BAG2_H
#define AC_T_BAG2_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Bag2_Profile;

typedef void (*BAG2_PROC)(ACTOR*);

typedef struct t_bag2_s{
    TOOLS_ACTOR tools_class;
    BAG2_PROC proc; 
    int current_id;
}BAG2_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

