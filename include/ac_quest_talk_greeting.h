#ifndef AC_QUEST_TALK_GREETING_H
#define AC_QUEST_TALK_GREETING_H

#include "types.h"
#include "ac_quest_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int aQMgr_get_hello_msg_no(ACTOR* client, aQMgr_GET_TIME_KIND_PROC time_proc, mActor_name_t give_item);

#ifdef __cplusplus
}
#endif

#endif
