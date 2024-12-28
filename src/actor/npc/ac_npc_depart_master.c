#include "ac_npc_depart_master.h"

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

void aNDM_actor_ct(ACTOR* depart_master, GAME* game);
void aNDM_actor_dt(ACTOR* actorx, GAME* game);
void aNDM_actor_move(ACTOR* actorx, GAME* game);
void aNDM_actor_draw(ACTOR* actorx, GAME* game);
void aNDM_actor_init(ACTOR* actorx, GAME* game);
void aNDM_actor_save(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Depart_Master_Profile = {
    mAc_PROFILE_NPC_DEPART_MASTER,    
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_DEPART_MASTER,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_DEPART_MASTER_ACTOR),
    &aNDM_actor_ct,
    &aNDM_actor_dt,
    &aNDM_actor_init,
    mActor_NONE_PROC1,
    &aNDM_actor_save,
};
// clang-format on

// TODO: are these declared in every file? DnM+ says they're static yet they seemingly must be defined after their usage...
static void aNSC_setupAction(NPC_DEPART_MASTER_ACTOR *depart_master, GAME_PLAY* play, int p3);
static int aNSC_check_buy_item_sub(u32 *p1, mActor_name_t itm_name);
static int aNSC_check_buy_paper(u32 *p1, mActor_name_t itm_name);
static void aNSC_init_proc(NPC_DEPART_MASTER_ACTOR *depart_master, GAME_PLAY * play, int p3);
static void aNSC_BGcheck(ACTOR* actorx);
static void aNSC_set_zone_data(NPC_DEPART_MASTER_ACTOR* depart_master, ACTOR* actor);
static void aNSC_set_player_angl(NPC_DEPART_MASTER_ACTOR* depart_master);
static void aNSC_talk_demo_proc(ACTOR* actorx);
static void aNSC_sell_camera(NPC_DEPART_MASTER_ACTOR* depart_master, GAME_PLAY* play);

void aNDM_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        &aNDM_actor_move, &aNDM_actor_draw, 0, NULL, NULL, NULL, 1,
    };

    NPC_DEPART_MASTER_ACTOR* depart_master = (NPC_DEPART_MASTER_ACTOR*)actorx;
    int action;

    CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);

    depart_master->npc_class.draw.main_animation.keyframe.morph_counter = 0.0f;
    depart_master->sell_item = EMPTY_NO;
    depart_master->npc_class.condition_info.hide_flg = FALSE;
    depart_master->talk_start_tim = -1;
    actorx->shape_info.draw_shadow = TRUE;

    action = 0;
    if (Common_Get(door_data).door_actor_name == RSV_NO) {
        depart_master->npc_class.talk_info.melody_inst = 0;
        action = 61;
    } else if (Common_Get(last_scene_no) == SCENE_DEPART_2) {
        depart_master->npc_class.talk_info.melody_inst = 0;
        action = 61;

        actorx->world.position.x = 320.0f;
        actorx->world.position.z = 200.0f;
        actorx->shape_info.rotation.y = DEG2SHORT_ANGLE2(180.0f);
        actorx->world.angle.y = DEG2SHORT_ANGLE2(180.0f);
    }

    depart_master->_9B9 = Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_EVENT;
    aNSC_setupAction(depart_master, (GAME_PLAY*)game, action);
}

void aNDM_actor_save(ACTOR* actorx, GAME* game) {
    (CLIP(npc_clip)->save_proc)(actorx, game);
}

void aNDM_actor_dt(ACTOR* actorx, GAME* game) {
    (CLIP(npc_clip)->dt_proc)(actorx, game);
}

void aNDM_actor_init(ACTOR* actorx, GAME* game) {
    (CLIP(npc_clip)->init_proc)(actorx, game);
}

void aNDM_actor_draw(ACTOR* actorx, GAME* game) {
    (CLIP(npc_clip)->draw_proc)(actorx, game);
}

#include "../src/actor/npc/ac_npc_depart_master_move.c_inc"
