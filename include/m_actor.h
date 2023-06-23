#ifndef M_ACTOR_H
#define M_ACTOR_H

#include "types.h"
#include "m_actor_type.h"
#include "game.h"
#include "m_lib.h"
#include "m_lights.h"
#include "m_collision_bg.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*mActor_proc)(ACTOR*, GAME*);

#define ACTOR_STATE_NO_MOVE_WHILE_CULLED (1 << 4)
#define ACTOR_STATE_NO_DRAW_WHILE_CULLED (1 << 5)
#define ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES (1 << 29)

#define ACTOR_OBJ_BANK_NONE 0
#define ACTOR_OBJ_BANK_3 3 /* TODO: rename, also likely an enum */
#define ACTOR_OBJ_BANK_7 7
#define ACTOR_OBJ_BANK_12 12

enum actor_part {
  ACTOR_PART_FG,
  ACTOR_PART_ITEM,
  ACTOR_PART_PLAYER,
  ACTOR_PART_NPC,
  ACTOR_PART_4, /* TODO: figure this one out */
  ACTOR_PART_BG,
  ACTOR_PART_EFFECT,
  ACTOR_PART_CONTROL,

  ACTOR_PART_NUM
};

/* sizeof(ACTOR_PROFILE) == 0x24 */
typedef struct actor_profile_s {
  /* 0x00 */ s16 id; /* unique actor type ID */
  /* 0x02 */ u8 part; /* actor type, seemingly called 'part' */
  /* 0x04 */ u32 initial_flags_state; /* initial actor flag state */
  /* 0x08 */ mActor_name_t npc_id; /* "world" npc id/name */
  /* 0x0A */ s16 obj_bank_id; /* used with object exchange */
  /* 0x0C */ size_t class_size; /* sizeof(ZZZ_ACTOR) */
  /* 0x10 */ mActor_proc ct_proc; /* constructor */
  /* 0x14 */ mActor_proc dt_proc; /* destructor */
  /* 0x18 */ mActor_proc mv_proc; /* move */
  /* 0x1C */ mActor_proc dw_proc; /* draw */
  /* 0x20 */ mActor_proc sv_proc; /* save */
} ACTOR_PROFILE;

typedef void (*mActor_shadow_proc)(ACTOR*, LightsN*, GAME_PLAY*);

/* sizeof(Shape_Info) == 0x48 */
typedef struct actor_shape_info_s {
  /* 0x00 */ s_xyz rotation;
  /* 0x06 */ s16 unk_6;
  /* 0x08 */ f32 ofs_y;
  /* 0x0C */ mActor_shadow_proc shadow_proc;
  /* 0x10 */ f32 shadow_size_x;
  /* 0x14 */ f32 shadow_size_z;
  /* 0x18 */ f32 shadow_size_change_rate;
  /* 0x1C */ f32 shadow_alpha_change_rate;
  /* 0x20 */ int unk_20;
  /* 0x24 */ xyz_t* shadow_position;
  /* 0x28 */ int unk_28;
  /* 0x2C */ u8 draw_shadow; /* TRUE = shadow is drawn, FALSE = shadow is not drawn */
  /* 0x2D */ u8 unk_2D;
  /* 0x2E */ u8 force_shadow_position; /* TRUE = shadow's position is forcefully updated, FALSE = non-forcefully updated */
  /* 0x2F */ u8 unused_2F[0x48-0x2F];
} Shape_Info;

/* sizeof(struct actor_s) == 0x174 */
struct actor_s {
  /* 0x000 */ s16 id; /* unique actor type ID */
  /* 0x002 */ u8 part;
  /* 0x003 */ u8 restore_fg; /* restores 'fgdata' according to restore_fgdata_all */
  /* 0x004 */ s16 scene_id;
  /* 0x006 */ mActor_name_t npc_id;
  /* 0x008 */ s8 block_x;
  /* 0x009 */ s8 block_z;
  /* 0x00A */ s16 move_actor_list_idx; /* used in aBC_setupCommonMvActor */
  /* 0x00C */ xyz_t home_position; /* actor 'home' pos */
  /* 0x018 */ s_xyz home_rotation; /* actor 'home' rotation */
  /* 0x020 */ u32 state_bitfield; /* bitfield of current actor state */
  /* 0x024 */ s16 actor_specific; /* actor specific temp data */
  /* 0x026 */ s16 data_bank_id; /* data bank id actor is in */
  /* 0x028 */ xyz_t world_position;
  /* 0x034 */ s_xyz world_rotation;
  /* 0x03C */ xyz_t last_world_position; /* previous actor world position */
  /* 0x048 */ xyz_t eye_position; /* actor "eyes" (head/lookat) world position */
  /* 0x054 */ s_xyz eye_rotation; /* actor "eyes" (head/lookat) world rotation */
  /* 0x05C */ xyz_t scale; /* actor size */
  /* 0x068 */ xyz_t position_speed; /* actor movement velocity (see Actor_position_speed_set) */
  /* 0x074 */ f32 speed; /* movement speed */
  /* 0x078 */ f32 gravity; /* gravity acting on actor */
  /* 0x07C */ f32 max_velocity_y; /* maximum y velocity possible due to gravity, usually -20.0f */
  /* 0x080 */ f32 ground_y; /* vertical position of ground underneath actor */
  /* 0x084 */ mCoBG_Check_c bg_collision_check; /* background object collision info with actor */
  /* 0x0B4 */ u8 unknown_b4; /* some sort of flag */
  /* 0x0B5 */ u8 drawn; /* was drawn flag, TRUE = actor was drawn, FALSE = actor was not drawn */
  /* 0x0B6 */ s16 player_angle_y; /* Y angle (yaw) between actor and player actor */
  /* 0x0B8 */ f32 player_distance; /* distance between actor and player actor (squared magnitude) */
  /* 0x0BC */ f32 player_distance_xz; /* distance between actor and player actor on XZ plane (magnitude) */
  /* 0x0C0 */ f32 player_distance_y; /* distance between actor and player actor on Y plane */
  /* 0x0C4 */ u8 status_data[0xDC-0xC4]; /* TODO: implement, see m_collision_obj */
  /* 0x0DC */ Shape_Info shape_info;
  /* 0x124 */ xyz_t camera_position; /* camera position relative to actor position */
  /* 0x130 */ f32 camera_w; /* camera projection W value */
  /* 0x134 */ f32 cull_width;
  /* 0x138 */ f32 cull_height;
  /* 0x13C */ f32 cull_distance;
  /* 0x140 */ f32 cull_radius;
  /* 0x144 */ f32 talk_distance; /* maximum distance for talking to be triggered, default seems to be 55.0f */
  /* 0x148 */ u8 cull_while_talking; /* flag to disable actor drawing while talking */
  /* 0x149 */ u8 skip_drawing; /* manual "do not draw" override flag only used by player umbrella actor */
  /* 0x14C */ ACTOR* parent_actor;
  /* 0x150 */ ACTOR* child_actor;
  /* 0x154 */ ACTOR* prev_actor;
  /* 0x158 */ ACTOR* next_actor;
  /* 0x15C */ mActor_proc ct_proc; /* constructor */
  /* 0x160 */ mActor_proc dt_proc; /* destructor */
  /* 0x164 */ mActor_proc mv_proc; /* move */
  /* 0x168 */ mActor_proc dw_proc; /* draw */
  /* 0x16C */ mActor_proc sv_proc; /* save */
  /* 0x170 */ void* dlftbl; /* display list function table */
};

#define mActor_NONE_PROC1 ((mActor_proc)none_proc1)

typedef struct actor_list_s {
  int num_actors;
  ACTOR* actor;
} Actor_list;

typedef struct actor_info_s {
  int total_num;
  Actor_list list[ACTOR_PART_NUM];
} Actor_info;

extern void Actor_delete(ACTOR* actor);
extern ACTOR* Actor_info_fgName_search(Actor_info* actor_info, mActor_name_t fg_name, int part);
extern void Actor_world_to_eye(ACTOR* actor, f32 eye_height);
extern void Shape_Info_init(ACTOR* actor, f32 y_ofs, mActor_shadow_proc shadow_proc, f32 shadow_sizeX, f32 shadow_sizeZ);
extern void Actor_position_moveF(ACTOR* actor);

extern void mAc_ActorShadowCircle(ACTOR* actor, LightsN* lightsN, GAME_PLAY* play);
extern void mAc_ActorShadowEllipse(ACTOR* actor, LightsN* lightsN, GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
