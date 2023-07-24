#ifndef M_NPC_WALK_H
#define M_NPC_WALK_H

#include "types.h"
#include "m_npc_personal_id.h"
#include "m_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mNpcW_GET_WALK_NUM(x) (int)((x) / 3)
#define mNpcW_MAX mNpcW_GET_WALK_NUM(ANIMAL_NUM_MAX)

typedef struct goal_data_s {
  u8* types;
  u8 count;
  int end_time;
} mNpcW_GoalData_c;

typedef struct goal_data_table_s {
  mNpcW_GoalData_c* data_p;
  int count;
} mNpc_GoalDataTable_c;

enum {
  mNpcW_GOAL_SHRINE,    /* Shrine/Wishing Well acre */
  mNpcW_GOAL_HOME,      /* Randomly selected acre with a villager house */
  mNpcW_GOAL_ALONE,     /* Randomly selected acre with no other animals in it */
  mNpcW_GOAL_MY_HOME,   /* Acre containing the villager's house */

  mNpcW_GOAL_NUM
};

typedef struct npc_walk_appear_s {
  u8 state;
  u8 target_direction;
} mNpcW_appear_c;

typedef struct npc_walk_information_s {
  AnmPersonalID_c id;
  int idx;
  u8 state;
  u8 goal_type;
  u8 goal_block_x;
  u8 goal_block_z;
  mNpcW_appear_c appear_info;
} mNpcW_info_c;

typedef struct npc_walk_s {
  mNpcW_info_c info[mNpcW_MAX];
  u16 used_idx_bitfield;
  u8 used_info_num;
  u8 info_max;
} mNpc_walk_c;

#ifdef __cplusplus
}
#endif

#endif
