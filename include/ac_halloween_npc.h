#ifndef AC_HALLOWEEN_NPC_H
#define AC_HALLOWEEN_NPC_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct halloween_npc_s HALLOWEEN_NPC_ACTOR;

typedef void (*aHWN_TALK_PROC)(HALLOWEEN_NPC_ACTOR*, GAME_PLAY*);
typedef void (*aHWN_THINK_PROC)(HALLOWEEN_NPC_ACTOR*, GAME_PLAY*);

/* sizeof(halloween_npc_s) == 0x9AC*/
struct halloween_npc_s {
    /* 0x000 */ NPC_ACTOR npc_class;
    /* 0x994 */ int dt_tbl_idx;
    /* 0x998 */ aHWN_THINK_PROC think_proc;
    /* 0x99C */ int _99C;
    /* 0x9A0 */ aHWN_TALK_PROC talk_proc;
    /* 0x9A4 */ mActor_name_t item;
    /* 0x9A8 */ BOOL wait_think_done;
};

enum {
    aHWN_TALK_FIRST_CALL_TALK, // 0
    aHWN_TALK_TRICK_OR_TREAT_TALK, // 1
    aHWN_TALK_MENU_OPEN_WAIT_TALK, // 2
    aHWN_TALK_MENU_CLOSE_WAIT_TALK, // 3
    aHWN_TALK_GET_OTHER_ITEM_WAIT_TALK, // 4
    aHWN_TALK_RECEIVE_TOOL_ITEM_START_WAIT_TALK, // 5
    aHWN_TALK_RECEIVE_TOOL_ITEM_END_WAIT_TALK, // 6
    aHWN_TALK_TRICK_TIMING_WAIT_TALK, // 7
    aHWN_TALK_TRICK_CHG_CLOTH_TALK, // 8
    aHWN_TALK_TRICK_CHG_CLOTH_END_WAIT_TALK, // 9
    aHWN_TALK_GET_AME_WAIT_TALK, // 10
    aHWN_TALK_GET_AME_TALK, // 11
    aHWN_TALK_PL_DEMO_CODE_END_WAIT_TALK, // 12
    aHWN_TALK_END_WAIT, // 13

    aHWN_TALK_NUM
};

enum {
    aHWN_THINK_APPROACH,
    aHWN_THINK_APPROACH_WAIT,

    aHWN_THINK_NUM
};

enum {
    aHWN_TRICK_TYPE_CHG_CLOTH,
    aHWN_TRICK_TYPE_CHG_ITEM,

    aHWN_TRICK_TYPE_NUM
};

extern ACTOR_PROFILE Halloween_Npc_Profile;

#ifdef __cplusplus
}
#endif

#endif
