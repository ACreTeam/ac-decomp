#ifndef AC_TOKYOSO_CONTROL_H
#define AC_TOKYOSO_CONTROL_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aTKC_LAP_NUM 4
#define aTKC_SUBLAP_NUM (2 * aTKC_LAP_NUM) // split into half of the circuit
#define aTKC_NPC_NUM 2

#define aTKC_ANGLE_FOR_LAP_COMPLETION 4000 // approximately 22 degrees

#define aTKC_FLAG_5 (1 << 5)
#define aTKC_FLAG_6 (1 << 6)
#define aTKC_FLAG_7 (1 << 7)
#define aTKC_FLAG_8 (1 << 8)
#define aTKC_FLAG_9 (1 << 9)
#define aTKC_FLAG_RACE_ACTIVE (1 << 10)
#define aTKC_FLAG_11 (1 << 11)
#define aTKC_FLAG_12 (1 << 12)
#define aTKC_FLAG_13 (1 << 13)
#define aTKC_FLAG_14 (1 << 14)
#define aTKC_FLAG_15 (1 << 15)

#define aTKC_MASK_13_14 (aTKC_FLAG_13 | aTKC_FLAG_14)

enum {
    aTKC_GOAL_NONE,
    aTKC_GOAL_WON,
    aTKC_GOAL_LOSE,

    aTKC_GOAL_NUM
};

typedef struct ac_tokyoso_event_s {
    u8 _00;
    u8 _01;
    u16 flags;
    s16 yasiro_pos[3]; // shrine pos (wishing well in AC and e+)
    s16 pos_0A[2][2];
    s16 angle[2];
    s16 next_angle[2];
    u8 lap[2];
    u8 goal[2];
} aEv_tokyoso_c;

typedef void (*aTKC_NEXT_RUN_PROC)(ACTOR* actorx);
typedef s16 (*aTKC_GET_ANGLE_PROC)(ACTOR* actorx);
typedef void (*aTKC_RUN_PROC)(ACTOR* actorx);
typedef s16 (*aTKC_RUN_CHECK_PROC)(ACTOR* actorx);
typedef s16 (*aTKC_TOP_CHECK_PROC)(ACTOR* actorx);
typedef s16 (*aTKC_GOAL_CHECK_PROC)(ACTOR* actorx);
typedef void (*aTKC_NPC1_THINK_INIT_PROC)(ACTOR* actorx, GAME_PLAY* play, u8 type);
typedef void (*aTKC_NEXT_POS_PROC)(ACTOR* actorx, int idx);
typedef void (*aTKC_NEXT_WARMUP_PROC)(ACTOR* actorx);
typedef void (*aTKC_SET_TALK_REQUEST_PROC)(ACTOR* actorx);

typedef struct tokyoso_control_clip_s {
    aTKC_NEXT_RUN_PROC next_run_proc;
    aTKC_GET_ANGLE_PROC get_angle_proc;
    aTKC_RUN_PROC run_proc;
    aTKC_RUN_CHECK_PROC run_check_proc;
    aTKC_TOP_CHECK_PROC top_check_proc;
    aTKC_GOAL_CHECK_PROC goal_check_proc;
    aTKC_NPC1_THINK_INIT_PROC npc1_think_init_proc;
    aTKC_NEXT_POS_PROC next_pos_proc;
    aTKC_NEXT_WARMUP_PROC next_warmup_proc;
    aTKC_SET_TALK_REQUEST_PROC set_talk_request_proc;
} aTKC_clip_c;

typedef struct tokyoso_control_actor_s TOKYOSO_CONTROL_ACTOR;

typedef void (*aTKC_PROC)(TOKYOSO_CONTROL_ACTOR* actor, GAME_PLAY* play);

struct tokyoso_control_actor_s {
    ACTOR actor_class;
    aTKC_clip_c clip;
    aTKC_PROC act_proc;
    int action;
    s16 timer;
};

extern ACTOR_PROFILE Tokyoso_Control_Profile;

#ifdef __cplusplus
}
#endif

#endif
