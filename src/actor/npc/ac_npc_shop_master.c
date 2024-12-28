#include "ac_npc_shop_master.h"

#include "m_shop.h"
#include "m_common_data.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_private.h"
#include "m_string.h"
#include "m_actor_type.h"
#include "m_player_lib.h"
#include "m_mail_password_check.h"
#include "m_actor.h"
#include "m_actor_type.h"
#include "m_camera2.h"
#include "m_house.h"
#include "m_melody.h"
#include "m_scene.h"
#include "m_collision_bg.h"
#include "m_demo.h"
#include "m_player.h"
#include "m_bgm.h"
#include "ac_npc.h"
#include "ac_uki.h"
#include "ac_npc_anim_def.h"

void aNSM_actor_ct(ACTOR* shop_master, GAME* game);
void aNSM_actor_dt(ACTOR* actorx, GAME* game);
void aNSM_actor_move(ACTOR* actorx, GAME* game);
void aNSM_actor_draw(ACTOR* actorx, GAME* game);
void aNSM_actor_init(ACTOR* actorx, GAME* game);
void aNSM_actor_save(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Shop_Master_Profile = {
    mAc_PROFILE_NPC_SHOP_MASTER,    
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_SHOP_MASTER,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_SHOP_MASTER_ACTOR),
    &aNSM_actor_ct,
    &aNSM_actor_dt,
    &aNSM_actor_init,
    mActor_NONE_PROC1,
    &aNSM_actor_save,
};
// clang-format on

// TODO: are these declared in every file? DnM+ says they're static yet they seemingly must be defined after their usage...
static void aNSC_setupAction(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY* play, int p3);
static int aNSC_check_buy_item_sub(u32 *p1, mActor_name_t itm_name);
static int aNSC_check_buy_paper(u32 *p1, mActor_name_t itm_name);
static void aNSC_init_proc(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY * play, int p3);
static void aNSC_BGcheck(ACTOR* actorx);
static void aNSC_set_zone_data(NPC_SHOP_MASTER_ACTOR* shop_master, ACTOR* actor);
static void aNSC_set_player_angl(NPC_SHOP_MASTER_ACTOR* shop_master);
static void aNSC_talk_demo_proc(ACTOR* actorx);
static void aNSC_sell_camera(NPC_SHOP_MASTER_ACTOR* shop_master, GAME_PLAY* play);

void aNSM_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        &aNSM_actor_move, &aNSM_actor_draw, 0, NULL, NULL, NULL, 1,
    };

    NPC_SHOP_MASTER_ACTOR* shop_master = (NPC_SHOP_MASTER_ACTOR*)actorx;
    int action = 0;

    CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);

    shop_master->npc_class.draw.main_animation.keyframe.morph_counter = 0.0f;
    shop_master->sell_item = EMPTY_NO;
    shop_master->npc_class.condition_info.hide_flg = FALSE;
    shop_master->talk_start_tim = -1;
    actorx->shape_info.draw_shadow = TRUE;

    if (Common_Get(door_data).door_actor_name == RSV_NO) {
        shop_master->npc_class.talk_info.melody_inst = 0;
        action = 61;
    } else {
        action = 0;
    }

    aNSC_setupAction(shop_master, (GAME_PLAY*)game, action);
}

void aNSM_actor_save(ACTOR* actorx, GAME* game) {
    (CLIP(npc_clip)->save_proc)(actorx, game);
}

void aNSM_actor_dt(ACTOR* actorx, GAME* game) {
    (CLIP(npc_clip)->dt_proc)(actorx, game);
}

void aNSM_actor_init(ACTOR* actorx, GAME* game) {
    (CLIP(npc_clip)->init_proc)(actorx, game);
}

void aNSM_actor_draw(ACTOR* actorx, GAME* game) {
    (CLIP(npc_clip)->draw_proc)(actorx, game);
}

#include "../src/actor/npc/ac_npc_shop_master_move.c_inc"
