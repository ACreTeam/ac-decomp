#ifndef AC_NPC_GUIDE2_H
#define AC_NPC_GUIDE2_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_guide2_actor_s NPC_GUIDE2_ACTOR;

typedef void (*aNG2_PROC)(NPC_GUIDE2_ACTOR*, GAME_PLAY*);

struct npc_guide2_actor_s {
    NPC_ACTOR npc_class;
    int action;
    int next_action;
    aNG2_PROC proc;
    int lock_camera_flag;
    int camera_morph_counter;
    s16 camera_move;
    s8 camera_move_cnt;
    s8 camera_move_set_counter;
    f32 camera_move_y;
    f32 camera_move_range;
    s16 camera_tilt_cur_angle;
    s16 camera_tilt_goal_angle;
    s16 camera_tilt_add;
    int answer_flags;
    ACTOR* train_door_actor;
    int obj_look_type;
    f32 obj_dist_ground;
    int camera_eyes_flag;
};

extern ACTOR_PROFILE Npc_Guide2_Profile;

#ifdef __cplusplus
}
#endif

#endif
