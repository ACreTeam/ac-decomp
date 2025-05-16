#include "ac_halloween_npc.h"

#include "ac_npc.h"
#include "ac_npc_h.h"
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
#include "m_npc.h"
#include "m_play.h"
#include "m_play_h.h"
#include "m_player.h"
#include "m_player_lib.h"
#include "m_room_type.h"
#include "m_soncho.h"
#include "m_vibctl.h"
#include "types.h"

static void aHWN_actor_ct(ACTOR* actorx, GAME* game);
static void aHWN_actor_dt(ACTOR* actorx, GAME* game);
static void aHWN_actor_save(ACTOR* actorx, GAME* game);
static void aHWN_actor_init(ACTOR* actorx, GAME* game);
static void aHWN_actor_draw(ACTOR* actorx, GAME* game);

static BOOL aHWN_set_request_act(HALLOWEEN_NPC_ACTOR* actorx, u8 prio, u8 idx, u8 type, u16 obj, s16 move_x,
                                 s16 move_z);
static void aHWN_actor_move(ACTOR* actorx, GAME* game);

static int aHWN_get_trick_type();
static void aHWN_restart_msg_win(HALLOWEEN_NPC_ACTOR* actorx, int msg_idx);
static void aHWN_first_call_talk_proc(HALLOWEEN_NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_trick_or_treat_talk_proc(HALLOWEEN_NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_menu_open_wait_talk_proc(HALLOWEEN_NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_menu_close_wait_talk_proc(HALLOWEEN_NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_get_other_item_wait_talk_proc(HALLOWEEN_NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_receive_tool_item_start_wait_talk_proc(HALLOWEEN_NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_receive_tool_item_end_wait_talk_proc(HALLOWEEN_NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_trick_timing_wait_talk_proc(HALLOWEEN_NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_trick_chg_cloth_talk_proc(HALLOWEEN_NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_trick_chg_cloth_end_wait_talk_proc(HALLOWEEN_NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_get_ame_wait_talk_proc(HALLOWEEN_NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_get_ame_talk_proc(HALLOWEEN_NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_pl_demo_code_end_wait_talk_proc(HALLOWEEN_NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_change_talk_proc(HALLOWEEN_NPC_ACTOR* actorx, int talk_proc_idx);
static void aHWN_set_force_talk_info(ACTOR* actorx);
static void aHWN_force_talk_request(ACTOR* actorx, GAME* game);
static void aHWN_set_norm_talk_info(HALLOWEEN_NPC_ACTOR* actorx);
static void aHWN_norm_talk_request(ACTOR* actorx, GAME* game);
static int aHWN_talk_init();
static BOOL aHWN_talk_end_chk(ACTOR* actorx, GAME* game);

static void aHWN_approach(HALLOWEEN_NPC_ACTOR* hwn_actor, GAME_PLAY* play);
static void aHWN_approach_wait(HALLOWEEN_NPC_ACTOR* hwn_actor, GAME_PLAY* play);
static void aHWN_think_main_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_think_init_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_approach_init(HALLOWEEN_NPC_ACTOR* hwn_actor, GAME_PLAY* play);
static void aHWN_approach_wait_init(HALLOWEEN_NPC_ACTOR* hwn_actor, GAME_PLAY* play);
static void aHWN_setup_think_proc(HALLOWEEN_NPC_ACTOR* hwn_actor, GAME_PLAY* play, int dt_tbl_idx);
static void aHWN_think_proc(NPC_ACTOR* actorx, GAME_PLAY* play, int think_proc_idx);
static void aHWN_schedule_think_init(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_schedule_init_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_schedule_main_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aHWN_schedule_proc(NPC_ACTOR* actorx, GAME_PLAY* play, int sche_proc_idx);

// clang-format off
ACTOR_PROFILE Halloween_Npc_Profile = {
    mAc_PROFILE_HALLOWEEN_NPC,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(HALLOWEEN_NPC_ACTOR),
    aHWN_actor_ct,
    aHWN_actor_dt,
    aHWN_actor_init,
    mActor_NONE_PROC1,
    aHWN_actor_save,
};
// clang-format on

static void aHWN_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        &aHWN_actor_move, 
        &aHWN_actor_draw,   
        aNPC_CT_SCHED_TYPE_SPECIAL, 
        &aHWN_force_talk_request,
        &aHWN_talk_init,  
        &aHWN_talk_end_chk, 
        0,
    };
    // clang-format on
    HALLOWEEN_NPC_ACTOR* hwn_actor = (HALLOWEEN_NPC_ACTOR*)actorx;
    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        hwn_actor->npc_class.schedule.schedule_proc = &aHWN_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        hwn_actor->npc_class.palActorIgnoreTimer = -1;
    }
}

static void aHWN_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aHWN_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aHWN_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aHWN_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_halloween_npc_move.c_inc"

#include "../src/actor/npc/ac_halloween_npc_talk.c_inc"

#include "../src/actor/npc/ac_halloween_npc_schedule.c_inc"
