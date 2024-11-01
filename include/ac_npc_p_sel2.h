#ifndef AC_NPC_P_SEL2_H
#define AC_NPC_P_SEL2_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_p_sel2_s NPC_P_SEL2_ACTOR;

typedef void (*aNPS2_TALK_PROC)(NPC_P_SEL2_ACTOR*, GAME_PLAY*);

struct npc_p_sel2_s {
    NPC_ACTOR npc_class;
    int talk_idx;
    aNPS2_TALK_PROC talk_proc;
    int talk_end_flag;
    int player_sum;
    int player_no;
    int card_file_idx;
    int base_message;
    int base_message2;
    int card_player_num;
    int card_player_idx;
    int card_player_next_choice_idx;
    int passport_slot;
    u8 start_flag;
};

extern ACTOR_PROFILE Npc_P_Sel2_Profile;

#ifdef __cplusplus
}
#endif

#endif
