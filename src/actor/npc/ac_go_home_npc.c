#include "ac_go_home_npc.h"

#include "m_common_data.h"
#include "m_font.h"
#include "m_msg.h"

static void aGHN_actor_ct(ACTOR* actorx, GAME* game);
static void aGHN_actor_dt(ACTOR* actorx, GAME* game);
static void aGHN_actor_init(ACTOR* actorx, GAME* game);
static void aGHN_actor_move(ACTOR* actorx, GAME* game);
static void aGHN_actor_draw(ACTOR* actorx, GAME* game);
static void aGHN_actor_save(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Go_Home_Npc_Profile = {
    mAc_PROFILE_GO_HOME_NPC,   ACTOR_PART_NPC, ACTOR_STATE_NONE, EMPTY_NO,         ACTOR_OBJ_BANK_KEEP,
    sizeof(GO_HOME_NPC_ACTOR), &aGHN_actor_ct, &aGHN_actor_dt,   &aGHN_actor_init, mActor_NONE_PROC1,
    &aGHN_actor_save
};

static void aGHN_talk_request(ACTOR* actorx, GAME* game);
static int aGHN_talk_init(ACTOR* actorx, GAME* game);
static int aGHN_talk_end_chk(ACTOR* actorx, GAME* game);

static void aGHN_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = { &aGHN_actor_move, &aGHN_actor_draw,   3, &aGHN_talk_request,
                                      &aGHN_talk_init,  &aGHN_talk_end_chk, 0 };

    if ((*Common_Get(clip).npc_clip->birth_check_proc)(actorx, game) == TRUE) {
        (*Common_Get(clip).npc_clip->ct_proc)(actorx, game, &ct_data);

        /* If the player has already spoken to the NPC, despawn them */
        if ((Common_Get(spnpc_first_talk_flags) & (1 << aNPC_SPNPC_BIT_GOHOME_NPC)) != 0) {
            Actor_delete(actorx);
        }
    }
}

static void aGHN_actor_dt(ACTOR* actorx, GAME* game) {
    (*Common_Get(clip).npc_clip->dt_proc)(actorx, game);
    mEv_actor_dying_message(mEv_EVENT_MASK_NPC, actorx);
}

static void aGHN_actor_save(ACTOR* actorx, GAME* game) {
    (*Common_Get(clip).npc_clip->save_proc)(actorx, game);
}

static void aGHN_actor_init(ACTOR* actorx, GAME* game) {
    (*Common_Get(clip).npc_clip->init_proc)(actorx, game);
}

static void aGHN_actor_draw(ACTOR* actorx, GAME* game) {
    (*Common_Get(clip).npc_clip->draw_proc)(actorx, game);
}

static void aGHN_set_free_str() {
    u8 str[2];
    int fig_start = 2;
    int num = lbRTC_GetIntervalDays(&Save_Get(return_animal).renew_time,
                                    Common_GetPointer(time.rtc_time)); // days since animal left

    if (num < 10) {
        fig_start = 1;
    }

    mFont_UnintToString(str, sizeof(str), num, fig_start, TRUE, FALSE, FALSE);
    mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR0, str, fig_start);
}

static void aGHN_set_talk_info(ACTOR* actorx) {
    int msg_no = MSG_12827 + mNpc_GetNpcLooks(actorx) * 4;

    if ((Common_Get(spnpc_first_talk_flags) & (1 << aNPC_SPNPC_BIT_GOHOME_NPC)) != 0) {
        msg_no += 1 + RANDOM(3);
    }

    mDemo_Set_msg_num(msg_no);
}

static void aGHN_talk_request(ACTOR* actorx, GAME* game) {
    mDemo_Request(mDemo_TYPE_TALK, actorx, &aGHN_set_talk_info);
}

static int aGHN_talk_init(ACTOR* actorx, GAME* game) {
    aNPC_SPNPC_BIT_SET(Common_Get(spnpc_first_talk_flags),
                       aNPC_SPNPC_BIT_GOHOME_NPC);                    // record that the npc has been spoken to before
    Save_Get(return_animal).talk_bit |= (1 << Common_Get(player_no)); // record this player has spoken to the npc
    aGHN_set_free_str();
    mDemo_Set_ListenAble();
    return TRUE;
}

static int aGHN_talk_end_chk(ACTOR* actorx, GAME* game) {
    int res = FALSE;

    if (mDemo_Check(mDemo_TYPE_TALK, actorx) == FALSE) {
        res = TRUE;
    }

    return res;
}

static void aGHN_actor_move(ACTOR* actorx, GAME* game) {
    (*Common_Get(clip).npc_clip->move_proc)(actorx, game);
}
