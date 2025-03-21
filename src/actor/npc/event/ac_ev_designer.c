#include "ac_ev_designer.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_msg.h"
#include "libultra/libultra.h"

enum {
    aEDSN_THINK_TALK_START_WAIT,
    aEDSN_THINK_GAME_START_CALL_WAIT,
    aEDSN_THINK_GAME_START_CALL,
    aEDSN_THINK_GAME_END_WAIT,
    aEDSN_THINK_GAME_END_CALL,

    aEDSN_THINK_NUM
};

static void aEDSN_actor_ct(ACTOR* actorx, GAME* game);
static void aEDSN_actor_dt(ACTOR* actorx, GAME* game);
static void aEDSN_actor_move(ACTOR* actorx, GAME* game);
static void aEDSN_actor_draw(ACTOR* actorx, GAME* game);
static void aEDSN_actor_init(ACTOR* actorx, GAME* game);
static void aEDSN_actor_save(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Ev_Designer_Profile = {
    mAc_PROFILE_EV_DESIGNER,
    ACTOR_PART_NPC,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    SP_NPC_DESIGNER,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EV_DESIGNER_ACTOR),
    aEDSN_actor_ct,
    aEDSN_actor_dt,
    aEDSN_actor_init,
    mActor_NONE_PROC1,
    aEDSN_actor_save,
};
// clang-format on

static int aEDSN_talk_init(ACTOR* actorx, GAME* game);
static int aEDSN_talk_end_chk(ACTOR* actorx, GAME* game);

static void aEDSN_change_talk_proc(EV_DESIGNER_ACTOR* designer, int talk_idx);
static void aEDSN_setup_think_proc(EV_DESIGNER_ACTOR* designer, GAME_PLAY* play, u8 think_idx);
static void aEDSN_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);

static void aEDSN_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        // clang-format off
        aEDSN_actor_move,
        aEDSN_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aEDSN_talk_init,
        aEDSN_talk_end_chk,
        0,
        // clang-format on
    };

    if (CLIP(npc_clip)->birth_check_proc(actorx, game) == TRUE) {
        EV_DESIGNER_ACTOR* designer = (EV_DESIGNER_ACTOR*)actorx;

        designer->npc_class.schedule.schedule_proc = aEDSN_schedule_proc;
        CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);
        designer->melody_save = designer->npc_class.talk_info.melody_inst;
    }
}

static void aEDSN_actor_save(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->save_proc(actorx, game);
}

static void aEDSN_actor_dt(ACTOR* actorx, GAME* game) {
    EV_DESIGNER_ACTOR* designer = (EV_DESIGNER_ACTOR*)actorx;

    if (designer->camera_flag == TRUE) {
        mDemo_Set_camera(CAMERA2_PROCESS_NORMAL);
        Camera2_change_priority((GAME_PLAY*)game, 0);
        designer->camera_flag = FALSE;
    }

    CLIP(npc_clip)->dt_proc(actorx, game);
    mEv_actor_dying_message(mEv_EVENT_DESIGNER, actorx);
}

static void aEDSN_actor_init(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->init_proc(actorx, game);
}

static void aEDSN_actor_draw(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->draw_proc(actorx, game);
}

#include "../src/actor/npc/event/ac_ev_designer_move.c_inc"
#include "../src/actor/npc/event/ac_ev_designer_talk.c_inc"
#include "../src/actor/npc/event/ac_ev_designer_schedule.c_inc"
