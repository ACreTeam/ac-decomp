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

static void aNSM_actor_ct(ACTOR *shop_master, GAME* game);
static void aNSM_actor_dt(ACTOR* actorx, GAME* game);
static void aNSM_actor_move(ACTOR* actorx, GAME* game);
static void aNSM_actor_draw(ACTOR* actorx, GAME* game);
static void aNSM_actor_init(ACTOR* actorx, GAME* game);
static void aNSM_actor_save(ACTOR* actorx, GAME* game);

static void aNSM_talk_request(ACTOR* actorx, GAME* game);
static int aNSM_talk_init(ACTOR* actorx, GAME* game);
static int aNSM_talk_end_chk(ACTOR* actorx, GAME* game);

static void aNSC_BGcheck(ACTOR *actorx);
static void aNSC_set_zone_data(NPC_SHOP_MASTER_ACTOR *shop_master, ACTOR *actor);
static void aNSC_set_player_angl(NPC_SHOP_MASTER_ACTOR *shop_master);
static void aNSC_talk_demo_proc(ACTOR *actorx);
static void aNSC_sell_camera(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game);

static void aNSM_actor_ct(ACTOR *actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        &aNSM_actor_move,
        &aNSM_actor_draw,
        0,
        &aNSM_talk_request,
        &aNSM_talk_init,
        &aNSM_talk_end_chk,
        TRUE 
    };

    NPC_SHOP_MASTER_ACTOR *shop_master = (NPC_SHOP_MASTER_ACTOR *)actorx;
    int action = 0;

    CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);

    shop_master->npc_class.draw.main_animation.keyframe.morph_counter = 0.0f;
    shop_master->sell_item = EMPTY_NO;
    shop_master->npc_class.condition_info.hide_flg = FALSE;
    shop_master->_9C0 = -1;
    actorx->shape_info.draw_shadow = TRUE;

    if (Common_Get(door_data).door_actor_name == RSV_NO) {
        shop_master->npc_class.talk_info.melody_inst = 0;
        action = 0x3d; 
    } else {
        action = 0;
    }

    aNSC_setupAction(shop_master, (GAME_PLAY *)game, action);
}

static void aNSM_actor_save(ACTOR* actorx, GAME* game) {
    (*Common_Get(clip).npc_clip->save_proc)(actorx, game);
}

static void aNSM_actor_dt(ACTOR* actorx, GAME* game) {
    (*Common_Get(clip).npc_clip->dt_proc)(actorx, game);
}

static void aNSM_actor_init(ACTOR* actorx, GAME* game) {
    (*Common_Get(clip).npc_clip->init_proc)(actorx, game);
}

static void aNSM_actor_draw(ACTOR* actorx, GAME* game) {
    (*Common_Get(clip).npc_clip->draw_proc)(actorx, game);
}

static int aNSM_get_zone(xyz_t *wpos) {
    if (wpos->x < (f32)120.0) {
        if (wpos->z < (f32)180.0) {
            return 1;
        } else {
            return 2;
        }
    }
    if (wpos->z < (f32)160.0) {
        return 0;
    } else {
        return 3;
    }
}

static u8 aNSM_get_next_zone(u8 p1, u8 p2) {
    static u8 next_zone[16] = {0, 1, 1, 1, 0, 1, 2, 2, 1, 1, 2, 3, 2, 2, 2, 3};
    int t = p2 * 4;
    return next_zone[t + p1];
}

static void aNSM_search_player(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *play) {
    ACTOR *actorx = (ACTOR *)shop_master;
    PLAYER_ACTOR *player = get_player_actor_withoutCheck(play); 

    if (player != NULL) {
        s16 angle = actorx->shape_info.rotation.y - shop_master->player_angle;
        if (ABS(angle) > 0x4000) {
            aNSC_setupAction(shop_master, play, 0x42);
        } else {
            chase_angle(&actorx->shape_info.rotation.y, shop_master->player_angle, 0x800);
            actorx->world.angle.y = actorx->shape_info.rotation.y;
        }
    }
}

static void aNSM_search_player2(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *play) {
    static f32 posX[4] = { 220.0, 100.0, 100.0, 220.0 };
    static f32 posZ[4] = { 140.0, 140.0, 220.0, 220.0 };
    PLAYER_ACTOR *player = get_player_actor_withoutCheck(play);
    if (player != NULL) {
            f32 dz = posX[shop_master->_9A3] - shop_master->npc_class.actor_class.world.position.x;
            f32 dx = posZ[shop_master->_9A3] - shop_master->npc_class.actor_class.world.position.z;

            s16 angle = atans_table(dx, dz);
            chase_angle(&shop_master->npc_class.actor_class.shape_info.rotation.y, angle, 0x800);

            shop_master->npc_class.actor_class.world.angle.y = shop_master->npc_class.actor_class.shape_info.rotation.y;

            if (dz * dz + dx * dx < (f32)0.0) {
                shop_master->_9A3 = aNSM_get_next_zone(shop_master->_9A4, shop_master->_9A2);
            }
    }

}

static int aNSM_check_safe_zone(NPC_SHOP_MASTER_ACTOR *shop_master, PLAYER_ACTOR *player) {
    int res = FALSE;
    if (player->actor_class.world.position.z > (f32)280.0 && shop_master->_9A2 == 3) {
        res = TRUE;
    }
    return res;
}

static void aNSM_actor_move(ACTOR *actorx, GAME *game) {
    NPC_SHOP_MASTER_ACTOR *shop_master = (NPC_SHOP_MASTER_ACTOR *)actorx;
    GAME_PLAY *play = (GAME_PLAY *)game;
    PLAYER_ACTOR *player = get_player_actor_withoutCheck(play);
    CLIP(npc_clip)->move_before_proc(actorx, game);
    aNSC_BGcheck(actorx);
    aNSC_set_zone_data(shop_master, (ACTOR *)player);
    aNSC_set_player_angl(shop_master);
    ((void (*)(ACTOR *actorx, GAME *game))(shop_master->proc))(actorx, game);
    aNSC_talk_demo_proc(actorx);
    CLIP(npc_clip)->move_after_proc(actorx, game);
    aNSC_sell_camera(shop_master, play);
}

static void aNSC_set_animation(NPC_SHOP_MASTER_ACTOR* shop_master, int action) {
    static aNSC_animation_data anime[70] = { 
        {aNPC_ANIM_WAIT1, FALSE},
        {aNPC_ANIM_WALK1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WALK1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WALK1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WALK1, TRUE},
        {aNPC_ANIM_TRANSFER1, TRUE},
        {aNPC_ANIM_TRANS_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_TRANSFER1, TRUE},
        {aNPC_ANIM_TRANS_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, FALSE},
        {aNPC_ANIM_WALK1, FALSE},
        {aNPC_ANIM_WALK1, FALSE},
        {aNPC_ANIM_RUN1, FALSE},
        {aNPC_ANIM_RUN1, FALSE},
        {aNPC_ANIM_WALK1, FALSE},
        {aNPC_ANIM_WAIT1, FALSE},
        {aNPC_ANIM_WAIT1, TRUE},
        {aNPC_ANIM_WAIT1, FALSE}
    };

    aNSC_animation_data *data = &anime[action];
    CLIP(npc_clip)->animation_init_proc((ACTOR*)shop_master, data->anim, data->talk_flag);
}

static void aNSC_BGcheck(ACTOR* actor) {
    mCoBG_BgCheckControll(NULL, actor, 8.0, 0.0, 1, 0, 0);
}

static int aNSC_check_present_balloon() {
    int idx;
    int res = 0;

    if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_EVENT
            && (Common_Get(spnpc_first_talk_flags) & (1 << aNPC_SPNPC_BIT_SHOP_MASTER)) == 0) {
        idx = mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO);
        if (idx != -1) {
            res = 1;
        }
    }

    return res;
}

static void aNSC_calc_talk_start_tim(NPC_SHOP_MASTER_ACTOR* shop_master) {
    int ivar1 = shop_master->_9C0;
    if (ivar1 <= -1) {
        ivar1 = 0xb4; 
    } else if (ivar1 != 0) {
        ivar1 -= 1;
    }
    shop_master->_9C0 = ivar1;
}

static u8 aNSC_item1_0_tanni_type[256] = {aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD};

static u8 aNSC_item1_1_tanni_type[4] = {0x6, 0x6, 0x6, 0x6};

static u8 aNSC_item1_2_tanni_type[92] = {0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3}; 
static u8 aNSC_item1_3_tanni_type[40] = {aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA};

static u8 aNSC_item1_4_tanni_type[255] = {aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH, aNSC_TANNI_STR_CLOTH};

static u8 aNSC_item1_5_tanni_type[49] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

static u8 aNSC_item1_6_tanni_type[67] = {aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD};

static u8 aNSC_item1_7_tanni_type[67] = {aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD};

static u8 aNSC_item1_8_tanni_type[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0};

static u8 aNSC_item1_9_tanni_type[11] = {aNSC_TANNI_STR_SAPPLING, aNSC_TANNI_STR_SAPPLING, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6};

static u8 aNSC_item1_A_tanni_type[55] = {aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD};

static u8 aNSC_item1_B_tanni_type[16] = {aNSC_TANNI_STR_DIARY, aNSC_TANNI_STR_DIARY, aNSC_TANNI_STR_DIARY, aNSC_TANNI_STR_DIARY, aNSC_TANNI_STR_DIARY, aNSC_TANNI_STR_DIARY, aNSC_TANNI_STR_DIARY, aNSC_TANNI_STR_DIARY, aNSC_TANNI_STR_DIARY, aNSC_TANNI_STR_DIARY, aNSC_TANNI_STR_DIARY, aNSC_TANNI_STR_DIARY, aNSC_TANNI_STR_DIARY, aNSC_TANNI_STR_DIARY, aNSC_TANNI_STR_DIARY, aNSC_TANNI_STR_DIARY};

static u8 aNSC_item1_C_tanni_type[96] = {aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD, aNSC_TANNI_STR_COMMOD};

static u8 aNSC_item1_D_tanni_type[45] = {aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA, aNSC_TANNI_STR_FAUNA};

static u8 aNSC_item1_E_tanni_type[2] = {0x6, 0x6};

static u8 aNSC_item1_F_tanni_type[4] = {aNSC_TANNI_STR_KABU, aNSC_TANNI_STR_KABU, aNSC_TANNI_STR_KABU, aNSC_TANNI_STR_KABU};

static u8 * aNSC_item_tanni_type[16] = {
    aNSC_item1_0_tanni_type,
    aNSC_item1_1_tanni_type,
    aNSC_item1_2_tanni_type,
    aNSC_item1_3_tanni_type,
    aNSC_item1_4_tanni_type,
    aNSC_item1_5_tanni_type,
    aNSC_item1_6_tanni_type,
    aNSC_item1_7_tanni_type,
    aNSC_item1_8_tanni_type,
    aNSC_item1_9_tanni_type,
    aNSC_item1_A_tanni_type,
    aNSC_item1_B_tanni_type,
    aNSC_item1_C_tanni_type,
    aNSC_item1_D_tanni_type,
    aNSC_item1_E_tanni_type,
    aNSC_item1_F_tanni_type
};

static void aNSC_request_show_camera(GAME_PLAY* play, int p2) {
    static xyz_t pcenter[2][2] = { 
        { 
            { 160.0, 85.0, 180.0 }, 
            { 160.0, 60.0, 285.0 } 
        }, {
            { 160.0, 85.0, 260.0 },
            { 160.0, 60.0, 365.0 }
        }
    };
    static xyz_t peye[2][2] = {
        { 
            { 160.0, 235.0, 900.0 }, 
            { 160.0, 475.0, 840.0 } 
        }, {
            { 160.0, 285.0, 980.0 },
            { 160.0, 475.0, 920.0 }
        }
    };
    int i;

    int level = mSP_GetShopLevel();
    i = (level == 3);

    Camera2_request_BuySikimono_WallPaper(play, &pcenter[i][p2], &peye[i][p2]);
}

static void aNSC_Set_ListenAble(NPC_SHOP_MASTER_ACTOR* shop_master) {
    mMld_ActorMakeMelody((ACTOR *)shop_master);
    mDemo_Set_ListenAble();
}

static void aNSC_set_rehouse_order_date(mHm_hs_c *home) {
    lbRTC_time_c *now = &Common_Get(time).rtc_time;
    home->size_info.upgrade_order_date.year = now->year;
    home->size_info.upgrade_order_date.month = now->month;
    home->size_info.upgrade_order_date.day = now->day;
}

static void aNSC_set_stop_spd(NPC_SHOP_MASTER_ACTOR *shop_master) {
    shop_master->npc_class.actor_class.speed = 0.0;
    shop_master->npc_class.movement.max_speed = 0.0;
    shop_master->npc_class.movement.acceleration = 0.0;
    shop_master->npc_class.movement.deceleration = 0.0;
}

static void aNSC_set_walk_spd(NPC_SHOP_MASTER_ACTOR *shop_master) {
    shop_master->npc_class.movement.max_speed = 1.0;
    shop_master->npc_class.movement.acceleration = 0.1;
    shop_master->npc_class.movement.deceleration = 0.2;
}

static void aNSC_set_run_spd(NPC_SHOP_MASTER_ACTOR *shop_master) {
    shop_master->npc_class.movement.max_speed = 4.0;
    shop_master->npc_class.movement.acceleration = 0.4;
    shop_master->npc_class.movement.deceleration = 0.8;
}

static void aNSC_set_sell_camera(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *play) {
    PLAYER_ACTOR *player;
    xyz_t wpos;
    f32 bg_y;

    player = get_player_actor_withoutCheck(play);
    mFI_UtNum2CenterWpos(&wpos, shop_master->ut_x, shop_master->ut_y);
    bg_y = mCoBG_GetBgY_OnlyCenter_FromWpos2(wpos, -40.0);
    wpos.y = bg_y;
    Camera2_request_main_talk_pos(play, (ACTOR *)player, &wpos, 5);
}

static void aNSC_sell_camera(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *play) {
    if (shop_master->action >= 0x1e && shop_master->action <= 0x28) {
        switch (ITEM_NAME_GET_TYPE(shop_master->sell_item)) {
        case NAME_TYPE_FTR0:
        case NAME_TYPE_FTR1:
            aNSC_set_sell_camera(shop_master, play);
            break;
        case NAME_TYPE_ITEM1:
            switch (ITEM_NAME_GET_CAT(shop_master->sell_item)) {
            case ITEM1_CAT_CLOTH:
                break;
            case ITEM1_CAT_TOOL:
                if (ITEM_IS_UMBRELLA2(shop_master->sell_item)) {
                    break;
                }
                // fall through
            default:
                return;
            }
            aNSC_set_sell_camera(shop_master, play);
        }
    }
}

static void aNSC_talk_demo_proc(ACTOR *actorx) {
    if (mDemo_Check(mDemo_TYPE_SPEAK, actorx) == TRUE || mDemo_Check(mDemo_TYPE_TALK, actorx) == TRUE) {
        CLIP(npc_clip)->talk_demo_proc(actorx);
    }
}

static void aNSC_set_make_basement_info() {
    int arrange_idx = mHS_get_arrange_idx(Common_Get(player_no));
    mHm_hs_c *home = &Save_Get(homes)[arrange_idx];
    home->size_info.basement_ordered = TRUE;
    aNSC_set_rehouse_order_date(home);
}

static mPr_catalog_order_c *aNSC_getP_free_ftr_order() {
    int i;
    mPr_catalog_order_c *order = Now_Private->catalog_orders;

    for (i = 0; i < 5; i++) {
        if (order->item == EMPTY_NO) {
            return order;
        }
        order += sizeof(u8);
    }
    return NULL;
}

static void aNSC_set_ftr_order(NPC_SHOP_MASTER_ACTOR *actor) {
    mPr_catalog_order_c *order = aNSC_getP_free_ftr_order();
    order->item = actor->order_item;
    order->shop_level = Save_Get(shop).shop_info.shop_level;

}

static void aNSC_set_last_day_str() {
    u8 buff[8];
    u16 day = (u16)lbRTC_GetDaysByMonth(Common_Get(time).rtc_time.year, Common_Get(time).rtc_time.month);

    mString_Load_DayStringFromRom(buff, day);
    mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR5, buff, 4);
}

static void aNSC_set_pw_name_str(NPC_SHOP_MASTER_ACTOR* shop_master) {
    mMsg_Window_c *msg_win = mMsg_Get_base_window_p();
    mMsg_Set_free_str(msg_win, mMsg_FREE_STR6, shop_master->_9C8, aNSC_9C8_LEN);
    mMsg_Set_free_str(msg_win, mMsg_FREE_STR7, shop_master->_9D0, aNSC_9D0_LEN);
}

static void aNSC_set_value_str(int p1, int p2) {
    u8 value_str[16];

    mFont_UnintToString(value_str, sizeof(value_str), p1, 0x10, TRUE, FALSE, TRUE);
    mMsg_Set_free_str(mMsg_Get_base_window_p(), p2, value_str, 0x10);
}

static void aNSC_set_item_name_str(mActor_name_t itm, u32 p2) {
    u8 buff[16];
    u32 art;
    mMsg_Window_c* msg_win;

    mIN_copy_name_str(buff, itm);
    art = mIN_get_item_article(itm);
    mMsg_Set_item_str_art(mMsg_Get_base_window_p(), p2, buff, 0x10, art);
}

static void aNSC_set_item_str(NPC_SHOP_MASTER_ACTOR* shop_master, mActor_name_t itm) {
    u32 value;
    u16 item = shop_master->sell_item;
    aNSC_set_item_name_str(item, 0);
    value = mSP_ItemNo2ItemPrice(item);
    aNSC_set_value_str(value, 4);
    shop_master->value = value;
}

static void aNSC_set_pw_password_str(NPC_SHOP_MASTER_ACTOR* shop_master) {
    mMsg_Window_c* msg_win = mMsg_Get_base_window_p();
    u8 *msg = shop_master->password_str;
    mMsg_Set_item_str(msg_win, mMsg_ITEM_STR3, msg, 14);
    mMsg_Set_item_str(msg_win, mMsg_ITEM_STR4, &msg[14], 14);
}

static void aNSC_set_pw_info_str(NPC_SHOP_MASTER_ACTOR* shop_master) {
    mMsg_Window_c* msg_win = mMsg_Get_base_window_p();
    mMsg_Set_free_str(msg_win, mMsg_FREE_STR6, shop_master->password.str1, 8);
    mMsg_Set_free_str(msg_win, mMsg_FREE_STR7, shop_master->password.str0, 8);
    aNSC_set_item_name_str(shop_master->password.item, 2);
}

static int aNSC_pc_check_password_famicom(mMpswd_password_c *pswd) {
    int res = aNSC_PSW_RES_0;
    if (pswd->hit_rate_index == 1) {
        if(mMpswd_check_name(pswd) == TRUE) {
            res = aNSC_PSW_GOOD_FAMICON;
        } else {
            res = aNSC_PSW_BAD;
        }
    }
    return res;
}

static int aNSC_pc_check_password_npc(mMpswd_password_c *pswd) {
    int res = aNSC_PSW_RES_0;
    if (pswd->hit_rate_index == 1 && mMpswd_check_npc_code(pswd) == TRUE) {
        if (mMpswd_check_name(pswd) == TRUE) {
            res = aNSC_PSW_GOOD_NPC;
        } else {
            res = aNSC_PSW_BAD;
        }
    }
    return res;
}

static int aNSC_pc_check_password_card_e(mMpswd_password_c *pswd) {
    return aNSC_PSW_CARDE;
}

static int aNSC_pc_check_password_magazine(mMpswd_password_c *pswd) {
    static f32 hit_rate_magazine[5] = {80.0, 60.0, 30.0, 0.0, 100.0};
    int res = 0;

    if (pswd->hit_rate_index <= 4) {
        if (RANDOM_F(100.0) < hit_rate_magazine[pswd->hit_rate_index]) {
            res = aNSC_PSW_GOOD_MAGAZINE_1;
        } else {
            res = aNSC_PSW_GOOD_MAGAZINE_2;
        }
    }
    return res;
}

static int aNSC_pc_check_password_card_e_mini(mMpswd_password_c *pswd) {
    int res = aNSC_PSW_RES_0;
    if (pswd->hit_rate_index == 1) {
        res = aNSC_PSW_GOOD_CARDEM;
    }
    return res;
}

static int aNSC_pc_check_password_user(mMpswd_password_c *pswd) {
    int res = aNSC_PSW_RES_0;
    if (pswd->hit_rate_index == 1) {
        if (mMpswd_check_name(pswd) == TRUE) {
            res = aNSC_PSW_GOOD_USER;
        } else {
            res = aNSC_PSW_BAD;
        }
    }
    return res;
}

static int aNSC_pc_check_password(NPC_SHOP_MASTER_ACTOR *shop_master) {
    static int (*pc_check_password_proc[6])(mMpswd_password_c *) = {
        aNSC_pc_check_password_famicom,
        aNSC_pc_check_password_npc,
        aNSC_pc_check_password_card_e,
        aNSC_pc_check_password_magazine,
        aNSC_pc_check_password_card_e_mini,
        aNSC_pc_check_password_user
    };

    int res = aNSC_PSW_RES_0; 
    u8 buff[24];

    if (shop_master->password_str[mMpswd_PASSWORD_STR_LEN - 1] == ' ') {
        res = aNSC_PSW_RES_9;
    } else {
        if (mMpswd_decode_code(buff, shop_master->password_str) == TRUE) {
            mMpswd_password_c *password = &shop_master->password;

            mMpswd_password(buff, password);
            if (mMpswd_password_zuru_check(password) == FALSE && mMpswd_check_present(password) == TRUE) {
                aNSC_set_pw_password_str(shop_master);
                aNSC_set_pw_info_str(shop_master);
                res = pc_check_password_proc[password->type](password);
            }
        }
    }

    return res;
}

static int aNSC_check_possession_item_make_password(NPC_SHOP_MASTER_ACTOR *shop_master) {
    mActor_name_t *item;
    int flags;
    int i;
    int res;

    flags = 0;
    res = 0;

    item = Now_Private->inventory.pockets;
    for (i = 0; i < 15; i++) {
        if ((*item != EMPTY_NO) && (mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, i) == 0) && mMpswd_check_present_user(*item) == TRUE) {
            res = 1;
            flags |= (1 << i);
        }
        item += 1;
    }
    shop_master->password_flags = flags; 

    return res;
}

static void aNSC_set_buy_sum_str(mActor_name_t item, u32 p2) {
    static int tanni_string_num[10] = {0x566, 0x575, 0x584, 0x593, 0x5a2, 0x5b1, 0x5c0, 0x5cf, 0x5de, 0x5ed};
    mActor_name_t type;
    u8 buff[16];
    u32 str_no;

    aNSC_set_item_name_str(item, mMsg_ITEM_STR2);
    aNSC_set_value_str(p2, 7);

    switch (ITEM_NAME_GET_TYPE(item)) {
    case NAME_TYPE_ITEM1:
        str_no = p2 + tanni_string_num[aNSC_item_tanni_type[ITEM_NAME_GET_CAT((mActor_name_t)item)][ITEM_NAME_GET_INDEX(item)]];
        str_no -= 1;
        break;
    case NAME_TYPE_FTR0:
    case NAME_TYPE_FTR1:
        str_no = p2 + 0x565;
        break;
    default:
        str_no = p2 + 0x565;
        break;
    }

    mString_Load_StringFromRom(buff, 0x10, str_no);
    mMsg_Set_free_str(mMsg_Get_base_window_p(), 8, buff, 0x10);
}

static int aNSC_decide_next_move_act(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *play) {
    int res;
    PLAYER_ACTOR *player;
    if ((shop_master->npc_class.collision.pipe.collision_obj.collision_flags0 & 0x2) != 0) {
        return 0x3d;
    } else {
        player = get_player_actor_withoutCheck(play);
        if (player == NULL) {
            return shop_master->action;
        }
        if (aNSM_check_safe_zone(shop_master, player) == TRUE) {
            return 0x3d;
        } else {
            if (shop_master->npc_class.actor_class.player_distance_xz < aNSC_PLAYER_DISTANCE || shop_master->_9C0 == 0) {
                    return 0x3d;
            } else {
                f32 player_distance_xz = shop_master->npc_class.actor_class.player_distance_xz;
                if (shop_master->_9A4 != shop_master->_9A2) {
                    if (shop_master->action != 0x3f && shop_master->action != 0x41) {
                        shop_master->_9A3 = aNSM_get_next_zone(shop_master->_9A4, shop_master->_9A2);
                    }
                    if (player_distance_xz < (f32)90.0) {
                        return 0x3f;
                    } else {
                        return 0x41;
                    }
                } else {
                    shop_master->_9A3 = shop_master->_9A4;
                    if (player_distance_xz < (f32)90.0) {
                        return 0x3e;
                    } else {
                        return 0x40;
                    }
                }
            }
        }
    }
}

static void aNSC_set_zone_data(NPC_SHOP_MASTER_ACTOR *shop_master, ACTOR *a2) {
    ACTOR *actorx = (ACTOR *)shop_master;
    xyz_t pos1;
    xyz_t pos2;

    pos1 = shop_master->npc_class.actor_class.world.position;
    shop_master->_9A2 = aNSM_get_zone(&pos1);

    if (a2 != NULL) {
        pos2 = a2->world.position;
        shop_master->_9A4 = aNSM_get_zone(&pos2);
    }
}

static void aNSC_set_player_angl(NPC_SHOP_MASTER_ACTOR *shop_master) {
    shop_master->player_angle = shop_master->npc_class.actor_class.player_angle_y; 
}

static int aNSC_check_buy_item_single(NPC_SHOP_MASTER_ACTOR *nook, Submenu *menu) {

    mActor_name_t item = menu->item_p[0].item;
    Submenu_Item_c *item_p = &menu->item_p[0];

    u32 res = aNSC_CHECK_BUY_NORMAL_SUB;
    u32 quant = 0;

    if (NowPrivate_GetItemCond(item_p->slot_no) & mPr_ITEM_COND_QUEST) {
        res = aNSC_CHECK_BUY_REFUSE_QUEST_COND;
    }
    else if (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_ITEM1 && ITEM_NAME_GET_CAT(item) == ITEM1_CAT_KABU) {
        if (item == ITM_KABU_SPOILED) {
            res = aNSC_CHECK_BUY_TAKE_OFF_HANDS;
            quant = 1;
        }
        else if (Common_Get(time).rtc_time.weekday == lbRTC_SUNDAY) {
            res = aNSC_CHECK_BUY_NO_SUNDAY_TURNIPS;
        }
        else {
            res = aNSC_check_buy_item_sub(&quant, item);
        }
    } 
    else {
        if (mSP_ItemNo2ItemPrice(item) / SELL_BUY_RATIO == 0) {
            res = aNSC_CHECK_BUY_TAKE_OFF_HANDS;
            quant = 1;
        }
        else if (ITEM_IS_PAPER(item)) {
            res = aNSC_check_buy_paper(&quant, item);
        } else {
            res = aNSC_check_buy_item_sub(&quant, item);
        }
    }
    
    nook->counter = quant;
    return res;
}

static int aNSC_check_buy_item_plural(NPC_SHOP_MASTER_ACTOR *nook, Submenu *menu) {
    Submenu_Item_c *selected = menu->item_p;

    u32 num_selected = menu->selected_item_num;
    int res = aNSC_CHECK_BUY_NORMAL;
    nook->counter = num_selected;

    while (num_selected) {
        if (ITEM_NAME_GET_TYPE(selected->item) == NAME_TYPE_ITEM1) {
            if (ITEM_NAME_GET_CAT(selected->item) == ITEM1_CAT_KABU) {
                res = aNSC_CHECK_BUY_TURNIPS;
                break;
            }
        }
        if (mSP_ItemNo2ItemPrice(selected->item) / SELL_BUY_RATIO != 0) {
            res = aNSC_CHECK_BUY_TURNIPS;
            break;
        }

        selected += 1;
        num_selected -= 1;
    }

    return res;
}

static int aNSC_check_buy_item(NPC_SHOP_MASTER_ACTOR *sm, Submenu *menu) {
    if (menu->selected_item_num == 1) {
        return aNSC_check_buy_item_single(sm, menu);
    } else {
        return aNSC_check_buy_item_plural(sm, menu);
    }
}

static int aNSC_check_item_with_ticket(mActor_name_t item) {
    int type;
    int cat;
    int res;

    type = ITEM_NAME_GET_TYPE(item);
    res = 0;

    switch (ITEM_NAME_GET_TYPE(item)) {
    case NAME_TYPE_FTR0:
    case NAME_TYPE_FTR1:
        return TRUE;
    case NAME_TYPE_ITEM1:
        switch (ITEM_NAME_GET_CAT(item)) {
        case ITEM1_CAT_CLOTH:
        case ITEM1_CAT_WALL:
        case ITEM1_CAT_CARPET:
            res = TRUE;
            break;
        case ITEM1_CAT_TOOL:
            if (item >= ITM_UMBRELLA_START && item <= ITM_UMBRELLA_END - 1) {
                res = TRUE;
            }
        }
    }

    return res;
}

static void aNSC_setup_ticket_remain() {
    s32 tickets = Now_Private->inventory.lotto_ticket_mail_storage;

    if (Common_Get(time).rtc_time.month != Now_Private->inventory.lotto_ticket_expiry_month) {
        tickets = 0;
        Now_Private->inventory.lotto_ticket_expiry_month = Common_Get(time).rtc_time.month;
    }
    tickets++;
    if (tickets > aNSC_MAX_TICKETS) {
        tickets = aNSC_MAX_TICKETS;
    }
    Now_Private->inventory.lotto_ticket_mail_storage = tickets;
}

static int aNSC_check_same_month_ticket(mActor_name_t ticket) {
    int res = FALSE;

    mActor_name_t new_ticket = ticket;
    int idx = mPlib_Get_space_putin_item_forTICKET(&new_ticket);
    if (idx != -1) {
        mPr_SetPossessionItem(Now_Private, idx, new_ticket, mPr_ITEM_COND_NORMAL);
        res = TRUE;
    }
    return res;
}

static int aNSC_check_money_overflow(u32 p1, u32 counter) {
    u32 bags;
    int empty_spaces;
    int res = FALSE;

    empty_spaces = mPr_GetPossessionItemSum(Now_Private, EMPTY_NO);
    bags = 0;
    for (; p1 >= mPr_WALLET_MAX; p1 -= 30000) {
        bags += 1;
    }

    if (bags <= empty_spaces + counter) {
        res = TRUE;
    }
    return res;
}

static int aNSC_check_buy_item_sub(u32 *quant, mActor_name_t itm_name) {
    int i;
    mActor_name_t *item = Now_Private->inventory.pockets;
    int res = aNSC_CHECK_BUY_NORMAL_SUB;

    for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
        if (*item == itm_name) {
            if (!((NowPrivate_GetItemCond(i) & mPr_ITEM_COND_QUEST) || (NowPrivate_GetItemCond(i) & mPr_ITEM_COND_PRESENT))) {
                *quant += 1;
            }
        }
        item += 1;
    }
    if (*quant > 1) {
        aNSC_set_buy_sum_str(itm_name, *quant);
        res = aNSC_CHECK_BUY_OFFER_BUY_ALL;
    }
    return res;
}

static int aNSC_check_buy_paper(u32 *quant, mActor_name_t itm_name) {
    int i;
    int res = 0; 
    mActor_name_t *pockets = Now_Private->inventory.pockets;
    int paper_type = PAPER2TYPE(itm_name - ITM_PAPER_START);

    for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
        mActor_name_t item = *pockets;
        if (ITEM_IS_PAPER(item)) {
            if (PAPER2TYPE(item - ITM_PAPER_START) == paper_type) {
                if (!((NowPrivate_GetItemCond(i) & mPr_ITEM_COND_QUEST) || (NowPrivate_GetItemCond(i) & mPr_ITEM_COND_PRESENT))) {
                    *quant += PAPER2STACK(item - ITM_PAPER_START) + 1;
                }
            }
        }
        pockets++;
    }
    if (*quant > 1) {
        aNSC_set_buy_sum_str(itm_name, *quant);
        res = aNSC_CHECK_BUY_OFFER_BUY_ALL;
    }
    return res;
}

static int aNSC_get_msg_no(int msg_no) {
    int res = 0x82a;
    if (msg_no < 0) {
        return res;
    }
    else if (msg_no < 100) {
        res = msg_no + 0x107b;
    }
    else if (msg_no < 200) {
        res = msg_no + 0x2baf;
    }
    else if (msg_no < 300) {
        res = msg_no + 0x2de6;
    } else {
        res = msg_no + 0x3cd2;
    }
    return res;
}

static void aNSC_Set_continue_msg_num(mMsg_Window_c* msg_p, NPC_SHOP_MASTER_ACTOR* shop_master, int msg_no) {
    mMsg_Set_continue_msg_num(msg_p, msg_no);
    shop_master->_9C4 = msg_no;
}

static void aNSC_ChangeMsgData(mMsg_Window_c* msg_p, NPC_SHOP_MASTER_ACTOR* shop_master, int p3) {
    mMsg_ChangeMsgData(msg_p, p3);
    shop_master->_9C4 = p3;
}

static void aNSC_set_player_angle()  {
    static f32 fc_1, fc_2, fc_3;
    PLAYER_ACTOR *player_actor;
    s_xyz pos_8;
    xyz_t stack_1;

    player_actor = GET_PLAYER_ACTOR_NOW();

    stack_1.x = ((f32)((int)player_actor->forward_ut_pos.x / mFI_UT_WORLDSIZE_X) + 0.5f) * mFI_UT_WORLDSIZE_X_F;
    stack_1.z = ((f32)((int)player_actor->forward_ut_pos.z / mFI_UT_WORLDSIZE_Z) + 0.5f) * mFI_UT_WORLDSIZE_Z_F;

    pos_8.y = atans_table(stack_1.z - player_actor->actor_class.world.position.z, stack_1.x - player_actor->actor_class.world.position.x);

    GET_PLAYER_ACTOR_NOW()->Set_force_position_angle_proc(gamePT, &player_actor->actor_class.world.position, &pos_8, mPlayer_FORCE_POSITION_ANGLE_ROTY);
}

static void aNSC_set_talk_info_show_item(NPC_SHOP_MASTER_ACTOR *actor, mActor_name_t item) {
    aNSC_set_item_str(actor, item);
    aNSC_set_player_angle();
    mDemo_Set_camera(1);
    mDemo_Set_msg_num(aNSC_get_msg_no(aNSC_MSG_SHOW_ITEM));
}

static void aNSC_set_talk_info_show_cloth(NPC_SHOP_MASTER_ACTOR *actor, mActor_name_t cloth) {
    PositionAngle pa;
    aNSC_set_item_str(actor, cloth);
    aNSC_set_player_angle();
    mDemo_Set_camera(0xd);
    mDemo_Set_msg_num(aNSC_get_msg_no(aNSC_MSG_SHOW_CLOTH));
}

static void aNSC_set_talk_info_sell_item(NPC_SHOP_MASTER_ACTOR *actor, mActor_name_t p2) {
    mActor_name_t item = actor->sell_item;
    u8 camera_type;
    int msg_no = aNSC_MSG_BUY_CANCEL;

    aNSC_set_item_str(actor, p2);
    aNSC_set_player_angle();

    if (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_FTR0 || ITEM_NAME_GET_TYPE(item) == NAME_TYPE_FTR1 || (ITM_UMBRELLA_START <= item && item <= ITM_UMBRELLA_END - 1)) {
        camera_type = mDemo_TYPE_EVENTMSG;
    } else {
        camera_type = mDemo_TYPE_SCROLL;
    }

    if (item >= ITM_RED_PAINT && item <= ITM_BROWN_PAINT) {
        if (mLd_PlayerManKindCheck() == FALSE) {
            msg_no = aNSC_MSG_SELL_PAINT;
        } else {
            msg_no = aNSC_MSG_SELL_PAINT_FOREIGN;
        }
    } else {
        if (item >= ITM_PAPER_START && item <= ITM_PAPER_END - 1) {
            msg_no = aNSC_MSG_SELL_PAPER;
        }
    }


    mDemo_Set_camera(camera_type);
    mDemo_Set_msg_num(aNSC_get_msg_no(msg_no));
}

static void aNSC_set_talk_info_message_ctrl() {
    mDemo_Set_msg_num(aNSC_get_msg_no(aNSC_MSG_INTERACT_START));
}

static void aNSC_set_talk_info_message_ctrl_aprilfool(ACTOR *actorx, GAME *game) {
    int msg_num = Common_Get(clip).aprilfool_control_clip->get_msg_num_proc(SP_NPC_SHOP_MASTER, 0);
    mDemo_Set_msg_num(msg_num);
}

static void aNSC_set_talk_info_message_ctrl_tokubai() {
    int msg_num = aNSC_get_msg_no(aNSC_MSG_GREET_DEPART);
    mDemo_Set_msg_num(msg_num);
}

static int aNSC_message_ctrl(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    PLAYER_ACTOR *player = GET_PLAYER_ACTOR_GAME(game);
    int res = 0;

    if (player != NULL && CLIP(shop_design_clip) != NULL) {
        if (player->item_in_front == EXIT_DOOR1) {
            aNSC_setupAction(shop_master, game, aNSC_ACTION_EXIT);
            res = TRUE;
        } else {
            ACTOR * actorx = (ACTOR *)shop_master;
            int action = 0;
            if (mDemo_Check(mDemo_TYPE_SPEAK, actorx) == TRUE) {
                if (mDemo_Check_ListenAble() == FALSE) {
                    aNSC_calc_talk_start_tim(shop_master); 
                    if (shop_master->npc_class.actor_class.player_distance_xz < 80.0f || shop_master->_9C0 == FALSE) {
                        if (chase_angle(&shop_master->npc_class.actor_class.shape_info.rotation.y, shop_master->player_angle, 0x800) == TRUE) {
                            mActor_name_t item = shop_master->sell_item;
                            if (item != EMPTY_NO) {
                                action = 0x1e;
                                if (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_ITEM1) {
                                    switch (ITEM_NAME_GET_CAT(item)) {
                                    case ITEM1_CAT_CLOTH:
                                    case ITEM1_CAT_CARPET:
                                    case ITEM1_CAT_WALL:
                                        action = 0x26;
                                        break;
                                    default:
                                        if (item >= ITM_RED_PAINT && item <= ITM_BROWN_PAINT) {
                                            if (mLd_PlayerManKindCheck() != FALSE) {
                                                action = 0xf;
                                            }
                                        }
                                        break;
                                    }
                                }
                                aNSC_setupAction(shop_master, game, action);
                            }
                            aNSC_Set_ListenAble(shop_master);
                            shop_master->_9C0 = -1;
                            res = TRUE;
                        }
                        actorx->world.angle.y = actorx->shape_info.rotation.y;
                    }
                }
            } else {
                if (mDemo_Check(mDemo_TYPE_TALK, (ACTOR *)shop_master) == TRUE) {
                    if (!mDemo_Check_ListenAble()) {
                        action = 0x1e;
                        if (chase_angle(&actorx->shape_info.rotation.y, shop_master->player_angle, 0x800) == TRUE) {
                            if (CLIP(aprilfool_control_clip) != NULL && CLIP(aprilfool_control_clip)->talk_chk_proc(SP_NPC_SHOP_MASTER) == FALSE) {
                                action = aNSC_ACTION_BUY_REFUSE;
                                CLIP(aprilfool_control_clip)->talk_set_proc(SP_NPC_SHOP_MASTER);
                            } else {
                                if (shop_master->_9B9 == TRUE) {
                                    action = aNSC_ACTION_BUY_REFUSE; 
                                } else {
                                    action = aNSC_ACTION_MONEY_OVERFLOW;
                                }
                            }
                            aNSC_setupAction(shop_master, game, action);
                            aNSC_Set_ListenAble(shop_master);
                            res = TRUE;
                        }
                        actorx->world.angle.y = actorx->shape_info.rotation.y;
                    }
                } else {
                    void *demo_proc;
                    shop_master->sell_item = EMPTY_NO;

                    if (player->a_btn_pressed == TRUE) {
                        int ut_x, ut_y;
                        u16 item;

                        xyz_t wpos = player->forward_ut_pos;
                        mFI_Wpos2UtNum(&ut_x, &ut_y, wpos);
                        item = CLIP(shop_design_clip)->unitNum2ItemNo_proc(ut_x, ut_y);
                        if (item != EMPTY_NO && item != RSV_NO) {
                            void *sell_proc = none_proc1;
                            shop_master->sell_item = item;
                            shop_master->ut_x = ut_x;
                            shop_master->ut_y = ut_y;

                            switch (ITEM_NAME_GET_TYPE(item)) {
                            case NAME_TYPE_FTR0:
                            case NAME_TYPE_FTR1:
                                sell_proc = aNSC_set_talk_info_sell_item;
                                break;
                            case NAME_TYPE_ITEM1:
                                switch (ITEM_NAME_GET_CAT(item)) {
                                case ITEM1_CAT_CARPET:
                                case ITEM1_CAT_WALL:
                                    sell_proc = aNSC_set_talk_info_show_item;
                                    break;
                                case ITEM1_CAT_CLOTH:
                                    sell_proc = aNSC_set_talk_info_show_cloth;
                                    break;
                                default:
                                    sell_proc = aNSC_set_talk_info_sell_item;
                                    break;
                                }
                                break;
                            }

                            mDemo_Request(mDemo_TYPE_SPEAK, actorx, sell_proc);
                            shop_master->_9C0 = -1;
                        }
                    }

                    if (CLIP(aprilfool_control_clip) != NULL && CLIP(aprilfool_control_clip)->talk_chk_proc(SP_NPC_SHOP_MASTER) == FALSE) {
                        demo_proc = aNSC_set_talk_info_message_ctrl_aprilfool; 
                    } else if (shop_master->_9B9 == TRUE) {
                        demo_proc = aNSC_set_talk_info_message_ctrl_tokubai;
                    } else {
                        demo_proc = aNSC_set_talk_info_message_ctrl;
                    }
                    mDemo_Request(mDemo_TYPE_TALK, actorx, demo_proc);
                }
            }
        }
    }

    return res;
}

static int aNSC_money_check(u32 amount) {
    return mSP_money_check(amount);
}

static void aNSC_get_sell_price(u32 amount) {
    mSP_get_sell_price(amount);
}

static mActor_name_t aNSC_exchange_itemNo[2] = { 0x2102, EMPTY_NO };

static int aNSC_buy_item_single(u32 *bells, mActor_name_t item, u32 p2) {
    int idx;
    Private_c *priv = Now_Private;
    int replace_with_bag;
    u32 bells_before;
    int res = 1;

    for (; p2 != 0; p2--) {
        bells_before = *bells;
        if (bells_before >= mPr_WALLET_MAX) {
            *bells -= 30000;
            replace_with_bag = 0;
            res = 0;
        } else {
            replace_with_bag = 1;
        }
        idx = mPr_GetPossessionItemIdxWithCond(priv, item, mPr_ITEM_COND_NORMAL);

        mPr_SetPossessionItem(Now_Private, idx, aNSC_exchange_itemNo[replace_with_bag], mPr_ITEM_COND_NORMAL);
    }

    while (*bells >= mPr_WALLET_MAX) {
        *bells -= 30000;
        mPr_SetFreePossessionItem(Now_Private, ITM_MONEY_30000, mPr_ITEM_COND_NORMAL);
    }

    return res;
}

static int aNSC_buy_paper(u32 *money, mActor_name_t itm, int quant) {
    struct private_s *priv = Now_Private;
    int paper_type = PAPER2TYPE(itm - ITM_PAPER_START);
    int stack_quant = 0;
    int place_in_wallet;

    int next = aNSC_BUY_OUTCOME_NORMAL;
    // TODO: BUG? doesn't this start with a stack quantity of -1?
    mActor_name_t current_item = paper_type + ITM_PAPER_START + (stack_quant - 1) * PAPER_UNIQUE_NUM;

    if (*money >= mPr_WALLET_MAX) {
        *money -= 30000;
        place_in_wallet = FALSE;
        next = aNSC_BUY_OUTCOME_BREAK_BAG;
    } else {
        place_in_wallet = TRUE;        
    }


    while (quant != 0) {
        u32 idx = mPr_GetPossessionItemIdxWithCond(priv, current_item, mPr_ITEM_COND_NORMAL);    
        if (idx != -1) {
            mPr_SetPossessionItem(Now_Private, idx, aNSC_exchange_itemNo[place_in_wallet], mPr_ITEM_COND_NORMAL);
            quant -= stack_quant;
            place_in_wallet = TRUE;
        } else {
            stack_quant += 1;
            if (stack_quant > 4) {
                break;
            }
            current_item = ITM_PAPER_START + paper_type + (stack_quant - 1) * PAPER_UNIQUE_NUM;
        }
    }

    return next;
}

static int aNSC_buy_item_only_one(u32 *bells, mActor_name_t itm, u8 *p3, int sell_value) {
    int next = aNSC_BUY_OUTCOME_NORMAL;
    Private_c* priv;
    int quant;
    int paper_type;
    int item;
    int idx;

    if (*bells >= mPr_WALLET_MAX) {
        *bells -= 30000;
        next = aNSC_BUY_OUTCOME_BREAK_BAG;
    }

    if (itm >= ITM_PAPER_START && itm <= ITM_PAPER_END - 1) {
        priv = Now_Private;
        paper_type = PAPER2TYPE(itm - ITM_PAPER_START);

        for (quant = 1; quant <= 4; quant++) {
            item = ITM_PAPER_START + paper_type + (quant - 1) * PAPER_UNIQUE_NUM;
            idx = mPr_GetPossessionItemIdx(priv, item);
            if (idx != -1 ) {
                if (quant == 1) {
                    mPr_SetPossessionItem(Now_Private, idx, aNSC_exchange_itemNo[next], mPr_ITEM_COND_NORMAL);
                } else if (next == FALSE) {
                    int empty_idx = mPr_GetPossessionItemIdx(priv, EMPTY_NO);
                    if (empty_idx != -1) {
                        item = ITM_PAPER_START + paper_type + (quant - 2) * PAPER_UNIQUE_NUM;
                        mPr_SetPossessionItem(Now_Private, idx, item, mPr_ITEM_COND_NORMAL);
                        mPr_SetPossessionItem(Now_Private, empty_idx, ITM_MONEY_30000, mPr_ITEM_COND_NORMAL);
                    } else {
                        next = 3;
                        *bells += 30000;
                        *bells -= sell_value;
                    }
                } else {
                    item = ITM_PAPER_START + paper_type + (quant - 2) * PAPER_UNIQUE_NUM;
                    mPr_SetPossessionItem(Now_Private, idx, item, mPr_ITEM_COND_NORMAL);
                }
                break;
            } 
        }
    } else {
        mPr_SetPossessionItem(Now_Private, p3[2], aNSC_exchange_itemNo[next], mPr_ITEM_COND_NORMAL);
    }

    while (*bells >= mPr_WALLET_MAX) {
        *bells -= 30000;
        mPr_SetFreePossessionItem(Now_Private, ITM_MONEY_30000, mPr_ITEM_COND_NORMAL);
    }

    return next;
}

static int aNSC_get_start_call_msg_no(ACTOR *actorx) {
    int no;
    if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_EVENT) {
        if (actorx->npc_id == SP_NPC_DEPART_MASTER) {
            no = aNSC_MSG_EVENT_DEPART;
        } else {
            no = aNSC_MSG_EVENT;
        }
    } else {
        no = aNSC_MSG_START_CALL_NORMAL;
    }
    return no;
}

static void aNSC_set_talk_info_start_wait(ACTOR *actorx) {
    static u32 rehouse_msg[4] = { aNSC_MSG_MEDIUM_BUILT, aNSC_MSG_LARGE_BUILT, aNSC_MSG_UPPER_BUILT, aNSC_MSG_STATUE_BUILT };
    static u32 rehouse_loan[4] = { aNSC_LOAN_MEDIUM, aNSC_LOAN_LARGE, aNSC_LOAN_UPPER, aNSC_LOAN_STATUE };
    u8 player_no = Common_Get(player_no);
    int idx = mHS_get_arrange_idx(player_no);
    Private_c *priv;
    struct home_size_info_s *size;
    int msg_no;
    NPC_SHOP_MASTER_ACTOR *shop_master = (NPC_SHOP_MASTER_ACTOR *)actorx;

    size = &Save_Get(homes)[idx].size_info;

    if (size->renew == TRUE) { 
        u32 next_loan;
        size->pad_1 = 0;
        if (size->basement_ordered == TRUE) {
            size->basement_ordered = FALSE;
            next_loan = aNSC_LOAN_BASEMENT;
            size->pad_1 = 1;
            msg_no = aNSC_MSG_BASEMENT_BUILT;
        } else {
            int i = size->size - 1;
            msg_no = rehouse_msg[i];
            next_loan = rehouse_loan[i];
        }

        Now_Private->inventory.loan = next_loan;
        size->renew = FALSE;
    } else {
        if (size->statue_ordered == TRUE && size->next_size == mHm_HOMESIZE_STATUE) {
            msg_no = aNSC_MSG_STATUE_BUILT;
            size->statue_ordered = FALSE;
        } else {
            if (Now_Private->inventory.loan == 0 && size->size == mHm_HOMESIZE_UPPER && size->size == size->next_size && size->statue_ordered == FALSE) {
                u8 statues_count = Save_Get(num_statues);
                mHm_hs_c *home_2;

                player_no = Common_Get(player_no);
                idx = mHS_get_arrange_idx(player_no);
                home_2 = Save_GetPointer(homes[idx]);

                size->statue_ordered = TRUE;
                
                size->statue_rank = statues_count;
                statues_count += 1;

                if (statues_count >= 4) {
                    statues_count = 3;
                }
                Save_Get(num_statues) = statues_count;
                aNSC_set_rehouse_order_date(home_2);
                msg_no = aNSC_MSG_REHOUSE_STATUE;
            } else {
                msg_no = aNSC_get_start_call_msg_no(actorx); 
            }
        }
    }
    mDemo_Set_msg_num(aNSC_get_msg_no(msg_no));
    shop_master->next_action = 1;
}

static void aNSC_set_talk_info_start_wait1() {
    int msg_no = 0;

    u8 player_no = Common_Get(player_no);
    int idx = mHS_get_arrange_idx(player_no);
    mHm_hs_c *home = &Save_Get(homes)[idx];

    switch (home->size_info.size) {
    case mHm_HOMESIZE_SMALL:
        msg_no = aNSC_MSG_REHOUSE_MEDIUM;
        break;
    case mHm_HOMESIZE_MEDIUM:
        if (home->flags.has_basement == FALSE) {
            msg_no = aNSC_MSG_REHOUSE_2_OFFER;
        } else {
            msg_no = aNSC_MSG_BASEMENT_PAID;
        }
        break;
    case mHm_HOMESIZE_LARGE:
        if (home->size_info.pad_1 == TRUE) {
            msg_no = aNSC_MSG_REHOUSE_UPPER;
            break;
        }
        if (home->flags.has_basement == FALSE) {
            msg_no = aNSC_MSG_REHOUSE_BASEMENT;
        } else {
            msg_no = aNSC_MSG_REHOUSE_LARGE;
        }
        break;
    }

    mDemo_Set_msg_num(aNSC_get_msg_no(msg_no));
}

static void aNSC_set_talk_info_start_wait2(ACTOR *actorx) {
    NPC_SHOP_MASTER_ACTOR *shop_master = (NPC_SHOP_MASTER_ACTOR *)actorx;
    int msg_no = aNSC_MSG_BALLOON;
    if (actorx->npc_id == SP_NPC_DEPART_MASTER) {
        msg_no = aNSC_MSG_BALLOON_DEPART;
    }
    mDemo_Set_msg_num(aNSC_get_msg_no(msg_no));
    shop_master->next_action = aNSC_ACTION_GIVE_BALLOON;
}

static void aNSC_set_talk_info_start_wait3(ACTOR *actorx) {
    NPC_SHOP_MASTER_ACTOR *shop_master = (NPC_SHOP_MASTER_ACTOR *)actorx;
    int msg_no = aNSC_get_start_call_msg_no(actorx);
    mDemo_Set_msg_num(aNSC_get_msg_no(msg_no));
    shop_master->next_action = TRUE;
}

static void aNSC_set_talk_info_start_wait4(ACTOR *actorx) {
    mDemo_Set_msg_num(aNSC_get_msg_no(-1));
}

static void aNSC_start_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    ACTOR *actorx = (ACTOR *)shop_master;
    int wait_type = aNSC_WAIT_TYPE_REHOUSE;
    int action;
    mDemo_REQUEST_PROC proc;

    if (mLd_PlayerManKindCheck() == FALSE) {
        if (mEv_CheckEvent(mEv_SAVED_HRATALK_PLR0 + Common_Get(player_no)) == TRUE) {
            wait_type = aNSC_WAIT_TYPE_HRATALK;
        } else if (aNSC_check_present_balloon() == TRUE) {
            wait_type = aNSC_WAIT_TYPE_BALLOON;
        } else {
            int idx = mHS_get_arrange_idx(Common_Get(player_no));
            mHm_rmsz_c *size = &Save_Get(homes)[idx].size_info;
            if (Now_Private->inventory.loan == 0 && size->renew == FALSE && size->size < 3 && size->size == size->next_size && size->basement_ordered == FALSE) {
                wait_type = aNSC_WAIT_TYPE_REHOUSE;
            }
        }
    } else if (aNSC_check_present_balloon() == TRUE) {
        wait_type = aNSC_WAIT_TYPE_BALLOON; 
    } else {
        wait_type = aNSC_WAIT_TYPE_3;
    }

    if (mDemo_Check(mDemo_TYPE_SPEAK, actorx) == TRUE && mDemo_Check_ListenAble() == FALSE) {
        switch (wait_type) {
        case aNSC_WAIT_TYPE_HRATALK:
            mEv_EventOFF(mEv_SAVED_HRATALK_PLR0 + Common_Get(player_no));
            action = 1;
            break;
        case aNSC_WAIT_TYPE_REHOUSE:
        case aNSC_WAIT_TYPE_BALLOON:
        case aNSC_WAIT_TYPE_3:
            action = shop_master->next_action;
            break;
        case aNSC_WAIT_TYPE_DONE_REHOUSE:
            {
                int idx = mHS_get_arrange_idx(Common_Get(player_no));
                mHm_hs_c *home = &Save_Get(homes)[idx];
                switch (home->size_info.size) {
                case mHm_HOMESIZE_MEDIUM:
                    if (home->flags.has_basement == FALSE) {
                        action = 0x6;
                    } else {
                        action = 0x4;
                    }
                    break;
                case mHm_HOMESIZE_LARGE:
                    if (home->flags.has_basement == FALSE) {
                        aNSC_set_make_basement_info();
                        action = 0x1;
                    } else {
                        action = 0x4;
                    }
                    break;
                default:
                    action = 0x4;
                    break;
                }
                break;
            }
        }
        aNSC_Set_ListenAble(shop_master);
        aNSC_setupAction(shop_master, game, action);
        return;
    }


    proc = (mDemo_REQUEST_PROC)none_proc1;
    switch (wait_type) {
    case aNSC_WAIT_TYPE_REHOUSE:
        proc = aNSC_set_talk_info_start_wait;
        break;
    case aNSC_WAIT_TYPE_DONE_REHOUSE:
        proc = aNSC_set_talk_info_start_wait1;
        break;
    case aNSC_WAIT_TYPE_BALLOON:
        proc = aNSC_set_talk_info_start_wait2;
        break;
    case aNSC_WAIT_TYPE_3:
        proc = aNSC_set_talk_info_start_wait3;
        break;
    case aNSC_WAIT_TYPE_HRATALK:
        proc = aNSC_set_talk_info_start_wait4;
        break;
    }
    mDemo_Request(0x8, actorx, proc);
}

static void aNSC_say_hello_approach(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    ACTOR *actorx = (ACTOR *)shop_master;
    f32 z = 260.0;
    if (actorx->world.position.z > z) {
        actorx->world.position.z = z;
        aNSC_setupAction(shop_master, game, 0x2);
    } else if (mDemo_Check(mDemo_TYPE_SPEAK, actorx) == FALSE && mDemo_Check(mDemo_TYPE_TALK, actorx) == FALSE) {
        aNSC_setupAction(shop_master, game, 0x2); 
    }
}

static void aNSC_say_hello_end_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    ACTOR *actorx = (ACTOR *)shop_master;
    if (mDemo_Check(mDemo_TYPE_SPEAK, actorx) == FALSE) {
        if (mDemo_Check(mDemo_TYPE_TALK, actorx) == FALSE) {
            shop_master->npc_class.talk_info.melody_inst = 0;
            aNSC_setupAction(shop_master, game, 0x3d);
        }
    }
}

static void aNSC_check_col_chg_or_make_basement(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    f32 z = 260.0;
    if (((ACTOR *)shop_master)->world.position.z > z) {
        ((ACTOR *)shop_master)->world.position.z = z;
        aNSC_set_stop_spd(shop_master);
        CLIP(npc_clip)->animation_init_proc((ACTOR *)shop_master, 0x5, 0x1);
    }
    if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) == TRUE) {
        int action = 0x4;
        switch (mChoice_Get_ChoseNum(mChoice_Get_base_window_p())) {
        case mChoice_CHOICE0:
            action = 0x4;
            break;
        case mChoice_CHOICE1:
            aNSC_set_make_basement_info();
            action = 0x2;
            break;
        }
        aNSC_setupAction(shop_master, game, action);
    }
}

static void aNSC_check_roof_col_order(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    f32 z = 260.0;
    int unk = mDemo_Get_OrderValue(mDemo_ORDER_NPC0, 9);
    if (((ACTOR *)shop_master)->world.position.z > z) {
        ((ACTOR *)shop_master)->world.position.z = z;
        aNSC_set_stop_spd(shop_master);
        CLIP(npc_clip)->animation_init_proc((ACTOR *)shop_master, 0x5, 0x1);
    } 
    if (unk) {
        if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) == TRUE) {
            mHm_hs_c *home = &Save_Get(homes)[mHS_get_arrange_idx(Common_Get(player_no))];
            int action;
            int choice = mChoice_Get_ChoseNum(mChoice_Get_base_window_p());
            switch (choice) {
            case 0:
            case 1:
            case 2:
                action = 0x2;
                home->size_info.next_size += 1;
                home->ordered_outlook_pal = choice;
                aNSC_set_rehouse_order_date(home);
                break;
            default:
                action = 0x5;
                break;
            }
            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 9, 0x0);
            aNSC_setupAction(shop_master, game, action);
        }
    }
}

static void aNSC_check_roof_col_order2(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) == TRUE) {
        mHm_hs_c *home = &Save_Get(homes)[mHS_get_arrange_idx(Common_Get(player_no))];
        int choice = mChoice_Get_ChoseNum(mChoice_Get_base_window_p());
        int unk = mDemo_Get_OrderValue(mDemo_ORDER_NPC0, 9);
        int action = 0;
        switch (choice) {
        case 0:
        case 1:
        case 2:
            action = 0x2;
            home->size_info.next_size += 1;
            home->ordered_outlook_pal = choice + unk * 3;
            aNSC_set_rehouse_order_date(home);
            break;
        default:
            action = 0x5;
        }
        mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 9, 0x0);
        aNSC_setupAction(shop_master, game, action);
    }
}

static void aNSC_present_balloon_start_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if ((int)mDemo_Get_OrderValue(0x4, 0x1) == 2) {
        aNSC_setupAction(shop_master, game, 0x8);
    }
}

static void aNSC_present_balloon_trans_move(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    ACTOR *actorx = (ACTOR *)shop_master;
    if (actorx->world.position.z > (f32)260.0) {
        actorx->world.position.z = (f32)260.0;
        aNSC_setupAction(shop_master, game, 0x9);
    }
}

static void aNSC_present_balloon_trans_takeout(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    ACTOR *actorx = (ACTOR *)shop_master;
    ACTOR *res;
    if (shop_master->npc_class.left_hand.item_actor_p == NULL) {
        res = CLIP(handOverItem_clip)->birth_proc(ITM_BALLOON_START, aHOI_REQUEST_PUTAWAY, aHOI_PRESENT, (ACTOR *)shop_master);
        if (res) {
            CLIP(handOverItem_clip)->chg_request_mode_proc((ACTOR *)shop_master, aHOI_REQUEST_TRANSFER);

            shop_master->npc_class.left_hand.item_actor_p = res;
        }
    }

    if (shop_master->npc_class.draw.main_animation_state == cKF_STATE_STOPPED) {
        if (CLIP(handOverItem_clip)->master_actor == (ACTOR *)shop_master) {
            CLIP(handOverItem_clip)->chg_request_mode_proc((ACTOR *)shop_master, 0x2); 
            aNSC_setupAction(shop_master, game, 0xa);
        }
    }
}

static void aNSC_present_balloon_trans_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (CLIP(handOverItem_clip)->master_actor != (ACTOR *)shop_master) {
        aNSC_setupAction(shop_master, game, 0xb);
    }
}

static void aNSC_present_balloon_end_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (CLIP(handOverItem_clip)->master_actor == NULL) {
        mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
        aNSC_setupAction(shop_master, game, 0x2);
    }
}

static void aNSC_set_talk_info_request_Q_start_wait() {
    mDemo_Set_msg_num(aNSC_get_msg_no(aNSC_MSG_INTERACT_START));
    mDemo_Set_talk_turn(0x0);
}

static void aNSC_request_Q_start_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    ACTOR *actorx = (ACTOR *)shop_master;
    if (mDemo_Check(mDemo_TYPE_TALK, actorx) == TRUE) {
        if (mDemo_Check_ListenAble() == FALSE) {
            aNSC_Set_ListenAble(shop_master);
            aNSC_setupAction(shop_master, game, 0xd);
        }
    } else {
        mDemo_Request(0x7, actorx, aNSC_set_talk_info_request_Q_start_wait);
    }
}

static void aNSC_request_Q_answer_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    static int msg_no[5] = {aNSC_MSG_OTHER, aNSC_MSG_SELL_START, aNSC_MSG_ORDER_FULL, aNSC_MSG_SHOW_CATALOGUE, aNSC_MSG_INTERACT_CANCEl};
    static int next_act_idx[5] = {0xe, 0x10, 0xd, 0x19, 0xf};
    int res = mDemo_Get_OrderValue(0x4, 0x9);
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    if (res != 0) {
        if (mMsg_Check_MainNormalContinue(msg_p) == TRUE) {
            int next;
            mDemo_Set_msg_num(aNSC_get_msg_no(aNSC_MSG_INTERACT_START));
            switch (mChoice_Get_ChoseNum(mChoice_Get_base_window_p())) {
            case mChoice_CHOICE0:
                next = 1;
                break;
            case mChoice_CHOICE1:
                if (aNSC_getP_free_ftr_order() == FALSE) {
                    next = 0x2;
                } else {
                    next = 0x3;
                }
                break;
            case mChoice_CHOICE2:
                next = 0x0;
                break;
            default:
                next = 0x4;
                break;
            }
            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
            aNSC_Set_continue_msg_num(msg_p, shop_master, aNSC_get_msg_no(msg_no[next]));
            aNSC_setupAction(shop_master, game, next_act_idx[next]);
        }
    }
}

static void aNSC_request_Q_answer_wait2(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    static int msg_no[9] = {aNSC_MSG_KABU_ON_SUNDAY, aNSC_MSG_KABU_INFO, aNSC_MSG_PSWD_INFO, aNSC_MSG_PSWD_NO_ITEM, aNSC_MSG_GIFT_OUT, aNSC_MSG_PSWD_SAY, aNSC_MSG_PSWD_INVENTORY_FULL, aNSC_MSG_PSWD_FOREIGN, aNSC_MSG_RETURN};
    static int next_act_idx[9] = {0xf, 0xf, 0x29, 0xd, 0xd, 0x34, 0xd, 0xd, 0xd};
    int res = mDemo_Get_OrderValue(0x4, 0x9);
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    if (res != 0) {
        if (mMsg_Check_MainNormalContinue(msg_p) == TRUE) {
            int temp;
            switch (mChoice_Get_ChoseNum(mChoice_Get_base_window_p())) {
            case 0x0:
                if (Common_Get(time).rtc_time.weekday == 0) {
                    temp = 0;
                } else {
                    aNSC_set_value_str(Kabu_get_price(), 0x1);
                    temp = 0x1;
                }
                break;
            case 0x1:
                if (aNSC_check_possession_item_make_password(shop_master) == TRUE) {
                    temp = 0x2;
                } else {
                    temp = 0x3;
                }
                break;
            case 0x2:
                if (mLd_PlayerManKindCheck() == FALSE) {
                    if (Common_Get(unk_nook_present_count) >= 3) {
                        temp = 0x4;
                    } else if (mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO) != -1) {
                        temp = 0x5;
                    } else {
                        temp = 0x6;
                    }
                } else {
                    temp = 0x7;
                }
                break;
            default:
                temp = 0x8;
            }

            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
            aNSC_Set_continue_msg_num(msg_p, shop_master, aNSC_get_msg_no(msg_no[temp]));
            aNSC_setupAction(shop_master, game, next_act_idx[temp]);
        }
    }
}

static void aNSC_request_Q_end_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    ACTOR *actorx = (ACTOR *)shop_master;
    if (mDemo_Check(mDemo_TYPE_SPEAK, actorx) == FALSE && mDemo_Check(mDemo_TYPE_TALK, actorx) == FALSE) {
        shop_master->sell_item = EMPTY_NO;
        aNSC_setupAction(shop_master, game, 0x3d);
    }
}

static void aNSC_answer_buy_item(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (mDemo_Get_OrderValue(0x4, 0x9)) {
        if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p())) {
            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
            aNSC_setupAction(shop_master, game, shop_master->action + 1);
        }
    }
}

static void aNSC_buy_menu_open_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (mMsg_Check_main_wait(mMsg_Get_base_window_p()) == TRUE) {
        aNSC_setupAction(shop_master, game, shop_master->action + 1);
    }
}

static void aNSC_buy_menu_close_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (game->submenu.open_flag == FALSE) {
        aNSC_setupAction(shop_master, game, shop_master->action + 1);
    }
}

static void aNSC_msg_win_open_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    static int msg_no_table[8] = {aNSC_MSG_SELL_OFFER, aNSC_MSG_SELL_CANCEL, aNSC_MSG_KABU_ON_SUNDAY, aNSC_MSG_JUNK_ACCEPT, aNSC_MSG_SELL_QUEST, aNSC_MSG_REHOUSE_MEDIUM, aNSC_MSG_BALLOON, aNSC_MSG_BUY_REFUSE};
    static int next_act_idx[8] = {0x15, 0x17, 0xf, 0xd, 0x18, aNSC_ACTION_TAKE_OFF_HANDS, 0x15, 0x15};
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    if (mMsg_Check_not_series_main_wait(msg_p) == TRUE) {
        int action;
        Submenu *submenu = &game->submenu;
        mActor_name_t item = submenu->item_p->item;
        int msg_no;
        if (item == EMPTY_NO) {
            action = aNSC_CHECK_BUY_NONE_SELECTED;
        } else {
           action = aNSC_check_buy_item(shop_master, submenu);
        }
        if (action == aNSC_CHECK_BUY_TAKE_OFF_HANDS) {
            msg_no = aNSC_MSG_TAKE_OFF_HANDS;
        } else {
            msg_no = aNSC_get_msg_no(msg_no_table[action]);
        }
        aNSC_Set_continue_msg_num(msg_p, shop_master, msg_no);
        mMsg_Set_ForceNext(msg_p);
        aNSC_setupAction(shop_master, game, next_act_idx[action]);
    }
}

static void aNSC_buy_sum_check(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (mDemo_Get_OrderValue(0x4, 0x9)) {
        int res = -1;
        switch (mChoice_Get_ChoseNum(mChoice_Get_base_window_p())) {
        case mChoice_CHOICE0:
            res = 0;
            break;
        case mChoice_CHOICE1:
            res = 1;
            shop_master->counter = 1;
            break;
        }
        if (res != -1) {
            mActor_name_t *item = &game->submenu.item_p->item;
            if (ITEM_IS_PAPER(*item)) {
                *item = PAPEROFQUANT(*item - ITM_PAPER_START, 1);
            }
            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
            aNSC_Set_continue_msg_num(mMsg_Get_base_window_p(), shop_master, aNSC_get_msg_no(0x1b));
            aNSC_setupAction(shop_master, game, 0x15);
        }
    }
}

static void aNSC_buy_check(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    static int msg_no[4] = {aNSC_MSG_BREAK_BAG, aNSC_MSG_SELL_NORMAL, aNSC_MSG_SELL_CANCEL, aNSC_MSG_MONEY_OVERFLOW};
    static int next_act_idx[4] = {aNSC_ACTION_BREAK_BAG, aNSC_ACTION_ANYTHING_ELSE, aNSC_ACTION_ANYTHING_ELSE, 0xd};
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    int n1 = aNSC_get_msg_no(aNSC_MSG_SELL_OFFER);
    int n2 = aNSC_get_msg_no(aNSC_MSG_BUY_MANY_OFFER);
    int n3 = aNSC_get_msg_no(aNSC_MSG_BUY_REFUSE);
    int num = mMsg_Get_msg_num(msg_p);
    int next;
    if (num == n1 || num == n2 || num == n3) {
        if (mMsg_Check_MainNormalContinue(msg_p)) {
            next = -1;
            switch (mChoice_Get_ChoseNum(mChoice_Get_base_window_p())) {
            case mChoice_CHOICE0:
                {
                    u32 bells = Now_Private->inventory.wallet;
                    u32 counter = shop_master->counter;
                    Submenu_Item_c *submenu_item = game->submenu.item_p;
                    bells += shop_master->_9A8;
                    next = 1;
                    if (!aNSC_check_money_overflow(bells, counter)) {
                        next = aNSC_BUY_OUTCOME_MONEY_OVERFLOW;
                    } else {
                        mActor_name_t item = Now_Private->inventory.pockets[submenu_item->slot_no];
                        mSP_PlusSales(shop_master->_9A8 / 2);
                        if (counter == 1) {
                            next = aNSC_buy_item_only_one(&bells, item, (u8 *)submenu_item, shop_master->_9A8);
                        } else if (game->submenu.selected_item_num > 1) {
                            int change;
                            for (; counter > 0; counter--) {
                                if (bells >= mPr_WALLET_MAX) {
                                    bells -= 30000;
                                    change = 0;
                                    next = aNSC_BUY_OUTCOME_BREAK_BAG;
                                } else {
                                    change = 1;
                                }
                                mPr_SetPossessionItem(Now_Private, submenu_item->slot_no, aNSC_exchange_itemNo[change], mPr_ITEM_COND_NORMAL);
                                submenu_item++;
                            }

                            while (bells >= mPr_WALLET_MAX) {
                                bells -= 30000;
                                mPr_SetFreePossessionItem(Now_Private, ITM_MONEY_30000, mPr_ITEM_COND_NORMAL);
                            }
                        } else if (ITEM_IS_PAPER(item)) {
                            next = aNSC_buy_paper(&bells, item, counter);
                        } else {
                            next = aNSC_buy_item_single(&bells, item, counter);
                        }
                        Now_Private->inventory.wallet = bells;
                    }
                }
                break;
            case mChoice_CHOICE1:
                next = aNSC_BUY_OUTCOME_CANCEL;
            }
            if (next != -1) {
                int no;
                mMsg_Set_ForceNext(msg_p);
                aNSC_Set_continue_msg_num(msg_p, shop_master, aNSC_get_msg_no(msg_no[next]));
                aNSC_setupAction(shop_master, game, next_act_idx[next]);
            }
        }
    }
}

static void aNSC_buy_after_service(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    int val = mDemo_Get_OrderValue(0x4, 0x9);
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    if (val != 0) {
        if (mMsg_Check_MainNormalContinue(msg_p) == TRUE) {
            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
            aNSC_setupAction(shop_master, game, aNSC_ACTION_ANYTHING_ELSE);
        }
    }
}

static void aNSC_buy_continue_check(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    static int next_act_idx[2] = {aNSC_ACTION_BUY_TRANSACT, aNSC_ACTION_BUY_REFUSE};
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    int n1 = aNSC_get_msg_no(aNSC_MSG_SELL_NORMAL);
    int n2 = aNSC_get_msg_no(aNSC_MSG_SELL_CANCEL);
    int num = mMsg_Get_msg_num(msg_p);
    if (num == n1 || num == n2) {
        if (mMsg_Check_MainNormalContinue(msg_p)) {
            int action = -1;
            switch (mChoice_Get_ChoseNum(mChoice_Get_base_window_p())) {
            case mChoice_CHOICE0:
                action = 0;
                break;
            case mChoice_CHOICE1:
                aNSC_Set_continue_msg_num(msg_p, shop_master, aNSC_get_msg_no(aNSC_MSG_BUY_CANCEL));
                action = 1;
                break;
            }
            if (action != -1) {
                aNSC_setupAction(shop_master, game, next_act_idx[action]); 
            }
        }
    }
}

static void aNSC_receive_check(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    int no = mMsg_Get_msg_num(msg_p);
    if (shop_master->_9C4 == no) {
        if (mMsg_Check_MainNormalContinue(msg_p)) {
            Submenu_Item_c *submenu_item = game->submenu.item_p;
            switch (mChoice_Get_ChoseNum(mChoice_Get_base_window_p())) {
            case 0:
                mPr_SetPossessionItem(Now_Private, submenu_item->slot_no, EMPTY_NO, mPr_ITEM_COND_NORMAL);
            }
            aNSC_setupAction(shop_master, game, 0xd);
        }
    }
}

static void aNSC_msg_win_open_wait2(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    static int msg_no[3] = {aNSC_MSG_ORDER_CANCEL, aNSC_MSG_ORDER_UNAVAILABLE, aNSC_MSG_ORDER_OFFER};
    static int next_act_idx[3] = {0xd, 0xd, 0x1d};
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    if (mMsg_Check_not_series_main_wait(msg_p) == TRUE) {
        Submenu_Item_c *submenu_item = game->submenu.item_p;
        mActor_name_t item = submenu_item->item;

        int action;
        if (item == EMPTY_NO) {
            action = 0;
        } else {
            action = (submenu_item->slot_no != 0 ? 2 : 1);
            aNSC_set_item_name_str(item, 0x1);
            shop_master->order_item = item;
        }
        aNSC_ChangeMsgData(msg_p, shop_master, aNSC_get_msg_no(msg_no[action]));
        mMsg_Set_ForceNext(msg_p);
        aNSC_setupAction(shop_master, game, next_act_idx[action]);
    }
}

static void aNSC_order_check(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    if (mMsg_Get_msg_num(msg_p) == shop_master->_9C4) {
        if (mMsg_Check_MainNormalContinue(msg_p)) {
            int msg_no = aNSC_MSG_WAIT;
            u32 price;
            switch (mChoice_Get_ChoseNum(mChoice_Get_base_window_p())) {
            case mChoice_CHOICE0:
                price = mSP_ItemNo2ItemPrice(shop_master->order_item);
                if (aNSC_money_check(price) == FALSE) {
                    msg_no = aNSC_MSG_INSUFFICIENT_FUNDS;
                } else {
                    msg_no = aNSC_MSG_ORDER_CONFIRM;
                    aNSC_set_ftr_order(shop_master);
                    aNSC_get_sell_price(price);
                    mSP_PlusSales(price);
                }
                break;
            case mChoice_CHOICE1:
                msg_no = aNSC_MSG_ORDER_CANCEL;
                break;
            }
            if (msg_no != aNSC_MSG_WAIT) {
                mMsg_Set_ForceNext(msg_p);
                aNSC_Set_continue_msg_num(msg_p, shop_master, aNSC_get_msg_no(msg_no));
                aNSC_setupAction(shop_master, game, 0xd);
            }
        }
    }
}

static void aNSC_sell_check_before(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (mDemo_Get_OrderValue(0x4, 0x9)) {
        mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
        aNSC_setupAction(shop_master, game, 0x1f);
    }
}

static void aNSC_sell_check(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p())) {
        int action = -1;
        switch (mChoice_Get_ChoseNum(mChoice_Get_base_window_p())) {
        case mChoice_CHOICE0:
            action = 0x20;
            break;
        case mChoice_CHOICE1:
            action = 0x21;
            break;
        }
        if (action != -1) {
            if (shop_master->_9B8 == 1 && ITEM_NAME_GET_CAT(shop_master->sell_item) == ITEM1_CAT_CLOTH) {
                shop_master->next_action = action; 
                action = 0x27;
                shop_master->_9BE = shop_master->_9BC;
            }
            aNSC_setupAction(shop_master, game, action);
        }
    }
}

static void aNSC_sell_answer0(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    static int next_act_idx[11] = {0x22, 0x23, 0x23, 0x25, 0x24, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22};
    static int msg_no[11] = {aNSC_MSG_BUY_NORMAL, aNSC_MSG_GIVE_TICKET, aNSC_MSG_MAIL_TICKET, aNSC_MSG_INSUFFICIENT_FUNDS, aNSC_MSG_POCKETS_FULL, aNSC_MSG_SELL_NET, aNSC_MSG_SELL_AXE, aNSC_MSG_SELL_SHOVEL, aNSC_MSG_SELL_ROD, ansc_msg_sell_paint_confirm, aNSC_MSG_SELL_SIGN};
    if (mDemo_Get_OrderValue(0x4, 0x9)) {
        mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
        if (mMsg_Check_MainNormal(msg_p) == TRUE) {
            int action = 0;
            if (aNSC_money_check(shop_master->value) == FALSE) {
                action = 0x3;
            } else {
                mActor_name_t item = shop_master->sell_item;
                if (item >= ITM_RED_PAINT && item <= ITM_BROWN_PAINT) {
                    mHm_hs_c *home = &Save_Get(homes)[mHS_get_arrange_idx(Common_Get(player_no))];
                    home->next_outlook_pal = (item >= ITM_RED_PAINT && item <= ITM_BROWN_PAINT) ? (item - ITM_RED_PAINT) : 0;
                    action = 0x9;
                    Now_Private->state_flags |= mPr_FLAG_UPDATE_OUTLOOK_PENDING;
                } else {
                    int idx = mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO);
                    if (idx == -1) {
                        action = 0x4;
                    } else {
                        mPr_SetPossessionItem(Now_Private, idx, item, mPr_ITEM_COND_NORMAL);
                        if (aNSC_check_item_with_ticket(item) == TRUE) {
                            mActor_name_t ticket = (Common_Get(time).rtc_time.month - 1) * 8 + ITM_TICKET_START;
                            if (aNSC_check_same_month_ticket(ticket) == TRUE) {
                                action = 0x1;
                            } else {
                                aNSC_setup_ticket_remain();
                                action = 0x2;
                            }
                        } else if (item == ITM_SIGNBOARD) {
                                action = 0xa;
                        } else {
                            switch (item) {
                            case ITM_NET:
                                action = 0x5;
                                break;
                            case ITM_AXE:
                                action = 0x6;
                                break;
                            case ITM_SHOVEL:
                                action = 0x7;
                                break;
                            case ITM_ROD:
                                action = 0x8;
                                break;
                            }
                        }
                    }
                }
            }
            aNSC_Set_continue_msg_num(msg_p, shop_master, aNSC_get_msg_no(msg_no[action]));
            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
            aNSC_setupAction(shop_master, game, next_act_idx[action]);
        }
    }
}

static void aNSC_sell_item_with_ticket(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    int val = mDemo_Get_OrderValue(0x4, 0x9);
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    if (val) {
        if (mMsg_Check_MainNormalContinue(msg_p)) {
            aNSC_set_last_day_str();
            aNSC_Set_continue_msg_num(msg_p, shop_master, aNSC_get_msg_no((int)((f32)3.0 * fqrand()) + aNSC_MSG_TICKET_1));
            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);       
            aNSC_setupAction(shop_master, game, 0xf);
        }
    }
}

static void aNSC_show_item_check(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    if (mMsg_Check_MainNormalContinue(msg_p)) {
        mActor_name_t item = shop_master->sell_item;
        int action = 0x1e;
        int msg_no = aNSC_MSG_WAIT;
        switch (mChoice_Get_ChoseNum(mChoice_Get_base_window_p())) {
        case mChoice_CHOICE0:
            switch (ITEM_NAME_GET_CAT(item)) {
            case ITEM1_CAT_WALL:
                CLIP(shop_indoor_clip)->change_wall_proc(item);
                msg_no = aNSC_MSG_SHOW_CARPET_OFFER;
                aNSC_request_show_camera(game, 0);
                break;
            case ITEM1_CAT_CARPET:
                CLIP(shop_indoor_clip)->change_carpet_proc(item);
                msg_no = aNSC_MSG_SHOW_CARPET_OFFER;
                aNSC_request_show_camera(game, 0x1);
                break;
            default:
                CLIP(shop_manekin_clip)->change2naked_manekin_proc(shop_master->ut_x, shop_master->ut_y);
                action = 0x27;
                msg_no = aNSC_MSG_CONFIRM_CLOTH;
                shop_master->next_action = 0x1e;
                shop_master->_9BC = Now_Private->cloth.item;
                shop_master->_9BE = shop_master->sell_item;
                break;
            }
            shop_master->_9B8 = TRUE;
            break;
        case mChoice_CHOICE1:
            switch (ITEM_NAME_GET_CAT(item)) {
            case ITEM1_CAT_CARPET:
            case ITEM1_CAT_WALL:
                msg_no = aNSC_MSG_SHOW_CARPET_DECLINE;
                break;
            default:
                msg_no = aNSC_MSG_CANCEL_CLOTH;
                break;
            }
            break;
        case mChoice_CHOICE2:
            action = 0x21;
            msg_no = aNSC_MSG_BUY_CANCEL;
            break;
        }

        if (msg_no != -1) {
            aNSC_Set_continue_msg_num(msg_p, shop_master, aNSC_get_msg_no(msg_no));
            mMsg_Set_ForceNext(msg_p);
            aNSC_setupAction(shop_master, game, action); 
        }
    }
}

static void aNSC_chg_cloth_start_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (mPlib_get_player_actor_main_index((GAME *)game) == mPlayer_INDEX_CHANGE_CLOTH) {
        aNSC_setupAction(shop_master, game, 0x28);
    } else {
        mActor_name_t item = shop_master->_9BE;
        if (item != RSV_CLOTH) {
            mPlib_request_main_change_cloth_forNPC_type1((GAME *)game, item, ITEM_IS_CLOTH(item) ? item - ITM_CLOTH_START : 0, TRUE);
        } else {
            mPlib_request_main_change_cloth_forNPC_type1((GAME *)game, 1 - 0x1e1, Now_Private->cloth.idx, TRUE);
        }
    }
}

static void aNSC_chg_cloth_end_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (mPlib_get_player_actor_main_index((GAME *)game) != mPlayer_INDEX_CHANGE_CLOTH) {
        mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
        aNSC_setupAction(shop_master, game, shop_master->next_action);
    }
}

static void aNSC_pw_entry_send_addr_start_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (mDemo_Get_OrderValue(0x4, 0x9)) {
        if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) == TRUE) {
            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
            aNSC_setupAction(shop_master, game, 0x2a);
        }
    }
}

static void aNSC_pw_msg_win_open_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    static int msg_no[2] = {aNSC_MSG_PSWD_SAME_NAME, aNSC_MSG_PSWD_CONFIRM};
    static int next_act_idx[2] = {0x29, 0x2d};
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    if (mMsg_Check_not_series_main_wait(msg_p) == TRUE) {
        int action = 0;
        if (mLd_CheckCmpLandName(shop_master->_9C8, mLd_GetLandName()) == FALSE) {
            action = 1;
        }
        aNSC_ChangeMsgData(msg_p, shop_master, aNSC_get_msg_no(msg_no[action]));
        mMsg_Set_ForceNext(msg_p);
        aNSC_setupAction(shop_master, game, next_act_idx[action]);
    }
}

static void aNSC_send_addr_check(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    static int next_act_idx[3] = {0x2e, 0x29, 0xd};
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    if (mMsg_Get_msg_num(msg_p) == aNSC_get_msg_no(aNSC_MSG_PSWD_CONFIRM)) {
        if (mMsg_Check_MainNormalContinue(msg_p)) {
            int choice = -1;
            switch (mChoice_Get_ChoseNum(mChoice_Get_base_window_p())) {
            case mChoice_CHOICE0:
                choice = 0;
                break;
            case mChoice_CHOICE1:
                choice = 1;
                break;
            case mChoice_CHOICE2:
                choice = 2;
                break;
            }
            if (choice != -1) {
                mMsg_Set_ForceNext(msg_p);
                aNSC_setupAction(shop_master, game, next_act_idx[choice]);
            }
        }
    }
}

static void aNSC_pw_sel_item_start_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (mDemo_Get_OrderValue(0x4, 0x9)) {
        if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) == TRUE) {
            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
            aNSC_setupAction(shop_master, game, 0x2f);
        }
    }
}

static void aNSC_pw_msg_win_open_wait2(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    static int msg_no[2] = {aNSC_MSG_PSWD_CANCEL, aNSC_MSG_PSWD_CHECK};
    static int next_act_idx[2] = {0x33, 0x32};
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    if (mMsg_Check_not_series_main_wait(msg_p) == TRUE) {
        int action = 0;
        mActor_name_t item = game->submenu.item_p->item;
        if (item != EMPTY_NO) {
            shop_master->_9F4 = item;
            aNSC_set_item_name_str(item, 0x2);
            action = 1;
        }
        aNSC_ChangeMsgData(msg_p, shop_master, aNSC_get_msg_no(msg_no[action]));
        mMsg_Set_ForceNext(msg_p);
        aNSC_setupAction(shop_master, game, next_act_idx[action]);
    }
}

static void aNSC_pw_send_check(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    static int next_act_idx[3] = {0xf, 0x29, 0xd};
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    if (mMsg_Get_msg_num(msg_p) == aNSC_get_msg_no(aNSC_MSG_PSWD_CHECK)) {
        if (mMsg_Check_MainNormalContinue(msg_p)) {
            int choice = -1;
            switch (mChoice_Get_ChoseNum(mChoice_Get_base_window_p())) {
            case mChoice_CHOICE0:
                {
                    Submenu_Item_c *submenu_item = game->submenu.item_p;
                    mMpswd_make_password(shop_master->password_str, 0x4, 0x1, shop_master->_9D0, shop_master->_9C8, shop_master->_9F4, 0x0, 0x0);
                    aNSC_set_pw_password_str(shop_master);
                    mPr_SetPossessionItem(Now_Private, submenu_item->slot_no, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                    choice = 0;
                    break;
                }
            case mChoice_CHOICE1:
                choice = 1;
                break;
            case mChoice_CHOICE2:
                choice = 2;
                break;
            }
            if (choice != -1) {
                mMsg_Set_ForceNext(msg_p);
                aNSC_setupAction(shop_master, game, next_act_idx[choice]);
            }
        }
    }
}

static aNSC_pw_retry_sel_item_check(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    static int next_act_idx[2] = {0x2f, 0xd};
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    if (mMsg_Get_msg_num(msg_p) == aNSC_get_msg_no(aNSC_MSG_PSWD_CANCEL)) {
        if (mMsg_Check_MainNormalContinue(msg_p)) {
            int choice = -1;
            switch (mChoice_Get_ChoseNum(mChoice_Get_base_window_p())) {
            case mChoice_CHOICE0:
                choice = 0;
                break;
            case mChoice_CHOICE1:
                choice = 1;
                break;
            }
            if (choice != -1) {
                mMsg_Set_ForceNext(msg_p);
                aNSC_setupAction(shop_master, game, next_act_idx[choice]);
            }
        }
    }
}

static void aNSC_pc_input_pw_start_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (mDemo_Get_OrderValue(0x4, 0x9)) {
        if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) == TRUE) {
            mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
            aNSC_setupAction(shop_master, game, 0x35);
        }
    }
}

static void aNSC_pc_msg_win_open_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    static int msg_no[10] = {aNSC_MSG_PSWD_WRONG, aNSC_MSG_PSWD_GOOD_FAMICON, aNSC_MSG_PSWD_GOOD_NPC, aNSC_MSG_PSWD_GOOD_MAGAZINE_1, aNSC_MSG_PSWD_CARDE, aNSC_MSG_PSWD_GOOD_USER, aNSC_MSG_PSWD_GOOD_CARDEM, aNSC_MSG_PSWD_GOOD_MAGAZINE_2, aNSC_MSG_PSWD_BAD, aNSC_MSG_PSWD_DECLINE};
    static int next_act_idx[10] = {0x38, 0x39, 0x39, 0x39, 0xf, 0x39, 0x39, 0xf, 0x38, 0xd};
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    if (mMsg_Check_not_series_main_wait(msg_p) == TRUE) {
        int act = aNSC_pc_check_password(shop_master);
        aNSC_ChangeMsgData(msg_p, shop_master, aNSC_get_msg_no(msg_no[act]));
        mMsg_Set_ForceNext(msg_p);
        aNSC_setupAction(shop_master, game, next_act_idx[act]);
    }
}

static void aNSC_pc_retry_input_pw_check(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    static int next_act_idx[2] = {0x35, 0xd};
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    int n1 = aNSC_get_msg_no(aNSC_MSG_PSWD_WRONG);
    int n2 = aNSC_get_msg_no(aNSC_MSG_PSWD_BAD);
    int no = mMsg_Get_msg_num(msg_p);
    if (no == n1 || no == n2) {
        if (mMsg_Check_MainNormalContinue(msg_p)) {
            int choice = -1;
            switch (mChoice_Get_ChoseNum(mChoice_Get_base_window_p())) {
            case mChoice_CHOICE0:
                choice = 0;
                break;
            case mChoice_CHOICE1:
                choice = 1;
                aNSC_ChangeMsgData(msg_p, shop_master, aNSC_get_msg_no(aNSC_MSG_PSWD_DECLINE));
                break;
            }
            if (choice != -1) {
                mMsg_Set_ForceNext(msg_p);
                aNSC_setupAction(shop_master, game, next_act_idx[choice]);
            }
        }
    }
}

static void aNSC_pc_present_start_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if ((int)mDemo_Get_OrderValue(0x4, 0x01) == 0x2) {
        aNSC_setupAction(shop_master, game, 0x3a);
    }
}

static void aNSC_pc_present_trans_takeout(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (shop_master->npc_class.left_hand.item_actor_p == NULL) {
        ACTOR *actor = CLIP(handOverItem_clip)->birth_proc(shop_master->password.item, 0x7, 0x1, (ACTOR *)shop_master);
        if (actor) {
            CLIP(handOverItem_clip)->chg_request_mode_proc((ACTOR *)shop_master, 0x1);
            shop_master->npc_class.left_hand.item_actor_p = actor;
        }
    }
    if (shop_master->npc_class.draw.main_animation_state == 0x1) {
        if (CLIP(handOverItem_clip)->master_actor == (ACTOR *)shop_master) {
            CLIP(handOverItem_clip)->chg_request_mode_proc((ACTOR *)shop_master, 0x2);
            aNSC_setupAction(shop_master, game, 0x3b);
        }
    }
}

static void aNSC_pc_present_trans_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (CLIP(handOverItem_clip)->master_actor != (ACTOR *)shop_master) {
        aNSC_setupAction(shop_master, game, 0x3c); 
    }
}

static void aNSC_pc_present_end_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (CLIP(handOverItem_clip)->master_actor == NULL) {
        mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
        aNSC_setupAction(shop_master, game, 0xf);
    }
}

static void aNSC_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (aNSC_message_ctrl(shop_master, game) != TRUE) {
        int act = aNSC_decide_next_move_act(shop_master, game);
        if (act != shop_master->action) {
            aNSC_setupAction(shop_master, game, act); 
        } else {
            aNSM_search_player(shop_master, game);
        }
    }
}

static void aNSC_walk_pl_other_zone(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (aNSC_message_ctrl(shop_master, game) != TRUE) {
        int act = aNSC_decide_next_move_act(shop_master, game);
        if (act != shop_master->action) {
            aNSC_setupAction(shop_master, game, act);
        } else {
            aNSM_search_player2(shop_master, game);
        }
    }
}

static void aNSC_turn(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    ACTOR *actorx = (ACTOR *)shop_master;
    if (aNSC_message_ctrl(shop_master, game) != TRUE) {
        if (get_player_actor_withoutCheck(game)) {
            s16 player_angle = shop_master->player_angle;
            chase_angle(&actorx->shape_info.rotation.y, player_angle, 0x800);
            actorx->world.angle.y = actorx->shape_info.rotation.y;
            if (ABS(player_angle - actorx->shape_info.rotation.y) <= 0x4000) {
                aNSC_setupAction(shop_master, game, 0x3d);
            }
        }
    }
}

static void aNSC_set_talk_info_goodbye_wait() {
    mDemo_Set_msg_num(aNSC_get_msg_no(aNSC_MSG_SAY_GOODBYE));
    mDemo_Set_camera(TRUE);
}

static void aNSC_goodbye_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    ACTOR *actorx = (ACTOR *)shop_master;
    if (mDemo_Check(mDemo_TYPE_SPEAK, (ACTOR *)shop_master) == TRUE) {
        if (mDemo_Check_ListenAble() == FALSE) {
            s16 player_angle = shop_master->player_angle;
            if (chase_angle(&actorx->shape_info.rotation.y, player_angle, 0x800) == TRUE) {
                aNSC_Set_ListenAble(shop_master);
                aNSC_setupAction(shop_master, game, 0x44);
            }
        }
    } else {
        mDemo_Request(0x8, actorx, aNSC_set_talk_info_goodbye_wait);
    }
}

static void aNSC_say_goodbye(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();
    if (mMsg_Check_idling_now(msg_p) == TRUE) {
        mMsg_request_main_disappear_wait_type1(msg_p);
        aNSC_setupAction(shop_master, game, 0x45);
    }
}

static void aNSC_exit_wait(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    if (mMsg_Check_main_wait(mMsg_Get_base_window_p()) == TRUE) {
        goto_other_scene(game, &Common_Get(structure_exit_door_data), 0x1);
        if (game->fb_wipe_mode == 0) {
            mBGMPsComp_scene_mode(0xe);
            mBGMPsComp_volume_talk_end();
            mBGMPsComp_make_ps_wipe(0x195);
        }
    }
}

static void aNSC_say_hello_approach_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    aNSC_set_walk_spd(shop_master);
}

static void aNSC_say_hello_end_wait_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    shop_master->_9A3 = shop_master->_9A2;
    aNSC_set_stop_spd(shop_master);
}

static void aNSC_check_col_chg_or_make_basement_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    aNSC_set_walk_spd(shop_master);
}

static void aNSC_check_roof_col_order_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
    aNSC_set_walk_spd(shop_master);
}

static void aNSC_check_roof_col_order2_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
}

static void aNSC_present_balloon_start_wait_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    Common_Get(spnpc_first_talk_flags) |= (1 << aNPC_SPNPC_BIT_SHOP_MASTER);
}

static void aNSC_present_balloon_trans_move_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    int rand;
    mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x1, 0x0);
    aNSC_set_walk_spd(shop_master);
    rand = (int)((f32)8.0 * fqrand());
    mPr_SetFreePossessionItem(Now_Private, ITM_BALLOON_START + rand, mPr_ITEM_COND_PRESENT);
    mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    shop_master->npc_class.head.lock_flag = TRUE;
}

static void aNSC_present_balloon_trans_takeout_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    ACTOR *actorx = (ACTOR *)shop_master;
    shop_master->_9A3 = shop_master->_9A2;
    aNSC_set_stop_spd(shop_master);
    sAdo_OngenTrgStart(0x69, &actorx->world.position);
}

static void aNSC_present_balloon_end_wait_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    shop_master->npc_class.left_hand.item_actor_p = NULL;
    shop_master->npc_class.head.lock_flag = FALSE;
}

static void aNSC_request_Q_answer_wait_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
    aNSC_set_stop_spd(shop_master);
}

static void aNSC_request_Q_end_wait_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    aNSC_set_stop_spd(shop_master);
}

static void aNSC_answer_buy_item_init() {
    mDemo_Set_OrderValue(mDemo_TYPE_4, 9, 0);
}

static void aNSC_buy_menu_open_wait_init() {
    mMsg_request_main_disappear_wait_type1(mMsg_Get_base_window_p());
}

static void aNSC_buy_menu_close_wait_init(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    mSM_open_submenu(&game->submenu, 0x1, 0x5, 0x0); 
    shop_master->next_action = 0x13;
}

static void aNSC_msg_win_open_wait_init() {
    mMsg_request_main_appear_wait_type1(mMsg_Get_base_window_p());
}

static void aNSC_buy_sum_Check_init() {
    mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
}

static void aNSC_buy_check_init(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    static int kabu_sum[4] = {0xa, 0x32, 0x64, 0x0};
    int value = 0;
    Submenu_Item_c *submenu_item = game->submenu.item_p;
    int quant = game->submenu.selected_item_num;
    u32 counter = shop_master->counter;

    if (quant > 1) {
        counter = 1; 
    }

    while (quant) {
        mActor_name_t item = submenu_item->item;
        if (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_ITEM1 && ITEM_NAME_GET_CAT(item) == ITEM1_CAT_KABU) {
            value += Kabu_get_price() * kabu_sum[item - ITM_KABU_START] * counter;
        } else if (ITEM_IS_PAPER(item)) {
            value += (mSP_ItemNo2ItemPrice(item) / SELL_BUY_RATIO) * counter;
        } else {
            value += (mSP_ItemNo2ItemPrice(item) / SELL_BUY_RATIO) * counter;
        }
        submenu_item++;
        quant--;
    }
    shop_master->_9A8 = value;
    aNSC_set_value_str(value, 0x2);
}

static void aNSC_buy_after_service_init() {
   mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0); 
}

static void aNSC_order_select_menu_close_wait_init(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    mSM_open_submenu(&game->submenu, 0x14, 0x0, 0x0); 
    shop_master->next_action = 0x1c;
}

static void aNSC_order_check_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    aNSC_set_value_str(mSP_ItemNo2ItemPrice(shop_master->order_item), 0x3);
}

static void aNSC_sell_check_before_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
    aNSC_set_stop_spd(shop_master);
}

static void aNSC_sell_answer0_init(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
    if (shop_master->_9B8 == 0x1) {
        switch (ITEM_NAME_GET_CAT(shop_master->sell_item)) {
        case ITEM1_CAT_CARPET:
        case ITEM1_CAT_WALL:
            if (CLIP(shop_indoor_clip) != NULL) {
                CLIP(shop_indoor_clip)->change2default_proc();
                Camera2_Inter_set_reverse_mode(game);
                shop_master->_9B8 = EMPTY_NO;
            }
            break;
        case ITEM1_CAT_CLOTH:
            if (!aNSC_money_check(shop_master->value) || !mPr_GetPossessionItemSum(Now_Private, 0) || shop_master->action == 0x21) {
                CLIP(shop_manekin_clip)->naked2cloth_proc(shop_master->ut_x, shop_master->ut_y);
            }
            shop_master->_9B8 = EMPTY_NO;
            break;
        }
    }
}

static void aNSC_sell_answer1_init(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    aNSC_sell_answer0_init(shop_master, game);
    shop_master->sell_item = EMPTY_NO;
}

static void aNSC_sell_item_init(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    aNSC_get_sell_price(shop_master->value); 
    if (CLIP(shop_design_clip) != NULL) {
        CLIP(shop_design_clip)->reportGoodsSale_proc(shop_master->ut_x, shop_master->ut_y);
    }
    shop_master->sell_item = EMPTY_NO;
}

static void aNSC_sell_item_with_ticket_init(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
    aNSC_sell_item_init(shop_master, game);
}

static void aNSC_sell_refuse0_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    shop_master->sell_item = EMPTY_NO;
}


static void aNSC_show_item_check_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    aNSC_set_stop_spd(shop_master);
}

static void aNSC_chg_cloth_start_wait_init(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    mMsg_Set_LockContinue(mMsg_Get_base_window_p());
}

static void aNSC_pw_entry_send_addr_start_wait_init() {
    mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
}

static void aNSC_pw_make_menu_close_wait_init(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    mem_clear(shop_master->_9C8, 0x10, 0x20);
    mSM_open_submenu_new(&game->submenu, 0x1d, 0x0, 0x0, &shop_master->_9C8);
    shop_master->next_action = 0x2c;
}

static void aNSC_pw_send_addr_check_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    aNSC_set_pw_name_str(shop_master);
}

static void aNSSC_pw_sel_item_menu_close_wait_init(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    mSM_open_submenu(&game->submenu, 0x1, 0x10, shop_master->password_flags);
    shop_master->next_action = 0x2c;
}

static void aNSC_pc_input_pw_start_wait_init(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    mem_clear(shop_master->password_str, 0x1c, 0x20);
    mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x9, 0x0);
}

static void aNSC_pc_chk_menu_close_wait_init(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game) {
    mSM_open_submenu_new(&game->submenu, 0x1e, 0x0, 0x0, shop_master->password_str);
    shop_master->next_action = 0x37;
}

static void aNSC_pc_present_trans_takeout_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    ACTOR *actorx = (ACTOR *)shop_master;
    mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0x1, 0x0);
    sAdo_OngenTrgStart(0x69, &actorx->world.position);
    mPr_SetFreePossessionItem(Now_Private, shop_master->password.item, mPr_ITEM_COND_PRESENT);
    Common_Get(unk_nook_present_count)++;
    mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    shop_master->npc_class.head.lock_flag = TRUE;
}

static void aNSC_pc_present_end_wait_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    shop_master->npc_class.left_hand.item_actor_p = NULL;
    shop_master->npc_class.head.lock_flag = FALSE;
}

static void aNSC_wait_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    aNSC_set_stop_spd(shop_master);
}

static void aNSC_walk_pl_same_zone_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    aNSC_set_walk_spd(shop_master);
}

static void aNSC_run_pl_same_zone_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    aNSC_set_run_spd(shop_master);
}

static void aNSC_goodbye_wait_init(NPC_SHOP_MASTER_ACTOR *shop_master) {
    aNSC_set_stop_spd(shop_master);
}

static void aNSC_say_goodbye_init() {
    mMsg_Set_idling_req(mMsg_Get_base_window_p());
}

void aNSC_init_proc(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY* game, int p3) {
    static int (*init_proc[70])(NPC_SHOP_MASTER_ACTOR *, GAME_PLAY *) = {};
    init_proc[p3](shop_master, game);
}

void aNSC_setupAction(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY *game, int action) {
    static aNSC_PROC process[70] = {};
    shop_master->action = action; 
    shop_master->proc = process[action];
    aNSC_set_animation(shop_master, action);
    aNSC_init_proc(shop_master, game, action);
}
