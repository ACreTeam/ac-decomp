#ifndef AC_T_BISCUS3_H
#define AC_T_BISCUS3_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Biscus3_Profile;

typedef void (*BISCUS3_PROC)(ACTOR*);

typedef struct t_biscus3_s{
    TOOLS_ACTOR tools_class;
    BISCUS3_PROC proc; 
    int current_id;
}BISCUS3_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

