#ifndef AC_T_BISCUS2_H
#define AC_T_BISCUS2_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Biscus2_Profile;

typedef void (*BISCUS2_PROC)(ACTOR*);

typedef struct t_biscus2_s{
    TOOLS_ACTOR tools_class;
    BISCUS2_PROC proc; 
    int current_id;
}BISCUS2_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

