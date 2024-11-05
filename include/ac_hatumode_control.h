#ifndef AC_HATUMODE_CONTROL_H
#define AC_HATUMODE_CONTROL_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hatumode_event_save_s {
    u16 state;
    u16 flags0;
    u16 flags1;
    s16 yashiro_pos[3];
    u8 cur_npc_idx;
} aEv_hatumode_save_c;

typedef void (*aHTMD_TALK_INFO_PROC)(ACTOR*, int);
typedef int (*aHTMD_THINK_INIT_PROC)(ACTOR*, GAME_PLAY*);
typedef int (*aHTMD_SET_START_PROC)(ACTOR*);
typedef int (*aHTMD_PLAYER_MOVE_PROC)(GAME_PLAY*, int);
typedef int (*aHTMD_LOOK_PLAYER_PROC)(ACTOR*);

typedef struct hatumode_ctrl_clip_s {
    aHTMD_TALK_INFO_PROC talk_info_proc;
    aHTMD_THINK_INIT_PROC think_init_proc;
    aHTMD_SET_START_PROC set_start_proc;
    aHTMD_PLAYER_MOVE_PROC player_move_proc;
    aHTMD_LOOK_PLAYER_PROC look_player_proc;
} aHTMD_clip_c;

typedef struct hatumode_ctrl_actor_s HATUMODE_CONTROL_ACTOR;

typedef void (*aHTC_MOVE_PROC)(HATUMODE_CONTROL_ACTOR*, GAME_PLAY*);

struct hatumode_ctrl_actor_s {
    ACTOR actor_class;
    aHTMD_clip_c clip;
    aHTC_MOVE_PROC move_proc;
};

extern ACTOR_PROFILE Hatumode_Control_Profile;

#ifdef __cplusplus
}
#endif

#endif
