#ifndef AC_NPC_POST_GIRL_H
#define AC_NPC_POST_GIRL_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"
#include "bg_post_item.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aPG_ADDR_STR_LEN 8
#define aPG_LOAN_STR_LEN 7

extern ACTOR_PROFILE Npc_Post_Girl_Profile;

typedef struct ac_npc_postgirl NPC_POSTGIRL_ACTOR;

typedef void (*aPG_PROC)(NPC_POSTGIRL_ACTOR*, GAME_PLAY*);
typedef void (*aPG_SETUP_PROC)(NPC_POSTGIRL_ACTOR*, GAME_PLAY*, int);
typedef void (*aPG_INIT_PROC)(ACTOR*, GAME*);

#define aPG_STATUS_NONE 0
#define aPG_STATUS_DESK_FULL (1 << 0)
#define aPG_STATUS_DONE_FIRST_JOB (1 << 1)
#define aPG_HAS_BANK_ACCOUNT (1 << 2)

struct ac_npc_postgirl {
    NPC_ACTOR npc_class;
    /* 0x994 */ int action;
    /* 0x998 */ int next_action;
    /* 0x99c */ aPG_PROC process;
    /* 0x9a0 */ aPG_SETUP_PROC setup_action;
    /* 0x9a4 */ u8 status;
    /* 0x9a5 */ u8 dest;
    /* 0x9a6 */ u8 is_desk_full;
    /* 0x9a7 */ u8 has_bank_account;
    /* 0x9a8 */ int loan;
    /* 0x9ac */ BG_POST_ITEM_ACTOR* _9ac;
    /* 0x9b0 */ int msg_no;
};

enum ac_npc_action {
    aPG_ACTION_ASK_FOR_BUSINESS,
    aPG_ACTION_NONE,
    aPG_ACTION_MSG_WIN_OPEN_WAIT,
    aPG_ACTION_RECEIVE_DEMO_START_WAIT,
    aPG_ACTION_RECEIVE_DEMO_END_WAIT,
    aPG_ACTION_RECEIVE_AFTER_MSG_END_WAIT,
    aPG_ACTION_REFUSE_DEMO_START_WAIT,
    aPG_ACTION_REFUSE_DEMO_STOP_WAIT,
    aPG_ACTION_REFUSE_MSG_END_WAIT,
    aPG_ACTION_REFUSE_DEMO_AFTER,
    aPG_ACTION_REFUSE_AFTER_MSG_END_WAIT,
    aPG_ACTION_REPAY_BEFORE,
    aPG_ACTION_MSG_WIN_CLOSE_WAIT,
    aPG_ACTION_REPAY_MENU_CLOSE_WAIT,
    aPG_ACTION_14,
    aPG_ACTION_REPAY_AFTER,
    aPG_ACTION_CARD_ERR_OTHERLAND, // 0x10
    aPG_ACTION_CARD_CHECK_CONDITION,
    aPG_ACTION_18,
    aPG_ACTION_CARD_SAVE_MENU_CLOSE_WAIT,
    aPG_ACTION_20,
    aPG_ACTION_21,
    aPG_ACTION_RECEIVE_MENU_CLOSE_WAIT,
    aPG_ACTION_CHECK_RECEIVE_AFTER,
    aPG_ACTION_DEPOSIT_BEFORE,
    aPG_ACTION_25,
    aPG_ACTION_DEPOSIT_MENU_CLOSE_WAIT,
    aPG_ACTION_27,
    aPG_ACTION_DEPOSIT_AFTER,
    aPG_ACTION_29
};

#ifdef __cplusplus
}
#endif

#endif

