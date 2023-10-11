#ifndef EF_ROOM_SUNSHINE_MINSECT_H
#define EF_ROOM_SUNSHINE_MINSECT_H

#include "types.h"
#include "m_actor.h"
#include "ef_room_sunshine.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Room_Sunshine_Minsect_Profile;

typedef struct effect_room_sunshine_minsect_s{
    ROOMSUNSHINE_ACTOR ef_sunshine_class;
}ROOMSUNSHINEMINSECT_ACTOR;   

extern u8 draw_status;

#ifdef __cplusplus
}
#endif

#endif

