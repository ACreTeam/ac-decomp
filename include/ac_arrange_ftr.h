#ifndef AC_ARRANGE_FTR_H
#define AC_ARRANGE_FTR_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct arrange_ftr_actor_s ARRANGE_FURNITURE_ACTOR;

struct arrange_ftr_actor_s {
    ACTOR actor_class;
    u8 _174[0x278 - 0x174];
};

extern ACTOR_PROFILE Arrange_Furniture_Profile;

#ifdef __cplusplus
}
#endif

#endif
