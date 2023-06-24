#ifndef AC_BOXMOVE_H
#define AC_BOXMOVE_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct box_move_s{
    ACTOR actor_class;
    u8 pad[0x28C - 0x174];
}BOXMOVE_ACTOR;

extern ACTOR_PROFILE BoxMove_Profile;

#ifdef __cplusplus
}
#endif

#endif

