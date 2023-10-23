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

typedef int (*aNPC_SETUP_ACTOR_PROC)(GAME_PLAY*, mActor_name_t, s8, int, s16, int, int, int, int);
typedef void (*aNPC_DMA_DRAW_DATA_PROC)(aNPC_draw_data_c*, mActor_name_t);
typedef void (*aNPC_FREE_OVERLAY_AREA_PROC)(ACTOR_DLFTBL*);
typedef ACTOR* (*aNPC_GET_ACTOR_AREA_PROC)(size_t, const char*, int);
typedef void (*aNPC_FREE_ACTOR_AREA_PROC)(ACTOR*);
typedef void (*aNPC_SET_ATTENTION_REQUEST_PROC)(u8, ACTOR*, xyz_t*);

typedef void (*aNPC_REBUILD_DMA_PROC)();

typedef int (*aNPC_FORCE_CALL_REQ_PROC)(NPC_ACTOR*, int);

struct ac_npc_clip_s {
  aNPC_SETUP_ACTOR_PROC setupActor_proc;
  void* _004;
  aNPC_FREE_OVERLAY_AREA_PROC free_overlay_area_proc;
  aNPC_GET_ACTOR_AREA_PROC get_actor_area_proc;
  aNPC_FREE_ACTOR_AREA_PROC free_actor_area_proc;
  aNPC_DMA_DRAW_DATA_PROC dma_draw_data_proc;
  aNPC_SET_ATTENTION_REQUEST_PROC set_attention_request_proc;
  void* _01C[(0x0F8 - 0x01C) / sizeof(void*)];
  aNPC_REBUILD_DMA_PROC rebuild_dma_proc;
  void* _0FC[(0x124 - 0x0FC) / sizeof(void*)];
  aNPC_FORCE_CALL_REQ_PROC force_call_req_proc;
  void* _128;
};

typedef struct npc_info_s {
  Animal_c* animal;
  mNpc_NpcList_c* list;
  mNPS_schedule_c* schedule;
  mNpc_EventNpc_c* event;
  mNpc_MaskNpc_c* mask;
  mActor_name_t npc_name;
} NpcActorInfo_c;

struct npc_actor_s {
  ACTOR actor_class;
  int _174;
  int _178;
  NpcActorInfo_c npc_info;
  u8 _194[0x718 - 0x194];
  int texture_bank_idx; // TEMP: this is part of draw struct
  u8 _71C[0x974 - 0x71C];
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

