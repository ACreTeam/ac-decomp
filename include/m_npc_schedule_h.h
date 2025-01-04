#ifndef M_NPC_SCHEDULE_H_H
#define M_NPC_SCHEDULE_H_H

#include "types.h"
#include "m_npc_personal_id.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  mNPS_SCHED_FIELD, /* in same acre as their home */
  mNPS_SCHED_IN_HOUSE, /* inside their house */
  mNPS_SCHED_SLEEP, /* asleep in their house */
  mNPS_SCHED_STAND, /* standing around town?? */
  mNPS_SCHED_WANDER, /* wander around town */
  mNPS_SCHED_WALK_WANDER, /* walk wander */
  mNPS_SCHED_SPECIAL, /* unique schedule method for each NPC actor type */

  mNPS_SCHED_TYPE_NUM
};

typedef struct schedule_data_s {
  u32 type;
  int end_time;
} mNPS_schedule_data_c;

typedef struct schedule_data_table_s {
  int count;
  mNPS_schedule_data_c* sched_data;
} mNPS_schedule_data_table_c;

typedef struct schedule_s {
  AnmPersonalID_c* id;
  mNPS_schedule_data_table_c* data_table;
  u8 current_type;
  u8 forced_type;
  u8 saved_type;
  int forced_timer;
} mNPS_schedule_c;

#ifdef __cplusplus
}
#endif

#endif
