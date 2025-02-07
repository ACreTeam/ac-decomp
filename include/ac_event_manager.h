#ifndef AC_EVENT_MANAGER_H
#define AC_EVENT_MANAGER_H

#include "types.h"
#include "m_actor.h"
#include "m_npc.h"
#include "m_olib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct event_manager_actor_s EVENT_MANAGER_ACTOR;

enum {
  aEvMgr_EVENT_PLACE_SHRINE = 4,
};

typedef int (*aEvMgr_TITLE_FADE_PROC)(EVENT_MANAGER_ACTOR*, int, int, u32);

typedef struct event_manager_clip_s {
  EVENT_MANAGER_ACTOR* event_manager_actor;
  aEvMgr_TITLE_FADE_PROC title_fade_proc;
} aEvMgr_Clip_c;

typedef struct event_manager_field_info_s {
  BlockOrUnit_c block_max;
  Anmhome_c* reserve_buf;
  int reserve_num;
} aEvMgr_field_info_c;

typedef struct event_manager_player_pos_s {
    int bx;
    int bz;
    int last_bx;
    int last_bz;
} aEvMgr_player_pos_c;

struct event_manager_actor_s {
  ACTOR actor_class;
  aEvMgr_player_pos_c player_pos;
  u8 _184[0x1E8 - 0x184];
  aEvMgr_field_info_c field_info;
  int _1F8;
  int _1FC;
  int month_day;
  int day_hour;
  int change;
  BlockOrUnit_c next_block;
  BlockOrUnit_c pool_block;
  int pool_block_exists;
  BlockOrUnit_c station_block;
  int station_block_exists;
  BlockOrUnit_c shrine_block;
  int shrine_block_exists;
  BlockOrUnit_c player_home_block;
  int player_home_exists;
  BlockOrUnit_c dock_block;
  int dock_block_exists;
  int skip_event_at_wade;
  int _254;
  aEvMgr_Clip_c clip;
};

extern ACTOR_PROFILE Event_Manager_Profile;

#ifdef __cplusplus
}
#endif

#endif
