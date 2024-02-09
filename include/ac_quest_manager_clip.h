#ifndef AC_QUEST_MANAGER_CLIP_H
#define AC_QUEST_MANAGER_CLIP_H

#include "types.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*aQMgr_TALK_REQUEST_PROC)(ACTOR*);
typedef int (*aQMgr_TALK_START_PROC)(ACTOR*);
typedef int (*aQMgr_TALK_CHECK_PROC)(ACTOR*);

typedef struct quest_manager_clip_s {
    aQMgr_TALK_REQUEST_PROC talk_request_proc;
    aQMgr_TALK_START_PROC talk_start_proc;
    aQMgr_TALK_CHECK_PROC talk_check_proc;
} aQMgr_Clip_c;

#ifdef __cplusplus
}
#endif

#endif
