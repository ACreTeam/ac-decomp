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

#define mSc_OBJECT_BANK_NUM 70

typedef struct object_bank_s {
  s16 bank_id;
  char* ram_start;
  // TODO: others
  u8 _08[0x58 - 0x08];
  s16 num_exist;
  u8 _0x5A[0x5C - 0x5A];
} Object_Bank_c;

typedef struct object_exchange_s {
  Object_Bank_c banks[mSc_OBJECT_BANK_NUM];
  int _1928;
  int _192C;
  int exchange_id;
  u8 _1934[0x1958-0x1934];
} Object_Exchange_c;

extern int mSc_bank_regist_check(Object_Exchange_c* exchange, s16 bank_id);
extern void mSc_regist_initial_exchange_bank(GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
