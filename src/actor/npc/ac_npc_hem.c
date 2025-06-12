#include "ac_npc_hem.h"
#include "m_name_table.h"
#include "ac_npc.h"
#include "ac_npc_h.h"
#include "m_common_data.h"
#include "m_msg.h"
#include "m_soncho.h"
#include "ac_shrine.h"

struct _NPC_HEM_ACTOR;

typedef (*NPC_HEM_PROC)(struct _NPC_HEM_ACTOR*);

typedef struct _NPC_HEM_ACTOR {
    NPC_ACTOR actor;
    int processIndex;
    aNPC_SUB_PROC processFunction;
    aNPC_SUB_PROC talkProcess;
    u8 _9A0;
    u8 _9A1;
    s16 _9A2;
} NPC_HEM_ACTOR;

void aNHM_actor_ct(ACTOR* actorx, GAME* game);
void aNHM_actor_dt(ACTOR* actorx, GAME* game);
void aNHM_actor_init(ACTOR* actorx, GAME* game);
void aNHM_actor_save(ACTOR* actorx, GAME* game);
void aNHM_actor_move(ACTOR* actorx, GAME* game);
void aNHM_actor_draw(ACTOR* actorx, GAME* game);
BOOL aNHM_talk_init(ACTOR* actorx, GAME* game);
BOOL aNHM_talk_end_chk(ACTOR* actorx, GAME* game);
void aNHM_schedule_proc(NPC_ACTOR*, GAME_PLAY*, int);
void aNHM_talk_request(ACTOR* actorx, GAME* game);
void aNHM_change_talk_proc(NPC_ACTOR* actorx, int);

// clang-format off
ACTOR_PROFILE Npc_Hem_Profile = {
    mAc_PROFILE_NPC_HEM,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_HEM,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_HEM_ACTOR),
    aNHM_actor_ct,
    aNHM_actor_dt,
    aNHM_actor_init,
    (mActor_proc)none_proc1,
    aNHM_actor_save
};
// clang-format on

void aNHM_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        aNHM_actor_move,
        aNHM_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aNHM_talk_init,
        aNHM_talk_end_chk,
        0
    };
    // clang-format on

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        ((NPC_HEM_ACTOR*)actorx)->actor.schedule.schedule_proc = aNHM_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
    }
}

void aNHM_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

void aNHM_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

void aNHM_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

void aNHM_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../../actor/npc/ac_npc_hem.c_inc"
