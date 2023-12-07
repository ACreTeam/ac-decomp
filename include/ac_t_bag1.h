#ifndef AC_T_BAG1_H
#define AC_T_BAG1_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Bag1_Profile;

typedef void (*BAG1_PROC)(ACTOR*);

typedef struct t_bag1_s{
    TOOLS_ACTOR tools_class;
    BAG1_PROC proc; 
    int current_id;
}BAG1_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

