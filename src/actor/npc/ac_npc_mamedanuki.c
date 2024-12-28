#include "ac_npc_mamedanuki.h"

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

#define aNSC_MAMEDANUKI

enum {
    aNMD_SALE_TYPE_NORMAL,
    aNMD_SALE_TYPE_FTR,
    aNMD_SALE_TYPE_CLOTH,
    aNMD_SALE_TYPE_CARPET,

    aNMD_SALE_TYPE_NUM
};

void aNMD_actor_ct(ACTOR* mamedanuki, GAME* game);
void aNMD_actor_dt(ACTOR* actorx, GAME* game);
void aNMD_actor_move(ACTOR* actorx, GAME* game);
void aNMD_actor_draw(ACTOR* actorx, GAME* game);
void aNMD_actor_init(ACTOR* actorx, GAME* game);
void aNMD_actor_save(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Mamedanuki_Profile = {
    mAc_PROFILE_NPC_MAMEDANUKI,    
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_MAMEDANUKI0,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_MAMEDANUKI_ACTOR),
    &aNMD_actor_ct,
    &aNMD_actor_dt,
    &aNMD_actor_init,
    mActor_NONE_PROC1,
    &aNMD_actor_save,
};
// clang-format on

// TODO: are these declared in every file? DnM+ says they're static yet they seemingly must be defined after their usage...
static void aNSC_setupAction(NPC_SHOP_COMMON_ACTOR *mamedanuki, GAME_PLAY* play, int p3);
static int aNSC_check_buy_item_sub(u32 *p1, mActor_name_t itm_name);
static int aNSC_check_buy_paper(u32 *p1, mActor_name_t itm_name);
static void aNSC_init_proc(NPC_SHOP_COMMON_ACTOR *mamedanuki, GAME_PLAY * play, int p3);
static void aNSC_BGcheck(ACTOR* actorx);
static void aNSC_set_zone_data(NPC_SHOP_COMMON_ACTOR* mamedanuki, ACTOR* actor);
static void aNSC_set_player_angl(NPC_SHOP_COMMON_ACTOR* mamedanuki);
static void aNSC_talk_demo_proc(ACTOR* actorx);
static void aNSC_sell_camera(NPC_SHOP_COMMON_ACTOR* mamedanuki, GAME_PLAY* play);

static ACTOR* aNMD_actor_p[2];
static int aNMD_selectIdx = 0;

void aNMD_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        &aNMD_actor_move,
        &aNMD_actor_draw,
        0,
        NULL,
        NULL,
        NULL,
        1,
    };
    // clang-format on

    static int start_act_idx[] = { 0, 1 }; // TODO: figure out how the hell to define this with enums
    // clang-format off
    static u8 special_sale_type[mSP_KIND_MAX] = {
        aNMD_SALE_TYPE_FTR,
        aNMD_SALE_TYPE_NORMAL,
        aNMD_SALE_TYPE_CLOTH,
        aNMD_SALE_TYPE_CARPET,
        aNMD_SALE_TYPE_CARPET,
    };
    // clang-format on

    NPC_MAMEDANUKI_ACTOR* mamedanuki = (NPC_MAMEDANUKI_ACTOR*)actorx;
    int action;
    CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);

    mamedanuki->npc_class.draw.main_animation.keyframe.morph_counter = 0.0f;
    mamedanuki->sell_item = EMPTY_NO;
    mamedanuki->npc_class.condition_info.hide_flg = FALSE;
    mamedanuki->talk_start_tim = -1;
    actorx->shape_info.draw_shadow = TRUE;
    actorx->shape_info.rotation.y = DEG2SHORT_ANGLE2(180.0f);
    actorx->world.angle.y = DEG2SHORT_ANGLE2(180.0f);
    mamedanuki->npc_class.collision.pipe.attribute.pipe.radius = 20;

    {
        u8 sale_type = aNMD_SALE_TYPE_NORMAL;

        if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_EVENT) {
            int sale_kind = mSP_WhatSpecialSale();

            if (sale_kind >= 0 && sale_kind <= mSP_KIND_WALLPAPER) {
                sale_type = special_sale_type[sale_kind];
            }
        }

        mamedanuki->sale_type = sale_type;
    }

    if (Common_Get(door_data).door_actor_name == RSV_NO) {
        mamedanuki->npc_class.talk_info.melody_inst = 0;
        action = 61;
    } else {
        action = start_act_idx[actorx->npc_id != SP_NPC_MAMEDANUKI0];
    }

    {
        int idx;

        if (actorx->npc_id == SP_NPC_MAMEDANUKI1) {
            idx = 1;
        } else {
            idx = 0;
        }

        aNMD_actor_p[idx] = actorx;
        aNSC_setupAction(mamedanuki, (GAME_PLAY*)game, action);
        aNMD_selectIdx = 0;
    }
}

void aNMD_actor_save(ACTOR* actorx, GAME* game) {
    (CLIP(npc_clip)->save_proc)(actorx, game);
}

void aNMD_actor_dt(ACTOR* actorx, GAME* game) {
    (CLIP(npc_clip)->dt_proc)(actorx, game);
}

void aNMD_actor_init(ACTOR* actorx, GAME* game) {
    (CLIP(npc_clip)->init_proc)(actorx, game);
}

void aNMD_actor_draw(ACTOR* actorx, GAME* game) {
    (CLIP(npc_clip)->draw_proc)(actorx, game);
}

static u8 aNMD_get_zone(NPC_MAMEDANUKI_ACTOR* mamedanuki, xyz_t wpos);
static u8 aNMD_get_next_zone(NPC_MAMEDANUKI_ACTOR* mamedanuki, u8 p1, u8 p2);
static void aNMD_search_player(NPC_MAMEDANUKI_ACTOR* mamedanuki, GAME_PLAY* play);
static void aNMD_search_player2(NPC_MAMEDANUKI_ACTOR* mamedanuki, GAME_PLAY* play);

#include "../src/actor/npc/ac_npc_mamedanuki_move.c_inc"
