#include "ac_npc_majin5.h"

#include "ac_npc.h"
#include "ac_npc_h.h"
#include "ac_quest_manager.h"
#include "ac_quest_manager_clip.h"
#include "dolphin/os/OSRtc.h"
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

static void aNMJ5_actor_ct(ACTOR* actorx, GAME* game);
static void aNMJ5_actor_save(ACTOR* actorx, GAME* game);
static void aNMJ5_actor_dt(ACTOR* actorx, GAME* game);
static void aNMJ5_actor_init(ACTOR* actorx, GAME* game);
static int aNMJ5_set_request_act(NPC_MAJIN5_ACTOR* actorx, u8 prio, u8 idx, u8 type, u16 obj, s16 move_x, s16 move_z);
static void aNMJ5_actor_move(ACTOR* actorx, GAME* game);
static void aNMJ5_actor_draw(ACTOR* actorx, GAME* game);

static void aNMJ5_think_main_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aNMJ5_think_init_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aNMJ5_think_proc(NPC_ACTOR* actorx, GAME_PLAY* play, int think_proc_idx);
static void aNMJ5_schedule_init_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aNMJ5_schedule_main_proc(NPC_ACTOR* actorx, GAME_PLAY* play);
static void aNMJ5_schedule_proc(NPC_ACTOR* actorx, GAME_PLAY* play, int sche_proc_idx);
// clang-format off
ACTOR_PROFILE Npc_Majin5_Profile = {
    mAc_PROFILE_NPC_MAJIN5,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_MAJIN5,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_MAJIN5_ACTOR),
    aNMJ5_actor_ct,
    aNMJ5_actor_dt,
    aNMJ5_actor_init,
    mActor_NONE_PROC1,
    aNMJ5_actor_save,
};
// clang-format on
static void aNMJ5_actor_ct(ACTOR* actorx, GAME* game) {
    NPC_MAJIN5_ACTOR* majin5_actor = (NPC_MAJIN5_ACTOR*)actorx;
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        &aNMJ5_actor_move, 
        &aNMJ5_actor_draw,   
        aNPC_CT_SCHED_TYPE_SPECIAL, 
        NULL,
        NULL,
        NULL,
        0,
    };
    // clang-format on
    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        majin5_actor->npc_class.schedule.schedule_proc = &aNMJ5_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        majin5_actor->npc_class.right_hand.umbrella_disabled_flag = TRUE;
        majin5_actor->npc_class.palActorIgnoreTimer = -1;
        majin5_actor->npc_class.collision.check_kind = aNPC_BG_CHECK_TYPE_NONE;
        majin5_actor->npc_class.condition_info.demo_flg = -1;
        majin5_actor->npc_class.actor_class.world.position.x =
            majin5_actor->npc_class.actor_class.home.position.x - 80.0f;
        majin5_actor->npc_class.actor_class.world.position.z =
            majin5_actor->npc_class.actor_class.home.position.z + 480.0f;

        CLIP(effect_clip)
            ->effect_make_proc(eEC_EFFECT_RESET_HOLE, majin5_actor->npc_class.actor_class.world.position, 3, 31000,
                               game, -1, 0, 0);
    }
}

static void aNMJ5_actor_save(ACTOR* actorx, GAME* game) {
    mNpc_RenewalSetNpc(actorx);
}

static void aNMJ5_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
    CLIP(effect_clip)->effect_kill_proc(eEC_EFFECT_RESET_HOLE, -1);
}

static void aNMJ5_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static int aNMJ5_set_request_act(NPC_MAJIN5_ACTOR* actorx, u8 prio, u8 idx, u8 type, u16 obj, s16 move_x, s16 move_z) {
    BOOL res = FALSE;
    if (prio >= actorx->npc_class.request.act_priority) {
        u16 args[aNPC_REQUEST_ARG_NUM];
        bzero(args, sizeof(args));
        args[0] = obj;
        args[2] = move_x;
        args[3] = move_z;
        actorx->npc_class.request.act_priority = prio;
        actorx->npc_class.request.act_idx = idx;
        actorx->npc_class.request.act_type = type;
        mem_copy((u8*)actorx->npc_class.request.act_args, (u8*)args, sizeof(args));
        res = TRUE;
    }
    return res;
}

static void aNMJ5_actor_move(ACTOR* actorx, GAME* game) {
    aNTT_event_save_c* save_area;
    save_area = (aNTT_event_save_c*)mEv_get_save_area(mEv_EVENT_KK_SLIDER, 10);
    NPC_CLIP->move_proc(actorx, game);
    actorx->shape_info.rotation.y = 31000;
    if ((save_area != NULL) && (save_area->bitfield & aNTT_FLAG_SP_DELETE_MAJIN)) {
        save_area->bitfield &= ~aNTT_FLAG_SP_DELETE_MAJIN;
        Actor_delete(actorx);
    }
    actorx->shape_info.draw_shadow = FALSE;
}

static void aNMJ5_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_majin5_schedule.c_inc"
