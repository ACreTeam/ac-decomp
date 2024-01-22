#ifndef AC_T_UTIWA_H
#define AC_T_UTIWA_H

#include "types.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Utiwa_Profile;

typedef void (*UTIWA_PROC)(ACTOR*);

typedef struct t_utiwa_s{
    TOOLS_ACTOR tools_class;
    UTIWA_PROC proc; 
    int current_id;
} UTIWA_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

