#include "ac_ev_speech_soncho.h"
#include "m_actor.h"
#include "m_clip.h"
#include "ac_npc.h"
#include "m_common_data.h"
#include "ac_groundhog_control.h"
#include "m_demo.h"
#include "m_string_data.h"

void aESS_actor_ct(ACTOR* actorx, GAME* game);
void aESS_actor_dt(ACTOR* actorx, GAME* game);
void aESS_actor_init(ACTOR* actorx, GAME* game);
void aESS_actor_save(ACTOR* actorx, GAME* game);
void aESS_schedule_proc(NPC_SPEECH_SONCHO* soncho, GAME_PLAY* play, int sche_idx);
void aESS_actor_move(ACTOR* actorx, GAME* game);
void aESS_actor_draw(ACTOR* actorx, GAME* game);
int aESS_talk_init(ACTOR* actorx, GAME* game);
void aESS_norm_talk_request(NPC_SPEECH_SONCHO* soncho, GAME_PLAY* play);
int aESS_norm_talk_end_chk(NPC_SPEECH_SONCHO* soncho);
void aESS_force_talk_request(NPC_SPEECH_SONCHO* soncho, GAME_PLAY* play);
int aESS_force_talk_end_chk(NPC_SPEECH_SONCHO* soncho);

// clang-format off
ACTOR_PROFILE Ev_Speech_Soncho_Profile = {
    mAc_PROFILE_EV_SPEECH_SONCHO,
    ACTOR_PART_NPC,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    SP_NPC_EV_SPEECH_SONCHO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_SPEECH_SONCHO),
    &aESS_actor_ct,
    &aESS_actor_dt,
    &aESS_actor_init,
    mActor_NONE_PROC1,
    &aESS_actor_save,
};
// clang-format on

void aESS_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = { &aESS_actor_move,
                                      &aESS_actor_draw,
                                      5,
                                      mActor_NONE_PROC1,
                                      &aESS_talk_init,
                                      (aNPC_TALK_END_CHECK_PROC)mActor_NONE_PROC1,
                                      1 };
    NPC_SPEECH_SONCHO* soncho = (NPC_SPEECH_SONCHO*)actorx;
    if (CLIP(npc_clip)->birth_check_proc(actorx, game) == TRUE) {
        soncho->npc_class.schedule.schedule_proc = (aNPC_SCHEDULE_PROC)aESS_schedule_proc;
        CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);
        CLIP(npc_clip)->animation_init_proc(actorx, 5, 0);
    }
}

void aESS_actor_save(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->save_proc(actorx, game);
}

void aESS_actor_dt(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->dt_proc(actorx, game);
}

void aESS_actor_init(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->init_proc(actorx, game);
}

void aESS_actor_move(ACTOR* actorx, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    if (actorx->parent_actor == NULL) {
        actorx->parent_actor =
            Actor_info_name_search(&play->actor_info, mAc_PROFILE_GROUNDHOG_CONTROL, ACTOR_PART_CONTROL);
    }
    CLIP(npc_clip)->move_proc(actorx, game);
}

void aESS_actor_draw(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->draw_proc(actorx, game);
}

#include "src/actor/npc/event/ac_ev_speech_soncho_talk.c_inc"
