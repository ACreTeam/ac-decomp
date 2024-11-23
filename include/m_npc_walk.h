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
} mNpcW_GoalDataTable_c;

enum {
  mNpcW_GOAL_SHRINE,    /* Shrine/Wishing Well acre */
  mNpcW_GOAL_HOME,      /* Randomly selected acre with a villager house */
  mNpcW_GOAL_ALONE,     /* Randomly selected acre with no other animals in it */
  mNpcW_GOAL_MY_HOME,   /* Acre containing the villager's house */

  mNpcW_GOAL_NUM
};

enum {
  mNpcW_GOAL_BLOCK_SHRINE,
  mNpcW_GOAL_BLOCK_HOME,

  mNpcW_GOAL_BLOCK_NUM
};

/* TODO: figure out remaining enums */
enum {
  mNpcW_APPEAR_STATUS_REGULAR,
  mNpcW_APPEAR_STATUS_GUEST,

  mNpcW_APPEAR_STATUS_NUM
};

enum {
  mNpcW_APPEAR_WAY_UP,
  mNpcW_APPEAR_WAY_DOWN,
  mNpcW_APPEAR_WAY_LEFT,
  mNpcW_APPEAR_WAY_RIGHT,

  mNpcW_APPEAR_WAY_NUM
};

/* TODO: figure out remaining enums */
enum {
  mNpcW_INFO_STATUS_NONE,
  mNpcW_INFO_STATUS_WALKING,
  mNpcW_INFO_STATUS_STAY_IN_BLOCK,
  mNpcW_INFO_STATUS_ARRIVE,
  mNpcW_INFO_STATUS_4,

  mNpcW_INFO_STATUS_NUM
};

typedef struct npc_walk_appear_s {
  u8 status;
  u8 way;
} mNpcW_appear_c;

typedef struct npc_walk_information_s {
  AnmPersonalID_c id;
  int idx;
  u8 status;
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

extern void mNpcW_ClearNpcWalkInfo(mNpcW_info_c* info, int num);
extern int mNpcW_GetNpcWalkInfoIdx(mNpcW_info_c* info, int num, AnmPersonalID_c* anm_id);
extern int mNpcW_ChangeNpcWalk(mNpc_walk_c* walk, mNpcW_info_c* info);
extern void mNpcW_SetGoalBlock(mNpcW_info_c* info);
extern void mNpcW_InitNpcWalk(mNpc_walk_c* walk);
extern int mNpcW_GetAppearStatusWay(u8* status, u8* way, Animal_c* animal);
extern u32* mNpcW_GetArriveStayCountP(int idx);
extern int mNpcW_GetWalkInfoStatusGoalAnimalIdx(int* status, int* goal, int idx);
extern int mNpcW_GetNearGate(int* target_ut_x, int* target_ut_z, int block_x, int block_z, int ut_x, int ut_z);

#ifdef __cplusplus
}
#endif

#endif
