#ifndef AC_QUEST_MANAGER_H
#define AC_QUEST_MANAGER_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"
#include "m_submenu.h"
#include "m_choice.h"
#include "ac_quest_manager_clip.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aQMgr_REGIST_NUM 35

enum {
    aQMgr_TALK_STATE_INIT,
    aQMgr_TALK_STATE_SUB,

    aQMgr_TALK_STATE_NUM
};

enum {
    aQMgr_TALK_SUB_STATE_WAIT,
    aQMgr_TALK_SUB_STATE_MSG_DISAPPEAR_WAIT,
    aQMgr_TALK_SUB_STATE_MSG_APPEAR_WAIT,
    aQMgr_TALK_SUB_STATE_CHECK_BUTTON,
    aQMgr_TALK_SUB_STATE_HAND_ITEM_WAIT,
    aQMgr_TALK_SUB_STATE_NPC_HAND_WAIT,
    aQMgr_TALK_SUB_STATE_ITEM_WAIT,
    aQMgr_TALK_SUB_STATE_DEMO_ORDER_WAIT,
    aQMgr_TALK_SUB_STATE_NO_WAIT,
    aQMgr_TALK_SUB_STATE_NPC_HAND_WAIT_MSG_WAIT,
    aQMgr_TALK_SUB_STATE_ITEM_WAIT_END,
    aQMgr_TALK_SUB_STATE_ITEM_PLAYER_WAIT,

    aQMgr_TALK_SUB_STATE_NUM
};

enum {
    aQMgr_TALK_COMMON_SET_TARGET,
    aQMgr_TALK_COMMON_GET_ITEM_IDX,
    aQMgr_TALK_COMMON_SET_MSG_NO,
    aQMgr_TALK_COMMON_CLEAR_TALK_INFO,
    aQMgr_TALK_COMMON_SET_CHOICE_STR,
    aQMgr_TALK_COMMON_GET_SET_DATA,
    aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_ITEM,
    aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_REWARD,
    aQMgr_TALK_COMMON_TALK_INIT_OVL,
    aQMgr_TALK_COMMON_CHANGE_TALK_NORMAL,
    aQMgr_TALK_COMMON_CHANGE_TALK_ISLAND,

    aQMgr_TALK_COMMON_NUM
};

enum {
    aQMgr_TALK_KIND_QUEST,
    aQMgr_TALK_KIND_FIRST_JOB,
    aQMgr_TALK_KIND_NORMAL,
    aQMgr_TALK_KIND_ISLAND,

    aQMgr_TALK_KIND_NUM
};

enum {
    aQMgr_MSG_KIND_REQUEST_INIT,
    aQMgr_MSG_KIND_REQUEST_END,
    aQMgr_MSG_KIND_REQUEST_RECONF, // reconfirm?
    aQMgr_MSG_KIND_REQUEST_REJECT, // rejected offer
    aQMgr_MSG_KIND_COMPLETE_INIT,
    aQMgr_MSG_KIND_COMPLETE_END,
    aQMgr_MSG_KIND_FAILURE_INIT,
    aQMgr_MSG_KIND_FAILURE_END,
    aQMgr_MSG_KIND_FULL_ITEM, // pockets are full so can't give quests
    aQMgr_MSG_KIND_AFTER_REWARD,
    aQMgr_MSG_KIND_AFTER_REWARD_THANKS,
    aQMgr_MSG_KIND_REWARD_FULL_ITEM,  // pockets are full so can't give reward
    aQMgr_MSG_KIND_REWARD_FULL_ITEM2, // pockets are still full
    aQMgr_MSG_KIND_NONE,

    aQMgr_MSG_KIND_NUM = aQMgr_MSG_KIND_NONE
};

enum {
    aQMgr_TIME_MORNING,
    aQMgr_TIME_DAY,
    aQMgr_TIME_EVENING,
    aQMgr_TIME_NIGHT,

    aQMgr_TIME_NUM
};

enum {
    aQMgr_QUEST_TARGET_RANDOM,
    aQMgr_QUEST_TARGET_RANDOM_EXCLUDED,
    aQMgr_QUEST_TARGET_ORIGINAL_TARGET, // same target as before?
    aQMgr_QUEST_TARGET_FOREIGN,
    aQMgr_QUEST_TARGET_LAST_REMOVE,
    aQMgr_QUEST_TARGET_CLIENT,

    aQMgr_QUEST_TARGET_NUM
};

enum {
    aQMgr_QUEST_ITEM_RANDOM,
    aQMgr_QUEST_ITEM_FRUIT,
    aQMgr_QUEST_ITEM_CLOTH,
    aQMgr_QUEST_ITEM_FROM_DATA,
    aQMgr_QUEST_ITEM_CURRENT_ITEM,
    aQMgr_QUEST_ITEM_NONE,

    aQMgr_QUEST_ITEM_NUM
};

enum {
    aQMgr_QUEST_REWARD_FTR,
    aQMgr_QUEST_REWARD_STATIONERY,
    aQMgr_QUEST_REWARD_CLOTH,
    aQMgr_QUEST_REWARD_CARPET,
    aQMgr_QUEST_REWARD_WALLPAPER,
    aQMgr_QUEST_REWARD_MONEY,
    aQMgr_QUEST_REWARD_WORN_CLOTH,
    aQMgr_QUEST_REWARD_7,

    aQMgr_QUEST_REWARD_NUM
};

typedef struct quest_manager_actor QUEST_MANAGER_ACTOR;

typedef union {
    mQst_base_c base;
    mQst_errand_c errand;
    mQst_delivery_c delivery;
    mQst_contest_c contest;
} aQMgr_quest_c;

typedef struct quest_manager_order_s {
    u16 type;
    u16 value;
} aQMgr_order_c;

typedef struct quest_manager_set_data_s {
    u32 to_type : 3;
    u32 day_limit : 6;
    u32 last_step : 4;
    u32 handover_item : 1;
    u32 src_item_type : 3;
    mActor_name_t item;
    u8 reward_percentages[aQMgr_QUEST_REWARD_NUM];
    u32 max_pay;
    int msg_start[aQMgr_MSG_KIND_NUM];
} aQMgr_set_data_c;

typedef struct quest_manager_flower_work_data_s {
    int goal_num;
    int exist_num;
    int remain_num;
} aQMgr_flower_data_c;

typedef union {
    aQMgr_flower_data_c flower;
} aQMgr_work_data_c;

typedef struct quest_manager_target_s {
    mQst_base_c quest_info;
    AnmPersonalID_c* from_id;
    AnmPersonalID_c* to_id;
    int quest_inv_item_idx;
    mActor_name_t quest_item;
    int reward_kind;
    mActor_name_t reward_item;
    u32 pay;
    lbRTC_time_c limit;
    aQMgr_set_data_c* set_data_p;
    int free_data_idx;
    mQst_base_c* free_data_p;
    s8 errand_type;
    aQMgr_work_data_c work;
} aQMgr_target_c;

typedef struct quest_manager_regist_s aQMgr_regist_c;

typedef void (*aQMgr_CHECK_LIMIT_PROC)(QUEST_MANAGER_ACTOR*, aQMgr_regist_c*);
typedef int (*aQMgr_CHECK_FINISH_PROC)(mQst_base_c*, Animal_c*);

struct quest_manager_regist_s {
    aQMgr_CHECK_LIMIT_PROC check_limit_proc;
    aQMgr_CHECK_FINISH_PROC check_finish_proc;
    mQst_base_c* quest_info;
    PersonalID_c* pid;
    AnmPersonalID_c from_id;
    AnmPersonalID_c to_id;
    mActor_name_t item;
    int animal_idx;
};

#define aQMgr_NORMAL_TRADE_ITEM_NUM 5

typedef struct {
    Anmmem_c* memory;
    Anmplmail_c* mail;
    int pay;
    int item_idx;
    int free_idx;
    mActor_name_t trade_items[aQMgr_NORMAL_TRADE_ITEM_NUM];
} aQMgr_normal_info_c;

typedef struct quest_manager_talk_wait_s {
    int flags[3];
} aQMgr_talk_wait_info_c;

typedef struct quest_manager_choice_s {
    int choice_ids[mChoice_CHOICE_NUM];
    int choice_num;
    int talk_action;
} aQMgr_choice_c;

#define aQMgr_LAST_STR_NUM 7

typedef int (*aQMgr_TALK_COMMON_PROC)(QUEST_MANAGER_ACTOR*, int);
typedef void (*aQMgr_ACTOR_CLEAR_REGIST_PROC)(aQMgr_regist_c*, int);
typedef void (*aQMgr_ACTOR_REGIST_QUEST_PROC)(QUEST_MANAGER_ACTOR*, int*, aQMgr_quest_c*, int);
typedef int (*aQMgr_GET_TIME_KIND_PROC)(int);
typedef void (*aQMgr_TALK_INIT_PROC)(QUEST_MANAGER_ACTOR*);

/* sizeof(struct quest_manager_actor) == 0xAA0 */
struct quest_manager_actor {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ Submenu* submenu;
    /* 0x178 */ ACTOR** client;
    /* 0x17C */ Anmmem_c** memory;
    /* 0x180 */ u8* mode;
    /* 0x184 */ u8 talk_state;
    /* 0x185 */ u8 sub_talk_state;
    /* 0x186 */ u8 talk_step;
    /* 0x188 */ aQMgr_choice_c choice;
    /* 0x1A8 */ int msg_no;
    /* 0x1AC */ int category_msg_no_start;
    /* 0x1B0 */ int msg_category;
    /* 0x1B4 */ aQMgr_order_c demo_order;
    /* 0x1B8 */ aQMgr_talk_wait_info_c wait_info;
    /* 0x1C4 */ mActor_name_t handover_item;
    /* 0x1C8 */ aQMgr_target_c target;
    /* 0x214 */ aQMgr_regist_c regist[aQMgr_REGIST_NUM];
    /* 0x930 */ int regist_idx;
    /* 0x934 */ int regist_use_no;
    /* 0x938 */ int _938;
    /* 0x93C */ int _93C;
    /* 0x940 */ aQMgr_Clip_c* clip;
    /* 0x944 */ aQMgr_TALK_INIT_PROC talk_init_proc;
    /* 0x948 */ aQMgr_TALK_COMMON_PROC talk_common_proc;
    /* 0x94C */ aQMgr_ACTOR_CLEAR_REGIST_PROC clear_regist_proc;
    /* 0x950 */ aQMgr_ACTOR_REGIST_QUEST_PROC regist_quest_proc;
    /* 0x954 */ aQMgr_GET_TIME_KIND_PROC get_time_kind_proc;
    /* 0x958 */ mActor_name_t cloth;
    /* 0x95A */ u8 talk_type;
    /* 0x95B */ u8 talk_change_type;
    /* 0x95C */ u8 errand_next[mPr_ERRAND_QUEST_NUM];
    /* 0x962 */ Mail_c mail;
    /* 0xA8C */ Anmmem_c* mail_memory;
    /* 0xA90 */ u8 last_strings[aQMgr_LAST_STR_NUM];
    /* 0xA98 */ mActor_name_t give_item;
    /* 0xA9C */ int _A9C;
};

#define aQMgr_GET_CLIENT(manager) ((NPC_ACTOR*)*manager->client)
#define aQMgr_GET_CLIENT_ANIMAL(manager) aQMgr_GET_CLIENT(manager)->npc_info.animal

extern ACTOR_PROFILE Quest_Manager_Profile;

#ifdef __cplusplus
}
#endif

#endif
