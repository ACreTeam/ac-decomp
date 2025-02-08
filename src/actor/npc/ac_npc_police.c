#include "ac_npc_police.h"

#include "m_common_data.h"
#include "libultra/libultra.h"
#include "m_msg.h"
#include "m_font.h"
#include "m_string.h"

enum {
    aPOL_ACT_TAISOU,
    aPOL_ACT_NEUM,

    aPOL_ACT_NUM
};

enum {
    aPOL_TALK_END_WAIT,
    aPOL_TALK_CHECK_SELECT,
    aPOL_TALK_CHECK_SELECT2,

    aPOL_TALK_NUM
};

static void aPOL_actor_ct(ACTOR* actorx, GAME* game);
static void aPOL_actor_dt(ACTOR* actorx, GAME* game);
static void aPOL_actor_move(ACTOR* actorx, GAME* game);
static void aPOL_actor_draw(ACTOR* actorx, GAME* game);
static void aPOL_actor_save(ACTOR* actorx, GAME* game);
static void aPOL_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Police_Profile = {
    mAc_PROFILE_NPC_POLICE,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_POLICE,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_POLICE_ACTOR),
    aPOL_actor_ct,
    aPOL_actor_dt,
    aPOL_actor_init,
    mActor_NONE_PROC1,
    aPOL_actor_save,
};
// clang-format on

static void aPOL_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int proc_type);
static void aPOL_setupAction(NPC_POLICE_ACTOR* actor, GAME_PLAY* play, int action);

static void aPOL_talk_request(ACTOR* actorx, GAME* game);
static int aPOL_talk_init(ACTOR* actorx, GAME* game);
static int aPOL_talk_end_chk(ACTOR* actorx, GAME* game);

static void aPOL_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aPOL_actor_move,
        aPOL_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        aPOL_talk_request,
        aPOL_talk_init,
        aPOL_talk_end_chk,
        0,
    };

    if (mEv_check_status(mEv_EVENT_MORNING_AEROBICS, mEv_STATUS_ACTIVE) == TRUE || mEv_check_status(mEv_EVENT_SPORTS_FAIR_AEROBICS, mEv_STATUS_ACTIVE) == TRUE) {
        Actor_delete(actorx);
        actorx->sv_proc = NULL;
        actorx->dt_proc = NULL;
        mNpc_RenewalSetNpc(actorx);
    } else if (CLIP(npc_clip)->birth_check_proc(actorx, game) == TRUE) {
        NPC_POLICE_ACTOR* actor = (NPC_POLICE_ACTOR*)actorx;
        
        actor->npc_class.schedule.schedule_proc = aPOL_schedule_proc;
        CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);
        actorx->status_data.weight = MASSTYPE_HEAVY;
        actor->setup_action_proc = aPOL_setupAction;
        actor->exit_greeting = FALSE;
        mPB_keep_item(*mFI_GetUnitFG(actorx->home.position));
        mFI_SetFG_common(RSV_NO, actorx->home.position, TRUE);
    }
}

static void aPOL_actor_save(ACTOR* actorx, GAME* game) {
    mActor_name_t* fg_p;
    
    CLIP(npc_clip)->save_proc(actorx, game);
    fg_p = mFI_GetUnitFG(actorx->home.position);
    if (fg_p != NULL && *fg_p == RSV_NO) {
        *fg_p = EMPTY_NO;
    }
}

static void aPOL_actor_dt(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->dt_proc(actorx, game);
}

static void aPOL_actor_init(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->init_proc(actorx, game);
}

static void aPOL_actor_draw(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_police_move.c_inc"
