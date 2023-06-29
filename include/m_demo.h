#ifndef M_DEMO_H
#define M_DEMO_H

#include "types.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*mDemo_REQUEST_PROC)(ACTOR*);

typedef struct demo_clip_s {
  void* class;
  int type; /* 0 = none?, 1 = intro_demo, 2 = ride_off_demo */
} mDemo_Clip_c;

enum demo_clip_type {
  mDemo_CLIP_TYPE_NONE,
  mDemo_CLIP_TYPE_INTRO_DEMO,
  mDemo_CLIP_TYPE_RIDE_OFF_DEMO,

  mDemo_CLIP_TYPE_NUM
};

extern int mDemo_Request(int type, ACTOR* actor, mDemo_REQUEST_PROC request_proc);
extern void mDemo_Set_msg_num(int msg_num);
extern int mDemo_Check(int type, ACTOR* actor);
extern int mDemo_Check_DiffAngle_forTalk(s16 angle);
extern int mDemo_Check_ListenAble();
extern void mDemo_Set_ListenAble();
extern ACTOR* mDemo_Get_talk_actor();
extern void mDemo_Set_OrderValue(int type, int idx, u16 value);
extern u16 mDemo_Get_OrderValue(int type, int idx);
extern void mDemo_Set_talk_return_demo_wait(u8 value);

#ifdef __cplusplus
}
#endif

#endif
