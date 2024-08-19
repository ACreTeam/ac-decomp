#ifndef AC_UKI_H
#define AC_UKI_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Uki_Profile;

typedef struct actor_uki_s {
    ACTOR actor_class;
    u8 pad[0xA4];
    xyz_t right_hand_pos;
    xyz_t position_speed;
    int angle_speed_y;
    int command;
    u8 pad2[0x10];
    xyz_t rod_top_position;
    xyz_t left_hand_pos;
} UKI_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

