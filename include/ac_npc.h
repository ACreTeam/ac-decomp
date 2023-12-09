#ifndef AC_NPC_H
#define AC_NPC_H

#include "types.h"
#include "m_actor.h"
#include "m_play.h"
#include "ac_npc_h.h"
#include "m_npc_schedule.h"
#include "m_actor_dlftbls.h"
#include "m_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aNPC_SPNPC_BIT_EV_SONCHO 5

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
  /* 0x0FC */ void* _0FC[(0x124 - 0x0FC) / sizeof(void*)];
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

/* Used for think, schedule, action, & talk */
typedef void (*aNPC_PROC)(NPC_ACTOR* npc_actorx, GAME_PLAY* play, int schedule_idx);
typedef void (*aNPC_SUB_PROC)(NPC_ACTOR* npc_actorx, GAME_PLAY* play);

struct npc_actor_s {
  ACTOR actor_class;
  int _174;
  int _178;
  NpcActorInfo_c npc_info;
  u8 _194[0x718 - 0x194];
  int texture_bank_idx; // TEMP: this is part of draw struct
  u8 _71C[0x751 - 0x71C];
  u8 _751;
  u8 _752[0x8F4 - 0x752];
  int _8F4;
  u8 _8F8[0x974 - 0x8F8];
  s16 talk_base_anim_id;
  s16 _976;
  s16 melody_inst;
  u8 _97A[0x994 - 0x97A]; /* TODO: 0x994 may be too big. Verify size. Seen in ac_normal_npc, ac_npc_engineer */
};

typedef struct animal_npc_actor_s {
  NPC_ACTOR npc_actor_class;
  u8 _994[0x9D8 - 0x994];
} ANIMAL_NPC_ACTOR;

extern ACTOR_PROFILE Npc_Profile;

#ifdef __cplusplus
}
#endif

#endif

