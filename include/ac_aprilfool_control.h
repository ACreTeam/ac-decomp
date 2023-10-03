#ifndef AC_APRILFOOL_CONTROL_H
#define AC_APRILFOOL_CONTROL_H

#include "types.h"
#include "m_actor.h"
#include "ac_aprilfool_control_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aAPC_GET_NPC_BIT(bitfield, data_idx) ((1 << (data_idx)) & (bitfield))
#define aAPC_SET_NPC_BIT(bitfield, data_idx) ((bitfield) | (1 << (data_idx)))

typedef int (*aAPC_TALK_CHK_PROC)(mActor_name_t);
typedef void (*aAPC_TALK_SET_PROC)(mActor_name_t);
typedef int (*aAPC_GET_MSG_NUM_PROC)(mActor_name_t, int);

typedef struct aprilfool_control_clip_s {
  aAPC_TALK_CHK_PROC talk_chk_proc;
  aAPC_TALK_SET_PROC talk_set_proc;
  aAPC_GET_MSG_NUM_PROC get_msg_num_proc;
  aAPC_event_save_data_c* event_save_data_p;
} aAPC_Clip_c;

extern ACTOR_PROFILE Aprilfool_Control_Profile;

typedef struct aprilfool_control_s {
  ACTOR actor_class;
  aAPC_Clip_c clip;
} APRILFOOL_CONTROL_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

