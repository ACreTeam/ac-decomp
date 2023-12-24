#ifndef AC_NAMEPLATE_H
#define AC_NAMEPLATE_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Nameplate_Profile;

typedef struct nameplate_actor_s{
    ACTOR actor_class;
    u8 pad[0x2D8 - 0x170];
}NAMEPLATE_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

