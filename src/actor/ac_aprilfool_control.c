#include "ac_aprilfool_control.h"

#include "m_event.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "libultra/libultra.h"

static void aAPC_actor_ct(ACTOR* actor, GAME* game);
static void aAPC_actor_dt(ACTOR* actor, GAME* game);

ACTOR_PROFILE Aprilfool_Control_Profile = {
    mAc_PROFILE_APRILFOOL_CONTROL,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(APRILFOOL_CONTROL_ACTOR),
    &aAPC_actor_ct,
    &aAPC_actor_dt,
    mActor_NONE_PROC1,
    mActor_NONE_PROC1,
    NULL,
};

static int aAPC_talk_chk_proc(mActor_name_t actor_name);
static void aAPC_talk_set_proc(mActor_name_t actor_name);
static int aAPC_get_msg_num_proc(mActor_name_t actor_name, int update_talked);

static void aAPC_actor_ct(ACTOR* actor, GAME* game) {
    APRILFOOL_CONTROL_ACTOR* aprilfool_control = (APRILFOOL_CONTROL_ACTOR*)actor;
    aAPC_event_save_data_c* save_data;

    if (Common_Get(clip).aprilfool_control_clip == NULL) {
        Common_Get(clip).aprilfool_control_clip = &aprilfool_control->clip;
    }

    save_data = (aAPC_event_save_data_c*)mEv_get_save_area(mEv_EVENT_APRILFOOLS_DAY, 0);
    if (save_data == NULL) {
        save_data = (aAPC_event_save_data_c*)mEv_reserve_save_area(mEv_EVENT_APRILFOOLS_DAY, 0);
        bzero(save_data, sizeof(aAPC_event_save_data_c));
    }

    Common_Get(clip).aprilfool_control_clip->talk_chk_proc = &aAPC_talk_chk_proc;
    Common_Get(clip).aprilfool_control_clip->talk_set_proc = &aAPC_talk_set_proc;
    Common_Get(clip).aprilfool_control_clip->get_msg_num_proc = &aAPC_get_msg_num_proc;
    Common_Get(clip).aprilfool_control_clip->event_save_data_p = save_data;
}

static void aAPC_actor_dt(ACTOR* actor, GAME* game) {
    Common_Get(clip).aprilfool_control_clip = NULL;
    mEv_actor_dying_message(mEv_EVENT_APRILFOOLS_DAY, actor);
}

typedef struct aprilfool_npc_data_s {
    mActor_name_t actor_name;
    u16 data_idx;
} aAPC_npc_data_c;

static int aAPC_get_data_idx(mActor_name_t actor_name) {
    static aAPC_npc_data_c npc_data_table[11] = {
        { SP_NPC_STATION_MASTER, 0x0000 }, /* Porter */
        { SP_NPC_SHOP_MASTER, 0x0001 },    /* Tom Nook */
        { SP_NPC_CURATOR, 0x0002 },        /* Blathers */
        { SP_NPC_NEEDLEWORK0, 0x0003 },    /* Mable */
        { SP_NPC_NEEDLEWORK1, 0x0004 },    /* Sable */
        { SP_NPC_POLICE, 0x0005 },         /* Copper */
        { SP_NPC_POLICE2, 0x0006 },        /* Booker */
        { SP_NPC_POST_GIRL, 0x0007 },      /* Pelly */
        { SP_NPC_POST_GIRL2, 0x0008 },     /* Phyllis */
        { SP_NPC_POST_MAN, 0x0009 },       /* Pete */
        { SP_NPC_SENDO, 0x000A }           /* Kapp'n */
    };

    aAPC_npc_data_c* npc_data_p = npc_data_table;
    int i;
    int res = -1;

    for (i = 0; i < 11; i++) {
        if (npc_data_p->actor_name == actor_name) {
            res = npc_data_p->data_idx;
            break;
        }

        npc_data_p++;
    }

    return res;
}

static int aAPC_talk_chk_proc(mActor_name_t actor_name) {
    int res = TRUE;

    if (mLd_PlayerManKindCheck() == FALSE) {
        int data_idx = aAPC_get_data_idx(actor_name);

        if (data_idx != -1) {
            u16 bitfield =
                Common_Get(clip).aprilfool_control_clip->event_save_data_p->talk_bitfield[Common_Get(player_no)];

            if (aAPC_GET_NPC_BIT(bitfield, data_idx) == 0) {
                res = FALSE;
            }
        }
    }

    return res;
}

static void aAPC_talk_set_proc(mActor_name_t actor_name) {
    int data_idx = aAPC_get_data_idx(actor_name);

    if (data_idx != -1) {
        u16* bitfield =
            &Common_Get(clip).aprilfool_control_clip->event_save_data_p->talk_bitfield[Common_Get(player_no)];
        data_idx = 1 << data_idx;

        bitfield[0] |= data_idx;
    }
}

static int aAPC_get_msg_num_proc(mActor_name_t actor_name, int update_talked) {
    static int msg_num_table[11] = { 0x3BB5, 0x3BAC, 0x3BB0, 0x3BB1, 0x3BB2, 0x3BB3,
                                     0x3BB4, 0x3BAE, 0x3BAF, 0x3BAD, 0x3BB6 };

    int data_idx = aAPC_get_data_idx(actor_name);
    int msg_num = -1;

    if (data_idx != -1) {
        if (update_talked == TRUE) {
            u16* bitfield =
                &Common_Get(clip).aprilfool_control_clip->event_save_data_p->talk_bitfield[Common_Get(player_no)];

            bitfield[0] = aAPC_SET_NPC_BIT(bitfield[0], data_idx);
        }

        msg_num = msg_num_table[data_idx];
    }

    return msg_num;
}
