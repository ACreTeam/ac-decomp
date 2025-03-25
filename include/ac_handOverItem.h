#ifndef AC_HANDOVERITEM_H
#define AC_HANDOVERITEM_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"
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

enum {
  aHOI_NOT_PRESENT,
  aHOI_PRESENT,

  aHOI_PRESENT_TYPE_NUM
};

// You must include m_common_data.h to use these macros
#define aHOI_CLIP CLIP(handOverItem_clip)
#define aHOI_TRANSFER_DONE() (aHOI_CLIP->master_actor == NULL)
#define aHOI_TRANSFER_IN_PROGRESS() (aHOI_CLIP->master_actor != NULL)

typedef struct hand_over_item_actor_s HANDOVERITEM_ACTOR;

typedef ACTOR* (*aHOI_BIRTH_PROC)(mActor_name_t, int, int, ACTOR*);
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
  TOOLS_ACTOR tools_class;
  int mode;
  f32 anm_cnt;
  xyz_t trans;
  f32 scale;
  u8 trans_flag;
  u8 item_type;
  u8 draw_type;
  u8 se_set_flag;
  int item;
  int gyo_type;
  int gyo_flag;
};

extern ACTOR_PROFILE HandOverItem_Profile;

#ifdef __cplusplus
}
#endif

#endif
