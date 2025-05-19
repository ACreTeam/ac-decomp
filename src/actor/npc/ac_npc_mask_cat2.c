#include "ac_npc_mask_cat2.h"

#include "ac_npc.h"
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
#include "types.h"
#include "ac_train_door.h"
static void aNM2_actor_ct(ACTOR* actorx, GAME* game);
static void aNM2_actor_save(ACTOR* actorx, GAME* game);
static void aNM2_actor_dt(ACTOR* actorx, GAME* game);
static void aNM2_actor_init(ACTOR* actorx, GAME* game);
static void aNM2_actor_draw(ACTOR* actorx, GAME* game);

static void aNM2_set_animation(ACTOR* actorx, int anime_idx);
static void aNM2_set_camera(NPC_MASK_CAT2_ACTOR* actorx, GAME_PLAY* play);
static void aNM2_set_camera_eyes(NPC_MASK_CAT2_ACTOR* actorx);
static void aNM2_set_walk_spd(NPC_MASK_CAT2_ACTOR* actorx);
static void aNM2_set_stop_spd(NPC_MASK_CAT2_ACTOR* actorx);
static void aNM2_talk_demo_proc(ACTOR* actorx);
static int aNM2_count_player_num_nextland(u8* player_name_array);
static int aNM2_count_player_num_beforeland(u8* player_name_array);
static void aNM2_set_free_str();
static int aNM2_GetBeforePrivateIdx(Private_c* now_priv);
static int aNM2_get_msg_no_mishiranuneko_talk_start();
static BOOL aNM2_chg_cond_keitai(NPC_MASK_CAT2_ACTOR* actorx, int mode);
static void aNM2_make_shasho(NPC_MASK_CAT2_ACTOR* actorx, GAME_PLAY* play);
static BOOL aNM2_chk_mask_texture();
static void aNM2_set_next_village_map();
static void aNM2_set_talk_info_announce_start_wait(ACTOR* actorx);
static void aNM2_announce_start_wait(ACTOR* actorx, GAME* game);
static void aNM2_save_start_wait(ACTOR* actorx, GAME* game);
static void aNM2_save_end_wait(ACTOR* actorx, GAME* game);
static void aNM2_announce_end_wait(ACTOR* actorx, GAME* game);
static void aNM2_walk_deck(ACTOR* actorx, GAME* game);
static void aNM2_turn_deck(ACTOR* actorx, GAME* game);
static void aNM2_keitai_off_start_wait(ACTOR* actorx, GAME* game);
static void aNM2_keitai_off_end_wait(ACTOR* actorx, GAME* game);
static void aNM2_enter(ACTOR* actorx, GAME* game);
static void aNM2_approach(ACTOR* actorx, GAME* game);
static void aNM2_set_talk_info_talk_start_wait(ACTOR* actorx);
static void aNM2_talk_start_wait(ACTOR* actorx, GAME* game);
static void aNM2_set_talk_info_talk_start_wait2(ACTOR* actorx);
static void aNM2_talk_start_wait2(ACTOR* actorx, GAME* game);
static void aNM2_sitdown_start_wait(ACTOR* actorx, GAME* game);
static void aNM2_sitdown(ACTOR* actorx, GAME* game);
static void aNM2_sdon_and_pb_wait(ACTOR* actorx, GAME* game);
static void aNM2_draw_menu_open_wait(ACTOR* actorx, GAME* game);
static void aNM2_draw_menu_close_wait(ACTOR* actorx, GAME* game);
static void aNM2_msg_win_open_wait(ACTOR* actorx, GAME* game);
static void aNM2_talk_end_wait(ACTOR* actorx, GAME* game);
static void aNM2_announce_start_wait_init(NPC_MASK_CAT2_ACTOR* actorx, GAME_PLAY* play);
static void aNM2_announce_start_wait2_init(NPC_MASK_CAT2_ACTOR* actorx, GAME_PLAY* play);
static void aNM2_walk_deck_init(NPC_MASK_CAT2_ACTOR* actorx, GAME_PLAY* play);
static void aNM2_turn_deck_init(NPC_MASK_CAT2_ACTOR* actorx, GAME_PLAY* play);
static void aNM2_keitai_off_start_wait_init(NPC_MASK_CAT2_ACTOR* actorx, GAME_PLAY* play);
static void aNM2_keitai_off_end_wait_init(NPC_MASK_CAT2_ACTOR* actorx, GAME_PLAY* play);
static void aNM2_approach_init(NPC_MASK_CAT2_ACTOR* actorx, GAME_PLAY* play);
static void aNM2_talk_start_wait_init(NPC_MASK_CAT2_ACTOR* actorx, GAME_PLAY* play);
static void aNM2_talk_start_wait2_init(NPC_MASK_CAT2_ACTOR* actorx, GAME_PLAY* play);
static void aNM2_sitdown_start_wait_init(NPC_MASK_CAT2_ACTOR* actorx, GAME_PLAY* play);
static void aNM2_sitdown_init(NPC_MASK_CAT2_ACTOR* actorx, GAME_PLAY* play);
static void aNM2_draw_menu_open_wait_init(NPC_MASK_CAT2_ACTOR* actorx, GAME_PLAY* play);
static void aNM2_draw_menu_close_wait_init(NPC_MASK_CAT2_ACTOR* actorx, GAME_PLAY* play);
static void aNM2_msg_win_open_wait_init();
static void aNM2_talk_end_wait_init();
static void aNM2_scene_change_wait_init(NPC_MASK_CAT2_ACTOR* actorx, GAME_PLAY* play);
static void aNM2_init_proc(ACTOR* actorx, GAME* game, int init_proc_idx);
static void aNM2_setupAction(ACTOR* actorx, GAME* game, int process_idx);
static void aNM2_actor_move(ACTOR* actorx, GAME* game);
// clang-format off
ACTOR_PROFILE Npc_Mask_Cat2_Profile = {
    mAc_PROFILE_NPC_MASK_CAT2,
    ACTOR_PART_NPC,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    SP_NPC_MASK_CAT2,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_MASK_CAT2_ACTOR),
    aNM2_actor_ct,
    aNM2_actor_dt,
    aNM2_actor_init,
    mActor_NONE_PROC1,
    aNM2_actor_save,
};
// clang-format on

static void aNM2_actor_ct(ACTOR* actorx, GAME* game) {
    NPC_MASK_CAT2_ACTOR* mask_cat2_actor = (NPC_MASK_CAT2_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player_actor;
    int process_idx;
    mNpc_MaskNpc_c* npc_info_mask;

    // clang-format off
    static aNPC_ct_data_c ct_data = {
        &aNM2_actor_move, 
        &aNM2_actor_draw,   
        aNPC_CT_SCHED_TYPE_NONE, 
        NULL,
        NULL,
        NULL,
        0,
    };
    // clang-format on

    NPC_CLIP->ct_proc(actorx, game, &ct_data);
    mask_cat2_actor->npc_class.condition_info.demo_flg =
        aNPC_COND_DEMO_SKIP_MOVE_RANGE_CHECK | aNPC_COND_DEMO_SKIP_MOVE_CIRCLE_REV | aNPC_COND_DEMO_SKIP_MOVE_Y |
        aNPC_COND_DEMO_SKIP_OBJ_COL_CHECK | aNPC_COND_DEMO_SKIP_BGCHECK | aNPC_COND_DEMO_SKIP_FORWARD_CHECK |
        aNPC_COND_DEMO_SKIP_ITEM | aNPC_COND_DEMO_SKIP_TALK_CHECK | aNPC_COND_DEMO_SKIP_HEAD_LOOKAT |
        aNPC_COND_DEMO_SKIP_ENTRANCE_CHECK;
    mask_cat2_actor->camera_morph_counter = 40;
    mask_cat2_actor->obj_look_type = 0;
    mask_cat2_actor->npc_class.eye_y = 30.0f;
    mask_cat2_actor->camera_move_set_counter = 1;
    mask_cat2_actor->npc_class.palActorIgnoreTimer = -1;
    mask_cat2_actor->train_door_actor = Actor_info_fgName_search(&play->actor_info, TRAIN_DOOR, ACTOR_PART_BG);
    mask_cat2_actor->npc_class.actor_class.shape_info.draw_shadow = TRUE;
    mPlib_request_main_demo_wait_type1(game, FALSE, NULL);

    player_actor = GET_PLAYER_ACTOR(play);
    if (player_actor != NULL) {
        player_actor->actor_class.state_bitfield |= ACTOR_STATE_INVISIBLE;
    }

    process_idx = aNM2_MOVE_ANNOUNCE_START_WAIT;
    npc_info_mask = mask_cat2_actor->npc_class.npc_info.mask;
    if ((npc_info_mask == 0) || npc_info_mask->npc_id == SP_NPC_GUIDE) {
        process_idx = aNM2_MOVE_ANNOUNCE_START_WAIT_DUPE_1;
        mask_cat2_actor->npc_class.actor_class.shape_info.rotation.y = -0x8000;
        mask_cat2_actor->npc_class.actor_class.world.angle.y = 0;
        mask_cat2_actor->npc_class.actor_class.world.position.z = 130.0f;
        mask_cat2_actor->npc_class.condition_info.hide_flg = FALSE;
    } else {
        mask_cat2_actor->npc_class.actor_class.shape_info.rotation.y = 0x4000;
        mask_cat2_actor->npc_class.actor_class.world.angle.y = 0x4000;
        mask_cat2_actor->npc_class.actor_class.world.position.x = 100.0f;
        mask_cat2_actor->npc_class.actor_class.world.position.z = 48.0f;
        mMC_mask_cat_init();
        mMC_set_time();
        mem_clear((u8*)&(Save_Get(mask_cat.design.design)), 0x200, 0xff);
        Save_Set(mask_cat.palette_no, mNW_PALETTE15);
    }

    aNM2_setupAction(&mask_cat2_actor->npc_class.actor_class, &play->game, process_idx);
    sAdo_SysLevStart(NA_SE_TRAIN_RIDE);
    Common_Set(sunlight_flag, FALSE);
    sAdo_TrgSeEcho(TRUE);
    sAdo_LevSeEcho(TRUE);
}

static void aNM2_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aNM2_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_MASK_CAT2_ACTOR* mask_cat2_actor = (NPC_MASK_CAT2_ACTOR*)actorx;
    ACTOR* sasho_actor;

    mask_cat2_actor->npc_class.actor_class.npc_id = SP_NPC_MASK_CAT2;
    sasho_actor = mask_cat2_actor->sasho_actor;
    if (mask_cat2_actor->sasho_actor) {
        mask_cat2_actor->sasho_actor = NULL;
        sasho_actor->parent_actor = NULL;
    }

    NPC_CLIP->dt_proc(actorx, game);
    Common_Set(demo_profiles[0], mAc_PROFILE_RIDE_OFF_DEMO);
    sAdo_SysLevStop(NA_SE_TRAIN_RIDE);
}

static void aNM2_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aNM2_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_mask_cat2_move.c_inc"
