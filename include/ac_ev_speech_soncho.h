#ifndef AC_EV_SPEECH_SONCHO_H
#define AC_EV_SPEECH_SONCHO_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Ev_Speech_Soncho_Profile;

typedef struct ac_npc_speech_soncho NPC_SPEECH_SONCHO;

typedef void (*aESS_PROC)(NPC_SPEECH_SONCHO* soncho, GAME_PLAY* play);
typedef void (*aESS_THINK_PROC)(NPC_SPEECH_SONCHO* soncho, GAME_PLAY* play);
typedef void (*aESS_SCHEDULE_PROC)(NPC_SPEECH_SONCHO* soncho, GAME_PLAY* play);

struct ac_npc_speech_soncho {
    NPC_ACTOR npc_class;
    /* 0x994 */ int think_proc_idk;
    /* 0x998 */ aESS_PROC think_proc;
};

struct aess_think_info {
    aESS_PROC think_proc;
    aNPC_TALK_REQUEST_PROC talk_request_proc;
    aNPC_TALK_END_CHECK_PROC talk_end_check_proc;
    u8 flag;
};

typedef struct aess_think_info aESS_think_info;

#ifdef __cplusplus
}
#endif

#endif
