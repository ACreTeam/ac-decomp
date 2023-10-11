#ifndef EF_LAMP_LIGHT_H
#define EF_LAMP_LIGHT_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Lamp_Light_Profile;

typedef struct ef_lamp_light_s{
    ACTOR actor_class;
    int switch_type;
    Lights lights;
    Light_list* node_p;
}LAMPLIGHT_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

