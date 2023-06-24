#ifndef AC_BOXTRICK01_H
#define AC_BOXTRICK01_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct box_trick01_s{
    ACTOR actor_class;
    u8 pad[0x17C - 0x174];
}BOXTRICK01_ACTOR;


extern ACTOR_PROFILE BoxTrick01_Profile;


#ifdef __cplusplus
}
#endif

#endif

