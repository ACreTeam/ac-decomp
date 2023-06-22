#ifndef M_DEMO_H
#define M_DEMO_H

#include "types.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*mDemo_REQUEST_PROC)(ACTOR*);

extern int mDemo_Request(int type, ACTOR* actor, mDemo_REQUEST_PROC request_proc);
extern void mDemo_Set_msg_num(int msg_num);
extern int mDemo_Check(int type, ACTOR* actor);
extern int mDemo_Check_DiffAngle_forTalk(s16 angle);
extern int mDemo_Check_ListenAble();
extern void mDemo_Set_ListenAble();

#ifdef __cplusplus
}
#endif

#endif
