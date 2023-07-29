#ifndef M_DEMO_H
#define M_DEMO_H

#include "types.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

enum demo_type {
  mDemo_TYPE_NONE,
  mDemo_TYPE_SCROLL,
  mDemo_TYPE_2,
  mDemo_TYPE_DOOR,
  mDemo_TYPE_4,
  mDemo_TYPE_SCROLL2,
  mDemo_TYPE_DOOR2,
  mDemo_TYPE_TALK,
  mDemo_TYPE_SPEAK,
  mDemo_TYPE_REPORT,
  mDemo_TYPE_SPEECH,
  mDemo_TYPE_OUTDOOR,
  mDemo_TYPE_12,
  mDemo_TYPE_EVENTMSG,
  mDemo_TYPE_EVENTMSG2,
  mDemo_TYPE_15,
  mDemo_TYPE_SCROLL3,

  mDemo_TYPE_NUM
};

enum demo_order_type {
  mDemo_ORDER_PLAYER,
  mDemo_ORDER_1,
  mDemo_ORDER_2,
  mDemo_ORDER_3,
  mDemo_ORDER_NPC0,
  mDemo_ORDER_NPC1,
  mDemo_ORDER_NPC2,
  mDemo_ORDER_7,
  mDemo_ORDER_8,
  mDemo_ORDER_QUEST,

  mDemo_ORDER_NUM
};

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
extern void mDemo_Set_talk_turn(u8 value);
extern void mDemo_Set_talk_display_name(u8 value);
extern void mDemo_Set_camera(u8 value);
extern void mDemo_Set_talk_window_color(rgba_t* color);
extern int mDemo_CheckDemo();

#ifdef __cplusplus
}
#endif

#endif
