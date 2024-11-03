#ifndef AC_EV_ANGLER_H
#define AC_EV_ANGLER_H

#include "types.h"
#include "m_actor.h"
#include "m_personal_id.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct fish_event_data_s {
    int size;
    PersonalID_c pID;
} aEANG_event_data_c;

extern ACTOR_PROFILE Ev_Angler_Profile;

#ifdef __cplusplus
}
#endif

#endif
