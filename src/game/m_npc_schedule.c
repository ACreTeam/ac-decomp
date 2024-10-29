#include "m_npc_schedule.h"

#include "m_common_data.h"

#define mNPS_TIME_2_SEC(hour, min, sec) ((hour) * 3600 + (min) * 60 + (sec))
#define mNPS_MAKE_SCHEDULE_TABLE(sched_data) { ARRAY_SIZE(sched_data, mNPS_schedule_data_c), sched_data }

static mNPS_schedule_data_c girl_schedule_dt[] = {
  { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(5, 0, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(6, 0, 0) },
  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(12, 0, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(13, 0, 0) },
  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(18, 30, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(21, 0, 0) },
  { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(24, 0, 0) }
};

static mNPS_schedule_data_table_c girl_schedule = mNPS_MAKE_SCHEDULE_TABLE(girl_schedule_dt);

static mNPS_schedule_data_c ko_girl_schedule_dt[] = {
  { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(7, 0, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(8, 0, 0) },
  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(13, 0, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(14, 0, 0) },
  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(22, 0, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(23, 30, 0) },
  { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(24, 0, 0) }
};

static mNPS_schedule_data_table_c ko_girl_schedule = mNPS_MAKE_SCHEDULE_TABLE(ko_girl_schedule_dt);

static mNPS_schedule_data_c boy_schedule_dt[] = {
  { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(8, 0, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(9, 0, 0) },
  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(12, 0, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(14, 0, 0) },
  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(19, 30, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(22, 0, 0) },
  { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(24, 0, 0) }
};

static mNPS_schedule_data_table_c boy_schedule = mNPS_MAKE_SCHEDULE_TABLE(boy_schedule_dt);

static mNPS_schedule_data_c sport_man_schedule_dt[] = {
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(1, 0, 0) },
  { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(5, 30, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(6, 30, 0) },
  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(12, 0, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(12, 30, 0) },
  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(23, 0, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(24, 0, 0) }
};

static mNPS_schedule_data_table_c sport_man_schedule = mNPS_MAKE_SCHEDULE_TABLE(sport_man_schedule_dt);

static mNPS_schedule_data_c grim_man_schedule_dt[] = {
  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(4, 0, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(5, 0, 0) },
  { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(10, 0, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(11, 0, 0) },
  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(15, 0, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(16, 0, 0) },
  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(22, 0, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(23, 0, 0) },
  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(24, 0, 0) }
};

static mNPS_schedule_data_table_c grim_man_schedule = mNPS_MAKE_SCHEDULE_TABLE(grim_man_schedule_dt);

static mNPS_schedule_data_c naniwa_lady_schedule_dt[] = {
  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(1, 30, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(2, 30, 0) },
  { mNPS_SCHED_SLEEP, mNPS_TIME_2_SEC(9, 0, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(10, 0, 0) },
  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(13, 0, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(14, 0, 0) },
  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(21, 0, 0) },
  { mNPS_SCHED_IN_HOUSE, mNPS_TIME_2_SEC(22, 0, 0) },
  { mNPS_SCHED_FIELD, mNPS_TIME_2_SEC(24, 0, 0) }
};

static mNPS_schedule_data_table_c naniwa_lady_schedule = mNPS_MAKE_SCHEDULE_TABLE(naniwa_lady_schedule_dt);

static mNPS_schedule_data_table_c* mNPS_schedule[mNpc_LOOKS_NUM] = {
  &girl_schedule,
  &ko_girl_schedule,
  &boy_schedule,
  &sport_man_schedule,
  &grim_man_schedule,
  &naniwa_lady_schedule
};

extern mNPS_schedule_c* mNPS_get_schedule_area(AnmPersonalID_c* anm_id) {
  mNPS_schedule_c* schedule = Common_Get(npc_schedule);
  int i;

  for (i = 0; i < SCHEDULE_NUM; i++) {
    if (schedule->id == anm_id) {
      return schedule;
    }

    schedule++;
  }

  return NULL;
}

static void mNPS_set_schedule_area(AnmPersonalID_c* anm_id) {
  mNPS_schedule_c* schedule = mNPS_get_schedule_area(NULL); /* try to get an unused schedule */

  if (schedule != NULL) {
    schedule->id = anm_id;
    schedule->data_table = mNPS_schedule[anm_id->looks];
    schedule->forced_timer = 0;
  }
}

extern void mNPS_set_island_schedule_area(AnmPersonalID_c* anm_id) {
  if (Common_Get(npc_schedule[ANIMAL_NUM_MAX]).id != NULL) {
    return;
  }

  Common_Set(npc_schedule[ANIMAL_NUM_MAX].id, anm_id);
  Common_Set(npc_schedule[ANIMAL_NUM_MAX].data_table, mNPS_schedule[anm_id->looks]);
  Common_Set(npc_schedule[ANIMAL_NUM_MAX].forced_timer, 0);
}

extern void mNPS_reset_schedule_area(AnmPersonalID_c* anm_id) {
  mNPS_schedule_c* schedule = mNPS_get_schedule_area(anm_id);

  if (schedule != NULL) {
    schedule->id = NULL;
  }
}

static void mNPS_schedule_manager_sub(mNPS_schedule_c* schedule) {
  int now_sec = Common_Get(time.now_sec);
  int count = schedule->data_table->count;
  mNPS_schedule_data_c* schedule_entry = schedule->data_table->sched_data;

  /* Locate our current scehdule entry */
  for (count; count != 0; count--) {
    if (schedule_entry->end_time > now_sec) {
      break;
    }
    
    schedule_entry++;
  }

  schedule->saved_type = schedule_entry->type;
  if (schedule->forced_timer > 0) {
    schedule->current_type = schedule->forced_type;
    schedule->forced_timer--;
  }
  else {
    schedule->current_type = schedule->saved_type;
  }
}

static void mNPS_schedule_manager_sub0() {
  mNPS_schedule_c* schedule = Common_Get(npc_schedule);
  int i;

  /* Set all town animals to go outside in their home block */
  for (i = 0; i < ANIMAL_NUM_MAX; i++) {
    if (schedule->id != NULL) {
      schedule->current_type = mNPS_SCHED_FIELD;
    }

    schedule++;
  }
}

static void mNPS_schedule_manager_sub1() {
  mNPS_schedule_c* schedule = Common_Get(npc_schedule);
  int i;

  /* Set all town animals to go about their intended schedule */
  for (i = 0; i < ANIMAL_NUM_MAX; i++) {
    if (schedule->id != NULL) {
      mNPS_schedule_manager_sub(schedule);
    }

    schedule++;
  }
}

static void mNPS_island_schedule_manager() {
  mNPS_schedule_c* schedule = Common_GetPointer(npc_schedule[ANIMAL_NUM_MAX]);

  if (schedule->id != NULL) {
    mNPS_schedule_manager_sub(schedule);
  }
}

extern void mNPS_schedule_manager() {
  int force_outside = FALSE;

  if (mEv_CheckFirstJob() == TRUE || mEv_check_status(mEv_EVENT_HALLOWEEN, mEv_STATUS_ACTIVE)) {
    force_outside = TRUE;
  }

  if (force_outside == TRUE) {
    mNPS_schedule_manager_sub0();
  }
  else {
    mNPS_schedule_manager_sub1();
  }

  mNPS_island_schedule_manager();
}

extern void mNPS_set_all_schedule_area() {
  Animal_c* animal = Save_Get(animals);
  int i;

  for (i = 0; i < ANIMAL_NUM_MAX; i++) {
    if (mNpc_CheckFreeAnimalInfo(animal) == FALSE) {
      mNPS_set_schedule_area(&animal->id);
    }
    
    animal++;
  }

  mNPS_schedule_manager();
}
