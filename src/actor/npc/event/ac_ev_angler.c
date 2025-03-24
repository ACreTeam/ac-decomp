#include "ac_ev_angler.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_string.h"
#include "m_msg.h"
#include "m_font.h"
#include "libultra/libultra.h"

enum {
    aEANG_TYPE_BASS,
    aEANG_TYPE_FISH,
    aEANG_TYPE_OTHER,
    aEANG_TYPE_TOOL,

    aEANG_TYPE_NUM
};

enum {
    aEANG_TALK_END_WAIT,
    aEANG_TALK_MENU_OPEN_WAIT,
    aEANG_TALK_MENU_CLOSE_WAIT,
    aEANG_TALK_MSG_WIN_OPEN_WAIT,
    aEANG_TALK_SAY_TURETA,
    aEANG_TALK_DEMO_GIVE_ME,
    aEANG_TALK_DEMO_HENKYAKU,
    aEANG_TALK_DEMO_HOUBI,
    aEANG_TALK_MSG_TO_MENU,
    aEANG_TALK_DEMO_MEASURE,

    aEANG_TALK_NUM
};

static void aEANG_actor_ct(ACTOR* actorx, GAME* game);
static void aEANG_actor_dt(ACTOR* actorx, GAME* game);
static void aEANG_actor_move(ACTOR* actorx, GAME* game);
static void aEANG_actor_draw(ACTOR* actorx, GAME* game);
static void aEANG_actor_init(ACTOR* actorx, GAME* game);
static void aEANG_actor_save(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Ev_Angler_Profile = {
    // clang-format off
    mAc_PROFILE_EV_ANGLER,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_ANGLER,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EV_ANGLER_ACTOR),
    aEANG_actor_ct,
    aEANG_actor_dt,
    aEANG_actor_init,
    mActor_NONE_PROC1,
    aEANG_actor_save,
    // clang-format on
};

static void aEANG_talk_request(ACTOR* actorx, GAME* game);
static int aEANG_talk_init(ACTOR* actorx, GAME* game);
static int aEANG_talk_end_chk(ACTOR* actorx, GAME* game);

static void aEANG_setupAction(EV_ANGLER_ACTOR* angler, GAME_PLAY* play, int talk_act);

static void fish_save_area_ct(ACTOR* actorx);
static void fish_save_area_dt(ACTOR* actorx);

static void aEANG_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        // clang-format off
        aEANG_actor_move,
        aEANG_actor_draw,
        aNPC_CT_SCHED_TYPE_STAND,
        aEANG_talk_request,
        aEANG_talk_init,
        aEANG_talk_end_chk,
        1,
        // clang-format on
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        EV_ANGLER_ACTOR* angler = (EV_ANGLER_ACTOR*)actorx;

        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        angler->setup_talk_proc = aEANG_setupAction;
        fish_save_area_ct(actorx);
        NPC_CLIP->set_dst_pos_proc((NPC_ACTOR*)actorx, actorx->world.position.x, actorx->world.position.z + 10.0f);
        actorx->status_data.weight = MASSTYPE_HEAVY;
    }
}
        
static void aEANG_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aEANG_actor_dt(ACTOR* actorx, GAME* game) {    
    NPC_CLIP->dt_proc(actorx, game);
    fish_save_area_dt(actorx);
}

static void aEANG_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aEANG_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/event/ac_ev_angler_move.c_inc"
