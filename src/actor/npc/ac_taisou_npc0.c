#include "ac_taisou_npc0.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_soncho.h"

// TODO - this file needs enums for action & talk states

static int aTS0_delete_flag = FALSE;
static int aTS0_regist_sum = 0;
static ACTOR* aTS0_failure_actor_p = NULL;

// @ 8056b300
static mActor_name_t aTS0_leader_no = SP_NPC_EV_TAISOU_4 + 1;


// @ 8056b304
static f32 aTS0_intro_startRatio[3] = {
    0.0f, 0.5f, 0.93581255f
};

// @ 8056b310
static f32 aTS0_taisou1_startRatio[5] = {
    0.0f, 0.25f, 0.5f, 0.75f, 0.96875f
};

// @ 8056b324
static f32 aTS0_taisou2_startRatio[3] = {
    0.0f, 0.5f, 0.96875f
};

// @ 8056b330
static f32 aTS0_taisou3_startRatio[5] = {
    0.0f, 0.25f, 0.5f, 0.75f, 0.96875f
};

// @ 8056b344
static f32 aTS0_taisou4_startRatio[3] = {
    0.0f, 0.5f, 0.96875f
};

// @ 8056b350
static f32 aTS0_taisou5_startRatio[5] = {
    0.0f, 0.25f, 0.5f, 0.75f, 0.96875f
};

// @ 8056b364
static f32 aTS0_taisou6_startRatio[5] = {
    0.0f, 0.5f, 1.0f, 1.5f, 0.96875f
};

// @ 8056b378
static f32 aTS0_taisou7_startRatio[5] = {
    0.0f, 0.25f, 0.5f, 0.75f, 0.96875f
};

// @ 8056b38c
static f32 aTS0_taisou8_startRatio[5] = {
    0.0f, 0.25f, 0.5f, 0.75f, 0.96875f
};

// @ 8056b3a0
static f32 aTS0_trailing_note_startRatio[2] = {
    0.0f, 0.96875f
};

// @ 8056b3a8
static f32* aTS0_startRatio[10] = {
    aTS0_intro_startRatio, aTS0_taisou1_startRatio, aTS0_taisou2_startRatio, aTS0_taisou3_startRatio, aTS0_taisou4_startRatio, aTS0_taisou5_startRatio, aTS0_taisou6_startRatio, aTS0_taisou7_startRatio,
    aTS0_taisou8_startRatio, aTS0_trailing_note_startRatio
};

// @ 8056b3d0
static f32 aTS0_endRatio[10] = {
    0.93581255f, 0.96875f, 0.96875f, 0.96875f, 0.96875f, 0.96875f, 0.96875f, 0.96875f,
    0.96875f, 0.96875f
};

// @ 8056b3f8
static f32 aTS0_morphRatio[10] = {
    0.030187488f, 0.03125f, 0.03125f, 0.03125f, 0.03125f, 0.03125f, 0.03125f, 0.03125f,
    0.03125f, 0.03125f
};

// @ 8056b420
static f32 aTS0_ratioLength[10][2] = {
    {0.5f, 0.5f},
    {0.25f, 0.25f},
    {0.5f, 0.5f},
    {0.25f, 0.25f},
    {0.5f, 0.5f},
    {0.25f, 0.25f},
    {0.5f, 0.5f},
    {0.25f, 0.25f},
    {0.25f, 0.25f},
    {1.0f, 1.0f},
};

static void aTS0_actor_ct(ACTOR* actorx, GAME* game);
static void aTS0_actor_dt(ACTOR* actorx, GAME* game);
static void aTS0_actor_move(ACTOR* actorx, GAME* game);
static void aTS0_actor_draw(ACTOR* actorx, GAME* game);
static void aTS0_actor_save(ACTOR* actorx, GAME* game);
static void aTS0_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Taisou_Npc0_Profile = {
    mAc_PROFILE_TAISOU_NPC0,
    ACTOR_PART_NPC,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(TAISOU_NPC0_ACTOR),
    aTS0_actor_ct,
    aTS0_actor_dt,
    aTS0_actor_init,
    mActor_NONE_PROC1,
    aTS0_actor_save,
};
// clang-format on

static void aTS0_talk_request(ACTOR* actorx, GAME* game);
static int aTS0_talk_init(ACTOR* actorx, GAME* game);
static int aTS0_talk_end_chk(ACTOR* actorx, GAME* game);

static void aTS0_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aTS0_setupAction(TAISOU_NPC0_ACTOR* actor, int action);

static void aTS0_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aTS0_actor_move,
        aTS0_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        aTS0_talk_request,
        aTS0_talk_init,
        aTS0_talk_end_chk,
        0,
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        TAISOU_NPC0_ACTOR* actor = (TAISOU_NPC0_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aTS0_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);

        if (aTS0_leader_no > actorx->npc_id) {
            aTS0_leader_no = actorx->npc_id;
        }

        aTS0_regist_sum++;
        actor->soncho_event = 0xFF;
    }
}

static void aTS0_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aTS0_actor_dt(ACTOR* actorx, GAME* game) {
    static int event_type[] = { mEv_EVENT_MORNING_AEROBICS, mEv_EVENT_SPORTS_FAIR_AEROBICS };

    NPC_CLIP->dt_proc(actorx, game);
    if (actorx->npc_id == aTS0_leader_no) {
        int idx;

        if (mEv_check_status(mEv_EVENT_MORNING_AEROBICS, mEv_STATUS_ACTIVE)) {
            idx = 0;
        } else {
            idx = 1;
        }

        actorx->world.position.x -= mFI_UT_WORLDSIZE_HALF_X_F;
        actorx->world.position.z -= mFI_UT_WORLDSIZE_HALF_Z_F;
        mEv_actor_dying_message(event_type[idx], actorx);
        aTS0_failure_actor_p = NULL;
        aTS0_leader_no = SP_NPC_EV_TAISOU_4 + 1;
    }

    aTS0_regist_sum--;

    if (aTS0_regist_sum <= 0) {
        aTS0_regist_sum = 0;
        aTS0_delete_flag = FALSE;
    }
}

static void aTS0_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aTS0_actor_move(ACTOR* actorx, GAME* game) {
    if (aTS0_delete_flag == TRUE) {
        Actor_delete(actorx);
    } else {
        NPC_CLIP->move_proc(actorx, game);
        if (actorx->npc_id == aTS0_leader_no && (actorx->state_bitfield & ACTOR_STATE_NO_CULL) != ACTOR_STATE_NO_CULL) {
            GAME_PLAY* play = (GAME_PLAY*)game;

            if (actorx->block_x != play->block_table.block_x || actorx->block_z != play->block_table.block_z) {
                aTS0_delete_flag = TRUE;
                Actor_delete(actorx);
            }
        }
    }
}

#include "../src/actor/npc/ac_taisou_npc0_anime.c_inc"
#include "../src/actor/npc/ac_taisou_npc0_talk.c_inc"

static void aTS0_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
