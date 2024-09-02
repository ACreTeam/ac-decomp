#ifndef AC_SHOP_LEVEL_H
#define AC_SHOP_LEVEL_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct shop_level_actor_s SHOP_LEVEL_ACTOR;

struct shop_level_actor_s {
    ACTOR actor_class;
    int bx;
    int bz;
};

extern ACTOR_PROFILE Shop_Level_Profile;

#ifdef __cplusplus
}
#endif

#endif
