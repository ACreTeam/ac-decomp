#ifndef AC_NPC_RTC_H
#define AC_NPC_RTC_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct actor_npc_rtc_s NPCRTC_ACTOR;

typedef void (*aNPCRTC_SUB_PROC)(NPCRTC_ACTOR* rtc, GAME_PLAY* play);

struct actor_npc_rtc_s{
    NPC_ACTOR npc_class;
    int unk994;
    int unk998; 
    aNPCRTC_SUB_PROC unk99C;
    int unk9A0;
    int unk9A4;
    int unk9A8;
    int unk9AC;
    int unk9B0; 
    int unk9B4;
    int unk9B8;
};

extern ACTOR_PROFILE Npc_Rtc_Profile;

#ifdef __cplusplus
}
#endif

#endif

