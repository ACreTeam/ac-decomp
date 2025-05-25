#include "ac_npc_post_man.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_house.h"
#include "ac_mailbox.h"
#include "m_melody.h"

enum {
    aPMAN_ACT_ENTER,
    aPMAN_ACT_BREAK,
    aPMAN_ACT_HOVER,
    aPMAN_ACT_LANDING,
    aPMAN_ACT_KYORO,
    aPMAN_ACT_TURN,
    aPMAN_ACT_WALK,
    aPMAN_ACT_DELIVERY_TURN,
    aPMAN_ACT_DELIVERY,
    aPMAN_ACT_TALK_TURN,
    aPMAN_ACT_TALK_END_WAIT,
    aPMAN_ACT_FLY_UP,
    aPMAN_ACT_EXIT,
    aPMAN_ACT_EXIT2,

    aPMAN_ACT_NUM
};

static void aPMAN_actor_ct(ACTOR* actorx, GAME* game);
static void aPMAN_actor_dt(ACTOR* actorx, GAME* game);
static void aPMAN_actor_save(ACTOR* actorx, GAME* game);
static void aPMAN_actor_init(ACTOR* actorx, GAME* game);
static void aPMAN_actor_move(ACTOR* actorx, GAME* game);
static void aPMAN_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Post_Man_Profile = {
    mAc_PROFILE_NPC_POST_MAN,
    ACTOR_PART_NPC,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    SP_NPC_POST_MAN,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_POST_MAN),
    aPMAN_actor_ct,
    aPMAN_actor_dt,
    aPMAN_actor_init,
    mActor_NONE_PROC1,
    aPMAN_actor_save,
};
// clang-format on

static void aPMAN_setupAction(NPC_POST_MAN* actor, GAME_PLAY* play, u8 action);
static s8 aPMAN_set_delivery_idx(NPC_POST_MAN* actor);
static s8 aPMAN_set_move_idx(NPC_POST_MAN* actor);

static void aPMAN_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        aPMAN_actor_move,
        aPMAN_actor_draw,
        aNPC_CT_SCHED_TYPE_NONE,
        NULL,
        NULL,
        NULL,
        1,
    };
    // clang-format on

    static f32 start_Ypos[] = { 160.0f, 0.0f };
    static u8 start_action[] = { aPMAN_ACT_ENTER, aPMAN_ACT_FLY_UP };
    
    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        NPC_POST_MAN* actor = (NPC_POST_MAN*)actorx;
        int type = actorx->actor_specific;
        
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        actor->npc_class.collision.check_kind = aNPC_BG_CHECK_TYPE_NORMAL;
        actor->npc_class.condition_info.hide_flg = FALSE;
        actor->npc_class.condition_info.demo_flg = aNPC_COND_DEMO_SKIP_TALK_CHECK | aNPC_COND_DEMO_SKIP_MOVE_CIRCLE_REV | aNPC_COND_DEMO_SKIP_MOVE_RANGE_CHECK;
        actor->now_idx = 6;
        actor->delivery_idx = aPMAN_set_delivery_idx(actor);
        actor->move_idx = aPMAN_set_move_idx(actor);
        actor->npc_class.palActorIgnoreTimer = -1;
        actorx->status_data.weight = MASSTYPE_HEAVY;
        actorx->world.position.y = start_Ypos[type] + mCoBG_GetBgY_AngleS_FromWpos(NULL, actorx->world.position, 0.0f);
        actorx->shape_info.draw_shadow = TRUE;
        if (type == aPMAN_BIRTH_PLAYER_HOUSE) {
            int bx;
            int bz;
            int pbx;
            int pbz;

            mFI_BlockKind2BkNum(&bx, &bz, mRF_BLOCKKIND_PLAYER);
            actorx->block_x = bx;
            actorx->block_z = bz;
            mFI_BlockKind2BkNum(&pbx, &pbz, mRF_BLOCKKIND_POSTOFFICE);
            actor->post_office_direct = bx < pbx ? 1 : 0;
        }

        aPMAN_setupAction(actor, (GAME_PLAY*)game, start_action[type]);
    }
}

static void aPMAN_actor_save(ACTOR* actorx, GAME* game) {
    mPO_delivery_all_address_proc();
    NPC_CLIP->save_proc(actorx, game);
}

static void aPMAN_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aPMAN_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_post_man_anime.c_inc"
#include "../src/actor/npc/ac_npc_post_man_move.c_inc"

static void aPMAN_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
