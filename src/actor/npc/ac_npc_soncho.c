#include "ac_npc_soncho.h"
#include "ac_npc.h"
#include "libultra/libultra.h"
#include "m_actor.h"
#include "m_actor_type.h"
#include "m_common_data.h"
#include "m_name_table.h"
#include "m_npc.h"
#include "m_soncho.h"

enum {
    aNS_TALK_END_WAIT,

    aNS_TALK_NUM
};

enum {
    aNS_THINK_WAIT,
    aNS_THINK_NORMAL_WAIT,
    aNS_THINK_WANDER,

    aNS_THINK_NUM
};

static void aNS_actor_ct(ACTOR* actorx, GAME* game);
static void aNS_actor_dt(ACTOR* actorx, GAME* game);
static void aNS_actor_init(ACTOR* actorx, GAME* game);
static void aNS_actor_move(ACTOR* actorx, GAME* game);
static void aNS_actor_draw(ACTOR* actorx, GAME* game);
static void aNS_actor_save(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Soncho_Profile = {
    mAc_PROFILE_NPC_SONCHO,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_SONCHO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_SONCHO_ACTOR),
    aNS_actor_ct,
    aNS_actor_dt,
    aNS_actor_init,
    mActor_NONE_PROC1,
    aNS_actor_save,
};
// clang-format on

static int aNS_talk_init(ACTOR* actorx, GAME* game);
static int aNS_talk_end_chk(ACTOR* actorx, GAME* game);
static void aNS_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aNS_setup_think_proc(NPC_SONCHO_ACTOR* actor, GAME_PLAY* play, u8 think_idx);

static void aNS_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        aNS_actor_move,
        aNS_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aNS_talk_init,
        aNS_talk_end_chk,
        0,
    };
    // clang-format on
    
    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        NPC_SONCHO_ACTOR* actor = (NPC_SONCHO_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aNS_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        actor->npc_class.palActorIgnoreTimer = -1;
        actor->npc_class.draw.sub_anim_type = aNPC_SUB_ANIM_TUE; // cane
        actor->think_chg_flag = FALSE;
        actor->_9A3 = 0;
    }
}

static void aNS_actor_save(ACTOR* actorx, GAME* game) {
    mNpc_RenewalSetNpc(actorx);
}

static void aNS_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aNS_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static int aNS_set_request_act(NPC_SONCHO_ACTOR* actor, u8 prio, u8 idx, u8 type, u16 obj, s16 move_x, s16 move_z) {
    int ret = FALSE;

    if (prio >= actor->npc_class.request.act_priority) {
        u16 arg_data[aNPC_REQUEST_ARG_NUM];

        bzero(arg_data, sizeof(arg_data));
        arg_data[0] = obj;
        arg_data[2] = move_x;
        arg_data[3] = move_z;

        actor->npc_class.request.act_priority = prio;
        actor->npc_class.request.act_idx = idx;
        actor->npc_class.request.act_type = type;
        mem_copy((u8*)actor->npc_class.request.act_args, (u8*)arg_data, sizeof(arg_data));
        ret = TRUE;
    }

    return ret;
}

static void aNS_actor_move(ACTOR* actorx, GAME* game) {
    NPC_SONCHO_ACTOR* actor = (NPC_SONCHO_ACTOR*)actorx;

    actor->npc_class.movement.range_center_x = actorx->home.position.x;
    actor->npc_class.movement.range_center_z = actorx->home.position.z;
    actor->npc_class.movement.range_radius = 60.0f;
    actor->npc_class.movement.range_type = aNPC_MOVE_RANGE_TYPE_CIRCLE;
    NPC_CLIP->move_proc(actorx, game);
}

static void aNS_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_soncho_talk.c_inc"
#include "../src/actor/npc/ac_npc_soncho_schedule.c_inc"
