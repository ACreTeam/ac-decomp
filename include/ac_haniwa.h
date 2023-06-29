#ifndef AC_HANIWA_H
#define AC_HANIWA_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"
#include "m_collision_obj.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct actor_haniwa_s HANIWA_ACTOR;

typedef void (*HANIWA_ACTOR_PROC)(ACTOR*, GAME*);

enum haniwa_msg {
  aHNW_MSG_NO_OWNER,
  aHNW_MSG_PROCEEDS,
  aHNW_MSG_NORMAL,
  aHNW_MSG_OTHER_OWNER,
  aHNW_MSG_NEED_FRIEND,

  aHNW_MSG_NUM
};

enum haniwa_handover {
  aHNW_HANDOVER_YES,
  aHNW_HANDOVER_NO,

  aHNW_HANDOVER_NUM
};

enum haniwa_action {
  aHNW_ACTION_WAIT,
  aHNW_ACTION_DANCE,
  aHNW_ACTION_CHECK_PROCEEDS,
  aHNW_ACTION_TALK_WITH_MASTER,
  aHNW_ACTION_TALK_WITH_MASTER2,
  aHNW_ACTION_TALK_END_WAIT,
  aHNW_ACTION_MENU_OPEN_WAIT,
  aHNW_ACTION_MENU_END_WAIT,
  aHNW_ACTION_TALK_WITH_GUEST,
  aHNW_ACTION_MENU_OPEN_WAIT_FOR_GUEST,
  aHNW_ACTION_MENU_END_WAIT_FOR_GUEST,
  aHNW_ACTION_ROOF_CHECK,
  aHNW_ACTION_SAVE_CHECK,
  aHNW_ACTION_SAVE_END_WAIT,
  aHNW_ACTION_PL_APPROACH_DOOR,
  aHNW_ACTION_DOOR_OPEN_WAIT,
  aHNW_ACTION_DOOR_OPEN_TIMER,

  aHNW_ACTION_NUM
};

struct actor_haniwa_s {
  ACTOR actor_class;

  int saved_current_frame;
  int keyframe_state;
  
  cKF_SkeletonInfo_R_c keyframe;
  int animation_state;

  ClObjPipe_c col_pipe;

  int action;
  char* bank_ram_start;
  s_xyz keyframe_work_area[8];
  s_xyz keyframe_morph_area[8];
  HANIWA_ACTOR_PROC action_proc;
  f32 anim_frame_speed;
  int player_approach_door_stage;
  u16 door_approach_frame;
  u8 submenu_type;
  u8 house_idx;
  u8 playing_save_bgm;
};

extern ACTOR_PROFILE Haniwa_Profile;

#ifdef __cplusplus
}
#endif

#endif

