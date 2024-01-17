#ifndef AC_NPC_H
#define AC_NPC_H

#include "types.h"
#include "m_actor.h"
#include "m_play.h"
#include "ac_npc_h.h"
#include "m_npc_schedule.h"
#include "m_actor_dlftbls.h"
#include "m_npc.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aNPC_SPNPC_BIT_CURATOR 0
#define aNPC_SPNPC_BIT_GOHOME_NPC 1
#define aNPC_SPNPC_BIT_MASK_CAT 2
#define aNPC_SPNPC_BIT_DOZAEMON 4
#define aNPC_SPNPC_BIT_EV_SONCHO 5

#define aNPC_SPNPC_BIT_GET(field, bit) (((field) >> (bit)) & 1)
#define aNPC_SPNPC_BIT_SET(field, bit) ((field) |= (1 << (bit)))
#define aNPC_SPNPC_BIT_CLR(field, bit) ((field) &= ~(1 << (bit)))

typedef struct ac_npc_clip_s aNPC_Clip_c;

typedef struct npc_draw_data_s {
  s16 model_bank;
  s16 texture_bank;
  u8 _04[0x68]; // TODO
} aNPC_draw_data_c;

enum {
  aNPC_ATTENTION_TYPE_NONE,
  aNPC_ATTENTION_TYPE_ACTOR,
  aNPC_ATTENTION_TYPE_POSITION,

  aNPC_ATTENTION_TYPE_NUM
};
 
enum {
  aNPC_THINK_WAIT,
  aNPC_THINK_WANDER,
  aNPC_THINK_WANDER2,
  aNPC_THINK_GO_HOME,
  aNPC_THINK_INTO_HOUSE,
  aNPC_THINK_LEAVE_HOUSE,
  aNPC_THINK_IN_BLOCK,
  aNPC_THINK_PITFALL,
  aNPC_THINK_SLEEP,
  aNPC_THINK_SPECIAL,

  aNPC_THINK_NUM
};

enum {
  aNPC_THINK_TYPE_INIT,
  aNPC_THINK_TYPE_CHK_INTERRUPT,
  aNPC_THINK_TYPE_MAIN,

  aNPC_THINK_TYPE_NUM
};

typedef void (*aNPC_TALK_REQUEST_PROC)(ACTOR*, GAME*);
typedef int (*aNPC_TALK_INIT_PROC)(ACTOR*, GAME*);
typedef int (*aNPC_TALK_END_CHECK_PROC)(ACTOR*, GAME*);

typedef struct npc_ct_data_s {
  mActor_proc move_proc;
  mActor_proc draw_proc;
  int _08;
  aNPC_TALK_REQUEST_PROC talk_request_proc;
  aNPC_TALK_INIT_PROC talk_init_proc;
  aNPC_TALK_END_CHECK_PROC talk_end_check_proc;
  int _18;
} aNPC_ct_data_c;

typedef int (*aNPC_SETUP_ACTOR_PROC)(GAME_PLAY*, mActor_name_t, s8, int, s16, int, int, int, int);
typedef void (*aNPC_DMA_DRAW_DATA_PROC)(aNPC_draw_data_c*, mActor_name_t);
typedef void (*aNPC_FREE_OVERLAY_AREA_PROC)(ACTOR_DLFTBL*);
typedef ACTOR* (*aNPC_GET_ACTOR_AREA_PROC)(size_t, const char*, int);
typedef void (*aNPC_FREE_ACTOR_AREA_PROC)(ACTOR*);
typedef void (*aNPC_SET_ATTENTION_REQUEST_PROC)(u8, ACTOR*, xyz_t*);
typedef int (*aNPC_BIRTH_CHECK_PROC)(ACTOR*, GAME*);
typedef void (*aNPC_CT_PROC)(ACTOR*, GAME*, aNPC_ct_data_c*);
typedef void (*aNPC_DT_PROC)(ACTOR*, GAME*);
typedef void (*aNPC_SAVE_PROC)(ACTOR*, GAME*);
typedef void (*aNPC_INIT_PROC)(ACTOR*, GAME*);
typedef void (*aNPC_MOVE_PROC)(ACTOR*, GAME*);
typedef void (*aNPC_MOVE_BEFORE_PROC)(ACTOR*, GAME*);
typedef void (*aNPC_MOVE_AFTER_PROC)(ACTOR*, GAME*);
typedef void (*aNPC_DRAW_PROC)(ACTOR*, GAME*);

typedef void (*aNPC_REBUILD_DMA_PROC)();
typedef void (*aNPC_ANIMATION_INIT_PROC)(ACTOR*, int, int);
typedef void (*aNPC_CHG_SCHEDULE_PROC)(NPC_ACTOR*, GAME_PLAY*, u8);
typedef int (*aNPC_CLIP_THINK_PROC)(NPC_ACTOR*, GAME_PLAY*, int, int);

typedef int (*aNPC_FORCE_CALL_REQ_PROC)(NPC_ACTOR*, int);

struct ac_npc_clip_s {
  /* 0x000 */ aNPC_SETUP_ACTOR_PROC setupActor_proc;
  /* 0x004 */ void* _004;
  /* 0x008 */ aNPC_FREE_OVERLAY_AREA_PROC free_overlay_area_proc;
  /* 0x00C */ aNPC_GET_ACTOR_AREA_PROC get_actor_area_proc;
  /* 0x010 */ aNPC_FREE_ACTOR_AREA_PROC free_actor_area_proc;
  /* 0x014 */ aNPC_DMA_DRAW_DATA_PROC dma_draw_data_proc;
  /* 0x018 */ aNPC_SET_ATTENTION_REQUEST_PROC set_attention_request_proc;
  /* 0x01C */ void* _01C[(0x0CC - 0x01C) / sizeof(void*)];
  /* 0x0CC */ aNPC_BIRTH_CHECK_PROC birth_check_proc;
  /* 0x0D0 */ aNPC_CT_PROC ct_proc;
  /* 0x0D4 */ aNPC_DT_PROC dt_proc;
  /* 0x0D8 */ aNPC_SAVE_PROC save_proc;
  /* 0x0DC */ aNPC_INIT_PROC init_proc;
  /* 0x0E0 */ aNPC_MOVE_PROC move_proc;
  /* 0x0E4 */ aNPC_MOVE_BEFORE_PROC move_before_proc;
  /* 0x0E8 */ aNPC_MOVE_AFTER_PROC move_after_proc;
  /* 0x0EC */ void* _0EC;
  /* 0x0F0 */ void* _0F0;
  /* 0x0F4 */ aNPC_DRAW_PROC draw_proc;
  /* 0x0F8 */ aNPC_REBUILD_DMA_PROC rebuild_dma_proc;
  /* 0x0FC */ void* _0FC[(0x114 - 0x0FC) / sizeof(void*)];
  /* 0x114 */ aNPC_ANIMATION_INIT_PROC animation_init_proc;
  /* 0x118 */ aNPC_CHG_SCHEDULE_PROC chg_schedule_proc;
  /* 0x11C */ void* _11C;
  /* 0x120 */ aNPC_CLIP_THINK_PROC think_proc;
  /* 0x124 */ aNPC_FORCE_CALL_REQ_PROC force_call_req_proc;
  /* 0x128 */ void* _128;
};

typedef struct npc_info_s {
  Animal_c* animal;
  mNpc_NpcList_c* list;
  mNPS_schedule_c* schedule;
  mNpc_EventNpc_c* event;
  mNpc_MaskNpc_c* mask;
  mActor_name_t npc_name;
} NpcActorInfo_c;

typedef struct npc_animation_s {
  cKF_SkeletonInfo_R_c keyframe;
  s_xyz work[27];
  s_xyz morph[27];
  int _1B4;
  s8 animation_id; 
} aNPC_ANIMATION_c;

/* TODO: draw data */
typedef struct npc_draw_info_s {
  /* 0x000 */ int main_animation_frame;
  /* 0x004 */ int _04; // TODO: figure out where this is set
  /* 0x008 */ int main_animation_frame_changed;
  /* 0x00C */ int _08; // TODO: figure out where this is set
  /* 0x010 */ int _0C; // TODO: figure out where this is set
  /* 0x014 */ aNPC_ANIMATION_c main_animation;
  /* 0x1D0 */ aNPC_ANIMATION_c sub_animation0;
  /* 0x38C */ aNPC_ANIMATION_c sub_animation1;
  /* 0x548 */ u8 _548[0x580 - 0x548];
  /* 0x580 */ int animation_id;
  /* 0x584 */ int texture_bank_idx;
  /* 0x588 */ u8 _588[0x5B9 - 0x588]; 
  /* 0x5B9 */ u8 _5B9;
  /* 0x5BA */ u8 _5BA;
  /* 0x5BB */ u8 _5BB;
  /* 0x5BC */ u8 _5BC;
  /* 0x5BD */ u8 _5BD;
  /* 0x5BE */ u8 _5BE;
  /* 0x5BE */ u8 _5BF[0x5D0 - 0x5BF];
  /* 0x5D0 */ f32 animation_speed;
  /* 0x5D4 */ u8 _5D4[0x630 - 0x5D4];
} aNPC_draw_info_c;

typedef void (*aNPC_THINK_PROC)(NPC_ACTOR*, GAME_PLAY*, int);

#define aNPC_THINK_INTERRUPT_FRIENDSHIP (1 << 0)
#define aNPC_THINK_INTERRUPT_FATIGUE    (1 << 1)
#define aNPC_THINK_INTERRUPT_OBSTANCE   (1 << 2)
#define aNPC_THINK_INTERRUPT_ENTRANCE   (1 << 3)

typedef struct npc_think_info_s {
  int idx;
  u8 end_flag;
  u8 force_call_flag;
  u16 force_call_timer;
  int force_call_msg_no;
  u8 force_call_camera_type;
  aNPC_THINK_PROC think_proc;
  u32 interrupt_flags;
} aNPC_think_info_c;

typedef void (*aNPC_SCHEDULE_PROC)(NPC_ACTOR*, GAME_PLAY*, int);

typedef struct npc_schedule_info_s {
  u8 type;
  u8 state;
  mNPS_schedule_c schedule;
  aNPC_SCHEDULE_PROC schedule_proc;
} aNPC_schedule_info_c;

enum {
  aNPC_ACT_OBJ_NONE,
  aNPC_ACT_OBJ_PLAYER,
  aNPC_ACT_OBJ_ANY_NPC,
  aNPC_ACT_OBJ_TARGET_NPC,
  aNPC_ACT_OBJ_4,
  aNPC_ACT_OBJ_5,
  aNPC_ACT_OBJ_INSECT,
  aNPC_ACT_OBJ_FISH,

  aNPC_ACT_OBJ_NUM
};

typedef void (*aNPC_ACTION_PROC)(NPC_ACTOR*, GAME_PLAY*, int);

#define aNPC_ACTION_END_STEP 0xFF

typedef struct npc_action_s {
  u8 priority;
  u8 idx;
  u8 step;
  u8 type;
  u8 prev_priority;
  u8 prev_step;
  s16 act_timer;
  u8 feel;
  u8 act_obj;
  u16 act_obj_id;
  s16 move_x;
  s16 move_z;
  aNPC_ACTION_PROC act_proc;
} aNPC_action_c;

typedef struct npc_request_s {
  u8 act_priority;
  u8 act_idx;
  u8 act_type;
  u16 act_args[6];
  u8 umb_flag;
  u8 _11;
  u8 head_priority;
  u8 head_type;
  ACTOR* head_target;
  xyz_t head_pos;
} aNPC_request_c;

#define aNPC_COND_DEMO_SKIP_MOVE_RANGE_CHECK  (1 <<  0) /* 0x0001 */
#define aNPC_COND_DEMO_SKIP_MOVE_CIRCLE_REV   (1 <<  1) /* 0x0002 */
#define aNPC_COND_DEMO_SKIP_MOVE_Y            (1 <<  2) /* 0x0004 */
#define aNPC_COND_DEMO_SKIP_OBJ_COL_CHECK     (1 <<  3) /* 0x0008 */
#define aNPC_COND_DEMO_SKIP_BGCHECK           (1 <<  4) /* 0x0010 */
#define aNPC_COND_DEMO_SKIP_FORWARD_CHECK     (1 <<  5) /* 0x0020 */
#define aNPC_COND_DEMO_SKIP_ITEM              (1 <<  6) /* 0x0040 */
#define aNPC_COND_DEMO_SKIP_TALK_CHECK        (1 <<  7) /* 0x0080 */
#define aNPC_COND_DEMO_SKIP_HEAD_LOOKAT       (1 <<  8) /* 0x0100 */
#define aNPC_COND_DEMO_SKIP_ENTRANCE_CHECK    (1 <<  9) /* 0x0200 */
#define aNPC_COND_DEMO_SKIP_KUTIPAKU          (1 << 10) /* 0x0400 */
#define aNPC_COND_DEMO_SKIP_FOOTSTEPS         (1 << 11) /* 0x0800 */
#define aNPC_COND_DEMO_SKIP_FEEL_CHECK        (1 << 12) /* 0x1000 */
#define aNPC_COND_DEMO_SKIP_LOVE_CHECK        (1 << 13) /* 0x2000 */
#define aNPC_COND_DEMO_SKIP_FOOTSTEPS_VFX     (1 << 14) /* 0x4000 */
#define aNPC_COND_DEMO_SKIP_UZAI_CHECK        (1 << 15) /* 0x8000 */

typedef struct npc_condition_s {
  u8 hide_flg;
  u8 hide_request;
  u8 action;
  u8 talk_condition;
  u8 greeting_flag;
  u8 entrance_flag;
  u16 fatigue;
  int feel_tim;
  int _0C;
  u32 demo_flg;
  u32 talk_demo_flg_save;
  u32 trans_demo_flg_save;
  u8 appear_flag;
  u8 appear_rotation;
  u8 pitfall_flag;
  u32 actor_state_save;
  int _24;
  int _28;
  int _2C;
  s8* friendship;
  int over_friendship;
  mActor_name_t* under_fg_p;
  int ut_x;
  int ut_z;
} aNPC_condition_info_c;

typedef struct npc_uzai_s {
  int step;
  u8 tool;
  u8 flag;
  u8 cross;
} aNPC_uzai_c;

typedef struct npc_hand_s {
  u8 item_type;
  u8 requested_item_type;
  mActor_name_t item;
  u8 after_mode;
  u8 present_flag;
  u8 umbrella_disabled_flag;
  u8 umbrella_type;
  ACTOR* item_actor_p;
  ACTOR* prev_item_actor_p;
  xyz_t pos;
} aNPC_hand_c;

typedef struct npc_head_s {
  s16 angle_x;
  s16 angle_y;
  s16 angle_add_x;
  s16 angle_add_y;
  s16 _08;
  u8 lock_flag;
  u8 target_type;
  ACTOR* target;
  xyz_t pos;
} aNPC_head_c;

enum {
  aNPC_FOOT_LEFT,
  aNPC_FOOT_RIGHT,

  aNPC_FOOT_NUM
};

typedef struct npc_movement_s {
  f32 max_speed;
  f32 acceleration;
  f32 deceleration;
  f32 target_pos_x;
  f32 target_pos_z;
  f32 avoid_pos_x;
  f32 avoid_pos_z;
  s16 move_timer;
  u8 avoid_direction;
  u8 range_type;
  f32 range_center_x;
  f32 range_center_z;
  f32 range_radius;
  s16 mv_angl;
  s16 mv_add_angl;
  f32 arrival_area_radius;
  ACTOR* target;
  s8 movement_ut_x;
  s8 movement_ut_z;
  s16 body_angle;
  u8 override_body_angle_flag;
  u8 demo_move_timer;
} aNPC_movement_c;

typedef struct npc_collision_s {
  ClObjPipe_c pipe;
  f32 BGcheck_radius;
  u8 collision_flag;
  u8 priority;
  u8 turn_flag;
  u16 _24;
  s16 turn_angle;
  f32 bg_rev_add;
} aNPC_collision_c;

typedef struct npc_actor_talk_info_s {
  aNPC_TALK_REQUEST_PROC talk_request_proc;
  aNPC_TALK_INIT_PROC talk_init_proc;
  aNPC_TALK_END_CHECK_PROC talk_end_check_proc;
  u8 type;
  u8 default_act;
  u8 demo_code;
  u8 turn;
  s16 default_animation;
  s16 default_turn_animation;
  s16 melody_inst;
  s16 npc_voice_id;
  u8 feel;
  u8 memory;
  u8 kutipaku_timer; // frames of mouth movement animation
} aNPC_talk_info_c;

typedef struct npc_accessory_s {
  s16 type;
  s16 pos_joint_idx; // might be better suited as base_joint_idx?
  ACTOR* accessory;
} aNPC_accessory_c;

/* Used for think, schedule, action, & talk */
typedef void (*aNPC_PROC)(NPC_ACTOR* npc_actorx, GAME_PLAY* play, int schedule_idx);
typedef void (*aNPC_SUB_PROC)(NPC_ACTOR* npc_actorx, GAME_PLAY* play);

enum {
  aNPC_SCHEDULE_TYPE_FIELD,
  aNPC_SCHEDULE_TYPE_IN_HOUSE,
  aNPC_SCHEDULE_TYPE_SLEEP,
  aNPC_SCHEDULE_TYPE_STAND,
  aNPC_SCHEDULE_TYPE_WANDER,
  aNPC_SCHEDULE_TYPE_WALK_WANDER,
  aNPC_SCHEDULE_TYPE_SPECIAL,

  aNPC_SCHEDULE_TYPE_NUM
};

struct npc_actor_s {
  ACTOR actor_class;
  s_xyz _174;
  NpcActorInfo_c npc_info;
  aNPC_draw_info_c draw;
  aNPC_think_info_c think;
  aNPC_schedule_info_c schedule;
  aNPC_action_c action;
  aNPC_request_c request;
  f32 eye_y;
  aNPC_condition_info_c condition_info;
  aNPC_uzai_c uzai;
  aNPC_hand_c left_hand;
  aNPC_hand_c right_hand;
  aNPC_head_c head;
  xyz_t feet[aNPC_FOOT_NUM];
  mActor_proc move_proc;
  mActor_proc draw_proc;
  ACTOR* palActor;
  int palActorIgnoreTimer;
  aNPC_movement_c movement;
  aNPC_collision_c collision;
  aNPC_talk_info_c talk_info;
  aNPC_accessory_c accessory;
  int act_react_tool_timer;
  int _98C;
  int _990;
};

typedef struct npc_control_cloth_s {
  u8 dma_flag;
  u8 init_flag;
  s16 _02;
  mActor_name_t cloth_item;
  u8 in_use_count;
  Object_Bank_c texture_bank;
  Object_Bank_c palette_bank;
} aNPC_cloth_c;

typedef struct npc_control_actor_s {
  ACTOR* actor_class;
  aNPC_cloth_c cloth[10];
  u8 _8F4[0x9D8 - 0x8F4]; // TODO
} NPC_CONTROL_ACTOR;

typedef struct npc_destruct_table_proc{
    aNPC_SUB_PROC unk0;
    aNPC_SUB_PROC unk4;
}NPC_DT_PROCS;

extern ACTOR_PROFILE Npc_Profile;

#ifdef __cplusplus
}
#endif

#endif

