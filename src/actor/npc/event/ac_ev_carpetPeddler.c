#include "ac_ev_carpetPeddler.h"

#include "m_clip.h"
#include "m_common_data.h"
#include "m_msg.h"
#include "m_shop.h"
#include "m_player_lib.h"
#include "m_submenu.h"
#include "m_font.h"
#include "m_string_data.h"

void aECPD_actor_ct(ACTOR* actorx, GAME* game);
void aECPD_actor_dt(ACTOR* actorx, GAME* game);
void aECPD_actor_init(ACTOR* actorx, GAME* game);
void aECPD_actor_move(ACTOR* actorx, GAME* game);
void aECPD_actor_draw(ACTOR* actorx, GAME* game);
void aECPD_actor_save(ACTOR* actorx, GAME* game);

void aECPD_setupAction(EV_CARPETPEDDLER_ACTOR*, GAME_PLAY*, int);

void aECPD_talk_request(ACTOR* actorx, GAME* game);
int aECPD_talk_init(ACTOR* actorx, GAME* game);
int aECPD_talk_end_chk(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Ev_CarpetPeddler_Profile = {
    mAc_PROFILE_EV_CARPETPEDDLER,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_CARPETPEDDLER,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EV_CARPETPEDDLER_ACTOR),
    &aECPD_actor_ct,
    &aECPD_actor_dt,
    &aECPD_actor_init,
    mActor_NONE_PROC1,
    &aECPD_actor_save,
};
// clang-format on

void aECPD_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        &aECPD_actor_move, &aECPD_actor_draw, 3, &aECPD_talk_request, &aECPD_talk_init, &aECPD_talk_end_chk, 0,
    };
    EV_CARPETPEDDLER_ACTOR* peddler = (EV_CARPETPEDDLER_ACTOR*)actorx;
    if (CLIP(npc_clip)->birth_check_proc(actorx, game) == TRUE) {
        CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);
        peddler->setup_action = aECPD_setupAction;
    }
}

void aECPD_actor_save(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->save_proc(actorx, game);
}

void aECPD_actor_dt(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->dt_proc(actorx, game);
    mEv_actor_dying_message(0x4f, actorx);
}

void aECPD_actor_init(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->init_proc(actorx, game);
}

void aECPD_actor_draw(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->draw_proc(actorx, game);
}

#include "../src/actor/npc/event/ac_ev_carpetPeddler.c_inc"
