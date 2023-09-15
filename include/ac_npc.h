#ifndef AC_NPC_H
#define AC_NPC_H

#include "types.h"
#include "m_actor.h"
#include "m_play.h"
#include "ac_npc_h.h"
#include "m_npc_schedule.h"
#include "m_actor_dlftbls.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ac_npc_clip_s aNPC_Clip_c;

typedef struct npc_draw_data_s {
  s16 model_bank;
  s16 texture_bank;
  u8 _04[0x68]; // TODO
} aNPC_draw_data_c;

typedef int (*aNPC_SETUP_ACTOR_PROC)(GAME_PLAY*, mActor_name_t, s8, int, s16, int, int, int, int);
typedef void (*aNPC_DMA_DRAW_DATA_PROC)(aNPC_draw_data_c*, mActor_name_t);
typedef void (*aNPC_FREE_OVERLAY_AREA_PROC)(ACTOR_DLFTBL*);
typedef ACTOR* (*aNPC_GET_ACTOR_AREA_PROC)(size_t, const char*, int);
typedef void (*aNPC_FREE_ACTOR_AREA_PROC)(ACTOR*);

typedef int (*aNPC_FORCE_CALL_REQ_PROC)(NPC_ACTOR*, int);

struct ac_npc_clip_s {
  aNPC_SETUP_ACTOR_PROC setupActor_proc;
  void* _004;
  aNPC_FREE_OVERLAY_AREA_PROC free_overlay_area_proc;
  aNPC_GET_ACTOR_AREA_PROC get_actor_area_proc;
  aNPC_FREE_ACTOR_AREA_PROC free_actor_area_proc;
  aNPC_DMA_DRAW_DATA_PROC dma_draw_data_proc;
  void* _018[(0x124 - 0x018) / sizeof(void*)];
  aNPC_FORCE_CALL_REQ_PROC force_call_req_proc;
  void* _128;
};

typedef struct npc_info_s {
  mNPS_schedule_c* schedule;
  mNpc_NpcList_c* list;
  Animal_c* animal;
  void* event; // TODO: EventNpc struct
} NpcActorInfo_c;

struct npc_actor_s {
  ACTOR actor_class;
  NpcActorInfo_c npc_info;
  // TODO: finish
  u8 _174[0x718 - 0x184];
  int texture_bank_idx; // TEMP: this is part of draw struct
  u8 _71C[0x9D8 - 0x71C];
};

extern ACTOR_PROFILE Npc_Profile;

#ifdef __cplusplus
}
#endif

#endif

