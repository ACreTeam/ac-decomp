#ifndef AC_T_COBRA1_H
#define AC_T_COBRA1_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"


#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Cobra1_Profile;

typedef void (*COBRA1_PROC)(ACTOR*);

typedef struct t_cobra1_s{
    TOOLS_ACTOR tools_class;
    COBRA1_PROC proc; 
    int current_id;
}COBRA1_ACTOR;


#ifdef __cplusplus
}
#endif

#endif

