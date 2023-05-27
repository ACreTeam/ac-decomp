#ifndef AC_SET_MANAGER_H
#define AC_SET_MANAGER_H

#include "types.h"
#include "m_actor.h"
#include "m_play.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct actor_set_manager_s SET_MANAGER;

#define aSetMgr_SET_OVERLAY_BUF_SIZE 0x4000

#define aSetMgr_INSECT_SPAWN_INFO_COUNT 43

/* sizeof(aSOI_insect_spawn_info_f_c) == 0xC */
typedef struct insect_spawn_info_f_s {
  int type;
  u8 spawn_area;
  float weight;
} aSOI_insect_spawn_info_f_c;

/* sizeof(aSOI_insect_keep_c) == 0x210 */
typedef struct insect_keep_s {
  aSOI_insect_spawn_info_f_c spawn_info[aSetMgr_INSECT_SPAWN_INFO_COUNT]; // devs forgot to update aSetMgr_INSECT_SPAWN_INFO_SIZE or something lol
  int now_month;
  int now_term;
  u8 info_num;
  u8 spawn_type;
} aSOI_insect_keep_c;

#define aSetMgr_WAIT_TIME 5 // wait time between aSetMgr_move_check_wait -> aSetMgr_move_set

#define aSetMgr_GYOEI_NUM 40

/* sizeof(aSOG_gyoei_spawn_info_weight_f_c) == 8 */
typedef struct gyoei_spawn_info_weight_f_s {
  /* 0x00 */ s16 type;
  /* 0x02 */ u8 spawn_area;
  /* 0x04 */ f32 spawn_weight;
} aSOG_gyoei_spawn_info_weight_f_c;

typedef struct gyoei_keep_s {
  /* 0x000 */ aSOG_gyoei_spawn_info_weight_f_c spawn_weights[aSetMgr_GYOEI_NUM];
  /* 0x140 */ int possible_gyoei_num;
} aSOG_gyoei_keep_c;

typedef int (*aSetMgr_ovl_proc)(SET_MANAGER*, GAME_PLAY*);

enum set_overlay_type {
  aSetMgr_OVERLAY_BEGIN = 0,

  aSetMgr_OVERLAY_INSECT = aSetMgr_OVERLAY_BEGIN,
  aSetMgr_OVERLAY_GYOEI,

  aSetMgr_OVERLAY_NUM
};

enum set_manager_move_proc_type {
  aSetMgr_MOVE_move_check_set,
  aSetMgr_MOVE_move_check_wait,
  aSetMgr_MOVE_move_set,

  aSetMgr_MOVE_PROC_NUM
};

/* sizeof(aSetMgr_keep_c) == 0x354 */
typedef struct actor_set_manager_keep_s {
  /* 0x000 */ aSOI_insect_keep_c insect_keep;
  /* 0x210 */ aSOG_gyoei_keep_c gyoei_keep;
} aSetMgr_keep_c;

/* sizeof(aSetMgr_set_ovl_c) == 0x4004 */
typedef struct actor_set_manager_ovl_s {
  /* 0x0000 */ u8 buf[aSetMgr_SET_OVERLAY_BUF_SIZE];
  /* 0x4000 */ aSetMgr_ovl_proc ovl_proc;
} aSetMgr_set_ovl_c;

/* sizeof(aSetMgr_player_pos) == 0x18 */
typedef struct actor_set_manager_player_pos_s {
  /* 0x00 */ int next_bx, next_bz; // TODO: there's a good chance these are structs
  /* 0x08 */ int now_bx, now_bz;
  /* 0x10 */ int last_bx, last_bz;
} aSetMgr_player_pos_c;

/* sizeof(SET_MANAGER) == 0x44F0 */
struct actor_set_manager_s {
  /* 0x0000 */ ACTOR actor_class;
  /* 0x0174 */ u8 move_proc;
  /* 0x0175 */ u8 next_move_proc;
  /* 0x0176 */ u8 set_ovl_type;
  /* 0x0178 */ aSetMgr_set_ovl_c set_overlay;
  /* 0x417C */ int unk_417C;
  /* 0x4180 */ aSetMgr_player_pos_c player_pos;
  /* 0x4198 */ aSetMgr_keep_c keep;
  /* 0x44EC */ s16 wait_timer;
};

extern ACTOR_PROFILE Set_Manager_Profile;

#ifdef __cplusplus
}
#endif

#endif
