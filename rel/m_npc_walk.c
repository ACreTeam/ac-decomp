#include "m_npc_walk.h"

#include "libultra/libultra.h"
#include "m_random_field.h"
#include "m_common_data.h"

static int l_arrive_stay_count[ANIMAL_NUM_MAX]; /* TODO: swap with l_goal_block when bss ordering is fixed */
static int l_goal_block[mNpcW_GOAL_BLOCK_NUM][2];

#define mNpcW_TIME_2_SEC(hour, min, sec) ((hour) * 3600 + (min) * 60 + (sec))
#define mNpcW_MAKE_SCHEDULE_TABLE(goal_data) { goal_data, ARRAY_SIZE(goal_data, mNpcW_GoalData_c) }

static u8 l_girl_time_12[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_HOME, mNpcW_GOAL_ALONE };
static u8 l_girl_time_18_30[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_HOME };

static mNpcW_GoalData_c l_girl_goal_data[] = { 
  { NULL, 0, mNpcW_TIME_2_SEC(6, 0, 0) },
  { l_girl_time_12, ARRAY_SIZE(l_girl_time_12, u8), mNpcW_TIME_2_SEC(12, 0, 0) },
  { NULL, 0, mNpcW_TIME_2_SEC(13, 0, 0) },
  { l_girl_time_18_30, ARRAY_SIZE(l_girl_time_18_30, u8), mNpcW_TIME_2_SEC(18, 30, 0) },
  { NULL, 0, mNpcW_TIME_2_SEC(24, 0, 0) }
};

static mNpcW_GoalDataTable_c l_girl_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_girl_goal_data);

static u8 l_kogirl_time_ed[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_HOME };

static mNpcW_GoalData_c l_kogirl_goal_data[] = { 
  { l_kogirl_time_ed, ARRAY_SIZE(l_kogirl_time_ed, u8), mNpcW_TIME_2_SEC(24, 0, 0) }
};

static mNpcW_GoalDataTable_c l_kogirl_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_kogirl_goal_data);

static u8 l_boy_time_12[] = { mNpcW_GOAL_ALONE };
static u8 l_boy_time_19_30[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_HOME };

static mNpcW_GoalData_c l_boy_goal_data[] = { 
  { NULL, 0, mNpcW_TIME_2_SEC(9, 0, 0) },
  { l_boy_time_12, ARRAY_SIZE(l_boy_time_12, u8), mNpcW_TIME_2_SEC(12, 0, 0) },
  { NULL, 0, mNpcW_TIME_2_SEC(14, 0, 0) },
  { l_boy_time_19_30, ARRAY_SIZE(l_boy_time_19_30, u8), mNpcW_TIME_2_SEC(19, 30, 0) },
  { NULL, 0, mNpcW_TIME_2_SEC(24, 0, 0) }
};

static mNpcW_GoalDataTable_c l_boy_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_boy_goal_data);

static u8 l_sports_man_time_12[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_HOME, mNpcW_GOAL_ALONE, mNpcW_GOAL_ALONE };
static u8 l_sports_man_time_23[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_HOME, mNpcW_GOAL_HOME, mNpcW_GOAL_ALONE };

static mNpcW_GoalData_c l_sports_man_goal_data[] = { 
  { NULL, 0, mNpcW_TIME_2_SEC(6, 30, 0) },
  { l_sports_man_time_12, ARRAY_SIZE(l_sports_man_time_12, u8), mNpcW_TIME_2_SEC(12, 0, 0) },
  { NULL, 0, mNpcW_TIME_2_SEC(12, 30, 0) },
  { l_sports_man_time_23, ARRAY_SIZE(l_sports_man_time_23, u8), mNpcW_TIME_2_SEC(23, 0, 0) },
  { NULL, 0, mNpcW_TIME_2_SEC(24, 0, 0) }
};

static mNpcW_GoalDataTable_c l_sports_man_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_sports_man_goal_data);

static u8 l_grim_man_time_ed[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_ALONE, mNpcW_GOAL_ALONE, mNpcW_GOAL_ALONE, mNpcW_GOAL_ALONE, mNpcW_GOAL_ALONE, mNpcW_GOAL_ALONE, mNpcW_GOAL_ALONE };

static mNpcW_GoalData_c l_grim_man_goal_data[] = { 
  { l_grim_man_time_ed, ARRAY_SIZE(l_grim_man_time_ed, u8), mNpcW_TIME_2_SEC(24, 0, 0) }
};

static mNpcW_GoalDataTable_c l_grim_man_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_grim_man_goal_data);

static u8 l_naniwa_lady_time_1_30[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_ALONE, mNpcW_GOAL_ALONE, mNpcW_GOAL_ALONE };
static u8 l_naniwa_lady_time_13[] = { mNpcW_GOAL_HOME };
static u8 l_naniwa_lady_time_21[] = { mNpcW_GOAL_SHRINE, mNpcW_GOAL_SHRINE, mNpcW_GOAL_HOME, mNpcW_GOAL_HOME, mNpcW_GOAL_ALONE };

static mNpcW_GoalData_c l_naniwa_lady_goal_data[] = { 
  { l_naniwa_lady_time_1_30, ARRAY_SIZE(l_naniwa_lady_time_1_30, u8), mNpcW_TIME_2_SEC(1, 30, 0) },
  { NULL, 0, mNpcW_TIME_2_SEC(10, 0, 0) },
  { l_naniwa_lady_time_13, ARRAY_SIZE(l_naniwa_lady_time_13, u8), mNpcW_TIME_2_SEC(13, 0, 0) },
  { NULL, 0, mNpcW_TIME_2_SEC(14, 0, 0) },
  { l_naniwa_lady_time_21, ARRAY_SIZE(l_naniwa_lady_time_21, u8), mNpcW_TIME_2_SEC(21, 0, 0) },
  { NULL, 0, mNpcW_TIME_2_SEC(22, 0, 0) },
  { l_naniwa_lady_time_1_30, ARRAY_SIZE(l_naniwa_lady_time_1_30, u8), mNpcW_TIME_2_SEC(24, 0, 0) }
};

static mNpcW_GoalDataTable_c l_naniwa_lady_goal_table = mNpcW_MAKE_SCHEDULE_TABLE(l_naniwa_lady_goal_data);

static mNpcW_GoalDataTable_c* l_looks_goal_table[mNpc_LOOKS_NUM] = {
  &l_girl_goal_table,
  &l_kogirl_goal_table,
  &l_boy_goal_table,
  &l_sports_man_goal_table,
  &l_grim_man_goal_table,
  &l_naniwa_lady_goal_table
};

static mNpcW_GoalData_c* mNpcW_GetGoalDataInfo(int looks, int now_sec) {
  int goal_num = l_looks_goal_table[looks]->count;
  mNpcW_GoalData_c* goal_data_save = l_looks_goal_table[looks]->data_p;
  mNpcW_GoalData_c* goal_data = goal_data_save;
  int i;

  for (i = 0; i < goal_num; i++) {
    if (goal_data->end_time > now_sec) {
      break;
    }

    goal_data++;
  }

  if (i != goal_num) {
    return goal_data;
  }

  return &goal_data_save[goal_num - 1];
}

static void mNpcW_ClearNpcWalkAppear(mNpcW_appear_c* appear) {
  appear->status = mNpcW_APPEAR_STATUS_NUM;
  appear->way = mNpcW_APPEAR_WAY_NUM;
}

extern void mNpcW_ClearNpcWalkInfo(mNpcW_info_c* info, int num) {
  for (num; num != 0 && info != NULL; num--) {
    bzero(info, sizeof(mNpcW_info_c));
    mNpc_ClearAnimalPersonalID(&info->id);
    info->idx = -1;
    info->status = mNpcW_INFO_STATUS_NUM;
    info->goal_type = mNpcW_GOAL_NUM;
    mNpcW_ClearNpcWalkAppear(&info->appear_info);

    info++;
  }
}

static void mNpcW_ClearNpcWalk(mNpc_walk_c* walk_info) {
  bzero(walk_info, sizeof(mNpc_walk_c));
  mNpcW_ClearNpcWalkInfo(walk_info->info, mNpcW_MAX);
}

static int mNpcW_CheckFreeNpcWalkInfo(mNpcW_info_c* info) {
  int res = FALSE;

  if (info != NULL) {
    res = mNpc_CheckFreeAnimalPersonalID(&info->id);
  }

  return res;
}

static int mNpcW_GetFreeNpcWalkInfoIdx(mNpcW_info_c* info, int num) {
  int idx = -1;
  int i;

  for (i = 0; i < num; i++) {
    if (mNpcW_CheckFreeNpcWalkInfo(info) == TRUE) {
      idx = i;
      break;
    }

    info++;
  }

  return idx;
}

extern int mNpcW_GetNpcWalkInfoIdx(mNpcW_info_c* info, int num, AnmPersonalID_c* anm_id) {
  int idx = -1;
  int i;

  if (anm_id != NULL && mNpc_CheckFreeAnimalPersonalID(anm_id) == FALSE) {
    for (i = 0; i < num; i++) {
      if (mNpc_CheckCmpAnimalPersonalID(anm_id, &info->id) == TRUE) {
        idx = i;
        break;
      }

      info++;
    }
  }

  return idx;
}

static int mNpcW_DecideNpc(Animal_c* animal, u16 used) {
  int idx;
  u16 exist;
  u16 possible_goal;
  int unused;
  int now_sec;
  int i;

  now_sec = Common_Get(time.now_sec);
  exist = 0;
  possible_goal = 0;
  unused = 0;
  idx = -1;

  for (i = 0; i < ANIMAL_NUM_MAX; i++) {
    if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
      mNpcW_GoalData_c* goal_data;
      
      exist |= (1 << i);
      goal_data = mNpcW_GetGoalDataInfo(animal->id.looks, now_sec);

      if (goal_data != NULL) {
        if (goal_data->count != 0) {
          possible_goal |= (1 << i);

          if (((used >> i) & 1) == FALSE) {
            unused++;
          }
        }
      }
    }

    animal++;
  }

  if (unused > 0) {
    int selected_num;
    u32 selection_field = possible_goal & (exist & ~used); /* clear the possible bitfield to only include unused existing villagers */

    selected_num = RANDOM(unused) + 1;

    while (selected_num != 0) {
      if ((selection_field & 1) == TRUE) {
        selected_num--;
      }

      selection_field >>= 1;
      idx++;
    }
  }

  return idx;
}

static void mNpcW_SetNpcWalkInfo(mNpcW_info_c* info, Animal_c* animal, int idx) {
  int now_sec = Common_Get(time.now_sec);
  mNpcW_GoalData_c* goal_data;
  
  mNpc_CopyAnimalPersonalID(&info->id, &animal->id);
  info->idx = idx;
  goal_data = mNpcW_GetGoalDataInfo(animal->id.looks, now_sec);

  if (goal_data != NULL && goal_data->count != 0) {
    info->goal_type = goal_data->types[RANDOM(goal_data->count)];
  }
  else {
    info->goal_type = mNpcW_GOAL_MY_HOME; /* Default to acre the villager's house is in */
  }

  info->status = mNpcW_INFO_STATUS_WALKING;
}

extern int mNpcW_ChangeNpcWalk(mNpc_walk_c* walk, mNpcW_info_c* info) {
  mNpcW_info_c* walk_info = walk->info;
  int free_idx;
  Animal_c* animals;
  int idx = -1;

  mNpcW_ClearNpcWalkInfo(info, 1);
  free_idx = mNpcW_GetFreeNpcWalkInfoIdx(walk_info, mNpcW_MAX);

  if (free_idx != -1) {
    mNpcW_info_c* free_info = &walk_info[free_idx];
    
    mNpcW_ClearNpcWalkInfo(free_info, 1);
    animals = Save_Get(animals);
    idx = mNpcW_DecideNpc(animals, walk->used_idx_bitfield);

    if (idx == -1) {
      int i;

      walk->used_idx_bitfield = 0;
      for (i = 0; i < mNpcW_MAX; i++) {
        int animal_idx = walk_info[i].idx;

        if (animal_idx >= 0 && animal_idx < ANIMAL_NUM_MAX) {
          walk->used_idx_bitfield |= (1 << animal_idx);
        }
      }

      idx = mNpcW_DecideNpc(animals, walk->used_idx_bitfield);
    }

    if (idx != -1) {
      mNpcW_SetNpcWalkInfo(free_info, Save_GetPointer(animals[idx]), idx);
      walk->used_idx_bitfield |= (1 << idx);
      mNpcW_SetGoalBlock(free_info);
    }
  }

  return idx;
}

static int mNpcW_GetAloneBlock(u8* goal_block_x, u8* goal_block_z) {
  u8 block_field[FG_BLOCK_Z_NUM + 2];
  Animal_c* animal = Save_Get(animals);
  mNpc_NpcList_c* npclist = Common_Get(npclist);
  u8 animal_count = 0;
  int selected;
  int bz;
  int bx;
  int i;
  int z;

  //   0 1 2 3 4 5 6
  // Q - - - - - - -
  // A - - - - - - -
  // B - - - - - - -
  // C - - - - - - -
  // D - - - x - - -
  // E - - - - - - -
  // F - - - - - - -
  // Z - - - - - - -

  /* Default goal block is D-3 */
  *goal_block_x = 3;
  *goal_block_z = 4;

  bzero(block_field, FG_BLOCK_Z_NUM + 2);
  /* Log all acres which currently have a villager in them */
  for (i = 0; i < ANIMAL_NUM_MAX; i++) {
    if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
      int block_x;
      int block_z;

      if (mFI_Wpos2BlockNum(&block_x, &block_z, npclist->position) == TRUE) {
        animal_count++;
        block_field[block_z] |= (1 << block_x);
      }
    }

    animal++;
    npclist++;
  }

  /* Select a random empty acre to go to */
  z = 1;
  selected = RANDOM(FG_BLOCK_TOTAL_NUM - animal_count);
  /* Find the random acre and set output */
  for (bz = 1; bz < BLOCK_Z_NUM - 3; bz++) {
    for (bx = 1; bx < BLOCK_X_NUM - 1; bx++) {
      if ((((block_field[z]) >> bx) & 1) == 0) {
        if (selected <= 0) {
          *goal_block_x = bx;
          *goal_block_z = bz;
          return TRUE;
        }
        else {
          selected--;
        }
      }
    }
    
    z++;
  }

  return FALSE;
}

static void mNpcW_GetBlockXZNumExceptHome(int* goal_block_x, int* goal_block_z, Animal_c* animal) {
  u8 possible_x = 0b11111111;
  u8 possible_z = 0b11111111;
  
  int x_num = 0;
  int z_num = 0;

  int selected_x;
  int selected_z;

  int i;

  for (i = 0; i < ANIMAL_NUM_MAX; i++) {
    if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
      u8 home_block_x = animal->home_info.block_x - 1;
      u8 home_block_z = animal->home_info.block_z - 1;

      if (((possible_x >> home_block_x) & 1) == 1) {
        x_num++;
        possible_x &= ~(1 << home_block_x);
      }

      if (((possible_z >> home_block_z) & 1) == 1) {
        z_num++;
        possible_z &= ~(1 << home_block_z);
      }
    }

    animal++;
  }

  selected_x = RANDOM(FG_BLOCK_X_NUM - x_num);
  selected_z = RANDOM(FG_BLOCK_Z_NUM - z_num);

  for (i = 0; i < FG_BLOCK_X_NUM; i++) {
    if (((possible_x >> i) & 1) == 1) {
      if (selected_x <= 0) {
        break;
      }
      else {
        selected_x--;
      }
    }
  }

  *goal_block_x = i + 1;

  for (i = 0; i < FG_BLOCK_Z_NUM; i++) {
    if (((possible_z >> i) & 1) == 1) {
      if (selected_z <= 0) {
        break;
      }
      else {
        selected_z--;
      }
    }
  }

  *goal_block_z = i + 1;

  if (*goal_block_x <= 0 || *goal_block_x >= BLOCK_X_NUM || *goal_block_z <= 0 || *goal_block_z >= (BLOCK_Z_NUM - 2)) {
    *goal_block_x = 4;
    *goal_block_z = 3;
  }
}

static int mNpcW_CheckDiffBlockWalkNpcHome(int block_x, int block_z, mNpcW_info_c* info) {
  int res = FALSE;
  Anmhome_c* home;
  int i;

  for (i = 0; i < mNpcW_MAX; i++) {
    if (info->idx != -1) {
      home = Save_GetPointer(animals[info->idx].home_info);

      if (home->block_x == block_x && home->block_z == block_z) {
        break;
      }
    }

    info++;
  }

  if (i == mNpcW_MAX) {
    res = TRUE;
  }

  return res;
}

static void mNpcW_SetHomeBlockSource(mNpc_walk_c* walk, Animal_c* animal) {
  Animal_c* animal_p = animal;
  u16 diff_animal_field;
  int diff_animal_num;
  int i;
  
  l_goal_block[mNpcW_GOAL_BLOCK_HOME][0] = 0;
  l_goal_block[mNpcW_GOAL_BLOCK_HOME][1] = 0;

  animal = animal_p;
  diff_animal_field = 0;
  diff_animal_num = 0;

  for (i = 0; i < ANIMAL_NUM_MAX; i++) {
    if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
      Anmhome_c* home = &animal->home_info;

      if (home->block_x != 0xFF && home->block_z != 0xFF) {
        if (mNpcW_CheckDiffBlockWalkNpcHome(home->block_x, home->block_z, walk->info) == TRUE) {
          diff_animal_num++;
          diff_animal_field |= (1 << i);
        }
      }
    }

    animal++;
  }

  if (diff_animal_num > 0) {
    int selected = RANDOM(diff_animal_num);
    
    animal = animal_p;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
      if (((diff_animal_field >> i) & 1) == 1) {
        if (selected == 0) {
          l_goal_block[mNpcW_GOAL_BLOCK_HOME][0] = animal->home_info.block_x;
          l_goal_block[mNpcW_GOAL_BLOCK_HOME][1] = animal->home_info.block_z;
          break;
        }
        else {
          selected--;
        }
      }

      animal++;
    }
  }

  if (l_goal_block[mNpcW_GOAL_BLOCK_HOME][0] == 0 || l_goal_block[mNpcW_GOAL_BLOCK_HOME][1] == 0) {
    mNpcW_GetBlockXZNumExceptHome(&l_goal_block[mNpcW_GOAL_BLOCK_HOME][0], &l_goal_block[mNpcW_GOAL_BLOCK_HOME][1], animal_p);
  }

  if (
    l_goal_block[mNpcW_GOAL_BLOCK_HOME][0] <= 0 || l_goal_block[mNpcW_GOAL_BLOCK_HOME][0] >= BLOCK_X_NUM ||
    l_goal_block[mNpcW_GOAL_BLOCK_HOME][1] <= 0 || l_goal_block[mNpcW_GOAL_BLOCK_HOME][1] >= (BLOCK_Z_NUM - 2)
  ) {
    l_goal_block[mNpcW_GOAL_BLOCK_HOME][0] = 4;
    l_goal_block[mNpcW_GOAL_BLOCK_HOME][1] = 3;
  }
}

static void mNpcW_InitGoalBlockSource(mNpc_walk_c* walk, Animal_c* animal) {
  int shrine_x;
  int shrine_z;

  if (mFI_BlockKind2BkNum(&shrine_x, &shrine_z, mRF_BLOCKKIND_SHRINE) == FALSE) {
    shrine_x = 4;
    shrine_z = 3;
  }

  l_goal_block[mNpcW_GOAL_BLOCK_SHRINE][0] = shrine_x;
  l_goal_block[mNpcW_GOAL_BLOCK_SHRINE][1] = shrine_z;

  mNpcW_SetHomeBlockSource(walk, animal);
}

extern void mNpcW_SetGoalBlock(mNpcW_info_c* info) {
  switch (info->goal_type) {
    case mNpcW_GOAL_SHRINE:
    {
      info->goal_block_x = l_goal_block[mNpcW_GOAL_BLOCK_SHRINE][0];
      info->goal_block_z = l_goal_block[mNpcW_GOAL_BLOCK_SHRINE][1];
      break;
    }

    case mNpcW_GOAL_HOME:
    {
      info->goal_block_x = l_goal_block[mNpcW_GOAL_BLOCK_HOME][0];
      info->goal_block_z = l_goal_block[mNpcW_GOAL_BLOCK_HOME][1];
      break;
    }

    case mNpcW_GOAL_ALONE:
    {
      mNpcW_GetAloneBlock(&info->goal_block_x, &info->goal_block_z);
      break;
    }

    case mNpcW_GOAL_MY_HOME:
    {
      int idx = info->idx;

      if (idx == -1) {
        idx = 0;
      }

      info->goal_block_x = Save_Get(animals[idx]).home_info.block_x;
      info->goal_block_z = Save_Get(animals[idx]).home_info.block_z;
      break;
    }

    default:
    {
      info->goal_block_x = 4;
      info->goal_block_z = 3;
      break;
    }
  }

  if (info->goal_block_x <= 0 || info->goal_block_x >= BLOCK_X_NUM || info->goal_block_z <= 0 || info->goal_block_z >= (BLOCK_Z_NUM - 2)) {
    info->goal_block_x = 4;
    info->goal_block_z = 3;
  }
}

extern void mNpcW_InitNpcWalk(mNpc_walk_c* walk) {
  Animal_c* animal;
  int npc_max;
  mNpcW_info_c* info = walk->info;
  int idx;
  int i;

  mNpcW_ClearNpcWalk(walk);
  bzero(l_goal_block, sizeof(l_goal_block));
  bzero(l_arrive_stay_count, sizeof(l_arrive_stay_count));

  animal = Save_Get(animals);
  npc_max = mNpcW_GET_WALK_NUM(Save_Get(now_npc_max));

  for (i = 0; i < npc_max; i++) {
    idx = mNpcW_DecideNpc(animal, walk->used_idx_bitfield);
    if (idx == -1) {
      break;
    }

    mNpcW_SetNpcWalkInfo(info, Save_GetPointer(animals[idx]), idx);
    walk->used_idx_bitfield |= (1 << idx);
    info++;
  }

  mNpcW_InitGoalBlockSource(walk, animal);
}

extern int mNpcW_GetAppearStatusWay(u8* status, u8* way, Animal_c* animal) {
  mNpc_walk_c* walk = Common_GetPointer(npc_walk);
  int info_idx;
  int res = FALSE;

  *status = mNpcW_APPEAR_STATUS_NUM;

  info_idx = mNpcW_GetNpcWalkInfoIdx(walk->info, mNpcW_MAX, &animal->id);

  if (info_idx >= 0) {
    *status = walk->info[info_idx].appear_info.status;
    *way = walk->info[info_idx].appear_info.way;
    res = TRUE;
  }
  else {
    *status = mNpcW_APPEAR_STATUS_0;
    *way = mNpcW_APPEAR_WAY_NUM;
  }

  return res;
}

extern int* mNpcW_GetArriveStayCountP(int idx) {
  if (idx >= 0 && idx < ANIMAL_NUM_MAX) {
    return &l_arrive_stay_count[idx];
  }

  return NULL;
}

extern int mNpcW_GetWalkInfoStatusGoalAnimalIdx(int* status, int* goal, int idx) {
  int res;
  
  *status = mNpcW_INFO_STATUS_NUM;
  *goal = mNpcW_GOAL_NUM;
  res = FALSE;

  if (idx >= 0 && idx < ANIMAL_NUM_MAX) {
    mNpc_walk_c* walk = Common_GetPointer(npc_walk);
    int info_idx = mNpcW_GetNpcWalkInfoIdx(walk->info, mNpcW_MAX, &Save_Get(animals[idx]).id);
    
    if (info_idx >= 0) {
      res = TRUE;
      *status = walk->info[info_idx].status;
      *goal = walk->info[info_idx].goal_type;
    }
  }

  return res;
}

extern int mNpcW_GetNearGate(int* target_ut_x, int* target_ut_z, int block_x, int block_z, int ut_x, int ut_z) {
  u8 block_type;
  int t_ut_x;
  int t_ut_z;
  mRF_gate_c* gate;
  int gate_count;
  int x;
  int z;
  int i;
  int direction;
  int res = FALSE;
  
  *target_ut_x = UT_X_NUM;
  *target_ut_z = UT_Z_NUM;

  if (ut_x >= 0 && ut_x < UT_X_NUM && ut_z >= 0 && ut_z < UT_Z_NUM) {
    block_type = mFI_BkNum2BlockType(block_x, block_z);
    t_ut_x = ut_x < (UT_X_NUM / 2) ? ut_x : UT_X_NUM - ut_x;
    t_ut_z = ut_z < (UT_Z_NUM / 2) ? ut_z : UT_Z_NUM - ut_z;


    if (t_ut_x < t_ut_z) {
      if (ut_x < (UT_X_NUM / 2)) {
        direction = mRF_DIRECT_WEST;
      }
      else {
        direction = mRF_DIRECT_EAST;
      }
    }
    else {
      if (ut_z < (UT_Z_NUM / 2)) {
        direction = mRF_DIRECT_NORTH;
      }
      else {
        direction = mRF_DIRECT_SOUTH;
      }
    }

    gate = mRF_BlockTypeDirect2GateData(&gate_count, block_type, direction);
    if (gate != NULL && gate_count > 0) {
      

      for (i = 0; i < gate_count; i++) {
        int difference;
        x = gate->ut1 & 0xF;
        z = gate->ut1 >> 4;
        
        /* BUG: this is likely meant to be 'if (direction == mRF_DIRECT_WEST || direction == mRF_DIRECT_EAST)' */
        #ifndef BUGFIXES
        if (direction == mRF_DIRECT_WEST || direction == mRF_DIRECT_WEST) {
        #else
        if (direction == mRF_DIRECT_WEST || direction == mRF_DIRECT_EAST) {
        #endif
          difference = ut_z - z;
          difference = ABS(difference);
        }
        else {
          difference = ut_x - x;
          difference = ABS(difference);
        }

        if (difference < UT_BASE_NUM) {
          *target_ut_x = x;
          *target_ut_z = z;
          res = TRUE;
        }

        gate++;
      }
    }
  }

  return res;
}
