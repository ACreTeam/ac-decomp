#ifndef M_SCENE_H
#define M_SCENE_H

#include "types.h"
#include "m_scene_table.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct door_data_s {
  int next_scene_id;
  u8 exit_orientation;
  u8 exit_type; // 0 = normal, 1 = restart game?
  u16 extra_data;
  s_xyz exit_position;
  mActor_name_t door_actor_name;
  u8 wipe_type;
  u8 pad[3]; // possibly necessary due to struct copy
} Door_data_c;

#ifdef __cplusplus
}
#endif

#endif
