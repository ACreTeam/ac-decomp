#ifndef AC_PTERMINAL_H
#define AC_PTERMINAL_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pterminal_actor_s PTERMINAL_ACTOR;

typedef void (*aPT_PROC)(PTERMINAL_ACTOR*, GAME* game);

struct pterminal_actor_s {
    ACTOR actor_class;
    int msg_no;
    int next_proc;
    int proc;
    int counter;
    int transSE_active;
    int transSE;
};

extern ACTOR_PROFILE Pterminal_Profile;

#ifdef __cplusplus
}
#endif

#endif
