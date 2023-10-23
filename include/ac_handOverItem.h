#ifndef AC_HANDOVERITEM_H
#define AC_HANDOVERITEM_H

#include "types.h"
#include "m_actor.h"
#include "m_scene.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  aHOI_REQUEST_NO_REQUEST,
  aHOI_REQUEST_TRANSFER,
  aHOI_REQUEST_TRANS_WAIT,
  aHOI_REQUEST_GET,
  aHOI_REQUEST_GET_PULL,
  aHOI_REQUEST_EAT,
  aHOI_REQUEST_CHANGE,
  aHOI_REQUEST_PUTAWAY,
  aHOI_REQUEST_GET_PULL_WAIT,
  aHOI_REQUEST_RETURN,
  aHOI_REQUEST_RETURN_WAIT,
  aHOI_REQUEST_ESTIMATE,

  aHOI_REQUEST_NUM
};

typedef struct hand_over_item_actor_s HANDOVERITEM_ACTOR;

typedef ACTOR* (*aHOI_BIRTH_PROC)(mActor_name_t, int, int);
typedef ACTOR* (*aHOI_CHG_MASTER_PROC)(ACTOR*);
typedef int (*aHOI_CHG_REQUEST_MODE_PROC)(ACTOR*, int);
typedef void (*aHOI_REBUILD_DMA_PROC)(Object_Exchange_c*, ACTOR*); /* yoinked from DnM, unused in AC */

typedef struct hand_over_item_clip_s {
  aHOI_BIRTH_PROC birth_proc;
  aHOI_CHG_MASTER_PROC chg_master_proc;
  aHOI_CHG_REQUEST_MODE_PROC chg_request_mode_proc;
  u8 request_mode;
  u8 player_after_mode;
  mActor_name_t item;
  ACTOR* master_actor;
  ACTOR* target_actor;
  u8 present_flag;
  u8 master_changed_flag;
  HANDOVERITEM_ACTOR* handOverItem_p;
  aHOI_REBUILD_DMA_PROC rebuild_dma_proc;
} aHOI_Clip_c;

struct hand_over_item_actor_s {
  ACTOR actor_class;
  u8 _174[0x1F4 - 0x174]; /* TODO */
};

extern ACTOR_PROFILE HandOverItem_Profile;

#ifdef __cplusplus
}
#endif

#endif

