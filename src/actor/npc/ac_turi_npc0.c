#include "ac_turi_npc0.h"
#include "ac_npc.h"
#include "m_actor.h"
#include "m_common_data.h"
#include "m_name_table.h"

enum {
    aTR0_ACT_WAIT,

    aTR0_ACT_NUM
};

static void aTR0_actor_ct(ACTOR* actorx, GAME* game);
static void aTR0_actor_dt(ACTOR* actorx, GAME* game);
static void aTR0_actor_init(ACTOR* actorx, GAME* game);
static void aTR0_actor_save(ACTOR* actorx, GAME* game);
static void aTR0_actor_move(ACTOR* actorx, GAME* game);
static void aTR0_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Turi_Npc0_Profile = {
    mAc_PROFILE_TURI_NPC0,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(TURI_NPC0_ACTOR),
    aTR0_actor_ct,
    aTR0_actor_dt,
    aTR0_actor_init,
    mActor_NONE_PROC1,
    aTR0_actor_save,
};
// clang-format on

static int regist_cnt = 0;
static ACTOR* turiActorx[aTR0_NPC_MAX];

static void aTR0_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aTR0_think_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aTR0_setupAction(TURI_NPC0_ACTOR* actor, int action);
static void aTR0_talk_request(ACTOR* actorx, GAME* game);
static int aTR0_talk_init(ACTOR* actorx, GAME* game);
static int aTR0_talk_end_chk(ACTOR* actorx, GAME* game);

static void aTR0_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        aTR0_actor_move,
        aTR0_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        aTR0_talk_request,
        aTR0_talk_init,
        aTR0_talk_end_chk,
        0,
    };
    // clang-format on

    if (regist_cnt == 0) {
        int i;

        for (i = 0; i < aTR0_NPC_MAX; i++) {
            turiActorx[i] = NULL;
        }
    }

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        TURI_NPC0_ACTOR* actor = (TURI_NPC0_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aTR0_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);

        {
            int idx = actorx->npc_id - SP_NPC_EV_TURI_0;
            
            turiActorx[idx] = actorx;
            regist_cnt++;
        }
    }
}

static void aTR0_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aTR0_actor_dt(ACTOR* actorx, GAME* game) {
    int idx;

    idx = actorx->npc_id - SP_NPC_EV_TURI_0;
    turiActorx[idx] = NULL;
    
    if (regist_cnt > 0) {
        regist_cnt--;
    }

    NPC_CLIP->dt_proc(actorx, game);
}

static void aTR0_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aTR0_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
}

static void aTR0_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_turi_npc0_anime.c_inc"
#include "../src/actor/npc/ac_turi_npc0_move.c_inc"
