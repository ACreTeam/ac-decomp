#ifndef AC_HATUMODE_NPC0_H
#define AC_HATUMODE_NPC0_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aHN0_TALK_REQ_NONE 0
#define aHN0_TALK_REQ_NORM 1
#define aHN0_TALK_REQ_FORCE 2

enum {
    aHN0_THINK_INIT_NONE,
    aHN0_THINK_INIT_NORMAL_WAIT,
    aHN0_THINK_INIT_MOVE,
    aHN0_THINK_INIT_TURN_F,
    aHN0_THINK_INIT_SAISEN,
    aHN0_THINK_INIT_OMAIRI_AF,
    aHN0_THINK_INIT_NEXT_POS,
    aHN0_THINK_INIT_TURN_MOVE,
    aHN0_THINK_INIT_MOVE_BF,
    aHN0_THINK_INIT_TURN_AISATU,
    aHN0_THINK_INIT_AISATU,
    aHN0_THINK_INIT_AISATU2,
    aHN0_THINK_INIT_HAIGO,

    aHN0_THINK_INIT_NUM
};

enum {
    aHN0_THINK_PROC_NONE,
    aHN0_THINK_PROC_BIRTH,
    aHN0_THINK_PROC_READY1,
    aHN0_THINK_PROC_READY2,
    aHN0_THINK_PROC_TURN_NEXT,
    aHN0_THINK_PROC_FLAG2_WAIT,
    aHN0_THINK_PROC_ANIME_WAIT,
    aHN0_THINK_PROC_ANIME_WAIT_SAISEN,
    aHN0_THINK_PROC_TIMER_WAIT,
    aHN0_THINK_PROC_MOVE_WAIT,
    aHN0_THINK_PROC_MOVE_BF,
    aHN0_THINK_PROC_AISATU_WAIT,
    aHN0_THINK_PROC_AISATU2_WAIT,
    aHN0_THINK_PROC_TO_OMAIRI,
    aHN0_THINK_PROC_PLAYER_MOVE,
    aHN0_THINK_PROC_PLAYER_WAIT,
    aHN0_THINK_PROC_KASASIMAI,
    aHN0_THINK_PROC_SANPAI_WAIT,

    aHN0_THINK_PROC_NUM
};

typedef struct hatumode_npc0_actor_s HATUMODE_NPC0_ACTOR;

typedef void (*aHN0_TALK_PROC)(HATUMODE_NPC0_ACTOR*, GAME_PLAY*);

struct hatumode_npc0_actor_s {
    NPC_ACTOR npc_class;
    aHN0_TALK_PROC talk_proc;
    int base_msg;
    s16 timer;
    s16 pos[2];
    u8 think_idx;
    u8 next_think_idx;
    u8 move_think_idx;
    u8 talk_idx;
    u8 think_proc_idx;
    u8 think_change_flag;
    u8 root;
    u8 player;
};

extern ACTOR_PROFILE Hatumode_Npc0_Profile;

#ifdef __cplusplus
}
#endif

#endif
