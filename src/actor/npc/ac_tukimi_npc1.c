#include "ac_tukimi_npc1.h"

#include "ac_npc.h"
#include "ac_npc_h.h"
#include "ac_quest_manager.h"
#include "audio.h"
#include "dolphin/os/OSRtc.h"
#include "game.h"
#include "libc64/qrand.h"
#include "libultra/libultra.h"
#include "m_actor.h"
#include "m_actor_type.h"
#include "m_bgm.h"
#include "m_card.h"
#include "m_choice.h"
#include "m_common_data.h"
#include "m_config.h"
#include "m_demo.h"
#include "m_event.h"
#include "m_field_info.h"
#include "m_land.h"
#include "m_lib.h"
#include "m_msg.h"
#include "m_npc.h"
#include "m_play.h"
#include "m_play_h.h"
#include "m_player_lib.h"
#include "m_private.h"
#include "m_quest.h"
#include "m_soncho.h"
#include "m_submenu.h"
#include "m_vibctl.h"
#include "sys_math.h"
#include "types.h"

static void aTM1_actor_ct(ACTOR* actorx, GAME* game);
static void aTM1_actor_save(ACTOR* actorx, GAME* game);
static void aTM1_actor_dt(ACTOR* actorx, GAME* game);
static void aTM1_actor_init(ACTOR* actorx, GAME* game);
static void aTM1_actor_move(ACTOR* actorx, GAME* game);
static void aTM1_actor_draw(ACTOR* actorx, GAME* game);

static void aTM1_set_animation(ACTOR* actorx, int anime_idx);

static void aTM1_set_request_act(NPC_ACTOR* actorx);
static void aTM1_act_chg_data_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aTM1_act_init_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aTM1_act_proc(NPC_ACTOR* actorx, GAME_PLAY* play, int act_idx);
static void aTM1_think_main_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aTM1_think_init_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aTM1_think_proc(NPC_ACTOR* actorx, GAME_PLAY* play, int think_idx);
static void aTM1_schedule_init_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aTM1_schedule_main_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aTM1_schedule_proc(NPC_ACTOR* actorx, GAME_PLAY* play,  int sche_proc_idx);
static void aTM1_set_talk_info(ACTOR* actorx);
static void aTM1_set_talk_info2(ACTOR* actorx);
static void aTM1_talk_request(ACTOR* actorx, GAME* game);
static int aTM1_talk_init(ACTOR* actorx, GAME* game);
static int aTM1_talk_end_chk(ACTOR* actorx, GAME* game);


// clang-format off
ACTOR_PROFILE Tukimi_Npc1_Profile = {
    mAc_PROFILE_TUKIMI_NPC1,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(TUKIMI_NPC1_ACTOR),
    aTM1_actor_ct,
    aTM1_actor_dt,
    aTM1_actor_init,
    mActor_NONE_PROC1,
    aTM1_actor_save,
};
// clang-format on

static void aTM1_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        &aTM1_actor_move,
        &aTM1_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        &aTM1_talk_request,
        &aTM1_talk_init,
        &aTM1_talk_end_chk,
        0,
    };
    // clang-format on

    TUKIMI_NPC1_ACTOR* tukimi_npc0_actor = (TUKIMI_NPC1_ACTOR*)actorx;
    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        tukimi_npc0_actor->npc_class.schedule.schedule_proc = aTM1_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data); 
    }
}

static void aTM1_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aTM1_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aTM1_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aTM1_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
}

static void aTM1_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_tukimi_npc1_anime.c_inc"

#include "../src/actor/npc/ac_tukimi_npc1_talk.c_inc"
