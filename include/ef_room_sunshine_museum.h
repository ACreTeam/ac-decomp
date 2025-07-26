#ifndef EF_ROOM_SUNSHINE_MUSEUM_H
#define EF_ROOM_SUNSHINE_MUSEUM_H

#include "types.h"
#include "m_actor.h"
#include "ef_room_sunshine.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    Ef_Room_Sunshine_Museum_TOP_RIGHT,
    Ef_Room_Sunshine_Museum_TOP_LEFT,
    Ef_Room_Sunshine_Museum_BOTTOM_RIGHT,
    Ef_Room_Sunshine_Museum_BOTTOM_LEFT,

    Ef_Room_Sunshine_Museum_NUM
};

typedef struct effect_room_sunshine_museum_s {
    ROOMSUNSHINE_ACTOR ef_sunshine_class;
} ROOMSUNSHINEMUSEUM_ACTOR;

extern ACTOR_PROFILE Room_Sunshine_Museum_Profile;

#ifdef __cplusplus
}
#endif

#endif
