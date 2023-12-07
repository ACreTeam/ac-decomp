#ifndef AC_T_ANRIUM1_H
#define AC_T_ANRIUM1_H

#include "types.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Anrium1_Profile;

typedef void (*ANRIUM1_PROC)(ACTOR*);

typedef struct t_anrium_s{
    TOOLS_ACTOR tools_class;
    ANRIUM1_PROC proc; 
    int current_id;
}ANRIUM1_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

