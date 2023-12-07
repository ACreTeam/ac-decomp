#ifndef AC_T_BISCUS4_H
#define AC_T_BISCUS4_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Biscus4_Profile;


typedef void (*BISCUS4_PROC)(ACTOR*);

typedef struct t_biscus4_s{
    TOOLS_ACTOR tools_class;
    BISCUS4_PROC proc; 
    int current_id;
}BISCUS4_ACTOR;


#ifdef __cplusplus
}
#endif

#endif

