#ifndef AC_QUEST_TALK_INIT_H
#define AC_QUEST_TALK_INIT_H

#include "types.h"
#include "ac_quest_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aQMgr_NEW_QUEST_SUCCESS 1
#define aQMgr_NEW_QUEST_NO_SPACE -1
#define aQMgr_NEW_QUEST_NO_FOREIGN_ID -2
#define aQMgr_NEW_QUEST_NO_REMOVE_ANIMAL_ID -3
#define aQMgr_NEW_QUEST_ERROR -4

#define aQMgr_FLOWER_GOAL_NUM 4

extern void aQMgr_actor_move_talk_init(QUEST_MANAGER_ACTOR* manager);

#ifdef __cplusplus
}
#endif

#endif
