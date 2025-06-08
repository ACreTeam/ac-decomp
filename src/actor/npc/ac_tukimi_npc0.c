#include "ac_tukimi_npc0.h"

#include "m_common_data.h"
#include "m_msg.h"

static void aTM0_actor_ct(ACTOR* actorx, GAME* game);
static void aTM0_actor_save(ACTOR* actorx, GAME* game);
static void aTM0_actor_dt(ACTOR* actorx, GAME* game);
static void aTM0_actor_init(ACTOR* actorx, GAME* game);
static void aTM0_actor_move(ACTOR* actorx, GAME* game);
static void aTM0_actor_draw(ACTOR* actorx, GAME* game);

static void aTM0_set_animation(ACTOR* actorx, GAME* game);

static void aTM0_set_request_act(NPC_ACTOR* actorx);
static void aTM0_act_chg_data_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aTM0_act_init_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aTM0_act_proc(NPC_ACTOR* actorx, GAME_PLAY* play, int act_idx);
static void aTM0_think_main_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aTM0_think_init_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aTM0_think_proc(NPC_ACTOR* actorx, GAME_PLAY* play, int think_idx);
static void aTM0_schedule_init_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aTM0_schedule_main_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aTM0_schedule_proc(NPC_ACTOR* actorx, GAME_PLAY* play, int sche_proc_idx);
static void aTM0_set_talk_info(ACTOR* actorx);
static void aTM0_talk_request(ACTOR* actorx, GAME* game);
static int aTM0_talk_init(ACTOR* actorx, GAME* game);
static int aTM0_talk_end_chk(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Tukimi_Npc0_Profile = {
    mAc_PROFILE_TUKIMI_NPC0,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(TUKIMI_NPC0_ACTOR),
    aTM0_actor_ct,
    aTM0_actor_dt,
    aTM0_actor_init,
    mActor_NONE_PROC1,
    aTM0_actor_save,
};
// clang-format on

static void aTM0_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        &aTM0_actor_move,
        &aTM0_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        &aTM0_talk_request,
        &aTM0_talk_init,
        &aTM0_talk_end_chk,
        0,
    };
    // clang-format on

    TUKIMI_NPC0_ACTOR* tukimi_npc0_actor = (TUKIMI_NPC0_ACTOR*)actorx;
    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        tukimi_npc0_actor->npc_class.schedule.schedule_proc = aTM0_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
    }
}

static void aTM0_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aTM0_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aTM0_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aTM0_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
}

static void aTM0_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_tukimi_npc0_anime.c_inc"

#include "../src/actor/npc/ac_tukimi_npc0_talk.c_inc"
