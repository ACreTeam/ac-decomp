#include "ac_tamaire_npc1.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_soncho.h"
#include "libultra/libultra.h"

enum {
    aTMN1_THINK_BIRTH,
    aTMN1_THINK_KYORO_MAE,
    aTMN1_THINK_KYORO,
    aTMN1_THINK_WALK_TURN,
    aTMN1_THINK_WALK,
    aTMN1_THINK_HIROU_MAE,
    aTMN1_THINK_HIROU,
    aTMN1_THINK_HIROU_SP,
    aTMN1_THINK_HIROU_END,
    aTMN1_THINK_NAGERU,
    aTMN1_THINK_NAGERU_END,

    aTMN1_THINK_NUM
};

enum {
    aTMN1_THINK_PROC_NONE,
    aTMN1_THINK_PROC_TIMER_NEXT,
    aTMN1_THINK_PROC_BIRTH,
    aTMN1_THINK_PROC_TURN_NEXT,
    aTMN1_THINK_PROC_WALK,
    aTMN1_THINK_PROC_HIROU,
    aTMN1_THINK_PROC_HIROU_SP,
    aTMN1_THINK_PROC_ANIME_NEXT,
    aTMN1_THINK_PROC_NAGERU,
    aTMN1_THINK_PROC_NAGERU_END,

    aTMN1_THINK_PROC_NUM
};

enum {
    aTMN1_THINK_INIT_PROC_NONE,
    aTMN1_THINK_INIT_PROC_NORMAL_WAIT,
    aTMN1_THINK_INIT_PROC_MOVE,
    aTMN1_THINK_INIT_PROC_KYORO_MAE,
    aTMN1_THINK_INIT_PROC_KYORO,
    aTMN1_THINK_INIT_PROC_WALK_TURN,
    aTMN1_THINK_INIT_PROC_HIROU_MAE,
    aTMN1_THINK_INIT_PROC_HIROU,
    aTMN1_THINK_INIT_PROC_HIROU_SP,
    aTMN1_THINK_INIT_PROC_HIROU_END,
    aTMN1_THINK_INIT_PROC_NAGERU,
    aTMN1_THINK_INIT_PROC_NAGERU_END,

    aTMN1_THINK_INIT_PROC_NUM
};

static void aTMN1_actor_ct(ACTOR* actorx, GAME* game);
static void aTMN1_actor_dt(ACTOR* actorx, GAME* game);
static void aTMN1_actor_move(ACTOR* actorx, GAME* game);
static void aTMN1_actor_draw(ACTOR* actorx, GAME* game);
static void aTMN1_actor_save(ACTOR* actorx, GAME* game);
static void aTMN1_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Tamaire_Npc1_Profile = {
    mAc_PROFILE_TAMAIRE_NPC1,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_EV_TAMAIRE_1,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(TAMAIRE_NPC1_ACTOR),
    aTMN1_actor_ct,
    aTMN1_actor_dt,
    aTMN1_actor_init,
    mActor_NONE_PROC1,
    aTMN1_actor_save,
};
// clang-format on

static u16 aTMN1_flag = 0;

static void aTMN1_talk_request(ACTOR* actorx, GAME* game);
static int aTMN1_talk_init(ACTOR* actorx, GAME* game);
static int aTMN1_talk_end_chk(ACTOR* actorx, GAME* game);

static void aTMN1_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aTMN1_setup_think_proc(TAMAIRE_NPC1_ACTOR* actor, GAME_PLAY* play, u8 think_idx);

static void aTMN1_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aTMN1_actor_move,
        aTMN1_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aTMN1_talk_init,
        aTMN1_talk_end_chk,
        0,
    };
    TAMAIRE_NPC1_ACTOR* actor = (TAMAIRE_NPC1_ACTOR*)actorx;

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        static int base_msg_table[] = { 0x1E65, 0x1E71, 0x1E59, 0x1E7D, 0x1E89, 0x1E95 };

        actor->npc_class.schedule.schedule_proc = aTMN1_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);

        actor->npc_class.palActorIgnoreTimer = -1;
        actor->change_flag = FALSE;
        actor->right = 0;
        actor->left = 0;
        actor->base_msg = base_msg_table[mNpc_GetNpcLooks(actorx)];
        actor->npc_class.collision.check_kind = aNPC_BG_CHECK_TYPE_NONE;
        actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, 0.0f);
        actorx->position_speed.y = 0.0f;
        actorx->gravity = 0.0;
        actorx->max_velocity_y = 0.0f;
        aTMN1_flag = 0;
        actor->npc_class.collision.pipe.attribute.pipe.radius = 35;
        actorx->talk_distance = 73.0f;
    }
}

static void aTMN1_actor_save(ACTOR* actorx, GAME* game) {
    mNpc_RenewalSetNpc(actorx);
}

static void aTMN1_actor_dt(ACTOR* actorx, GAME* game) {
    TAMAIRE_NPC1_ACTOR* actor = (TAMAIRE_NPC1_ACTOR*)actorx;

    if (actor->npc_class.left_hand.item_actor_p != NULL) {
        Actor_delete(actor->npc_class.left_hand.item_actor_p);
    }

    NPC_CLIP->dt_proc(actorx, game);
}

static void aTMN1_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static int aTMN1_set_request_act(TAMAIRE_NPC1_ACTOR* actor, u8 prio, u8 idx, u8 type, u16 obj, s16 move_x, s16 move_z) {
    int res = FALSE;

    if (prio >= actor->npc_class.request.act_priority) {
        u16 args[6];
        
        bzero(args, sizeof(args));
        args[0] = obj;
        args[2] = move_x;
        args[3] = move_z;
        actor->npc_class.request.act_priority = prio;
        actor->npc_class.request.act_idx = idx;
        actor->npc_class.request.act_type = type;
        mem_copy((u8*)actor->npc_class.request.act_args, (u8*)args, sizeof(args));
        res = TRUE;
    }

    return res;
}

static void aTMN1_tama_process(ACTOR* actorx, GAME* game) {
    TAMAIRE_NPC1_ACTOR* actor = (TAMAIRE_NPC1_ACTOR*)actorx;
    static u8 table[] = { TOOL_TAMA2, TOOL_TAMA1, TOOL_TAMA4, TOOL_TAMA3 };

    if (actor->npc_class.right_hand.item_actor_p == NULL) {
        actor->npc_class.right_hand.item_actor_p = CLIP(tools_clip)->aTOL_birth_proc(table[(((mActor_name_t)(actorx->npc_id - SP_NPC_EV_TAMAIRE_1) >> 1) & 1 ^ 1)], aTOL_ACTION_TAKEOUT, actorx, game, -1, NULL);
    } else {
        TOOLS_ACTOR* tama = (TOOLS_ACTOR*)actor->npc_class.right_hand.item_actor_p;

        tama->work2 = actor->right;
    }

    if (actor->npc_class.left_hand.item_actor_p == NULL) {
        actor->npc_class.left_hand.item_actor_p = CLIP(tools_clip)->aTOL_birth_proc(table[2 + (((mActor_name_t)(actorx->npc_id - SP_NPC_EV_TAMAIRE_1) >> 1) & 1 ^ 1)], aTOL_ACTION_TAKEOUT, actorx, game, -1, NULL);
    } else {
        TOOLS_ACTOR* tama = (TOOLS_ACTOR*)actor->npc_class.left_hand.item_actor_p;

        tama->work2 = actor->left;
    }
}

static void aTMN1_actor_move(ACTOR* actorx, GAME* game) {
    aTMN1_tama_process(actorx, game);
    NPC_CLIP->move_proc(actorx, game);
}

#include "../src/actor/npc/ac_tamaire_npc1_talk.c_inc"
#include "../src/actor/npc/ac_tamaire_npc1_schedule.c_inc"

static void aTMN1_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
