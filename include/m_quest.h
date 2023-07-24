#ifndef M_QUEST_H
#define M_QUEST_H

#include "types.h"
#include "libu64/gfxprint.h"
#include "lb_rtc.h"
#include "m_actor_type.h"
#include "m_personal_id.h"
#include "m_npc_personal_id.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  mQst_QUEST_TYPE_DELIVERY, /* Deliver item quest */
  mQst_QUEST_TYPE_ERRAND,   /* Villager 'can I help' quests */
  mQst_QUEST_TYPE_CONTEST,  /* Villager send letter, plant flowers, bring ball, etc */
  mQst_QUEST_TYPE_NONE
};

/* sizeof(mQst_base_c) == 0xC */
typedef struct quest_base_s {
  /* 0x00 */ u32 quest_type:2; /* type, 0 = delivery, 1 = errand, 2 = contest, 3 = none */
  /* 0x00 */ u32 quest_kind:6; /* kind, differs by type */
  /* 0x01 */ u32 time_limit_enabled:1; /* when set, the time limit will be utilized */
  /* 0x01 */ u32 progress:4; /* progress towards quest goal */
  /* 0x01 */ u32 give_reward:1; /* set to true when player cannot take the item, and will skip quest completion checks */
  /* 0x01 */ u32 unused:2;

  /* 0x02 */ lbRTC_time_c time_limit;
} mQst_base_c;

/* Contest Quest */

enum {
  mQst_CONTEST_KIND_FRUIT,   /* get fruit for villager */
  mQst_CONTEST_KIND_SOCCER,  /* get ball for villager */
  mQst_CONTEST_KIND_SNOWMAN, /* build snowman for villager */
  mQst_CONTEST_KIND_FLOWER,  /* plant flowers for villager */
  mQst_CONTEST_KIND_FISH,    /* get fish for villager */
  mQst_CONTEST_KIND_INSECT,  /* get insect for villager */
  mQst_CONTEST_KIND_LETTER   /* send letter to villager */
};

/* sizeof(mQst_contest_info_u) == 4 */
typedef union quest_contest_info_s {
  struct {
    /* 0x00 */ u8 flowers_requested; /* number of flowers village requests be planted in acre */
  } flower_data;

  struct {
    /* 0x00 */ u8 score; /* score rank of letter */
    /* 0x02 */ mActor_name_t present; /* present sent with letter */
  } letter_data;
} mQst_contest_info_u;

/* sizeof(mQst_contest_c) == 0x28 */
typedef struct quest_contest_s {
  /* 0x00 */ mQst_base_c base; /* quest base struct */
  /* 0x0C */ mActor_name_t requested_item; /* item (if any) requested by the villager */
  /* 0x0E */ PersonalID_c player_id; /* personal id of the player */
  /* 0x22 */ s8 type; /* type of quest, seems to be repeat of data in quest base */
  /* 0x24 */ mQst_contest_info_u info; /* contest info for flower & letter quests */
} mQst_contest_c;

/* Delivery Quest */

/* sizeof(mQst_delivery_c) == 0x28 */
typedef struct quest_delivery_s {
  /* 0x00 */ mQst_base_c base; /* quest base info */
  /* 0x0C */ AnmPersonalID_c recipient; /* villager who will receive it */
  /* 0x1A */ AnmPersonalID_c sender; /* villager who sent it */
} mQst_delivery_c;

/* Errand Quest */
#define mQst_ERRAND_FIRST_JOB_ANIMAL_NUM 2
#define mQst_ERRAND_CHAIN_ANIMAL_NUM 3

enum {
  mQst_ERRAND_TYPE_NONE,
  mQst_ERRAND_TYPE_CHAIN,
  mQst_ERRAND_TYPE_FIRST_JOB
};

/* sizeof(mQst_first_job_c) == 0x20 */
typedef struct quest_first_job_s {
  /* 0x00 */ AnmPersonalID_c used_ids[mQst_ERRAND_FIRST_JOB_ANIMAL_NUM]; /* villagers already used for first job quest (furniture, then letter) */
  /* 0x1C */ u8 used_num:7; /* used count for 'used_ids' */
  /* 0x1C */ u8 wrong_cloth:1; /* set to TRUE if player changes out of work uniform during chores */
} mQst_firstjob_c;

/* sizeof(mQst_errand_chain_c) == 0x2C */
typedef struct quest_errand_chain_s {
  /* 0x00 */ AnmPersonalID_c used_ids[mQst_ERRAND_CHAIN_ANIMAL_NUM];
  /* 0x2A */ u8 used_num;
} mQst_errand_chain_c;

/* sizeof(mQst_errand_info_u) == 0x2C */
typedef union {
  mQst_errand_chain_c chain;
  mQst_firstjob_c first_job;
} mQst_errand_info_u;

/* sizeof(mQst_errand_c) == 0x58 */
typedef struct quest_errand_s {
  /* 0x00 */ mQst_base_c base; /* quest base info */
  /* 0x0C */ AnmPersonalID_c recipient; /* villager who will receive it */
  /* 0x1A */ AnmPersonalID_c sender; /* villager who sent it */
  /* 0x28 */ mActor_name_t item; /* errand item */
  /* 0x2A */ s8 pockets_idx:5; /* index in player pockets where the errand item is */
  /* 0x2A */ s8 errand_type:3; /* errand type */
  /* 0x2C */ mQst_errand_info_u info; /* errand type-specific data */
} mQst_errand_c;

/* 'Not Saved' Quest */
typedef struct not_saved_quest_s {
  int work;
  u8 h;
} mQst_not_saved_c;

extern void mQst_PrintQuestInfo(gfxprint_t* gfxprint);
extern void mQst_ClearGrabItemInfo();

#ifdef __cplusplus
}
#endif

#endif
