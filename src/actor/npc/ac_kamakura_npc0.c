#include "ac_kamakura_npc0.h"

#include "ac_npc.h"
#include "ac_npc_h.h"
#include "ac_quest_manager.h"
#include "ac_quest_manager_clip.h"
#include "dolphin/os/OSRtc.h"
#include "libc64/qrand.h"
#include "libultra/libultra.h"
#include "m_actor_type.h"
#include "m_bgm.h"
#include "m_card.h"
#include "m_choice.h"
#include "m_common_data.h"
#include "m_config.h"
#include "m_demo.h"
#include "m_lib.h"
#include "m_msg.h"
#include "m_name_table.h"
#include "m_npc.h"
#include "m_play.h"
#include "m_play_h.h"
#include "m_player.h"
#include "m_player_lib.h"
#include "m_room_type.h"
#include "m_soncho.h"
#include "m_vibctl.h"
#include "types.h"

static void aKM0_actor_ct(ACTOR* actorx, GAME* game);
static void aKM0_actor_save(ACTOR* actorx, GAME* game);
static void aKM0_actor_dt(ACTOR* actorx, GAME* game);
static void aKM0_actor_init(ACTOR* actorx, GAME* game);
static void aKM0_actor_move(ACTOR* actorx, GAME* game);
static void aKM0_actor_draw(ACTOR* actorx, GAME* game);

static void aKM0_talk_request(ACTOR* actorx, GAME* game);
static int aKM0_talk_init(ACTOR* actorx, GAME* game);
static int aKM0_talk_end_chk(ACTOR* actorx, GAME* game);
// clang-format off
ACTOR_PROFILE Kamakura_Npc0_Profile = {
    mAc_PROFILE_KAMAKURA_NPC0,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_KAMUKURA_NPC0_ACTOR),
    aKM0_actor_ct,
    aKM0_actor_dt,
    aKM0_actor_init,
    mActor_NONE_PROC1,
    aKM0_actor_save,
};
// clang-format on

static void aKM0_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        &aKM0_actor_move, 
        &aKM0_actor_draw,   
        aNPC_CT_SCHED_TYPE_WANDER, 
        &aKM0_talk_request,
        &aKM0_talk_init,  
        &aKM0_talk_end_chk, 
        0,
    };
    // clang-format on
    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        NPC_CLIP->set_start_pos_proc(actorx);
    }
}

static void aKM0_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aKM0_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aKM0_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aKM0_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
}

static void aKM0_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_kamakura_npc0_talk.c_inc"
